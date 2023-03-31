
#include <initguid.h>
#include "CSampleRdsProtocolManager.h"
#include "CSampleRdsProtocolListener.h"
#include "guid.h"
#include "dll.h"
#include "helpers.h"

CSampleRdsProtocolManager::CSampleRdsProtocolManager():
    _cRef(1)
{
    Log(L"CSampleRdsProtocolManager::\n");
    DllAddRef();
}

CSampleRdsProtocolManager::~CSampleRdsProtocolManager()
{
    Log(L"CSampleRdsProtocolManager::~\n");
    if (listener != NULL) {
        listener->Release();
    }
    DllRelease();
}

HRESULT CSampleRdsProtocolManager::CreateListener(
    /* [string][in] */ __RPC__in_string WCHAR* wszListenerName,
    /* [out] */ __RPC__deref_out_opt IWRdsProtocolListener** pProtocolListener)
{
    Log(L"CSampleRdsProtocolManager::CreateListener: %s\n", wszListenerName);

    HRESULT hr = S_OK;
    listener = new (std::nothrow) CSampleRdsProtocolListener();
    if (listener)
    {
        hr = listener->QueryInterface(pProtocolListener);
        listener->Release();
    }
    else
    {
        hr = E_OUTOFMEMORY;
    }
   // *pProtocolListener = listener;

    return hr;
}

HRESULT CSampleRdsProtocolManager::NotifyServiceStateChange(__RPC__in WRDS_SERVICE_STATE* pTSServiceStateChange)
{
    Log(L"CSampleRdsProtocolManager::NotifyServiceStateChange\n");
    HRESULT hr = S_OK;
    return hr;
}

HRESULT CSampleRdsProtocolManager::NotifySessionOfServiceStart(__RPC__in WRDS_SESSION_ID* SessionId)
{
    Log(L"CSampleRdsProtocolManager::NotifySessionOfServiceStart\n");
    HRESULT hr = S_OK;
    return hr;
}

HRESULT CSampleRdsProtocolManager::NotifySessionOfServiceStop(__RPC__in WRDS_SESSION_ID* SessionId)
{
    Log(L"CSampleRdsProtocolManager::NotifySessionOfServiceStop %d, %d\n", SessionId->SessionId, SessionId->SessionUniqueGuid);
    HRESULT hr = S_OK;
    return hr;
}

HRESULT CSampleRdsProtocolManager::NotifySessionStateChange(__RPC__in WRDS_SESSION_ID* SessionId, ULONG EventId)
{
    Log(L"CSampleRdsProtocolManager::NotifySessionStateChange %d, %d, eventId: %d\n", SessionId->SessionId, SessionId->SessionUniqueGuid, EventId);
    HRESULT hr = S_OK;
    return hr;
}

HRESULT CSampleRdsProtocolManager::Initialize(
    /* [in] */ __RPC__in_opt IWRdsProtocolSettings* pIWRdsSettings,
    /* [in] */ __RPC__in PWRDS_SETTINGS pWRdsSettings)
{
    Log(L"CSampleRdsProtocolManager::Initialize\n");
    HRESULT hr = S_OK;
    return hr;
}

HRESULT CSampleRdsProtocolManager::NotifySettingsChange(
    /* [in] */ __RPC__in PWRDS_SETTINGS pWRdsSettings)
{
    Log(L"CSampleRdsProtocolManager::NotifySettingsChange\n");
    HRESULT hr = S_OK;
    return hr;
}

HRESULT CSampleRdsProtocolManager::Uninitialize(void)
{
    Log(L"CSampleRdsProtocolManager::Uninitialize\n");
    HRESULT hr = S_OK;
    return hr;
}

// Boilerplate code to create our CSampleRdsProtocolManager.
HRESULT CSample_CreateInstance(_In_ REFIID riid, _Outptr_ void **ppv)
{
    Log(L"CSample_CreateInstance\n");
    HRESULT hr;
    CSampleRdsProtocolManager* pMgr = new(std::nothrow) CSampleRdsProtocolManager();
    if (pMgr)
    {
        hr = pMgr->QueryInterface(riid, ppv);
        pMgr->Release();
    }
    else
    {
        hr = E_OUTOFMEMORY;
    }
    return hr;
}
