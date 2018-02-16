#include "SceneManagerFacade.h"


/// <summary>
/// Initializes a new instance of the <see cref="SceneManagerFacade"/> class.
/// </summary>
SceneManagerFacade::SceneManagerFacade()
{
}


/// <summary>
/// Finalizes an instance of the <see cref="SceneManagerFacade"/> class.
/// </summary>
SceneManagerFacade::~SceneManagerFacade()
{

}

//void SceneManagerFacade::PrepareScenes(ResourceManager* _resourceManager, Renderer* _renderer)
//{
//	sceneManager->PrepareScenes();
//}
Scene* SceneManagerFacade::CreateScene(int _levelIndex, HWND _handler, std::string _level)
{
	std::ifstream file(_level);
	if (!file.good())
	{
		int mb = MessageBox(NULL, L"Level file is not found.", L"Error", MB_ICONERROR);

		switch (mb)
		{
		case IDOK:
			Log::Instance()->LogMessage("SceneManagerFacade - Level file is not found.", Log::MESSAGE_ERROR);
			std::exit(0);
		}
	}

	return sceneManager->CreateScene(_levelIndex, _handler, _level);
}