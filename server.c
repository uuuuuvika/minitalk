#include "minitalk.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	i;

	i = 0;
	if (size == 0)
		return (strlen(src));
	while (src[i] != '\0' && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (size > 0)
		dest[i] = '\0';
	return (strlen(src));
}

unsigned int	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t			dest_size;
	size_t			src_size;
	unsigned int	i;

	dest_size = strlen(dest);
	src_size = strlen(src);
	i = 0;
	if (size == 0 && dest_size == 0)
		return (src_size);
	if (dest_size >= size)
		return (size + src_size);
	while (src[i] != '\0' && (i + dest_size) < size - 1)
	{
		dest[dest_size + i] = src[i];
		i++;
	}
	dest[dest_size + i] = '\0';
	return ((dest_size + src_size));
}

char *strjoin(char const *s1, char const *s2) //-lbsd
{
	char *ptr;
	int lens1;
	int lens2;

	lens1 = strlen(s1);
	lens2 = strlen(s2);
	ptr = malloc(sizeof(char) * (lens1 + lens2 + 1));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s1, lens1 + 1);
	ft_strlcat(ptr, s2, lens1 + lens2 + 1);
	return (ptr);
}

void cleanup_client(t_client *client)
{
	free(client->buffer);
	client->buffer = NULL;
}

void print_and_clean(t_client *client)
{
	printf("\n%s\n", client->buffer);
	printf("\n👌 Received [%d] bytes from PID [%d]\n\n", client->bytes_recived, client->pid);
	cleanup_client(client);
}

void reset_client(t_client *client, int pid)
{
	cleanup_client(client);
	printf(YEL"\nReceiving new message from PID [%d]\n"RESET, pid);
	client->pid = pid;
	client->num_bit = 0;
	client->bytes_recived = 0;
	client->buffer = strdup("");
}

void append_byte(t_client *client)
{
	char str_byte[2];
	char *new_buffer;

	str_byte[0] = client->byte;
	str_byte[1] = '\0';
	new_buffer = ft_strjoin(client->buffer, str_byte);
	free(client->buffer);
	client->buffer = new_buffer;

	client->bytes_recived++;

	if (client->byte == 0)
	{
		print_and_clean(client);
	}
	// else
	// {
	// 	printf(YEL "\rReceiving [%d] bytes" RESET, client->bytes_recived + 1);
	// }
	client->byte = 0;
	client->num_bit = 0;
}

void signal_recived(int sig, siginfo_t *si, void *uap)
{
	static t_client client;

	(void)si;
	(void)uap;

	if (client.pid != si->si_pid && si->si_pid != 0)
		reset_client(&client, si->si_pid);

	client.byte |= (sig == SIGUSR2);
	if (++client.num_bit == 8)
		append_byte(&client);
	else
		client.byte <<= 1;
	usleep(60);
	kill(client.pid, SIGUSR1);
}

int main(void)
{
	struct sigaction signal;

	signal.sa_sigaction = signal_recived;
	signal.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR2, &signal, NULL);
	sigaction(SIGUSR1, &signal, NULL);
	printf(BLU "\n🐀 Running server PID [%d]\n\n" RESET, getpid());
	while (1)
	{
		pause();
	}
}