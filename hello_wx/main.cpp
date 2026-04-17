#include <wx/wx.h>

class MyApp : public wxApp
{
public:
    bool OnInit() override;
};

class MyFrame : public wxFrame
{
public:
    MyFrame();
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    // wxWidgets がトップレベルウィンドウのライフタイムを管理するため delete 不要
    MyFrame* frame = new MyFrame();
    frame->Show(true);
    return true;
}

MyFrame::MyFrame()
    : wxFrame(nullptr, wxID_ANY, "Hello World", wxDefaultPosition, wxSize(640, 480))
{
    // 子ウィジェットは親（panel / frame）が所有し、親の破棄時に自動解放される
    wxPanel* panel = new wxPanel(this);
    wxStaticText* text = new wxStaticText(
        panel, wxID_ANY, "Hello, World!",
        wxDefaultPosition, wxDefaultSize,
        wxALIGN_CENTER_HORIZONTAL);

    wxFont font = text->GetFont();
    font.SetPointSize(24);
    text->SetFont(font);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->AddStretchSpacer(1);
    sizer->Add(text, 0, wxALIGN_CENTER_HORIZONTAL);
    sizer->AddStretchSpacer(1);
    panel->SetSizer(sizer);
}
