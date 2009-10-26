Introduction
~~~~~~~~~~~~
This is an unofficial recreation of one of my favorite rpg games in history.

System Requirements
~~~~~~~~~~~~~~~~~~~
Linux/UNIX (preferrably Arch) computer with at least 1GHz processor. I will 
not create a makefile for or test this game on Windows (How does it feel to not
 have support for your platform?). I'm sure Mac will work fine also.

If the make file doesn't compile on your distro type allegro-config --static
at the command line. Open the makefile in an editor and comment out my 
ALLEG macro line. I will include both the working lines for ubuntu 9.04 and 
Arch linux just comment out the one you want, or add one using my examples
and the output of the above command as a guideline.

Required software: make, gcc, and the allegro libraries installed. Allegro
is available by way of pacman if you use Arch. If you don't, you should 
switch immediately: http://archlinux.org.

How to play
~~~~~~~~~~~
We'll get there. For now just use the arrows to move around. Escape exits the 
game.

How to run
~~~~~~~~~~~~~~
Linux/UNIX/Mac:
make
./dragonfighter

Windows:
Get a real operating system then run the above commands.
