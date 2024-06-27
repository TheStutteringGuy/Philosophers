/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 07:07:16 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/06/27 05:00:17 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_dead(char *str, t_data *data)
{
	sem_wait(data->dead_process);
	sem_post(data->dead_process);
	sem_wait(data->print_sem);
	printf("%ld %ld %s\n", (get_time() - data->start), data->seat, str);
	sem_post(data->print_sem);
}

void	philo_think(t_data *data)
{
	long	time;

	time = 0;
	sem_wait(data->dead_process);
	sem_post(data->dead_process);
	if (data->number_of_philosophers % 2 == 1)
	{
		if (data->time_to_die > data->time_to_eat + data->time_to_sleep)
			time = 2;
	}
	my_usleep(time);
}

void	philo_sleep(t_data *data, long time)
{
	sem_wait(data->dead_process);
	sem_post(data->dead_process);
	if (check(data) == 0 || check(data) == -1)
		return ;
	my_usleep(time);
}

void	fix_time(t_data *data)
{
	sem_wait(data->dead_process);
	sem_post(data->dead_process);
	if (check(data) == 0 || check(data) == -1)
		return ;
	sem_wait(data->dead_sem);
	data->last_eat = get_time();
	sem_post(data->dead_sem);
}

void	add_meals(t_data *data)
{
	sem_wait(data->dead_process);
	sem_post(data->dead_process);
	if (check(data) == 0 || check(data) == -1)
		return ;
	sem_wait(data->meal_sem);
	*(data->meals) += 1;
	sem_post(data->meal_sem);
}
