# Linux MiniShell in C

A compact Linux command shell implemented in C to practice process creation, program execution, pipes, redirection, file descriptors, built-ins, and signal handling.

## Supported
- External commands
- `cd`
- `pwd`
- `echo`
- `env`
- `export`
- `unset`
- `exit`
- `<`
- `>`
- `>>`
- `|`

## Build
```bash
make
```

## Run
```bash
./minishell
```

## Examples
```text
minishell$ pwd
minishell$ echo hello
minishell$ ls | wc -l
minishell$ echo hello > output.txt
minishell$ cat < output.txt
minishell$ exit
```

## System Calls / APIs
- `fork`
- `execvp`
- `waitpid`
- `pipe`
- `dup2`
- `open`
- `close`
- `chdir`
- `getcwd`
- `sigaction`

## Limitations
This is an educational shell and is not Bash-compatible. Advanced quoting, command substitution, job control, wildcard expansion and full shell grammar are intentionally outside the initial implementation.
