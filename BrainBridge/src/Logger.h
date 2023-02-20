#pragma once
enum LogLevel{ info, error};
#define LOG_BB() Logger DoLog()
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
		std::cout << id << "\n";
		return *this;
	}
	inline Logger& operator()(LogLevel level);

	LogLevel l;
	
private:
	//static Logger* mInstance;
	uint64_t id = BBGUID();
	std::string mMsg;

};

Logger& Logger::operator()(LogLevel level) {
	std::cout << "Operator overloaded";
	std::cout << id << "\n";
	return *this;
}