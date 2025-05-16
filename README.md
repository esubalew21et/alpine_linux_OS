# alpine_linux_OS
Alpine_Linux_operating-system

installation

To install Alpine Linux, I used VirtualBox to create a virtual machine. I downloaded the standard ISO from the official Alpine website. 
After attaching the ISO to the VM, I booted into the Alpine setup. The interface was command-line based, but the instructions were clear. 
I set up networking with setup-alpine, chose a keyboard layout, selected a mirror, and configured the disk with the guided installer.
I used the default settings for most options, including sys disk mode. Then I set the hostname, timezone, and created a user account.
Once the installation was complete, I ran reboot, removed the ISO, and booted into my Alpine Linux system for the first time. 
It was minimal and fast, and the whole experience helped me understand lightweight Linux setups better.
package management
Alpine Linux uses the apk package manager. 
It's simple and fast. To update the package index, I used:
apk update
To install a package, the command is:
apk add <package-name>
For example, I installed nano like this:
apk add nano
I also used apk info to check installed packages and apk del to remove them. Working with apk taught me how minimalist systems handle software installation efficiently.

system call

A system call in Alpine Linux works the same way as in other UNIX-like systems. It's how a program interacts with the kernel, like reading files or creating processes.
Since Alpine uses musl libc instead of glibc, the system calls are handled slightly differently at the library level, but conceptually they are the same. 
While exploring system calls, I tried running a simple C program that used open() and write() system calls. 
This helped me see how applications communicate with the operating system, and I started to understand how Alpine remains small yet powerful by using essential system-level tools.
