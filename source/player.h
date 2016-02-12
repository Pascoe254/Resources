#if defined(__APPLE__)

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "SDL2_mixer/SDL_mixer.h"
#include "SDL2_ttf/SDL_ttf.h"

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



using namespace std;

//bullet includes
#include <vector>
#include "bullet.h"

class Player{

public:

	int playerScore,oldScore,playerLives,oldLives;

	TTF_Font* font;

	SDL_Color colorP1 = {0,255,0,0255};

	SDL_Color colorP2 = {0,0,255,0255};

	SDL_Surface *scoreSurface, *livesSurface;

	SDL_Texture *scoreTexture, *livesTexture;

	SDL_Rect scorePos, livesPos;

	string tempScore,tempLives;

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

	void Update(float deltaTime,SDL_Renderer *renderer);

	void Draw(SDL_Renderer *renderer);

	void OnControllerAxis(const SDL_ControllerAxisEvent event);

	void OnControllerButton(const SDL_ControllerButtonEvent event);


	void UpdateScore(SDL_Renderer *renderer);

	~Player();



private:
	void CreateBullet();
};
