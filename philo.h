/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuerliu <yuerliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:27:01 by yuerliu           #+#    #+#             */
/*   Updated: 2025/07/16 21:52:54 by yuerliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_philop
{
	int				id;
	int				eat_count;
	int				fork;
	int	full;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_t		thread;
	size_t			last_time_eat;
	struct s_table	*table;
}					t_philop;

//for other purpose maybe
typedef struct s_list
{
	void			*now;
	struct s_list	*front;
}					t_list;

typedef struct s_table
{
	int				head;
	size_t			start_time;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				min_times_to_eat;
	bool			someone_died;
	t_list			*garbabe_location;
	pthread_mutex_t	death;
	pthread_mutex_t	*forks;
	pthread_mutex_t	p_lock;
	t_philop		*philop;
}					t_table;
