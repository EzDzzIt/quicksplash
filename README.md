# quicksplash

Simple sdl2 program to show an image; specifically for aarch64-based Linux handhelds.

Planning to expand functionality to be able to set custom text, progress through multiple screens, set custom resolution, etc.

## *Compilation*

I am compiling on Ubuntu using:

aarch64-linux-gnu-g++ -o splash splash.c $(sdl2-config --cflags --libs) -lSDL2_image

Just make sure your compiler has a clear path to the SDL libs.

requires sdl2-dev, sdl2-image

## *Usage*

$ chmod +x splash  
$ ./splash <path_to_image> <delay_time (optional)>  
