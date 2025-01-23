# strace

A Linux based shell command to read system calls of executables

## Description

This is a simple clone of the strace command that comes standard in linux distributions. It runs an executable, printing every system call, their arguments given and returned values as they happen in real time, which is incredibly handy data when troubleshooting code.

## Environment

strace was designed in and to be run on POSIX compliant distros (specifically Ubuntu 22.04)

## How to Install and Run

1. Clone the repository `git clone https://github.com/DaveyCHaysIII/strace`
2. In your terminal, run `gcc strace_x.c -o strace_x` // 0 for call numbers, 1 for names, 2 for complete data
3. In your terminal, run `./strace_x <file>`

## Output

strace will output at the beginning and end of every system call of an executable, giving us access to not only the call itself but also its return value.

Example:

```
$ ./strace_3 /testing/helo

execve(0, 0, 0) = 0
brk(0) = 0x5ec59457c000
arch_prctl(0x3001, 0x7ffc08ce5610) = 0xffffffffffffffea
mmap(0, 0x2000, 0x3, 0x22, 0xffffffff, 0) = 0x7b333f409000
access(0x7b333f43ad90, 0x4) = 0xfffffffffffffffe
openat(0xffffff9c, 0x7b333f43921b, 0x80000) = 0x3
newfstatat(0) = 0
mmap(0, 0x105ab, 0x1, 0x2, 0x3, 0) = 0x7b333f3f8000
close(0x3) = 0
openat(0xffffff9c, 0x7b333f409140, 0x80000) = 0x3
read(0x3, 0x7ffc08ce4998, 0x340) = 0x340
pread64(0x3, 0x7ffc08ce45a0, 0x310, 0x40) = 0x310
pread64(0x3, 0x7ffc08ce4560, 0x30, 0x350) = 0x30
pread64(0x3, 0x7ffc08ce4510, 0x44, 0x380) = 0x44
newfstatat(0) = 0
pread64(0x3, 0x7ffc08ce4470, 0x310, 0x40) = 0x310
mmap(0, 0x228e50, 0x1, 0x802, 0x3, 0) = 0x7b333f000000
mprotect(0x7b333f028000, 0x1ee000, 0) = 0
mmap(0x7b333f028000, 0x195000, 0x5, 0x812, 0x3, 0x28000) = 0x7b333f028000
mmap(0x7b333f1bd000, 0x58000, 0x1, 0x812, 0x3, 0x1bd000) = 0x7b333f1bd000
mmap(0x7b333f216000, 0x6000, 0x3, 0x812, 0x3, 0x215000) = 0x7b333f216000
mmap(0x7b333f21c000, 0xce50, 0x3, 0x32, 0xffffffff, 0) = 0x7b333f21c000
close(0x3) = 0
mmap(0, 0x3000, 0x3, 0x22, 0xffffffff, 0) = 0x7b333f3f5000
arch_prctl(0x1002, 0x7b333f3f5740) = 0
set_tid_address(0x7b333f3f5a10) = 0x1435
set_robust_list(0x7b333f3f5a20, 0x18) = 0
rseq(0) = 0
mprotect(0x7b333f216000, 0x4000, 0x1) = 0
mprotect(0x5ec568337000, 0x1000, 0x1) = 0
mprotect(0x7b333f443000, 0x2000, 0x1) = 0
prlimit64(0) = 0
munmap(0x7b333f3f8000, 0x105ab) = 0
newfstatat(0) = 0
getRandom(0) = 0x8
brk(0) = 0x5ec59457c000
brk(0x5ec59459d000) = 0x5ec59459d000
write(0x1, 0x5ec59457c2a0, 0xc) Hello world!= 0xc
exit_group(0) = ?



```

