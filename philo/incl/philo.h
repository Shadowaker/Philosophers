/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 21:41:53 by jaeskim           #+#    #+#             */
/*   Updated: 2022/04/13 19:27:10 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				n;
	int				n_eat;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	check_mutex;
	pthread_t		thread;
	struct s_env	*env;
	struct timeval	last_time_to_eat;

}					t_philo;

typedef struct s_env
{
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_philos_eat;
	int				n_must_eat;
	int				end;
	pthread_mutex_t	mutex_;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	struct timeval	born_time;
}			t_env;

int			init(int argc, char **argv, t_env *env);
void		*philo(void *argv);
void		*monitor(void *argv);
void		*monitor_each_must_eat(void *argv);

int			ft_atoi(char *str);
int			ft_error_handler(int error);
long long	time_to_ms(struct timeval now);
void		log_(t_philo *philo, char *str);

#endif
