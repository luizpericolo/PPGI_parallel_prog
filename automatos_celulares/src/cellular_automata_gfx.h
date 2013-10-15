#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP 32

#define true 1
#define false 0

int init(SDL_Surface *screen);
void clean_up(SDL_Surface *image);
int show_screen();