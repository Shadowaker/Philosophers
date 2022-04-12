/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 13:44:46 by dridolfo          #+#    #+#             */
/*   Updated: 2022/04/12 17:24:43 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

static void	join_and_free_philos(t_env *env)
{
	int		i;

	i = 0;
	while (i < env->n_philos)
	{
		pthread_join(env->philos[i].thread, NULL);
		pthread_mutex_destroy(&env->philos[i++].check_mutex);
	}
	free(env->philos);
	i = 0;
	while (i < env->n_philos)
		pthread_mutex_destroy(&env->forks[i++]);
	free(env->forks);
}

static void	create_philos(t_env *env)
{
	int			i;
	pthread_t	thread;

	gettimeofday(&env->born_time, NULL);
	i = 0;
	while (i < env->n_philos)
	{
		env->philos[i].last_time_to_eat = env->born_time;
		pthread_create(&env->philos[i].thread, NULL, \
			philo, &env->philos[i]);
		pthread_create(&thread, NULL, monitor, &env->philos[i]);
		pthread_detach(thread);
		i++;
	}
	if (env->n_must_eat != 0)
	{
		pthread_create(&thread, NULL, monitor_each_must_eat, env);
		pthread_detach(thread);
	}
}

int	main(int argc, char **argv)
{
	t_env	env;

	memset(&env, 0, sizeof(env));
	if (argc != 5 && argc != 6)
	// Error here.
		return (1);
	if (init(argc, argv, &env))
	// Error here.
		return (1);
	create_philos(&env);
	join_and_free_philos(&env);
	return (0);
}
