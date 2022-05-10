/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 13:44:05 by dridolfo          #+#    #+#             */
/*   Updated: 2022/05/10 20:04:29 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

long	time_to_ms(struct timeval now)
{
	return (now.tv_sec * ((u_int64_t) 1000) + ((u_int64_t) now.tv_usec / 1000));
}

void	log_(t_philo *philo, char *str)
{
	long			ms;
	struct timeval	now;

	pthread_mutex_lock(&philo->env->mutex_);
	gettimeofday(&now, NULL);
	ms = time_to_ms(now) - time_to_ms(philo->env->born_time);
	if (!philo->env->end)
		printf("%ld\t%d\t %s\n", ms, philo->n + 1, str);
	pthread_mutex_unlock(&philo->env->mutex_);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	else
	{
		while (s1[i] == s2[i] && i < n - 1)
		{
			if (s1[i] == '\0' || s2[i] == '\0')
				break ;
			i++;
		}
	}
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}

int	ft_atoi(char *str)
{
	int	i;
	int	r;
	int	s;

	i = 0;
	r = 0;
	s = 1;
	if (ft_strncmp("-2147483648", str, 12) == 0)
		return (-2147483648);
	while (str[i] != '\0' && ((str[i] > 8 && 14 > str[i]) || str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while (str[i] != '\0' && (str[i] > 47 && str[i] < 58))
	{
		r *= 10;
		r += (str[i] - 48);
		i++;
	}
	return (r * s);
}

int	ft_error_handler(int error)
{
	if (error == 1)
		printf("\033[91mError.\nInvalid argument passed.\033[0m");
	else if (error == 2)
		printf("\033[91mError.\nThere are no philosophers to simulate.\033[0m");
	else if (error == 3)
		printf("\033[91mError.\nNot enough space.\033[0m");
	else if (error == 4)
		printf("\033[91mError.\nWrong number of parameters passed.\033[0m");
	return (0);
}
