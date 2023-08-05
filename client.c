#include "minitalk.h"

static t_info get_input(int args, char **argv, t_info info)
{
    if (args < 3)
        exit(1);
    info.server_pid = atoi(argv[1]);
    info.client_pid = getpid();
    info.message = argv[2];
    return (info);
}

static void bit_mask(t_info info)
{
	int bit = 8;
	int i = -1;

	while (info.message[++i] != '\0')
	{
		while (--bit >= 0)
		{
			if ((info.message[i] >> bit) & 1)
			{
				kill(info.server_pid, SIGUSR1);
				usleep(80);
			}
			else
			{
				kill(info.server_pid, SIGUSR2);
				usleep(80);
			}
		}
		bit = 8;
	}
	if (info.message[i] == '\0')
	{
		while (bit-- > 0)
		{
			kill(info.server_pid, SIGUSR1);
			usleep(80);
		}
	}
	write(1, "ALL GOOD!\n", 10);
}

// static void send_bit(int pid, int bit)
// {
//     if (bit)
//         kill(pid, SIGUSR1);
//     else
//         kill(pid, SIGUSR2);
//     usleep(80);
// }

// static void bit_mask(t_info info)
// {
//     int bit = 8;
//     int i = -1;

//     while (info.message[++i] != '\0')
//     {
//         while (--bit >= 0)
//         {
//             send_bit(info.server_pid, (info.message[i] >> bit) & 1);
//         }
//         bit = 8;
//     }
//     if (info.message[i] == '\0')
//     {
//         while (bit-- > 0)
//         {
//             send_bit(info.server_pid, 0);
//         }
//     }
//     write(1, "ALL GOOD!\n", 10);
// }

int main(int args, char **argv)
{
    t_info info;
    char *str;
    int cl_pid;

    if (args == 3)
    {
        info = get_input(args, argv, info);
        str = info.message;
        cl_pid = info.client_pid;
        printf(YEL "%d", cl_pid);
        bit_mask(info);
        return (0);
    }
    else
    {
        printf("smth is fucked!\n");
        exit(1);
    }
}