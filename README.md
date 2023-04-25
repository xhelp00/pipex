Battle plan:

Validate the input arguments:
a. Check that there are exactly 4 arguments passed to the program.
b. Check that file1 and file2 exist and are readable and writable.
c. Check that cmd1 and cmd2 are valid shell commands.

Create two pipes to connect the output of cmd1 to the input of cmd2:
a. Call the pipe() system call to create a pipe.
b. Fork a child process.
c. In the child process:
i. Redirect the standard output to the write end of the pipe using dup2().
ii. Close the read end of the pipe using close().
iii. Execute cmd1 using execvp().
d. In the parent process:
i. Close the write end of the pipe using close().
e. Repeat steps b-d to create a second child process and a second pipe.

Redirect the standard input and output of the parent process to the appropriate files:
a. Open file1 and file2 using open() with appropriate flags and mode.
b. Redirect the standard input and output using dup2().

Wait for both child processes to terminate using waitpid().

Print an error message if any of the system calls or commands fail.
********************************
STUDY:

- fork() creates child process that runs along with the "main" one, function fork also return number representing id of process
- child process always has pid 0
- wait(0) function that make parent process wait until child process is over
main/parent
|
fork
| \	pid 0
|  \
|  /  do smth
| /   
wait(0)
|    
- for doing stuff in parent process only we may use if (pid != 0)
- child process has its own copy of variables in memory when forked (different place in memory even tho that values are the same)

