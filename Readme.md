# File Descriptor Omission Attack

There is nothing special about stdin, stdout, and stderr.
They are just the file descriptors 0, 1, and 2.

A program is not guaranteed to start with the standard streams.
It is possible for a program to close them, and then exec to another program.

Testing:
```
./build.sh
./show_open
strace ./fd_omit
```

Show open should show:
```
FD 0: 0
FD 1: 0
FD 2: 0
FD 3: -1
...
```

Running fd_omit with strace:
```
...
fcntl(1, F_GETFD)                       = -1 EBADF (Bad file descriptor)
fcntl(2, F_GETFD)                       = -1 EBADF (Bad file descriptor)
fcntl(3, F_GETFD)                       = -1 EBADF (Bad file descriptor)
fcntl(4, F_GETFD)                       = -1 EBADF (Bad file descriptor)
fcntl(5, F_GETFD)                       = -1 EBADF (Bad file descriptor)
fcntl(6, F_GETFD)                       = -1 EBADF (Bad file descriptor)
fcntl(7, F_GETFD)                       = -1 EBADF (Bad file descriptor)
fcntl(8, F_GETFD)                       = -1 EBADF (Bad file descriptor)
fcntl(9, F_GETFD)                       = -1 EBADF (Bad file descriptor)
write(1, "FD 0: -1\nFD 1: -1\nFD 2: -1\nFD 3:"..., 90) = -1 EBADF (Bad file descriptor)
```

This is dangerous for setuid/setgid programs.
If the file descriptor 3 is closed, then calls to `fprintf(stderr...)` will end up writing to the first application opened file.



From "The Art of Software Security Assessment"

> Many modern UNIX distributions have addressed this issue via modifications to the kernel or the C libraries. Typically, they make sure that when a new process runs, all three of its first file descriptors are allocated. If any aren’t, the fixes usually open the /dev/null device driver for the missing descriptors.

This does not seem to be true on Linux.
I don't find many references to this attack class, but anyone can exec a setuid program on Linux with stdin, stdout, or stderr closed.

[OpenBSD advisory](https://www.freebsd.org/security/advisories/FreeBSD-SA-02:23.stdio.asc)
