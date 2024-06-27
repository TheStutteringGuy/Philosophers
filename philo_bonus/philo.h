/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:00:13 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/06/27 06:18:01 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <strings.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <time.h>
# include <unistd.h>

# define TRUE 1

// STRUCTS :

typedef struct s_data
{
	long	number_of_philosophers;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	philosopher_must_eat;
	pid_t	*pids;
	sem_t	*forks;
	sem_t	*print_sem;
	sem_t	*dead_sem;
	sem_t	*meal_sem;
	long	start;
	long	last_eat;
	long	seat;
	long	*meals;
	long	*dead_notice;
	long	*meal_notice;
	sem_t	*dead_process;
}			t_data;

// PROTOTYPES :

// Parsing :

void		ft_stderr(char *str);
void		ft_stdout(char *str);
int			pars_arg(int ac, char **av);
long		ft_atol(const char *str);
int			zero_five(int ac, char **av);
int			check_time(void);
int			get_time(void);

// Philo :

int			forking(t_data *data);
int			initialize_sem(t_data *data);
void		clean_everything(t_data *data);
void		philo_print(char *str, t_data *data);
void		wait_forks(t_data *data);
void		post_forks(t_data *data);
int			initalize_notice(t_data *data);
int			check(t_data *data);
void		fix_time(t_data *data);
void		add_meals(t_data *data);
void		my_usleep(long time);
void		philo_sleep(t_data *data, long time);
int			case_one(t_data *data);
void		philo_think(t_data *data);
void		philo_dead(char *str, t_data *data);
void		clean_everything_process(t_data *data);
int			done_eating(t_data *data);

#endif
