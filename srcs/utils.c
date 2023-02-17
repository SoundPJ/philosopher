/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 12:37:58 by pjerddee          #+#    #+#             */
/*   Updated: 2023/02/18 02:20:56 by pjerddee         ###   ########.fr       */
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

int	ft_err(char *str, t_data *data)
{
	(void)	data;
	printf("%s", str);
	//free philolst
	exit(0);
}

void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo	*ptr;

	if (*lst == NULL)
		*lst = new;
	else
	{
		ptr = *lst;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
		ptr->next->prev = ptr;
	}
}

t_philo	*ft_philonew(t_data *data, int name)
{
	t_philo	*node;

	node = (t_philo *)malloc(sizeof(t_philo));
	if (!node)
		return (NULL);
	node->name = name;
	node->nate = 0;
	node->data = data;
	node->next = NULL;
	pthread_mutex_init(&(node->fork), NULL);
	return (node);
}
