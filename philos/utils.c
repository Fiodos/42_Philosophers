/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:45:32 by fyuzhyk           #+#    #+#             */
/*   Updated: 2022/10/18 21:38:12 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	minus_count;
	int	num;

	i = 0;
	minus_count = 1;
	num = 0;
	while (str[i] == '\r' || str[i] == '\t' || str[i] == ' '
		|| str[i] == '\f' || str[i] == '\v' || str[i] == '\n')
		i++;
	if (str[i] == '-')
	{
		minus_count *= (-1);
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] <= '9' && str[i] >= '0')
	{
		num = (str[i] - '0') + (num * 10);
		i++;
	}
	return (num * minus_count);
}

void	locked_print(t_philo *philo, char mode)
{
	int	timestamp;

	pthread_mutex_lock(philo->main);
	timestamp = get_timestamp(philo->start);
	if (mode == 'f')
		printf("%d %d has taken fork\n", timestamp, philo->id);
	else if (mode == 'e')
		printf("%d %d is eating\n", timestamp, philo->id);
	else if (mode == 's')
		printf("%d %d is sleeping\n", timestamp, philo->id);
	else if (mode == 't')
		printf("%d %d is thinking\n", timestamp, philo->id);
	else if (mode == 'd')
		printf("%d %d died\n", timestamp, philo->id);
	pthread_mutex_unlock(philo->main);
}

void	free_all(t_vars *vars, pthread_t *threads, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < vars->amount)
	{
		pthread_mutex_destroy(&vars->forks[i]);
		i++;
	}
	free(threads);
	free(philos);
	free(vars->forks);
}
