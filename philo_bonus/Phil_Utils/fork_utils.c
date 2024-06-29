/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 04:25:44 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/06/28 07:39:11 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	initialize_sem4(t_data *data)
{
	data->notify_process = sem_open("/Notify_sem", O_CREAT | O_EXCL | O_RDWR,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP, 0);
	if (data->dead_process == SEM_FAILED)
	{
		sem_unlink("/Forks");
		sem_unlink("/Print_sem");
		sem_unlink("/Dead_sem");
		sem_unlink("/Meal_sem");
		sem_unlink("/Process_sem");
		free(data->pids);
		printf("Sem_open (Notify) Failed\n");
		return (0);
	}
	return (1);
}

int	initialize_sem3(t_data *data)
{
	data->dead_process = sem_open("/Process_sem", O_CREAT | O_EXCL | O_RDWR,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP, 1);
	if (data->dead_process == SEM_FAILED)
	{
		sem_unlink("/Forks");
		sem_unlink("/Print_sem");
		sem_unlink("/Dead_sem");
		sem_unlink("/Meal_sem");
		printf("Sem_open (Process) Failed\n");
		return (0);
	}
	data->pids = malloc(sizeof(pid_t) * data->number_of_philosophers);
	if (!data->pids)
	{
		sem_unlink("/Forks");
		sem_unlink("/Print_sem");
		sem_unlink("/Dead_sem");
		sem_unlink("/Meal_sem");
		sem_unlink("/Process_sem");
		printf("Pids array Failed\n");
		return (0);
	}
	return (1);
}

int	initialize_sem2(t_data *data)
{
	data->dead_sem = sem_open("/Dead_sem", O_CREAT | O_EXCL | O_RDWR,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP, 1);
	if (data->dead_sem == SEM_FAILED)
	{
		sem_unlink("/Forks");
		sem_unlink("/Print_sem");
		printf("Sem_open (Dead) Failed\n");
		return (0);
	}
	data->meal_sem = sem_open("/Meal_sem", O_CREAT | O_EXCL | O_RDWR,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP, 1);
	if (data->meal_sem == SEM_FAILED)
	{
		sem_unlink("/Forks");
		sem_unlink("/Print_sem");
		sem_unlink("/Dead_sem");
		printf("Sem_open (Meal) Failed\n");
		return (0);
	}
	return (1);
}

int	initialize_sem(t_data *data)
{
	data->forks = sem_open("/Forks", O_CREAT | O_EXCL | O_RDWR,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP,
			data->number_of_philosophers);
	if (data->forks == SEM_FAILED)
	{
		printf("Sem_open (FORKS) Failed\n");
		return (0);
	}
	data->print_sem = sem_open("/Print_sem", O_CREAT | O_EXCL | O_RDWR,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP, 1);
	if (data->print_sem == SEM_FAILED)
	{
		sem_unlink("/Forks");
		printf("Sem_open (PRINT) Failed\n");
		return (0);
	}
	if (initialize_sem2(data) == 0)
		return (0);
	if (initialize_sem3(data) == 0)
		return (0);
	if (initialize_sem4(data) == 0)
		return (0);
	return (1);
}

void	clean_everything(t_data *data)
{
	sem_unlink("/Forks");
	sem_unlink("/Print_sem");
	sem_unlink("/Dead_sem");
	sem_unlink("/Meal_sem");
	sem_unlink("/Process_sem");
	sem_unlink("/Notify_sem");
	sem_close(data->forks);
	sem_close(data->print_sem);
	sem_close(data->dead_sem);
	sem_close(data->meal_sem);
	sem_close(data->dead_process);
	sem_close(data->notify_process);
}
