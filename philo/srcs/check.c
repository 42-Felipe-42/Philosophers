/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:27:47 by plangloi          #+#    #+#             */
/*   Updated: 2024/05/13 14:25:15 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_input(char **av, t_data_shared *data_shared)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_atoi(av[i]) == -1 || (ft_atoi(av[1]) <= 0
				|| ft_atoi(av[1]) > 200))
		{
			printf("No valid arguments!\n");
			return (1);
		}
		i++;
	}
	data_shared->nb_of_philos = ft_atoi(av[1]);
	data_shared->time_to_die = ft_atoi(av[2]);
	data_shared->time_to_eat = ft_atoi(av[3]);
	data_shared->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data_shared->nb_meals_to_eat = ft_atoi(av[5]);
	else
		data_shared->nb_meals_to_eat = -2;
	return (0);
}

int	philo_dead(t_philo *philo, int index, size_t time_to_die)
{
	pthread_mutex_lock(philo[index].meal_lock);
	if (get_time() - philo[index].last_meal >= time_to_die
		&& !philo[index].eating)
	{
		pthread_mutex_unlock(philo[index].meal_lock);
		print_msg(ROUGE PRINT_DIE RESETCOLOR, &philo[index], philo[index].id);
		pthread_mutex_lock(philo[0].dead_lock);
		*philo->dead = 1;
		pthread_mutex_unlock(philo[0].dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo[index].meal_lock);
	return (0);
}

int	check_if_all_ate(t_philo *philo, t_data_shared *data_shared)
{
	int	i;
	int	eat;

	i = -1;
	eat = 0;
	if (data_shared->nb_meals_to_eat == -2)
		return (0);
	while (++i < data_shared->nb_of_philos)
	{
		pthread_mutex_lock(philo[i].meal_lock);
		if (philo[i].nb_time_eat >= data_shared->nb_meals_to_eat)
			eat++;
		pthread_mutex_unlock(philo[i].meal_lock);
	}
	if (eat == philo[0].data_shared->nb_of_philos)
	{
		pthread_mutex_lock(philo[0].dead_lock);
		*philo->dead = 1;
		pthread_mutex_unlock(philo[0].dead_lock);
		if (data_shared->nb_meals_to_eat != 0)
			printf(VERT "All the philo have eaten %d times \n" RESETCOLOR,
				data_shared->nb_meals_to_eat);
		return (1);
	}
	return (0);
}

int	he_was_die(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	destroy_all(char *str, t_data *data, t_philo *philo,
		pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (str)
		printf("Error : %s\n", str);
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->dead_lock);
	while (i < philo->data_shared->nb_of_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
	if (philo)
		free(philo);
}
