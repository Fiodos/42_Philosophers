/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 09:55:39 by fyuzhyk           #+#    #+#             */
/*   Updated: 2022/10/16 15:25:00 by fyuzhyk          ###   ########.fr       */
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
	struct timeval	*end;
	int				created;
	int				amount;
	int				philo_id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				*fork_array;
	int				*iterations;
	int				*last_meal;
	int				must_eat;
	int				reached_end;
}				t_vars;
#endif
