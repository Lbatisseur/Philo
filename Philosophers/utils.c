/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouar42 <nbelouar42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:36:44 by nbelouar42        #+#    #+#             */
/*   Updated: 2024/05/23 23:49:14 by nbelouar42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"


int	ft_sleep(size_t time)
{
	size_t start;

	start = get_time();
	while (get_time() - start < time)
		usleep(50);
	return (0);
}

size_t get_time() 
{
    struct timeval time;
   if(gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
       return (time.tv_sec * 1000 + time.tv_usec / 1000);
}



int	ft_deadspace(int c)
{
	if (c == 9 || c == 10 || c == 11 || c == 12 || c == 13 || c == 32)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	if(!str)
		return (0);
	while (ft_deadspace(str[i]))
		i++;
	if (str[i] == '+' && str[i + 1] != '-')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] && str[i] >= 48 && str[i] <= 57)
	{
		result *= 10;
		result += str[i] - 48;
		i++;
	}
	result *= sign;
	return (result);
}