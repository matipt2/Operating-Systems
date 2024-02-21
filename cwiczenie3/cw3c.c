#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

void child_program(char* child_program_name, char* program_name, char* mode, char* signal_num) {
    execlp(child_program_name, child_program_name, program_name, mode, signal_num, NULL);
    perror("execlp failed");
    exit(EXIT_FAILURE);
}

void parent_program(pid_t child_pid, int signal_num) {
    int status;
    pid_t group_id = getpgid(child_pid);

    if (group_id >= 0) {
        kill(-group_id, signal_num);
    }

    waitpid(child_pid, &status, 0);

    if (WIFSIGNALED(status)) {
        int signal_code = WTERMSIG(status);
        char* signal_name = strsignal(signal_code);
        printf("Child process terminated with signal %d (%s)\n", signal_code, signal_name);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 5) {
        fprintf(stderr, "Usage: %s [child_program] [mode] [signal_num] [program_name]\n", argv[0]);
        return EXIT_FAILURE;
    }

    char* child_program_name = argv[1];
    char* mode = argv[3];
    int signal_num = atoi(argv[4]);
    char* program_name = argv[2];

    pid_t child_pid = fork();

    if (child_pid < 0) {
        perror("fork failed");
        return EXIT_FAILURE;
    } else if (child_pid == 0) {
        setpgid(0, 0);
        child_program(child_program_name, program_name, mode, argv[4]);
    } else {
        sleep(1);
        parent_program(child_pid, signal_num);
    }

    return EXIT_SUCCESS;
}


