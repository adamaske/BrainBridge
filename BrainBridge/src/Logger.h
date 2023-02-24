#pragma once
enum LogLevel{ info, error};
enum LogAction{ end, start, etc};
#define INIT_LOG Logger Log()
struct Logged {

};

class Logger {
public:
	Logger();

	//When wanting to call Logger[info]
	///We need a function whic
	template<typename T>
	Logger& operator<<(const T& message) {
		std::ostringstream stream;
		stream << message;
		std::cout << message;
		return *this;
	}
	inline Logger& operator()(Logger& logger, LogLevel level);
	inline Logger& operator()(LogLevel level);
	inline Logger& operator()(LogAction action);
	LogLevel l;

	void EndLoggingCurrent();
private:
	//static Logger* mInstance;
	uint64_t id = BBGUID();
	std::string mMsg;
	std::vector<std::shared_ptr<Logged>> mLogged;
};

inline Logger& Logger::operator()(Logger& logger, LogLevel level)
{
	// TODO: insert return statement here

	return *this;
}

Logger& Logger::operator()(LogLevel level) {

	return *this;
}
Logger& Logger::operator()(LogAction action) {
	if (action == end) {
		//End the logging here
		EndLoggingCurrent();
	}

	return *this;
}

inline void Logger::EndLoggingCurrent()
{
	//If were already logging
}
