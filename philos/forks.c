/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:44:40 by fyuzhyk           #+#    #+#             */
/*   Updated: 2022/10/18 21:35:58 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_forks(t_philo *philo, t_vars *vars, int index)
{
	philo->forks = vars->forks;
	if (philo->id == 1)
	{
		philo->r_fork = &vars->forks[0];
		philo->l_fork = &vars->forks[philo->amount - 1];
	}
	else
	{
		philo->r_fork = &vars->forks[index];
		philo->l_fork = &vars->forks[index - 1];
	}
}

pthread_mutex_t	*create_forks(int amount)
{
	int				i;
	pthread_mutex_t *forks;

	i = 0;
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * amount);
	while (i < amount)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}
