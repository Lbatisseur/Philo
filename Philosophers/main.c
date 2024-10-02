/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbelouar42 <nbelouar42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:22:20 by nbelouar42        #+#    #+#             */
/*   Updated: 2024/05/28 08:53:55 by nbelouar42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_number(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	return (0);
}



int	check_args(char **argv)
{
	if (ft_atoi(argv[1]) > 200 || ft_atoi(argv[1]) <= 0
		|| check_number(argv[1]) == 1)
		return (write(2, "Nombre de philosophe invalide\n", 31), 1);
	if (ft_atoi(argv[2]) <= 0 || check_number(argv[2]) == 1)
		return (write(2, "Time to die invalide\n", 22), 1);
	if (ft_atoi(argv[3]) <= 0 || check_number(argv[3]) == 1)
		return (write(2, "Time to eat invalide\n", 22), 1);
	if (ft_atoi(argv[4]) <= 0 || check_number(argv[4]) == 1)
		return (write(2, "Time to sleep invalide\n", 24), 1);
	if (argv[5] && (ft_atoi(argv[5]) < 0 || check_number(argv[5]) == 1))
		return (write(2, "Nombre de fois ou les philosophes doivent manger invalide\n",
				59), 1); // traiter le cas ou il n y a pas cette argument
	return (0);
}

int main(int argc, char **argv)
{
	table t;
	if (argc != 5 && argc != 6)
		return (write(2, "erreur arg\n", 11), 1);
	int i = 0;
	
	t.start_time = get_time();
	
	if (check_args(argv))
		return (1);
	if(init_table(&t, argv) != 0)
	{
		printf("Erreur lors de l'initialisation de la table\n");
		return (1);
	}
		pthread_join(t.monitor, NULL);
	while(i < t.number_philo)
	{
		pthread_join(t.philosophers[i].thread_id, NULL);
		 i++;
	}
	printf("/////////fin du programme /////////////\n");
	return 0;
}
