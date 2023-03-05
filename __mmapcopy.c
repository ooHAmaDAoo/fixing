#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    char *buffer;
    int fd;
    struct stat info;
    size_t length;
    ssize_t s;
    pid_t pid;
    int status;

    // check if the file name passed as argument or exit if error
    if (argc != 2)
    {
        printf("Wrong Number Of Args\n");
        exit(1);
    }

    // open the file here or exit if error
    // FILE *fptr;
    fd = open(argv[1], 0);

    if (!fd)
    {
        printf("Error Opening File\n");
        exit(1);
    }
    //=-=-=-=-=-=-=-=-=-=-=-=-=-=
    if (fstat(fd, &info) == -1)
    {
        printf("%s empty\n", argv[1]);
        exit(0);
    }
    if ((pid = fork()) == 0)
    {

        printf("Child process\n");

        buffer = mmap(NULL, info.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

        // and check if an error occurs
        if (buffer == MAP_FAILED)
        {
            printf("MAP FAILED\n");
            exit(1);
        }
        // child process write out the file content
        write(0, buffer, info.st_size);
        if (munmap(buffer, info.st_size) == -1)
        {
            printf("UNMAP FAILED\n");
            exit(1);
        }

        printf("CP: done\n");
        exit(1);
    }
    printf("Parent process\n");
    // parent wait
    wait(NULL);
    printf("PP: done\n");
    exit(1);
}
