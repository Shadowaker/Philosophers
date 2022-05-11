/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 20:14:32 by dridolfo          #+#    #+#             */
/*   Updated: 2022/05/11 12:49:02 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				n;
	int				n_eats;
	char			*name;
	sem_t			*check;
	pid_t			pid;
	struct s_env	*info;
	struct timeval	last_time_to_eat;

}					t_philo;

typedef struct s_env
{
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_must_eat;
	sem_t			*acting;
	sem_t			*n_eat_finish_philo;
	sem_t			*end;
	sem_t			*forks;
	t_philo			*philos;
	struct timeval	born_time;
}			t_env;

int			init(t_env *env, int argc, char *argv[]);
void		philo(t_philo *philo);
void		*monitor(void *argv);
void		*finish_monitor(void *arg);
void		*monitor_each_must_eat(void *argv);

char		*name_process(char *name, int n);
int			ft_atoi(char *nptr);
int			ft_mallocchino(void *dst, size_t size);
long long	time_to_ms(struct timeval now);
void		log_(t_philo *philo, char *str);
void		pprint(t_philo *philo, char *str);
int			ft_error_handler(char *str);

#endif
