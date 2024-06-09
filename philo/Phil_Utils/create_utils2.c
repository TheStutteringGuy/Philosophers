/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 23:05:58 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/06/08 00:51:05 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	thread_check(t_philos *philo)
{
	pthread_mutex_lock(philo->info->dead_mutex);
	if (philo->meals == philo->info->philosopher_must_eat
		|| *(philo->info->dead_notice) == 1)
	{
		pthread_mutex_unlock(philo->info->dead_mutex);
		return (0);
	}
	pthread_mutex_unlock(philo->info->dead_mutex);
	return (1);
}

int	case_one_seat(t_philos *philo)
{
	if (philo->info->number_of_philosophers == 1)
	{
		pthread_mutex_lock(philo->r_fork);
		philo_printf("has taken the right fork", philo);
		while (*(philo->info->dead_notice) == 0)
		{
		}
		pthread_mutex_unlock(philo->r_fork);
		return (0);
	}
	return (0);
}
