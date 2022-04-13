/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 13:44:46 by dridolfo          #+#    #+#             */
/*   Updated: 2022/04/13 19:27:24 by dridolfo         ###   ########.fr       */
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
	int		ck;

	memset(&env, 0, sizeof(env));
	if (argc != 5 && argc != 6)
		return (printf("\033[91mError.\nWrong parameters passed.\033[0m"));
	ck = init(argc, argv, &env);
	if (ck != 0)
		return (ft_error_handler(ck));
	create_philos(&env);
	join_and_free_philos(&env);
	return (0);
}
