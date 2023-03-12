#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

int main()
{
    int fd = open("first_time.txt", O_WRONLY);
    if (fd < 0)
    {
        perror("Error Opening File\n");
        exit(1);
    }

    char ch[1];
    int length = 0;
    ch[0] = getc(stdin);
    while (ch[0] != EOF)
    {
        length = write(fd, ch, 1);
        ch[0] = getc(stdin);
    }

    int check = close(fd);

    if (check)
    {
        perror("error close not 0\n");
        exit(1);
    }
    check = 0;
    fd = 0;

    int fd2 = open("Exists.txt", O_RDONLY);
    fd = open("first_time.txt", /*O_WRONLY |*/ O_APPEND);
    if (fd2 < 0 || fd < 0)
    {
        perror("Error Opening File\n");
        exit(1);
    }

    while ((length = read(fd2, ch, 1)) > 0)
    {
        check = write(fd, ch, length);
        if (check < 0)
        {
            perror("Error Writing File\n");
            exit(1);
        }
    }

    check = close(fd2);
    if (check)
    {
        perror("error close not 0\n");
        exit(1);
    }
    check = 0;

    check = close(fd);
    if (check)
    {
        perror("error close not 0\n");
        exit(1);
    }

    struct stat stats;
    check = stat("first_time.txt", &stats);
    if (check)
    {
        perror("Error - stat\n");
        exit(1);
    }

    printf("\nFile access: ");
    if (stats.st_mode & R_OK)
        printf("read ");
    if (stats.st_mode & W_OK)
        printf("write ");
    if (stats.st_mode & X_OK)
        printf("execute");

    printf("\nFile size: %ld", stats.st_size);
    struct tm dt;
    dt = *(gmtime(&stats.st_mtime));
    printf("\nModified on: %d:%d:%d\n", dt.tm_hour + 3, dt.tm_min, dt.tm_sec);
    return 0;
}
