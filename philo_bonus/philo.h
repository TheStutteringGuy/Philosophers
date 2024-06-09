/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:00:13 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/06/09 23:51:15 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <strings.h>
# include <sys/stat.h>
# include <sys/time.h>
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

#endif
