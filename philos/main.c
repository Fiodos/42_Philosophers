// 1 800 200 200 => philo should die
// 5 800 200 200 => no one should die
// 5 800 200 200 7 => no one should die. simulation stops after every philo has eaten 7 times
// 4 410 200 200 => no one should die
// 4 310 200 100 => one philo should die

#include "philo.h"
#include "vars.h"
#include "routine.h"
#include "utils.h"
#include "monitor.h"

int main(int argc, char **argv)
{
	t_vars				vars;
	t_philo				*philos;
	pthread_t			*threads;

	argc = 0;
	init_vars(argv, &vars, argc);
	vars.forks = create_forks(vars.amount);
	philos = init_philos(&vars);
	threads = create_threads(&vars, philos);
	mr_calories_deficit(philos, &vars);
	join_threads(&vars, threads);
	free_all(&vars, threads, philos);
	return (0);
}
