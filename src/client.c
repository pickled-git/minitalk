/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oprosvir <oprosvir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 23:01:49 by oprosvir          #+#    #+#             */
/*   Updated: 2024/03/04 17:08:28 by oprosvir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/include/libft.h"
#include "minitalk.h"

void	send_char(int server_pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if (c & (1 << bit))
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		usleep(500);
		bit++;
	}
}

int	main(int argc, char *argv[])
{
	int		server_pid;
	char	*msg;

	if (argc != 3)
	{
		ft_printf("Usage: ./client [Server PID] [String to send]\n");
		exit(EXIT_FAILURE);
	}
	server_pid = ft_atoi(argv[1]);
	if (kill(server_pid, 0) < 0)
	{
		ft_printf("ERROR: Failed to send signal to PID: %d\n", server_pid);
		exit(EXIT_FAILURE);
	}
	msg = argv[2];
	while (*msg)
	{
		send_char(server_pid, *msg);
		msg++;
	}
	return (0);
}
