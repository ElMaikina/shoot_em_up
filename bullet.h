typedef struct {
    SDL_Surface* surface;
    SDL_Texture* tex;
    SDL_Rect dest;
} Bullet;

// creates the player
Bullet *createBullet(SDL_Renderer* rend, int x, int y);