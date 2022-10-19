/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:44:28 by fyuzhyk           #+#    #+#             */
/*   Updated: 2022/10/19 17:33:16 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

void	destroy_if_failed(t_vars *vars, int mode)
{
	if (mode == 1)
		pthread_mutex_destroy(&vars->main_mutex);
	else if (mode == 2)
	{
		pthread_mutex_destroy(&vars->main_mutex);
		pthread_mutex_destroy(&vars->death_mutex);
	}
	else if (mode == 3)
	{
		pthread_mutex_destroy(&vars->main_mutex);
		pthread_mutex_destroy(&vars->death_mutex);
		pthread_mutex_destroy(&vars->iters_mutex);
	}
	else if (mode == 4)
	{
		pthread_mutex_destroy(&vars->main_mutex);
		pthread_mutex_destroy(&vars->death_mutex);
		pthread_mutex_destroy(&vars->iters_mutex);
		pthread_mutex_destroy(&vars->created_mutex);
	}
}

int	init_mutexes(t_vars *vars)
{
	if (pthread_mutex_init(&vars->main_mutex, NULL) != 0)
	{
		printf("init main_mutex failed\n");
		return (1);
	}
	if (pthread_mutex_init(&vars->death_mutex, NULL) != 0)
	{
		printf("init death_mutex failed\n");
		destroy_if_failed(vars, 1);
		return (1);
	}
	if (pthread_mutex_init(&vars->iters_mutex, NULL) != 0)
	{
		printf("init iters_mutex failed\n");
		destroy_if_failed(vars, 2);
		return (1);
	}
	if (pthread_mutex_init(&vars->created_mutex, NULL) != 0)
	{
		printf("init created_mutex failed\n");
		destroy_if_failed(vars, 3);
		return (1);
	}
	return (0);
}

int	init_vars(char **argv, t_vars *vars)
{
	if (argv[5])
		vars->must_eat = ft_atoi(argv[5]);
	else
		vars->must_eat = 0;
	vars->amount = ft_atoi(argv[1]);
	vars->time_to_die = ft_atoi(argv[2]);
	vars->time_to_eat = ft_atoi(argv[3]);
	vars->time_to_sleep = ft_atoi(argv[4]);
	if (vars->must_eat == -1 || vars->amount == -1
		|| vars->time_to_die == -1 || vars->time_to_eat == -1
		|| vars->time_to_sleep == -1)
	{
		printf("invalid argument\n");
		return (1);
	}
	vars->died = 0;
	vars->created = 0;
	if (init_mutexes(vars))
	{
		printf("vars creation failed\n");
		return (1);
	}
	return (0);
}

void	init_times(t_philo *philo, t_vars *vars)
{
	philo->time_to_die = vars->time_to_die;
	philo->time_to_eat = vars->time_to_eat;
	philo->time_to_sleep = vars->time_to_sleep;
	philo->start = &vars->start;
}
