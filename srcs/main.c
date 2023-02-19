/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:56:35 by pjerddee          #+#    #+#             */
/*   Updated: 2023/02/19 15:17:30 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
//n_of_philosophers t_to_die t_to_eat t_to_sleep [ntimes_must_eat]

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
	data->philo_lst = NULL;
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
	return (0);
}

void	start_thread(t_data *data)
{
	int		i;
	t_philo	*ptr;

	ptr = *(data->philo_lst);
	i = data->nphi;
	gettimeofday(&(data->tstart), NULL);
	data->tstart.tv_sec += 1;
	while (i--)
	{
		ptr->tseat = 0;
		pthread_create(&(ptr->thrd), NULL, &philo_activities, ptr);
		ptr = ptr->next;
	}
}

void	philo_create(t_data *data)
{
	int		i;
	t_philo	*ptr;
	t_philo	*new;

	data->philo_lst = malloc(data->nphi * sizeof(t_philo));
	i = 0;
	while (i < data->nphi)
	{
		new = ft_philonew(data, i);
		ft_lstadd_back(data->philo_lst, new);
		i++;
	}
	ptr = *(data->philo_lst);
	while (ptr->next != NULL)
		ptr = ptr->next;
	if (ptr != *(data->philo_lst))
		ptr->next = *(data->philo_lst);
	start_thread(data);
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
		printf("Invalid input\n");
	else if (res == -2)
		printf("All input should be positive integer\n");
	else
	{
		philo_create(&data);
		philo_join(&data);
	}
	ft_clean(&data);
	return (0);
}
