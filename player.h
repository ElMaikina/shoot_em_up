#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <stdbool.h>

#define PLAYER_SPEED 6
#define PLAYER_SHOOT_DELAY 12

typedef struct {
    SDL_Surface* surface;
    SDL_Texture* tex;
    SDL_Rect dest;
    int shoot;
} Player;

// creates the player
Player *createPlayer(SDL_Renderer* rend, int winw, int winh);

// manages player movement
void movePlayer(Player *player);

// makes player shoot bullets
// returns 1 if it shoots, 0 otherwise
bool shootBullet(Player *player);