/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 09:55:39 by fyuzhyk           #+#    #+#             */
/*   Updated: 2022/10/17 17:42:23 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <errno.h>

typedef struct s_vars {
	pthread_mutex_t	*forks;
	pthread_mutex_t *main_mutex;
	struct timeval	*start;
	int				amount;
	int				created;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
}				t_vars;

typedef struct s_philo {
	pthread_mutex_t	*forks;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*main;
	struct timeval	*start;
	int				iterations;
	int				id;
	int				amount;
	int				must_eat;
	int				last_meal;
	// int				starvation;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				*created;
}				t_philo;
#endif
