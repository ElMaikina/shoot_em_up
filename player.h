#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <stdbool.h>

typedef struct {
    SDL_Surface* surface;
    SDL_Texture* tex;
    SDL_Rect dest;
    int speed;
} Player;

// creates the player
Player *createPlayer(SDL_Renderer* rend, int winw, int winh);

// manages player movement
void movePlayer(Player *player);