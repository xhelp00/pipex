## Battle plan:

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
## STUDY:

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
- when fork() fails it returns -1
- child process has its own copy of variables in memory when forked (different place in memory even tho that values are the same)
- process id of current process can be called by getpid(), or getppid() if we want to call parent process id (#include <sys/wait.h>)
- if (wait(NULL) == -1) can be used for checking that there is nothing else to be waiting for
- wait() should be usually called by the end of program in case that we are forking processes
- pipe() function takes 2 ints - filedesc,
- execlp() execution function REPLACE current process with whatever is executed as a passed command (it means that function called in main after execlp is called will not be executed!)
 - therefore exec should NOT be called in main/parent process but in child process
 - in case that we call exec in parent process that has been forked before - we create a zombie child XD
 - execlp replace the process ONLY in case that command exists, in case of error execlp returns -1
 - execve function has arguments as follows
 int execve( const char * path, 	A path name that identifies the new process image file.
            char * const argv[], 	An array of character pointers to NULL-terminated strings. Your application must ensure that the last member of this array is a NULL pointer. These strings constitute the argument list available to the new process image. The value in argv[0] must point to a filename that's associated with the process being started.
            char * const envp[] );  An array of character pointers to NULL-terminated strings. These strings constitute the environment for the new process image. Terminate the envp array with a NULL pointer.
- exec function runs executable directly and NOT through out bash - therefore we cannot use | to chain more commands as we do it in bash
- int WIFEXITED(int status); Query status to see if a child process ended normally
- file descriptors - unique across one process, file descriptor 0 = STDIN, therefore read(0) == scanf, file descriptor 1 = STDOUT, file descriptor 2 = STDERR.... these 3 fd gets open in every process automatically 
- dup function gets fd and duplicates it
- dup2 function gets two fds - file descriptor and other one that gets replaced (eg. dup2(fd, STDOUT_FILENO) replaces stdout by fd)
