/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:09:46 by plangloi          #+#    #+#             */
/*   Updated: 2024/05/13 10:44:03 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int ac, char **av)
{
	t_data			data;
	t_philo			*philos;
	t_data_shared	data_shared;
	pthread_mutex_t	*forks;

	if (ac >= 5 && ac <= 6)
	{
		if (check_input(av, &data_shared) == 1)
			return (1);
		philos = malloc(sizeof(t_philo) * ft_atoi(av[1]));
		if (!philos)
			return (write(2, "Error: malloc\n", 14), 1);
		forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
		if (!forks)
			return (write(2, "Error: malloc\n", 14), free(philos), 1);
		init_data(&data, philos);
		init_forks(forks, ft_atoi(av[1]));
		init_philo(philos, &data, &data_shared, forks);
		create_thread(&data, forks);
		free(philos);
		free(forks);
	}
	return (0);
}
