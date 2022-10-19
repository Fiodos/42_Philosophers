/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 21:00:05 by fyuzhyk           #+#    #+#             */
/*   Updated: 2022/10/19 15:14:21 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORKS_H
# define FORKS_H

# include "philo.h"

pthread_mutex_t	*create_forks(t_vars *vars);

void			init_forks(t_philo *philo, t_vars *vars, int index);
#endif
