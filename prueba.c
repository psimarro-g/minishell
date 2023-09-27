// Scott Kuhl
// Code is largely inspired by:
// http://741mhz.com/signal-handler/
// Also see:
// https://www.securecoding.cert.org/confluence/pages/viewpage.action?pageId=3903

#define _GNU_SOURCE
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv, char **envp)
{
	pid_t pid;

	char *args[] = {"./hello.sh", NULL};
	char *path = "./hello.sh";

	// Create a pipe to communicate with child process
	pid = fork();
	if(pid == 0) {
		// Child process
		execve(path, args, envp);
	}
	else {
		// Parent process
		int status;
		waitpid(pid, &status, 0);
		printf("Child process exited with status %d\n", status);
	}

}