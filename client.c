/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctete <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 03:48:30 by ctete             #+#    #+#             */
/*   Updated: 2024/07/29 05:06:49 by ctete            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include<signal.h>
#include<stdlib.h>

int	ft_atoi(char *str)
{
	int	sinal;
	int	resultado;

	sinal = 1;
	resultado = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sinal = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
		resultado = resultado * 10 + *str++ - '0';
	return (sinal * resultado);
}

void	send_bits(int pid_server, unsigned char c)
{
	int	i;

	i = 0;
	while (i <= 7)
	{
		if (c << i & 0b10000000)
			kill(pid_server, SIGUSR1);
		else
			kill(pid_server, SIGUSR2);
		usleep(9000);
		i++;
	}
}

int	main(int argc, char **argv)
{
	int	i;
	int	pid;

	if (argc == 3)
	{
		i = 0;
		pid = ft_atoi(argv[1]);
		while (argv[2][i] != '\0')
		{
			send_bits(pid, argv[2][i]);
			i++;
		}
	}
	else
		write(1, "\033[90m dados inválidos cadete...\033[0m\n", 38);
	return (0);
}
