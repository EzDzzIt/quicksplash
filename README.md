# quicksplash

 simple sdl2 program to show an image; specifically for aarch64-based linux handhelds

## *compilation*

I am compiling on Ubuntu using:

aarch64-linux-gnu-g++ -o splash splash.c $(sdl2-config --cflags --libs) -lSDL2_image

requires sdl2-dev, sdl2-image

## *usage*

$ chmod +x splash  
$ ./splash <path_to_image> <delay_time (optional)>  
