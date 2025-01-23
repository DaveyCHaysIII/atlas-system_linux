# HNM

A Linux based shell command to read symbols of executables

## Description

This is a simple clone of the nm command that comes standard in linux distributions. It runs an
executable, printing every symbol in the elf file.

## Environment

hnm was designed in and to be run on POSIX compliant distros (specifically Ubuntu 22.04)

## How to Install and Run

1. Clone the repository `git clone https://github.com/DaveyCHaysIII/nm_objdump`
2. In your terminal, run `make'
3. In your terminal, run `./hnm <file>`

## Output

Example:

```
$ ./hnm elf_files/exec/netbsd32

0804858c t _strrchr
080487c4 t gcc2_compiled.
         U __syscall
080486cc W dlerror
08049988 B __mainprog_obj
08048700 T _dladdr
08049900 A _DYNAMIC
08048660 T _dlclose
080487c4 A _etext
08048698 T _dlsym
08048700 W dladdr
08048660 W dlclose
08048440 T _init
0804862c T _dlopen
0804998c B environ
080484c0 T __start
080486cc T _dlerror
080498a8 D __progname
080484c0 T _start
0804862c W dlopen
08048698 W dlsym
08049988 A __bss_start
08049990 B main
080487c4 T _fini
         U atexit
080484d8 T ___start
08049988 A _edata
080498cc A _GLOBAL_OFFSET_TABLE_
08049994 A _end
080498ac D __ps_strings
         U exit
080485b8 T _rtld_setup

```
