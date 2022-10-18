/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:28:20 by fyuzhyk           #+#    #+#             */
/*   Updated: 2022/10/18 21:35:40 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "routine.h"

pthread_t	*create_threads(t_vars *vars, t_philo *philos)
{
	int			i;
	pthread_t	*threads;

	i = 0;
	threads = (pthread_t *)malloc(sizeof(pthread_t) * vars->amount);
	while (i < vars->amount)
	{
		pthread_create(&threads[i], NULL, &dinner, &philos[i]);
		i++;
	}
	pthread_mutex_lock(philos[i - 1].created_mutex);
	vars->created = 1;
	pthread_mutex_unlock(philos[i - 1].created_mutex);
	gettimeofday(philos[i - 1].start, NULL);
	return (threads);
}

void	await_threads(t_philo *philo)
{
	while (1)
	{
		usleep(100);
		pthread_mutex_lock(philo->created_mutex);
		if (*philo->created)
		{
			pthread_mutex_unlock(philo->created_mutex);
			return ;
		}
		pthread_mutex_unlock(philo->created_mutex);
	}
}

void	join_threads(t_vars *vars, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < vars->amount)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}
