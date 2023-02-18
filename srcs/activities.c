/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:09:57 by pjerddee          #+#    #+#             */
/*   Updated: 2023/02/19 02:39:00 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_take_fork(t_philo *philo)
{
	// printf("to take fork\n");
	pthread_mutex_lock(&(philo->data->rwq));
	// printf("take fork lock\n");
	if (get_tstamp(philo->data) - philo->tseat < (unsigned long)philo->data->tdie && philo->data->stop == 0)
	{
		if (!philo->afork)
		{
			pthread_mutex_lock(&(philo->fork));
			philo->afork = 1;
			pthread_mutex_lock(&(philo->data->printq));
			printf("%ld #%d has taken a fork.\n", get_tstamp(philo->data), philo->name);
			pthread_mutex_unlock(&(philo->data->printq));
		}
		if (philo->next && !philo->bfork)
		{
			// printf("hello\n");
			pthread_mutex_lock(&(philo->next->fork));
			philo->bfork = 1;
			pthread_mutex_lock(&(philo->data->printq));
			printf("%ld #%d has taken a fork.\n", get_tstamp(philo->data), philo->name);
			pthread_mutex_unlock(&(philo->data->printq));
		}	
		// if (philo->next && !philo->bfork && !philo->next->afork)
	}
	else
	{
		philo_put_fork(philo);
		if (philo->data->stop != FULL)
			philo->data->stop = DEAD;
		philo_stop(philo);
	}
	// printf("#%d, before unlock\n", philo->name);
	pthread_mutex_unlock(&(philo->data->rwq));
	// printf("take fork #%d, after unlock\n", philo->name);
}

void	philo_put_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->rwq));
	// printf("to put fork\n");
	if (philo->afork == 1)
	{
		// printf("fork a released\n");
		pthread_mutex_unlock(&(philo->fork));
		philo->afork = 0;
	}
	if (philo->bfork == 1)
	{
		pthread_mutex_unlock(&(philo->next->fork));
		philo->bfork = 0;
	}
	// if (!philo->data->ndead)
	// {
	// 	pthread_mutex_lock(&(philo->data->printq));
	// 	printf("%ld #%d is putting a fork.\n", get_tstamp(philo->data), philo->name);
	// 	pthread_mutex_unlock(&(philo->data->printq));
	// }
	// printf("#%d, before unlock\n", philo->name);
	pthread_mutex_unlock(&(philo->data->rwq));
	// printf("put fork #%d, after unlock\n", philo->name);
}

void	philo_eat(t_philo *philo)
{
	long	diff;

	// printf("to eat\n");
	pthread_mutex_lock(&(philo->data->rwq));
	if (philo->afork == 1 && philo->bfork == 1)
	{
		if (get_tstamp(philo->data) - philo->tseat < (unsigned long)philo->data->tdie && philo->data->stop == 0)	
		{
			philo->tseat = get_tstamp(philo->data);
			pthread_mutex_lock(&(philo->data->printq));
			printf("%ld #%d is eating.\n", get_tstamp(philo->data), philo->name);
			pthread_mutex_unlock(&(philo->data->printq));
			diff = get_tstamp(philo->data) - philo->tseat;
			while (diff < philo->data->teat)
				diff = get_tstamp(philo->data) - philo->tseat;
			philo_put_fork(philo);
			philo->ate = 1;
			philo->nate++;
			if (philo->nate >= philo->data->neat && philo->data->neat > 0)
				philo->isfull = 1;
			if (if_allfull(philo) == 1)
				philo->data->stop = FULL;
		}
		else
		{
			philo_put_fork(philo);
			if (philo->data->stop != FULL)
				philo->data->stop = DEAD;
			philo_stop(philo);
		}
	}
	// printf("#%d, before unlock\n", philo->name);
	pthread_mutex_unlock(&(philo->data->rwq));
	// printf("eat #%d, after unlock\n", philo->name);
}

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->rwq));
	if (get_tstamp(philo->data) - philo->tseat < (unsigned long)philo->data->tdie + 1 && philo->data->stop == 0)	
	{
		pthread_mutex_lock(&(philo->data->printq));
		printf("%ld #%d is thinking.\n", get_tstamp(philo->data), philo->name);
		pthread_mutex_unlock(&(philo->data->printq));
	}
	else
	{
		philo_put_fork(philo);
		if (philo->data->stop != FULL)
			philo->data->stop = DEAD;
		philo_stop(philo);
	}
	// printf("#%d, before unlock\n", philo->name);
	pthread_mutex_unlock(&(philo->data->rwq));
	// printf("think #%d, after unlock\n", philo->name);
}

void	philo_sleep(t_philo *philo)
{
	long	diff;

	pthread_mutex_lock(&(philo->data->rwq));
	if (philo->ate == 1)
	{
		// printf("sleeping\n");
		if (get_tstamp(philo->data) - philo->tseat < (unsigned long)philo->data->tdie + 1 && philo->data->stop == 0)	
		{
			philo->tssleep = get_tstamp(philo->data);
			pthread_mutex_lock(&(philo->data->printq));
			printf("%ld #%d is sleeping.\n", get_tstamp(philo->data), philo->name);
			pthread_mutex_unlock(&(philo->data->printq));
			diff = get_tstamp(philo->data) - philo->tssleep;
			while (diff < philo->data->tsleep)
				diff = get_tstamp(philo->data) - philo->tssleep;
			philo_think(philo);
		}
		else
		{
			philo_put_fork(philo);
			if (philo->data->stop != FULL)
				philo->data->stop = DEAD;
			philo_stop(philo);
		}
		philo->ate = 0;
	}
	// printf("#%d, before unlock\n", philo->name);
	pthread_mutex_unlock(&(philo->data->rwq));
	// printf("sleep #%d, after unlock\n", philo->name);
}

void	philo_stop(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->rwq));
	if (philo->data->stop == DEAD && !philo->data->ndead)
	{
		pthread_mutex_lock(&(philo->data->printq));
		printf("%ld #%d die.\n", get_tstamp(philo->data), philo->name);
		pthread_mutex_unlock(&(philo->data->printq));
		philo->data->ndead++;
	}
	else if (philo->data->stop == FULL)
	{
		pthread_mutex_lock(&(philo->data->printq));
		printf("Every philosopher is full.\n");
		pthread_mutex_unlock(&(philo->data->printq));
		// printf("unlock printq\n");
	}
	// printf("#%d, before unlock\n", philo->name);
	pthread_mutex_unlock(&(philo->data->rwq));
	// printf("stop #%d, after unlock\n", philo->name);
}
