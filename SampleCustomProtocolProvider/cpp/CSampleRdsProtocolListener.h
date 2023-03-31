//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//

#include <windows.h>
#include <strsafe.h>
#include <shlguid.h>
#include <propkey.h>
#include <wtsprotocol.h>
#include "dll.h"
#include "helpers.h"

class CSampleRdsProtocolListener : public IWRdsProtocolListener
{
  public:
    // IUnknown
    IFACEMETHODIMP_(ULONG) AddRef()
    {
        return ++_cRef;
    }

    IFACEMETHODIMP_(ULONG) Release()
    {
        long cRef = --_cRef;
        if (!cRef)
        {
            delete this;
        }
        return cRef;
    }

    IFACEMETHODIMP QueryInterface(_In_ REFIID riid, _COM_Outptr_ void **ppv)
    {
        static const QITAB qit[] =
        {
            QITABENT(CSampleRdsProtocolListener, IWRdsProtocolListener), // IID_IWTSProtocolListener
            {0},
        };
        return QISearch(this, qit, riid, ppv);
    }

  public:
 
    IFACEMETHODIMP GetSettings(
        /* [in] */ WRDS_LISTENER_SETTING_LEVEL WRdsListenerSettingLevel,
        /* [ref][out] */ __RPC__out PWRDS_LISTENER_SETTINGS pWRdsListenerSettings);

    IFACEMETHODIMP StartListen(
        /* [in] */ __RPC__in_opt IWRdsProtocolListenerCallback* pCallback);

    IFACEMETHODIMP StopListen(void);

    public:
      CSampleRdsProtocolListener();
    __override ~CSampleRdsProtocolListener();

  private:
      

private:
    long                                    _cRef;            // Used for reference counting.
    IWRdsProtocolListenerCallback* pListenerCallback;
    HANDLE threadHandle;
};
