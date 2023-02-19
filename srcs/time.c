/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:11:10 by pjerddee          #+#    #+#             */
/*   Updated: 2023/02/19 15:43:31 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// get timestamp from tstart
long	getts(t_data *data)
{
	t_tv	ta;
	t_tv	tb;
	long	tstamp;

	ta = data->tstart;
	gettimeofday(&tb, NULL);
	tstamp = ((tb.tv_sec - ta.tv_sec) * 1000) \
		+ ((tb.tv_usec - ta.tv_usec) / 1000);
	return (tstamp);
}

int	istimesout(t_philo *philo)
{
	return (getts(philo->data) - philo->tseat < philo->data->tdie);
}
