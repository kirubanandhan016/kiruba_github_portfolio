#include "minishell.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
    char line[MAX_LINE];
    Command cmds[MAX_PIPE_CMDS];
    int count;

    install_signals();

    for (;;)
    {
        fputs("minishell$ ", stdout);
        fflush(stdout);
        if (!fgets(line, sizeof line, stdin))
        {
            putchar('\n');
            break;
        }

        line[strcspn(line, "\n")] = '\0';
        if (!line[0]) continue;

        if (!parse_line(line, cmds, &count))
        {
            fprintf(stderr, "minishell: syntax error\n");
            continue;
        }
        execute_commands(cmds, count);
    }
    return 0;
}
