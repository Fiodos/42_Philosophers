/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:59:58 by fyuzhyk           #+#    #+#             */
/*   Updated: 2022/10/18 21:18:12 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "philo.h"
# include "vars.h"

pthread_mutex_t	*create_forks(int amount);

int				ft_atoi(const char *str);

int				get_timestamp(struct timeval *start);

void			my_sleep(int time, t_philo *philo, int timestamp);

void			locked_print(t_philo *philo, char mode);

void			init_forks(t_philo *philo, t_vars *vars, int index);

void			free_all(t_vars *vars, pthread_t *threads, t_philo *philos);
#endif
