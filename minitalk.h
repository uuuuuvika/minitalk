#ifndef MINITALK_H_
# define MINITALK_H_

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include "colors.h"


typedef struct s_info{
	pid_t 	server_pid;
	pid_t 	client_pid;
	char	*message;
} t_info;


void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);

#endif