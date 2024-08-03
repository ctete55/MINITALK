/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctete <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 04:38:10 by ctete             #+#    #+#             */
/*   Updated: 2024/07/29 05:04:41 by ctete            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include<signal.h>
#include<string.h>

void	print_number(int num)
{
	char	*str;

	str = "0123456789";
	if (num > 9)
		print_number(num / 10);
	write(1, &str[num % 10], 1);
}

void	ft_to_receve(int signal)
{
	static int				i;
	static unsigned char	bit;

	if (signal == SIGUSR2)
		bit = (bit << 1);
	else if (signal == SIGUSR1)
		bit = (bit << 1) | 0b00000001;
	i++;
	if (i == 8)
	{
		write(1, &bit, 1);
		bit = 0;
		i = 0;
	}
}

int	main(void)
{
	int	pid;

	pid = getpid();
	write(1, "PID ", 4);
	print_number(pid);
	write(1, "\n", 1);
	while (1)
	{	
		signal(SIGUSR1, ft_to_receve);
		signal(SIGUSR2, ft_to_receve);
	}
	return (0);
}
