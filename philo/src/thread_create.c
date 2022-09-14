/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yogun <yogun@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 13:26:43 by yogun             #+#    #+#             */
/*   Updated: 2022/09/14 13:28:13 by yogun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_thread_sub(t_info *data)
{
	if (*data->die)
		return ;
	pthread_mutex_lock(data->fork_r);
	ft_printf("has taken a fork", data);
	if (*data->die)
	{
		pthread_mutex_unlock(data->fork_r);
		return ;
	}
	pthread_mutex_lock(data->fork_l);
	ft_printf("has taken a fork", data);
	if (gettimeofday(data->last_eat, 0))
		return ;
	if (*data->die)
	{
		pthread_mutex_unlock(data->fork_l);
		pthread_mutex_unlock(data->fork_r);
		return ;
	}
	ft_printf("is eating", data);
	ft_sleep(data->t2e);
	pthread_mutex_unlock(data->fork_l);
	pthread_mutex_unlock(data->fork_r);
}

void	ft_thread_t2em(t_info *data)
{
	while (data->t2em)
	{
		ft_thread_sub(data);
		if (*data->die)
			return ;
		data->t2em--;
		if (data->t2em == 0)
		{
			pthread_mutex_lock(data->done_eat);
			*data->done += 1;
			pthread_mutex_unlock(data->done_eat);
			return ;
		}
		ft_printf("is sleeping", data);
		ft_sleep(data->t2s);
		ft_printf("is thinking", data);
	}
}

void	ft_thread_infinite(t_info *data)
{
	while (*data->die == 0)
	{
		ft_thread_sub(data);
		ft_printf("is sleeping", data);
		if (*data->die)
			return ;
		ft_sleep(data->t2s);
		ft_printf("is thinking", data);
	}
}

void	ft_thread(t_info *data)
{
	if (data->philo_N % 2 != 0)
		usleep(data->t2e * 100);
	if (data->t2em)
		ft_thread_t2em(data);
	else
		ft_thread_infinite(data);
}