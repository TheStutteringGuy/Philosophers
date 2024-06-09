/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 03:06:35 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/06/09 23:51:34 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <strings.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

# define TRUE 1

// STRUCTS :

typedef struct s_data
{
	long			number_of_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			philosopher_must_eat;
	long			time_to_think;
	long			*dead_notice;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*dead_mutex;
}					t_data;

typedef struct s_philos
{
	pthread_t		thread;
	t_data			*info;
	long			start;
	long			last_eat;
	int				seat;
	int				meals;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}					t_philos;

// PROTOTYPES :

// Parsing

void				ft_stderr(char *str);
void				ft_stdout(char *str);
int					pars_arg(int ac, char **av);
long				ft_atol(const char *str);
int					zero_five(int ac, char **av);
int					check_time(void);
int					get_time(void);

// Philo :

int					thread(t_data *data);
int					return_fail(t_data *data);
int					forks_alloca(pthread_mutex_t **forks, t_data *data);
int					return_fail2(t_philos *philos, t_data *data);
int					return_fail3(t_philos *philos, pthread_mutex_t **forks,
						t_data *data);
int					return_fail5(t_philos *philos, pthread_mutex_t **forks,
						t_data *data);
int					return_fail4(t_philos *philos, pthread_mutex_t **forks,
						t_data *data);
void				thread_create(t_philos *philos);
int					thread_norm(t_philos *philos, pthread_mutex_t **forks,
						t_data *data);
void				destroy_everything(t_philos *philos,
						pthread_mutex_t **forks);
void				philo_printf(char *str, t_philos *philo);
void				philo_sleep(t_philos *philo, long time);
int					thread_check(t_philos *philo);
void				lock(t_philos *philo);
void				unlock(t_philos *philo);
void				monitor_lock(t_philos *philos, long j);
void				monitor_unlock(t_philos *philos, long j);
void				philo_printf_dead(char *str, t_philos *philo);
int					case_one_seat(t_philos *philo);

#endif
