
Registry Location
Create a registry key in the following location for each listener (IWRdsProtocolListener) that your protocol uses. In this example, the new listener keys are called MyListener1 and MyListener2.


Copy
HKEY_LOCAL_MACHINE
   System
      CurrentControlSet
         Control
            Terminal Server
               WinStations
                  RDP-Tcp
                  MyListener1
                  MyListener2
For reference, you can view the value entries under the default RDP-Tcp listener key in this location.

Registry Value Entries
The listener key for the protocol must have a value entry called LoadableProtocol_Object

Data type

REG_SZ
of type **REG\_SZ** that contains the CLSID of the protocol manager for that listener. (The protocol manager is a COM server that implements the **IWRdsProtocolManager** interface.) The Remote Desktop Services service uses this CLSID to instantiate the protocol manager for this listener after it finds the listener in the registry.
If your protocol provider uses more than one listener, the Remote Desktop Services service only creates one instance of the protocol manager, and uses it to call CreateListener once for each listener.

Related topics
Creating a Remote Desktop Protocol Provider

Method Call Sequence

https://learn.microsoft.com/en-us/windows/win32/termserv/registering-the-custom-protocol