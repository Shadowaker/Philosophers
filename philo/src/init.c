/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 13:44:52 by dridolfo          #+#    #+#             */
/*   Updated: 2022/04/12 17:23:54 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

static void	parsing_arg(int argc, char **argv, t_env *env)
{
	env->n_philos = ft_atoi(argv[1]);
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_eat = ft_atoi(argv[3]);
	env->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		env->n_must_eat = ft_atoi(argv[5]);
}

static int	philos_init(t_env *env)
{
	int		i;

	pthread_mutex_init(&env->mutex_, NULL);
	ft_malloc(&env->philos, sizeof(t_philo) * env->n_philos);
	ft_malloc(&env->forks, sizeof(pthread_mutex_t) * env->n_philos);
	i = 0;
	while (i < env->n_philos)
	{
		env->philos[i].n = i;
		pthread_mutex_init(&env->forks[i], NULL);
		pthread_mutex_init(&env->philos[i].check_mutex, NULL);
		if (i == 0)
			env->philos[i].left = &env->forks[env->n_philos - 1];
		else
			env->philos[i].left = &env->forks[i - 1];
		env->philos[i].right = &env->forks[i];
		env->philos[i].env = env;
		i++;
	}
	return (0);
}

int	init(int argc, char **argv, t_env *env)
{
	parsing_arg(argc, argv, env);
	// Insert here error handler
	if (philos_init(env))
		return (1);
	return (0);
}
