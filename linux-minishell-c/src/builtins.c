#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int is_builtin(const Command *c)
{
    if (!c->argv[0]) return 0;
    const char *s = c->argv[0];
    return !strcmp(s,"cd") || !strcmp(s,"pwd") || !strcmp(s,"echo") ||
           !strcmp(s,"env") || !strcmp(s,"export") || !strcmp(s,"unset") ||
           !strcmp(s,"exit");
}

int run_builtin(Command *c)
{
    const char *name = c->argv[0];
    if (!strcmp(name, "exit")) exit(0);

    if (!strcmp(name, "cd"))
    {
        const char *dir = c->argv[1] ? c->argv[1] : getenv("HOME");
        if (!dir || chdir(dir) != 0) perror("cd");
        return 0;
    }

    if (!strcmp(name, "pwd"))
    {
        char cwd[4096];
        if (getcwd(cwd, sizeof cwd)) puts(cwd);
        else perror("pwd");
        return 0;
    }

    if (!strcmp(name, "echo"))
    {
        for (int i=1; c->argv[i]; ++i)
            printf("%s%s", i > 1 ? " " : "", c->argv[i]);
        putchar('\n');
        return 0;
    }

    if (!strcmp(name, "env"))
    {
        extern char **environ;
        for (char **e=environ; *e; ++e) puts(*e);
        return 0;
    }

    if (!strcmp(name, "export"))
    {
        if (!c->argv[1]) return run_builtin(&(Command){.argv={"env",NULL}});
        for (int i=1; c->argv[i]; ++i)
        {
            char *eq = strchr(c->argv[i], '=');
            if (!eq) { fprintf(stderr, "export: expected NAME=value\n"); continue; }
            *eq = '\0';
            if (setenv(c->argv[i], eq + 1, 1) != 0) perror("export");
        }
        return 0;
    }

    if (!strcmp(name, "unset"))
    {
        for (int i=1; c->argv[i]; ++i) unsetenv(c->argv[i]);
        return 0;
    }
    return 1;
}
