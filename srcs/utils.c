/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 12:37:58 by pjerddee          #+#    #+#             */
/*   Updated: 2023/02/04 18:47:29 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *nptr)
{
	int	val;
	int	i;

	val = 0;
	i = 0;
	if (nptr[i] < '0' || nptr[i] > '9')
		return (-1);
	while (nptr[i] >= '0' && nptr[i] <= '9')
		val = (val * 10) + (nptr[i++] - '0');
	return (val);
}

int	ft_err(char *str)
{
	printf("%s", str);
	exit(0);
}
