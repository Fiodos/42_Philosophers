/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:30:11 by fyuzhyk           #+#    #+#             */
/*   Updated: 2022/10/18 21:37:17 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "routine.h"
#include "utils.h"

void	handle_philos(t_philo *philo)
{
	if (check_death(philo))
		return ;
	pthread_mutex_lock(philo->l_fork);
	locked_print(philo, 'f');
	pthread_mutex_lock(philo->r_fork);
	locked_print(philo, 'f');
	locked_print(philo, 'e');
	philo->last_meal = get_timestamp(philo->start);
	my_sleep(philo->time_to_eat, philo, get_timestamp(philo->start));
	pthread_mutex_lock(philo->iters_mutex);
	philo->iters++;
	pthread_mutex_unlock(philo->iters_mutex);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	if (check_death(philo))
		return ;
	locked_print(philo, 's');
	my_sleep(philo->time_to_sleep, philo, get_timestamp(philo->start));
	locked_print(philo, 't');
}

t_philo	*init_philos(t_vars *vars)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = (t_philo *)malloc(sizeof(t_philo) * vars->amount);
	while (i < vars->amount)
	{
		if (vars->must_eat)
			philo[i].must_eat = vars->must_eat;
		philo[i].id = i + 1;
		philo[i].amount = vars->amount;
		init_times(&philo[i], vars);
		init_forks(&philo[i], vars, i);
		philo[i].main = &vars->main_mutex;
		philo[i].death = &vars->death_mutex;
		philo[i].created_mutex = &vars->created_mutex;
		philo[i].iters_mutex = &vars->iters_mutex;
		philo[i].last_meal = 0;
		philo[i].iters = 0;
		philo[i].died = &vars->died;
		philo[i].created = &vars->created;
		i++;
	}
	return (philo);
}
