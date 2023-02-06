
#include "Headset.h"

Headset::Headset()
{
}

Headset::Headset(const Json::Value& jheadset)
{
	FromJson(jheadset);
}
//Reads the const json value
void Headset::FromJson(const Json::Value& jheadset)
{
	mID = jheadset["id"].asString();
	mLabel = jheadset["label"].asString();
	mConnectedBy = jheadset["connectedBy"].asString();
	mStatus = jheadset["status"].asString();
}

std::string Headset::HeadsetToString()
{
	std::string string = (mID + ", " + mStatus + " " + mConnectedBy);
	return string;
}
