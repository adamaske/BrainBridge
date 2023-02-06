#include "pch.h"
#include "Communicator.h"
#include "CortexCommunicator.h"
#include "BrainBridge.h"
CortexCommunicator::CortexCommunicator(BrainBridge* own) : Communicator(own) {
    std::cout << "Cortex Communicator Created\n";
}
int CortexCommunicator::Init()
{
    return 1;
}
bool CortexCommunicator::Connect()
{
    return false;
}
;