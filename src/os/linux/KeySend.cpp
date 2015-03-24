/*
* Copyright (c) 2003-2015 Rony Shapiro <ronys@users.sourceforge.net>.
* All rights reserved. Use of the code is allowed under the
* Artistic License 2.0 terms, as specified in the LICENSE file
* distributed with this code, or available from
* http://www.opensource.org/licenses/artistic-license-2.0.php
*/
#include "../KeySend.h"
#include "../sleep.h"
#include "./xsendstring.h"
#include "../../core/Util.h"
#include "../../core/PWSprefs.h"

/////////////////////////////////////////////////////////////////////
// CKeySendImpl - Linux specific bits
///////////////
class CKeySendImpl
{
  static bool GetPref(PWSprefs::BoolPrefs pref) {
    return PWSprefs::GetInstance()->GetPref(pref);
  }

  static pws_os::AutotypeMethod DefaultAutytypeMethod() {
    return GetPref(PWSprefs::UseAltAutoType)? pws_os::ATMETHOD_XTEST: pws_os::ATMETHOD_XSENDKEYS;
  }

  pws_os::AutotypeMethod m_autotypeMethod = DefaultAutytypeMethod();
  bool m_eraseBeforeTyping = GetPref(PWSprefs::EraseAllBeforeAutotyping);
  bool m_emulateModsSeparately = GetPref(PWSprefs::EmulateModifiersSeparately);
  bool m_justStarted = true;

public:
  void SendString(const StringX &data, unsigned delay);
};

void CKeySendImpl::SendString(const StringX &data, unsigned delay)
{
  if (m_justStarted  && m_eraseBeforeTyping) {
    pws_os::SelectAll();
    m_justStarted = false;
  }
  pws_os::SendString(data, m_autotypeMethod, delay, m_eraseBeforeTyping, m_emulateModsSeparately);
}

////////////////////////////////////////////////////
// CKeySend - The generic implementation
CKeySend::CKeySend(bool, unsigned defaultDelay)
  : m_delayMS(defaultDelay),
    m_impl(new CKeySendImpl)
{
}

CKeySend::~CKeySend()
{
  delete m_impl;
}

void CKeySend::SendString(const StringX &data)
{
  m_impl->SendString(data, m_delayMS);
}

void CKeySend::SetDelay(unsigned d)
{
  m_delayMS = d;
}

// SetAndDelay allows users to put \d500\d10 in autotype and
// then it will cause a delay of half a second then subsequent
// key stokes will be delayed by 10 ms 
// thedavecollins 2004-08-05

void CKeySend::SetAndDelay(unsigned d) {
  SetDelay(d);
  pws_os::sleep_ms(m_delayMS);
}

//it doesn't matter in X what the CAPSLOCK state is
void CKeySend::SetCapsLock(const bool /*bState*/)
{
}

bool CKeySend::isCapsLocked() const
{
  return false; // as X doesn't care
}

void CKeySend::BlockInput(bool) const
{
  // XXX TBD
}

void CKeySend::ResetKeyboardState() const
{
  // XXX Need we implement this for X?
}
