/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 13:44:36 by dridolfo          #+#    #+#             */
/*   Updated: 2022/04/14 16:57:18 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

void	*monitor_each_must_eat(void *argv)
{
	t_env	*env;

	env = argv;
	while (!env->end)
	{
		pthread_mutex_lock(&env->mutex_);
		if (env->n_philos_eat == env->n_philos)
			env->end = 1;
		pthread_mutex_unlock(&env->mutex_);
	}
	return (NULL);
}

void	*monitor(void *argv)
{
	t_philo			*philo;
	struct timeval	now;
	long long		ms;

	philo = argv;
	while (!philo->env->end)
	{
		pthread_mutex_lock(&philo->check_mutex);
		pthread_mutex_lock(&philo->env->mutex_);
		gettimeofday(&now, NULL);
		ms = time_to_ms(now) - time_to_ms(philo->last_time_to_eat);
		gettimeofday(&now, NULL);
		if (ms >= philo->env->time_to_die && philo->env->end == 0)
		{
			printf("%lld\t%d\t %s\n", \
				time_to_ms(now) - time_to_ms(philo->env->born_time), \
				philo->n + 1, "died");
			philo->env->end = 1;
		}
		pthread_mutex_unlock(&philo->env->mutex_);
		pthread_mutex_unlock(&philo->check_mutex);
	}
	return (NULL);
}
