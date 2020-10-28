#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
    char *argv[] = { "/bin/ls", "-la", 0 };
    char *envp[] =
    {
        "HOME=/",
        "PATH=/bin:/usr/bin",
        "USER=brandon",
        0
    };
    int fd = open("log.log", O_WRONLY|O_CREAT|O_TRUNC, 0666);
    dup2(fd, 1); // stdout is file descriptor 1
    close(fd);
    execve(argv[0], &argv[0], envp);
    fprintf(stderr, "Oops!\n");
    return -1;
}