/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anilchen <anilchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:52:31 by anilchen          #+#    #+#             */
/*   Updated: 2024/11/07 13:52:40 by anilchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_number(const char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_arguments(int argc, const char *argv[])
{
	int	i;
	int	min_args;
	int	max_args;

	i = 1;
	min_args = 5;
	max_args = 6;
	if (argc < min_args || argc > max_args)
	{
		printf(RED "Error: number of arguments should be 4 or 5.\n" RESET);
		return (0);
	}
	while (i < argc)
	{
		if (!is_number(argv[i]))
		{
			printf(RED "Error: arguments must be positive integers\n" RESET);
			return (0);
		}
		i++;
	}
	return (1);
}
