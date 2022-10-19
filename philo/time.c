/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 09:46:50 by fyuzhyk           #+#    #+#             */
/*   Updated: 2022/10/19 17:18:37 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_timestamp(struct timeval *start)
{
	int				time;
	struct timeval	curr;

	gettimeofday(&curr, NULL);
	time = curr.tv_sec * 1000000 + curr.tv_usec;
	time -= (start->tv_sec * 1000000 + start->tv_usec);
	return (time / 1000);
}

void	my_sleep(int time, t_philo *philo, int timestamp)
{
	int	end_stamp;

	end_stamp = timestamp + time;
	while (get_timestamp(philo->start) < end_stamp)
		usleep(200);
}
