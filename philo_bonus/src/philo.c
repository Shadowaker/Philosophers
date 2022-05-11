/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 20:20:52 by dridolfo          #+#    #+#             */
/*   Updated: 2022/05/11 12:49:04 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

static void	pickup_fork(t_philo *philo)
{
	sem_wait(philo->info->forks);
	pprint(philo, "has taken a fork");
	sem_wait(philo->info->forks);
	pprint(philo, "has taken a fork");
}

static void	eating(t_philo *philo)
{
	sem_wait(philo->check);
	gettimeofday(&philo->last_time_to_eat, NULL);
	pprint(philo, "is eating");
	philo->n_eats += 1;
	if (philo->n_eats == philo->info->n_must_eat)
		sem_post(philo->info->n_eat_finish_philo);
	usleep(philo->info->time_to_eat * 1000);
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
	sem_post(philo->check);
}

static void	sleeping(t_philo *philo)
{
	pprint(philo, "is sleeping");
	usleep(philo->info->time_to_sleep * 1000);
}

static void	thinking(t_philo *philo)
{
	pprint(philo, "is thinking");
}

void	philo(t_philo *philo)
{
	pthread_t	thread;

	pthread_create(&thread, NULL, monitor, philo);
	if (philo->n % 2 == 0)
		usleep(philo->info->time_to_eat * 1000);
	while (1)
	{
		pickup_fork(philo);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	exit(0);
}
