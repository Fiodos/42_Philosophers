/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 21:00:05 by fyuzhyk           #+#    #+#             */
/*   Updated: 2022/10/18 21:31:11 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARS_H
# define VARS_H

# include "philo.h"

void	init_mutexes(t_vars *vars);

void	init_times(t_philo *philo, t_vars *vars);

void	init_vars(char **argv, t_vars *vars, int argc);
#endif
