#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

// Function to scale the sprite based on window dimensions
SDL_Rect scaleSprite(SDL_Rect spriteRect, int windowWidth, int windowHeight) {
    SDL_Rect scaledRect;
    
    // Maintain aspect ratio
    float spriteAspect = (float)spriteRect.w / (float)spriteRect.h;
    float windowAspect = (float)windowWidth / (float)windowHeight;

    if (windowAspect > spriteAspect) {
        // Window is wider relative to its height
        scaledRect.w = windowHeight * spriteAspect;
        scaledRect.h = windowHeight;
    } else {
        // Window is taller relative to its width
        scaledRect.w = windowWidth;
        scaledRect.h = windowWidth / spriteAspect;
    }

    // Center the sprite
    scaledRect.x = (windowWidth - scaledRect.w) / 2;
    scaledRect.y = (windowHeight - scaledRect.h) / 2;

    return scaledRect;
}

int main(int argc, char *argv[]) {
    // Check for proper argument count
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <sprite_path> <splash_delay> \n", argv[0]);
        return 1;
    }

    const char *spritePath = argv[1];
    //default is 5000ms
    int splashDelay = 5000;
    //optional argument for splash delay time
    if (argv[2] != NULL && atoi(argv[2]) > 0) {
        splashDelay = atoi(argv[2]);
    }
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    if (IMG_Init(0) != 0) {
        SDL_Log("SDL_image could not initialize! IMG_Error: %s", IMG_GetError());
        return 1;
    }

    SDL_DisplayMode mode;
    if (SDL_GetCurrentDisplayMode(0, &mode) != 0) {
        fprintf(stderr, "Unable to get display mode for display %d: %s\n", 0, SDL_GetError());
    }

    int windowWidth = mode.w;
    int windowHeight = mode.h;

    // Print a summary of what we are doing
    if (splashDelay > 10) {
    printf("\nSplash: Detected Resolution is %dx%d\n", mode.w, mode.h);
    }
    printf("Splash: Delay set to %d ms\n", splashDelay);

    // Create the window
    SDL_Window *window = SDL_CreateWindow(
        "Splash",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth,
        windowHeight,
        SDL_WINDOW_SHOWN
    );

        if (!window) {
        SDL_Log("Unable to create window: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Set the window to fullscreen
    // if (SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN) < 0) {
    //     SDL_Log("Unable to set fullscreen mode! SDL_Error: %s\n", SDL_GetError());
    // }

    // Create the renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Unable to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Load the image
    SDL_Surface *spriteSurface = IMG_Load(spritePath);
    if (!spriteSurface) {
        SDL_Log("Unable to load image: %s", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Create a texture from the image
    SDL_Texture *spriteTexture = SDL_CreateTextureFromSurface(renderer, spriteSurface);
    SDL_FreeSurface(spriteSurface); // No longer need the surface
    if (!spriteTexture) {
        SDL_Log("Unable to create texture: %s", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Get the texture dimensions
    int texWidth, texHeight;
    SDL_QueryTexture(spriteTexture, NULL, NULL, &texWidth, &texHeight);

    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);


        // Calculate the scaled rectangle to maintain aspect ratio
    SDL_Rect scaledRect = scaleSprite((SDL_Rect){0, 0, texWidth, texHeight}, windowWidth, windowHeight);

    // Copy the texture to the renderer
    SDL_RenderCopy(renderer, spriteTexture, NULL, &scaledRect);

    // Present the renderer
    SDL_RenderPresent(renderer);

    SDL_Delay(splashDelay); 

    SDL_DestroyTexture(spriteTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
 }

