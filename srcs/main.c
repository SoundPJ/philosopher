/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:56:35 by pjerddee          #+#    #+#             */
/*   Updated: 2023/02/05 16:22:34 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
//number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
// void	*test_print()
void	test_print(t_data *data)
{
	printf("nphi: %d\n", data->nphi);
	printf("tdie: %d\n", data->tdie);
	printf("teat: %d\n", data->teat);
	printf("tsleep: %d\n", data->tsleep);
	printf("neat: %d\n", data->neat);
}

void	*philo_actions(void *philo)
{
	t_philo *tmp;
	tmp = (t_philo *)philo;

	// if (philo_take_fork(data))
	// 	philo_eat(data);
	// philo_sleep(data);
	// philo_think(data);
	int i = 10;
	while (i--)
	{
		printf("%d is eating\n", tmp->name);
		tmp->nate++;
	}
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

int	main(int ac, char **av)
{
	t_data		data;
	t_philo		*ptr;
	int			res;
	int			i;
	
	res = get_argv(ac, av, &data);
	if (res == -1)
		ft_err("Invalid input\n");
	else if (res == -2)
		ft_err("All input should be positive integer\n");
	else
	{
		i = 0;
		while (i < data.nphi)
		{
			t_philo	*new;
			new = ft_philonew(&data, i);
			ft_lstadd_back(data.philo_lst, new);
			i++;
		}
		ptr = *(data.philo_lst);
		while (ptr)
		{
			pthread_create(&(ptr->thrd), NULL, &philo_actions, ptr);
			ptr = ptr->next;
		}
		ptr = *(data.philo_lst);
		while (ptr != NULL)
		{
			pthread_join(ptr->thrd, NULL);
			ptr = ptr->next;
		}
	}
	return (0);
}
