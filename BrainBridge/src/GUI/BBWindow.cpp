#include "pch.h"
#include "BBWindow.h"


BBWindow::BBWindow() : wxFrame(nullptr, wxID_ANY, "BB Window"), BBGUID()
{
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(1, "&Hello...\tCtrl-H",
        "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);

    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");

    Bind(wxEVT_MENU, &BBWindow::OnHello, this, 1);
    Bind(wxEVT_MENU, &BBWindow::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &BBWindow::OnExit, this, wxID_EXIT);
}

BBWindow::~BBWindow()
{
    ID();
}
void BBWindow::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}
void BBWindow::OnExit(wxCommandEvent& event)
{
    wxLogMessage("Closed window!");
    Close(true);
}
void BBWindow::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a test", "About This");
}
