/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 13:44:23 by dridolfo          #+#    #+#             */
/*   Updated: 2022/05/11 17:35:17 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

static void	pickup_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right);
	log_(philo, "has taken a fork");
	while (philo->env->n_philos == 1)
	{
		if (philo->env->end)
			return ;
		usleep(1);
	}
	pthread_mutex_lock(philo->left);
	log_(philo, "has taken a fork");
}

static void	eating(t_philo *philo)
{
	long	ms;

	pthread_mutex_lock(&philo->check_mutex);
	gettimeofday(&philo->last_time_to_eat, NULL);
	ms = time_to_ms(philo->last_time_to_eat) - \
		time_to_ms(philo->env->born_time);
	pthread_mutex_lock(&philo->env->mutex_);
	if (!philo->env->end)
		printf("%ld\t%d\t %s\n", ms, philo->n + 1, "is eating");
	philo->n_eat += 1;
	if (philo->n_eat == philo->env->n_must_eat)
		philo->env->n_philos_eat += 1;
	pthread_mutex_unlock(&philo->env->mutex_);
	ft_usleep(philo, philo->env->time_to_eat);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(&philo->check_mutex);
}

static void	sleeping(t_philo *philo)
{
	int	i;

	i = 0;
	log_(philo, "is sleeping");
	ft_usleep(philo, philo->env->time_to_sleep);
}

static void	thinking(t_philo *philo)
{
	log_(philo, "is thinking");
}

void	*philo(void *argv)
{
	t_philo	*philo;

	philo = argv;
	philo->n_eat = 0;
	if (philo->n % 2 == 0)
		ft_usleep(philo, philo->env->time_to_eat);
	while (!philo->env->end)
	{
		pickup_fork(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
