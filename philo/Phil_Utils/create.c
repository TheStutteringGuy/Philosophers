/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 09:01:35 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/06/11 04:00:36 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	init_time(t_philos *philos)
{
	long	i;

	i = 0;
	while (i < philos[0].info->number_of_philosophers)
	{
		philos[i].last_eat = get_time();
		philos[i].start = get_time();
		++i;
	}
}

int	done_eating(t_philos *philos)
{
	long	i;

	i = 0;
	while (i < philos[0].info->number_of_philosophers)
	{
		pthread_mutex_lock(&philos[i].statue_mutex);
		if (philos[i].meals != philos[0].info->philosopher_must_eat)
		{
			pthread_mutex_unlock(&philos[i].statue_mutex);
			return (0);
		}
		pthread_mutex_unlock(&philos[i].statue_mutex);
		++i;
	}
	pthread_mutex_lock(philos[0].info->dead_mutex);
	*(philos[0].info->meal_notice) = 1;
	pthread_mutex_unlock(philos[0].info->dead_mutex);
	return (1);
}

void	*monitoring(void *arg)
{
	t_philos	*philos;
	long		i;

	philos = arg;
	while (TRUE)
	{
		i = 0;
		while (i < philos[0].info->number_of_philosophers)
		{
			pthread_mutex_lock(&philos[i].statue_mutex);
			if (get_time() - philos[i].last_eat > philos[0].info->time_to_die)
			{
				pthread_mutex_lock(philos[0].info->dead_mutex);
				*(philos[0].info->dead_notice) = 1;
				pthread_mutex_unlock(philos[0].info->dead_mutex);
				pthread_mutex_unlock(&philos[i].statue_mutex);
				return ((void *)&philos[i]);
			}
			pthread_mutex_unlock(&philos[i].statue_mutex);
			if (done_eating(philos) == 1)
				return (NULL);
			++i;
		}
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philos	*philo;

	philo = arg;
	if (case_one_seat(philo) == 1)
		return (NULL);
	if (philo->seat % 2 == 0)
		usleep(250);
	while (TRUE)
	{
		if (thread_check(philo) == 0)
			return (NULL);
		lock(philo);
		philo_printf("is eating", philo);
		pthread_mutex_lock(&philo->statue_mutex);
		philo->last_eat = get_time();
		philo->meals += 1;
		pthread_mutex_unlock(&philo->statue_mutex);
		philo_sleep(philo, philo->info->time_to_eat * 1000);
		unlock(philo);
		philo_printf("is sleeping", philo);
		philo_sleep(philo, philo->info->time_to_sleep * 1000);
		philo_printf("is thinking", philo);
		philo_think(philo);
	}
	return (NULL);
}

void	thread_create(t_philos *philos)
{
	pthread_t	monitor;
	long		i;
	void		*monitor_ret;

	init_time(philos);
	pthread_create(&monitor, NULL, &monitoring, (void *)philos);
	i = 0;
	while (i < philos[0].info->number_of_philosophers)
	{
		if (pthread_create(&philos[i].thread, NULL, &routine,
				(void *)&philos[i]) > 0)
			return ;
		++i;
	}
	i = 0;
	pthread_join(monitor, &monitor_ret);
	if (*(philos[0].info->dead_notice) == 1)
		philo_printf_dead("Is Dead", (t_philos *)monitor_ret);
	while (i < philos[0].info->number_of_philosophers)
	{
		if (pthread_join(philos[i].thread, NULL) > 0)
			return ;
		++i;
	}
}
