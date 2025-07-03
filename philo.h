/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuerliu <yuerliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:27:01 by yuerliu           #+#    #+#             */
/*   Updated: 2025/07/01 18:49:05 by yuerliu          ###   ########.fr       */
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
	pthread_t		thread;
	long			last_time_eat;
}					t_philop;

typedef struct s_list
{
	void			*now;
	struct s_list	*next;
}	t_list;


typedef struct s_table
{
	int				head;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				think_time;
	int				min_time_to_eat;
	pthread_mutex_t	fork_left;
	pthread_mutex_t	fork_right;
	t_philop		*philop;
}					t_table;
