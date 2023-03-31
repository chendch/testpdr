
#include <unknwn.h>
#include "guid.h"
#include "CSampleWRdsProtocolConnection.h"
#include "helpers.h"
#include "CSampleWRdsProtocolLicenseConnection.h"

CSampleWRdsProtocolConnection::CSampleWRdsProtocolConnection() :
	_cRef(1)
{
	Log(L"CSampleWRdsProtocolConnection::\n");
	DllAddRef();
}

CSampleWRdsProtocolConnection::~CSampleWRdsProtocolConnection()
{
	Log(L"CSampleWRdsProtocolConnection::~\n");
	DllRelease();
}

HRESULT CSampleWRdsProtocolConnection::GetLogonErrorRedirector(
	/* [out] */ __RPC__deref_out_opt IWRdsProtocolLogonErrorRedirector** ppLogonErrorRedir)
{
	Log(L"CSampleWRdsProtocolConnection::GetLogonErrorRedirector\n");
	HRESULT hr = S_OK;
	return hr;
}

HRESULT CSampleWRdsProtocolConnection::AcceptConnection(void)
{
	Log(L"CSampleWRdsProtocolConnection::AcceptConnection\n");
	HRESULT hr = S_OK;
	return hr;
}

HRESULT CSampleWRdsProtocolConnection::GetClientData(
	/* [out] */ __RPC__out WRDS_CLIENT_DATA* pClientData)
{
	Log(L"CSampleWRdsProtocolConnection::GetClientData\n");
	errno_t copyReturnValue;

	// Some sample values
	(*pClientData).fEnableWindowsKey = 1;
	(*pClientData).fInheritAutoLogon = 1;
	(*pClientData).fNoAudioPlayback = 1;

	pClientData->fDisableCtrlAltDel = FALSE;
	pClientData->fDoubleClickDetect = TRUE;
	pClientData->fInheritInitialProgram = TRUE;
	pClientData->EncryptionLevel = 3;
	pClientData->PerformanceFlags = 0;
	pClientData->PerformanceFlags |= WTS_PERF_ENABLE_DESKTOP_COMPOSITION;
	pClientData->PerformanceFlags |= WTS_PERF_ENABLE_ENHANCED_GRAPHICS;
	pClientData->fMaximizeShell = TRUE;
	pClientData->fHideTitleBar = FALSE;
	pClientData->fInheritAutoLogon = FALSE;
	pClientData->fPromptForPassword = FALSE;
	pClientData->fUsingSavedCreds = FALSE;
	pClientData->fPasswordIsScPin = FALSE;
	pClientData->fInheritInitialProgram = FALSE;
	pClientData->fMaximizeShell = FALSE;
	pClientData->fMaximizeShell = TRUE;
	pClientData->fInheritInitialProgram = TRUE;
	wcscpy_s(pClientData->WorkDirectory, WTS_DIRECTORY_LENGTH, L"%TEMP%");
	wcscpy_s(pClientData->InitialProgram, WTS_INITIALPROGRAM_LENGTH, L"%SYSTEMROOT%\\system32\\notepad.exe");




	copyReturnValue = wcsncpy_s(pClientData->Domain, this->Domain, wcslen(this->Domain));
	copyReturnValue = wcsncpy_s(pClientData->UserName, this->UserName, wcslen(this->UserName));
	copyReturnValue = wcsncpy_s(pClientData->Password, this->Password, wcslen(this->Password));

	pClientData->fInheritColorDepth = TRUE;
	pClientData->ColorDepth = 32; // 32; 16 = The display uses 32 bits per pixel for a maximum of 2^32 colors.
	pClientData->HRes = 1024; // 1920;
	pClientData->VRes = 768; // 1200;


	pClientData->fMouse = FALSE;



	pClientData->ClientBuildNumber = 0;

	pClientData->ClientProductId = 1;          // 1 == WINDOWS_NT      -- from client
	 pClientData->OutBufCountHost = 0;          // ???
	 pClientData->OutBufCountClient = 0;        // ???
	pClientData->OutBufLength = 0;             // ???
	 pClientData->ClientSessionId = 0;


	 pClientData->fNoAudioPlayback = FALSE;
	 pClientData->fRemoteConsoleAudio = FALSE;

	 //wcscpy_s(pClientData->DisplayDriverName, WTS_DRIVER_NAME_LENGTH, L"vmwrdsdd");
	 //wcscpy_s(pClientData->DisplayDeviceName, WTS_DEVICE_NAME_LENGTH, L"VMWRDSVideo");

	 

     wcscpy_s(pClientData->DisplayDriverName, WTS_DRIVER_NAME_LENGTH, L"RDPUDD");
	 wcscpy_s(pClientData->DisplayDeviceName, WTS_DEVICE_NAME_LENGTH, L"Video0");


	pClientData->SerialNumber = 1;

	wcscpy_s(pClientData->ClientDigProductId,WTS_CLIENT_PRODUCT_ID_LENGTH + 1, L"00000-000-0000000-00000");
	pClientData->fDisableCpm = TRUE;
	pClientData->fDisableCdm = FALSE;
	pClientData->fDisableCcm = TRUE;
    pClientData->fDisableLPT = TRUE;
	pClientData->fDisableClip = TRUE;
	pClientData->fDisablePNP = TRUE;




	//This is what gets returned when a user will run "qwinsta" and is mandatory
	WCHAR* protocolName = L"TL-Ext";
	copyReturnValue = wcsncpy_s((*pClientData).ProtocolName, protocolName, wcslen(protocolName));

	HRESULT hr = S_OK;
	return hr;
}

HRESULT CSampleWRdsProtocolConnection::GetClientMonitorData(
	/* [out] */ __RPC__out UINT* pNumMonitors,
	/* [out] */ __RPC__out UINT* pPrimaryMonitor)
{
	Log(L"CSampleWRdsProtocolConnection::GetClientMonitorData\n");
	HRESULT hr = S_OK;
	return hr;
}

HRESULT CSampleWRdsProtocolConnection::GetUserCredentials(
	/* [out] */ __RPC__out WRDS_USER_CREDENTIAL* pUserCreds)
{
	Log(L"CSampleWRdsProtocolConnection::GetUserCredentials\n");
	//Return user credentials to pass to winlogon if not using kerberos or other secure mechanisms
  //These can also be passed in from GetClientData
  //Be really really careful about relying on this, and cleaning up plain-text passwords
  //Highly suggested to rely on kerberos/AD/AAD that are significantly more secure
	errno_t copyReturnValue;

	copyReturnValue = wcsncpy_s((*pUserCreds).Domain, this->Domain, wcslen(this->Domain));
	if (copyReturnValue != 0)
	{
		return ERROR;
	}

	copyReturnValue = wcsncpy_s((*pUserCreds).UserName, this->UserName, wcslen(this->UserName));
	if (copyReturnValue != 0)
	{
		return ERROR;
	}

	copyReturnValue = wcsncpy_s((*pUserCreds).Password, this->Password, wcslen(this->Password));
	if (copyReturnValue != 0)
	{
		return ERROR;
	}
	HRESULT hr = S_OK;
	return hr;
}

HRESULT CSampleWRdsProtocolConnection::GetLicenseConnection(
	/* [out] */ __RPC__deref_out_opt IWRdsProtocolLicenseConnection** ppLicenseConnection)
{
	Log(L"CSampleWRdsProtocolConnection::GetLicenseConnection\n");
	/*CComObject<CWRdsProtocolLicenseConnection>* pLicenseConnection = NULL;
	hr = CComObject<CWRdsProtocolLicenseConnection>::CreateInstance(&pLicenseConnection);
	if (FAILED(hr))
	{
		return E_FAIL;
	}*/

	*ppLicenseConnection = new CSampleWRdsProtocolLicenseConnection();

	HRESULT hr = S_OK;
	return hr;
}

HRESULT CSampleWRdsProtocolConnection::AuthenticateClientToSession(
	/* [out] */ __RPC__out WRDS_SESSION_ID* SessionId)
{
	Log(L"CSampleWRdsProtocolConnection::AuthenticateClientToSession : id: %d, guid: %d\n", SessionId->SessionId, SessionId->SessionUniqueGuid);
	HRESULT hr = S_OK;
	return E_NOTIMPL;
}

HRESULT CSampleWRdsProtocolConnection::NotifySessionId(
	/* [in] */ __RPC__in WRDS_SESSION_ID* SessionId,
	/* [in] */ HANDLE_PTR SessionHandle)
{
	Log(L"CSampleWRdsProtocolConnection::NotifySessionId : id: %d, guid: %d\n", SessionId->SessionId, SessionId->SessionUniqueGuid);
	HRESULT hr = S_OK;
	return hr;
}

HRESULT CSampleWRdsProtocolConnection::GetInputHandles(
	/* [out] */ __RPC__out HANDLE_PTR* pKeyboardHandle,
	/* [out] */ __RPC__out HANDLE_PTR* pMouseHandle,
	/* [out] */ __RPC__out HANDLE_PTR* pBeepHandle)
{
	Log(L"CSampleWRdsProtocolConnection::GetInputHandles\n");

	pKeyboardHandle = NULL;
	pMouseHandle = NULL;
	pBeepHandle = NULL;

	HRESULT hr = S_OK;
	return hr;
}

HRESULT CSampleWRdsProtocolConnection::GetVideoHandle(
	/* [out] */ __RPC__out HANDLE_PTR* pVideoHandle)
{
	Log(L"CSampleWRdsProtocolConnection::GetVideoHandle\n");
	HRESULT hr = S_OK;
	return hr;
}

HRESULT CSampleWRdsProtocolConnection::ConnectNotify(
	/* [in] */ ULONG SessionId)
{
	Log(L"CSampleWRdsProtocolConnection::ConnectNotify %u\n", SessionId);
	HRESULT hr = S_OK;
	return hr;
}

HRESULT CSampleWRdsProtocolConnection::IsUserAllowedToLogon(
	/* [in] */ ULONG SessionId,
	/* [in] */ HANDLE_PTR UserToken,
	/* [string][in] */ __RPC__in_string WCHAR* pDomainName,
	/* [string][in] */ __RPC__in_string WCHAR* pUserName)
{
	Log(L"CSampleWRdsProtocolConnection::IsUserAllowedToLogon\n");
	HRESULT hr = S_OK;
	return hr;
}

HRESULT CSampleWRdsProtocolConnection::SessionArbitrationEnumeration(
	/* [in] */ HANDLE_PTR hUserToken,
	/* [in] */ BOOL bSingleSessionPerUserEnabled,
	/* [size_is][out] */ __RPC__out_ecount_full(*pdwSessionIdentifierCount) ULONG* pSessionIdArray,
	/* [out][in] */ __RPC__inout ULONG* pdwSessionIdentifierCount)
{
	Log(L"CSampleWRdsProtocolConnection::SessionArbitrationEnumeration\n");
	HRESULT hr = S_OK;
	//return hr;
	return E_NOTIMPL;
}

HRESULT CSampleWRdsProtocolConnection::LogonNotify(
	/* [in] */ HANDLE_PTR hClientToken,
	/* [string][in] */ __RPC__in_string WCHAR* wszUserName,
	/* [string][in] */ __RPC__in_string WCHAR* wszDomainName,
	/* [in] */ __RPC__in WRDS_SESSION_ID* SessionId,
	/* [out][in] */ __RPC__inout PWRDS_CONNECTION_SETTINGS pWRdsConnectionSettings)
{
	Log(L"CSampleWRdsProtocolConnection::LogonNotify: id: %d, guid: %d\n", SessionId->SessionId, SessionId->SessionUniqueGuid);
	HRESULT hr = S_OK;
	return hr;
}

HRESULT CSampleWRdsProtocolConnection::PreDisconnect(
	/* [in] */ ULONG DisconnectReason)
{
	Log(L"CSampleWRdsProtocolConnection::PreDisconnect DisconnectReason:%d\n", DisconnectReason);
	HRESULT hr = S_OK;
	return hr;
}

HRESULT CSampleWRdsProtocolConnection::DisconnectNotify(void)
{
	Log(L"CSampleWRdsProtocolConnection::DisconnectNotify\n");
	HRESULT hr = S_OK;
	return hr;
}

HRESULT CSampleWRdsProtocolConnection::Close(void)
{
	Log(L"CSampleWRdsProtocolConnection::Close\n");

	IWRdsProtocolConnectionCallback* localConnectionCallback = NULL;

	if (this->Domain != NULL)
	{
		delete[] this->Domain;
		this->Domain = NULL;
	}
	if (this->UserName != NULL)
	{
		delete[] this->UserName;
		this->UserName = NULL;
	}
	if (this->Password != NULL)
	{
		delete[] this->Password;
		this->Password = NULL;
	}

	localConnectionCallback = GetConnectionCallback();
	if (NULL != localConnectionCallback)
	{
		localConnectionCallback->Release();
		localConnectionCallback = NULL;
	}

	HRESULT hr = S_OK;
	return hr;
}

HRESULT CSampleWRdsProtocolConnection::GetProtocolStatus(
	/* [out] */ __RPC__out WRDS_PROTOCOL_STATUS* pProtocolStatus)
{
	Log(L"CSampleWRdsProtocolConnection::GetProtocolStatus\n");
	WTS_PROTOCOL_COUNTERS* EmptyProtocolCounters = new WTS_PROTOCOL_COUNTERS;
	WTS_CACHE_STATS* EmptyCacheStats = new WTS_CACHE_STATS;

	(*pProtocolStatus).Output = *EmptyProtocolCounters;
	(*pProtocolStatus).Input = *EmptyProtocolCounters;
	(*pProtocolStatus).Cache = *EmptyCacheStats;
	(*pProtocolStatus).AsyncSignal = 0;
	(*pProtocolStatus).AsyncSignalMask = 0;
	HRESULT hr = S_OK;
	return hr;
}

HRESULT CSampleWRdsProtocolConnection::GetLastInputTime(
	/* [out] */ __RPC__out ULONG64* pLastInputTime)
{
	Log(L"CSampleWRdsProtocolConnection::GetLastInputTime\n");
	HRESULT hr = S_OK;
	*pLastInputTime = 0;
	return hr;
}

HRESULT CSampleWRdsProtocolConnection::SetErrorInfo(
	/* [in] */ ULONG ulError)
{
	Log(L"CSampleWRdsProtocolConnection::SetErrorInfo %u\n", ulError);
	HRESULT hr = S_OK;
	//return hr;
	return E_NOTIMPL;
}

HRESULT CSampleWRdsProtocolConnection::CreateVirtualChannel(
	/* [string][in] */ __RPC__in_string CHAR* szEndpointName,
	/* [in] */ BOOL bStatic,
	/* [in] */ ULONG RequestedPriority,
	/* [out] */ __RPC__out ULONG_PTR* phChannel)
{
	Log(L"CSampleWRdsProtocolConnection::CreateVirtualChannel\n");
	HRESULT hr = S_OK;
	//return hr;
	return E_NOTIMPL;
}

HRESULT CSampleWRdsProtocolConnection::QueryProperty(
	/* [in] */ GUID QueryType,
	/* [in] */ ULONG ulNumEntriesIn,
	/* [in] */ ULONG ulNumEntriesOut,
	/* [size_is][optional][in] */ __RPC__in_ecount_full(ulNumEntriesIn) PWRDS_PROPERTY_VALUE pPropertyEntriesIn,
	/* [size_is][optional][out] */ __RPC__out_ecount_full(ulNumEntriesOut) PWRDS_PROPERTY_VALUE pPropertyEntriesOut)
{
	Log(L"CSampleWRdsProtocolConnection::QueryProperty\n");
	HRESULT hr = S_OK;
	//return hr;
	return E_NOTIMPL;
}

HRESULT CSampleWRdsProtocolConnection::GetShadowConnection(
	/* [out] */ __RPC__deref_out_opt IWRdsProtocolShadowConnection** ppShadowConnection)
{
	Log(L"CSampleWRdsProtocolConnection::GetShadowConnection\n");
	HRESULT hr = S_OK;
	//return hr;
	return E_NOTIMPL;
}

HRESULT CSampleWRdsProtocolConnection::NotifyCommandProcessCreated(
	/* [in] */ ULONG SessionId)
{
	Log(L"CSampleWRdsProtocolConnection::NotifyCommandProcessCreated %d\n", SessionId);
	HRESULT hr = S_OK;
	return hr;
}


HRESULT __stdcall CSampleWRdsProtocolConnection::GetHardwareId(WCHAR* pDisplayDriverHardwareId, DWORD Count)
{
	Log(L"CSampleWRdsProtocolConnection::GetHardwareId\n");
	// Required for IDD graphics drivers
	// https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nf-wtsprotocol-iwrdswddmiddprops-gethardwareid
	// Return your valid graphics driver here, this is defined in the driver's INF file.
	WCHAR* DefaultDisplayDriverHardwareId;
	DefaultDisplayDriverHardwareId = L"PCI\VEN_15AD&DEV_0405&SUBSYS_040515AD&REV_00";//L"SampleGPU_IndirectDisplay_v14_SimpleAutoRemoteConfig";
	HRESULT hr = StringCchCopyW(
		pDisplayDriverHardwareId,
		Count,
		DefaultDisplayDriverHardwareId
	);

	return S_OK;
}

HRESULT __stdcall CSampleWRdsProtocolConnection::OnDriverLoad(ULONG SessionId, HANDLE_PTR DriverHandle)
{
	Log(L"CSampleWRdsProtocolConnection::OnDriverLoad\n");
	//Optional: Called when the IDD driver has been loaded
	//https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nf-wtsprotocol-iwrdswddmiddprops-ondriverload
	return S_OK;
}

HRESULT __stdcall CSampleWRdsProtocolConnection::OnDriverUnload(ULONG SessionId)
{
	Log(L"CSampleWRdsProtocolConnection::OnDriverUnload\n");
	//Optional: Called when the IDD driver has been unloaded
	//https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nf-wtsprotocol-iwrdswddmiddprops-ondriverunload
	return S_OK;
}

HRESULT __stdcall CSampleWRdsProtocolConnection::EnableWddmIdd(BOOL Enabled)
{
	Log(L"CSampleWRdsProtocolConnection::EnableWddmIdd\n");
	//Required: https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nf-wtsprotocol-iwrdswddmiddprops-enablewddmidd
	//Termsrv tells the stack whether to use IDD or XDDM, modern windows systems will always return true
	//If this returns true, it will load IDD drivers
	//If this returns false, it will load XDDM drivers (legacy)
	return S_OK;
}


HRESULT _stdcall CSampleWRdsProtocolConnection::SetCredentials(WCHAR* Domain, WCHAR* UserName, WCHAR* Password)
{
	//Optional, this is not part of the interface and provided as a helper method
	//This is not secure, please use kerberos or other modern authentication mechanisms
	//Handle credentials with care such as using ZeroMemory
	size_t len;
	size_t result;

	len = wcslen(Domain) + 1;
	this->Domain = new WCHAR[len];
	result = StringCchCopyW(this->Domain, len, Domain);

	len = wcslen(UserName) + 1;
	this->UserName = new WCHAR[len];
	result = StringCchCopyW(this->UserName, len, UserName);

	len = wcslen(Password) + 1;
	this->Password = new WCHAR[len];
	result = StringCchCopyW(this->Password, len, Password);

	return S_OK;
}

void CSampleWRdsProtocolConnection::SetConnectionCallback(IWRdsProtocolConnectionCallback* ConnectionCallback)
{
	//https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nn-wtsprotocol-iwtsprotocolconnectioncallback
	this->ConnectionCallback = ConnectionCallback;
}

IWRdsProtocolConnectionCallback* CSampleWRdsProtocolConnection::GetConnectionCallback()
{
	//https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nn-wtsprotocol-iwtsprotocolconnectioncallback
	return this->ConnectionCallback;
}


