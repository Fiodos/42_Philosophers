// 1 800 200 200 => philo should die
// 5 800 200 200 => no one should die
// 5 800 200 200 7 => no one should die. simulation stops after every philo has eaten 7 times
// 4 410 200 200 => no one should die
// 4 310 200 100 => one philo should die

#include "../lib/philo.h"

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

int	get_timestamp(t_vars *vars)
{
	int	time;

	gettimeofday(vars->end, NULL);
	time = vars->end->tv_sec * 1000000 + vars->end->tv_usec;
	time -= (vars->start->tv_sec * 1000000 + vars->start->tv_usec);
	return (time / 1000);
}

void	my_sleep(int time, t_vars *vars)
{
	int	end_stamp;

	end_stamp = get_timestamp(vars) + time;
	while (get_timestamp(vars) < end_stamp)
		usleep(time / 10);
}

void	custom_lock(pthread_mutex_t mutex)
{
	if (pthread_mutex_lock(&mutex) != 0)
	{
		perror("mutex lock failed\n");
		exit(errno);
	}
}

void	custom_unlock(pthread_mutex_t mutex)
{
	if (pthread_mutex_unlock(&mutex) != 0)
	{
		perror("mutex unlock failed\n");
		exit(errno);
	}
}

int	check_if_dead(t_vars *vars, int last_meal, int id)
{
	if (last_meal + vars->time_to_die < get_timestamp(vars))
	{
		printf("%d %d died!\n", get_timestamp(vars), id);
		return (1);
	}
	else
		return (0);
}

void	eating(t_vars *vars, int *last_meal, int id)
{
	printf("%d %d is eating\n", get_timestamp(vars), id);
	my_sleep(vars->time_to_eat, vars);
	*last_meal = get_timestamp(vars);
	if (id == 1)
	{
		custom_unlock(vars->forks[0]);
		custom_unlock(vars->forks[vars->amount - 1]);
	}
	else
	{
		custom_unlock(vars->forks[id - 1]);
		custom_unlock(vars->forks[id - 2]);
	}
}

void	sleeping(t_vars *vars, int id)
{
	printf("%d %d is sleeping\n", get_timestamp(vars), id);
	my_sleep(vars->time_to_sleep, vars);
}

void	thinking(t_vars *vars, int id)
{
	printf("%d %d is thinking\n", get_timestamp(vars), id);
}

void	take_forks(t_vars *vars, int id)
{
	if (id == 1)
	{
		custom_lock(vars->forks[0]);
		custom_lock(vars->forks[vars->amount - 1]);
	}
	else
	{
		custom_lock(vars->forks[id - 1]);
		custom_lock(vars->forks[id - 2]);
	}
	printf("%d %d has taken fork\n", get_timestamp(vars), id);
	printf("%d %d has taken fork\n", get_timestamp(vars), id);
}

// void	*test(void *arg)
// {
// 	t_vars	*new_vars;
// 	int		last_meal;
// 	int		id;

// 	new_vars = (t_vars *)arg;
// 	last_meal = 0;
// 	custom_lock(*new_vars->main_mutex);
// 	id = new_vars->phil_id++;
// 	custom_unlock(*new_vars->main_mutex);
// 	usleep(500);
// 	gettimeofday(new_vars->start, NULL);
// 	while (1)
// 	{
// 		if (id == 1)
// 		{
// 			pthread_mutex_lock(&new_vars->forks[0]);
// 			pthread_mutex_lock(&new_vars->forks[new_vars->amount - 1]);
// 		}
// 		else
// 		{
// 			pthread_mutex_lock(&new_vars->forks[id - 1]);
// 			pthread_mutex_lock(&new_vars->forks[id - 2]);
// 		}
// 		if (check_if_dead(new_vars, last_meal, id))
// 			exit(1);
// 		printf("%d %d has taken fork\n", get_timestamp(new_vars), id);
// 		printf("%d %d has taken fork\n", get_timestamp(new_vars), id);
// 		printf("%d %d is eating\n", get_timestamp(new_vars), id);
// 		my_sleep(new_vars->time_to_eat, new_vars);
// 		last_meal = get_timestamp(new_vars);
// 		if (id == 1)
// 		{
// 			pthread_mutex_unlock(&new_vars->forks[0]);
// 			pthread_mutex_unlock(&new_vars->forks[new_vars->amount - 1]);
// 		}
// 		else
// 		{
// 			pthread_mutex_unlock(&new_vars->forks[id - 1]);
// 			pthread_mutex_unlock(&new_vars->forks[id - 2]);
// 		}
// 		sleeping(new_vars, id);
// 		thinking(new_vars, id);
// 	}
// 	exit (1);
// }

void	*test(void *arg)
{
	t_vars	*vars;
	int		last_meal;
	int		id;

	vars = (t_vars *)arg;
	last_meal = 0;
	custom_lock(*vars->main_mutex);
	id = vars->philo_id++;
	custom_unlock(*vars->main_mutex);
	usleep(500); // this should make sure that all threads are running;
	gettimeofday(vars->start, NULL); // start global clock;
	if (id % 2 == 0) // even philos sleep at the beginning;
		my_sleep(vars->time_to_eat, vars);
	while (1)
	{
		if (id % 2) // odd;
		{
			if (check_if_dead(vars, last_meal, id))
				exit(1);
			if (id == 1)
			{
				pthread_mutex_lock(&vars->forks[0]);
				pthread_mutex_lock(&vars->forks[vars->amount - 1]);
				if (vars->fork_array[0] > 0 && vars->fork_array[vars->amount - 1] > 0)
				{
					memset(&vars->fork_array[0], 0, 1);
					printf("%d %d has taken fork\n", get_timestamp(vars), id);
					memset(&vars->fork_array[vars->amount - 1], 0, 1);
					printf("%d %d has taken fork\n", get_timestamp(vars), id);
				}
			}
			else
			{
				pthread_mutex_lock(&vars->forks[id - 1]);
				pthread_mutex_lock(&vars->forks[id - 2]);
				if (vars->fork_array[id - 1] > 0 && vars->fork_array[id - 2] > 0)
				{
					memset(&vars->fork_array[id - 1], 0, 1);
					printf("%d %d has taken fork\n", get_timestamp(vars), id);
					memset(&vars->fork_array[id - 2], 0, 1);
					printf("%d %d has taken fork\n", get_timestamp(vars), id);
				}
			}
			printf("%d %d is eating\n", get_timestamp(vars), id);
			last_meal = get_timestamp(vars);
			my_sleep(vars->time_to_eat, vars);
			if (id == 1)
			{
				memset(&vars->fork_array[0], 1, 1);
				memset(&vars->fork_array[vars->amount - 1], 1, 1);
				pthread_mutex_unlock(&vars->forks[0]);
				pthread_mutex_unlock(&vars->forks[vars->amount - 1]);
				sleeping(vars, id);
				printf("%d %d is thinking\n", get_timestamp(vars), id);
				while (vars->fork_array[0] == 0 && vars->fork_array[vars->amount - 1] == 0)
					usleep(10);
			}
			else
			{
				memset(&vars->fork_array[id - 1], 1, 1);
				memset(&vars->fork_array[id - 2], 1, 1);
				pthread_mutex_unlock(&vars->forks[id - 1]);
				pthread_mutex_unlock(&vars->forks[id - 2]);
				sleeping(vars, id);
				printf("%d %d is thinking\n", get_timestamp(vars), id);
				while (vars->fork_array[id - 1] == 0 && vars->fork_array[id - 2] == 0)
					usleep(10);
			}
		}
		else
		{
			if (check_if_dead(vars, last_meal, id))
				exit(1);
			pthread_mutex_lock(&vars->forks[id - 1]);
			pthread_mutex_lock(&vars->forks[id - 2]);
			if (vars->fork_array[id - 1] > 0 && vars->fork_array[id - 2] > 0)
			{
				memset(&vars->fork_array[id - 1], 0, 1);
				printf("%d %d has taken fork\n", get_timestamp(vars), id);
				memset(&vars->fork_array[id - 2], 0, 1);
				printf("%d %d has taken fork\n", get_timestamp(vars), id);
				printf("%d %d is eating\n", get_timestamp(vars), id);
				last_meal = get_timestamp(vars);
				my_sleep(vars->time_to_eat, vars);
				memset(&vars->fork_array[id - 1], 1, 1);
				memset(&vars->fork_array[id - 2], 1, 1);
				pthread_mutex_unlock(&vars->forks[id - 1]);
				pthread_mutex_unlock(&vars->forks[id - 2]);
				sleeping(vars, id);
				printf("%d %d is thinking\n", get_timestamp(vars), id);
			}
			while (vars->fork_array[id - 1] == 0 && vars->fork_array[id - 2] == 0)
				usleep(10);
		}
		// exit(0);
	}
}

pthread_mutex_t	*create_forks(int amount)
{
	int	i;
	pthread_mutex_t *forks;

	i = 0;
	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * amount);
	while (i < amount)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

int	*create_fork_array(int amount)
{
	int	i;
	int	*forks;

	i = 0;
	forks = (int *)malloc(sizeof(int) * amount);
	while (i < amount)
	{
		forks[i] = 1;
		i++;
	}
	forks[i] = 0;
	return (forks);
}

pthread_t	*create_philos(t_vars *vars)
{
	pthread_t	*philos;
	int			i;

	philos = (pthread_t *)malloc(sizeof(pthread_t) * vars->amount);
	i = 0;
	while (i < vars->amount)
	{
		pthread_create(&philos[i], NULL, &test, vars);
		i++;
	}
	i = 0;
	while (i < vars->amount)
	{
		pthread_join(philos[i], NULL);
		i++;
	}
	return (philos);
}

void	init_times(char **argv, t_vars *vars)
{
	vars->time_to_die = ft_atoi(argv[2]);
	vars->time_to_eat = ft_atoi(argv[3]);
	vars->time_to_sleep = ft_atoi(argv[4]);
}

int main(int argc, char **argv)
{
	t_vars		vars;
	pthread_t	*philos;
	pthread_mutex_t	main;

	argc = 0;
	vars.philo_id = 1;
	vars.amount = ft_atoi(argv[1]);
	vars.start = malloc(sizeof(struct timeval *));
	vars.end = malloc(sizeof(struct timeval *));
	vars.fork_array = create_fork_array(vars.amount);
	pthread_mutex_init(&main, NULL);
	vars.main_mutex = &main;
	init_times(argv, &vars);
	vars.forks = create_forks(vars.amount);
	philos = create_philos(&vars);
	printf("End of main\n");
	return (0);
}
