/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 23:05:58 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/06/11 04:06:32 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_think(t_philos *philo)
{
	long	time;

	time = 0;
	pthread_mutex_lock(philo->info->dead_mutex);
	if (*(philo->info->dead_notice) == 1 || *(philo->info->meal_notice) == 1)
	{
		pthread_mutex_unlock(philo->info->dead_mutex);
		return ;
	}
	pthread_mutex_unlock(philo->info->dead_mutex);
	pthread_mutex_lock(&philo->statue_mutex);
	if (philo->info->number_of_philosophers % 2 == 1)
	{
		if (philo->info->time_to_die > philo->info->time_to_eat
			+ philo->info->time_to_sleep)
			time = 2;
	}
	pthread_mutex_unlock(&philo->statue_mutex);
	usleep(time * 1000);
}

int	thread_check(t_philos *philo)
{
	pthread_mutex_lock(philo->info->dead_mutex);
	if (*(philo->info->meal_notice) == 1 || *(philo->info->dead_notice) == 1)
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
		while (TRUE)
		{
			pthread_mutex_lock(philo->info->dead_mutex);
			if (*(philo->info->dead_notice) == 1)
				break ;
			pthread_mutex_unlock(philo->info->dead_mutex);
		}
		pthread_mutex_unlock(philo->info->dead_mutex);
		pthread_mutex_unlock(philo->r_fork);
		return (0);
	}
	return (0);
}
