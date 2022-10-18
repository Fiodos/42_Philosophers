/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:31:29 by fyuzhyk           #+#    #+#             */
/*   Updated: 2022/10/18 21:36:11 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

int	scan_iters(t_philo *philo, t_vars *vars, int *have_eaten)
{
	pthread_mutex_lock(philo->iters_mutex);
	if (philo->iters >= vars->must_eat && vars->must_eat > 0)
	{
		(*have_eaten)++;
		if (*have_eaten == vars->amount)
		{
			pthread_mutex_unlock(philo->iters_mutex);
			return (1);
		}
	}
	pthread_mutex_unlock(philo->iters_mutex);
	return (0);
}

int	scan_death(t_philo *philo, t_vars *vars)
{
	int	timestamp;

	timestamp = get_timestamp(&vars->start);
	if (philo->last_meal + philo->time_to_die < timestamp)
	{
		pthread_mutex_lock(philo->death);
		vars->died = 1;
		pthread_mutex_unlock(philo->death);
		locked_print(philo, 'd');
		return (1);
	}
	return (0);
}

void	mr_calories_deficit(t_philo *philos, t_vars *vars)
{
	int	i;
	int	have_eaten;

	have_eaten = 0;
	while (1)
	{
		i = 0;
		while (i < vars->amount)
		{
			if (scan_iters(&philos[i], vars, &have_eaten))
				return ;
			if (scan_death(&philos[i], vars))
				return ;
			i++;
		}
	}
}
