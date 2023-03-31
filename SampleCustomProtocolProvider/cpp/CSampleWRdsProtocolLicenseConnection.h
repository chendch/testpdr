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

class CSampleWRdsProtocolLicenseConnection : public IWRdsProtocolLicenseConnection
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
            QITABENT(CSampleWRdsProtocolLicenseConnection, IWRdsProtocolLicenseConnection), // IID_IWRdsProtocolLicenseConnection
            {0},
        };
        return QISearch(this, qit, riid, ppv);
    }

  public:
 
    IFACEMETHODIMP RequestLicensingCapabilities(
        /* [out] */ __RPC__out PWRDS_LICENSE_CAPABILITIES ppLicenseCapabilities,
        /* [out][in] */ __RPC__inout ULONG* pcbLicenseCapabilities);

    IFACEMETHODIMP SendClientLicense(
        /* [size_is][in] */ __RPC__in_ecount_full(cbClientLicense) PBYTE pClientLicense,
        /* [in] */ ULONG cbClientLicense);

    IFACEMETHODIMP RequestClientLicense(
        /* [size_is][in] */ __RPC__in_ecount_full(Reserve2) PBYTE Reserve1,
        /* [in] */ ULONG Reserve2,
        /* [size_is][out] */ __RPC__out_ecount_full(*pcbClientLicense) PBYTE ppClientLicense,
        /* [out][in] */ __RPC__inout ULONG* pcbClientLicense);

    IFACEMETHODIMP ProtocolComplete(
        /* [in] */ ULONG ulComplete);

    

public:
      CSampleWRdsProtocolLicenseConnection();
    __override ~CSampleWRdsProtocolLicenseConnection();

  private:

private:
    long                                    _cRef;            // Used for reference counting.
};
