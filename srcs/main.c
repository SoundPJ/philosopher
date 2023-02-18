/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:56:35 by pjerddee          #+#    #+#             */
/*   Updated: 2023/02/19 01:03:55 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
//n_of_philosophers t_to_die t_to_eat t_to_sleep [ntimes_must_eat]

void	*philo_activities(void *philo)
{
	t_philo	*tmp;

	tmp = (t_philo *)philo;
	if (tmp->name % 2 == 0)
		usleep(100);
	while (tmp->data->stop == 0)
	{
		// printf("#%d, new loop\t status: %d\n", tmp->name, tmp->data->stop);
		if (tmp->data->stop == 0)
			philo_take_fork(tmp);
		else
			return (NULL);
		if (tmp->data->stop == 0)
			philo_eat(tmp);
		else
			return (NULL);
		if (tmp->data->stop == 0)	
			philo_sleep(tmp);
		else
			return (NULL);
		// printf("#%d, new loop\t status: %d\n", tmp->name, tmp->data->stop);
	}
	// printf("Hello There\n");
	return (NULL);
}

int	get_argv(int ac, char **av, t_data *data)
{
	if (ac < 5 || ac > 6)
		return (-1);
	data->nphi = ft_atoi(av[1]);
	data->tdie = ft_atoi(av[2]);
	data->teat = ft_atoi(av[3]);
	data->tsleep = ft_atoi(av[4]);
	data->stop = 0;
	data->ndead = 0;
	data->nfull = 0;
	pthread_mutex_init(&(data->printq), NULL);
	if (ac == 6)
	{
		data->neat = ft_atoi(av[5]);
		if (data->neat < 0)
			return (-2);
	}
	else
		data->neat = -1;
	if (data->nphi < 0 || data->tdie < 0 || data->teat < 0 || data->tsleep < 0)
		return (-2);
	data->philo_lst = malloc(data->nphi * sizeof(t_philo));
	return (0);
}

void	start_thread(t_data *data)
{
	int		i;
	t_philo	*ptr;

	ptr = *(data->philo_lst);
	i = data->nphi;
	gettimeofday(&(data->tstart), NULL);
	while (i--)
	{
		ptr->tseat = get_tstamp(data);
		pthread_create(&(ptr->thrd), NULL, &philo_activities, ptr);
		ptr = ptr->next;
	}
}

void	philo_create(t_data *data)
{
	int		i;
	t_philo	*ptr;
	t_philo	*new;

	i = 0;
	while (i < data->nphi)
	{
		new = ft_philonew(data, i);
		ft_lstadd_back(data->philo_lst, new);
		i++;
	}
	start_thread(data);
	ptr = *(data->philo_lst);
	while (ptr->next != NULL)
		ptr = ptr->next;
	if (ptr != *(data->philo_lst))
		ptr->next = *(data->philo_lst);
}

void	philo_join(t_data *data)
{
	int		i;
	t_philo	*ptr;

	i = data->nphi;
	ptr = *(data->philo_lst);
	while (i--)
	{
		pthread_join(ptr->thrd, NULL);
		ptr = ptr->next;
	}
}

int	main(int ac, char **av)
{
	t_data		data;
	int			res;

	res = get_argv(ac, av, &data);
	if (res == -1)
		ft_err("Invalid input\n", &data);
	else if (res == -2)
		ft_err("All input should be positive integer\n", &data);
	else
	{
		philo_create(&data);
		philo_join(&data);
	}
	return (0);
}
