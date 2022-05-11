/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 20:23:15 by dridolfo          #+#    #+#             */
/*   Updated: 2022/05/11 16:04:37 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

static sem_t	*ft_sem_init(
	const char *name,
	unsigned int value)
{
	sem_t	*sem;

	sem = sem_open(name, O_CREAT | O_EXCL, 0644, value);
	if (sem != SEM_FAILED)
		return (sem);
	sem_unlink(name);
	return (sem_open(name, O_CREAT | O_EXCL, 0644, value));
}

static void	parsing_arg(t_env *env, int argc, char *argv[])
{
	env->n_philos = ft_atoi(argv[1]);
	env->time_to_die = ft_atoi(argv[2]);
	env->time_to_eat = ft_atoi(argv[3]);
	env->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		env->n_must_eat = ft_atoi(argv[5]);
}

static int	check_info(t_env *env, int argc)
{
	if (argc == 6 && env->n_must_eat <= 0)
		return (ft_error_handler("\033[91mERROR: wrong num of must eat\033[0m\n"));
	if (env->n_philos <= 0)
		return (ft_error_handler("\033[91mERROR: wrong num of philo\033[0m\n"));
	if (env->time_to_die < 0)
		return (ft_error_handler("\033[91mERROR: wrong time to die\033[0m\n"));
	if (env->time_to_eat < 0)
		return (ft_error_handler("\033[91mERROR: wrong time to eat\033[0m\n"));
	if (env->time_to_sleep < 0)
		return (ft_error_handler("\033[91mERROR: wrong time to sleep\033[0m\n"));
	return (0);
}

static int	init_philos(t_env *env)
{
	int		i;

	env->end = ft_sem_init("finish", 0);
	env->acting = ft_sem_init("acting", 1);
	env->forks = ft_sem_init("forks", env->n_philos);
	env->n_eat_finish_philo = ft_sem_init("num_of_eat_finish_philo", 0);
	if (ft_mallocchino(&env->philos, sizeof(t_philo) * env->n_philos))
		return (ft_error_handler("\033[91mERROR: malloc failed\033[0m\n"));
	i = 0;
	while (i < env->n_philos)
	{
		env->philos[i].name = name_process("philo", i);
		env->philos[i].check = ft_sem_init(env->philos[i].name, 1);
		env->philos[i].n = i;
		env->philos[i].info = env;
		++i;
	}
	return (0);
}

int	init(t_env *env, int argc, char *argv[])
{
	parsing_arg(env, argc, argv);
	if (check_info(env, argc))
		return (1);
	if (init_philos(env))
		return (1);
	return (0);
}
