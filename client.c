#include "minitalk.h"

static t_info	ft_get_input(int args, char** argv, t_info info)
{	
	if (args < 3)
		exit(1);
	info.server_pid = atoi(argv[1]);
	if (!info.server_pid || info.server_pid <= 100 || info.server_pid >= 99999)
		exit(1);
	info.client_pid = getpid();
	if (!info.client_pid)
		exit(1);
	info.message = argv[2];
	if (!info.message)
		exit(1);
	return (info);
}

static void ft_bitmask(t_info info)
{
	int	bit = 8;
	int	i = -1;
	
	while (info.message[++i] != '\0')
	{
		while (--bit >= 0)
		{
			if ((info.message[i] >> bit) & 1)
			{
				kill(info.server_pid, SIGUSR1);
				usleep(100);
			}
			else
			{
				kill(info.server_pid, SIGUSR2);
				usleep(100);
			}
		}
		bit = 8;
	}
	if (info.message[i] == '\0')
	{
		while (bit-- > 0)
		{
			kill(info.server_pid, SIGUSR1);
			usleep(100);
		}
	}
	write(1, "successful\n", 11);
}

static void	ft_transfer_to_server(t_info info)
{
	char	*str;

	str = info.message;
	if (!info.server_pid)
	{
		write(1,"invalid server_pid\n", 19);
		exit(1);
	}
	ft_bitmask(info);
}

int	main(int args, char **argv)
{		
	t_info	info;
	
	if (args == 3)
	{
		info = ft_get_input(args, argv, info);
		ft_transfer_to_server(info);
		return (0);
	}
	else
	{
		printf("exception\n");
		exit(1);
	}
}