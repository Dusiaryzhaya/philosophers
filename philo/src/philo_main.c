/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anilchen <anilchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:58:25 by anilchen          #+#    #+#             */
/*   Updated: 2024/11/14 12:49:10 by anilchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// number_of_philosophers
// time_to_die
// time_to_eat
// time_to_sleep
//[number_of_times_each_philosopher_must_eat]

void	init_shared_data(t_shared_data *shared_data)
{
	int	i;

	i = 0;
	shared_data->forks = malloc(sizeof(pthread_mutex_t)
			* shared_data->number_of_philosophers);
	shared_data->threads = malloc(sizeof(pthread_t)
			* shared_data->number_of_philosophers);
	if (!shared_data->forks || !shared_data->threads)
	{
		printf("Error allocating memory for forks or threads\n");
		return ;
	}
	while (i < shared_data->number_of_philosophers)
	{
		pthread_mutex_init(&shared_data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&shared_data->dead_flag_mutex, NULL);
	pthread_mutex_init(&shared_data->log_mutex, NULL);
	pthread_mutex_init(&shared_data->time_mutex, NULL);
	shared_data->start_timestamp = get_cur_timestamp(shared_data);
}

void	create_philosophers(t_philo **philosophers, t_shared_data *shared_data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < shared_data->number_of_philosophers)
	{
		philo = malloc(sizeof(t_philo));
		philo->philosopher_id = i + 1;
		philo->meals_eaten = 0;
		philo->left_fork = (philo->philosopher_id - 1
				+ shared_data->number_of_philosophers)
			% shared_data->number_of_philosophers;
		philo->right_fork = philo->philosopher_id
			% shared_data->number_of_philosophers;
		philo->is_holding_forks = 0;
		philo->last_meal_time = get_cur_timestamp(shared_data);
		philo->shared_data = shared_data;
		philosophers[i] = philo;
		pthread_mutex_init(&philo->meal_time_mutex, NULL);
		pthread_create(&shared_data->threads[i], NULL,
			philosopher_life_management, (void *)philo);
		i++;
	}
}

void	simulation(t_shared_data *shared_data)
{
	int				i;
	t_philo			**philosophers;
	t_waiter_args	waiter_args;

	i = 0;
	shared_data->dead_flag = 0;
	shared_data->is_dead_logged = 0;
	init_shared_data(shared_data);
	philosophers = malloc(shared_data->number_of_philosophers
			* sizeof(t_philo *));
	create_philosophers(philosophers, shared_data);
	if (shared_data->number_of_philosophers > 1)
	{
		waiter_args.shared_data = shared_data;
		waiter_args.philos = philosophers;
		pthread_create(&shared_data->waiter_thread, NULL, waiter_function,
			(void *)&waiter_args);
		pthread_join(shared_data->waiter_thread, NULL);
	}
	while (i < shared_data->number_of_philosophers)
	{
		pthread_join(shared_data->threads[i], NULL);
		i++;
	}
	finish_simulation(philosophers, shared_data);
}

int	main(int argc, char const *argv[])
{
	t_shared_data	shared_data;

	if (!check_arguments(argc, argv))
	{
		return (1);
	}
	memset(&shared_data, 0, sizeof(t_shared_data));
	shared_data.number_of_philosophers = ft_atoi(argv[1]);
	if (shared_data.number_of_philosophers == 0)
	{
		printf(RED "Error: there is no philosophers to kill\n" RESET);
		return (1);
	}
	if (argc == 6)
		shared_data.notepme = ft_atoi(argv[5]);
	else
		shared_data.notepme = -1;
	shared_data.time_to_die = ft_atoi(argv[2]);
	shared_data.time_to_eat = ft_atoi(argv[3]);
	shared_data.time_to_sleep = ft_atoi(argv[4]);
	simulation(&shared_data);
	return (0);
}
