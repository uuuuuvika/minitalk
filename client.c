#include "minitalk.h"

int ack;

void get_ack(int sig)
{
    if (sig == SIGUSR1)
        ack++;
}

static void bit_mask(char *str, int server_pid)
{
    int i = 0;
    int bit = 7;

    while (1)
    {
        char current_byte = str[i];
        char current_bit = (current_byte >> bit) & 1;

        if (current_bit == 1)
            kill(server_pid, SIGUSR2);
        else
            kill(server_pid, SIGUSR1);
        pause();
        if (bit == 0)
        {
            bit = 7;
            i++;
            if (current_byte == '\0')
                break;
        }
        else
            bit--;
    }
}

int main(int argv, char **argc)
{
    int server_pid;
    struct sigaction signal;

    if (argv == 3)
    {
        signal.sa_handler = get_ack;
        signal.sa_flags = 0;
        sigaction(SIGUSR1, &signal, NULL);
        server_pid = atoi(argc[1]);
        printf("\n🦢 Running client PID [%d]\n", getpid());
        bit_mask(argc[2], server_pid);

        printf("\n🔹 Recived [%d] ACK from PID [%d]\n\n", ack / 8, server_pid);
    }
    else
        write(1, "Invalid arguments", 18);
    return (0);
}