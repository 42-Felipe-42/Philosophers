/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plangloi <plangloi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:01:27 by plangloi          #+#    #+#             */
/*   Updated: 2024/05/13 14:22:38 by plangloi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define RESETCOLOR "\033[0m"
# define ROUGE "\033[0;31m"
# define VERT "\033[0;32m"
# define PRINT_DIE "died 💀"
# define PRINT_EAT "is eating 🍜"
# define TAKE_FORK "has taken a fork 🥢"
# define SLEEPING "is sleeping 🛌"
# define THINKING "is thinking 🤔💭"

typedef struct s_data_shared
{
	int				nb_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals_to_eat;
}					t_data_shared;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				nb_time_eat;
	size_t			last_meal;
	size_t			start_time;
	int				*dead;
	t_data_shared	*data_shared;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_data
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_data;

/**********************************\
*        INITIALISATION			   *
\**********************************/
void				init_philo(t_philo *philo, t_data *data,
						t_data_shared *data_shared, pthread_mutex_t *forks);
void				init_forks(pthread_mutex_t *forks, int nb_philo);
void				init_data(t_data *data, t_philo *philos);
/**********************************\
*        THREADS/ROUTINE		   *
\**********************************/
void				is_thinking(t_philo *philo);
void				is_sleeping(t_philo *philo);
void				is_eating(t_philo *philo);
int					philo_dead(t_philo *philo, int index, size_t time_to_die);
void				*monitor(void *arg);
int					check_if_all_ate(t_philo *philo,
						t_data_shared *data_shared);
int					he_was_die(t_philo *philo);
void				*philo_routine(void *arg);
int					create_thread(t_data *data, pthread_mutex_t *forks);
void				destroy_all(char *str, t_data *data, t_philo *philo,
						pthread_mutex_t *forks);
/**********************************\
*              UTILS			   *
\**********************************/
int					ft_atoi(const char *nptr);
int					check_input(char **av, t_data_shared *data_shared);
int					ft_usleep(size_t milliseconds);
void				print_msg(char *str, t_philo *philo, int id);
size_t				get_time(void);
#endif

// Les philosophes alternativement mangent, dorment ou pensent.
// Pendant qu’ils mangent, ils ne pensent ni ne dorment,
// pendant qu’ils pensent, ils ne mangent ni ne dorment
// et, bien sûr, pendant leur sommeil, ils ne mangent ni ne pensent.
