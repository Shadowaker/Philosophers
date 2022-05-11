/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 20:17:51 by dridolfo          #+#    #+#             */
/*   Updated: 2022/05/11 12:46:46 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

void	*finish_monitor(void *arg)
{
	int		i;
	t_env	*env;

	env = arg;
	sem_wait(env->end);
	i = 0;
	while (i < env->n_philos)
		kill(env->philos[i++].pid, SIGTERM);
	return (NULL);
}

void	*monitor_each_must_eat(void *argv)
{
	t_env	*env;
	int		i;

	env = argv;
	i = 0;
	while (i++ < env->n_philos)
		sem_wait(env->n_eat_finish_philo);
	sem_post(env->end);
	return (NULL);
}

void	*monitor(void *argv)
{
	t_philo			*philo;
	struct timeval	now;
	long long		ms;

	philo = argv;
	while (1)
	{
		sem_wait(philo->check);
		sem_wait(philo->info->acting);
		gettimeofday(&now, NULL);
		ms = time_to_ms(now) - time_to_ms(philo->last_time_to_eat);
		gettimeofday(&now, NULL);
		if (ms >= philo->info->time_to_die)
		{
			printf("%lld\t%d\t %s\n", \
				time_to_ms(now) - time_to_ms(philo->info->born_time), \
				philo->n + 1, "died");
			sem_post(philo->info->end);
			return (NULL);
		}
		sem_post(philo->info->acting);
		sem_post(philo->check);
	}
	return (NULL);
}
