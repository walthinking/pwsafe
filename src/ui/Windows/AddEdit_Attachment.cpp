/*
* Copyright (c) 2003-2014 Rony Shapiro <ronys@users.sourceforge.net>.
* All rights reserved. Use of the code is allowed under the
* Artistic License 2.0 terms, as specified in the LICENSE file
* distributed with this code, or available from
* http://www.opensource.org/licenses/artistic-license-2.0.php
*/
// AddEdit_Attachment.cpp : implementation file
//

#include "stdafx.h"
#include "PasswordSafe.h"

#include "ThisMfcApp.h"    // For Help
#include "DboxMain.h"

#include "AddEdit_Attachment.h"
#include "AddEdit_PropertySheet.h"

/////////////////////////////////////////////////////////////////////////////
// CAddEdit_DateTimes property page

IMPLEMENT_DYNAMIC(CAddEdit_Attachment, CAddEdit_PropertyPage)

CAddEdit_Attachment::CAddEdit_Attachment(CWnd *pParent, st_AE_master_data *pAEMD)
  : CAddEdit_PropertyPage(pParent, 
                          CAddEdit_Attachment::IDD, CAddEdit_Attachment::IDD_SHORT,
                          pAEMD),
  m_bInitdone(false), m_AttName(_T("")), m_AttFile(_T(""))
{
}

CAddEdit_Attachment::~CAddEdit_Attachment()
{
}

void CAddEdit_Attachment::DoDataExchange(CDataExchange* pDX)
{
    CAddEdit_PropertyPage::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(CAddEdit_Attachment)
    //}}AFX_DATA_MAP
    DDX_Text(pDX, IDC_ATT_NAME, m_AttName);
    DDX_Text(pDX, IDC_ATT_FILE, m_AttFile);
    DDX_Control(pDX, IDC_ATT_IMAGE, m_AttStatic);
}

BEGIN_MESSAGE_MAP(CAddEdit_Attachment, CAddEdit_PropertyPage)
  //{{AFX_MSG_MAP(CAddEdit_Attachment)
  ON_BN_CLICKED(ID_HELP, OnHelp)

  // Common
  ON_MESSAGE(PSM_QUERYSIBLINGS, OnQuerySiblings)
  //}}AFX_MSG_MAP
  ON_WM_PAINT()
  ON_BN_CLICKED(IDC_ATT_ADD, &CAddEdit_Attachment::OnBnClickedAttAdd)
  ON_BN_CLICKED(IDC_ATT_REMOVE, &CAddEdit_Attachment::OnBnClickedAttRemove)
END_MESSAGE_MAP()

BOOL CAddEdit_Attachment::PreTranslateMessage(MSG* pMsg)
{
  if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F1) {
    PostMessage(WM_COMMAND, MAKELONG(ID_HELP, BN_CLICKED), NULL);
    return TRUE;
  }

  return CAddEdit_PropertyPage::PreTranslateMessage(pMsg);
}

BOOL CAddEdit_Attachment::OnInitDialog()
{
  return TRUE;
}

BOOL CAddEdit_Attachment::OnKillActive()
{
  if (UpdateData(TRUE) == FALSE)
    return FALSE;

  return CAddEdit_PropertyPage::OnKillActive();
}


LRESULT CAddEdit_Attachment::OnQuerySiblings(WPARAM , LPARAM )
{
  UpdateData(TRUE);

  // Have any of my fields been changed?
  return 0L;
}

BOOL CAddEdit_Attachment::OnApply()
{
  if (M_uicaller() == IDS_VIEWENTRY || M_protected() != 0)
    return FALSE; //CAddEdit_PropertyPage::OnApply();

  return CAddEdit_PropertyPage::OnApply();
}

void CAddEdit_Attachment::OnHelp()
{
  ShowHelp(L"::/html/attachments.html");
}

void CAddEdit_Attachment::OnPaint()
{
  CAddEdit_PropertyPage::OnPaint();
  if (!m_AttImage.IsNull()) {
    CRect rect;
    m_AttStatic.GetClientRect(rect);
    m_AttImage.StretchBlt(m_AttStatic.GetDC()->GetSafeHdc(), 0, 0,
                          rect.Width(), rect.Height(), SRCCOPY);
  }
}

void CAddEdit_Attachment::OnBnClickedAttAdd()
{
  CString filter;
	CSimpleArray<GUID> aguidFileTypes;
	HRESULT hResult;

	hResult = m_AttImage.GetImporterFilterString(filter,aguidFileTypes);
	if (FAILED(hResult))
		return;

  CFileDialog fileDlg(TRUE, NULL, NULL, 0, filter, this);
  if (fileDlg.DoModal() == IDOK) {
    m_AttFile = fileDlg.GetPathName();
    hResult = m_AttImage.Load(m_AttFile);
    if (FAILED(hResult)) {
      CString fmt;
      fmt.Format(L"Load image failed:\n%x", hResult);
      ::AfxMessageBox(fmt);
      return;
	}
    Invalidate();
    UpdateData(FALSE);
    UpdateWindow();
  }
}

void CAddEdit_Attachment::OnBnClickedAttRemove()
{
    // TODO: Add your control notification handler code here
}
