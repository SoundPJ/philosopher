/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:09:57 by pjerddee          #+#    #+#             */
/*   Updated: 2023/02/19 15:49:28 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_take_fork(t_philo *philo)
{
	if (istimesout(philo) && philo->data->stop == 0)
	{
		takeforka(philo);
		takeforkb(philo);
	}
	else
		philo_stop(philo);
}

void	philo_put_fork(t_philo *philo)
{
	if (philo->af == 1)
	{
		pthread_mutex_unlock(&(philo->fork));
		philo->af = 0;
	}
	if (philo->bf == 1)
	{
		pthread_mutex_unlock(&(philo->next->fork));
		philo->bf = 0;
	}
}

void	philo_eat(t_philo *philo)
{
	long	diff;

	if (philo->af == 1 && philo->bf == 1)
	{
		if (istimesout(philo) && philo->data->stop == 0)
		{
			philo->tseat = getts(philo->data);
			pthread_mutex_lock(&(philo->data->printq));
			if (philo->data->stop == 0)
				printf("%ld #%d is eating.\n", getts(philo->data), philo->id);
			pthread_mutex_unlock(&(philo->data->printq));
			diff = getts(philo->data) - philo->tseat;
			while (diff < philo->data->teat)
				diff = getts(philo->data) - philo->tseat;
			philo_put_fork(philo);
			philo->ate = 1;
			philo->nate++;
			if (philo->nate >= philo->data->neat && philo->data->neat > 0)
				philo->isfull = 1;
			if (if_allfull(philo) == 1)
				philo->data->stop = FULL;
		}
		else
			philo_stop(philo);
	}
}

void	philo_think(t_philo *philo)
{
	if (philo->data->stop == 0)
	{
		pthread_mutex_lock(&(philo->data->printq));
		if (philo->data->stop == 0)
			printf("%ld #%d is thinking.\n", getts(philo->data), philo->id);
		pthread_mutex_unlock(&(philo->data->printq));
	}
	else
		philo_stop(philo);
}

void	philo_sleep(t_philo *philo)
{
	long	diff;

	if (philo->ate == 1)
	{
		if (istimesout(philo) && philo->data->stop == 0)
		{
			philo->tssleep = getts(philo->data);
			pthread_mutex_lock(&(philo->data->printq));
			if (philo->data->stop == 0)
				printf("%ld #%d is sleeping.\n", getts(philo->data), philo->id);
			pthread_mutex_unlock(&(philo->data->printq));
			diff = getts(philo->data) - philo->tssleep;
			while (diff < philo->data->tsleep)
				diff = getts(philo->data) - philo->tssleep;
			philo_think(philo);
		}
		else
			philo_stop(philo);
		philo->ate = 0;
	}
}
