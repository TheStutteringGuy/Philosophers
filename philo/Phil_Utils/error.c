/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 06:47:26 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/06/06 23:00:59 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	return_fail(t_data *data)
{
	free(data->dead_notice);
	ft_stderr("Allocating Failed\n");
	return (-1);
}

int	return_fail2(t_philos *philos, t_data *data)
{
	free(data->dead_notice);
	free(philos);
	ft_stderr("Allocating Failed\n");
	return (-1);
}

int	return_fail3(t_philos *philos, pthread_mutex_t **forks, t_data *data)
{
	long	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(forks[i]);
		free(forks[i]);
		++i;
	}
	free(forks);
	free(data->dead_notice);
	free(philos);
	ft_stderr("Failed mutex init\n");
	return (-1);
}

int	return_fail5(t_philos *philos, pthread_mutex_t **forks, t_data *data)
{
	long	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(forks[i]);
		free(forks[i]);
		++i;
	}
	free(forks);
	free(data->print_mutex);
	free(data->dead_notice);
	free(philos);
	ft_stderr("Failed mutex init\n");
	return (-1);
}

int	return_fail4(t_philos *philos, pthread_mutex_t **forks, t_data *data)
{
	long	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(forks[i]);
		free(forks[i]);
		++i;
	}
	free(forks);
	free(data->dead_notice);
	free(data->dead_mutex);
	free(data->print_mutex);
	free(philos);
	ft_stderr("Failed mutex init\n");
	return (-1);
}
