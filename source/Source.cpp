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
#include "SDL2/SDL_ttf.h"
#include <unistd.h>
#endif



#if defined(_WIN32) || (_WIN64)

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf"
#endif

#if defined(_WIN32) || (_WIN64)

#include<direct.h>
#define getcwd _getcwd

#endif

#include <stdio.h>
#include <iostream>
#include "player.h"
using namespace std;

//create the SDL_rectangle for the texture's position and size - x,y,w,h
SDL_Rect bkgd1pos;
SDL_Rect bkgd2pos;

//code for frame rate independance
float deltaTime = 0.0;
int thistime = 0;
int lasttime = 0;
//set up speed for background
int bkgdSpeed = 100;

//setup temp var to hold movement-background1
float BG1pos_x = 0, BG1pos_y = 0;

//setup temp var to hold movement-background2
float BG2pos_x = 0, BG2pos_y = -768;

//move the background
void UpdateBackground() {
	//update background1
	BG1pos_y += (bkgdSpeed * 1) * deltaTime;

	//set new bkgsd1 position
	bkgd1pos.y = (int) (BG1pos_y + 0.5f);

	//reset when off the bottom of the screen
	if (bkgd1pos.y >= 768) {
		bkgd1pos.y = -768;
		BG1pos_y = bkgd1pos.y;
	}

	//update background1
	BG2pos_y += (bkgdSpeed * 1) * deltaTime;

	//set new bkgsd1 position
	bkgd2pos.y = (int) (BG2pos_y + 0.5f);

	//reset when off the bottom of the screen
	if (bkgd2pos.y >= 768) {
		bkgd2pos.y = -768;
		BG2pos_y = bkgd2pos.y;
	}

}

const int JOYSTICK_DEAD_ZONE = 8000;

float xDir,yDir;

float pos_x,pos_y;

SDL_Rect cursorpos,activepos;

int CursorSpeed = 400;




void moveCursor(const SDL_ControllerAxisEvent event){
	if (event.which == 0){
		if(event.axis == 0)
		{
			if(event.value < -JOYSTICK_DEAD_ZONE)
			{
				xDir=-1.0f;
			}else if(event.value > JOYSTICK_DEAD_ZONE){
				xDir = 1.0f;
			}else{
				xDir = 0.0f;
			}
		}

		if(event.axis == 1){
			if(event.value < -JOYSTICK_DEAD_ZONE)
			{
				yDir=-1.0f;
			}else if(event.value > JOYSTICK_DEAD_ZONE){
				yDir = 1.0f;
			}else{
				yDir = 0.0f;
			}
		}
	}

}

void UpdateCursor(float deltaTime){
	//update cursor
	pos_x+=(CursorSpeed * xDir)*deltaTime;
	pos_y+=(CursorSpeed * yDir)*deltaTime;

	//assign to SDL_RECT ints x and y
	cursorpos.x=(int)(pos_x+0.5f);
	cursorpos.y=(int)(pos_y+0.5f);

	activepos.x = cursorpos.x;
	activepos.y = cursorpos.y;

	if(cursorpos.x<0)
		cursorpos.x=0;
	pos_x=cursorpos.x;

	if(cursorpos.x>1024-cursorpos.w)
	{
		cursorpos.x=1024-cursorpos.w;
		pos_x=cursorpos.x;
	}


	if(cursorpos.y<0)
		cursorpos.y=0;
	pos_y=cursorpos.y;

	if(cursorpos.y>768-cursorpos.h)
	{
		cursorpos.y=768-cursorpos.h;
		pos_y=cursorpos.y;
	}
}

int main(int argc, char* argv[]) {

#if defined(__APPLE__)

	cout << "running on apple..";
	//get the current working directory
	string s_cwd(getcwd(NULL, 0));

	//create a string linking to the mac's image folder
	string s_cwd_images = s_cwd + "/Resources/images";

	string audio_dir = s_cwd + "/Resources/audio";

	//test
	cout << s_cwd_images << endl;

#endif

#if defined(__linux__)
	cout << "running on linux..";
	cout << "added on linux..";

	//get the current working directory
	string s_cwd(getcwd(NULL, 0));

	//create a string linking to the mac's image folder
	string s_cwd_images = s_cwd + "/Resources/images";

	string audio_dir = s_cwd + "/Resources/audio";

#endif

#if defined(_WIN32) || (_WIN64)

	cout << "running on windows..";
	//get the current working directory
	string s_cwd(getcwd(NULL, 0));

	//create a string linking to the mac's image folder
	string s_cwd_images = s_cwd + "\\Resources\\images\\";

	string audio_dir = s_cwd + "\\Resources\\audio\\";
#endif

	SDL_Window *window;                    // Declare a pointer

	SDL_Init(SDL_INIT_EVERYTHING);              // Initialize SDL2

	// Create an application window with the following settings:
	window = SDL_CreateWindow("An SDL2 window",                  // window title
		SDL_WINDOWPOS_UNDEFINED,           // initial x position
		SDL_WINDOWPOS_UNDEFINED,           // initial y position
		1024,                               // width, in pixels
		768,                               // height, in pixels
		SDL_WINDOW_OPENGL                  // flags - see below
		);

	// Check that the window was successfully created
	if (window == NULL) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Renderer* renderer = NULL;

	//create the renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);




	//**********Create background image********
	string BKGDpath = s_cwd_images + "/background.png";

	//create a SDL Surface to hold the background image
	SDL_Surface *surface = IMG_Load(BKGDpath.c_str());

	//create a SDL texture

	SDL_Texture *bkgd1;

	//place surface info into the texture background
	bkgd1 = SDL_CreateTextureFromSurface(renderer, surface);

	//create sdl texture - background2
	SDL_Texture *bkgd2;

	//place surface info into the texture background
	bkgd2 = SDL_CreateTextureFromSurface(renderer, surface);

	//set the x,y,w,h for the rectangle
	bkgd1pos.x = 0;
	bkgd1pos.y = 0;
	bkgd1pos.w = 1024;
	bkgd1pos.h = 768;

	bkgd2pos.x = 0;
	bkgd2pos.y = -768;
	bkgd2pos.w = 1024;
	bkgd2pos.h = 768;

	//create title//////////////////////////////////////////////////////////
	string titlepath = s_cwd_images + "/title.png";

	//create a SDL Surface to hold the background image
	surface = IMG_Load(titlepath.c_str());

	//create a SDL texture
	SDL_Texture *title;

	title = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect titlepos;

	titlepos.x = 167;
	titlepos.y = 69;
	titlepos.w = 697;
	titlepos.h = 33;

	//title end

	//create player1//////////////////////////////////////////////////////////////////////
	string player1npath = s_cwd_images + "/1playernorm.png";

	//create a SDL Surface to hold the background image
	surface = IMG_Load(player1npath.c_str());

	//create a SDL texture
	SDL_Texture *player1n;

	player1n = SDL_CreateTextureFromSurface(renderer, surface);

	//create player1
	string player1opath = s_cwd_images + "/1playerover.png";

	//create a SDL Surface to hold the background image
	surface = IMG_Load(player1opath.c_str());

	//create a SDL texture
	SDL_Texture *player1o;

	player1o = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect player1npos;

	player1npos.x = 211;
	player1npos.y = 471;
	player1npos.w = 608;
	player1npos.h = 33;

	//player 1 end

	//create player2//////////////////////////////////////////////////////
	string player2npath = s_cwd_images + "/2playernorm.png";

	//create a SDL Surface to hold the background image
	surface = IMG_Load(player2npath.c_str());

	//create a SDL texture
	SDL_Texture *player2n;

	player2n = SDL_CreateTextureFromSurface(renderer, surface);

	//create player2
	string player2opath = s_cwd_images + "/2playerover.png";

	//create a SDL Surface to hold the background image
	surface = IMG_Load(player2opath.c_str());

	//create a SDL texture
	SDL_Texture *player2o;

	player2o = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect player2npos;

	player2npos.x = 205;
	player2npos.y = 570;
	player2npos.w = 621;
	player2npos.h = 33;

	//player 2 end

	//create instructions//////////////////////////////////////////////////////
	string instructnpath = s_cwd_images + "/instructnormal.png";

	//create a SDL Surface to hold the background image
	surface = IMG_Load(instructnpath.c_str());

	//create a SDL texture
	SDL_Texture *instructn;

	instructn = SDL_CreateTextureFromSurface(renderer, surface);

	//create instructions overlay
	string instructopath = s_cwd_images + "/instructover.png";

	//create a SDL Surface to hold the background image
	surface = IMG_Load(instructopath.c_str());

	//create a SDL texture
	SDL_Texture *instructo;

	instructo = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect instructnpos;

	instructnpos.x = 250;
	instructnpos.y = 373;
	instructnpos.w = 530;
	instructnpos.h = 27;

	//instructions 2 end

	string quitnpath = s_cwd_images + "/quit.png";

	//create a SDL Surface to hold the background image
	surface = IMG_Load(quitnpath.c_str());

	//create a SDL texture
	SDL_Texture *quitn;

	quitn = SDL_CreateTextureFromSurface(renderer, surface);

	//create player2
	string quitopath = s_cwd_images + "/quitover.png";

	//create a SDL Surface to hold the background image
	surface = IMG_Load(quitopath.c_str());

	//create a SDL texture
	SDL_Texture *quito;

	quito = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect quitnpos;

	quitnpos.x = 397;
	quitnpos.y = 664;
	quitnpos.w = 188;
	quitnpos.h = 33;

	//instructions end

	//main menu end

	//create instructions screen//////////////////////////////////////////////////////

	//create instructions overlay
	string instructtextpath = s_cwd_images + "/instructtext.png";

	//create a SDL Surface to hold the background image
	surface = IMG_Load(instructtextpath.c_str());

	//create a SDL texture
	SDL_Texture *instructtext;

	instructtext = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect instructtextpos;

	instructtextpos.x = 125;
	instructtextpos.y = 231;
	instructtextpos.w = 759;
	instructtextpos.h = 258;

	//instructions  end

	//create menu button overlay
	string menunpath = s_cwd_images + "/menunorm.png";

	//create a SDL Surface to hold the background image
	surface = IMG_Load(menunpath.c_str());

	//create a SDL texture
	SDL_Texture *menunorm;

	menunorm = SDL_CreateTextureFromSurface(renderer, surface);

	string menuopath = s_cwd_images + "/menuover.png";

	//create a SDL Surface to hold the background image
	surface = IMG_Load(menuopath.c_str());

	//create a SDL texture
	SDL_Texture *menuover;

	menuover = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect menupos;

	menupos.x = 735;
	menupos.y = 711;
	menupos.w = 241;
	menupos.h = 27;

	//instructions 2 end

	//win screen begin-----------------------------------
	//create win screen overlay
	string winpath = s_cwd_images + "/Win.png";

	//create a SDL Surface to hold the background image
	surface = IMG_Load(winpath.c_str());

	//create a SDL texture
	SDL_Texture *wintext;

	wintext = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect winpos;

	winpos.x = 144;
	winpos.y = 318;
	winpos.w = 728;
	winpos.h = 119;

	//instructions  end

	//create menu button overlay
	string playpath = s_cwd_images + "/Play.png";

	//create a SDL Surface to hold the background image
	surface = IMG_Load(playpath.c_str());

	//create a SDL texture
	SDL_Texture *playnorm;

	playnorm = SDL_CreateTextureFromSurface(renderer, surface);

	string playopath = s_cwd_images + "/playover.png";

	//create a SDL Surface to hold the background image
	surface = IMG_Load(playopath.c_str());

	//create a SDL texture
	SDL_Texture *playover;

	playover = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect playpos;

	playpos.x = 45;
	playpos.y = 707;
	playpos.w = 198;
	playpos.h = 33;

	//win screen end--------------------------------------

	//create lose screen overlay
	string losepath = s_cwd_images + "/Lose.png";

	//create a SDL Surface to hold the background image
	surface = IMG_Load(losepath.c_str());

	//create a SDL texture
	SDL_Texture *losetext;

	losetext = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect losepos;

	losepos.x = 246;
	losepos.y = 314;
	losepos.w = 581;
	losepos.h = 114;

	///lose screen end

	//create cursor
	string CURSORpath = s_cwd_images + "/reticle.png";

	//create a SDL Surface to hold the background image
	surface = IMG_Load(CURSORpath.c_str());

	//create a SDL texture
	SDL_Texture *cursor;

	//place surface info into the texture background
	cursor = SDL_CreateTextureFromSurface(renderer, surface);

	cursorpos.x = 0;
	cursorpos.y = 0;
	cursorpos.w = 32;
	cursorpos.h = 32;
	//
	activepos.x = 10;
	activepos.y = 10;
	activepos.w = 10;
	activepos.h = 10;


	//free SDL surface
	SDL_FreeSurface(surface);



	//set up game controller variable *****


	//****Turn on game controller events**
	SDL_GameControllerEventState(SDL_ENABLE);


	SDL_GameController* gGameController0 = NULL;

	//*****Open game controller up****
	gGameController0 = SDL_GameControllerOpen(0);

	SDL_GameController* gGameController1 = NULL;

	//*****Open game controller up****
	gGameController1 = SDL_GameControllerOpen(1);

	//****Turn on game controller events**
	SDL_GameControllerEventState(SDL_ENABLE);

	//***SDL event to handle input
	SDL_Event event;

	//set up variables for the game states
	enum GameState {
		MENU, INSTRUCTIONS, PLAYERS1, PLAYERS2, WIN, LOSE
	};

	//setup initial state
	GameState gameState = MENU;

	//bolean values to control movement through states

	bool menu = false, instructions = false, players1 = false, players2 = false, win = false, lose = false, quit = false;
	bool players1Over = false, players2Over = false, instructionsOver = false, quitOver = false, menuOver = false, playOver = false;


	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	Mix_Music *bgm = Mix_LoadMUS((audio_dir + "/background.wav").c_str());

	if (!Mix_PlayingMusic())
		Mix_PlayMusic(bgm, -1);

	Mix_Chunk *overSound = Mix_LoadWAV((audio_dir + "/over.wav").c_str());

	Mix_Chunk *pressedSound = Mix_LoadWAV((audio_dir + "/pressed.wav").c_str());

	bool alreadyOver = false;

	/////////////////////////////////create players
	Player player1 = Player(renderer, 0, s_cwd_images.c_str(), audio_dir.c_str(), 250.0, 500.0);

	Player player2 = Player(renderer, 1, s_cwd_images.c_str(), audio_dir.c_str(), 750.0, 500.0);




	// The window is open: could enter program loop here (see SDL_PollEvent())

	while (!quit) {
		switch (gameState) {

		case MENU:
			menu = true;
			alreadyOver = false;

			while (menu) {
				//set up framerate for the section, or CASE
				thistime = SDL_GetTicks();
				deltaTime = (float)(thistime - lasttime) / 1000;
				lasttime = thistime;
				//check for input events
				if (SDL_PollEvent(&event)) {
					//check to see if the SDL window is closed - player clicks x in window
					if (event.type == SDL_QUIT) {
						quit = true;
						menu = false;
						break;
					}
					switch (event.type) {
					case SDL_CONTROLLERBUTTONDOWN:
						if (event.cdevice.which == 0) {
							if (event.cbutton.button
								== SDL_CONTROLLER_BUTTON_A) {
								if (players1Over) {
									Mix_PlayChannel(-1, pressedSound, 0);
									menu = false;
									gameState = PLAYERS1;
									players1Over = false;
								}

								if (players2Over) {
									Mix_PlayChannel(-1, pressedSound, 0);
									menu = false;
									gameState = PLAYERS2;
									players2Over = false;
								}

								if (instructionsOver) {
									Mix_PlayChannel(-1, pressedSound, 0);
									menu = false;
									gameState = INSTRUCTIONS;
									instructionsOver = false;
								}

								if (quitOver) {
									Mix_PlayChannel(-1, pressedSound, 0);
									SDL_Delay(200);
									menu = false;
									quit = true;
									quitOver = false;
								}

								break;
					case SDL_CONTROLLERAXISMOTION:
						moveCursor(event.caxis);
						break;

							}
							break;
						}
					}
				}

				//update section
				UpdateBackground();
				UpdateCursor(deltaTime);

				players1Over = SDL_HasIntersection(&activepos, &player1npos);
				players2Over = SDL_HasIntersection(&activepos, &player2npos);
				instructionsOver = SDL_HasIntersection(&activepos, &instructnpos);
				quitOver = SDL_HasIntersection(&activepos, &quitnpos);

				// audio code section

				if (players1Over || players2Over || instructionsOver || quitOver)
				{
					if (alreadyOver == false) {
						Mix_PlayChannel(-1, overSound, 0);
						alreadyOver = true;
					}

				}

				if (!players1Over && !players2Over && !instructionsOver && !quitOver) {
					alreadyOver = false;
				}


				//start drawing
				//clear SDL renderer
				SDL_RenderClear(renderer);

				//draw the background
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1pos);

				SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2pos);

				SDL_RenderCopy(renderer, title, NULL, &titlepos);

				if (players1Over)
				{
					SDL_RenderCopy(renderer, player1o, NULL, &player1npos);
				}
				else {
					SDL_RenderCopy(renderer, player1n, NULL, &player1npos);
				}


				if (players2Over)
				{
					SDL_RenderCopy(renderer, player2o, NULL, &player2npos);
				}
				else {
					SDL_RenderCopy(renderer, player2n, NULL, &player2npos);
				}

				if (instructionsOver)
				{
					SDL_RenderCopy(renderer, instructo, NULL, &instructnpos);
				}
				else {
					SDL_RenderCopy(renderer, instructn, NULL, &instructnpos);
				}

				if (quitOver)
				{
					SDL_RenderCopy(renderer, quito, NULL, &quitnpos);
				}
				else {
					SDL_RenderCopy(renderer, quitn, NULL, &quitnpos);
				}
				SDL_RenderCopy(renderer, cursor, NULL, &cursorpos);

				//SDL Render present
				SDL_RenderPresent(renderer);

			}
			break;				//end main menu case

		case INSTRUCTIONS:
			instructions = true;
			alreadyOver = false;
			while (instructions) {
				thistime = SDL_GetTicks();
				deltaTime = (float)(thistime - lasttime) / 1000;
				lasttime = thistime;
				//check for input events
				if (SDL_PollEvent(&event)) {
					//check to see if the SDL window is closed - player clicks x in window
					if (event.type == SDL_QUIT) {
						quit = true;
						instructions = false;
						break;
					}
					switch (event.type) {
					case SDL_CONTROLLERBUTTONDOWN:
						if (event.cdevice.which == 0) {
							if (event.cbutton.button
								== SDL_CONTROLLER_BUTTON_A) {

								if (instructionsOver) {
									Mix_PlayChannel(-1, pressedSound, 0);
									instructions = false;
									gameState = MENU;
									menuOver = false;
								}

							}

						}
						break;
					case SDL_CONTROLLERAXISMOTION:
						moveCursor(event.caxis);
						break;
					}
				}

				//update section
				UpdateBackground();

				//start drawing
				UpdateCursor(deltaTime);

				menuOver = SDL_HasIntersection(&activepos, &menupos);

				if (menuOver)
				{
					if (alreadyOver == false) {
						Mix_PlayChannel(-1, overSound, 0);
						alreadyOver = true;
					}

				}

				if (!menuOver) {
					alreadyOver = false;
				}

				//clear SDL renderer
				SDL_RenderClear(renderer);

				//drae the background
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1pos);

				SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2pos);

				SDL_RenderCopy(renderer, title, NULL, &titlepos);

				SDL_RenderCopy(renderer, instructtext, NULL, &instructtextpos);

				SDL_RenderCopy(renderer, cursor, NULL, &cursorpos);

				if (menuOver) {
					SDL_RenderCopy(renderer, menuover, NULL, &menupos);
				}
				else {
					SDL_RenderCopy(renderer, menunorm, NULL, &menupos);
				}


				//SDL Render present
				SDL_RenderPresent(renderer);
			}
			break;						//end instructions case

		case PLAYERS1:
			players1 = true;

			while (players1) {
				thistime = SDL_GetTicks();
				deltaTime = (float)(thistime - lasttime) / 1000;
				lasttime = thistime;
				//check for input events
				if (SDL_PollEvent(&event)) {
					//check to see if the SDL window is closed - player clicks x in window
					if (event.type == SDL_QUIT) {
						quit = true;
						players1 = false;
						break;
					}
					switch (event.type) {
					case SDL_CONTROLLERBUTTONDOWN:
						if (event.cdevice.which == 0) {
							if (event.cbutton.button
								== SDL_CONTROLLER_BUTTON_X) {
								players1 = false;
								gameState = WIN;

							}
							if (event.cbutton.button
								== SDL_CONTROLLER_BUTTON_Y) {
								players1 = false;
								gameState = LOSE;
							}

							player1.OnControllerButton(event.cbutton);
						}
						break;
					case SDL_CONTROLLERAXISMOTION:
						player1.OnControllerAxis(event.caxis);
						break;
					}
				}

				//update section
				UpdateBackground();

				player1.Update(deltaTime,renderer);

				//start drawing
				//clear SDL renderer
				SDL_RenderClear(renderer);

				//drae the background
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1pos);

				SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2pos);

				//SDL_RenderCopy(renderer, player1n, NULL, &player1npos);

				player1.Draw(renderer);

				//SDL Render present
				SDL_RenderPresent(renderer);
			}
			break;					//end player 1 case
		case PLAYERS2:
			players2 = true;


			while (players2) {
				thistime = SDL_GetTicks();
				deltaTime = (float)(thistime - lasttime) / 1000;
				lasttime = thistime;
				//check for input events
				if (SDL_PollEvent(&event)) {
					//check to see if the SDL window is closed - player clicks x in window
					if (event.type == SDL_QUIT) {
						quit = true;
						players2 = false;
						break;
					}
					switch (event.type) {
					case SDL_CONTROLLERBUTTONDOWN:
						if (event.cdevice.which == 0 || event.cdevice.which == 1) {
							if (event.cbutton.button
								== SDL_CONTROLLER_BUTTON_X) {
								players2 = false;
								gameState = WIN;

							}
							if (event.cbutton.button
								== SDL_CONTROLLER_BUTTON_Y) {
								players2 = false;
								gameState = LOSE;
							}

						}

						player1.OnControllerButton(event.cbutton);
						player2.OnControllerButton(event.cbutton);
						break;

					case SDL_CONTROLLERAXISMOTION:
						player1.OnControllerAxis(event.caxis);
						player2.OnControllerAxis(event.caxis);
						break;
					}
				}
				//update section
				UpdateBackground();
				player1.Update(deltaTime,renderer);
				player2.Update(deltaTime,renderer);
				//start drawing
				//clear SDL renderer
				SDL_RenderClear(renderer);

				//drae the background
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1pos);

				SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2pos);

				//SDL_RenderCopy(renderer, player2n, NULL, &player2npos);


				player1.Draw(renderer);
				player2.Draw(renderer);

				//SDL Render present
				SDL_RenderPresent(renderer);
			}
			break;										//end player 2 case
		case WIN:
			alreadyOver = false;
			win = true;


			while (win) {

				thistime = SDL_GetTicks();
				deltaTime = (float)(thistime - lasttime) / 1000;
				lasttime = thistime;

				//check for input events
				if (SDL_PollEvent(&event)) {
					//check to see if the SDL window is closed - player clicks x in window
					if (event.type == SDL_QUIT) {
						quit = true;
						win = false;
						break;
					}
					switch (event.type) {
					case SDL_CONTROLLERBUTTONDOWN:
						if (event.cdevice.which == 0) {
							if (event.cbutton.button
								== SDL_CONTROLLER_BUTTON_X) {
								win = false;
								gameState = MENU;

							}
							if (event.cbutton.button
								== SDL_CONTROLLER_BUTTON_Y) {
								win = false;
								gameState = PLAYERS1;
							}


							if (event.cbutton.button
								== SDL_CONTROLLER_BUTTON_A) {

								if (playOver) {
									Mix_PlayChannel(-1, pressedSound, 0);
									win = false;
									gameState = PLAYERS1;
									playOver = false;
								}

								if (menuOver) {
									Mix_PlayChannel(-1, pressedSound, 0);
									win = false;
									gameState = MENU;
									menuOver = false;
								}


							}






						}
						break;
					case SDL_CONTROLLERAXISMOTION:
						moveCursor(event.caxis);
						break;
					}
				}
				//update section
				UpdateBackground();

				UpdateCursor(deltaTime);

				menuOver = SDL_HasIntersection(&activepos, &menupos);

				playOver = SDL_HasIntersection(&activepos, &playpos);





				if (menuOver || playOver)
				{
					if (alreadyOver == false) {
						Mix_PlayChannel(-1, overSound, 0);
						alreadyOver = true;
					}

				}

				if (!menuOver && !playOver) {
					alreadyOver = false;
				}

				//start drawing
				//clear SDL renderer
				SDL_RenderClear(renderer);

				//drae the background
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1pos);

				SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2pos);

				SDL_RenderCopy(renderer, wintext, NULL, &winpos);

				if (menuOver) {
					SDL_RenderCopy(renderer, menuover, NULL, &menupos);
				}
				else {
					SDL_RenderCopy(renderer, menunorm, NULL, &menupos);
				}

				if (playOver) {
					SDL_RenderCopy(renderer, playover, NULL, &playpos);
				}
				else {
					SDL_RenderCopy(renderer, playnorm, NULL, &playpos);
				}


				SDL_RenderCopy(renderer, cursor, NULL, &cursorpos);

				//SDL Render present
				SDL_RenderPresent(renderer);
			}
			break;										//end win case
		case LOSE:
			lose = true;
			alreadyOver = false;


			while (lose) {

				thistime = SDL_GetTicks();
				deltaTime = (float)(thistime - lasttime) / 1000;
				lasttime = thistime;

				//check for input events
				if (SDL_PollEvent(&event)) {
					//check to see if the SDL window is closed - player clicks x in window
					if (event.type == SDL_QUIT) {
						quit = true;
						lose = false;
						break;
					}
					switch (event.type) {
					case SDL_CONTROLLERBUTTONDOWN:
						if (event.cdevice.which == 0) {
							if (event.cbutton.button
								== SDL_CONTROLLER_BUTTON_X) {
								lose = false;
								gameState = MENU;

							}
							if (event.cbutton.button
								== SDL_CONTROLLER_BUTTON_Y) {
								lose = false;
								gameState = PLAYERS1;
							}

							if (event.cbutton.button
								== SDL_CONTROLLER_BUTTON_A) {

								if (playOver) {
									lose = false;
									gameState = PLAYERS1;
									Mix_PlayChannel(-1, pressedSound, 0);
									playOver = false;
								}

								if (menuOver) {
									lose = false;
									gameState = MENU;
									Mix_PlayChannel(-1, pressedSound, 0);
									menuOver = false;
								}


							}
							break;
					case SDL_CONTROLLERAXISMOTION:
						moveCursor(event.caxis);
						break;
						}
					}
					//update section
					UpdateBackground();

					UpdateCursor(deltaTime);

					menuOver = SDL_HasIntersection(&activepos, &menupos);

					playOver = SDL_HasIntersection(&activepos, &playpos);


					if (menuOver || playOver)
					{
						if (alreadyOver == false) {
							Mix_PlayChannel(-1, overSound, 0);
							alreadyOver = true;
						}

					}

					if (!menuOver && !playOver) {
						alreadyOver = false;
					}

					//start drawing
					//clear SDL renderer
					SDL_RenderClear(renderer);

					//drae the background
					SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1pos);

					SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2pos);

					SDL_RenderCopy(renderer, losetext, NULL, &losepos);

					if (menuOver) {
						SDL_RenderCopy(renderer, menuover, NULL, &menupos);
					}
					else {
						SDL_RenderCopy(renderer, menunorm, NULL, &menupos);
					}

					if (playOver) {
						SDL_RenderCopy(renderer, playover, NULL, &playpos);
					}
					else {
						SDL_RenderCopy(renderer, playnorm, NULL, &playpos);
					}

					SDL_RenderCopy(renderer, cursor, NULL, &cursorpos);

					//SDL Render present
					SDL_RenderPresent(renderer);
				}
				break;
			}//end win case
		default:
			break;
			}

		}

		//SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example

		// Close and destroy the window
		SDL_DestroyWindow(window);

		// Clean up
		SDL_Quit();
		return 0;
	}
