/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:28:03 by plangloi          #+#    #+#             */
/*   Updated: 2024/05/13 10:44:39 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	is_thinking(t_philo *philo)
{
	print_msg(THINKING, philo, philo->id);
}

void	is_sleeping(t_philo *philo)
{
	print_msg(SLEEPING, philo, philo->id);
	ft_usleep(philo->data_shared->time_to_sleep);
}

void	is_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_msg(TAKE_FORK, philo, philo->id);
	if (philo->data_shared->nb_of_philos == 1)
	{
		ft_usleep(philo->data_shared->time_to_die);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	print_msg(TAKE_FORK, philo, philo->id);
	philo->eating = 1;
	print_msg(PRINT_EAT, philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_time();
	philo->nb_time_eat++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->data_shared->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!he_was_die(philo))
	{
		is_eating(philo);
		is_sleeping(philo);
		is_thinking(philo);
	}
	return (arg);
}
