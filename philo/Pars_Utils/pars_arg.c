/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 06:29:54 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/06/03 13:46:27 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_five(int ac, char **av)
{
	if (ac == 6)
	{
		if (ft_atol(av[5]) == -1)
			return (0);
	}
	return (1);
}

int	zero_five(int ac, char **av)
{
	if (ac == 6)
	{
		if (ft_atol(av[5]) == 0)
			return (0);
	}
	return (1);
}

int	check_num(char **av)
{
	int	i;

	i = 1;
	while (i < 5)
	{
		if (ft_atol(av[i]) == 0 || ft_atol(av[i]) == -1)
			return (0);
		++i;
	}
	return (1);
}

int	check_if_num(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		if (av[i][j] == '+' || (av[i][j] >= '0' && av[i][j] <= '9'))
			++j;
		else
			return (0);
		while (av[i][j] != '\0')
		{
			if (av[i][j] >= '0' && av[i][j] <= '9')
				++j;
			else
				return (0);
		}
		++i;
	}
	return (1);
}

int	pars_arg(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		if (check_if_num(ac, av) == 0)
			return (0);
		if (check_num(av) == 0)
			return (0);
		if (check_five(ac, av) == 0)
			return (0);
	}
	return (1);
}
