/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters_getters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsanz-su <vsanz-su@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:31:56 by vsanz-su          #+#    #+#             */
/*   Updated: 2024/05/15 11:31:57 by vsanz-su         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	get_bool(t_mtx *mtx, bool *value)
{
	bool	res;

	safe_lock_handle(mtx, LOCK);
	res = *value;
	safe_lock_handle(mtx, UNLOCK);
	return (res);
}

void	set_bool(t_mtx *mtx, bool *dest, bool value)
{
	safe_lock_handle(mtx, LOCK);
	*dest = value;
	safe_lock_handle(mtx, UNLOCK);
}

void	set_long(t_mtx *mutex, size_t *dest, size_t value)
{
	safe_lock_handle(mutex, LOCK);
	*dest = value;
	safe_lock_handle(mutex, UNLOCK);
}

size_t	get_long(t_mtx *mutex, size_t *value)
{
	size_t	ret;

	safe_lock_handle(mutex, LOCK);
	ret = *value;
	safe_lock_handle(mutex, UNLOCK);
	return (ret);
}
