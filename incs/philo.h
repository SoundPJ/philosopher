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

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct	timeval		t_tv;
typedef struct	timezone	t_tz;
typedef struct	s_data		t_data;

typedef struct s_philo
{
	int				name;
	int				nate;
	pthread_t		thrd;
	pthread_mutex_t	fork;
	struct s_data	*data;
	struct s_philo	*next;
}	t_philo;

typedef struct s_data
{
	int	nphi;
	int tdie;
	int teat;
	int tsleep;
	int neat;
	t_philo	**philo_lst;
}	t_data;

//utils.c
int		ft_atoi(char *nptr);
int		ft_err(char *str);
void	ft_lstadd_back(t_philo **lst, t_philo *new);
t_philo	*ft_philonew(t_data *data, int name);

#endif
