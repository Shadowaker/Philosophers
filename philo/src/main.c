/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 13:44:46 by dridolfo          #+#    #+#             */
/*   Updated: 2022/05/11 17:26:35 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

static int	ft_isint(char **s, int size)
{
	int	i;
	int	j;

	i = 1;
	while (i < size)
	{
		j = 0;
		while (s[i][j] != '\0')
		{
			if (s[i][j] < 48 || s[i][j] > 57)
			{
				if (s[i][j] == 43 && size != 1)
					;
				else
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

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
	if (argc < 5 || argc > 6)
		return (ft_error_handler(4));
	ck = ft_isint(argv, argc);
	if (ck != 1)
		return (ft_error_handler(1));
	ck = init(argc, argv, &env);
	if (ck != 0)
		return (ft_error_handler(ck));
	create_philos(&env);
	join_and_free_philos(&env);
	return (0);
}
