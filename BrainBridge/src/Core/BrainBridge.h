#pragma once
#include <memory>
#include <unordered_map>

class BrainBridge{
public:
    BrainBridge();
    int Init();
    int Run();
private:
    bool bRunning = true;

    //Some sort of stack of screens
   //stack<
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
 
};

template<class T>
inline T* BrainBridge::CreateCommunicator(std::string name)
{
    //Communicators are injected with this brainbridge as its owner
    std::shared_ptr<T> com = std::make_shared<T>(this);

    mCommunicators.insert({ name, com });

    return com.get();
}
