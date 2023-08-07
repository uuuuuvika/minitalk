#ifndef MINITALK_H_
# define MINITALK_H_

# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"
# define RESET "\033[0m"

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

typedef struct {
	 pid_t server_pid;
    pid_t client_pid;
    char* message;
} t_info;

#endif