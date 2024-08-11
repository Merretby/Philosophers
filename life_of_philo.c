/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_of_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:23:08 by moer-ret          #+#    #+#             */
/*   Updated: 2024/08/11 14:48:03 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	help_philo(t_data *data)
{
	int			i;
	pthread_t	mounitor;

	pthread_create(&mounitor, NULL, &the_tabel, data);
	i = 0;
	while (i < data->n_of_philo)
	{
		if (pthread_join(data->philo[i].th, NULL) == -1)
			ft_putendl_fd("error in pthread_join", 2);
		i++;
	}
	if (pthread_join(mounitor, NULL) == -1)
		ft_putendl_fd("error in pthread_join", 2);
}

static void	take_fork_and_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->d_philo->forks[philo->left_fork]);
	ft_print(philo, "has taken a fork", 0);
	pthread_mutex_lock(&philo->d_philo->forks[philo->right_fork]);
	ft_print(philo, "has taken a fork", 0);
	ft_print(philo, "is eating", 0);
	philo->tmp = timer() - philo->d_philo->start_time;
	pthread_mutex_lock(philo->d_philo->tour);
	if (philo->d_philo->n_of_meals != -1)
		philo->d_philo->stop += 1;
	pthread_mutex_unlock(philo->d_philo->tour);
	ft_usleep(philo->d_philo->time_to_eat);
	pthread_mutex_unlock(&philo->d_philo->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->d_philo->forks[philo->right_fork]);
}

static void	take_fork_and_eat_odd(t_philo *philo)
{
	usleep(500);
	pthread_mutex_lock(&philo->d_philo->forks[philo->left_fork]);
	ft_print(philo, "has taken a fork", 0);
	pthread_mutex_lock(&philo->d_philo->forks[philo->right_fork]);
	ft_print(philo, "has taken a fork", 0);
	ft_print(philo, "is eating", 0);
	philo->tmp = timer() - philo->d_philo->start_time;
	pthread_mutex_lock(philo->d_philo->tour);
	if (philo->d_philo->n_of_meals != -1)
		philo->d_philo->stop += 1;
	pthread_mutex_unlock(philo->d_philo->tour);
	ft_usleep(philo->d_philo->time_to_eat);
	pthread_mutex_unlock(&philo->d_philo->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->d_philo->forks[philo->right_fork]);
}

void	*diner(void *data_of_philo)
{
	t_philo	*philo;

	philo = (t_philo *)data_of_philo;
	while (1)
	{
		pthread_mutex_lock(philo->d_philo->dead_mutex);
		if (philo->d_philo->dead == 1)
		{
			pthread_mutex_unlock(philo->d_philo->dead_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(philo->d_philo->dead_mutex);
		if (philo->id % 2 == 0)
			take_fork_and_eat(philo);
		else
			take_fork_and_eat_odd(philo);
		ft_print(philo, "is sleeping", 0);
		ft_usleep(philo->d_philo->time_to_sleep);
		ft_print(philo, "is thinking", 1);
	}
	return (NULL);
}
