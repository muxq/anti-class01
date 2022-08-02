// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(VFC_MAINDLG_H__F8B54B81_B73A_4136_B8DF_03559AC62276__INCLUDED_)
#define VFC_MAINDLG_H__F8B54B81_B73A_4136_B8DF_03559AC62276__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
#include <exception>
#include <string>

class CMainDlg : public CDialogImpl<CMainDlg> {
private:
  std::string name_;
  std::string paswd_;

public:
  enum { IDD = IDD_MAINDLG };

  BEGIN_MSG_MAP(CMainDlg)
  MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
  COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
  COMMAND_ID_HANDLER(IDOK, OnOK)
  COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
  END_MSG_MAP()

  // Handler prototypes (uncomment arguments if needed):
  //	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM
  ///*lParam*/, BOOL& /*bHandled*/) 	LRESULT CommandHandler(WORD
  ////*wNotifyCode*/,
  // WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/) 	LRESULT
  // NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

  LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/,
                       BOOL & /*bHandled*/) {
    // center the dialog on the screen
    CenterWindow();

    // set icons
    HICON hIcon = (HICON)::LoadImage(
        _Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME),
        IMAGE_ICON, ::GetSystemMetrics(SM_CXICON),
        ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
    SetIcon(hIcon, TRUE);
    HICON hIconSmall = (HICON)::LoadImage(
        _Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME),
        IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON),
        ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
    SetIcon(hIconSmall, FALSE);
    char config[MAX_PATH];
    GetModuleFileNameA(NULL, config, sizeof(config));
    PathRemoveFileSpec(config);
    PathAppend(config, "config.ini");
    if (!PathFileExists(config)) {
      throw std::logic_error("config file not exist");
    }
    char buffer[MAX_PATH] = {0};
    GetPrivateProfileStringA("config", "name", NULL, buffer, sizeof(buffer),
                            config);
    if (2 == GetLastError()) {
      throw std::logic_error("config file not fond name param");
    }
    name_ = buffer;
    GetPrivateProfileStringA("config", "password", NULL, buffer, sizeof(buffer),
                            config);
    if (2 == GetLastError()) {
      throw std::logic_error("config file not fond password param");
    }
    paswd_ = buffer;
    return TRUE;
  }

  LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/,
                     BOOL & /*bHandled*/) {
    CSimpleDialog<IDD_ABOUTBOX, FALSE> dlg;
    dlg.DoModal();
    return 0;
  }

  LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/,
               BOOL & /*bHandled*/) {
    // TODO: Add validation code
    char name[1024];
    GetDlgItemText(IDC_EDIT_USER_NAME, name, sizeof(name));
    if (0 == strlen(name)) {
      MessageBox("请输入正确的账号", "错误", MB_OK);
      ::SetFocus(GetDlgItem(IDC_EDIT_USER_NAME));
      return 0;
    }
    char pasw[1024];
    GetDlgItemText(IDC_EDIT_USER_PASW, pasw, sizeof(pasw));
    if (0 == strlen(name)) {
      MessageBox("请输入正确的密码", "错误", MB_OK);
      ::SetFocus(GetDlgItem(IDC_EDIT_USER_PASW));
      return 0;
    }

    if (0 == strcmp(name, name_.c_str()) && 0 == strcmp(pasw, paswd_.c_str())) {
      MessageBox("登录成功", "提示", MB_OK);
      EndDialog(wID);
      return 0;
    }
    MessageBox("登录失败", "错误", MB_OK);
    return 0;
  }

  LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/,
                   BOOL & /*bHandled*/) {
    EndDialog(wID);
    return 0;
  }
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// VisualFC AppWizard will insert additional declarations immediately before the
// previous line.

#endif // !defined(VFC_MAINDLG_H__F8B54B81_B73A_4136_B8DF_03559AC62276__INCLUDED_)
