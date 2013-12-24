/*
 * Copyright (c) 2003-2013 Rony Shapiro <ronys@users.sourceforge.net>.
 * All rights reserved. Use of the code is allowed under the
 * Artistic License 2.0 terms, as specified in the LICENSE file
 * distributed with this code, or available from
 * http://www.opensource.org/licenses/artistic-license-2.0.php
 */

#ifndef __PWS_TOOLBAR_BUTTONS_H
#define __PWS_TOOLBAR_BUTTONS_H

#include <wx/dynarray.h>

enum {ID_SEPARATOR = -1};

struct _PwsToolbarInfo{
  int id;
  const wxChar* tooltip;
  const char** bitmap_normal;
  const char** bitmap_disabled;
  const char** bitmap_classic;
  const char** bitmap_classic_disabled;
};

WX_DECLARE_OBJARRAY(_PwsToolbarInfo, PwsToolbarInfoArray);

const PwsToolbarInfoArray& GetPwsToolbarbuttons();


#endif
