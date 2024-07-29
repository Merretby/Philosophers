/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:38:54 by moer-ret          #+#    #+#             */
/*   Updated: 2024/07/29 15:34:32 by user             ###   ########.fr       */
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
	int				id;
	int				left_fork;
	int				right_fork;
	long int		start;
	long int		tmp;
	pthread_t		th;
	struct s_data	*d_philo;
}	t_philo;

typedef struct s_data
{
	int				stop;
	int				n_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_of_meals;
	long int		start_time;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*msg;
	pthread_mutex_t	*tour;
}	t_data;

//parsing
long		ft_atoi(const char *str);
void		ft_putendl_fd(char *s, int fd);
void		parsing(int ac, char **av);

//init
void		init_data(int ac, char **av, t_data *data);
long int	timer(void);
void		ft_usleep(int time);

#endif