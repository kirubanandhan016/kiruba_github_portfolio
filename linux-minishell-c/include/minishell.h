#ifndef MINISHELL_H
#define MINISHELL_H
#define MAX_LINE 4096
#define MAX_ARGS 128
#define MAX_PIPE_CMDS 32

typedef struct {
    char *argv[MAX_ARGS];
    int argc;
    char *infile;
    char *outfile;
    int append;
} Command;

int parse_line(char *line, Command *cmds, int *count);
int is_builtin(const Command *cmd);
int run_builtin(Command *cmd);
int execute_commands(Command *cmds, int count);
void install_signals(void);
#endif
