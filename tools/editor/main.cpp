#include <editor-version/Repository.h>

#include <wx/filedlg.h>
#include <wx/stdpaths.h>
#include <wx/wx.h>

namespace
{

class MainFrame : public wxFrame
{
public:
    MainFrame();

private:
    void OnNew(wxCommandEvent &event);
    void OnOpen(wxCommandEvent &event);
    void OnSave(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
    void OnUndo(wxCommandEvent &event);
    void OnRedo(wxCommandEvent &event);
    void OnCut(wxCommandEvent &event);
    void OnCopy(wxCommandEvent &event);
    void OnPaste(wxCommandEvent &event);

    wxTextCtrl *m_textCtrl;
    wxString m_filePath;
};

class EditorApp : public wxApp
{
public:
    bool OnInit() override;
};

MainFrame::MainFrame():
    wxFrame(nullptr, wxID_ANY, "Editor", wxDefaultPosition, wxSize(800, 600))
{
    wxMenuBar *menuBar = new wxMenuBar();

    wxMenu *fileMenu = new wxMenu();
    fileMenu->Append(wxID_NEW, "&New\tCtrl+N");
    fileMenu->Append(wxID_OPEN, "&Open\tCtrl+O");
    fileMenu->Append(wxID_SAVE, "&Save\tCtrl+S");
    fileMenu->AppendSeparator();
    fileMenu->Append(wxID_EXIT, "E&xit\tAlt+F4");
    menuBar->Append(fileMenu, "&File");

    wxMenu *editMenu = new wxMenu();
    editMenu->Append(wxID_UNDO, "&Undo\tCtrl+Z");
    editMenu->Append(wxID_REDO, "&Redo\tCtrl+Y");
    editMenu->AppendSeparator();
    editMenu->Append(wxID_CUT, "Cu&t\tCtrl+X");
    editMenu->Append(wxID_COPY, "&Copy\tCtrl+C");
    editMenu->Append(wxID_PASTE, "&Paste\tCtrl+V");
    menuBar->Append(editMenu, "&Edit");

    wxMenu *helpMenu = new wxMenu();
    helpMenu->Append(wxID_ABOUT, "&About");
    menuBar->Append(helpMenu, "&Help");

    wxFrameBase::SetMenuBar(menuBar);

    wxFrameBase::CreateStatusBar();
    wxFrameBase::SetStatusText("Ready");

    m_textCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);

    Bind(wxEVT_MENU, &MainFrame::OnNew, this, wxID_NEW);
    Bind(wxEVT_MENU, &MainFrame::OnOpen, this, wxID_OPEN);
    Bind(wxEVT_MENU, &MainFrame::OnSave, this, wxID_SAVE);
    Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainFrame::OnUndo, this, wxID_UNDO);
    Bind(wxEVT_MENU, &MainFrame::OnRedo, this, wxID_REDO);
    Bind(wxEVT_MENU, &MainFrame::OnCut, this, wxID_CUT);
    Bind(wxEVT_MENU, &MainFrame::OnCopy, this, wxID_COPY);
    Bind(wxEVT_MENU, &MainFrame::OnPaste, this, wxID_PASTE);
}

void MainFrame::OnNew(wxCommandEvent &event)
{
    m_textCtrl->Clear();
    m_filePath.Clear();
    SetTitle("Editor");
}

void MainFrame::OnOpen(wxCommandEvent &event)
{
    wxFileDialog dialog(this, "Open File", "", "",
        "Text files (*.txt)|*.txt|All files (*.*)|*.*",
        wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (dialog.ShowModal() == wxID_OK)
    {
        m_filePath = dialog.GetPath();
        m_textCtrl->LoadFile(m_filePath);
        SetTitle("Editor - " + dialog.GetFilename());
    }
}

void MainFrame::OnSave(wxCommandEvent &event)
{
    if (m_filePath.IsEmpty())
    {
        wxFileDialog dialog(this, "Save File", "", "",
            "Text files (*.txt)|*.txt|All files (*.*)|*.*",
            wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

        if (dialog.ShowModal() == wxID_OK)
        {
            m_filePath = dialog.GetPath();
            m_textCtrl->SaveFile(m_filePath);
            SetTitle("Editor - " + dialog.GetFilename());
        }
    }
    else
    {
        m_textCtrl->SaveFile(m_filePath);
    }
}

void MainFrame::OnExit(wxCommandEvent &event)
{
    Close(true);
}

void MainFrame::OnAbout(wxCommandEvent &event)
{
    wxMessageBox("Editor Application", "About", wxOK | wxICON_INFORMATION, this);
}

void MainFrame::OnUndo(wxCommandEvent &event)
{
    m_textCtrl->Undo();
}

void MainFrame::OnRedo(wxCommandEvent &event)
{
    m_textCtrl->Redo();
}

void MainFrame::OnCut(wxCommandEvent &event)
{
    m_textCtrl->Cut();
}

void MainFrame::OnCopy(wxCommandEvent &event)
{
    m_textCtrl->Copy();
}

void MainFrame::OnPaste(wxCommandEvent &event)
{
    m_textCtrl->Paste();
}

bool EditorApp::OnInit()
{
    std::filesystem::path dir{wxStandardPaths::Get().GetUserDataDir().ToStdString()};
    dir /= "UtahCpp";
    dir /= "Editor-Git";
    if (!std::filesystem::is_directory(dir))
    {
        std::filesystem::create_directories(dir);
    }
    std::shared_ptr repo{
        std::filesystem::is_directory(dir / ".git") ? version::open_repository(dir) : version::create_repository(dir)};

    MainFrame *frame = new MainFrame();
    frame->Show(true);
    return true;
}

} // namespace

wxIMPLEMENT_APP(EditorApp);
