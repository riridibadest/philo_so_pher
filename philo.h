/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuerliu <yuerliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:27:01 by yuerliu           #+#    #+#             */
/*   Updated: 2025/07/19 17:13:26 by yuerliu          ###   ########.fr       */
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
	int				full;
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
	size_t			die_time;
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

void				eat(t_philop *pp);
void				p_sleep(t_philop *pp);
void				thinking(t_philop *pp);
void				solo_eating(t_philop *pp);
t_table				read_input(int ac, char **av);
void				init_philop(t_table *pimp);
void				make_philops(t_table *pp);
t_table				make_table(int ac, char **av);
void				make_philops(t_table *pp);
void				init_philop(t_table *pimp);
t_table				read_input(int ac, char **av);
void				clean_up(t_list *garbabe);
int					ok_input(int ac, char **av);
int					ft_isdigit(int num);
int					zero(int ac, char **av);
t_list				*malloc_table_sth(size_t size);
size_t				get_time_ms(void);
size_t				eat_gap(t_table *pp, int id);
void				o_print(t_table *pp, int i, int id);
int					feast_time(t_table *pp);
void				*life_of_philop(void *pp);
void				*dead_yet(void *pp);
int					we_r_full(t_table *pp);