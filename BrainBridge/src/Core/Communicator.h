#pragma once
class Communicator {
public:
    Communicator(class BrainBridge* own) : mOwner(own) {

    };
    virtual int Init();
    virtual bool Connect();
    //The communicator needs stuff
    //Map to hold queued requests from the driver
    std::unordered_map<int, std::string> mOutgoingRequests;
    //Called from the driver to send a request to the communicator
    void Request(const std::string& method);

protected:
    BrainBridge* mOwner;
};




