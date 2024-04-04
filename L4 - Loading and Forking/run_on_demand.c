#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void handle_signal(int signum);
void cleanup();

int should_exit = 0;

void main(void) {
    signal(SIGUSR1, handle_signal);
    signal(SIGUSR2, handle_signal);
    signal(SIGINT, handle_signal); // handle CTRL+C




    while (!should_exit) {
        pause(); // wait for a signal
    }

    cleanup();
}

void handle_signal(int signum) {
    if (signum == SIGINT) {
        should_exit = 1; // set flag to exit program
        return;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // child process
        char* cmd;
        if (signum == SIGUSR1) {
            cmd = "ls";
        } else if (signum == SIGUSR2) {
            cmd = "ls -l -a";
        } else {
            exit(0);
        }

        printf("Received signal %d.\n", signum);
        printf("Running %s.\n", cmd);
        printf("Done!\n");

        char* args[] = {cmd, NULL};
        execvp(args[0], args);
        perror("execvp");
        exit(1);
    } else {
        // parent process
        int status;
        waitpid(pid, &status, 0);
    }
}

void cleanup() {
    printf("Leaving gracefully!\n");
}
