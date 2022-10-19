/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:51:11 by fyuzhyk           #+#    #+#             */
/*   Updated: 2022/10/19 16:46:54 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITOR_H
# define MONITOR_H

# include "philo.h"

void	mr_calorie_deficit(t_philo *philos, t_vars *vars);

int		scan_death(t_philo *philo, t_vars *vars);

int		scan_iters(t_philo *philo, t_vars *vars, int *have_eaten);
#endif
