/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 18:56:35 by pjerddee          #+#    #+#             */
/*   Updated: 2022/12/19 20:17:52 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
int	main(int ac, char **av)
{
	(void) ac;
	(void) av;
	t_tv	tv;
	// t_tz	tz;

	gettimeofday(&tv, NULL);
	printf("%ld\t%ld\n", tv.tv_sec, tv.tv_usec);
	printf("hour = %ld\n", tv.tv_sec/(3600*24*365));

	return (0);
}