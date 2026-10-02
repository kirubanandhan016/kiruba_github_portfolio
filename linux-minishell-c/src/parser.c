#include "minishell.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static char *next_token(char **p)
{
    char *s = *p;
    while (*s == ' ' || *s == '\t') s++;
    if (!*s) { *p = s; return NULL; }

    if (*s == '|' || *s == '<' || *s == '>')
    {
        char *start = s++;
        if (*start == '>' && *s == '>') s++;
        *p = s;
        return start;
    }

    char *start = s;
    while (*s && *s != ' ' && *s != '\t' && *s != '|' && *s != '<' && *s != '>')
        s++;
    if (*s) *s++ = '\0';
    *p = s;
    return start;
}

int parse_line(char *line, Command *cmds, int *count)
{
    memset(cmds, 0, sizeof(Command) * MAX_PIPE_CMDS);
    *count = 1;
    char *p = line;
    char *tok;

    while ((tok = next_token(&p)) != NULL)
    {
        Command *c = &cmds[*count - 1];

        if (strcmp(tok, "|") == 0)
        {
            if (c->argc == 0 || *count >= MAX_PIPE_CMDS) return 0;
            (*count)++;
            continue;
        }

        if (strcmp(tok, "<") == 0 || strcmp(tok, ">") == 0 || strcmp(tok, ">>") == 0)
        {
            char *file = next_token(&p);
            if (!file || !strcmp(file, "|") || !strcmp(file, "<") ||
                !strcmp(file, ">") || !strcmp(file, ">>")) return 0;
            if (tok[0] == '<') c->infile = file;
            else { c->outfile = file; c->append = strcmp(tok, ">>") == 0; }
            continue;
        }

        if (c->argc >= MAX_ARGS - 1) return 0;
        c->argv[c->argc++] = tok;
        c->argv[c->argc] = NULL;
    }
    return cmds[0].argc > 0;
}
