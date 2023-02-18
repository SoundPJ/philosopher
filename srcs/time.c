/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:11:10 by pjerddee          #+#    #+#             */
/*   Updated: 2023/02/18 23:35:24 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_tstamp(t_data *data)
{
	t_tv	ta;
	t_tv	tb;
	long	tstamp;

	ta = data->tstart;
	gettimeofday(&tb, NULL);
	tstamp = ((tb.tv_sec - ta.tv_sec) * 1000) \
		+ ((tb.tv_usec - ta.tv_usec) / 1000);
	// printf("tstamp = %ld\n", tstamp);
	return (tstamp);
}

void	sleep_ms(int tsleep_ms)
{
	t_tv	ta;
	t_tv	tb;
	long	tdiff;

	gettimeofday(&ta, NULL);
	tdiff = 0;
	while (tdiff < tsleep_ms)
	{
		gettimeofday(&tb, NULL);
		tdiff = ((tb.tv_sec - ta.tv_sec) * 1000) \
			+ ((tb.tv_usec - ta.tv_usec) / 1000);
	}
}
