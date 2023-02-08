#pragma once
#include "../Core/BBGUID.h"
class System : public BBGUID {
public:
	System();
	System(class BrainBridge* bb);
	~System();

	virtual void Init();
	virtual void Run();
	//Some sort of stack of screens
	std::unordered_map<std::string, std::shared_ptr<class BBWindow>> mWindows;
	void InsertWindow(BBWindow* window);
protected:
	BrainBridge* mBrainBridge;

	//Systems
	std::unordered_map<std::string, std::shared_ptr<System>> mSystems;
public:
	//Systems that are children of the
	void InsertSystem(System& system);
	System* GetSystem(std::string& name);
};

class MainMenuSystem : public System {
public:
	MainMenuSystem();
	~MainMenuSystem();

	void Init() override;
	void Run() override;
};