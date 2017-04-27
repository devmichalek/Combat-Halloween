[![bar](https://cloud.githubusercontent.com/assets/19840443/25200350/4d0039c2-254e-11e7-906d-5fd63c3f76ee.png)](https://youtu.be/F4lgM118sAE)
[![linux](https://cloud.githubusercontent.com/assets/19840443/25199468/3b54c178-254b-11e7-9d29-7f582afc42d9.png)](https://drive.google.com/uc?export=download&id=0B36D1JHNNqr-cWNhOFhqQ0RjSk0)
[![windows](https://cloud.githubusercontent.com/assets/19840443/25199497/515257ba-254b-11e7-89d8-d3ce908ba02f.png)](https://drive.google.com/uc?export=download&id=0B36D1JHNNqr-MGJmamFyRzlja28)
[![code](https://cloud.githubusercontent.com/assets/19840443/25199629/bf2eb86e-254b-11e7-9cf7-52199eaf50a6.png)](https://drive.google.com/uc?export=download&id=0B36D1JHNNqr-LVhidzZnQjFEZ0U)
[![data](https://cloud.githubusercontent.com/assets/19840443/25199526/682e43b8-254b-11e7-889f-d61a7ce0aa80.png)](https://drive.google.com/uc?export=download&id=0B36D1JHNNqr-Rks3TmFMaWt5bTQ)
[![dll](https://cloud.githubusercontent.com/assets/19840443/25199506/5bf2a698-254b-11e7-95b0-1d6e6e1d33d6.png)](https://drive.google.com/uc?export=download&id=0B36D1JHNNqr-YmJhaWxXWUdDM3c)
<br/>
<br/>
<br/>
## About
First of all Assassin's Genesis is not the next version of Assassin's Creed. Unfortunately Ubisoft didn't pay me any money, so basically I don't care about them. All you need to know that this project is made with my own fair hands and I'm proud of it. It's created via SFML multimedia and SDL_Mixer audio library completed with c++ language. Two frustrating things is no-rezising window and no-checking files before application starts. I wish I finished this project soon but now just try what I have. Btw remember that there are no bugs there are features!
<br/>
<br/>
<br/>
## Download
Application is available for windows users and linux-familiar people. You have two buttons under the picture, choose one of them to download. You might want to download only pictures, .mp3, .wav etc. files then just click on button with label "files". Whole code is forthcoming, click on button "code". The last button gives you .dll files. 
<br/>
<br/>
<br/>
## For involved
I used [this](https://www.sfml-dev.org/files/SFML-2.4.2-windows-gcc-6.1.0-mingw-32-bit.zip) SFML 2.4.2 (GCC 6.1.0 MinGW (DW2) - 32-bit) according to [this](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/6.1.0/threads-posix/dwarf/i686-6.1.0-release-posix-dwarf-rt_v5-rev0.7z/download) compiler (MinGW Builds 6.1.0 (32-bit)).

# Try Assembly on Linux

## Install nasm
We need **nasm** to create object file by assembly code. [Wikipedia](https://en.wikipedia.org/wiki/Netwide_Assembler "Click me!") says: **nasm** is an assembler and disassembler for the Intel x86 architecture. It can be used to write 16-bit, 32-bit (IA-32) and 64-bit (x86-64) programs. NASM is considered to be one of the most popular assemblers for Linux. Try <br/>
```
sudo apt install nasm
```
<br/>
## Create asm file
We want to see results so just copy the code below and save as "main.asm". Code is from ![logo](https://cloud.githubusercontent.com/assets/19840443/19013290/f3fcb338-87cc-11e6-96a5-eaa50f0c0aca.png)<br/>
``` 
section	.text
    global _start   ;must be declared for linker (ld)
_start:	            ;tells linker entry point
    mov	edx,len     ;message length
    mov	ecx,msg     ;message to write
    mov	ebx,1       ;file descriptor (stdout)
    mov	eax,4       ;system call number (sys_write)
    int	0x80        ;call kernel
	
    mov	eax,1       ;system call number (sys_exit)
    int	0x80        ;call kernel

section	.data
msg db 'Hello, world!', 0xa  ;string to be printed
len equ $ - msg     ;length of the string
```
<br/>
## Create object file
