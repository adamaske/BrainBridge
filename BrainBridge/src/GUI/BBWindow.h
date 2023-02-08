#pragma once
#include "wx/wx.h"
class BBWindow : public wxFrame, public BBGUID {
public:
	BBWindow();
	BBWindow(BBWindow* parent);
	~BBWindow();

	//void OnOpen();
	//void OnClose();
	//
	//void OnRefresh();

private:
	void OnHello(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

	//Parent window
	BBWindow* mRoot;
	//Not shared because this should not extend lifetime of antoher window
	std::vector<BBWindow*> mWindows;

};

