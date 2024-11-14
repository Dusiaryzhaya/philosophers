/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anilchen <anilchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:38:03 by anilchen          #+#    #+#             */
/*   Updated: 2024/11/11 17:25:18 by anilchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	goodbye(t_shared_data *shared_data, t_philo *philos)
{
	pthread_mutex_lock(&shared_data->dead_flag_mutex);
	if (!shared_data->dead_flag)
	{
		shared_data->dead_flag = 1;
		logs_msg(0, philos);
	}
	pthread_mutex_unlock(&shared_data->dead_flag_mutex);
}

int	if_finish(t_shared_data *shared_data, t_philo *philos, int *finished)
{
	long	current_time;
	long	time_since_last_meal;

	pthread_mutex_lock(&philos->meal_time_mutex);
	current_time = get_cur_timestamp(shared_data);
	time_since_last_meal = current_time - philos->last_meal_time;
	if (time_since_last_meal >= shared_data->time_to_die)
	{
		pthread_mutex_unlock(&philos->meal_time_mutex);
		return (1);
	}
	else if (shared_data->notepme != -1
		&& philos->meals_eaten >= shared_data->notepme)
	{
		(*finished)++;
	}
	pthread_mutex_unlock(&philos->meal_time_mutex);
	return (0);
}

int	check_philosophers(t_shared_data *shared, t_philo **philos, int *finished)
{
	int	i;

	i = 0;
	*finished = 0;
	while (i < shared->number_of_philosophers)
	{
		if (if_finish(shared, philos[i], finished))
		{
			goodbye(shared, philos[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*waiter_function(void *arg)
{
	t_waiter_args	*args;
	t_shared_data	*shared;
	t_philo			**philos;
	int				finished_philosophers;

	args = (t_waiter_args *)arg;
	shared = args->shared_data;
	philos = args->philos;
	while (1)
	{
		if (check_philosophers(shared, philos, &finished_philosophers))
			return (NULL);
		if (shared->notepme != -1
			&& finished_philosophers == shared->number_of_philosophers)
			break ;
		usleep(1000);
	}
	return (NULL);
}
