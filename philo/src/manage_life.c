/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_life.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anilchen <anilchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:55:01 by anilchen          #+#    #+#             */
/*   Updated: 2024/11/11 17:12:16 by anilchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher_life(t_philo *philos)
{
	long	cur_timestamp;

	while (!find_corpse(philos))
	{
		take_forks(philos);
		eating(philos);
		sleeping(philos);
		thinking(philos);
		if (philos->shared_data->notepme != -1
			&& philos->meals_eaten >= philos->shared_data->notepme
			&& !find_corpse(philos))
		{
			cur_timestamp = get_cur_timestamp(philos->shared_data)
				- philos->shared_data->start_timestamp;
			pthread_mutex_lock(&philos->shared_data->log_mutex);
			printf(GREEN "%ld Philosopher %d finished.\n" RESET, cur_timestamp,
				philos->philosopher_id);
			pthread_mutex_unlock(&philos->shared_data->log_mutex);
			break ;
		}
	}
	return (NULL);
}

void	*philosopher_life_management(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	if (philos->shared_data->number_of_philosophers == 1)
	{
		single_philosopher_must_die(philos);
		return (NULL);
	}
	philosopher_life(philos);
	if (philos->is_holding_forks)
	{
		pthread_mutex_unlock(&philos->shared_data->forks[philos->left_fork]);
		pthread_mutex_unlock(&philos->shared_data->forks[philos->right_fork]);
		philos->is_holding_forks = 0;
	}
	return (NULL);
}
