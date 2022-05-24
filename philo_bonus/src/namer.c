/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   namer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dridolfo <dridolfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 20:17:39 by dridolfo          #+#    #+#             */
/*   Updated: 2022/05/24 16:18:59 by dridolfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/philo.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (*str++)
		++i;
	return (i);
}

long long	time_to_ms(struct timeval now)
{
	long long		ms;

	ms = now.tv_sec * 1000;
	ms += now.tv_usec / 1000;
	return (ms);
}

void	pprint(t_philo *philo, char *str)
{
	long long		ms;
	struct timeval	now;

	sem_wait(philo->info->acting);
	gettimeofday(&now, NULL);
	ms = time_to_ms(now) - time_to_ms(philo->info->born_time);
	printf("%lld\t%d\t %s\n", ms, philo->n + 1, str);
	sem_post(philo->info->acting);
}

char	*name_process(char *name, int n)
{
	char	*result;
	int		num;
	int		i;

	i = 0;
	num = n;
	while (num)
	{
		num /= 10;
		++i;
	}
	result = malloc(sizeof(char) * (i + ft_strlen(name) + 1));
	if (result == NULL)
		return (NULL);
	num = -1;
	while (++num < i)
		result[num] = name[num];
	while (n)
	{
		result[i++] = n % 10 + '0';
		n /= 10;
	}
	result[i] = 0;
	return (result);
}
