/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stderr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aibn-ich <aibn-ich@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:12:25 by aibn-ich          #+#    #+#             */
/*   Updated: 2024/05/25 09:43:24 by aibn-ich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_stderr(char *str)
{
	char	*ptr;

	ptr = str;
	while (*ptr)
		write(2, ptr++, 1);
}

void	ft_stdout(char *str)
{
	char	*ptr;

	ptr = str;
	while (*ptr)
		write(2, ptr++, 1);
}
