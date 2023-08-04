#include "minitalk.h"

void ft_putstr_fd(char *s, int fd)
{
  int i;

  i = 0;
  while (s[i] != '\0')
  {
    write(fd, &s[i], 1);
    i++;
  }
}

void ft_putchar_fd(char c, int fd)
{
  write(fd, &c, 1);
}

void ft_putnbr_fd(int n, int fd)
{
  if (n == -2147483648)
  {
    ft_putstr_fd("-2147483648", fd);
    return;
  }
  if (n < 0)
  {
    ft_putchar_fd('-', fd);
    ft_putnbr_fd(-n, fd);
  }
  else if (n > 9)
  {
    ft_putnbr_fd(n / 10, fd);
    ft_putnbr_fd(n % 10, fd);
  }
  else
    ft_putchar_fd(n + '0', fd);
}

static void msg(int sig_num, siginfo_t *siginfo_t, void *t)
{
  static int bit = 0;
  static unsigned char c = 0;

  (void)t;
  c |= (sig_num == SIGUSR1);
  if (++bit == 8)
  {
    bit = 0;
    if (c >= 0 && c <= 127)
      ft_putchar_fd(c, 1);
    else
      ft_putchar_fd('\n', 1);
    c = 0;
  }
  else
    c <<= 1;
}

int main(int args, char **argv)
{
  struct sigaction server_act;
  (void)argv;

  if (args != 1)
    exit(1);
  server_act.sa_flags = SA_SIGINFO;
  sigemptyset(&server_act.sa_flags);
  server_act.sa_sigaction = msg;
  sigaction(SIGUSR1, &server_act, NULL);
  sigaction(SIGUSR2, &server_act, NULL);

  printf(GRN "Welcome to the server [PID: %d]\n", getpid());

  while (1)
    pause();
  return (0);
}