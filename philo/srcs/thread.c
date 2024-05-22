/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:58:35 by plangloi          #+#    #+#             */
/*   Updated: 2024/05/15 10:32:40 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	create_thread(t_data *data, pthread_mutex_t *forks)
{
	pthread_t	observer;
	int			i;

	i = 0;
	if (pthread_create(&observer, NULL, &monitor, data->philos) != 0)
		destroy_all("Thread creation", data, data->philos, forks);
	while (i < data->philos[0].data_shared->nb_of_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &philo_routine,
				&data->philos[i]) != 0)
			destroy_all("Thread creation", data, data->philos, forks);
		i++;
	}
	i = 0;
	if (pthread_join(observer, NULL) != 0)
		destroy_all("Thread join", data, data->philos, forks);
	while (i < data->philos[0].data_shared->nb_of_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			destroy_all("Thread join", data, data->philos, forks);
		i++;
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_philo			*philo;
	t_data_shared	*data_shared;
	int				philo_died;
	int				index;

	philo = (t_philo *)arg;
	data_shared = philo->data_shared;
	philo_died = 0;
	while (1)
	{
		index = 0;
		while (index < data_shared->nb_of_philos)
		{
			if (philo_dead(philo, index, data_shared->time_to_die))
			{
				philo_died = 1;
				break ;
			}
			index++;
		}
		if (philo_died || check_if_all_ate(philo, data_shared))
			break ;
	}
	return (arg);
}

// void	*monitor(void *arg)
// {
// 	t_philo			*philo;
// 	t_data_shared	*data_shared;
// 	int				philo_died;
// 	int				index;

// 	philo = (t_philo *)arg;
// 	data_shared = philo->data_shared;
// 	philo_died = 0;
// 	while (1)
// 	{
// 		index = 0;
// 		ft_usleep(1000);
// 		while (index < data_shared->nb_of_philos)
// 		{
// 			if (philo_dead(philo, index, data_shared->time_to_die))
// 			{
// 				philo_died = 1;
// 				break ;
// 			}
// 			index++;
// 		}
// 		if (philo_died || check_if_all_ate(philo, data_shared))
// 			break ;
// 	}
// 	return (arg);
// }
