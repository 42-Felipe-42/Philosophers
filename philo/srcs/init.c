/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:55:25 by felipe            #+#    #+#             */
/*   Updated: 2024/05/10 11:42:18 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_data(t_data *data, t_philo *philos)
{
	data->dead_flag = 0;
	data->philos = philos;
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
}

void	init_forks(pthread_mutex_t *forks, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	init_philo(t_philo *philo, t_data *data, t_data_shared *data_shared,
		pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < data_shared->nb_of_philos)
	{
		philo[i].id = i + 1;
		philo[i].eating = 0;
		philo[i].nb_time_eat = 0;
		philo[i].data_shared = data_shared;
		philo[i].start_time = get_time();
		philo[i].last_meal = get_time();
		philo[i].write_lock = &data->write_lock;
		philo[i].dead_lock = &data->dead_lock;
		philo[i].meal_lock = &data->meal_lock;
		philo[i].dead = &data->dead_flag;
		philo[i].left_fork = &forks[i];
		if (i == 0)
			philo[i].right_fork = &forks[data_shared->nb_of_philos - 1];
		else
			philo[i].right_fork = &forks[i - 1];
		i++;
	}
}
