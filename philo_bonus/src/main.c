/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 20:17:26 by dridolfo          #+#    #+#             */
/*   Updated: 2022/05/10 20:47:32 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

static void	join_and_free_philos(t_env *env)
{
	int		i;
	int		status;

	i = -1;
	while (++i < env->n_philos)
	{
		waitpid(env->philos[i].pid, &status, 0);
		sem_close(env->philos[i].check);
		free(env->philos[i].name);
	}
	free(env->philos);
	sem_close(env->end);
	sem_close(env->acting);
	sem_close(env->forks);
	sem_close(env->n_eat_finish_philo);
}

static void	fork_philos(t_env *env)
{
	int			i;

	gettimeofday(&env->born_time, NULL);
	i = 0;
	while (i < env->n_philos)
	{
		env->philos[i].last_time_to_eat = env->born_time;
		env->philos[i].pid = fork();
		if (env->philos[i].pid == 0)
			return (philo(&env->philos[i]));
		else if (env->philos[i].pid < 0)
		{
			ft_error_handler("ERROR: fork failed");
			exit(1);
		}
		++i;
	}
}

int	main(int argc, char *argv[])
{
	t_env		env;
	pthread_t	thread;

	memset(&env, 0, sizeof(t_env));
	if (argc != 5 && argc != 6)
		return (ft_error_handler("\033[91mError.\nWrong args passed.\033[0m"));
	if (init(&env, argc, argv))
		return (1);
	fork_philos(&env);
	if (env.n_must_eat != 0)
		pthread_create(&thread, NULL, monitor_each_must_eat, &env);
	pthread_create(&thread, NULL, finish_monitor, &env);
	join_and_free_philos(&env);
	return (0);
}
