/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anilchen <anilchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:25:19 by anilchen          #+#    #+#             */
/*   Updated: 2024/11/11 16:35:37 by anilchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_cur_timestamp(t_shared_data *shared_data)
{
	struct timeval	tv;

	pthread_mutex_lock(&shared_data->time_mutex);
	gettimeofday(&tv, NULL);
	pthread_mutex_unlock(&shared_data->time_mutex);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	find_corpse(t_philo *philos)
{
	int	dead;

	dead = 0;
	pthread_mutex_lock(&philos->shared_data->dead_flag_mutex);
	dead = philos->shared_data->dead_flag;
	pthread_mutex_unlock(&philos->shared_data->dead_flag_mutex);
	return (dead);
}

void	logs_msg(int action_flag, t_philo *philos)
{
	long	cur_timestamp;

	pthread_mutex_lock(&philos->shared_data->log_mutex);
	cur_timestamp = get_cur_timestamp(philos->shared_data)
		- philos->shared_data->start_timestamp;
	if (action_flag == 0)
	{
		if (!philos->shared_data->is_dead_logged)
		{
			philos->shared_data->is_dead_logged = 1;
			printf(RED "%ld %d died\n" RESET, cur_timestamp,
				philos->philosopher_id);
		}
	}
	else if (action_flag == 1)
		printf("%ld %d is eating\n", cur_timestamp, philos->philosopher_id);
	else if (action_flag == 2)
		printf("%ld %d is sleeping\n", cur_timestamp, philos->philosopher_id);
	else if (action_flag == 3)
		printf("%ld %d is thinking\n", cur_timestamp, philos->philosopher_id);
	else if (action_flag == 4)
		printf("%ld %d has taken a fork\n", cur_timestamp,
			philos->philosopher_id);
	pthread_mutex_unlock(&philos->shared_data->log_mutex);
}

void	finish_simulation(t_philo **philosophers, t_shared_data *shared_data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&shared_data->dead_flag_mutex);
	pthread_mutex_destroy(&shared_data->log_mutex);
	pthread_mutex_destroy(&shared_data->time_mutex);
	while (i < shared_data->number_of_philosophers)
	{
		pthread_mutex_destroy(&shared_data->forks[i]);
		pthread_mutex_destroy(&philosophers[i]->meal_time_mutex);
		free(philosophers[i]);
		i++;
	}
	free(philosophers);
	free(shared_data->forks);
	free(shared_data->threads);
}

// special case
void	single_philosopher_must_die(t_philo *philos)
{
	pthread_mutex_lock(&philos->shared_data->forks[philos->left_fork]);
	logs_msg(4, philos);
	usleep(philos->shared_data->time_to_die * 1000);
	pthread_mutex_unlock(&philos->shared_data->forks[philos->left_fork]);
	logs_msg(0, philos);
	pthread_mutex_lock(&philos->shared_data->dead_flag_mutex);
	philos->shared_data->dead_flag = 1;
	pthread_mutex_unlock(&philos->shared_data->dead_flag_mutex);
}
