#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "GameState.h"
#include "Asset.h"

// Override base class with your custom functionality
class Example : public olc::PixelGameEngine
{
public:
	Example()
	{
		// Name you application
		sAppName = "Example";
	}

public:
	State *temp, *state = new SplashState();

	bool OnUserCreate() override
	{
		asset::loadAllAssets();
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		if (state == nullptr) { return false; }
		else { 
			temp = state->run(fElapsedTime, this); 
			if (state != temp) { 
				delete state;
				state = temp; 
			}
		}
		return true;
	}
};

int main()
{
	Example demo;
	if (demo.Construct(400, 300, 2, 2))
		demo.Start();
	return 0;
}
