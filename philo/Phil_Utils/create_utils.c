/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 09:33:59 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/06/07 23:27:37 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_printf(char *str, t_philos *philo)
{
	pthread_mutex_lock(philo->info->print_mutex);
	pthread_mutex_lock(philo->info->dead_mutex);
	if (*(philo->info->dead_notice) == 1
		|| philo->meals == philo->info->philosopher_must_eat)
	{
		pthread_mutex_unlock(philo->info->print_mutex);
		pthread_mutex_unlock(philo->info->dead_mutex);
		return ;
	}
	pthread_mutex_unlock(philo->info->dead_mutex);
	printf("%ld %d %s\n", (get_time() - philo->start), philo->seat, str);
	pthread_mutex_unlock(philo->info->print_mutex);
}

void	philo_sleep(t_philos *philo, long time)
{
	pthread_mutex_lock(philo->info->dead_mutex);
	if (*(philo->info->dead_notice) == 1
		|| philo->meals == philo->info->philosopher_must_eat)
	{
		pthread_mutex_unlock(philo->info->dead_mutex);
		return ;
	}
	pthread_mutex_unlock(philo->info->dead_mutex);
	usleep(time);
}

void	lock(t_philos *philo)
{
	pthread_mutex_lock(philo->l_fork);
	philo_printf("has taken a fork", philo);
	pthread_mutex_lock(philo->r_fork);
	philo_printf("has taken a fork", philo);
}

void	unlock(t_philos *philo)
{
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	philo_printf_dead(char *str, t_philos *philo)
{
	pthread_mutex_lock(philo->info->print_mutex);
	printf("%ld %d %s\n", (get_time() - philo->start), philo->seat, str);
	pthread_mutex_unlock(philo->info->print_mutex);
}
