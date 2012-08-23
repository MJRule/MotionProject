#include "StdAfx.h"
#include "NetworkModel.h"

SocketClient *socketClient;
NetworkModel::NetworkModel()
{
}


NetworkModel::~NetworkModel(void)
{
}

//---------------------------------------------------
// @Name:		connect
// @Author:		Lane (PeePeeSpeed)/ James Bayliss
// @Inputs:		char* IPaddress, int port)
// @Outputs:	bool stating whether there is a connection  or not
//
// @Desc:		Attempts a connection to the local or remote server. Sets 'connected' to 1 if it is successful.
//				Otherwise, it catches and displays the appropriate error, then deletes the 'socketClient' pointer.
//---------------------------------------------------
bool NetworkModel::connect(std::string IPaddress, int port)
{
	try 
	{
		//socketClient = new SocketClient("192.168.21.58", 9000);

		/*EventLogResult = SendDlgItemMessage( m_hWnd, IDC_EVENTLOG, WM_GETTEXT, 9000, (LPARAM)eventLogTemp );
		_tcscat_s( eventLogTemp, 1024, L"\r\nIP Address: " );
		_tcscat_s( eventLogTemp, 1024, IPOutput );
		_tcscat_s( eventLogTemp, 1024, L"\r\nPort Address: " );
		_tcscat_s( eventLogTemp, 1024, PortOutput );
		SendDlgItemMessage( m_hWnd, IDC_EVENTLOG, WM_SETTEXT, 0, (LPARAM)eventLogTemp );*/
		socketClient = new SocketClient(IPaddress, port);
		MessageBox(NULL, L"Socket connected", L"Sockets", MB_OK);

		return true;
	} 
  
	catch (const char* s) 
	{
		OutputDebugString(L"Error");
		MessageBox(NULL, L"Error1", L"Error1", MB_OK);
		delete( socketClient );
				return false;
	} 
  
	catch (std::string s) 
	{
	  OutputDebugString(L"Error"); //contains 'Unknown Error'
	  MessageBox(NULL, L"Error2", L"Error2", MB_OK);
	  delete( socketClient );
	  return false;
	} 

	catch (...) 
	{
	  OutputDebugString(L"Error");
	  MessageBox(NULL, L"Error3", L"Error3", MB_OK);
	  delete( socketClient );
	  return false;
	}
}

bool NetworkModel::disconnect()
{
	socketClient->Close();
	return false;
}

void NetworkModel::sendString(std::string str)
{
	socketClient->SendLine(str);
}