///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jul 13 2016)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "MyFrame_generated.h"


///////////////////////////////////////////////////////////////////////////

MyFrame_generated::MyFrame_generated(wxWindow* parent,
        wxWindowID id,
        const wxString& title,
        const wxPoint& pos,
        const wxSize& size, long style)
: wxFrame(parent, id, title, pos, size, style) {
    this->SetSizeHints(wxDefaultSize, wxDefaultSize);

    wxBoxSizer* bSizer1;
    bSizer1 = new wxBoxSizer(wxHORIZONTAL);

    wxBoxSizer* bSizer3;
    bSizer3 = new wxBoxSizer(wxVERTICAL);

    m_startButton = new wxButton(this, wxID_ANY, wxT("Start "), wxDefaultPosition, wxDefaultSize, wxBU_LEFT);
    bSizer3->Add(m_startButton, 0, wxALL, 5);

    m_button6 = new wxButton(this, wxID_ANY, wxT("Add Price Observer"), wxDefaultPosition, wxDefaultSize, 0);
    bSizer3->Add(m_button6, 0, wxALL, 5);

    m_button7 = new wxButton(this, wxID_ANY, wxT("Add High Observer"), wxDefaultPosition, wxDefaultSize, 0);
    bSizer3->Add(m_button7, 0, wxALL, 5);

    m_button8 = new wxButton(this, wxID_ANY, wxT("Add Low Observer"), wxDefaultPosition, wxDefaultSize, 0);
    bSizer3->Add(m_button8, 0, wxALL, 5);

    m_button9 = new wxButton(this, wxID_ANY, wxT("Add Average Observer"), wxDefaultPosition, wxDefaultSize, 0);
    bSizer3->Add(m_button9, 0, wxALL, 5);


    bSizer1->Add(bSizer3, 1, 0, 5);

    wxGridSizer* gSizer2;
    gSizer2 = new wxGridSizer(0, 2, 0, 0);

    m_staticText2 = new wxStaticText(this, wxID_ANY, wxT("Price"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticText2->Wrap(-1);
    gSizer2->Add(m_staticText2, 0, wxALL, 5);

    m_textCtrlPrice = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    gSizer2->Add(m_textCtrlPrice, 0, wxALL, 5);

    m_staticText3 = new wxStaticText(this, wxID_ANY, wxT("High"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticText3->Wrap(-1);
    gSizer2->Add(m_staticText3, 0, wxALL, 5);

    m_textCtrlHigh = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    gSizer2->Add(m_textCtrlHigh, 0, wxALL, 5);

    m_staticText4 = new wxStaticText(this, wxID_ANY, wxT("Low"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticText4->Wrap(-1);
    gSizer2->Add(m_staticText4, 0, wxALL, 5);

    m_textCtrlLow = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    gSizer2->Add(m_textCtrlLow, 0, wxALL, 5);

    m_staticText5 = new wxStaticText(this, wxID_ANY, wxT("Average"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticText5->Wrap(-1);
    gSizer2->Add(m_staticText5, 0, wxALL, 5);

    m_textCtrlAverage = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    gSizer2->Add(m_textCtrlAverage, 0, wxALL, 5);


    bSizer1->Add(gSizer2, 1, wxEXPAND, 5);


    this->SetSizer(bSizer1);
    this->Layout();
    m_statusBar1 = this->CreateStatusBar(1, wxST_SIZEGRIP, wxID_ANY);
    m_menubar1 = new wxMenuBar(0);
    m_menu1 = new wxMenu();
    wxMenuItem* m_menuItem1;
    m_menuItem1 = new wxMenuItem(m_menu1, wxID_ANY, wxString(wxT("Exit")), wxEmptyString, wxITEM_NORMAL);
    m_menu1->Append(m_menuItem1);

    m_menubar1->Append(m_menu1, wxT("MyMenu"));

    this->SetMenuBar(m_menubar1);


    this->Centre(wxBOTH);

    // Connect Events
    m_startButton->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame_generated::onStartButtonClicked), NULL, this);
    m_button6->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame_generated::onAddPriceObserverClicked), NULL, this);
    m_button7->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame_generated::onAddHighObserverClicked), NULL, this);
    m_button8->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame_generated::onAddLowObserverClicked), NULL, this);
    m_button9->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame_generated::onAddAverageObserverClicked), NULL, this);
}

MyFrame_generated::~MyFrame_generated() {
    // Disconnect Events
    m_startButton->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame_generated::onStartButtonClicked), NULL, this);
    m_button6->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame_generated::onAddPriceObserverClicked), NULL, this);
    m_button7->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame_generated::onAddHighObserverClicked), NULL, this);
    m_button8->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame_generated::onAddLowObserverClicked), NULL, this);
    m_button9->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame_generated::onAddAverageObserverClicked), NULL, this);
}

