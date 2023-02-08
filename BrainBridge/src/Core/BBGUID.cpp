#include "BBGUID.h"
#include <random>

//Setting up the random generator, this is boilerplate
static std::random_device sRandomDevice;
static std::mt19937_64 sEngine(sRandomDevice());
static std::uniform_int_distribution<uint64_t> sUniformDistribution;

//Set mID to a random 128bit number
BBGUID::BBGUID() : mID(sUniformDistribution(sEngine))
{

}

BBGUID::BBGUID(uint64_t guid) : mID(guid)
{
}

uint64_t BBGUID::ID()
{
	return mID;
}
