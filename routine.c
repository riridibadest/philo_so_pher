/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuerliu <yuerliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:19:44 by yuerliu           #+#    #+#             */
/*   Updated: 2025/10/29 20:50:24 by yuerliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	eat(t_philop *pp)
// {
// 	size_t	id;
// 	bool	state;
// 	// pthread_mutex_t	*first;
// 	// pthread_mutex_t	*second;

// 	id = pp->id;
// 	if (pp->table->head == 1)
// 		solo_eating(pp);
// 	// if ((pp->table->head % 2) == 0)
// 	if ((id % 2) == 1)
// 		usleep(100);
// 	// else
// 	// {
// 	// 	if ((id % 2) == 1)
// 	// 		usleep(id * 10);
// 	// }
// 	pthread_mutex_lock(&pp->table->death);
// 	state = pp->table->someone_died;
// 	pthread_mutex_unlock(&pp->table->death);
// 	if (state)
// 		return ;
// 	// if ((pp->id % 2) == 0)
// 	// {
// 	// 	first = pp->l_fork;
// 	// 	second = pp->r_fork;
// 	// }
// 	// else
// 	// {
// 	// 	first = pp->r_fork;
// 	// 	second = pp->l_fork;
// 	// }
// 	pthread_mutex_lock(pp->l_fork);
// 	o_print(pp, 1, id);
// 	pthread_mutex_lock(pp->r_fork);
// 	o_print(pp, 1, id);
// 	o_print(pp, 2, id);
// 	pp->last_time_eat = get_time_ms();
// 	pp->eat_count++;
// 	if (pp->eat_count == pp->table->min_times_to_eat)
// 		pp->full = 1;
// 	smart_rest(pp, pp->table->eat_time);
// 	// Fix: Unlock in reverse order of locking
// 	pthread_mutex_unlock(pp->r_fork);
// 	pthread_mutex_unlock(pp->l_fork);
// }

void	eat(t_philop *pp)
{
	size_t			id;
	bool			state;
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	id = pp->id;
	if (pp->table->head == 1)
		solo_eating(pp);
	state = check_death(pp);
	if (state)
		return ;
	first = &pp->table->forks[(id - 1 + pp->table->head) % pp->table->head];
	second = &pp->table->forks[id % pp->table->head];
	if (take_forks(first, second, pp) == 1)
		return ;
	o_print(pp, 2, id);
	smart_rest(pp, pp->table->eat_time);
	pthread_mutex_lock(&pp->eatime);
	pp->last_time_eat = get_time_ms();
	pp->eat_count++;
	if (pp->eat_count == pp->table->min_times_to_eat)
		pp->full = 1;
	pthread_mutex_unlock(&pp->eatime);
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
}

int	take_forks(pthread_mutex_t *first, pthread_mutex_t *second, t_philop *pp)
{
	size_t	id;
	bool	state;

	id = pp->id;
	pthread_mutex_lock(first);
	pthread_mutex_lock(second);
	state = check_death(pp);
	if (state)
		return (1);
	o_print(pp, 1, id);
	o_print(pp, 1, id);
	return (0);
}

void	p_sleep(t_philop *pp)
{
	bool	state;

	pthread_mutex_lock(&pp->table->death);
	state = pp->table->someone_died;
	pthread_mutex_unlock(&pp->table->death);
	if (state)
		return ;
	pthread_mutex_lock(&pp->eatime);
	if (pp->full == 1)
	{
		pthread_mutex_unlock(&pp->eatime);
		return ;
	}
	pthread_mutex_unlock(&pp->eatime);
	o_print(pp, 3, pp->id);
	smart_rest(pp, pp->table->sleep_time);
}

void	thinking(t_philop *pp)
{
	bool	state;

	pthread_mutex_lock(&pp->table->death);
	state = pp->table->someone_died;
	pthread_mutex_unlock(&pp->table->death);
	if (state)
		return ;
	pthread_mutex_lock(&pp->eatime);
	if (pp->full == 1)
	{
		pthread_mutex_unlock(&pp->eatime);
		return ;
	}
	pthread_mutex_unlock(&pp->eatime);
	o_print(pp, 4, pp->id);
}

void	solo_eating(t_philop *pp)
{
	int	id;

	id = pp->id;
	pthread_mutex_lock(pp->r_fork);
	o_print(pp, 1, id);
	smart_rest(pp, pp->table->die_time);
	pthread_mutex_unlock(pp->r_fork);
	pthread_mutex_lock(&pp->table->death);
	pp->table->someone_died = true;
	pthread_mutex_unlock(&pp->table->death);
}
