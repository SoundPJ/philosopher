/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 15:13:19 by pjerddee          #+#    #+#             */
/*   Updated: 2023/02/19 15:21:52 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_activities(void *philo)
{
	t_philo	*tmp;

	tmp = (t_philo *)philo;
	while (get_tstamp(tmp->data) < 0)
		;
	if (tmp->id % 2 == 0)
		usleep(1000);
	while (tmp->data->stop == 0)
	{
		if (tmp->data->stop == 0)
			philo_take_fork(tmp);
		if (tmp->data->stop == 0)
			philo_eat(tmp);
		if (tmp->data->stop == 0)
			philo_sleep(tmp);
	}
	philo_put_fork(tmp);
	return (NULL);
}

void	philo_stop(t_philo *philo)
{
	if (philo->data->stop == DEAD && !philo->data->ndead)
	{
		pthread_mutex_lock(&(philo->data->printq));
		printf("%ld #%i die.\n", get_tstamp(philo->data), philo->id);
		pthread_mutex_unlock(&(philo->data->printq));
		philo->data->ndead++;
	}
	else if (philo->data->stop == FULL)
	{
		pthread_mutex_lock(&(philo->data->printq));
		printf("Every philosopher is full.\n");
		pthread_mutex_unlock(&(philo->data->printq));
	}
}

void	takeforka(t_philo *philo)
{
	if (!philo->afork && !philo->data->stop)
	{
		pthread_mutex_lock(&(philo->fork));
		philo->afork = 1;
		pthread_mutex_lock(&(philo->data->printq));
		if (philo->data->stop == 0)
			printf("%ld #%i has taken a fork.\n", get_tstamp(philo->data), philo->id);
		pthread_mutex_unlock(&(philo->data->printq));
	}
}

void	takeforkb(t_philo *philo)
{
	if (philo->next && !philo->bfork && !philo->data->stop && !philo->next->afork)
	{
		pthread_mutex_lock(&(philo->next->fork));
		philo->bfork = 1;
		pthread_mutex_lock(&(philo->data->printq));
		if (philo->data->stop == 0)
			printf("%ld #%i has taken a fork.\n", get_tstamp(philo->data), philo->id);
		pthread_mutex_unlock(&(philo->data->printq));
	}
}
