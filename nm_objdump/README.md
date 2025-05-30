# Project 2216: C - ELF: nm/objdump
----

## Resources

**Read or watch**:

* [ELF Wikipedia](https://en.wikipedia.org/wiki/Executable_and_Linkable_Format)
* [ELF](https://stevens.netmeister.org/631/elf.html)
* [Executable and Linkable Format (ELF)](https://www.cs.cmu.edu/afs/cs/academic/class/15213-f00/docs/elf.pdf)
* [The ELF Object File Format: Introduction](https://www.linuxjournal.com/article/1059)
* [The ELF Object File Format by Dissection](https://www.linuxjournal.com/article/1060)

**man or help**:

* `elf (5)`
* `nm (1)`
* `objdump (1)`
## Learning Objectives

At the end of this project, you are expected to be able to[explain to anyone](https://fs.blog/feynman-learning-technique/),**without the help of Google**:

### General

* What is the ELF format
* What are the commands`nm`and`objdump`
* How to use them properly
* How to parse the content of an`ELF`file
* What information can be extracted from an`ELF`file
* What are the differences between`nm`and`objdump`
## Requirements

### General

* Allowed editors:`vi`,`vim`,`emacs`
* All your files will be compiled on Ubuntu 20.04 LTS
* Your C programs and functions will be compiled with`gcc 9.4.0`using the flags`-Wall``-Werror``-Wextra``and -pedantic`
* All your files should end with a new line
* A`README.md`file, at the root of the folder of the project, is mandatory
* Your code should use the`Betty`style. It will be checked using[betty-style.pl](https://github.com/hs-hq/Betty/blob/master/betty-style.pl)and[betty-doc.pl](https://github.com/hs-hq/Betty/blob/master/betty-doc.pl)
* You are not allowed to have more than 5 functions per file
* All your header files should be include guarded
### Allowed Functions and System Calls

* Unless specified otherwise, you are allowed to use the C standard library
* You’re not allowed to use`system`(3)
* You’re not allowed to use`exec*`(2 and 3)
### Tests

* Your program must be able to handle both 32-bit and 64-bit ELF files
* Your program must be able to handle both little and big endian ELF files
* Your program must be able to handle all types of ELF files
## More Info

See also`/usr/include/elf.h`


----
## Tasks
---
### 0. nm

Write a program that reproduces the <!--plain-NL-->`GNU nm`<!--inline-NL--> command<!--plain-NL-->

- Usage: `hnm [objfile ...]`
- The output should be the exact same as `nm -p`
- Your sources must be compiled and linked using a `Makefile`

Your makefile must define the rule <!--plain-NL-->`hnm`<!--inline-NL--> and compile the needed sources to form the executable <!--plain-NL-->`hnm`<!--inline-NL-->

```
alex@~/nm_objdump$ ./hnm elf_files/ubuntu64
0000000000600e20 d __JCR_LIST__
0000000000400630 t deregister_tm_clones
0000000000400670 t register_tm_clones
00000000004006b0 t __do_global_dtors_aux
0000000000601068 b completed.7585
0000000000600e18 t __do_global_dtors_aux_fini_array_entry
00000000004006d0 t frame_dummy
0000000000600e10 t __frame_dummy_init_array_entry
0000000000400b20 r __FRAME_END__
0000000000600e20 d __JCR_END__
0000000000600e18 t __init_array_end
0000000000600e28 d _DYNAMIC
0000000000600e10 t __init_array_start
00000000004009f8 r __GNU_EH_FRAME_HDR
0000000000601000 d _GLOBAL_OFFSET_TABLE_
0000000000400980 T __libc_csu_fini
                 w _ITM_deregisterTMCloneTable
0000000000601058 W data_start
                 U write@@GLIBC_2.2.5
0000000000601068 D _edata
0000000000400984 T _fini
                 U __stack_chk_fail@@GLIBC_2.4
                 U close@@GLIBC_2.2.5
                 U dprintf@@GLIBC_2.2.5
                 U read@@GLIBC_2.2.5
                 U __libc_start_main@@GLIBC_2.2.5
0000000000601058 D __data_start
                 w __gmon_start__
0000000000601060 D __dso_handle
0000000000400990 R _IO_stdin_used
0000000000400910 T __libc_csu_init
0000000000601070 B _end
0000000000400600 T _start
0000000000601068 B __bss_start
00000000004006f6 T main
                 U open@@GLIBC_2.2.5
                 w _Jv_RegisterClasses
                 U exit@@GLIBC_2.2.5
0000000000601068 D __TMC_END__
                 w _ITM_registerTMCloneTable
0000000000400540 T _init
alex@~/nm_objdump$ ./hnm elf_files/netbsd32
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
alex@~/nm_objdump$

```

**Repo:**

- GitHub repository: `atlas-system_linux`
- Directory: `nm_objdump`
- File: `Makefile`


---
### 1. objdump -sf

Write a program that reproduces the <!--plain-NL-->`GNU objdump`<!--inline-NL--> command<!--plain-NL-->

- Usage: `hobjdump [objfile ...]`
- The output should be the exact same as `objdump -sf`
- Your sources must be compiled and linked using a `Makefile`

Your makefile must define the rule <!--plain-NL-->`hobjdump`<!--inline-NL--> and compile the needed sources to form the executable <!--plain-NL-->`hobjdump`<!--inline-NL-->

```
alex@~/nm_objdump$ ./hobjdump elf_files/ubuntu64

elf_files/ubuntu64:     file format elf64-x86-64
architecture: i386:x86-64, flags 0x00000112:
EXEC_P, HAS_SYMS, D_PAGED
start address 0x0000000000400600

Contents of section .interp:
 400238 2f6c6962 36342f6c 642d6c69 6e75782d  /lib64/ld-linux-
 400248 7838362d 36342e73 6f2e3200           x86-64.so.2.
Contents of section .note.ABI-tag:
 400254 04000000 10000000 01000000 474e5500  ............GNU.
 400264 00000000 02000000 06000000 20000000  ............ ...
Contents of section .note.gnu.build-id:
 400274 04000000 14000000 03000000 474e5500  ............GNU.
 400284 d74b66f2 ac1e252c b3dce6c0 1303871c  .Kf...%,........
 400294 b789ca60                             ...`
Contents of section .gnu.hash:
 400298 01000000 01000000 01000000 00000000  ................
 4002a8 00000000 00000000 00000000           ............
Contents of section .dynsym:
 4002b8 00000000 00000000 00000000 00000000  ................
 4002c8 00000000 00000000 4b000000 12000000  ........K.......
 4002d8 00000000 00000000 00000000 00000000  ................
 4002e8 18000000 12000000 00000000 00000000  ................
 4002f8 00000000 00000000 2e000000 12000000  ................
 400308 00000000 00000000 00000000 00000000  ................
 400318 0b000000 12000000 00000000 00000000  ................
 400328 00000000 00000000 29000000 12000000  ........).......
 400338 00000000 00000000 00000000 00000000  ................
 400348 39000000 12000000 00000000 00000000  9...............
 400358 00000000 00000000 51000000 20000000  ........Q... ...
 400368 00000000 00000000 00000000 00000000  ................
 400378 34000000 12000000 00000000 00000000  4...............
 400388 00000000 00000000 13000000 12000000  ................
 400398 00000000 00000000 00000000 00000000  ................
Contents of section .dynstr:
 4003a8 006c6962 632e736f 2e360064 7072696e  .libc.so.6.dprin
 4003b8 74660065 78697400 5f5f7374 61636b5f  tf.exit.__stack_
 4003c8 63686b5f 6661696c 00726561 6400636c  chk_fail.read.cl
 4003d8 6f736500 6f70656e 005f5f6c 6962635f  ose.open.__libc_
 4003e8 73746172 745f6d61 696e0077 72697465  start_main.write
 4003f8 005f5f67 6d6f6e5f 73746172 745f5f00  .__gmon_start__.
 400408 474c4942 435f322e 3400474c 4942435f  GLIBC_2.4.GLIBC_
 400418 322e322e 3500                        2.2.5.
Contents of section .gnu.version:
 40041e 00000200 03000200 02000200 02000000  ................
 40042e 02000200                             ....
Contents of section .gnu.version_r:
 400438 01000200 01000000 10000000 00000000  ................
 400448 1469690d 00000300 60000000 10000000  .ii.....`.......
 400458 751a6909 00000200 6a000000 00000000  u.i.....j.......
Contents of section .rela.dyn:
 400468 f80f6000 00000000 06000000 07000000  ..`.............
 400478 00000000 00000000                    ........
Contents of section .rela.plt:
 400480 18106000 00000000 07000000 01000000  ..`.............
 400490 00000000 00000000 20106000 00000000  ........ .`.....
 4004a0 07000000 02000000 00000000 00000000  ................
 4004b0 28106000 00000000 07000000 03000000  (.`.............
 4004c0 00000000 00000000 30106000 00000000  ........0.`.....
 4004d0 07000000 04000000 00000000 00000000  ................
 4004e0 38106000 00000000 07000000 05000000  8.`.............
 4004f0 00000000 00000000 40106000 00000000  ........@.`.....
 400500 07000000 06000000 00000000 00000000  ................
 400510 48106000 00000000 07000000 08000000  H.`.............
 400520 00000000 00000000 50106000 00000000  ........P.`.....
 400530 07000000 09000000 00000000 00000000  ................
Contents of section .init:
 400540 4883ec08 488b05ad 0a200048 85c07405  H...H.... .H..t.
 400550 e89b0000 004883c4 08c3               .....H....
Contents of section .plt:
 400560 ff35a20a 2000ff25 a40a2000 0f1f4000  .5.. ..%.. ...@.
 400570 ff25a20a 20006800 000000e9 e0ffffff  .%.. .h.........
 400580 ff259a0a 20006801 000000e9 d0ffffff  .%.. .h.........
 400590 ff25920a 20006802 000000e9 c0ffffff  .%.. .h.........
 4005a0 ff258a0a 20006803 000000e9 b0ffffff  .%.. .h.........
 4005b0 ff25820a 20006804 000000e9 a0ffffff  .%.. .h.........
 4005c0 ff257a0a 20006805 000000e9 90ffffff  .%z. .h.........
 4005d0 ff25720a 20006806 000000e9 80ffffff  .%r. .h.........
 4005e0 ff256a0a 20006807 000000e9 70ffffff  .%j. .h.....p...
Contents of section .plt.got:
 4005f0 ff25020a 20006690                    .%.. .f.
Contents of section .text:
 400600 31ed4989 d15e4889 e24883e4 f0505449  1.I..^H..H...PTI
 400610 c7c08009 400048c7 c1100940 0048c7c7  ....@.H....@.H..
 400620 f6064000 e897ffff fff4660f 1f440000  ..@.......f..D..
 400630 b86f1060 0055482d 68106000 4883f80e  .o.`.UH-h.`.H...
 400640 4889e576 1bb80000 00004885 c074115d  H..v......H..t.]
 400650 bf681060 00ffe066 0f1f8400 00000000  .h.`...f........
 400660 5dc30f1f 4000662e 0f1f8400 00000000  ]...@.f.........
 400670 be681060 00554881 ee681060 0048c1fe  .h.`.UH..h.`.H..
 400680 034889e5 4889f048 c1e83f48 01c648d1  .H..H..H..?H..H.
 400690 fe7415b8 00000000 4885c074 0b5dbf68  .t......H..t.].h
 4006a0 106000ff e00f1f00 5dc3660f 1f440000  .`......].f..D..
 4006b0 803db109 20000075 11554889 e5e86eff  .=.. ..u.UH...n.
 4006c0 ffff5dc6 059e0920 0001f3c3 0f1f4000  ..].... ......@.
 4006d0 bf200e60 0048833f 007505eb 930f1f00  . .`.H.?.u......
 4006e0 b8000000 004885c0 74f15548 89e5ffd0  .....H..t.UH....
 4006f0 5de97aff ffff5548 89e54881 ec400400  ].z...UH..H..@..
 400700 0089bdcc fbffff48 89b5c0fb ffff6448  .......H......dH
 400710 8b042528 00000048 8945f831 c083bdcc  ..%(...H.E.1....
 400720 fbffff03 741ebe98 094000bf 02000000  ....t....@......
 400730 b8000000 00e866fe ffffbf61 000000e8  ......f....a....
 400740 9cfeffff 488b85c0 fbffff48 83c00848  ....H......H...H
 400750 8b00be00 00000048 89c7b800 000000e8  .......H........
 400760 6cfeffff 8985d8fb ffff83bd d8fbffff  l...............
 400770 ff752f48 8b85c0fb ffff4883 c008488b  .u/H......H...H.
 400780 004889c2 beb80940 00bf0200 0000b800  .H.....@........
 400790 000000e8 08feffff bf620000 00e83efe  .........b....>.
 4007a0 ffff488b 85c0fbff ff4883c0 10488b00  ..H......H...H..
 4007b0 bab40100 00be4102 00004889 c7b80000  ......A...H.....
 4007c0 0000e809 feffff89 85dcfbff ff83bddc  ................
 4007d0 fbffffff 0f859300 0000488b 85c0fbff  ..........H.....
 4007e0 ff4883c0 10488b00 4889c2be d8094000  .H...H..H.....@.
 4007f0 bf020000 00b80000 0000e8a1 fdffffbf  ................
 400800 63000000 e8d7fdff ff488b95 e0fbffff  c........H......
 400810 488d8df0 fbffff8b 85dcfbff ff4889ce  H............H..
 400820 89c7e849 fdffff48 8985e8fb ffff488b  ...I...H......H.
 400830 85e0fbff ff483b85 e8fbffff 742f488b  .....H;.....t/H.
 400840 85c0fbff ff4883c0 10488b00 4889c2be  .....H...H..H...
 400850 d8094000 bf020000 00b80000 0000e83d  ..@............=
 400860 fdffffbf 63000000 e873fdff ff488d8d  ....c....s...H..
 400870 f0fbffff 8b85d8fb ffffba00 04000048  ...............H
 400880 89ce89c7 e827fdff ff488985 e0fbffff  .....'...H......
 400890 4883bde0 fbffff00 0f8f6bff ffff4883  H.........k...H.
 4008a0 bde0fbff ffff752f 488b85c0 fbffff48  ......u/H......H
 4008b0 83c00848 8b004889 c2beb809 4000bf02  ...H..H.....@...
 4008c0 000000b8 00000000 e8d3fcff ffbf6200  ..............b.
 4008d0 0000e809 fdffff8b 85d8fbff ff89c7e8  ................
 4008e0 acfcffff 8b85dcfb ffff89c7 e89ffcff  ................
 4008f0 ffb80100 0000488b 4df86448 330c2528  ......H.M.dH3.%(
 400900 00000074 05e876fc ffffc9c3 0f1f4000  ...t..v.......@.
 400910 41574156 4189ff41 5541544c 8d25ee04  AWAVA..AUATL.%..
 400920 20005548 8d2dee04 20005349 89f64989   .UH.-.. .SI..I.
 400930 d54c29e5 4883ec08 48c1fd03 e8fffbff  .L).H...H.......
 400940 ff4885ed 742031db 0f1f8400 00000000  .H..t 1.........
 400950 4c89ea4c 89f64489 ff41ff14 dc4883c3  L..L..D..A...H..
 400960 014839eb 75ea4883 c4085b5d 415c415d  .H9.u.H...[]A\A]
 400970 415e415f c390662e 0f1f8400 00000000  A^A_..f.........
 400980 f3c3                                 ..
Contents of section .fini:
 400984 4883ec08 4883c408 c3                 H...H....
Contents of section .rodata:
 400990 01000200 00000000 55736167 653a2063  ........Usage: c
 4009a0 70206669 6c656e61 6d652074 6578740a  p filename text.
 4009b0 00000000 00000000 4572726f 723a2043  ........Error: C
 4009c0 616e2774 20726561 64206672 6f6d2066  an't read from f
 4009d0 696c6520 25730a00 4572726f 723a2043  ile %s..Error: C
 4009e0 616e2774 20777269 74652074 6f206669  an't write to fi
 4009f0 6c652025 730a00                      le %s..
Contents of section .eh_frame_hdr:
 4009f8 011b033b 34000000 05000000 68fbffff  ...;4.......h...
 400a08 80000000 08fcffff 50000000 fefcffff  ........P.......
 400a18 a8000000 18ffffff c8000000 88ffffff  ................
 400a28 10010000                             ....
Contents of section .eh_frame:
 400a30 14000000 00000000 017a5200 01781001  .........zR..x..
 400a40 1b0c0708 90010710 14000000 1c000000  ................
 400a50 b0fbffff 2a000000 00000000 00000000  ....*...........
 400a60 14000000 00000000 017a5200 01781001  .........zR..x..
 400a70 1b0c0708 90010000 24000000 1c000000  ........$.......
 400a80 e0faffff 90000000 000e1046 0e184a0f  ...........F..J.
 400a90 0b770880 003f1a3b 2a332422 00000000  .w...?.;*3$"....
 400aa0 1c000000 44000000 4efcffff 16020000  ....D...N.......
 400ab0 00410e10 8602430d 06031102 0c070800  .A....C.........
 400ac0 44000000 64000000 48feffff 65000000  D...d...H...e...
 400ad0 00420e10 8f02420e 188e0345 0e208d04  .B....B....E. ..
 400ae0 420e288c 05480e30 8606480e 3883074d  B.(..H.0..H.8..M
 400af0 0e40720e 38410e30 410e2842 0e20420e  .@r.8A.0A.(B. B.
 400b00 18420e10 420e0800 14000000 ac000000  .B..B...........
 400b10 70feffff 02000000 00000000 00000000  p...............
 400b20 00000000                             ....
Contents of section .init_array:
 600e10 d0064000 00000000                    ..@.....
Contents of section .fini_array:
 600e18 b0064000 00000000                    ..@.....
Contents of section .jcr:
 600e20 00000000 00000000                    ........
Contents of section .dynamic:
 600e28 01000000 00000000 01000000 00000000  ................
 600e38 0c000000 00000000 40054000 00000000  ........@.@.....
 600e48 0d000000 00000000 84094000 00000000  ..........@.....
 600e58 19000000 00000000 100e6000 00000000  ..........`.....
 600e68 1b000000 00000000 08000000 00000000  ................
 600e78 1a000000 00000000 180e6000 00000000  ..........`.....
 600e88 1c000000 00000000 08000000 00000000  ................
 600e98 f5feff6f 00000000 98024000 00000000  ...o......@.....
 600ea8 05000000 00000000 a8034000 00000000  ..........@.....
 600eb8 06000000 00000000 b8024000 00000000  ..........@.....
 600ec8 0a000000 00000000 76000000 00000000  ........v.......
 600ed8 0b000000 00000000 18000000 00000000  ................
 600ee8 15000000 00000000 00000000 00000000  ................
 600ef8 03000000 00000000 00106000 00000000  ..........`.....
 600f08 02000000 00000000 c0000000 00000000  ................
 600f18 14000000 00000000 07000000 00000000  ................
 600f28 17000000 00000000 80044000 00000000  ..........@.....
 600f38 07000000 00000000 68044000 00000000  ........h.@.....
 600f48 08000000 00000000 18000000 00000000  ................
 600f58 09000000 00000000 18000000 00000000  ................
 600f68 feffff6f 00000000 38044000 00000000  ...o....8.@.....
 600f78 ffffff6f 00000000 01000000 00000000  ...o............
 600f88 f0ffff6f 00000000 1e044000 00000000  ...o......@.....
 600f98 00000000 00000000 00000000 00000000  ................
 600fa8 00000000 00000000 00000000 00000000  ................
 600fb8 00000000 00000000 00000000 00000000  ................
 600fc8 00000000 00000000 00000000 00000000  ................
 600fd8 00000000 00000000 00000000 00000000  ................
 600fe8 00000000 00000000 00000000 00000000  ................
Contents of section .got:
 600ff8 00000000 00000000                    ........
Contents of section .got.plt:
 601000 280e6000 00000000 00000000 00000000  (.`.............
 601010 00000000 00000000 76054000 00000000  ........v.@.....
 601020 86054000 00000000 96054000 00000000  ..@.......@.....
 601030 a6054000 00000000 b6054000 00000000  ..@.......@.....
 601040 c6054000 00000000 d6054000 00000000  ..@.......@.....
 601050 e6054000 00000000                    ..@.....
Contents of section .data:
 601058 00000000 00000000 00000000 00000000  ................
Contents of section .comment:
 0000 4743433a 20285562 756e7475 20352e34  GCC: (Ubuntu 5.4
 0010 2e302d36 7562756e 7475317e 31362e30  .0-6ubuntu1~16.0
 0020 342e3429 20352e34 2e302032 30313630  4.4) 5.4.0 20160
 0030 36303900                             609.
alex@~/nm_objdump$

```

**Repo:**

- GitHub repository: `atlas-system_linux`
- Directory: `nm_objdump`
- File: `Makefile`


---
### 2. Blog post

Write a blog post about the <!--plain-NL-->`ELF`<!--inline-NL--> format<!--plain-NL-->

Your blog post should cover the following:<!--plain-NL-->

- What is `ELF`
- Why it is used
- What information is stored in it
- How this information is stored
- How to parse this information
- Describe the `readelf` command
- Describe the `nm` command
- Describe the `objdump` command

Your posts should have examples and at least one picture, at the top. Publish your blog post on <!--plain-NL-->`Medium`<!--inline-NL--> or <!--plain-NL-->`LinkedIn`<!--inline-NL-->, and share it at least on <!--plain-NL-->`Twitter`<!--inline-NL--> and <!--plain-NL-->`LinkedIn`<!--inline-NL-->.<!--plain-NL-->

When done, please add all urls below (blog post, tweet, etc.)<!--plain-NL-->

Please, remember that these blogs must be written in English to further your technical ability in a variety of settings.<!--plain-NL-->
