/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 12:37:58 by pjerddee          #+#    #+#             */
/*   Updated: 2023/02/19 01:13:04 by pjerddee         ###   ########.fr       */
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
	return (0);
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
	node->afork = 0;
	node->bfork = 0;
	node->ate = 0;
	node->isfull = 0;
	pthread_mutex_init(&(node->fork), NULL);
	return (node);
}

int	ifdead(t_philo *philo)
{
	if (get_tstamp(philo->data) - philo->tseat < (unsigned long)philo->data->tdie && philo->data->stop == 0)
	{
		return (0);
	}
	else
	{
		philo_put_fork(philo);
		if (philo->data->stop != FULL)
			philo->data->stop = DEAD;
		philo_stop(philo);
		return (1);
	}
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
