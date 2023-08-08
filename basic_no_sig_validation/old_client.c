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