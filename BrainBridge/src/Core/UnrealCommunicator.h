#pragma once
//The Unreal communicator is responsible for sending and receiving to and from the driver to Unreal
class UnrealEngineCommunicator : public Communicator {
public:
    UnrealEngineCommunicator(BrainBridge* own);

    virtual int Init() override;
    virtual bool Connect() override;
};