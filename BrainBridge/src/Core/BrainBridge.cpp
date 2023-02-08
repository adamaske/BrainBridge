#include "pch.h"
#include "BrainBridge.h"
#include "json/json.h"

#include "Communicator.h"
#include "CortexCommunicator.h"
#include "UnrealCommunicator.h"

/*
 * To get a client id and a client secret, you must connect to your Emotiv
 * account on emotiv.com and create a Cortex app.
 * https://www.emotiv.com/my-account/cortex-apps/
 */
static const std::string ClientID = "1KkcmNkhTy22HiM2CMzXz03nnvGV1T7950LtMoEc";
static const std::string ClientSecret = "dPb5EplnkaRFt7AVs1PuNOrTBGsp3HTEXBnUlX4A86p1Ev1V6OI5KMuPbOvPbpXq4AYQ9m6pNNcOnCr2KK5ETLsGyX94rJxhAHauZhQb1ADEML7jyHWhXMxd3CHcwPRS";

// The name of the training profile used for the facial expression and mental command
static const std::string TrainingProfileName = "example";

struct Command {
	std::string mCommandName = "Right";
	float mActivationTreshold = 0.2f;
};

struct TrainingProfile {
	std::string mProfileName = "Profile";
	std::vector<Command> mCommands;
};
// If you use an Epoc Flex headset, then you must put your configuration here
//static const Json::Value FlexMapping = {
//	{ "LA", "AF3" },
//	{ "LB", "AF7" }
//	// etc...
//};

BrainBridge::BrainBridge()
{
	
}

int BrainBridge::Init()
{
	return 1;
}

int BrainBridge::Run()
{
	int err = 0;
	//For this we're using Cortex and Unreal, these should be called from the gui
	auto cortex = CreateCommunicator<CortexCommunicator>("CortexCommunicator");
	err = cortex->Init();

	auto unreal = CreateCommunicator<UnrealEngineCommunicator>("UnrealEngineCommunicator");
	err = unreal->Init();

	return 0;
	while (true) {
		using dsec = std::chrono::duration<double>;
		auto invFpsLimit = std::chrono::duration_cast<std::chrono::system_clock::duration>(dsec{ 1. / mAsyncTickRate });
		auto m_BeginFrame = std::chrono::system_clock::now();
		auto m_EndFrame = m_BeginFrame + invFpsLimit;
		unsigned frame_count_per_second = 0;
		auto prev_time_in_seconds = std::chrono::time_point_cast<std::chrono::seconds>(m_BeginFrame);
		while (true)
		{
			// Do drawing work ...

			// This part is just measuring if we're keeping the frame rate.
			// It is not necessary to keep the frame rate.
			auto time_in_seconds = std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now());
			++frame_count_per_second;
			if (time_in_seconds > prev_time_in_seconds)
			{
				std::cerr << frame_count_per_second << " frames per second\n";
				frame_count_per_second = 0;
				prev_time_in_seconds = time_in_seconds;
			}

			// This part keeps the frame rate.
			std::this_thread::sleep_until(m_EndFrame);
			m_BeginFrame = m_EndFrame;
			m_EndFrame = m_BeginFrame + invFpsLimit;
		}
	}
	return 0;
	
	
	//We now have communicators up and running
	
	//The bci communicator wants a client and a server
	//The client for sending stuff to the cortex and a server for recieveing it

	//For unreal communicaton we want a server running listening for connections and data
	//This server will have a set IP and port (localhost)
	//The user must then plug this into unreal to establish a connection from unreal to this server

	//Array of the types of profiles the user can make
	std::vector<TrainingProfile> mTrainingProfiles;
	//Create and fill the a profile
	TrainingProfile car;
	car.mProfileName = "CarController";
	car.mCommands.push_back(Command{ "CarRight", 0 });
	//Add the profile
	mTrainingProfiles.push_back(car);

	std::cout << "Printing training profiles:\n";
	for (int i = 0; i < mTrainingProfiles.size(); i++) {
		std::cout << "\t" << mTrainingProfiles[i].mProfileName << "\n";
		//std::cout << "\tCommands:\n";
		for (int j = 0; j < mTrainingProfiles[i].mCommands.size(); j++) {
			std::cout << "\t\t" << mTrainingProfiles[i].mCommands[j].mCommandName << " : ";
			std::cout << mTrainingProfiles[i].mCommands[j].mActivationTreshold << "\n";
		}
	}
	std::cout << "Finished printing.\n\n";

	//All the time we need to send and receive data

	//Arcitechture
	//A connection is always between two decvis, and each side uses its own IP and port number. 
	//Usually one side is called the client, thoe other side the server.
	//The server is coninually waiting for incoming connections. This is called listening which is always done on a certain IP and port number.
	//A client can send request to connect to a certain IP and port number

	//A socket is "A pipe btewteen to computers on a network through which data flows"
	//Almost all WInsock function soperate on a socket, as its your handle to the conneciton. Bot sides of the connection use a socket. 
	//Sockets are also two-way, data can be both sent and recieved. 
	//There are two common types for a socket. Streaming and Datagram, TCP and UDP respectivly


	Recv();
	//ask the cortex for info

	//we want to connect to the cortex, Ask it access
	Json::Value params;
	params["clientId"] = ClientID;
	params["clientSecret"] = ClientSecret;
	//sendRequest("requestAccess", params);
	//(method == "requestAccess") {
	//	bool accessGranted = result["accessGranted"].toBool();
	//	QString message = result["message"].toString();
	//	emit requestAccessOk(accessGranted, message);
	// 
	//while (bRunning) {
	//	Milestones
	//
	//}

	return 1;
}

void BrainBridge::Recv()
{
	std::cout << "BrainBridge : Sending fake method to HandleMethod\n";
	//We now recieved a string as bytes
	std::string method = "{ \"method\" : \"StartDataStream\" }";
	HandleMethod(method);
}

void BrainBridge::HandleMethod(const std::string& method)
{
	std::cout << "Brian Bridge : Handle Method\n";
	//Create a json object from a string
	Json::CharReaderBuilder builder;
	Json::CharReader* reader = builder.newCharReader();
	//The json object
	Json::Value json;
	std::string errors;
	bool parsing = reader->parse(method.c_str(), method.c_str() + method.size(), &json, &errors);
	delete reader;
	//Chech if the parsing worked
	if (!parsing) {
		std::cout << "BrainBridge: HandleMethod : Failed to parse Json, errors:\n" << "\t" << errors << "\n";
		return;
	}
	//What method is this?
	std::cout << "Brain Bridge : Json method = " << json["method"].asString() << "\n";


	//std::string method = obj["method"].toStyledString();
	if (mActiveFunctions.find(method) == mActiveFunctions.end()) {
		//The function is not in the map

	}
	//The bool is not true, this is not an active function
	if (!mActiveFunctions[method]) {
		std::cout << "BrainBridge : HandleMethod : This function is not active!\n";
		return;
	}


}

void BrainBridge::CreateProfile(const std::string& method)
{

}

