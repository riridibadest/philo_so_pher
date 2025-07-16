/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuerliu <yuerliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:33:31 by yuerliu           #+#    #+#             */
/*   Updated: 2025/07/16 22:01:06 by yuerliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//here i malloc memory for storing things for content of a struct, and
//create a list that technically store the same struct and return pointer at
// end of list

t_list	*malloc_table_sth(size_t size, t_table *pp)
{
	void	*pt;
	t_list	*elements;

	pt = malloc(size);
	if (!pt)
		return (NULL);
	elements = malloc(sizeof(t_list));
	if (!elements)
	{
		free(pt);
		return (NULL);
	}
	elements->now = pt;
	elements->front = pp->garbabe_location;
	pp->garbabe_location = elements;
	return (pt);
}

size_t	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000L) + (time.tv_usec / 1000));
}

size_t	eat_gap(t_table *pp, int id)
{
	size_t	now;
	size_t	hunger_time;

	now = get_time_ms();
	hunger_time = pp->philop[id].last_time_eat - now;
	return (hunger_time);
}
//1 = takefork; 2 = eating; 3 = sleeping; 4 = thinking; 5 = died

void	o_print(t_table *pp, int i, int id)
{
	size_t	time;

	time = (get_time_ms() - pp->start_time);
	pthread_mutex_lock(&pp->p_lock);
	if (i = 1)
		printf("%d, %d has taken a fork\n", time, id);
	else if (i = 2)
		printf("%d, %d is eating\n", time, id);
	else if (i = 3)
		printf("%d, %d is sleeping\n", time, id);
	else if (i = 4)
		printf("%d, %d is thinking\n", time, id);
	else
		printf("%d, %d died\n", time, id);
	pthread_mutex_unlock(&pp->p_lock);
}
