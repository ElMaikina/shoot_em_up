typedef struct {
    SDL_Surface* surface;
    SDL_Texture* tex;
    SDL_Rect dest;
} Enemy;

// creates the player
Enemy *createEnemy(SDL_Renderer* rend, int x, int y);