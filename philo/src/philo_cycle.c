/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anilchen <anilchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:34:38 by anilchen          #+#    #+#             */
/*   Updated: 2024/11/11 16:47:11 by anilchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philos)
{
	long	start_eating;

	if (find_corpse(philos))
		return ;
	logs_msg(1, philos);
	pthread_mutex_lock(&philos->meal_time_mutex);
	philos->last_meal_time = get_cur_timestamp(philos->shared_data);
	pthread_mutex_unlock(&philos->meal_time_mutex);
	start_eating = get_cur_timestamp(philos->shared_data);
	while (get_cur_timestamp(philos->shared_data)
		- start_eating < philos->shared_data->time_to_eat)
	{
		if (find_corpse(philos))
			return ;
		else
			usleep(1000);
	}
	pthread_mutex_unlock(&philos->shared_data->forks[philos->left_fork]);
	pthread_mutex_unlock(&philos->shared_data->forks[philos->right_fork]);
	philos->is_holding_forks = 0;
	pthread_mutex_lock(&philos->meal_time_mutex);
	philos->meals_eaten++;
	pthread_mutex_unlock(&philos->meal_time_mutex);
}

void	change_order(t_philo *philos, int *first_fork, int *second_fork)
{
	if (philos->philosopher_id % 2 == 0)
	{
		usleep(100);
		*(first_fork) = philos->right_fork;
		*(second_fork) = philos->left_fork;
	}
	else
	{
		*(first_fork) = philos->left_fork;
		*(second_fork) = philos->right_fork;
	}
}

void	take_forks(t_philo *philos)
{
	int	first_fork;
	int	second_fork;

	change_order(philos, &first_fork, &second_fork);
	pthread_mutex_lock(&philos->shared_data->forks[first_fork]);
	pthread_mutex_lock(&philos->shared_data->forks[second_fork]);
	if (!find_corpse(philos))
	{
		logs_msg(4, philos);
		logs_msg(4, philos);
		philos->is_holding_forks = 1;
	}
	else
	{
		pthread_mutex_unlock(&philos->shared_data->forks[first_fork]);
		pthread_mutex_unlock(&philos->shared_data->forks[second_fork]);
		philos->is_holding_forks = 0;
	}
}

void	thinking(t_philo *philos)
{
	long	start_thinking;
	long	time_to_think;

	time_to_think = 1;
	if (find_corpse(philos))
		return ;
	logs_msg(3, philos);
	start_thinking = get_cur_timestamp(philos->shared_data);
	while (get_cur_timestamp(philos->shared_data)
		- start_thinking < time_to_think)
	{
		if (find_corpse(philos))
			return ;
		usleep(1000);
	}
}

void	sleeping(t_philo *philos)
{
	long	start_sleeping;

	if (find_corpse(philos))
		return ;
	logs_msg(2, philos);
	start_sleeping = get_cur_timestamp(philos->shared_data);
	while (get_cur_timestamp(philos->shared_data)
		- start_sleeping < philos->shared_data->time_to_sleep)
	{
		if (find_corpse(philos))
			return ;
		else
			usleep(1000);
	}
}
