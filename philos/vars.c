/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:44:28 by fyuzhyk           #+#    #+#             */
/*   Updated: 2022/10/18 21:38:26 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

void	init_mutexes(t_vars *vars)
{
	pthread_mutex_init(&vars->main_mutex, NULL);
	pthread_mutex_init(&vars->death_mutex, NULL);
	pthread_mutex_init(&vars->created_mutex, NULL);
	pthread_mutex_init(&vars->iters_mutex, NULL);
}

void	init_vars(char **argv, t_vars *vars, int argc)
{
	if (argv[5] + argc)
		vars->must_eat = ft_atoi(argv[5]);
	vars->amount = ft_atoi(argv[1]);
	vars->time_to_die = ft_atoi(argv[2]);
	vars->time_to_eat = ft_atoi(argv[3]);
	vars->time_to_sleep = ft_atoi(argv[4]);
	vars->died = 0;
	vars->created = 0;
	init_mutexes(vars);
}

void	init_times(t_philo *philo, t_vars *vars)
{
	philo->time_to_die = vars->time_to_die;
	philo->time_to_eat = vars->time_to_eat;
	philo->time_to_sleep = vars->time_to_sleep;
	philo->start = &vars->start;
}
