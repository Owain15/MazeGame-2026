
#include "src/componentes.h"
#include "windows/application.h"


int main()
{
	MazeGame::Player player(
		{ 100.0f, 200.0f, 50.0f, 50.0f },
		{ 0.0f, 1.0f, 0.0f, 1.0f },
		0.0f);

	MazeGame::Wall testWall(
		{ 300.0f, 400.0f, 400.0f, 5.0f },
		{ 1.0f, .0f, 0.0f, 1.0f },
		0.0f);

	SeraphimEngine::Windows::Application app = SeraphimEngine::Windows::Application(player,testWall);
	

	app.Run();


    return 0;

}

