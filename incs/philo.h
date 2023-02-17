/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:57:12 by pjerddee          #+#    #+#             */
/*   Updated: 2023/02/05 16:18:06 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
#endif

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct	timeval		t_tv;
typedef struct	timezone	t_tz;
typedef struct	s_data		t_data;

typedef struct s_philo
{
	int				name;
	int				nate;
	long			tseat;
	long			tssleep;
	pthread_t		thrd;
	pthread_mutex_t	fork;
	struct s_data	*data;
	struct s_philo	*next;
	struct s_philo	*prev;	
}	t_philo;

typedef struct s_data
{
	int		nphi;
	int 	tdie;
	int 	teat;
	int 	tsleep;
	int 	neat;
	int		stop;
	t_tv	tstart;
	pthread_mutex_t	printq;
	t_philo	**philo_lst;
}	t_data;

//utils.c
int		ft_atoi(char *nptr);
int		ft_err(char *str);
void	ft_lstadd_back(t_philo **lst, t_philo *new);
long	get_timestamp(t_data *data);
void	sleep_ms(int tsleep_ms);
t_philo	*ft_philonew(t_data *data, int name);

//activities.c
int		philo_take_fork(t_philo *philo);
void	philo_put_fork(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
