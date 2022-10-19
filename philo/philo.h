/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 09:55:39 by fyuzhyk           #+#    #+#             */
/*   Updated: 2022/10/19 17:34:48 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>

typedef struct s_vars {
	pthread_mutex_t	*forks;
	pthread_mutex_t	main_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	iters_mutex;
	pthread_mutex_t	created_mutex;
	struct timeval	start;
	int				died;
	int				amount;
	int				created;
	int				must_eat;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
}				t_vars;

typedef struct s_philo {
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*main;
	pthread_mutex_t	*death;
	pthread_mutex_t	*iters_mutex;
	pthread_mutex_t	*created_mutex;
	struct timeval	*start;
	int				id;
	int				iters;
	int				amount;
	int				must_eat;
	int				last_meal;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				*died;
	int				*created;
}				t_philo;

void	handle_philos(t_philo *philo);

void	handle_single_philo(t_philo *philo);

t_philo	*init_philos(t_vars *vars);
#endif
