/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:57:12 by pjerddee          #+#    #+#             */
/*   Updated: 2023/02/19 15:19:51 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define DEAD 1
# define FULL 2

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct timeval		t_tv;
typedef struct timezone		t_tz;
typedef struct s_data		t_data;

typedef struct s_philo
{
	int				id;
	int				nate;
	int				afork;
	int				bfork;
	int				ate;
	int				isfull;
	long			tseat;
	long			tssleep;
	pthread_t		thrd;
	pthread_mutex_t	fork;
	struct s_data	*data;
	struct s_philo	*next;
}	t_philo;

typedef struct s_data
{
	int				nphi;
	int				tdie;
	int				teat;
	int				tsleep;
	int				neat;
	int				stop;
	int				ndead;
	t_tv			tstart;
	t_philo			**philo_lst;
	pthread_mutex_t	printq;
}	t_data;

//utils.c
int		ft_atoi(char *nptr);
int		if_allfull(t_philo *philo);
void	ft_clean(t_data *data);
void	ft_lstadd_back(t_philo **lst, t_philo *new);
t_philo	*ft_philonew(t_data *data, int name);

//activities.c
void	philo_take_fork(t_philo *philo);
void	philo_put_fork(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);

//time.c
long	get_tstamp(t_data *data);
void	sleep_ms(int tsleep_ms);

//routine.c
void	*philo_activities(void *philo);
void	takeforkb(t_philo *philo);
void	takeforka(t_philo *philo);
void	philo_stop(t_philo *philo);

#endif
