#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <stdbool.h>
 
int main(int argc, char *argv[])
{
    int window_width = 640;
    int window_height = 360;
    int framerate = 300;

    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    SDL_Window* win = SDL_CreateWindow("Platform Game", // creates a window
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       window_width, 
                                       window_height, 
                                       0);

    // set the window to fullscreen
    //SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN);

    // triggers the program that controls
    // your graphics hardware and sets flags
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
 
    // creates a renderer to render our images
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
 
    // creates a surface to load an image into the main memory
    SDL_Surface* surface;
 
    // please provide a path for your image
    surface = IMG_Load("melody.png");
 
    // loads image to our graphics hardware memory.
    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
 
    // clears main-memory
    SDL_FreeSurface(surface);
 
    // let us control our image position
    // so that we can move it with our keyboard.
    SDL_Rect dest;
 
    // connects our texture with dest to control position
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
 
    // adjust height and width of our image box.
    dest.w /= 6;
    dest.h /= 6;
 
    // sets initial x-position of object
    dest.x = (window_width - dest.w) / 2;
 
    // sets initial y-position of object
    dest.y = (window_height - dest.h) / 2;
 
    // controls animation loop
    int close = 0;
 
    // speed of box
    int speed = 6;
 
    // animation loop
    while (!close) {

        SDL_Event event;

        while (SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_QUIT) {
                close = 1;
                return 0;
            }
        }
    
        const Uint8* keystate = SDL_GetKeyboardState(NULL);
        
        // movement keys
        if (keystate[SDL_SCANCODE_UP]) 
            dest.y -= speed;

        if (keystate[SDL_SCANCODE_DOWN]) 
            dest.y += speed;

        if (keystate[SDL_SCANCODE_LEFT])
            dest.x -= speed;

        if (keystate[SDL_SCANCODE_RIGHT])
            dest.x += speed;
        
        // clears the screen
        SDL_RenderClear(rend);
        SDL_RenderCopy(rend, tex, NULL, &dest);
 
        // triggers the double buffers
        // for multiple rendering
        SDL_RenderPresent(rend);
 
        // limits framerate
        SDL_Delay(1000 / framerate);
    }
 
    // destroy texture
    SDL_DestroyTexture(tex);
 
    // destroy renderer
    SDL_DestroyRenderer(rend);
 
    // destroy window
    SDL_DestroyWindow(win);
     
    // close SDL
    SDL_Quit();
 
    return 0;
}
