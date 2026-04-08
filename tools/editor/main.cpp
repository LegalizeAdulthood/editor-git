#include <editor-version/Repository.h>

#include <wx/filedlg.h>
#include <wx/listctrl.h>
#include <wx/stdpaths.h>
#include <wx/wx.h>

#include <filesystem>

namespace
{

class MainFrame : public wxFrame
{
public:
    explicit MainFrame(const std::filesystem::path &dir, version::RepositoryPtr repo);

private:
    void OnNew(wxCommandEvent &event);
    void OnOld(wxCommandEvent &event);
    void OnSave(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
    void OnUndo(wxCommandEvent &event);
    void OnRedo(wxCommandEvent &event);
    void OnCut(wxCommandEvent &event);
    void OnCopy(wxCommandEvent &event);
    void OnPaste(wxCommandEvent &event);

    wxTextCtrl *m_text_ctrl;
    std::filesystem::path m_file_path;
    version::RepositoryPtr m_repo;
};

class EditorApp : public wxApp
{
public:
    bool OnInit() override;
};

MainFrame::MainFrame(const std::filesystem::path &dir, version::RepositoryPtr repo) :
    wxFrame(nullptr, wxID_ANY, "Editor", wxDefaultPosition, wxSize(800, 600)),
    m_file_path(dir / "config.txt"),
    m_repo(repo)
{
    wxMenuBar *menu_bar = new wxMenuBar();

    wxMenu *file_menu = new wxMenu();
    file_menu->Append(wxID_NEW, "&New\tCtrl+N");
    file_menu->Append(wxID_OPEN, "&Old\tCtrl+O");
    file_menu->Append(wxID_SAVE, "&Save\tCtrl+S");
    file_menu->AppendSeparator();
    file_menu->Append(wxID_EXIT, "E&xit\tAlt+F4");
    menu_bar->Append(file_menu, "&File");

    wxMenu *edit_menu = new wxMenu();
    edit_menu->Append(wxID_UNDO, "&Undo\tCtrl+Z");
    edit_menu->Append(wxID_REDO, "&Redo\tCtrl+Y");
    edit_menu->AppendSeparator();
    edit_menu->Append(wxID_CUT, "Cu&t\tCtrl+X");
    edit_menu->Append(wxID_COPY, "&Copy\tCtrl+C");
    edit_menu->Append(wxID_PASTE, "&Paste\tCtrl+V");
    menu_bar->Append(edit_menu, "&Edit");

    wxMenu *help_menu = new wxMenu();
    help_menu->Append(wxID_ABOUT, "&About");
    menu_bar->Append(help_menu, "&Help");

    wxFrameBase::SetMenuBar(menu_bar);

    wxFrameBase::CreateStatusBar();
    wxFrameBase::SetStatusText("Ready");

    m_text_ctrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    if (std::filesystem::exists(m_file_path))
    {
        m_text_ctrl->LoadFile(m_file_path.string());
    }

    Bind(wxEVT_MENU, &MainFrame::OnNew, this, wxID_NEW);
    Bind(wxEVT_MENU, &MainFrame::OnOld, this, wxID_OPEN);
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
    m_text_ctrl->Clear();
    SetTitle("Editor");
}

void MainFrame::OnOld(wxCommandEvent &event)
{
    version::History history = m_repo->get_file_history(m_file_path.filename().string().c_str());

    wxDialog dialog(this, wxID_ANY, "File History", wxDefaultPosition, wxSize(600, 400));
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    wxListCtrl *list =
        new wxListCtrl(&dialog, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL);
    list->InsertColumn(0, "Commit ID", wxLIST_FORMAT_LEFT, 80);
    list->InsertColumn(1, "Timestamp", wxLIST_FORMAT_LEFT, 150);
    list->InsertColumn(2, "Message", wxLIST_FORMAT_LEFT, 350);

    long index = 0;
    for (const auto &commit : history)
    {
        list->InsertItem(index, commit.id.substr(0, 8));
        list->SetItem(index, 1, commit.timestamp);
        list->SetItem(index, 2, commit.message);
        list->SetItemPtrData(index, reinterpret_cast<wxUIntPtr>(&commit));
        ++index;
    }

    // NOLINTBEGIN(bugprone-suspicious-enum-usage, clang-diagnostic-enum-enum-conversion)
    sizer->Add(list, 1, wxEXPAND | wxALL, 10);
    sizer->Add(dialog.CreateButtonSizer(wxOK | wxCANCEL), 0, wxALIGN_CENTER | wxBOTTOM, 10);
    // NOLINTend(bugprone-suspicious-enum-usage, clang-diagnostic-enum-enum-conversion)
    dialog.SetSizer(sizer);

    wxButton *ok_button = wxDynamicCast(dialog.FindWindow(wxID_OK), wxButton);
    ok_button->Disable();

    list->Bind(wxEVT_LIST_ITEM_SELECTED, [ok_button](wxListEvent &) { ok_button->Enable(); });
    list->Bind(wxEVT_LIST_ITEM_DESELECTED, [ok_button](wxListEvent &) { ok_button->Disable(); });

    if (dialog.ShowModal() == wxID_OK)
    {
        long selected = list->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
        if (selected != -1)
        {
            const auto *commit = reinterpret_cast<const version::Commit *>(list->GetItemData(selected));
            std::string content = m_repo->get_file_content(commit->id.c_str(), m_file_path.filename().string().c_str());
            m_text_ctrl->SetValue(content);
            m_text_ctrl->SaveFile(m_file_path.string());
        }
    }
}

void MainFrame::OnSave(wxCommandEvent &event)
{
    wxTextEntryDialog dialog(this, "Enter commit message:", "Save", "Checkpoint");
    if (dialog.ShowModal() == wxID_OK)
    {
        m_text_ctrl->SaveFile(m_file_path.string());
        m_repo->commit_file(m_file_path.filename().string().c_str(), dialog.GetValue().ToStdString().c_str());
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
    m_text_ctrl->Undo();
}

void MainFrame::OnRedo(wxCommandEvent &event)
{
    m_text_ctrl->Redo();
}

void MainFrame::OnCut(wxCommandEvent &event)
{
    m_text_ctrl->Cut();
}

void MainFrame::OnCopy(wxCommandEvent &event)
{
    m_text_ctrl->Copy();
}

void MainFrame::OnPaste(wxCommandEvent &event)
{
    m_text_ctrl->Paste();
}

bool EditorApp::OnInit()
{
    SetVendorName("UtahCpp");
    SetAppName("Editor");
    wxStandardPaths::Get().UseAppInfo(wxStandardPaths::AppInfo_VendorName | wxStandardPaths::AppInfo_AppName);
    const std::filesystem::path dir{wxStandardPaths::Get().GetUserDataDir().ToStdString()};
    if (!std::filesystem::is_directory(dir))
    {
        std::filesystem::create_directories(dir);
    }
    version::RepositoryPtr repo{
        std::filesystem::is_directory(dir / ".git") ? version::open_repository(dir) : version::create_repository(dir)};

    MainFrame *frame = new MainFrame(dir, repo);
    frame->Show(true);
    return true;
}

} // namespace

wxIMPLEMENT_APP(EditorApp);
