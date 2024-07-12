#define BULLET_SPEED 16

typedef struct Bullet {
    SDL_Surface* surface;
    SDL_Texture* tex;
    SDL_Rect dest;
    struct Bullet *next;
} Bullet;

// creates the player
void createBullet(SDL_Renderer* rend, Bullet *bullet, int x, int y);

// creates the player
void addBullet(SDL_Renderer* rend, Bullet *bullet, Player *player);