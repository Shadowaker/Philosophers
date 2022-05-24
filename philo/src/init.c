/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 13:44:52 by dridolfo          #+#    #+#             */
/*   Updated: 2022/05/14 18:23:37 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

void	ft_usleep(t_philo *philo, int time)
{
	struct timeval	now;
	long			start;

	gettimeofday(&now, NULL);
	start = time_to_ms(now);
	while ((time_to_ms(now) - start) < (long) time)
	{
		if (philo->env->end)
			return ;
		gettimeofday(&now, NULL);
		usleep(100);
	}
}

static int	parsing_arg(int argc, char **argv, t_env *env)
{
	int	n;

	n = ft_atoi(argv[1]);
	if (n == 0)
		return (1);
	else if (n < 0)
		return (2);
	env->n_philos = n;
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_eat = ft_atoi(argv[3]);
	env->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		env->n_must_eat = ft_atoi(argv[5]);
	return (0);
}

static int	mallocchino(t_env *env)
{
	env->philos = malloc(sizeof(t_philo) * env->n_philos);
	if (!env->philos)
		return (3);
	memset(env->philos, 0, sizeof(t_philo) * env->n_philos);
	env->forks = malloc(sizeof(pthread_mutex_t) * env->n_philos);
	if (!env->forks)
		return (3);
	memset(env->forks, 0, sizeof(pthread_mutex_t) * env->n_philos);
	return (0);
}

static int	philos_init(t_env *env)
{
	int		i;

	pthread_mutex_init(&env->mutex_, NULL);
	i = mallocchino(env);
	if (i == 3)
		return (3);
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
	int	ck;

	ck = parsing_arg(argc, argv, env);
	if (ck != 0)
		return (ck);
	if (env->time_to_die < 0 || env->time_to_eat < 0 || env->time_to_sleep < 0)
		return (1);
	if (philos_init(env))
		return (3);
	return (0);
}
