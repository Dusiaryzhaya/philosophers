/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anilchen <anilchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:45:46 by anilchen          #+#    #+#             */
/*   Updated: 2024/11/11 16:49:45 by anilchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <fcntl.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define RESET "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[32m"

typedef struct s_shared_data
{
	int				dead_flag;
	int				number_of_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				notepme;
	long			start_timestamp;
	int				is_dead_logged;
	pthread_t		*threads;
	pthread_t		waiter_thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t	dead_flag_mutex;
	pthread_mutex_t	log_mutex;
	pthread_mutex_t	time_mutex;
	pthread_mutex_t	waiter_mutex;
}					t_shared_data;

typedef struct s_philo
{
	int				philosopher_id;
	long			last_meal_time;
	int				is_holding_forks;
	int				meals_eaten;
	int				left_fork;
	int				right_fork;
	pthread_mutex_t	meal_time_mutex;
	t_shared_data	*shared_data;
}					t_philo;

typedef struct s_waiter_args
{
	t_shared_data	*shared_data;
	t_philo			**philos;
}					t_waiter_args;

/* ************************************************************************** */
/*                            ft_atoi functions                               */
/* ************************************************************************** */

int					ft_atoi(const char *str);

/* ************************************************************************** */
/*                                   Utils                                    */
/* ************************************************************************** */

long				get_cur_timestamp(t_shared_data *shared_data);
void				logs_msg(int action_flag, t_philo *philos);
int					find_corpse(t_philo *philos);
void				finish_simulation(t_philo **philosophers,
						t_shared_data *shared_data);
void				single_philosopher_must_die(t_philo *philos);

/* ************************************************************************** */
/*                                Philo_cycle                                 */
/* ************************************************************************** */

void				eating(t_philo *philos);
void				take_forks(t_philo *philo);
void				thinking(t_philo *philos);
void				sleeping(t_philo *philos);

/* ************************************************************************** */
/*                                manage life                                 */
/* ************************************************************************** */

// void				*goodbye(t_philo *philos);
void				*philosopher_life(t_philo *philos);
void				*philosopher_life_management(void *arg);

/* ************************************************************************** */
/*                             check arguments                                */
/* ************************************************************************** */

int					check_arguments(int argc, const char *argv[]);

/* ************************************************************************** */
/*                             waiter function                                */
/* ************************************************************************** */

void				*waiter_function(void *arg);

#endif