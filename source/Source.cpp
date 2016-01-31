#if defined(__APPLE__)

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"

#endif

#if defined(__linux__)
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <unistd.h>
#endif



#if defined(_WIN32) || (_WIN64)

#include "SDL.h"
#include "SDL_image.h"
#endif

#if defined(_WIN32) || (_WIN64)

#include<direct.h>
#define getcwd _getcwd
#endif

#include <stdio.h>
#include <iostream>
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

int main(int argc, char* argv[]) {

#if defined(__APPLE__)

	cout << "running on apple..";
	//get the current working directory
	string s_cwd(getcwd(NULL, 0));

	//create a string linking to the mac's image folder
	string s_cwd_images = s_cwd + "/Resources/images";

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

#endif

#if defined(_WIN32) || (_WIN64)

	cout << "running on windows..";
	//get the current working directory
	string s_cwd(getcwd(NULL, 0));

	//create a string linking to the mac's image folder
	string s_cwd_images = s_cwd + "\\Resources\\images\\";
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
	string instructnpath = s_cwd_images + "/instructnorm.png";

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
	SDL_Texture *reticle;

	//place surface info into the texture background
	reticle = SDL_CreateTextureFromSurface(renderer, surface);

	//create the SDL_rectangle for the texture's position and size - x,y,w,h
	SDL_Rect reticlepos;

	//set the x,y,w,h for the rectangle
	reticlepos.x = 0;
	reticlepos.y = 0;
	reticlepos.w = 32;
	reticlepos.h = 32;

	//free SDL surface
	SDL_FreeSurface(surface);

	/*//The surface contained by the window
	 SDL_Surface* screenSurface = NULL;

	 //Get window surface
	 screenSurface = SDL_GetWindowSurface( window );

	 //Fill the surface white
	 SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0, 42, 254 ) );

	 //Update the surface
	 SDL_UpdateWindowSurface( window );*/

	//set up game controller variable *****
	SDL_GameController* gGameController = NULL;

	//*****Open game controller up****
	gGameController = SDL_GameControllerOpen(0);

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

	bool menu=false, instructions=false, players1=false, players2=false, win=false, lose=false, quit = false;


	// The window is open: could enter program loop here (see SDL_PollEvent())



	// The window is open: could enter program loop here (see SDL_PollEvent())

	while (!quit) {
		switch (gameState) {

		case MENU:
			menu = true;
			cout << "the gamestate is menu" << endl;
			cout << "Press the A button for Instructions" << endl;
			cout << "Press the B button for 1 player game" << endl;
			cout << "Press the X button for 2 player game" << endl;
			cout << "Press the Y button to Quit game" << endl;
			cout << endl;
			while (menu) {
				//set up framerate for the section, or CASE
				thistime = SDL_GetTicks();
				deltaTime = (float) (thistime - lasttime) / 1000;
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
								menu = false;
								gameState = INSTRUCTIONS;

							}
							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_B) {
								menu = false;
								gameState = PLAYERS1;

							}
							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_X) {
								menu = false;
								gameState = PLAYERS2;

							}
							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_Y) {
								menu = false;
								quit = true;

							}

						}
						break;
					}
				}

				//update section
				UpdateBackground();

				//start drawing
				//clear SDL renderer
				SDL_RenderClear(renderer);

				//draw the background
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1pos);

				SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2pos);

				SDL_RenderCopy(renderer, title, NULL, &titlepos);

				SDL_RenderCopy(renderer, player1n, NULL, &player1npos);

				SDL_RenderCopy(renderer, player1o, NULL, &player1npos);

				SDL_RenderCopy(renderer, player2n, NULL, &player2npos);

				SDL_RenderCopy(renderer, player2o, NULL, &player2npos);

				SDL_RenderCopy(renderer, instructn, NULL, &instructnpos);

				SDL_RenderCopy(renderer, instructo, NULL, &instructnpos);

				SDL_RenderCopy(renderer, quitn, NULL, &quitnpos);

				SDL_RenderCopy(renderer, quito, NULL, &quitnpos);

				SDL_RenderCopy(renderer, reticle, NULL, &reticlepos);

				//SDL Render present
				SDL_RenderPresent(renderer);

			}
			break;				//end main menu case

		case INSTRUCTIONS:
			instructions = true;
			cout << "the gamestate is Instructions" << endl;
			cout << "Press the A button to go to Menu" << endl;
			cout << endl;
			while (instructions) {
				thistime = SDL_GetTicks();
				deltaTime = (float) (thistime - lasttime) / 1000;
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
								instructions = false;
								gameState = MENU;

							}

						}
						break;
					}
				}

				//update section
				UpdateBackground();

				//start drawing
				//clear SDL renderer
				SDL_RenderClear(renderer);

				//drae the background
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1pos);

				SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2pos);

				SDL_RenderCopy(renderer, title, NULL, &titlepos);

				SDL_RenderCopy(renderer, instructtext, NULL, &instructtextpos);

				SDL_RenderCopy(renderer, reticle, NULL, &reticlepos);

				SDL_RenderCopy(renderer, menunorm, NULL, &menupos);

				SDL_RenderCopy(renderer, menuover, NULL, &menupos);

				//SDL Render present
				SDL_RenderPresent(renderer);
			}
			break;						//end instructions case

		case PLAYERS1:
			players1 = true;
			cout << "the gamestate is 1 Player Game" << endl;
			cout << "Press the A button for Win Screen" << endl;
			cout << "Press the B button for Lose Screen" << endl;
			cout << endl;
			while (players1) {
				thistime = SDL_GetTicks();
				deltaTime = (float) (thistime - lasttime) / 1000;
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
									== SDL_CONTROLLER_BUTTON_A) {
								players1 = false;
								gameState = WIN;

							}
							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_B) {
								players1 = false;
								gameState = LOSE;
							}

						}
						break;
					}
				}

				//update section
				UpdateBackground();

				//start drawing
				//clear SDL renderer
				SDL_RenderClear(renderer);

				//drae the background
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1pos);

				SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2pos);

				SDL_RenderCopy(renderer, player1n, NULL, &player1npos);

				//SDL Render present
				SDL_RenderPresent(renderer);
			}
			break;					//end player 1 case
		case PLAYERS2:
			players2 = true;
			cout << "the gamestate is 2 Player Game" << endl;
			cout << "Press the A button for Win Screen" << endl;
			cout << "Press the B button for Lose Screen" << endl;
			cout << endl;

			while (players2) {
				thistime = SDL_GetTicks();
				deltaTime = (float) (thistime - lasttime) / 1000;
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
						if (event.cdevice.which == 0) {
							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_A) {
								players2 = false;
								gameState = WIN;

							}
							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_B) {
								players2 = false;
								gameState = LOSE;
							}

						}
						break;
					}
				}
				//update section
				UpdateBackground();

				//start drawing
				//clear SDL renderer
				SDL_RenderClear(renderer);

				//drae the background
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1pos);

				SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2pos);

				SDL_RenderCopy(renderer, player2n, NULL, &player2npos);

				//SDL Render present
				SDL_RenderPresent(renderer);
			}
			break;										//end player 2 case
		case WIN:
			win = true;
			cout << "the gamestate is WIN Screen" << endl;
			cout << "Press the A button to go to Menu" << endl;
			cout << "Press the B button to Play Again" << endl;
			cout << endl;

			while (win) {

				thistime = SDL_GetTicks();
				deltaTime = (float) (thistime - lasttime) / 1000;
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
									== SDL_CONTROLLER_BUTTON_A) {
								win = false;
								gameState = MENU;

							}
							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_B) {
								win = false;
								gameState = PLAYERS1;
							}

						}
						break;
					}
				}
				//update section
				UpdateBackground();

				//start drawing
				//clear SDL renderer
				SDL_RenderClear(renderer);

				//drae the background
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1pos);

				SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2pos);

				SDL_RenderCopy(renderer, wintext, NULL, &winpos);

				SDL_RenderCopy(renderer, menunorm, NULL, &menupos);

				SDL_RenderCopy(renderer, menuover, NULL, &menupos);

				SDL_RenderCopy(renderer, playnorm, NULL, &playpos);

				SDL_RenderCopy(renderer, playover, NULL, &playpos);

				//SDL Render present
				SDL_RenderPresent(renderer);
			}
			break;										//end win case
		case LOSE:
			lose = true;
			cout << "the gamestate is WIN Screen" << endl;
			cout << "Press the A button to go to Menu" << endl;
			cout << "Press the B button to Replay game" << endl;
			cout << endl;

			while (lose) {

				thistime = SDL_GetTicks();
				deltaTime = (float) (thistime - lasttime) / 1000;
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
									== SDL_CONTROLLER_BUTTON_A) {
								lose = false;
								gameState = MENU;

							}
							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_B) {
								win = false;
								gameState = PLAYERS1;
							}

						}
						break;
					}
				}
				//update section
				UpdateBackground();

				//start drawing
				//clear SDL renderer
				SDL_RenderClear(renderer);

				//drae the background
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1pos);

				SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2pos);

				SDL_RenderCopy(renderer, losetext, NULL, &losepos);

				SDL_RenderCopy(renderer, menunorm, NULL, &menupos);

				SDL_RenderCopy(renderer, menuover, NULL, &menupos);

				SDL_RenderCopy(renderer, playnorm, NULL, &playpos);

				SDL_RenderCopy(renderer, playover, NULL, &playpos);

				//SDL Render present
				SDL_RenderPresent(renderer);
			}
			break;										//end win case
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
