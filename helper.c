/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:19:56 by moer-ret          #+#    #+#             */
/*   Updated: 2024/08/11 12:37:36 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}

void	ft_print(t_philo *philo, char *s, int flag)
{
	pthread_mutex_lock(philo->d_philo->msg);
	if (philo->d_philo->dead == 1)
	{
		pthread_mutex_unlock(philo->d_philo->msg);
		return ;
	}
	printf("%ld %d %s\n", \
		timer() - philo->d_philo->start_time, philo->id, s);
	pthread_mutex_unlock(philo->d_philo->msg);
	if (flag == 1)
	{
		if (philo->d_philo->n_of_philo && \
		(philo->d_philo->time_to_sleep <= philo->d_philo->time_to_eat))
			usleep((philo->d_philo->time_to_eat * 2) \
			- philo->d_philo->time_to_sleep);
	}
}

int	timing(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(data->tour);
	if (data->stop / data->n_of_meals == data->n_of_philo)
		i = 1;
	pthread_mutex_unlock(data->tour);
	if (i == 1)
		return (0);
	return (1);
}

int	its_time_to_die(t_philo philo)
{
	if (((timer() - philo.d_philo->start_time) - philo.tmp) \
		>= philo.d_philo->time_to_die)
		return (0);
	return (1);
}
