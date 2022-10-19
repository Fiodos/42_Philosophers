/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:44:40 by fyuzhyk           #+#    #+#             */
/*   Updated: 2022/10/19 15:33:49 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

static void	handle_forks_fail(pthread_mutex_t *forks, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}

void	init_forks(t_philo *philo, t_vars *vars, int index)
{
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

pthread_mutex_t	*create_forks(t_vars *vars)
{
	int				i;
	pthread_mutex_t	*forks;

	i = 0;
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * vars->amount);
	if (!forks)
	{
		printf("malloc failed\n");
		destroy_if_failed(vars, 4);
		return (NULL);
	}
	while (i < vars->amount)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			printf("create forks failed\n");
			handle_forks_fail(forks, i);
			return (NULL);
		}
		i++;
	}
	return (forks);
}
