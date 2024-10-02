/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouar42 <nbelouar42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:50:25 by nbelouar42        #+#    #+#             */
/*   Updated: 2024/05/28 08:59:03 by nbelouar42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_print(table *t,char *str,clock_t td, int id)
{
    pthread_mutex_lock(&t->print_mutex);
    
    printf(str,(td - t->start_time),id);
    pthread_mutex_unlock(&t->print_mutex);
}
// gerez le cas ou il n y a que 1 philo (il doit mourire au bout de time_to_die)
 void    eating(philosopher *p)
{
    pthread_mutex_lock(p->table->monitor_read);
    table *t = p->table;
    pthread_mutex_unlock(p->table->monitor_read);
    
    pthread_mutex_lock(p->g_fork);
    if (t->number_philo == 1)
	{
		ft_sleep(t->time_to_die);
		pthread_mutex_unlock(p->g_fork);
		return;
	}
    pthread_mutex_lock(p->d_fork);
    ft_print(t,"%ld Philo %d has taken a fork\n", get_time(), p->id);
    ft_sleep(t->time_to_eat);
    ft_print(t,"%ld Philo %d is eating\n", get_time(), p->id);
    pthread_mutex_lock(t->monitor_read);
    p->nb_meals_eaten++;
    p->last_meal = get_time();
    pthread_mutex_unlock(t->monitor_read);
    pthread_mutex_unlock(p->d_fork);
    pthread_mutex_unlock(p->g_fork);
}
void    lock_mutex_monitor(table *t)
{
    int i;
    i = 0;
    while(i != t->number_philo)
    {
        pthread_mutex_lock(&t->monitor_read[i]);
        i++;
    }
}
void *job_monitor(void *arg)
{
    table *t = (table *)arg;
    int i;
    int time;

    i = 0;
    philosopher *p = &t->philosophers[i];
    while (1)
    {
        pthread_mutex_lock(&t->monitor_read[i]);
        if (p->nb_meals != p->nb_meals_eaten)
        {
            if (p->nb_meals_eaten == 0)
                time = get_time() - t->start_time;
            if (p->nb_meals_eaten > 0)
                time = get_time() - p->last_meal;
            pthread_mutex_unlock(&t->monitor_read[i]);
            if (time >= t->time_to_die)
            {
                //lock_mutex_monitor(t);
                ft_print(t, "/////////////////////%ld ms Philo %d has died///////////////////\n", get_time(), p->id);
                exit(0);
            }
        }
        i = (i + 1) % t->number_philo;
    }
    pthread_exit(0);
}

        
        

void  *job_philosopher(void *arg) 
{
    philosopher *p = (philosopher *)arg;
    table *t = p->table;
    if (p->id % 2 == 0 && p->nb_meals_eaten == 0)
       usleep(0.42 * t->time_to_eat);
        
    while(p->nb_meals_eaten < p->nb_meals)
    {
        eating(p);
        p->nb_meals_eaten++;
        ft_print(t,"%ld Philo %d is sleeping\n",get_time(),p->id);
        ft_sleep(t->time_to_sleep); 
        ft_print(t,"%ld Philo %d  is thinking\n",get_time(),p->id);
    }
    pthread_exit(0);
}


void    init_fork(table *t)
{
    int i;
    i = 0;
    while(i != t->number_philo)
    {
        pthread_mutex_init(&t->fork[i], NULL);
        i++;
    }
}
void    init_monitor(table *t)
{
    int i;
    i = 0;
    while(i != t->number_philo)
    {
        pthread_mutex_init(&t->monitor_read[i], NULL);
        i++;
    }
}
void   init_mutex(table *t)
{
    
    pthread_mutex_init(&t->print_mutex, NULL);
}
int	init_table(table *t, char **argv)
{
    int i;
    i = 0;
	t->time_to_die = ft_atoi(argv[2]);
	t->time_to_eat = ft_atoi(argv[3]);
	t->time_to_sleep = ft_atoi(argv[4]);
	t->number_philo = ft_atoi(argv[1]);
    
    init_fork(t);
    init_mutex(t);
    init_monitor(t);

    while(i != t->number_philo)
    {
        
		philosopher *p = &t->philosophers[i];
        p->nb_meals = ft_atoi(argv[5]);
        if(argv[5] == NULL)
            p->nb_meals = MAX_MEALS;
        p->id = i+1;
        p->table = t;
        p->nb_meals_eaten = 0;
        p->monitor = &t->monitor_read[i];
        p->g_fork = &t->fork[i];
        p->d_fork = &t->fork[(i + 1) % t->number_philo];
        p->die = 0;
        if (pthread_create(&p->thread_id, NULL, &job_philosopher, (void *)p))
            return (printf("erreur a la creation du thread\n"));
		i++;
    }
 pthread_create(&t->monitor, NULL, &job_monitor, (void *)t);
    return(0);
}

