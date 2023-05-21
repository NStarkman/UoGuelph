#include "A2.h"

/**
 * It closes all the pipes and frees the memory allocated for pipes and child_pids.
 * 
 * @param pipes a 2D array of file descriptors, where each row is a pipe.
 * @param child_pids an array of pid_t, which is the process id of each child process.
 */
void free_all (int ** pipes,  pid_t * child_pids){
    int i;
    for (i = 0; i < MaxChildNum; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
        free(pipes[i]);
    }
    free(pipes);
    free(child_pids);
    
}
/**
 * It waits for a child process to terminate, and then writes the letter frequency histogram to a file
 * 
 * @param signum The signal number.
 */

void child_handler(int signum) {
    pid_t pid;
    int status;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        printf("Child process %d terminated.\n", pid);
        int i;
        for (i = 0; i < MaxChildNum; i++) {
            if (child_pids[i] == pid && status == 0) {
                int letter_counts[26] = {0};
                int j, count;
                read(pipes[i][0], &count, sizeof(count));
                for (j = 0; j < count; j++) {
                    char letter;
                    int freq;
                    read(pipes[i][0], &letter, sizeof(letter));
                    read(pipes[i][0], &freq, sizeof(freq));
                    letter_counts[letter - 'a'] = freq;
                }
                close(pipes[i][1]);
                char filename[50];
                sprintf(filename, "file%d.hist", pid);
                int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                for (j = 0; j < 26; j++) {
                    char buffer[20];
                    sprintf(buffer, "%c %d\n", j + 'a', letter_counts[j]);
                    write(fd, buffer, strlen(buffer));
                }
                close(fd);
                break;
            }
        }
    }
    child_count--;
}

/**
 * It opens the file, reads the contents into a character array, calculates the letter frequency in the
 * character array, and sends the letter frequency data to the parent process through a pipe
 * 
 * @param file_index the index of the pipe to use for communication with the parent process
 * @param filename the name of the file to be read
 */

void child_process(int file_index, char *filename) {
    // Open input file and read contents into character array
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        if (strcmp(filename, "SIG") == 0) {
            printf("Child process %d received SIGINT.\n", getpid());
            kill(getpid(), SIGINT);
            free_all(pipes, child_pids);
            exit(1);
        }
        printf("Error: failed to open file.\n");
        free_all(pipes, child_pids);
        exit(1);
    } 
    off_t file_size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    char *file_contents = malloc(file_size);
    if (file_contents == NULL) {
        printf("Error: failed to allocate memory.\n");
        free_all(pipes, child_pids);
        close(fd);
        exit(1);
    }
    ssize_t bytes_read = read(fd, file_contents, file_size);
    if (bytes_read == -1) {
        printf("Error: failed to read file.\n");
        free(file_contents);
        free_all(pipes, child_pids);
        close(fd);
        exit(1);
    }
    close(fd);

    // Calculate letter frequency in character array
    int letter_counts[26] = {0};
    int i;
    for (i = 0; i < file_size; i++) {
        char c = tolower(file_contents[i]);
        if (c >= 'a' && c <= 'z') {
            letter_counts[c - 'a']++;
        }
    }
    free(file_contents);

    // Send letter frequency data to parent process through pipe
    int count = 26;
    write(pipes[file_index][1], &count, sizeof(count));
    for (i = 0; i < 26; i++) {
        char letter = i + 'a';
        int freq = letter_counts[i];
        write(pipes[file_index][1], &letter, sizeof(letter));
        write(pipes[file_index][1], &freq, sizeof(freq));
    }
    close(pipes[file_index][1]);
    free_all(pipes, child_pids);
    exit(0);
}

/**
 * The parent process creates a pipe for each child process, forks a child process, and then waits for
 * all child processes to complete
 * 
 * @param argc The number of arguments passed to the program.
 * @param argv the array of arguments passed to the program
 * 
 * @return The return value of the last command executed in the child process.
 */

int main(int argc, char *argv[]) {
    pid_t pid;
    MaxChildNum = argc - 1;

    pipes = (int **)malloc(MaxChildNum * sizeof(int *));
    child_pids = (pid_t *)malloc(MaxChildNum * sizeof(pid_t));
    for(int i = 0; i < MaxChildNum; i++){
        pipes[i] = (int *)malloc(2 * sizeof(int));
    }

    if (argc < 2) {
        printf("Usage: %s file1 file2 ... fileN\n", argv[0]);
        free_all(pipes, child_pids);
        exit(1);
    }
    
    signal(SIGCHLD, child_handler);

    int i;
    for (i = 0; i < MaxChildNum; i++) {
        if (pipe(pipes[i]) < 0) {
            printf("Error: pipe creation failed.\n");
            free_all(pipes, child_pids);
            exit(1);
        }
    }

    for (i = 0; i < MaxChildNum; i++) {
        pid = fork();
        if (pid == -1) {
            printf("Error: fork failed.\n");
            free_all(pipes, child_pids);
            exit(1);
        } else if (pid == 0) {
            child_process(i, argv[i + 1]);
        } else {
            child_pids[i] = pid;
            close(pipes[i][1]);
            child_count++;

        }
    }

    // Wait for child processes to complete
    while (child_count>0) {
        int i, num_terminated = 0;
        int status;
        pause();
        for (i = 0; i < MaxChildNum; i++) {
            if ((pid = waitpid(-1, &status, WNOHANG)) == -1) {
                num_terminated++;
            }
            
        }
        if (num_terminated == MaxChildNum) {
            break;
        }
    }

    // Free allocated memory
    free_all(pipes, child_pids);
    
    return 0;
}