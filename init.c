/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:19:25 by moer-ret          #+#    #+#             */
/*   Updated: 2024/07/22 12:35:37 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	printf("n_of_philo2: %d\n", data->n_of_philo);
	data->philo = malloc(sizeof(t_philo) * data->n_of_philo);
	while (i < data->n_of_philo)
	{
		data->philo[i].id = i;
		data->philo[i].n_of_meals = 0;
		data->philo[i].last_meal = 0;
		data->philo[i].dead_flag = 0;
		data->philo[i].left_fork = i;
		data->philo[i].right_fork = (i + 1) % data->n_of_philo;
		i++;
	}
}

void	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(t_forks) * data->n_of_philo);
	while (i < data->n_of_philo)
	{
		data->forks[i].id = i;
		pthread_mutex_init(&data->forks[i].fork_mutex, NULL);
		i++;
	}
}

void	init_data(int ac, char **av, t_data *data)
{
	int	i;

	i = 0;
	data->dead_flag = 0;
	data->n_of_philo = ft_atoi(av[1]);
	printf("n_of_philo11: %d\n", data->n_of_philo);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		data->n_of_meals = ft_atoi(av[5]);
		if (data->n_of_meals == 0)
			ft_putendl_fd("number of meals must be greater than 0", 2);
	else
		data->n_of_meals = -1;
	}
	init_forks(data);
	init_philo(data);
	free(data->philo);
	free(data->forks);
}
