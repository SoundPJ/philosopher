/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 12:37:58 by pjerddee          #+#    #+#             */
/*   Updated: 2023/02/05 16:16:54 by pjerddee         ###   ########.fr       */
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

void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo *ptr;

	if (*lst == NULL)
	{
		*lst = new;
	}
	else
	{
		ptr = *lst;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
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
	return (node);
}

long	get_timestamp(t_data *data)
{
	t_tv	ta;
	t_tv	tb;
	long	tstamp;

	ta = data->tstart;
	gettimeofday(&tb, NULL);
	tstamp = ((tb.tv_sec - ta.tv_sec) * 1000) + ((tb.tv_usec - ta.tv_usec) / 1000);
	return (tstamp);
}

void sleep_ms(int tsleep_ms)
{
	t_tv			ta;
	t_tv			tb;
	long	tdiff;

	gettimeofday(&ta, NULL);
	tdiff = 0;
	while (tdiff < tsleep_ms)
	{
		gettimeofday(&tb, NULL);
		tdiff = ((tb.tv_sec - ta.tv_sec) * 1000) + ((tb.tv_usec - ta.tv_usec) / 1000);
	}
}