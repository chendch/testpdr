//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//

#include "helpers.h"
#include <windows.h>
#include <strsafe.h>
#include <new>


class CSampleRdsProtocolManager : public IWRdsProtocolManager
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
            QITABENT(CSampleRdsProtocolManager, IWRdsProtocolManager), // IID_IWRdsProtocolManager
            {0},
        };
        return QISearch(this, qit, riid, ppv);
    }

  public:

    IFACEMETHODIMP CreateListener(
        /* [string][in] */ __RPC__in_string WCHAR* wszListenerName,
        /* [out] */ __RPC__deref_out_opt IWRdsProtocolListener** pProtocolListener);

    IFACEMETHODIMP NotifyServiceStateChange( __RPC__in WRDS_SERVICE_STATE* pTSServiceStateChange);

    IFACEMETHODIMP NotifySessionOfServiceStart(__RPC__in WRDS_SESSION_ID* SessionId);

    IFACEMETHODIMP NotifySessionOfServiceStop(__RPC__in WRDS_SESSION_ID* SessionId);

    IFACEMETHODIMP NotifySessionStateChange(__RPC__in WRDS_SESSION_ID* SessionId,ULONG EventId);

    IFACEMETHODIMP Initialize(
        /* [in] */ __RPC__in_opt IWRdsProtocolSettings* pIWRdsSettings,
        /* [in] */ __RPC__in PWRDS_SETTINGS pWRdsSettings);
    IFACEMETHODIMP NotifySettingsChange(
        /* [in] */ __RPC__in PWRDS_SETTINGS pWRdsSettings);

    IFACEMETHODIMP Uninitialize(void);

    friend HRESULT CSample_CreateInstance(_In_ REFIID riid, _Outptr_ void** ppv);

public:
      CSampleRdsProtocolManager();
    __override ~CSampleRdsProtocolManager();

  private:

private:
    long                                    _cRef;            // Used for reference counting.
    IWRdsProtocolListener*            listener;
};
