#include "pch.h"
#include "Communicator.h"
#include "UnrealCommunicator.h"

UnrealEngineCommunicator::UnrealEngineCommunicator(BrainBridge* own) : Communicator(own) {
    std::cout << "Unreal Engine Communicator Created\n";
}
int UnrealEngineCommunicator::Init()
{
    return 1;
}
bool UnrealEngineCommunicator::Connect()
{
    return false;
}
;