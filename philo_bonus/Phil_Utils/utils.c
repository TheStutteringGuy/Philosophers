/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 06:10:24 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/06/28 11:37:38 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check(t_data *data)
{
	sem_wait(data->meal_sem);
	if (*(data->meal_notice) == 1)
	{
		sem_post(data->meal_sem);
		return (-1);
	}
	sem_post(data->meal_sem);
	return (1);
}

void	wait_forks(t_data *data)
{
	sem_wait(data->forks);
	philo_print("has taken a fork", data);
	sem_wait(data->forks);
	philo_print("has taken a fork", data);
}

void	post_forks(t_data *data)
{
	sem_post(data->forks);
	sem_post(data->forks);
}

void	philo_print(char *str, t_data *data)
{
	if (check(data) == -1)
		return ;
	sem_wait(data->print_sem);
	printf("%ld %ld %s\n", (get_time() - data->start), data->seat, str);
	sem_post(data->print_sem);
}

int	case_one(t_data *data)
{
	if (data->number_of_philosophers != 1)
		return (1);
	else
	{
		sem_wait(data->forks);
		philo_print("has taken a fork", data);
		while (TRUE)
		{
			sem_wait(data->dead_sem);
			if (*(data->dead_notice) == 1)
				break ;
			sem_post(data->dead_sem);
		}
		sem_post(data->dead_sem);
		sem_post(data->forks);
		return (0);
	}
	return (1);
}
