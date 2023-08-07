//#include "minitalk.h"

// static t_info get_input(int args, char **argv, t_info info)
// {
//     if (args < 3)
//         exit(1);
//     info.server_pid = atoi(argv[1]);
//     info.client_pid = getpid();
//     info.message = argv[2];
//     return (info);
// }

// // static void bit_mask(t_info info)
// // {
// // 	int bit = 8;
// // 	int i = -1;

// // 	while (info.message[++i] != '\0')
// // 	{
// // 		while (--bit >= 0)
// // 		{
// // 			if ((info.message[i] >> bit) & 1)
// // 			{
// // 				kill(info.server_pid, SIGUSR1);
// // 				//printf("0");
// // 				usleep(120);
// // 			}
// // 			else
// // 			{
// // 				kill(info.server_pid, SIGUSR2);
// // 				//printf("1");
// // 				usleep(120);
// // 			}
// // 		}
// // 		bit = 8;
// // 	}
// // 	if (info.message[i] == '\0')
// // 	{
// // 		while (bit-- > 0)
// // 		{
// // 			kill(info.server_pid, SIGUSR1);
// // 			usleep(120);
// // 		}
// // 	}
// // 	//write(1, "ALL GOOD!\n", 10);
// // }


// static void send_bit(int server_pid, int bit)
// {
//     if (bit)
//         kill(server_pid, SIGUSR1);
//     else
//         kill(server_pid, SIGUSR2);
//     usleep(120);
// }

// static void send_byte(int server_pid, unsigned char byte)
// {
//     for (int bit = 7; bit >= 0; --bit) {
//         int bit_value = (byte >> bit) & 1;
//         send_bit(server_pid, bit_value);
//     }
// }

// static void bit_mask(t_info info)
// {
//     // Send start signal to indicate the start of transmission
//     kill(info.server_pid, SIGUSR1);
//     usleep(120);

//     int i = 0;
//     while (info.message[i] != '\0') {
//         send_byte(info.server_pid, info.message[i]);
//         i++;
//     }

//     // Send end signal to indicate the end of transmission
//     kill(info.server_pid, SIGUSR2);
//     usleep(120);
// }



// int main(int args, char **argv)
// {
//     t_info info;
//     char *str;
//     int cl_pid;

//     if (args == 3)
//     {
//         info = get_input(args, argv, info);
//         str = info.message;
//         cl_pid = info.client_pid;
//        // printf(YEL "%d", cl_pid);
//         bit_mask(info);
//         return (0);
//     }
//     else
//     {
//         printf("smth is fucked!\n");
//         exit(1);
//     }
// }


#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

int	g_num_ack;

/*
	This function does not do anything, is just to recive the ACK signal
	from the server that takes out the usleep() of send_byte
*/

void	clean_semaforo(int sig, siginfo_t *si, void *uap)
{
	(void)uap;
	(void)si;
	if (sig == SIGUSR1)
		g_num_ack++;
}

	/* 
		This funcion rotate 8 times the bits of byte, and send the correspondig 
		signal depending if the lowest bit is 1 o 0. Then set a uslepp like a 
		TimeOut of ACK signal of the server. The funcion will continue if a ACK 
		signal from the server is recived or the usleep is over
	*/

void	send_byte(char byte, int pid)
{
	int			i;
	int			kill_response;
	int			signal;
	static int	num_bytes;

	i = 0;
	while (i < 8)
	{
		if (byte & 0x80)
			signal = SIGUSR2;
		else
			signal = SIGUSR1;
		kill_response = kill(pid, signal);
		if (kill_response < 0)
		{
			write(1, "Signal error", 13);
			exit(-1);
		}
		pause();
		byte <<= 1;
		i++;
	}
	num_bytes++;
	printf("\r\e[1;34mSending [%d] bytes\e[0m", num_bytes);
}

	/* 
	This function calls send_byte() for each byte in the string str
	If gnl==1 will not send null caracter to avoid the server think is the 
	end of the transmision in each file og get_next_line
	*/

int	send_string(char *str, int server_pid, int gnl)
{
	int	size;

	size = strlen (str);
	if (!gnl)
		g_num_ack = 0;
	while (*str)
		send_byte(*(str++), server_pid);
	if (!gnl)
	{
		send_byte(*str, server_pid);
		size++;
	}
	return (size);
}

/*
	This function extract the lines of a fd and send to
	send_string with gnl=1
*/


int	main(int argv, char **argc)
{
	int					server_pid;	
	struct sigaction	signal;
	int					bytes_send;

	if (argv == 3 || argv == 4)
	{
		signal.sa_sigaction = clean_semaforo;
		signal.sa_flags = SA_SIGINFO;
		sigaction(SIGUSR1, &signal, NULL);
		server_pid = atoi(argc[1]);
		
		bytes_send = send_string (argc[2], server_pid, 0);
		printf("\n\n 📟 Sended %d bytes to PID [%d].\n", \
		bytes_send, server_pid);
		printf("\n 🔰 Recived %d bytes ACK from PID [%d].\n\n", \
		g_num_ack / 8, server_pid);
	}
	else
		write(1, "Invalid arguments", 18);
	return (0);
}