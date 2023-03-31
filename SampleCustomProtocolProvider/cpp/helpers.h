//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// Helper functions for copying parameters and packaging the buffer
// for GetSerialization.

#pragma once

#pragma warning(push)
#pragma warning(disable: 28251)
#include <credentialprovider.h>
#include <wtsprotocol.h>
#include <ntsecapi.h>
#pragma warning(pop)

#define SECURITY_WIN32
#include <security.h>
#include <intsafe.h>

#include <windows.h>
#include <strsafe.h>

#pragma warning(push)
#pragma warning(disable: 4995)
#include <shlwapi.h>
#pragma warning(pop)

#pragma warning(push)
#pragma warning(disable: 28301)
#include <wincred.h>
#pragma warning(pop)


#include <unordered_set>

#include "wtsdefs.h"

using namespace std;

#define MAX_STR_SIZE 256

typedef struct _CONNECTION_CONFIG
{
    WCHAR Domain[MAX_STR_SIZE];
    WCHAR UserName[MAX_STR_SIZE];
    WCHAR Password[MAX_STR_SIZE];
}   CONNECTION_CONFIG, * PCONNECTION_CONFIG;

typedef struct _CONNECTION_OUTPUT
{
    ULONG ulConnectionId;
    WCHAR ActivityId[MAX_STR_SIZE];
}   CONNECTION_OUTPUT, * PCONNECTION_OUTPUT;


DWORD WINAPI WaitToConnect(LPVOID lpParameter);

HRESULT CreateTestConnection(
    IWRdsProtocolListenerCallback* pListenerCallback,
    PCONNECTION_CONFIG pConnectionConfig,
    PCONNECTION_OUTPUT pConnectionOutput
);

//makes a copy of a field descriptor using CoTaskMemAlloc
HRESULT FieldDescriptorCoAllocCopy(
    _In_ const CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR &rcpfd,
    _Outptr_result_nullonfailure_ CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR **ppcpfd
    );

//makes a copy of a field descriptor on the normal heap
HRESULT FieldDescriptorCopy(
    _In_ const CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR &rcpfd,
    _Out_ CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR *pcpfd
    );

//creates a UNICODE_STRING from a NULL-terminated string
HRESULT UnicodeStringInitWithString(
    _In_ PWSTR pwz,
    _Out_ UNICODE_STRING *pus
    );

//initializes a KERB_INTERACTIVE_UNLOCK_LOGON with weak references to the provided credentials
HRESULT KerbInteractiveUnlockLogonInit(
    _In_ PWSTR pwzDomain,
    _In_ PWSTR pwzUsername,
    _In_ PWSTR pwzPassword,
    _In_ CREDENTIAL_PROVIDER_USAGE_SCENARIO cpus,
    _Out_ KERB_INTERACTIVE_UNLOCK_LOGON *pkiul
    );

//packages the credentials into the buffer that the system expects
HRESULT KerbInteractiveUnlockLogonPack(
    _In_ const KERB_INTERACTIVE_UNLOCK_LOGON &rkiulIn,
    _Outptr_result_bytebuffer_(*pcb) BYTE **prgb,
    _Out_ DWORD *pcb
    );

//get the authentication package that will be used for our logon attempt
HRESULT RetrieveNegotiateAuthPackage(
    _Out_ ULONG *pulAuthPackage
    );

//encrypt a password (if necessary) and copy it; if not, just copy it
HRESULT ProtectIfNecessaryAndCopyPassword(
    _In_ PCWSTR pwzPassword,
    _In_ CREDENTIAL_PROVIDER_USAGE_SCENARIO cpus,
    _Outptr_result_nullonfailure_ PWSTR *ppwzProtectedPassword
    );

HRESULT KerbInteractiveUnlockLogonRepackNative(
    _In_reads_bytes_(cbWow) BYTE *rgbWow,
    _In_ DWORD cbWow,
    _Outptr_result_bytebuffer_(*pcbNative) BYTE **prgbNative,
    _Out_ DWORD *pcbNative
    );

void KerbInteractiveUnlockLogonUnpackInPlace(
    _Inout_updates_bytes_(cb) KERB_INTERACTIVE_UNLOCK_LOGON *pkiul,
    DWORD cb
    );

HRESULT DomainUsernameStringAlloc(
    _In_ PCWSTR pwszDomain,
    _In_ PCWSTR pwszUsername,
    _Outptr_result_nullonfailure_ PWSTR *ppwszDomainUsername
    );

HRESULT SplitDomainAndUsername(_In_ PCWSTR pszQualifiedUserName, _Outptr_result_nullonfailure_ PWSTR *ppszDomain, _Outptr_result_nullonfailure_ PWSTR *ppszUsername);

void Log(wchar_t* fmt, ...);