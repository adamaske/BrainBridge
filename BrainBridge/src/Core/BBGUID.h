#pragma once

#include <xhash>
//Class for giving everythig uniqe identiferes so that stuff can be saved
class BBGUID {
public:
	BBGUID();
	BBGUID(uint64_t guid);
	BBGUID(const BBGUID&) = default;

	//Returns the GUID
	uint64_t ID();

	operator uint64_t() const { return mID; };
private:
	uint64_t mID = 0;
};

//TODO
//Overridden hash function, this is gotten from a Cherno video, go back to find reasions and refrences here
namespace std {
	//Override how this class is hashed, just hash the mID through the operator override
	template <>
	struct hash<BBGUID>
	{
		std::size_t operator()(const BBGUID& guid) const {
			return hash<uint64_t>()((uint64_t)guid);
		}
	};
}