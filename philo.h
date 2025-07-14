/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuerliu <yuerliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:27:01 by yuerliu           #+#    #+#             */
/*   Updated: 2025/07/14 03:04:31 by yuerliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_philop
{
	int				id;
	int				eat_count;
	int				fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_t		thread;
	long			last_time_eat;
}					t_philop;

//for other purpose maybe
typedef struct s_list
{
	void			*now;
	struct s_list	*next;
}					t_list;

typedef struct s_table
{
	int				head;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				think_time;
	int				min_time_to_eat;
	t_list			*garbabe_location;
	pthread_mutex_t	*forks;
	t_philop		*philop;
}					t_table;
