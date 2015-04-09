/*
* Copyright (c) 2003-2015 Rony Shapiro <ronys@users.sourceforge.net>.
* All rights reserved. Use of the code is allowed under the
* Artistic License 2.0 terms, as specified in the LICENSE file
* distributed with this code, or available from
* http://www.opensource.org/licenses/artistic-license-2.0.php
*/

/*
 * xsendstring.h - interface for sending a given string as keyboard input
 * to the X application in focus
 */

#ifndef __XSENDSTRING_H__
#define __XSENDSTRING_H__

#include "../../core/StringX.h"

namespace pws_os {
  /* Set the method to AUTO if you're not sure what it should be */
  typedef enum { ATMETHOD_AUTO, ATMETHOD_XTEST, ATMETHOD_XSENDKEYS } AutotypeMethod;
}

/////////////////////////////////////////////////////////////////////
// CKeySendImpl - Linux specific bits
///////////////
class CKeySendImpl
{
    pws_os::AutotypeMethod m_autotypeMethod;
    bool m_emulateModsSeparately = true;
    bool m_eraseBeforeTyping = false;

  public:

    CKeySendImpl(pws_os::AutotypeMethod method): m_autotypeMethod(method){}

    void SendString(const StringX &data, unsigned delay);
    void EmulateMods(bool emulate) { m_emulateModsSeparately = emulate; }
    bool IsEmulatingMods() const { return m_emulateModsSeparately; }
    void SelectAll();
};

#endif

