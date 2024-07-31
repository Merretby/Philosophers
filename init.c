/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 18:19:25 by moer-ret          #+#    #+#             */
/*   Updated: 2024/07/31 16:59:10 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_print(t_philo *philo, char *s)
{
	pthread_mutex_lock(philo->d_philo->msg);
	if (philo->d_philo->dead == 1)
	{
		pthread_mutex_unlock(philo->d_philo->msg);
		return ;
	}
	printf("%ld philo %d %s\n", timer() - philo->d_philo->start_time, philo->id, s);
	pthread_mutex_unlock(philo->d_philo->msg);
}

void	take_fork_and_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->d_philo->forks[philo->left_fork]);
	ft_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->d_philo->forks[philo->right_fork]);
	ft_print(philo, "has taken a fork");
	ft_print(philo, "is eating");
	philo->tmp = timer() - philo->d_philo->start_time;
	pthread_mutex_lock(philo->d_philo->tour);
	if (philo->d_philo->n_of_meals != -1)
		philo->d_philo->stop += 1;
	pthread_mutex_unlock(philo->d_philo->tour);
	ft_usleep(philo->d_philo->time_to_eat);
	pthread_mutex_unlock(&philo->d_philo->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->d_philo->forks[philo->right_fork]);
}

void	take_fork_and_eat_odd(t_philo *philo)
{
	usleep(500);
	pthread_mutex_lock(&philo->d_philo->forks[philo->right_fork]);
	ft_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->d_philo->forks[philo->left_fork]);
	ft_print(philo, "has taken a fork");
	ft_print(philo, "is eating");
	philo->tmp = timer() - philo->d_philo->start_time;
	pthread_mutex_lock(philo->d_philo->tour);
	if (philo->d_philo->n_of_meals != -1)
		philo->d_philo->stop += 1;
	pthread_mutex_unlock(philo->d_philo->tour);
	ft_usleep(philo->d_philo->time_to_eat);
	pthread_mutex_unlock(&philo->d_philo->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->d_philo->forks[philo->left_fork]);
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
			return NULL;
		}
		pthread_mutex_unlock(philo->d_philo->dead_mutex);
		if (philo->id % 2 == 0)
			take_fork_and_eat(philo);
		else
			take_fork_and_eat_odd(philo);
		ft_print(philo, "is sleeping");
		ft_usleep(philo->d_philo->time_to_sleep);
		ft_print(philo, "is thinking");
	}
	return (NULL);
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

void	*the_tabel(void *d)
{
	int	i;
	t_data	*data;

	data = (t_data *)d;
	i = 0;
	while (1)
	{
		if (data->n_of_meals != -1 && timing(data) == 0)
		{
			pthread_mutex_lock(data->msg);
			pthread_mutex_lock(data->dead_mutex);
			data->dead = 1;
			pthread_mutex_unlock(data->dead_mutex);
			pthread_mutex_unlock(data->msg);
			return NULL;
		}
		if (!its_time_to_die(data->philo[i]))
		{
			pthread_mutex_lock(data->msg);
			printf("%ld philo %d died\n", \
				timer() - data->start_time, data->philo[i].id);
			pthread_mutex_lock(data->dead_mutex);
			data->dead = 1;
			pthread_mutex_unlock(data->dead_mutex);
			pthread_mutex_unlock(data->msg);
			return NULL;
		}
		i++;
		if (i == data->n_of_philo)
			i = 0;
	}
	return (NULL);
}

void	init_philo2(t_data *data)
{
	int	i;
	pthread_t 		mounitor;

	i = 0;
	data->start_time = timer();
	while (i < data->n_of_philo)
	{
		data->philo[i].id = i + 1;
		if (i == data->n_of_philo - 1)
		{
			data->philo[i].right_fork = i;
			data->philo[i].left_fork = (i + 1) % data->n_of_philo;
		}
		else
		{
			data->philo[i].left_fork = i;
			data->philo[i].right_fork = (i + 1) % data->n_of_philo;
		}
		data->philo[i].start = timer();
		data->philo[i].d_philo = data;
		pthread_create(&data->philo[i].th, NULL, &diner, &data->philo[i]);\
		i++;
		usleep(60);
	}
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

void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_data) * data->n_of_philo);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_of_philo);
	data->msg = malloc(sizeof(pthread_mutex_t));
	data->tour = malloc(sizeof(pthread_mutex_t));
	data->dead_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->dead_mutex, NULL);
	pthread_mutex_init(data->msg, NULL);
	pthread_mutex_init(data->tour, NULL);
	while (i < data->n_of_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	init_philo2(data);
	i = 0;
	while (i < data->n_of_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(data->dead_mutex);
	pthread_mutex_destroy(data->msg);
	pthread_mutex_destroy(data->tour);
	free(data->philo);
	free(data->forks);
	free(data->msg);
	free(data->tour);
}

void	init_data(int ac, char **av, t_data *data)
{
	data->n_of_philo = ft_atoi(av[1]);
	if (data->n_of_philo == 0)
		ft_putendl_fd("number of philosophers must be greater than 0", 2);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		data->n_of_meals = ft_atoi(av[5]);
		if (data->n_of_meals == 0)
			ft_putendl_fd("number of meals must be greater than 0", 2);
	}
	else
		data->n_of_meals = -1;
	data->stop = 0;
	data->dead = 0;
	if (data->n_of_philo == 1)
	{
		printf("0 philo 1 has taken a fork\n");
		ft_usleep(data->time_to_die);
		printf("%d philo 1 died\n", ++data->time_to_die);
		return ;
	}
	init_philo(data);
}
