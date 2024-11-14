/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anilchen <anilchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:26:16 by anilchen          #+#    #+#             */
/*   Updated: 2024/11/05 13:21:30 by anilchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

static void	ft_skip_whitespace(const char *str, int *i)
{
	while (str[*i] == ' ' || (str[*i] >= '\t' && str[*i] <= '\r'))
	{
		(*i)++;
	}
}

static void	ft_handle_sign(const char *str, int *i, int *sign)
{
	if (str[*i] == '-')
	{
		*sign = -1;
		(*i)++;
	}
	else if (str[*i] == '+')
	{
		(*i)++;
	}
}

static int	ft_convert_digits(const char *str, int *i, long *res)
{
	int	digit;

	while (ft_isdigit(str[*i]))
	{
		digit = str[*i] - '0';
		*res = *res * 10 + digit;
		(*i)++;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	res;
	int		i;

	sign = 1;
	res = 0;
	i = 0;
	ft_skip_whitespace(str, &i);
	ft_handle_sign(str, &i, &sign);
	ft_convert_digits(str, &i, &res);
	return (res * sign);
}
