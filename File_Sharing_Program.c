#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char **argv)
{
	if (aragc != 3)
	{
		perror("Wrong argc Number\n");
		exit(1);
	}

	int fd2 = open( argv[2], O_WRONLY );
	if (fd2 == -1)
	{
		perror("Error Opening file fd2\n");
		exit(1);
	}

	int pid = fork();

	if (pid < 0)
	{
		perror("Error while fork\n");
		exit(1);
	}
	else if (pid == 0)
	{
		//chiled proces
		int fd_c = open( argv[1], O_RDONLY);
		if (fd_c == -1)
		{
			perror("Error Opening file in chiled proces\n");
			exit(1);
		}

		char ch;
		int count = 0;
		int pid = getpid();
		while (read (fd_c, &ch, sizeof(char) > 0))
		{
			if (isalpha(ch))
			{	count++;	}
		}

		write(fd2, "Child PID ", strlen("Child PID "));
		write(fd2, pid, sizeof(int));
		write(fd2, "counted ", strlen("counted "));
		write(fd2, count, sizeof(int));
		write(fd2, " alphabets", strlen(" alphabets"));
		close(fd_c);
		

	}
	else
	{
		//parent proces
		int fd_p = open(argv[1], O_RDONLY);
		if (fd_p ==  -1)
		{
			perror("Error Opening file in parent proces\n");
			exit(1);
		}
		char ch;
		int count = 0;
		int pid = getpid();
		while( read (fd_p, &ch, sizeof(char) > 0) )
		{
			if(isdigit(ch))
			{	count++;	}
		}

		wait(NULL);

		write (fd2, "Parent PID ", strlen("Parent PID "));
		write (fd2, pid, sizeof(int));
		write (fd2, "counted ", strlen("counted "));
		write (fd2, count, sizeof(int));
		write (fd2, " digits", strlen(" digits"));
		close(fd_p);

	}
	close(fd2);
	return 0;
}
