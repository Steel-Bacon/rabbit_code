#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "GameState.h"
#include "Asset.h"

// Override base class with your custom functionality
class GameEngine : public olc::PixelGameEngine {
private:
	shi::StateManager stateManager;

public:
	GameEngine()
	{
		// Name you application
		sAppName = "Example";
	}

	bool OnUserCreate() override
	{
		asset::loadAllAssets();
		stateManager.setState<SplashState>();
		stateManager.setFPS(60);
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		return stateManager.run(fElapsedTime, this);
	}
};

int main() {
	GameEngine game;
	if (game.Construct(400, 300, 2, 2))
		game.Start();
	return 0;
}
