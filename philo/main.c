/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:07:55 by fyuzhyk           #+#    #+#             */
/*   Updated: 2022/10/19 16:47:04 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "forks.h"
#include "routine.h"
#include "utils.h"
#include "monitor.h"

int	main(int argc, char **argv)
{
	t_vars				vars;
	t_philo				*philos;
	pthread_t			*threads;

	if (check_input(argc))
		return (1);
	if (init_vars(argv, &vars))
		return (1);
	vars.forks = create_forks(&vars);
	if (!vars.forks)
		return (1);
	philos = init_philos(&vars);
	if (!philos)
		return (1);
	threads = create_threads(&vars, philos);
	if (!threads)
	{
		free_and_destroy(&vars, threads, philos);
		return (1);
	}
	mr_calorie_deficit(philos, &vars);
	join_threads(&vars, threads);
	free_and_destroy(&vars, threads, philos);
	return (0);
}
