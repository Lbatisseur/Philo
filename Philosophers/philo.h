/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouar42 <nbelouar42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:48:34 by nbelouar42        #+#    #+#             */
/*   Updated: 2024/07/24 17:33:18 by nbelouar42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Philo
#define Philo

#define MAX_PHILO 200
#define MAX_MEALS 999999999

#include <pthread.h>
#include "stdlib.h"
#include "stdio.h"
#include "unistd.h"
#include "string.h"
#include "sys/time.h"


typedef struct s_philo
{
	int id; // numero du philo
	pthread_t thread_id;// l identitfiant du thread
	struct s_table *table;
	int nb_meals;
	int nb_meals_eaten;
	pthread_mutex_t	*d_fork;
	pthread_mutex_t	*g_fork;
	long long int	last_meal;
	long long int	time_meal;
	pthread_mutex_t *monitor;
	int  die;
	
	
} philosopher;
// recuperer le dernier thread id quand on malloc le tableau de philo pour pouvoir le donner a thread_join

typedef struct s_table 
{
	pthread_t monitor;
	pthread_mutex_t print_mutex;;
    long long start_time;
	pthread_mutex_t fork[MAX_PHILO];
	pthread_mutex_t monitor_read[MAX_PHILO];
	int number_philo; 
	int time_to_die;
	int time_to_sleep;
	int time_to_eat;
	philosopher philosophers[MAX_PHILO];
} table;


int	ft_atoi(const char *str);
int init_table(table *t, char **argv);
size_t get_time();
int	ft_sleep(size_t time);
void ft_print(table *t,char *str,clock_t td, int id);
void eating(philosopher *p);
void *job_monitor(void *arg);
void *job_philosopher(void *arg);
void init_forks(table *t);
void init_mutex(table *t);


#endif