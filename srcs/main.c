/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:56:35 by pjerddee          #+#    #+#             */
/*   Updated: 2023/02/04 18:52:39 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
//number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

void	*print_stupid()
{
	printf("This is to be printed\n");
	return (NULL);
}

void	test_print(t_philo *data)
{
	printf("nphi: %d\n", data->nphi);
	printf("tdie: %d\n", data->tdie);
	printf("teat: %d\n", data->teat);
	printf("tsleep: %d\n", data->tsleep);
	printf("nteat: %d\n", data->nteat);
}

int	get_argv(int ac, char **av, t_philo *data)
{
	if (ac < 5 || ac > 6)
		return (-1);	
	data->nphi = ft_atoi(av[1]);
	data->tdie = ft_atoi(av[2]);
	data->teat = ft_atoi(av[3]);
	data->tsleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		data->nteat = ft_atoi(av[5]);
		if (data->nteat < 0)
			return (-2);
	}
	else
		data->nteat = -1;
	if (data->nphi < 0 || data->tdie < 0 || data->teat < 0 || data->tsleep < 0)
		return (-2);
	return (0);
}

int	main(int ac, char **av)
{
	pthread_t	*th;
	t_philo		data;
	int			res;
	int			i;
	
	res = get_argv(ac, av, &data);
	if (res == -1)
		ft_err("Arg format: number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
	else if (res == -2)
		ft_err("All input should be positive integer\n");
	else
	{
		th = malloc(data.nphi * sizeof(pthread_t));
		test_print(&data);
		i = 0;
		while (i < data.nphi)
		{
			pthread_create(th + i, NULL, &print_stupid, NULL);
			i++;
		}
		i = 0;
		while (i < data.nphi)
		{
			pthread_join(th[i], NULL);
			i++;
		}
	}
	return (0);
}
