/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:38:54 by moer-ret          #+#    #+#             */
/*   Updated: 2024/07/22 12:26:27 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
#include <sys/time.h>
// # include <fcntl.h>

typedef struct s_philo
{
	int			id;
	int			n_of_meals;
	int			left_fork;
	int			right_fork;
	int			dead_flag;
	size_t		last_meal;
	pthread_t	thread;
}	t_philo;

typedef struct s_forks
{
	pthread_mutex_t	fork_mutex;
	int				id;
}	t_forks;

typedef struct s_data
{
	int		n_of_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		n_of_meals;
	int		dead_flag;
	size_t	start_time;
	t_philo	*philo;
	t_forks	*forks;
}	t_data;

//parsing
long	ft_atoi(const char *str);
void	ft_putendl_fd(char *s, int fd);
void	parsing(int ac, char **av);

//init
void	init_data(int ac, char **av, t_data *data);

#endif