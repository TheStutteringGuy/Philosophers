/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 06:41:25 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/06/27 02:00:36 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	initalize_notice(t_data *data)
{
	data->meals = malloc(sizeof(long));
	if (!data->meals)
	{
		printf("meals allocation failed \n");
		return (0);
	}
	data->dead_notice = malloc(sizeof(long));
	if (!data->dead_notice)
	{
		printf("dead_notice allocation\n");
		return (0);
	}
	*data->dead_notice = 0;
	data->meal_notice = malloc(sizeof(long));
	if (!data->meal_notice)
	{
		free(data->dead_notice);
		printf("dead_notice allocation\n");
		return (0);
	}
	*data->meal_notice = 0;
	return (1);
}
