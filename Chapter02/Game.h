#pragma once
#include "Math.h"
#include <SDL3/SDL.h>
#include <vector>

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);
	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint64 mTicksCount;
	bool mIsRunning;
	bool mUpdatingActors;

	std::vector<class Actor*> mActors;
	std::vector<class Actor*> mPenddingActors;
	std::vector<class SpriteComponent*> mSprites;
};

