
#include <unknwn.h>
#include "guid.h"
#include "CSampleWRdsProtocolLicenseConnection.h"

CSampleWRdsProtocolLicenseConnection::CSampleWRdsProtocolLicenseConnection() :
	_cRef(1)
{
    Log(L"CSampleWRdsProtocolLicenseConnection::\n");
	DllAddRef();
}

CSampleWRdsProtocolLicenseConnection::~CSampleWRdsProtocolLicenseConnection()
{
    Log(L"CSampleWRdsProtocolLicenseConnection::~\n");
	DllRelease();
}

HRESULT CSampleWRdsProtocolLicenseConnection::RequestLicensingCapabilities(
    /* [out] */ __RPC__out PWRDS_LICENSE_CAPABILITIES ppLicenseCapabilities,
    /* [out][in] */ __RPC__inout ULONG* pcbLicenseCapabilities)
{
    Log(L"CSampleWRdsProtocolLicenseConnection::RequestLicensingCapabilities\n");
    HRESULT hr = S_OK;
    return hr;
}

HRESULT CSampleWRdsProtocolLicenseConnection::SendClientLicense(
    /* [size_is][in] */ __RPC__in_ecount_full(cbClientLicense) PBYTE pClientLicense,
    /* [in] */ ULONG cbClientLicense)
{
    Log(L"CSampleWRdsProtocolLicenseConnection::SendClientLicense\n");
    HRESULT hr = S_OK;
    return hr;
}

HRESULT CSampleWRdsProtocolLicenseConnection::RequestClientLicense(
    /* [size_is][in] */ __RPC__in_ecount_full(Reserve2) PBYTE Reserve1,
    /* [in] */ ULONG Reserve2,
    /* [size_is][out] */ __RPC__out_ecount_full(*pcbClientLicense) PBYTE ppClientLicense,
    /* [out][in] */ __RPC__inout ULONG* pcbClientLicense)
{
    Log(L"CSampleWRdsProtocolLicenseConnection::RequestClientLicense\n");
    HRESULT hr = S_OK;
    return hr;
}

HRESULT CSampleWRdsProtocolLicenseConnection::ProtocolComplete(
    /* [in] */ ULONG ulComplete)
{
    Log(L"CSampleWRdsProtocolLicenseConnection::ProtocolComplete\n");
    HRESULT hr = S_OK;
    return hr;
}

