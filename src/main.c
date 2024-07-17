#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <stdbool.h>

#include "../include/player.h"
#include "../include/bullet.h"
#include "../include/enemy.h"
#include "../include/config.h"
 
int main(int argc, char *argv[])
{
    // returns zero on success else non-zero
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    // creates a window
    SDL_Window* win = SDL_CreateWindow("Shoot Em' Up",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WINDOW_WIDTH, 
                                       WINDOW_HEIGHT, 
                                       0);
    // set the window to fullscreen
    // SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN);

    // triggers the program that controls
    // your graphics hardware and sets flags
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
 
    // creates a renderer to render our images
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
 
    // create the main player
    Player *player = createPlayer(rend, WINDOW_WIDTH, WINDOW_HEIGHT);

    // stores all the bullets to be drawn in a linked list
    Bullet *bullets[BULLET_QTY];
    int bullet_qty = 0;

    // create the enemy
    Enemy *enemy = createEnemy(rend, 2 * WINDOW_WIDTH / 3, WINDOW_HEIGHT / 2);

    // create all the bullets and draw them outside the screen
    // when the player shoot, they teleport to the player position
    for (int b = 0; b < BULLET_QTY; b++) {
        Bullet *bullet = createBullet(rend, -WINDOW_HEIGHT, -WINDOW_WIDTH);
        bullets[b] = bullet;
    }
    
    // controls animation loop
    int close = 0;

    // count game ticks twice to update according to refresh rate
    Uint32 ticks_a = 0;
    Uint32 ticks_b = 0;

    // get the difference of ticks between a frame and another
    Uint32 delta = 0;
 
    // animation loop
    while (!close) {

        // fetch game ticks
        ticks_a = SDL_GetTicks();
        
        // get delta ticks to limit framerate
        delta = ticks_a - ticks_b;

        // poll os events
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                close = 1;
                return 0;
            }
        }

        // limit framerate by adding a delay
        if (delta > 1000 / WINDOW_RATE) 
        {
            // print fps in terminal
            printf("FPS: %d\n", (1000 / delta));

            // update the tick count
            ticks_b = ticks_a;
            
            // clears the screen
            SDL_RenderClear(rend);

            // manages player movement
            movePlayer(player);

            // apply limits to player movement
            limitPlayer(player, WINDOW_WIDTH, WINDOW_HEIGHT);

            // moves the bullets to the players location
            // to make the illusion that they are spawning
            if (shootBullet(player)) {
                int bullet_index = bullet_qty % BULLET_QTY;
                bullets[bullet_index]->dest.x = player->dest.x;// + (bullets[bullet_index]->dest.w / 2);
                bullets[bullet_index]->dest.y = player->dest.y;// + (bullets[bullet_index]->dest.h / 2);
                bullet_qty++;
            }
            
            // draws all the bullets first
            for (int b = 0; b < BULLET_QTY; b++) {
                bullets[b]->dest.x += BULLET_SPEED;
                SDL_RenderCopy(rend, bullets[b]->tex, NULL, &bullets[b]->dest);
            }

            // then draws the player over
            SDL_RenderCopy(rend, player->tex, NULL, &player->dest);
    
            // then draws the player over
            SDL_RenderCopy(rend, enemy->tex, NULL, &enemy->dest);
    
            // triggers the double buffers
            // for multiple rendering
            SDL_RenderPresent(rend);
        }
    }
 
    // destroy texture
    SDL_DestroyTexture(player->tex);
 
    // destroy renderer
    SDL_DestroyRenderer(rend);
 
    // destroy window
    SDL_DestroyWindow(win);
     
    // close SDL
    SDL_Quit();
 
    return 0;
}
