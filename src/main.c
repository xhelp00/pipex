/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <phelebra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:17:47 by phelebra          #+#    #+#             */
/*   Updated: 2023/04/24 15:09:54 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int main(int argc, char *argv[])
{
    int pipefd[2];
    pid_t pid1, pid2;
    int fd1, fd2;

    // Validate input arguments
    if (argc != 5) {
        fprintf(stderr, "Usage: %s file1 cmd1 cmd2 file2\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if (access(argv[1], R_OK) == -1) {
        perror("file1");
        exit(EXIT_FAILURE);
    }
    if (access(argv[4], W_OK) == -1) {
        perror("file2");
        exit(EXIT_FAILURE);
    }

    // Create the pipes
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Execute cmd1 in child process 1
    pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid1 == 0) {
        // Child process 1
        if (close(pipefd[0]) == -1) { // Close read end of pipe
            perror("close");
            exit(EXIT_FAILURE);
        }
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) { // Redirect stdout to write end of pipe
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        if (close(pipefd[1]) == -1) { // Close write end of pipe
            perror("close");
            exit(EXIT_FAILURE);
        }
        execlp("sh", "sh", "-c", argv[2], NULL); // Execute cmd1
        perror("execlp");
        exit(EXIT_FAILURE);
    }

	pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        exit(1);
    } else if (pid2 == 0) {
        // Child process 2
        close(pipefd[1]);  // Close the write end of the pipe

        if (dup2(pipefd[0], STDIN_FILENO) == -1) {
            perror("dup2");
            exit(1);
        }

        if (dup2(open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666), STDOUT_FILENO) == -1) {
            perror("dup2");
            exit(1);
        }

        execl("/bin/sh", "sh", "-c", argv[3], NULL);
        perror("execl");
        exit(1);
    }

    // Parent process
    close(pipefd[0]);  // Close both ends of the pipe
    close(pipefd[1]);

    if (waitpid(pid1, NULL, 0) == -1) {
        perror("waitpid");
        exit(1);
    }

    if (waitpid(pid2, NULL, 0) == -1) {
        perror("waitpid");
        exit(1);
    }

    return 0;
}
