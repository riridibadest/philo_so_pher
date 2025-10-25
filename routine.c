/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuerliu <yuerliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:19:44 by yuerliu           #+#    #+#             */
/*   Updated: 2025/10/26 00:51:39 by yuerliu          ###   ########.fr       */
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
	pthread_mutex_lock(&pp->table->death);
	state = pp->table->someone_died;
	pthread_mutex_unlock(&pp->table->death);
	if (state)
		return ;
	first = &pp->table->forks[(id - 1 + pp->table->head) % pp->table->head];
	second = &pp->table->forks[id % pp->table->head];
	pthread_mutex_lock(first);
	pthread_mutex_lock(second);
	o_print(pp, 1, id); // Log the first fork pickup

	o_print(pp, 1, id); // Log the second fork pickup
	// --- END OF FIX ---
	// if (id == 3)
	// 	printf("id: %zu, %d\n", id, pp[id - 1].fork);
	// if (id == 1){
	// 	printf("id: %zu, %d\n", id, pp[id - 1].fork);
	// 	printf("id: %zu, %d\n", id, pp[id - 1].fork + 1);
	// }
	// if (id == 2)
	// 	printf("id: %zu, %d\n", id, pp[id - 1].fork);
	o_print(pp, 2, id);
	smart_rest(pp, pp->table->eat_time);
	pthread_mutex_lock(&pp->eatime);
	pp->last_time_eat = get_time_ms();
	pp->eat_count++;
	if (pp->eat_count == pp->table->min_times_to_eat)
		pp->full = 1;
	pthread_mutex_unlock(&pp->eatime);
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
