/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:14:09 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/06/06 23:01:20 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	forks_alloca(pthread_mutex_t **forks, t_data *data)
{
	long	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		forks[i] = malloc(sizeof(pthread_mutex_t));
		if (forks[i] == NULL)
		{
			while (i > 0)
			{
				free(forks[--i]);
			}
			return (0);
		}
		++i;
	}
	return (1);
}

int	init_mutex(t_data *data)
{
	if (pthread_mutex_init(data->print_mutex, NULL) > 0)
		return (0);
	if (pthread_mutex_init(data->dead_mutex, NULL) > 0)
		return (0);
	return (1);
}

int	init_forks(pthread_mutex_t **forks, t_data *data)
{
	long	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_mutex_init(forks[i], NULL) > 0)
		{
			while (i > 0)
			{
				pthread_mutex_destroy(forks[--i]);
			}
			return (0);
		}
		++i;
	}
	return (1);
}

int	thread_norm2(t_philos *philos, pthread_mutex_t **forks, t_data *data)
{
	data->dead_mutex = malloc(sizeof(pthread_mutex_t));
	if (data->dead_mutex == NULL)
	{
		return_fail5(philos, forks, data);
		return (-1);
	}
	if (init_mutex(data) == 0)
	{
		return_fail4(philos, forks, data);
		return (-1);
	}
	return (1);
}

int	thread_norm(t_philos *philos, pthread_mutex_t **forks, t_data *data)
{
	if (forks_alloca(forks, data) == 0)
	{
		return_fail2(philos, data);
		return (-1);
	}
	if (init_forks(forks, data) == 0)
	{
		return_fail3(philos, forks, data);
		return (-1);
	}
	data->print_mutex = malloc(sizeof(pthread_mutex_t));
	if (data->print_mutex == NULL)
	{
		return_fail3(philos, forks, data);
		return (-1);
	}
	if (thread_norm2(philos, forks, data) == -1)
		return (-1);
	return (1);
}
