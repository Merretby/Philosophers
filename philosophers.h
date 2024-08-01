/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moer-ret <moer-ret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 20:38:54 by moer-ret          #+#    #+#             */
/*   Updated: 2024/08/01 13:34:07 by moer-ret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>
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
	int				dead;
	t_philo			*philo;
	pthread_mutex_t	*dead_mutex;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*msg;
	pthread_mutex_t	*tour;
}	t_data;

//parsing
long		ft_atoi(const char *str);
void		ft_putendl_fd(char *s, int fd);
void		parsing(int ac, char **av);
int			ft_isdigit(int c);

//philo
void		init_data(int ac, char **av, t_data *data);
void		*the_tabel(void *d);
void		*diner(void *data_of_philo);
void		help_philo(t_data *data);
long int	timer(void);
void		ft_usleep(int time);
void		desrtoy(t_data *data);
int			timing(t_data *data);
int			its_time_to_die(t_philo philo);
void		ft_print(t_philo *philo, char *s);

#endif