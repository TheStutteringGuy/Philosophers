/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 06:17:11 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/06/28 07:43:01 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	clean_everything_process(t_data *data)
{
	free(data->dead_notice);
	free(data->meal_notice);
	free(data->meals);
	free(data->pids);
	sem_close(data->forks);
	sem_close(data->print_sem);
	sem_close(data->dead_sem);
	sem_close(data->meal_sem);
	sem_close(data->dead_process);
	sem_close(data->notify_process);
}

int	done_eating(t_data *data)
{
	sem_wait(data->meal_sem);
	if (*(data->meals) == data->philosopher_must_eat)
	{
		*(data->meal_notice) = 1;
		sem_post(data->meal_sem);
		return (0);
	}
	sem_post(data->meal_sem);
	return (1);
}
