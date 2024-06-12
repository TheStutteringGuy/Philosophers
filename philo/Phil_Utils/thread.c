/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 06:25:11 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/06/12 00:23:13 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	destroy_everything(t_philos *philos, pthread_mutex_t **forks)
{
	long	i;

	i = 0;
	while (i < philos[0].info->number_of_philosophers)
	{
		pthread_mutex_destroy(forks[i]);
		free(forks[i]);
		++i;
	}
	free(forks);
	pthread_mutex_destroy(philos->info->print_mutex);
	free(philos->info->print_mutex);
	pthread_mutex_destroy(philos->info->dead_mutex);
	free(philos->info->dead_mutex);
	free(philos->info->dead_notice);
	free(philos->info->meal_notice);
	free(philos);
}

void	init_philos(t_data *data, t_philos *philos, pthread_mutex_t **forks)
{
	long	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		philos[i].info = data;
		philos[i].seat = i + 1;
		philos[i].meals = 0;
		philos[i].r_fork = forks[i];
		if (data->number_of_philosophers != 1)
		{
			if (i == 0)
				philos[i].l_fork = forks[data->number_of_philosophers - 1];
			else
				philos[i].l_fork = forks[i - 1];
		}
		pthread_mutex_init(&philos[i].statue_mutex, NULL);
		i++;
	}
}

int	thread(t_data *data)
{
	t_philos		*philos;
	pthread_mutex_t	**forks;

	philos = malloc(sizeof(t_philos) * data->number_of_philosophers);
	if (philos == NULL)
	{
		return_fail(data);
		return (-1);
	}
	forks = malloc(sizeof(pthread_mutex_t *) * data->number_of_philosophers);
	if (forks == NULL)
	{
		return_fail2(philos, data);
		return (-1);
	}
	if (thread_norm(philos, forks, data) == -1)
		return (-1);
	init_philos(data, philos, forks);
	thread_create(philos);
	destroy_everything(philos, forks);
	return (0);
}
