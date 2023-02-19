/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 15:13:19 by pjerddee          #+#    #+#             */
/*   Updated: 2023/02/19 15:49:53 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_activities(void *philo)
{
	t_philo	*tmp;

	tmp = (t_philo *)philo;
	while (getts(tmp->data) < 0)
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
	philo_put_fork(philo);
	if (philo->data->stop == FULL)
	{
		pthread_mutex_lock(&(philo->data->printq));
		printf("Every philosopher is full.\n");
		pthread_mutex_unlock(&(philo->data->printq));
	}
	else if (!philo->data->ndead)
	{
		philo->data->stop = DEAD;
		pthread_mutex_lock(&(philo->data->printq));
		printf("%ld #%i die.\n", getts(philo->data), philo->id);
		pthread_mutex_unlock(&(philo->data->printq));
		philo->data->ndead++;
	}
}

void	takeforka(t_philo *philo)
{
	if (!philo->af && !philo->data->stop)
	{
		pthread_mutex_lock(&(philo->fork));
		philo->af = 1;
		pthread_mutex_lock(&(philo->data->printq));
		if (philo->data->stop == 0)
			printf("%ld #%i has taken a fork.\n", getts(philo->data), philo->id);
		pthread_mutex_unlock(&(philo->data->printq));
	}
}

void	takeforkb(t_philo *philo)
{
	if (philo->next && !philo->bf && !philo->data->stop && !philo->next->af)
	{
		pthread_mutex_lock(&(philo->next->fork));
		philo->bf = 1;
		pthread_mutex_lock(&(philo->data->printq));
		if (philo->data->stop == 0)
			printf("%ld #%i has taken a fork.\n", getts(philo->data), philo->id);
		pthread_mutex_unlock(&(philo->data->printq));
	}
}
