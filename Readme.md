Testing:
```
./build.sh
./show_open
strace ./fd_omit
```

Quoting "The Art of Software Security Assessment"
```
Every time a process opens a new file or object that causes the creation of a file descriptor, that descriptor is placed in the process’s file descriptor table at the lowest available numerical position. For example, say a process has file descriptors 1, 2, 3, 4, and 5 open. If it closes file descriptors 2 and 4, the next file descriptor that gets created is 2, and the file descriptor created after that is 4.

There’s a convention in the UNIX library code that the first three file descriptors are special: File descriptor 0 is standard input, file descriptor 1 is standard output, and file descriptor 2 is standard error. As you might expect, there have been security vulnerabilities related to these assumptions. In general, if you open a file that is assigned a file descriptor lower than 3, library code might assume your file is one of the standard I/O descriptors. If it does, it could end up writing program output or error messages into your file or reading program input from your file.
```
