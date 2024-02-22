#include "pipex.h"

// open and close the filedescriptors that you want to use

void	child2_process(char *av[], char **env, int *p_fd)
{
    int fd;
    fd = open(av[1], O_CREAT | O_TRUNC | O_WRONLY);
    dup2(fd, 1);
    dup2(p_fd[0], 0);
    close(fd);
    close(p_fd[1]);
    close(p_fd[0]);
    cmd_execute(av, env);
}
// open and close the filedescriptors that you want to use
// Fonction to execute the command // 

void	child_process(char *av[], char **env, int *p_fd)
{
	int	fd;
	fd = open(av[1], O_RDONLY);
	dup2(fd, 0);
    dup2(p_fd[1], 1);
    close(fd);
    close(p_fd[0]);
    close(p_fd[1]);
    cmd_execute(av, env);
}
// waiting for the child process one and two to reach the end

void	waiting_process(pid_t id, pid_t id2)
{
    waitpid(id, NULL, 0);
    waitpid(id2, NULL, 0);
}

// go to child fonction with the av[] the file descriptor and the env for the path later.
// wait both of the children

int	main(int ac, char *av[], char **env)
{
    int	p_fd[2];
    pid_t	p_id;
    pid_t	p_id2;

    if (pipe(p_fd) == -1)
        exit(-1);
    p_id = fork();
    if (p_id == -1)
        exit(-1);
    else if (p_id == 0)
        child_process(av, env, p_fd);
    p_id2 = fork();
    if (p_id2 == -1)
        exit(-1);
    else if (p_id2 == 0)
        child_process(av, env, p_fd);
    waiting_process(p_id, p_id2);
    return (0);
}