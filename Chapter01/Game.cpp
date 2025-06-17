#include "Game.h"

const int thickness = 15;
const float paddleH = 100;

Game::Game()
	:mWindow(nullptr)
	, mRenderer(nullptr)
	, mIsRunning(true)
{

}

bool Game::Initialize() 
{
	bool success = SDL_Init(SDL_INIT_VIDEO);
	if (!success)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow("Game Programming in C++ (Chapter 1)", 1024, 768, 0);
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	
	mRenderer = SDL_CreateRenderer(mWindow, NULL);
	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	if (!SDL_SetRenderVSync(mRenderer, 1)) {
		SDL_Log("Failed to enable VSync: %s", SDL_GetError());
		return false;
	}

	mPaddlePos.x = 10;
	mPaddlePos.y = 768 / 2;
	
	mBallPos.x = 1024 / 2;
	mBallPos.y = 768 / 2;

	return true;
}

void Game::RunLoop() 
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_EVENT_QUIT:
				mIsRunning = false;
				break;
		}
	}

	const bool* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
}

void Game::UpdateGame()
{

}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mRenderer);

	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

	// Top wall
	SDL_FRect wall{ 0, 0, 1024, thickness };
	SDL_RenderFillRect(mRenderer, &wall);

	// Bottom wall
	wall.y = 768 - thickness;
	SDL_RenderFillRect(mRenderer, &wall);

	// Right wall
	wall.x = 1024 - thickness;
	wall.y = 0;
	wall.w = thickness;
	wall.h = 1024;
	SDL_RenderFillRect(mRenderer, &wall);

	SDL_FRect paddle{ mPaddlePos.x, mPaddlePos.y - paddleH / 2, thickness, paddleH };
	SDL_RenderFillRect(mRenderer, &paddle);

	SDL_FRect ball{ mBallPos.x - thickness / 2, mBallPos.y - thickness / 2, thickness, thickness };
	SDL_RenderFillRect(mRenderer, &ball);

	SDL_RenderPresent(mRenderer);
}

void Game::Shutdown() 
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}
