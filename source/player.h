#if defined(__APPLE__)

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "SDL2_image/SDL_mixer.h"

#endif

#if defined(__linux__)
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#endif



#if defined(_WIN32) || (_WIN64)
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#endif

#include <string>
#include <iostream>
#include <sstream>

//bullet includes
#include <vector>
#include "bullet.h"

using namespace std;

class Player{
protected:



public:

	Mix_Chunk *laser;

	vector<Bullet> bulletList;



	int playerNum;
	string playerpath;
	SDL_Surface *surface;
	SDL_Texture *texture;
	SDL_Rect posRect;

	float xDir,yDir;
	float speed;

	float pos_X,pos_Y;

	Player(SDL_Renderer *renderer,int pNum,string filepath,string audioPath,float x,float y);

	void Update(float deltaTime);

	void Draw(SDL_Renderer *renderer);

	void OnControllerAxis(const SDL_ControllerAxisEvent event);

	void OnControllerButton(const SDL_ControllerButtonEvent event);



	~Player();

private:
	void CreateBullet();
};
