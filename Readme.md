# File Descriptor Omission Attack

There is nothing special about stdin, stdout, and stderr.
They are just the file descriptors 0, 1, and 2.

A program is not guaranteed to start with the standard streams.
It is possible for a program to close them, and then exec to another program.
This used to be an attack class for older Unix operating systems, but nowadays glibc will prevent the standard fds from being closed on setuid/setgid programs.

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
fcntl(0, F_GETFD)                       = -1 EBADF (Bad file descriptor)
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

[OpenBSD advisory](https://www.freebsd.org/security/advisories/FreeBSD-SA-02:23.stdio.asc)
