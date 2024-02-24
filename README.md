<h1 align="center" id="top">42_pipex</h1>

<p align="center">
  <a href="#about">About</a> &#xa0; | &#xa0; 
  <a href="#examples">Examples</a> &#xa0; | &#xa0;
  <a href="#bonus-functionalities">Bonus functionalities</a> &#xa0; | &#xa0;
  <a href="#usage">Usage</a> &#xa0; | &#xa0;
  <a href="#allowed-functions">Allowed functions</a> &#xa0; | &#xa0;
  <a href="https://github.com/Szabold1" target="_blank">Author</a>
</p>

<br>

## About

Pipex is a project written in C that aims to recreate the functionality of pipes in the Unix shell. The program takes a command-line input in the form of:

```shell
./pipex infile cmd1 cmd2 outfile
```

This is designed to behave like the Unix command:

```shell
< infile cmd1 | cmd2 > outfile
```

Here's how it works:

- infile: Input file to be read from.
- cmd1: First command to be executed.
- cmd2: Second command to be executed.
- outfile: Output file to be written to.

## Examples

- To count the number of lines in a file:

```shell
# pipex version
./pipex infile "ls -l" "wc -l" outfile
# Unix version
< infile ls -l | wc -l > outfile
```

- To count the number of words containing 'a' in a file:

```shell
# pipex version
./pipex infile "grep a" "wc -w" outfile
# Unix version
< infile grep a | wc -w > outfile
```

## Bonus functionalities

- Handling multiple pipes:

```shell
# pipex_bonus version
./pipex infile cmd1 cmd2 cmd3 ... cmdn outfile
# Unix version
< infile cmd1 | cmd2 | cmd3 ... | cmdn > outfile
```

- Support for "here_doc" syntax:

```shell
# pipex_bonus version
./pipex here_doc LIMITER cmd cmd1 file
# Unix version
cmd << LIMITER | cmd1 >> file
```

## Usage

To create pipex, run the following command inside the pipex folder:

```shell
make
```

To create pipex_bonus, run the following command inside the pipex folder:

```shell
make bonus
```

## Allowed functions

The following functions were allowed for use in this project:

| **Function** | **Man**        | **Short Description**                                                    |
| ------------ | -------------- | ------------------------------------------------------------------------ |
| open         | man 2 open     | Opens a file or device and returns a file descriptor                     |
| close        | man 2 close    | Closes a file descriptor                                                 |
| read         | man 2 read     | Reads data from a file descriptor                                        |
| write        | man 2 write    | Writes data to a file descriptor                                         |
| malloc       | man 3 malloc   | Allocates a block of memory dynamically                                  |
| free         | man 3 free     | Deallocates a block of memory                                            |
| perror       | man 3 perror   | Prints a descriptive error message to stderr based on the value of errno |
| strerror     | man 3 strerror | Returns a string describing the error code passed as argument            |
| access       | man 2 access   | Checks the accessibility of a file or directory                          |
| dup          | man 2 dup      | Duplicates a file descriptor                                             |
| dup2         | man 2 dup2     | Duplicates a file descriptor to a specified new descriptor               |
| execve       | man 2 execve   | Executes a program                                                       |
| exit         | man 3 exit     | Terminates the calling process                                           |
| fork         | man 2 fork     | Creates a new process                                                    |
| pipe         | man 2 pipe     | Creates a pipe, a unidirectional communication channel                   |
| unlink       | man 2 unlink   | Deletes a name from the filesystem                                       |
| wait         | man 2 wait     | Waits for a child process to terminate                                   |
| waitpid      | man 2 waitpid  | Waits for a specific child process to terminate                          |

<br>

Made by <a href="https://github.com/Szabold1" target="_blank">Boldizsar Szabo</a>

&#xa0;

<a href="#top">Back to top</a>
