/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 12:37:58 by pjerddee          #+#    #+#             */
/*   Updated: 2023/02/19 15:19:45 by pjerddee         ###   ########.fr       */
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
	}
}

t_philo	*ft_philonew(t_data *data, int id)
{
	t_philo	*node;

	node = (t_philo *)malloc(sizeof(t_philo));
	if (!node)
		return (NULL);
	node->id = id;
	node->nate = 0;
	node->data = data;
	node->next = NULL;
	node->afork = 0;
	node->bfork = 0;
	node->ate = 0;
	node->isfull = 0;
	pthread_mutex_init(&(node->fork), NULL);
	return (node);
}

int	if_allfull(t_philo *philo)
{
	int		i;
	t_philo	*ptr;

	i = philo->data->nphi;
	ptr = philo;
	while (i--)
	{
		if (ptr->isfull == 0)
			return (0);
		ptr = ptr->next;
	}
	return (1);
}

void	ft_clean(t_data *data)
{
	int		i;
	t_philo	*ptr1;
	t_philo	*ptr2;

	if (data->philo_lst == NULL)
		return ;
	ptr1 = *(data->philo_lst);
	i = data->nphi;
	while (i--)
	{
		ptr2 = ptr1->next;
		free(ptr1);
		ptr1 = ptr2;
	}
	free(data->philo_lst);
}
