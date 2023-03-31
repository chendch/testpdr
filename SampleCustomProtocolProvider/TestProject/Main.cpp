#include <wtsprotocol.h>
#include <initguid.h>
#include "guid.h"

void main()
{

    HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED); // 注册表HKEY_CLASSES_ROOT\CLSID\{372E5ABE-0BA4-49CE-AB33-2C7931983FFE}\InprocServer32 ThreadingModel=Free
    // HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED); //注册表HKEY_CLASSES_ROOT\CLSID\{372E5ABE-0BA4-49CE-AB33-2C7931983FFE}\InprocServer32 ThreadingModel=Apartment  如果不匹配,会报错：E_NOINTERFACE No such interface supported.
    IWRdsProtocolListener* pListener = NULL;


    REFIID riid1 = __uuidof(IWRdsProtocolListener);
    //hr = CoGetClassObject(CLSID_CSample, CLSCTX_INPROC_SERVER, NULL, riid1,(LPVOID*) & pListener);
    hr = CoCreateInstance(CLSID_CSample, NULL, CLSCTX_INPROC_SERVER, riid1, (LPVOID*)&pListener);

   // Sleep(10000);
    
    if (FAILED(hr)) {
        // Handle error
    }

    // Create an instance of the protocol manager
    IWRdsProtocolManager* pProtocolManager = NULL;
   // hr = CoCreateInstance(CLSID_WRdsProtocolManager, NULL, CLSCTX_INPROC_SERVER, IID_IWRdsProtocolManager, (LPVOID*)&pProtocolManager);
    //hr = CoCreateInstance(CLSID_CSample, NULL, CLSCTX_INPROC_SERVER, IID_IWRdsProtocolManager, (LPVOID*)&pProtocolManager);
    //MIDL_INTERFACE("DC796967-3ABB-40CD-A446-105276B58950")
    REFIID riid = __uuidof(IWRdsProtocolManager);
    hr = CoCreateInstance(CLSID_CSample, NULL, CLSCTX_INPROC_SERVER, riid, (LPVOID*)&pProtocolManager);
   // hr = CoGetClassObject(CLSID_CSample, CLSCTX_INPROC_SERVER, NULL, riid, (LPVOID*)&pProtocolManager);

    
    if (FAILED(hr)) {
        // Handle error
    }

    IWRdsProtocolSettings* pIWRdsSettings = nullptr;
    PWRDS_SETTINGS pWRdsSettings = nullptr;
    hr = pProtocolManager->Initialize(pIWRdsSettings, pWRdsSettings);

    // Create a listener
 
    hr = pProtocolManager->CreateListener((WCHAR*)L"MyListener", &pListener);
    if (FAILED(hr)) {
        // Handle error
    }

    // Configure the listener
      DWORD cbSettings = sizeof(WRDS_LISTENER_SETTINGS);
      WRDS_LISTENER_SETTINGS* pcpfd = (WRDS_LISTENER_SETTINGS*)CoTaskMemAlloc(cbSettings);
     // pcpfd->WRdsListenerSetting.WRdsListenerSettings1
     
     hr = pListener->GetSettings(pcpfd->WRdsListenerSettingLevel, pcpfd);

    // Start listening for incoming connections
    IWRdsProtocolListenerCallback* pCallback = nullptr;
    hr = pListener->StartListen(pCallback);
    if (FAILED(hr)) {
        // Handle error
    }

    // Wait for incoming connections
    // ...

    // Clean up
    pListener->Release();
    pProtocolManager->Release();
    CoUninitialize();
}