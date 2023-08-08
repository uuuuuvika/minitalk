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

#include <string.h>

#include <signal.h>
#include <limits.h>
#include <unistd.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>



typedef struct {
	char	byte;
	char	num_bit;
	int		pid;
	int		bytes_recived;
	char	*buffer;
}	t_client;


#endif