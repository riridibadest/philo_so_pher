/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuerliu <yuerliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:19:44 by yuerliu           #+#    #+#             */
/*   Updated: 2025/07/22 22:52:08 by yuerliu          ###   ########.fr       */
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
	size_t	id;
	bool	state;
	// FIX: Declare two pointers for the forks to enforce a specific lock order
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	id = pp->id;
	if (pp->table->head == 1)
		solo_eating(pp);
	
	// The original usleep(100) is removed as it does not prevent deadlock.
	
	pthread_mutex_lock(&pp->table->death);
	state = pp->table->someone_died;
	pthread_mutex_unlock(&pp->table->death);
	if (state)
		return ;

	// --- DEADLOCK FIX: ASYMMETRIC LOCKING ---
	// Philosophers with an EVEN ID (2, 4, ...) lock the RIGHT fork first.
	// Philosophers with an ODD ID (1, 3, 5, ...) lock the LEFT fork first.
	if ((pp->id % 2) == 0) 
	{ 
		first = pp->r_fork; 
		second = pp->l_fork; 
	} 
	else 
	{ 
		first = pp->l_fork; 
		second = pp->r_fork; 
	}

	pthread_mutex_lock(first);
	o_print(pp, 1, id); // Log the first fork pickup

	pthread_mutex_lock(second);
	o_print(pp, 1, id); // Log the second fork pickup
	// --- END OF FIX ---

	o_print(pp, 2, id);
	pp->last_time_eat = get_time_ms();
	pp->eat_count++;
	if (pp->eat_count == pp->table->min_times_to_eat)
		pp->full = 1;
	smart_rest(pp, pp->table->eat_time);

	// Unlock in the reverse order of locking (second then first)
	pthread_mutex_unlock(second);
	pthread_mutex_unlock(first);
}

void	p_sleep(t_philop *pp)
{
	bool	state;

	pthread_mutex_lock(&pp->table->death);
	state = pp->table->someone_died;
	pthread_mutex_unlock(&pp->table->death);
	if (state)
		return ;
	if (pp->full == 1)
		return ;
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
	if (pp->full == 1)
		return ;
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
