/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:32:52 by fyuzhyk           #+#    #+#             */
/*   Updated: 2022/10/19 15:33:37 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "routine.h"

void	*dinner(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	await_threads(philo);
	if (philo->id % 2 == 0)
		usleep(philo->time_to_eat * 1000);
	while (1)
	{
		handle_philos(philo);
		if (check_iters(philo))
			return (NULL);
		if (check_death(philo))
			return (NULL);
	}
}

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(philo->death);
	if (*philo->died)
	{
		pthread_mutex_unlock(philo->death);
		return (1);
	}
	pthread_mutex_unlock(philo->death);
	return (0);
}

int	check_iters(t_philo *philo)
{
	pthread_mutex_lock(philo->iters_mutex);
	if (philo->iters == philo->must_eat && philo->must_eat > 0)
	{
		pthread_mutex_unlock(philo->iters_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->iters_mutex);
	return (0);
}
