#include "minitalk.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

char	*strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		lens1;
	int		lens2;

	lens1 = strlen(s1);
	lens2 = strlen(s2);
	ptr = malloc (sizeof(char) * (lens1 + lens2 + 1));
	if (!ptr)
		return (NULL);
	strlcpy(ptr, s1, lens1 + 1);
	strlcat(ptr, s2, lens1 + lens2 + 1);
	return (ptr);
}

typedef struct s_client{
	char	byte;
	char	num_bit;
	int		pid;
	int		bytes_recived;
	char	*buffer;
}	t_client;

	/* 
	Sigaction is a struct describing a signal handler. It contains:
		- A signal handler function
		- A signal mask which specifies which signals should be blocked
		 while the signal handler function is running. If the signal
		 handler returns normally, the original signal mask will be
		 restored. To understand signal masks, see sigprocmask.c
		- A set of flags.
	
	Specify the signal handler function to be called when one of
	the specified signals occur.

		>> signal.sa_sigaction = signal_recived;

	Add all of the signals to the signal mask set. This means that
	all signals will be blocked (i.e., delayed) while our signal
	handler function is running. The original signal mask will be
	restored when our signal handler exits normally.
	
		>> sigfillset(&signal.sa_mask);

 	If the signal handler gets run in the middle of some function
	calls (such as open(), read(), or write()) and the signal
	handler returns normally, there are couple of options: return a
	failure code EINTR from those functions, or try to resume the
	function. With SA_RESTART, the function is resumed instead of
	returning an error. 
	
		>> signal.sa_flags = SA_RESTART;

	*/

void	print_msj(int bytes_recived, int pid, char *msj)
{
	printf("\n%s\n", msj);
	printf("\n\n 📟 Message finished from PID[%d]\n", pid);
	printf(" 🔸 %d bytes recived\n\n", bytes_recived);
}

void	reset_client(t_client *client, int pid)
{
	printf("\n\n 📥 Starting new message from PID [%d]\n\n", pid);
	client->pid = pid;
	client->num_bit = 0;
	client->bytes_recived = 0;
	free(client->buffer);
	client->buffer = NULL;
	client->buffer = strdup("");
}

void	new_byte(t_client *client)
{
	char	*tmp;
	char	str_byte[2];

	str_byte[0] = client->byte;
	str_byte[1] = '\0';
	tmp = strjoin(client->buffer, str_byte);
	free (client->buffer);
	client->buffer = tmp;
	client->bytes_recived++;
	if (client->byte == 0)
	{
		print_msj(client->bytes_recived, client->pid, client->buffer);
		free(client->buffer);
		client->buffer = NULL;
	}
	else
		printf("\r\e[1;34mReceiving [%d] bytes\e[0m", client->bytes_recived);
	client->byte = 0;
	client->num_bit = 0;
}


void	signal_recived(int sig, siginfo_t *si, void *uap)
{
	static t_client	client;

	(void)si;
	(void)uap;
	if (client.pid != si->si_pid && si->si_pid != 0)
		reset_client (&client, si->si_pid);
        
	client.byte |= (sig == SIGUSR2);
	if (++client.num_bit == 8)
		new_byte(&client);
	else
		client.byte <<= 1;
	usleep(60);
	kill (client.pid, SIGUSR1);
}


int	main(void)
{
	struct sigaction	signal;

	signal.sa_sigaction = signal_recived;
	signal.sa_flags = SA_RESTART;
	sigaction(SIGUSR2, &signal, NULL);
	sigaction(SIGUSR1, &signal, NULL);
	printf("\nServer PID [%d]\n\n", getpid());
	while (1)
	{
		pause();
	}
}