// 1 800 200 200 => philo should die
// 5 800 200 200 => no one should die
// 5 800 200 200 7 => no one should die. simulation stops after every philo has eaten 7 times
// 4 410 200 200 => no one should die
// 4 310 200 100 => one philo should die

#include "../lib/philo.h"

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

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

void	phil_sleep(struct timeval *time, int time_to_sleep, int philo)
{
	gettimeofday(time, NULL);
	printf("%d %d is sleeping\n", time->tv_usec, philo);
	usleep(time_to_sleep);
}

void	take_fork(t_vars *new_vars, struct timeval *time, int philo)
{
	memset(new_vars->forks, 0, sizeof(*new_vars->forks) * new_vars->amount);
	gettimeofday(time, NULL);
	printf("%d %d has taken a fork\n", time->tv_usec, philo);
}

void	eat(t_vars *new_vars, struct timeval *time, int philo, int time_to_eat)
{
	gettimeofday(time, NULL);
	printf("%d %d is eating\n", time->tv_usec, philo);
	usleep(time_to_eat);
	memset(new_vars->forks, 1, sizeof(*new_vars->forks) * new_vars->amount);
}

void	think(struct timeval *time, int philo, int time_to_die, int time_to_sleep)
{
	gettimeofday(time, NULL);
	printf("%d %d is thinking\n", time->tv_usec, philo);
	usleep(time_to_die - time_to_sleep);
}

void	*test(void *arg)
{
	struct	timeval *time;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	char	*ttd_arg;
	char	*tte_arg;
	char	*tts_arg;
	pthread_t	id;
	int			philo;
	t_vars	*new_vars;

	id = pthread_self();
	new_vars = (t_vars *)arg;
	ttd_arg = new_vars->argv[2];
	tte_arg = new_vars->argv[3];
	tts_arg = new_vars->argv[4];
	time = malloc(sizeof(struct timeval *));
	time_to_die = ft_atoi(ttd_arg);
	time_to_eat = ft_atoi(tte_arg);
	time_to_sleep = ft_atoi(tts_arg);
	time_to_die *= 1000;
	time_to_eat *= 1000;
	time_to_sleep *= 1000;
	gettimeofday(time, NULL);
	printf("start: %d\n", time->tv_usec);
	pthread_mutex_lock(new_vars->mutex);
	philo = new_vars->phil_id++;
	while (new_vars->forks[0] > 0 && new_vars->forks[1] > 0)
	{
		take_fork(new_vars, time, philo);
		eat(new_vars, time, philo, time_to_eat);
		pthread_mutex_unlock(new_vars->mutex);
		phil_sleep(time, time_to_sleep, philo);
		think(time, philo, time_to_die, time_to_sleep);
	}
	gettimeofday(time, NULL);
	printf("end: %d\n", time->tv_usec);
	printf("Philo %d died!\n", philo);
	exit (1);
}

void	create_forks(int amount, int *fork_arr)
{
	int	i;

	i = 0;
	while (i < amount)
	{
		*(fork_arr + i) = i + 1;
		i++;
	}
}

pthread_t	**create_philos(t_vars *vars)
{
	pthread_t	**philos;
	int			i;

	philos = malloc(sizeof(struct pthread_t *) * vars->amount);
	i = 0;
	while (i < vars->amount)
	{
		philos[i] = malloc(sizeof(struct pthread_t *));
		pthread_create(philos[i], NULL, &test, vars);
		i++;
	}
	i = 0;
	while (i < vars->amount)
	{
		pthread_join(*philos[i], NULL);
		i++;
	}
	return (philos);
}

int main(int argc, char **argv)
{
	t_vars			vars;
	pthread_t		**philos;
	pthread_mutex_t	main_mutex;

	argc = 0;
	pthread_mutex_init(&main_mutex, NULL);
	vars.phil_id = 1;
	vars.mutex = &main_mutex;
	vars.amount = ft_atoi(argv[1]);
	vars.forks = malloc(sizeof(int) * vars.amount);
	create_forks(vars.amount, vars.forks);
	vars.argv = argv;
	philos = create_philos(&vars);
	pthread_mutex_destroy(vars.mutex);
	printf("End of main\n");
	return (0);
}
