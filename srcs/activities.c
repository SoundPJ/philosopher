/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:09:57 by pjerddee          #+#    #+#             */
/*   Updated: 2023/02/18 02:09:58 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_take_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->fork));
	pthread_mutex_lock(&(philo->next->fork));
	pthread_mutex_lock(&(philo->data->printq));
	printf("%ld #%d has taken a fork.\n", get_tstamp(philo->data), philo->name);
	pthread_mutex_unlock(&(philo->data->printq));
	return (1);
}

void	philo_put_fork(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->fork));
	pthread_mutex_unlock(&(philo->next->fork));
	pthread_mutex_lock(&(philo->data->printq));
	printf("%ld #%d is putting a fork.\n", get_tstamp(philo->data), philo->name);
	pthread_mutex_unlock(&(philo->data->printq));
}

void	philo_eat(t_philo *philo)
{
	long	diff;

	philo->tseat = get_tstamp(philo->data);
	pthread_mutex_lock(&(philo->data->printq));
	printf("%ld #%d is eating.\n", get_tstamp(philo->data), philo->name);
	pthread_mutex_unlock(&(philo->data->printq));
	diff = get_tstamp(philo->data) - philo->tseat;
	while (diff < philo->data->teat)
	diff = get_tstamp(philo->data) - philo->tseat;
	philo_put_fork(philo);
	philo->nate++;
	if (philo->nate >= philo->data->neat)
		philo->data->stop = 1;
}

void	philo_sleep(t_philo *philo)
{
	long	diff;

	philo->tssleep = get_tstamp(philo->data);
	pthread_mutex_lock(&(philo->data->printq));
	printf("%ld #%d is sleeping.\n", get_tstamp(philo->data), philo->name);
	pthread_mutex_unlock(&(philo->data->printq));
	diff = get_tstamp(philo->data) - philo->tssleep;
	while (diff < philo->data->tsleep)
		diff = get_tstamp(philo->data) - philo->tssleep;
}

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->printq));
	printf("%ld #%d is thinking.\n", get_tstamp(philo->data), philo->name);
	pthread_mutex_unlock(&(philo->data->printq));
}
