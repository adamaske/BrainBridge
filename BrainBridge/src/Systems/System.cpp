#include "pch.h"
#include "System.h"

#include "../BrainBridge.h"

System::System()
{
}

System::System(BrainBridge* bb) : mBrainBridge(bb) {

}

System::~System() {

}

void System::Init()
{
}

void System::Run()
{
}

void System::InsertWindow(BBWindow* window) {

}

void System::InsertSystem(System& system)
{
}

System* System::GetSystem(std::string& name)
{
	return nullptr;
}

MainMenuSystem::MainMenuSystem() 
{

}

MainMenuSystem::~MainMenuSystem()
{
}

void MainMenuSystem::Init()
{
	//Make a window and open it

}

void MainMenuSystem::Run()
{
}
