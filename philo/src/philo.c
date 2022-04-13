/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 13:44:23 by dridolfo          #+#    #+#             */
/*   Updated: 2022/04/13 19:55:35 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

static void	pickup_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right);
	log_(philo, "has taken a fork");
	pthread_mutex_lock(philo->left);
	log_(philo, "has taken a fork");
}

static void	eating(t_philo *philo)
{
	long long	ms;

	pthread_mutex_lock(&philo->check_mutex);
	gettimeofday(&philo->last_time_to_eat, NULL);
	ms = time_to_ms(philo->last_time_to_eat) - \
		time_to_ms(philo->env->born_time);
	pthread_mutex_lock(&philo->env->mutex_);
	if (!philo->env->end)
		printf("%lld\t%d\t %s\n", ms, philo->n + 1, "is eating");
	philo->n_eat += 1;
	if (philo->n_eat == philo->env->n_must_eat)
		philo->env->n_philos_eat += 1;
	pthread_mutex_unlock(&philo->env->mutex_);
	usleep(philo->env->time_to_eat * 1000);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(&philo->check_mutex);
}

static void	sleeping(t_philo *philo)
{
	log_(philo, "is sleeping");
	usleep(philo->env->time_to_sleep * 1000);
}

static void	thinking(t_philo *philo)
{
	log_(philo, "is thinking");
}

void	*philo(void *argv)
{
	t_philo	*philo;

	philo = argv;
	if (philo->n % 2 == 0)
		usleep(philo->env->time_to_eat * 1000);
	while (!philo->env->end)
	{
		pickup_fork(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
