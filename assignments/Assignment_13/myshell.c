#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main()
{
	char line[1024], *args[1024], *tmp;
	int i, output_file, pid, status_of_child, spaces, output_to_file_location;
	int run_second_command_location, second_command_executed, second_command_strict;

	while (1)
	{
		/* Clean all values before running/re-running 'command line' */
		memset(&args[0], 0, sizeof(args));
		memset(&line[0], '\0', sizeof(line));
		i = output_file = pid = status_of_child = spaces = output_to_file_location = 0;
		run_second_command_location = second_command_executed = second_command_strict = 0;

		/* '$PS1' immitation */
		printf("Hello!> ");

		/* If cannot read input die() */
		if (! fgets(line, 1023, stdin))
			break;

		/* If input 'exit', die() */
		if (strcmp(line, "exit\n") == 0)
			break;

		/* Replace out linebreaks w/ string enders */
		for (i = 0; i < strlen(line); i++)
			if (line[i] == '\n')
				line[i] = '\0';

		/* Set args */
		tmp = strtok(line, " ");
		while (tmp)
		{
			if (strchr(">\0", *tmp))
			{
				/* Seems like we want to port out to a file */
				args[spaces++] = NULL;
				output_to_file_location = spaces;
			}
			else if (strcmp("&&", tmp) == 0)
			{
				/* There will be two commands given, and the first must succeed to run second */
				args[spaces++] = NULL;
				run_second_command_location = spaces;
				second_command_strict = 1;
			}
			else if (strcmp(";", tmp) == 0)
			{
				/* There will be two commands given, and they will both execute */
				args[spaces++] = NULL;
				run_second_command_location = spaces;
				second_command_strict = 0;
			}
			else
			{
				args[spaces++] = tmp;
			}
			tmp = strtok(NULL, " ");
		}
		args[++spaces] = NULL;

		/* Set flag for second command via double commands */
		if (0)
			RUN_AGAIN: second_command_executed = 1;

		/* LET US BEGIN THE FORKING! */
		pid = fork();

		if (pid == 0) /* Child */
		{
			if (output_to_file_location)
			{
				/* Child wants to print to a file, so lets do so */
				output_file = open(args[output_to_file_location], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
				dup2(output_file, 1);
			}

			execvp(line, args);
			fprintf(stderr, "Error: %s\n", strerror(errno));
			exit(errno);
		}
		else
		{
			if (run_second_command_location && second_command_executed == 0)
			{
				/* Running the second command */
				if (waitpid(pid, &status_of_child, 0) == -1)
				{
					perror("waitpid failed");
					return EXIT_FAILURE;
				}

				/* If (child exits w/ 0 AND strict is on) OR (strict is off), execute 2nd command */
				if ( (WEXITSTATUS(status_of_child) == 0 && second_command_strict == 1) ||  second_command_strict == 0)
				{
					/* Overwrite old args w/ new args of second command */
					for (i = run_second_command_location; i < spaces; i++)
						args[i-run_second_command_location] = args[i];
					args[i] = NULL;

					/* Copy command into the line */
					strcpy(line, args[0]);

					/* Jump back to fork() again */
					goto RUN_AGAIN;
				}
			}
			else
			{
				wait(NULL);
			}
		}
	}

	return 0;
}