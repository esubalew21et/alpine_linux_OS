#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <string.h>

#define FILE_NAME "alpine_output.txt"
#define MSG "Hello from child process using write syscall!\n"

int main() {
    int fd;
    pid_t pid;
    void *mem;

    // 1. Create and open a file using system call `open`
    fd = open(FILE_NAME, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // 2. Fork a child process
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process

        // 3. Write to file using `write`
        if (write(fd, MSG, strlen(MSG)) < 0) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        // 4. Use `mmap` to allocate memory and write something
        mem = mmap(NULL, 4096, PROT_READ | PROT_WRITE,
                   MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
        if (mem == MAP_FAILED) {
            perror("mmap");
            exit(EXIT_FAILURE);
        }

        strcpy((char *)mem, "Memory mapped content from child\n");
        write(STDOUT_FILENO, mem, strlen((char *)mem));

        // 5. Exit child
        _exit(0);
    } else {
        // Parent process
        wait(NULL); // 6. Wait for child

        // 7. Use `lseek` and `read` to read the file content
        lseek(fd, 0, SEEK_SET);
        char buf[100];
        int n = read(fd, buf, sizeof(buf)-1);
        if (n < 0) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        buf[n] = '\0';
        printf("Parent read from file:\n%s", buf);

        close(fd);
    }

    return 0;
}
