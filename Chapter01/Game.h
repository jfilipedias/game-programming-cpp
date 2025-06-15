#pragma once
#include <SDL3/SDL.h>

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();
private:
	// Helper functions for the game loop
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	// Window created by SDL
	SDL_Window* mWindow;
	bool mIsRunning;
};
