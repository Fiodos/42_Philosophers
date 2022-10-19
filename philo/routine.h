/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 21:12:20 by fyuzhyk           #+#    #+#             */
/*   Updated: 2022/10/19 15:17:17 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROUTINE_H
# define ROUTINE_H

# include "philo.h"
# include "forks.h"

void		*dinner(void *arg);

void		await_threads(t_philo *philo);

void		join_threads(t_vars *vars, pthread_t *threads);

int			check_death(t_philo *philo);

int			check_iters(t_philo *philo);

pthread_t	*create_threads(t_vars *vars, t_philo *philos);
#endif
