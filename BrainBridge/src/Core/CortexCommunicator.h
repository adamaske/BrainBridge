#pragma once
#include <wx/wx.h>
#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp> 
#include <boost/beast/websocket/ssl.hpp>
#include <boost/asio/strand.hpp>

using tcp = boost::asio::ip::tcp;

//The cortex communicator is responsible for sending and receiving to and from the driver to the cortex
class CortexCommunicator : public Communicator {
public:
    CortexCommunicator(BrainBridge* own);

    virtual int Init() override;
    virtual bool Connect() override;
    
};

class CortexWindow : public wxFrame {
public:
    CortexWindow();
    ~CortexWindow();


};