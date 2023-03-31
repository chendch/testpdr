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
#include "helpers.h"
#include "dll.h"

class CSampleWRdsProtocolConnection : public IWRdsProtocolConnection, public IWRdsWddmIddProps
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
            QITABENT(CSampleWRdsProtocolConnection, IWRdsProtocolConnection), // IID_IWRdsProtocolConnection
            QITABENT(CSampleWRdsProtocolConnection, IWRdsWddmIddProps),
            {0},
        };
        return QISearch(this, qit, riid, ppv);
    }

  public:
 
    IFACEMETHODIMP GetLogonErrorRedirector(
        /* [out] */ __RPC__deref_out_opt IWRdsProtocolLogonErrorRedirector** ppLogonErrorRedir);

    IFACEMETHODIMP AcceptConnection(void);

    IFACEMETHODIMP GetClientData(
        /* [out] */ __RPC__out WRDS_CLIENT_DATA* pClientData);

    IFACEMETHODIMP GetClientMonitorData(
        /* [out] */ __RPC__out UINT* pNumMonitors,
        /* [out] */ __RPC__out UINT* pPrimaryMonitor);

    IFACEMETHODIMP GetUserCredentials(
        /* [out] */ __RPC__out WRDS_USER_CREDENTIAL* pUserCreds);

    IFACEMETHODIMP GetLicenseConnection(
        /* [out] */ __RPC__deref_out_opt IWRdsProtocolLicenseConnection** ppLicenseConnection);

    IFACEMETHODIMP AuthenticateClientToSession(
        /* [out] */ __RPC__out WRDS_SESSION_ID* SessionId);

    IFACEMETHODIMP NotifySessionId(
        /* [in] */ __RPC__in WRDS_SESSION_ID* SessionId,
        /* [in] */ HANDLE_PTR SessionHandle);

    IFACEMETHODIMP GetInputHandles(
        /* [out] */ __RPC__out HANDLE_PTR* pKeyboardHandle,
        /* [out] */ __RPC__out HANDLE_PTR* pMouseHandle,
        /* [out] */ __RPC__out HANDLE_PTR* pBeepHandle);

    IFACEMETHODIMP GetVideoHandle(
        /* [out] */ __RPC__out HANDLE_PTR* pVideoHandle);

    IFACEMETHODIMP ConnectNotify(
        /* [in] */ ULONG SessionId);

    IFACEMETHODIMP IsUserAllowedToLogon(
        /* [in] */ ULONG SessionId,
        /* [in] */ HANDLE_PTR UserToken,
        /* [string][in] */ __RPC__in_string WCHAR* pDomainName,
        /* [string][in] */ __RPC__in_string WCHAR* pUserName);

    IFACEMETHODIMP SessionArbitrationEnumeration(
        /* [in] */ HANDLE_PTR hUserToken,
        /* [in] */ BOOL bSingleSessionPerUserEnabled,
        /* [size_is][out] */ __RPC__out_ecount_full(*pdwSessionIdentifierCount) ULONG* pSessionIdArray,
        /* [out][in] */ __RPC__inout ULONG* pdwSessionIdentifierCount);

    IFACEMETHODIMP LogonNotify(
        /* [in] */ HANDLE_PTR hClientToken,
        /* [string][in] */ __RPC__in_string WCHAR* wszUserName,
        /* [string][in] */ __RPC__in_string WCHAR* wszDomainName,
        /* [in] */ __RPC__in WRDS_SESSION_ID* SessionId,
        /* [out][in] */ __RPC__inout PWRDS_CONNECTION_SETTINGS pWRdsConnectionSettings);

    IFACEMETHODIMP PreDisconnect(
        /* [in] */ ULONG DisconnectReason);

    IFACEMETHODIMP DisconnectNotify(void);

    IFACEMETHODIMP Close(void);

    IFACEMETHODIMP GetProtocolStatus(
        /* [out] */ __RPC__out WRDS_PROTOCOL_STATUS* pProtocolStatus);

    IFACEMETHODIMP GetLastInputTime(
        /* [out] */ __RPC__out ULONG64* pLastInputTime);

    IFACEMETHODIMP SetErrorInfo(
        /* [in] */ ULONG ulError);

    IFACEMETHODIMP CreateVirtualChannel(
        /* [string][in] */ __RPC__in_string CHAR* szEndpointName,
        /* [in] */ BOOL bStatic,
        /* [in] */ ULONG RequestedPriority,
        /* [out] */ __RPC__out ULONG_PTR* phChannel);

    IFACEMETHODIMP QueryProperty(
        /* [in] */ GUID QueryType,
        /* [in] */ ULONG ulNumEntriesIn,
        /* [in] */ ULONG ulNumEntriesOut,
        /* [size_is][optional][in] */ __RPC__in_ecount_full(ulNumEntriesIn) PWRDS_PROPERTY_VALUE pPropertyEntriesIn,
        /* [size_is][optional][out] */ __RPC__out_ecount_full(ulNumEntriesOut) PWRDS_PROPERTY_VALUE pPropertyEntriesOut);

    IFACEMETHODIMP GetShadowConnection(
        /* [out] */ __RPC__deref_out_opt IWRdsProtocolShadowConnection** ppShadowConnection);

    IFACEMETHODIMP NotifyCommandProcessCreated(
        /* [in] */ ULONG SessionId);


    // Inherited via IWRdsWddmIddProps
    virtual HRESULT __stdcall GetHardwareId(WCHAR* pDisplayDriverHardwareId, DWORD Count) override;

    virtual HRESULT __stdcall OnDriverLoad(ULONG SessionId, HANDLE_PTR DriverHandle) override;

    virtual HRESULT __stdcall OnDriverUnload(ULONG SessionId) override;

    virtual HRESULT __stdcall EnableWddmIdd(BOOL Enabled) override;

  public:
      CSampleWRdsProtocolConnection();
    __override ~CSampleWRdsProtocolConnection();
    HRESULT _stdcall SetCredentials(WCHAR* Domain, WCHAR* UserName, WCHAR* Password);
    void CSampleWRdsProtocolConnection::SetConnectionCallback(IWRdsProtocolConnectionCallback* ConnectionCallback);
    IWRdsProtocolConnectionCallback* CSampleWRdsProtocolConnection::GetConnectionCallback();

  private:

private:
    long                                    _cRef;            // Used for reference counting.
    IWRdsProtocolConnectionCallback* ConnectionCallback = NULL;
    WCHAR* UserName = NULL;
    WCHAR* Password = NULL;
    WCHAR* Domain = NULL;
};
