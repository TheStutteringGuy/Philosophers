/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 23:50:16 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/06/27 06:20:35 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*monitoring(void *arg)
{
	t_data	*data;
	long	i;

	data = arg;
	i = 0;
	while (TRUE)
	{
		sem_wait(data->dead_sem);
		if (get_time() - data->last_eat >= data->time_to_die)
		{
			philo_dead("is dead", data);
			*(data->dead_notice) = 1;
			sem_post(data->dead_sem);
			return (NULL);
		}
		sem_post(data->dead_sem);
		if (done_eating(data) == 0)
			return (NULL);
	}
	return (NULL);
}

int	actual_routine(t_data *data)
{
	if (data->seat % 2 == 0)
		my_usleep(1);
	while (TRUE)
	{
		if (check(data) == 0 || check(data) == -1)
			break ;
		wait_forks(data);
		philo_print("is eating", data);
		fix_time(data);
		add_meals(data);
		philo_sleep(data, data->time_to_eat);
		post_forks(data);
		philo_print("is sleeping", data);
		philo_sleep(data, data->time_to_sleep);
		philo_think(data);
	}
	if (check(data) == 0)
		return (1);
	else if (check(data) == -1)
		return (-1);
	else
		return (0);
}

void	routine(t_data *data)
{
	pthread_t	monitor;

	pthread_create(&monitor, NULL, monitoring, (void *)data);
	if (case_one(data) == 0)
	{
		pthread_join(monitor, NULL);
		clean_everything_process(data);
		exit(0);
	}
	if (actual_routine(data) == 1)
	{
		pthread_join(monitor, NULL);
		clean_everything_process(data);
		exit(1);
	}
	else
	{
		pthread_join(monitor, NULL);
		clean_everything_process(data);
		exit(-1);
	}
}

int	fork_num_philo(t_data *data, long number_philo)
{
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
	{
		if (initalize_notice(data) == 0)
			exit(10);
		data->seat = data->number_of_philosophers - number_philo + 1;
		data->start = get_time();
		data->last_eat = get_time();
		routine(data);
	}
	else
	{
		data->pids[data->number_of_philosophers - number_philo] = id;
		fork_num_philo(data, number_philo - 1);
	}
	return (1);
}

int	forking(t_data *data)
{
	int	status;

	if (initialize_sem(data) == 0)
		return (0);
	data->pids = malloc(sizeof(pid_t) * data->number_of_philosophers);
	if (!data->pids)
		return (clean_everything(data), 0);
	if (fork_num_philo(data, data->number_of_philosophers) == 0)
		return (free(data->pids), clean_everything(data), 0);
	clean_everything(data);
	while (TRUE)
	{
		if (waitpid(-1, &status, 0) == -1)
		{
			if (errno == ECHILD)
				break ;
		}
	}
	printf("HELLOOOOOOOOOOOOOOOOOOOOO\n");
	return (free(data->pids), 1);
}
