#include "stdafx.h"
#include "CppUnitTest.h"
#include "ResourceManager.h"
#include "RendererDx.h"

namespace KB01EngineTest
{
	TEST_CLASS(ResourceManagerTest)
	{

	public:

		TEST_METHOD(LoadMesh)
		{
			Renderer* renderer = new RendererDx();
			ResourceManager* resourceManager = new ResourceManager();
			renderer->InitDevice(GetForegroundWindow());
			resourceManager->InitResourceLoader(renderer);
			Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsNotNull(resourceManager->LoadMesh("..\\Meshes\\", "Tiger.x"));
		}

		TEST_METHOD(LoadMeshUnknown)
		{
			Renderer* renderer = new RendererDx();
			ResourceManager* resourceManager = new ResourceManager();
			renderer->InitDevice(GetForegroundWindow());
			resourceManager->InitResourceLoader(renderer);
			Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsNull(resourceManager->LoadMesh("..\\Meshes\\", "Idontexist"));
		}

		TEST_METHOD(InitResourceLoader)
		{
			Renderer* renderer = new RendererDx();
			ResourceManager* resourceManager = new ResourceManager();
			Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(true, resourceManager->InitResourceLoader(renderer));
		}

	};
}