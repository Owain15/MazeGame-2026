
#include "src/testObject.h"
#include "windows/application.h"


int main()
{

	MazeGame::TestObject tObject(
		{ 100.0f, 100.0f, 200.0f, 150.0f },
		{ 1.0f, 0.0f, 0.0f, 1.0f },
		120.0f);

	SeraphimEngine::Windows::Application app = SeraphimEngine::Windows::Application(tObject);
	

	app.Run();


    return 0;

}

