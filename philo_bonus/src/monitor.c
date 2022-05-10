/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 20:17:51 by dridolfo          #+#    #+#             */
/*   Updated: 2022/05/10 20:20:44 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

void	*finish_monitor(void *arg)
{
	int		i;
	t_info	*info;

	info = arg;
	sem_wait(info->end);
	i = 0;
	while (i < info->n_philos)
		kill(info->philos[i++].pid, SIGTERM);
	return (NULL);
}

void	*monitor_each_must_eat(void *argv)
{
	t_info	*info;
	int		i;

	info = argv;
	i = 0;
	while (i++ < info->n_philos)
		sem_wait(info->n_eat_finish_philo);
	sem_post(info->end);
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
