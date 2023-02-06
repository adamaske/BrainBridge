#pragma once

#include "json/json.h"
class Headset {
public:
	Headset();
	Headset(const Json::Value& jheadset);
	//Init the headset from the json file
	void FromJson(const Json::Value& jheadset);
	//Get headset as string
	std::string HeadsetToString();
	//Variables for a headset
	std::string mID;
	std::string mLabel;
	std::string mConnectedBy;
	std::string mStatus;

};