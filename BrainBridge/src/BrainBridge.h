#pragma once
#include <wx/wx.h>

class BrainBridge  {
public:
    BrainBridge();
    ~BrainBridge();
    //This is the one running on the main thread
    int Run();
private:
    bool bRunning = true;

  
    //Logging
    //Logger
    std::shared_ptr<class BBLogger> mLoggerFrame;

    template<class T>
    T* CreateCommunicator(std::string name);
    std::unordered_map<std::string, std::shared_ptr<class Communicator>> mCommunicators;

    //Networking
    //a client for sending data to unreal engine
    //A server for sending and recv from Cortex
    //Stand-in function for recieveing over TCP
    void Recv();
    void HandleMethod(const std::string& method);
    std::unordered_map<std::string, bool> mActiveFunctions;

    //
    void CreateProfile(const std::string& method);

    float mAsyncTickRate = 1;
    int mAsyncTickRateSeconds = 1 / mAsyncTickRate;
 
    
    //Windows
    std::unordered_map<std::string, std::shared_ptr<class Window>> mWindows;

    //Systems
    std::unordered_map<std::string, std::shared_ptr<class System>> mSystems;
    //Add a system to the lowest level of application
    void InsertSystem(System& system);
    System* GetSystem(std::string& name);
    //Must be run on thread
    void HandleSystems();

    //Threading
    std::vector<std::thread> mThreads;

};

template<class T>
inline T* BrainBridge::CreateCommunicator(std::string name)
{
    //Communicators are injected with this brainbridge as its owner
    std::shared_ptr<T> com = std::make_shared<T>(this);

    mCommunicators.insert({ name, com });

    return com.get();
}
