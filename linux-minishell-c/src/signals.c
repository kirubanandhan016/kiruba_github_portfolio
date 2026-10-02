#include "minishell.h"
#include <signal.h>
#include <stdio.h>

static void handle_sigint(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\nminishell$ ", 12);
}

void install_signals(void)
{
    struct sigaction sa = {0};
    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);
    signal(SIGQUIT, SIG_IGN);
}
