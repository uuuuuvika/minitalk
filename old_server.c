#include "minitalk.h"

// void decode(int sig_num)
// {
//   static int bit = 0;
//   static unsigned char c = 0;
//   //(void)t;
//   // int cl_pid = siginfo_t->si_pid;
//   c |= (sig_num == SIGUSR1);
//   if (++bit == 8)
//   {
//     bit = 0;
//     if (c >= 0 && c <= 127)
//       write(1, &c, 1);
//     else
//       write(1, "\n", 1);
//     c = 0;
//   }
//   else
//     c <<= 1;
// }

// int main()
// {
//   struct sigaction signal_received;

//   signal_received.sa_handler = decode;
//   signal_received.sa_flags = 0;

//   // signal_received.sa_sigaction = decode;
//   // signal_received.sa_flags = SA_SIGINFO;
//   // sigemptyset(&signal_received.sa_flags);

//   sigaction(SIGUSR1, &signal_received, NULL);
//   sigaction(SIGUSR2, &signal_received, NULL);

//   printf(GRN "Welcome to the server [PID: %d]\n", getpid());

//   while (1)
//   {
//     // pause();
//   }

//   return (0);
// }
