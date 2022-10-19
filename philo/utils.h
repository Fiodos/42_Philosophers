/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:59:58 by fyuzhyk           #+#    #+#             */
/*   Updated: 2022/10/19 16:36:05 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "philo.h"
# include "forks.h"

int		ft_atoi(const char *str);

int		init_mutexes(t_vars *vars);

int		check_input(int argc);

int		get_timestamp(struct timeval *start);

int		init_vars(char **argv, t_vars *vars);

void	destroy_mutexes(t_vars *vars);

void	locked_print(t_philo *philo, char mode);

void	init_times(t_philo *philo, t_vars *vars);

void	destroy_if_failed(t_vars *vars, int mode);

void	my_sleep(int time, t_philo *philo, int timestamp);

void	init_forks(t_philo *philo, t_vars *vars, int index);

void	free_and_destroy(t_vars *vars, pthread_t *threads, t_philo *philos);
#endif
