/*
 * Copyright (c) 2003-2009 Rony Shapiro <ronys@users.sourceforge.net>.
 * All rights reserved. Use of the code is allowed under the
 * Artistic License 2.0 terms, as specified in the LICENSE file
 * distributed with this code, or available from
 * http://www.opensource.org/licenses/artistic-license-2.0.php
 */

#include "pwsdca.h"
#include "pwsclip.h"

#include <wx/string.h>
#include <wx/intl.h>
#include <wx/msgdlg.h>

#include "corelib/PWSprefs.h"
#include "passwordsafeframe.h"

void PWSdca::Doit(wxWindow *w, const CItemData &item)
{
  wxString action;

  switch (PWSprefs::GetInstance()->GetPref(PWSprefs::DoubleClickAction)) {
  case PWSprefs::DoubleClickAutoType:
    action = _("AutoType");
    //PostMessage(WM_COMMAND, ID_MENUITEM_AUTOTYPE);
    break;
  case PWSprefs::DoubleClickBrowse:
    action = _("Browse");
    //PostMessage(WM_COMMAND, ID_MENUITEM_BROWSEURL);
    break;
  case PWSprefs::DoubleClickCopyNotes:
    action = _("CopyNotes");
    //OnCopyNotes();
    break;
  case PWSprefs::DoubleClickCopyPassword:
    //OnCopyPassword();
    PWSclip::SetData(item.GetPassword());
    break;
  case PWSprefs::DoubleClickCopyUsername:
    action = _("CopyUsername");
    // OnCopyUsername();
    break;
  case PWSprefs::DoubleClickCopyPasswordMinimize:
    PWSclip::SetData(item.GetPassword());
    action = _("CopyPasswordMinimize");
    //OnCopyPasswordMinimize();
    break;
  case PWSprefs::DoubleClickViewEdit: {
    wxCommandEvent event(ID_EDIT, w->GetId());
    event.SetEventObject(w);
    w->GetEventHandler()->ProcessEvent(event);
  }
    break;
  case PWSprefs::DoubleClickBrowsePlus:
    action = _("BrowsePlusAutotype");
    break;
  case PWSprefs::DoubleClickRun:
    action = _("Run Command");
    break;
  case PWSprefs::DoubleClickSendEmail:
    action = _("Send email");
    break;
  default:
    action.Format(_("Unknown code: %d"),
                  PWSprefs::GetInstance()->GetPref(PWSprefs::DoubleClickAction));
    break;
  }
  if (!action.empty())
    wxMessageBox(action);
}
