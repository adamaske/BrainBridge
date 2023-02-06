#pragma once
//The cortex communicator is responsible for sending and receiving to and from the driver to the cortex
class CortexCommunicator : public Communicator {
public:
    CortexCommunicator(BrainBridge* own);

    virtual int Init() override;
    virtual bool Connect() override;
};