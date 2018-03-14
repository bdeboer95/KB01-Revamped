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
			resourceManager->InitResourceLoader(static_cast<LPDIRECT3DDEVICE9>(renderer->GetDevice()));
			Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsNotNull(resourceManager->LoadMesh("Tiger.x"));
		}

		TEST_METHOD(LoadMeshUnknown)
		{
			Renderer* renderer = new RendererDx();
			ResourceManager* resourceManager = new ResourceManager();
			renderer->InitDevice(GetForegroundWindow());
			resourceManager->InitResourceLoader(static_cast<LPDIRECT3DDEVICE9>(renderer->GetDevice()));
			Microsoft::VisualStudio::CppUnitTestFramework::Assert::IsNull(resourceManager->LoadMesh("Idontexist"));
		}

		TEST_METHOD(InitResourceLoader)
		{
			Renderer* renderer2 = new RendererDx();
			ResourceManager* resourceManager2 = new ResourceManager();
			Microsoft::VisualStudio::CppUnitTestFramework::Assert::AreEqual(true, resourceManager2->InitResourceLoader(renderer2->GetDevice()));
		}

	};
}