/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuerliu <yuerliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:33:31 by yuerliu           #+#    #+#             */
/*   Updated: 2025/07/14 03:13:14 by yuerliu          ###   ########.fr       */
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
	if (elements->now == NULL)
		elements->now = pt;
	else
	{
		elements->next = pt;
		elements = elements->next;
	}
		return (pt);
}

