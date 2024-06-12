/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 23:50:16 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/06/11 07:18:45 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	routine(sem_t *sem, t_data *data)
{
	// printf("HELLO\n");
	exit(1);
}

int	fork_num_philo(sem_t *sem, t_data *data, long number_philo)
{
	long	i;
	pid_t	id;

	if (number_philo == 0)
		return (1);
	id = fork();
	if (id == -1)
	{
		printf("Fork failed\n");
		return (0);
	}
	else if (id == 0)
		routine(sem, data);
	else
		fork_num_philo(sem, data, number_philo - 1);
}

int	forking(t_data *data)
{
	sem_t	*sem;

	sem = sem_open("/forks", O_CREAT | O_EXCL | O_RDWR,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP,
			data->number_of_philosophers);
	if (sem == SEM_FAILED)
	{
		printf("Sem_open Failed\n");
		return (0);
	}
	if (fork_num_philo(sem, data, data->number_of_philosophers) == 0)
		return (0);
	// printf("HELLO\n");
	sem_unlink("/forks");
	sem_close(sem);
}
