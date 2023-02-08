#include "pch.h"

#include "BBWindow.h"
#include "BBLogger.h"


BBLogger::BBLogger() : BBWindow()
{
	//Need a list box
	//Some text box

	auto list = new wxListBox(this, wxID_ANY, wxPoint(10, 110), wxSize(300, 300));
}

BBLogger::~BBLogger()
{
}
