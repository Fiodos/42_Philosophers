/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyuzhyk <fyuzhyk@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 20:45:32 by fyuzhyk           #+#    #+#             */
/*   Updated: 2022/10/19 16:36:22 by fyuzhyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"
#include "routine.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (str[i] == '\r' || str[i] == '\t' || str[i] == ' '
		|| str[i] == '\f' || str[i] == '\v' || str[i] == '\n')
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] <= '9' && str[i] >= '0')
		num = (str[i++] - '0') + (num * 10);
	if (str[i] != '\0')
		return (-1);
	if (num == 0 && i == 0)
		return (-1);
	return (num);
}

void	locked_print(t_philo *philo, char mode)
{
	int	timestamp;

	pthread_mutex_lock(philo->main);
	if (check_death(philo))
	{
		pthread_mutex_unlock(philo->main);
		return ;
	}
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

void	destroy_mutexes(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->amount)
	{
		if (pthread_mutex_destroy(&vars->forks[i]) != 0)
		{
			printf("destroying fork mutex failed\n");
			return ;
		}
		i++;
	}
	if (pthread_mutex_destroy(&vars->main_mutex) != 0)
		printf("destroying main_mutex failed\n");
	if (pthread_mutex_destroy(&vars->death_mutex) != 0)
		printf("destroying death_mutex failed\n");
	if (pthread_mutex_destroy(&vars->iters_mutex) != 0)
		printf("destroying iters_mutex failed\n");
	if (pthread_mutex_destroy(&vars->created_mutex) != 0)
		printf("destroying created_mutex failed\n");
}

void	free_and_destroy(t_vars *vars, pthread_t *threads, t_philo *philos)
{
	destroy_mutexes(vars);
	free(philos);
	if (threads)
		free(threads);
	free(vars->forks);
}

int	check_input(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("invalid amount of arguments\n");
		return (1);
	}
	return (0);
}
