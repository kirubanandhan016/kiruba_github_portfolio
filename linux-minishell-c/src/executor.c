#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static int redirect(const Command *c)
{
    if (c->infile)
    {
        int fd = open(c->infile, O_RDONLY);
        if (fd < 0) { perror(c->infile); return 0; }
        if (dup2(fd, STDIN_FILENO) < 0) { perror("dup2"); close(fd); return 0; }
        close(fd);
    }
    if (c->outfile)
    {
        int flags = O_WRONLY | O_CREAT | (c->append ? O_APPEND : O_TRUNC);
        int fd = open(c->outfile, flags, 0644);
        if (fd < 0) { perror(c->outfile); return 0; }
        if (dup2(fd, STDOUT_FILENO) < 0) { perror("dup2"); close(fd); return 0; }
        close(fd);
    }
    return 1;
}

int execute_commands(Command *cmds, int count)
{
    int prev_read = -1;
    pid_t pids[MAX_PIPE_CMDS];

    for (int i=0; i<count; ++i)
    {
        int pipefd[2] = {-1,-1};
        if (i < count-1 && pipe(pipefd) < 0) { perror("pipe"); return 1; }

        if (count == 1 && is_builtin(&cmds[i]))
            return run_builtin(&cmds[i]);

        pid_t pid = fork();
        if (pid < 0) { perror("fork"); return 1; }

        if (pid == 0)
        {
            if (prev_read != -1) {
                dup2(prev_read, STDIN_FILENO);
                close(prev_read);
            }
            if (i < count-1) {
                close(pipefd[0]);
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[1]);
            }
            if (!redirect(&cmds[i])) _exit(1);
            execvp(cmds[i].argv[0], cmds[i].argv);
            perror(cmds[i].argv[0]);
            _exit(127);
        }

        pids[i] = pid;
        if (prev_read != -1) close(prev_read);
        if (i < count-1) {
            close(pipefd[1]);
            prev_read = pipefd[0];
        }
    }

    if (prev_read != -1) close(prev_read);
    int status = 0;
    for (int i=0; i<count; ++i)
        waitpid(pids[i], &status, 0);
    return WIFEXITED(status) ? WEXITSTATUS(status) : 1;
}
