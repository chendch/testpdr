
#include <unknwn.h>
//#include <Windows.h>
#include <winsock.h>
#include "guid.h"
#include "CSampleRdsProtocolListener.h"
#include "CSampleWRdsProtocolConnection.h"
#include "helpers.h"
#include <thread>

using namespace std;

//#pragma comment (lib, "Ws2_32.lib")

#define usPort 7000
SOCKET listenSocket;

BOOL ListenSocket(SOCKET* ServerSocket);
BOOL AcceptSocket(SOCKET* sockListen, SOCKET* outServerSocket);
void runTask(IWRdsProtocolListenerCallback* pCallback);

CSampleRdsProtocolListener::CSampleRdsProtocolListener():
    _cRef(1)
{
    Log(L"CSampleRdsProtocolListener::\n");
    DllAddRef();
}

CSampleRdsProtocolListener::~CSampleRdsProtocolListener()
{
    Log(L"CSampleRdsProtocolListener::~\n");
    closesocket(listenSocket);
    DllRelease();
}

HRESULT CSampleRdsProtocolListener::GetSettings(
    /* [in] */ WRDS_LISTENER_SETTING_LEVEL WRdsListenerSettingLevel,
    /* [ref][out] */ __RPC__out PWRDS_LISTENER_SETTINGS pWRdsListenerSettings)
{
    Log(L"CSampleRdsProtocolListener:GetSettings, Level: %d, %d\n", WRdsListenerSettingLevel, pWRdsListenerSettings->WRdsListenerSetting.WRdsListenerSettings1.MaxProtocolListenerConnectionCount);
   // DWORD cbSettings = sizeof(WRDS_LISTENER_SETTINGS);
   // WRDS_LISTENER_SETTINGS* pcpfd = (WRDS_LISTENER_SETTINGS*)CoTaskMemAlloc(cbSettings);

  //  pWRdsListenerSettings->WRdsListenerSettingLevel = WRdsListenerSettingLevel;

  //  pWRdsListenerSettings->WRdsListenerSetting.WRdsListenerSettings1.MaxProtocolListenerConnectionCount = 10;

  //  Log(L"CSampleRdsProtocolListener:GetSettings set, Level: %d, %d\n", WRdsListenerSettingLevel, pWRdsListenerSettings->WRdsListenerSetting.WRdsListenerSettings1.MaxProtocolListenerConnectionCount);

    pWRdsListenerSettings->WRdsListenerSettingLevel = WRdsListenerSettingLevel;
    pWRdsListenerSettings->WRdsListenerSetting.WRdsListenerSettings1.MaxProtocolListenerConnectionCount = 1;
    pWRdsListenerSettings->WRdsListenerSetting.WRdsListenerSettings1.SecurityDescriptorSize = 0;
    pWRdsListenerSettings->WRdsListenerSetting.WRdsListenerSettings1.pSecurityDescriptor = NULL;

    //Sleep(10000);
    HRESULT hr = S_OK;
    return hr;
}

/*
HRESULT CSampleRdsProtocolListener::StartListen(__RPC__in_opt IWRdsProtocolListenerCallback* inPCallback)
{
    Log(L"CSampleRdsProtocolListener:StartListen\n");

    pListenerCallback = inPCallback;
  //  std::this_thread::sleep_for(std::chrono::seconds(3));

    ListenSocket(&listenSocket);

    std::thread t(runTask, pListenerCallback);
    t.detach();

    HRESULT hr = S_OK;
    return hr;
}

HRESULT CSampleRdsProtocolListener::StopListen(void)

{
    Log(L"CSampleRdsProtocolListener:StopListen");
    HRESULT hr = S_OK;
    return hr;
}*/

HRESULT __stdcall CSampleRdsProtocolListener::StartListen(IWRdsProtocolListenerCallback* pCallback)
{
    OutputDebugString(L"CWRdsProtocolListener::StartListen\n");
    //Required: https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nf-wtsprotocol-iwrdsprotocollistener-startlisten
    //Called when listener is enabled/termsrv is started
    this->pListenerCallback = pCallback;
    // Note: From documentation: The protocol must add a reference
    //       to this object and release it when StopListen is called.
    pCallback->AddRef();

    // For validation purposes only
    //When we start the listener, create a thread that waits until the command for a sample connection
    //This is defined in TestProtocolAPI.cpp
    this->threadHandle = CreateThread(NULL, 0, &WaitToConnect, this->pListenerCallback, 0, NULL);
    if (this->threadHandle == NULL)
    {
        OutputDebugString(L"CWRdsProtocolListener::StartListen£¬ Failed to create Thread");
        return ERROR;
    }

    return S_OK;
}

HRESULT __stdcall CSampleRdsProtocolListener::StopListen(void)
{
    //Required: https://docs.microsoft.com/en-us/windows/win32/api/wtsprotocol/nf-wtsprotocol-iwrdsprotocollistener-stoplisten
    //Called when termsrv is being shutdown (such as machine is shutting down) or listener is stopped
    if (this->threadHandle != NULL)
    {
        CloseHandle(this->threadHandle);
        this->threadHandle = NULL;
    }
    if (NULL != this->pListenerCallback)
    {
        this->pListenerCallback->Release();
        this->pListenerCallback = NULL;
    }

    return S_OK;
}




void runTask(IWRdsProtocolListenerCallback* pCallback)
{
    SOCKET serverSocket;
    while (TRUE)
    {
        Log(L"Waiting for client to connect...\n");
        if (!AcceptSocket(&listenSocket, &serverSocket)) {
            Log(L"Failed to get the socket. return -1\n");
            return;
        }


        IWRdsProtocolConnection* pConnection = new CSampleWRdsProtocolConnection();
        WRDS_CONNECTION_SETTINGS pWRdsConnectionSettings;
        IWRdsProtocolConnectionCallback* pConnCallback;

        pCallback->OnConnected(pConnection, &pWRdsConnectionSettings, &pConnCallback);

    }
}



BOOL ListenSocket(SOCKET* ServerSocket)
{
    SOCKET sockListen;
    SOCKADDR_IN sockIn;

    WSADATA wsaData;
    int iResult;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        Log(L"WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    //-----------------------------------------------------------------   
    //  Create listening socket.

    sockListen = socket(PF_INET, SOCK_STREAM, 0);

    if (INVALID_SOCKET == sockListen)
    {
        Log(L"Failed to create socket: %u\n", GetLastError());
        return(FALSE);
    }

    //-----------------------------------------------------------------   
    //  Bind to local port.

    sockIn.sin_family = AF_INET;
    sockIn.sin_addr.s_addr = 0;
    sockIn.sin_port = htons(usPort);

    if (SOCKET_ERROR == bind(sockListen, (LPSOCKADDR)&sockIn, sizeof(sockIn)))
    {
        Log(L"bind failed: %u\n", WSAGetLastError());
        closesocket(sockListen);
        WSACleanup();
        return(FALSE);
    }

    //-----------------------------------------------------------------   
    //  Listen for client.

    if (SOCKET_ERROR == listen(sockListen, 1))
    {
        Log(L"Listen failed: %u\n", WSAGetLastError());
        closesocket(sockListen);
        WSACleanup();
        return(FALSE);
    }
    else
    {
        Log(L"Listening on: %d! \n", usPort);
    }

    *ServerSocket = sockListen;

    return TRUE;
}

BOOL AcceptSocket(SOCKET* sockListen, SOCKET* outServerSocket)
{
  
    SOCKET serverSocket;
  
    serverSocket = accept(*sockListen, NULL, NULL);

    if (INVALID_SOCKET == serverSocket)
    {
        Log(L"accept failed: %u\n", WSAGetLastError());
        closesocket(*sockListen);
        WSACleanup();
        return(FALSE);
    }

    *outServerSocket = serverSocket;


    return TRUE;
}



