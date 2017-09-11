#include "Ablaze.h"

using namespace Ablaze;

class Game : public Application
{
private:


public:
	void Init() override
	{
		BuildWindow(1280, 720, "Ablaze");
	}

	void Tick() override
	{
	
	}

	void Update() override
	{
	
	}

	void Render() override
	{
		Application::Render();
		UpdateDisplay();
	}

};

int main()
{
	Game g;
	g.Start();
	return 0;
}