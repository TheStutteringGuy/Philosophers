/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 18:59:54 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/06/09 23:49:49 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	more_restrict(t_data *data)
{
	if (data->number_of_philosophers > 124507)
		ft_stderr("You exceeded The threads-max\n");
	if (data->number_of_philosophers <= 200 && data->time_to_die >= 60
		&& data->time_to_eat >= 60 && data->time_to_sleep >= 60)
		return (1);
	else
		ft_stderr("Please Follow The instructions\n");
	return (0);
}

void	init(int ac, char **av, t_data *data)
{
	data->number_of_philosophers = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (ac == 6)
		data->philosopher_must_eat = ft_atol(av[5]);
	else
		data->philosopher_must_eat = -1;
}

int	main(int ac, char **av)
{
	t_data	data;

	if ((ac == 5 || ac == 6) && pars_arg(ac, av) != 0)
	{
		if (zero_five(ac, av) == 0)
			return (0);
		if (check_time() == 0)
			return (1);
		init(ac, av, &data);
		if (more_restrict(&data) == 0)
			return (1);
		if (forking(&data) == 0)
			return (-1);
	}
	else
		ft_stderr("False Arguments\n");
	return (0);
}
