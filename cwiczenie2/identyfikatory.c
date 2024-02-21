#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    printf("Potomny PID procesu \"identyfikatory\": %d\n", getpid());
    printf("Potomny UID procesu \"identyfikatory\": %d\n", getuid());
    printf("Potomny GID procesu \"identyfikatory\": %d\n", getgid());
    return 0;


}

