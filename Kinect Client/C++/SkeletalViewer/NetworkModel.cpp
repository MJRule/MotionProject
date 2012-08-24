#include "StdAfx.h"
#include "NetworkModel.h"

// TC inside networkmodel
//SocketClient *socketClient;
// TC

std::wstring s2ws(const std::string& s)
{
 int len;
 int slength = (int)s.length() + 1;
 len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
 wchar_t* buf = new wchar_t[len];
 MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
 std::wstring r(buf);
 delete[] buf;
 return r;
}


// public methods

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
bool NetworkModel::connect(std::string IPaddress, int port = 0)
{
	try 
	{
		//socketClient = new SocketClient("192.168.21.58", 9000); // test code?
		isHTTP = false;
		
		// TC true if is an IP address then we treat this as a socket version
		if( isIPaddress(IPaddress) ) // have IP
		{	
			socketClient = new SocketClient(IPaddress, port);
		    MessageBox(NULL, L"Socket connected", L"Sockets", MB_OK);
		}
		else // we're going for an http request
		{
			
			// TC This is a test
			if(validURL(IPaddress))
			{
				MessageBox(NULL, L"Sucessful http", L"HTTP Request", MB_OK);
				isHTTP = true;
				siteURL = s2ws(IPaddress);
			}
			else
			{
				MessageBox(NULL, L"Invalid Http", L"HTTP Request", MB_OK);
			}
			
			// TC
			
		}
		
		connected = true;
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
	if( isHTTP == false )
	{
		//MessageBox( NULL, L"NOT HTTP", L"sendString", NULL );
		socketClient->SendLine(str);
	}
	else
	{
		//MessageBox( NULL, L"Tis HTTP", L"sendString", NULL );
		HTTPget(str);
	}
}

bool NetworkModel::isConnected()
{
	return connected;
}

// private methods

std::wstring NetworkModel::HttpDomain(std::wstring strURL)
{
    std::wstring result;
	
	int pos = 0;
	int resultPos = 0;
	bool done = false;
	char c ;
	int state = 0;

	result.resize(strURL.length());

	while( ! done)
	{
	
	    char c = strURL[pos];
		switch(state)
		{

		case 0:
			if(c == 'h') state = 1;
			else
			{
				done = true;
				state = -1;
			}
			break;
		case 1: 
			if(c == 't' && strURL[pos+1] == 't')
			{
				pos++;
				state = 2;
			}
			else
			{
				done = true;
				state = -1;
			}
			break;
		case 2: 
			if(c == 'p' && strURL[pos+1] == 's' )
			{
				pos++;
				state = 3;
			}
			else if( c == 'p' && strURL[pos+1] == ':')
			{
				state = 3;
			}
			else
			{
				done = true;
				state = -1;
			}
			break;
		case 3: 
			if(c == ':' )
			{
				state = 4;
			}
			else
			{
				done = true;
				state = -1;
			}
			break;
		case 4: 
			if(c == '/' && strURL[pos+1] == '/' )
			{
				pos++;
				state = 5;
			}
			else
			{
				done = true;
				state = -1;
			}
			break;
		case 5: 
			if(c != '/')
			{
			  result[resultPos] = c;
			  resultPos++;
			}
			else
				done = true;
			break;

		}
		
		pos++;
		done = done || pos == strURL.length(); 
	  }

	return result;
}

std::wstring NetworkModel::HttpPath(std::wstring strURL)
{
    std::wstring result;
	
	int pos = 0;
	int resultPos = 0;
	bool done = false;
	char c ;
	int state = 0;

	result.resize(strURL.length());

	while( ! done)
	{
	
	    char c = strURL[pos];
		switch(state)
		{

		case 0:
			if(c == 'h') state = 1;
			else
			{
				done = true;
				state = -1;
			}
			break;
		case 1: 
			if(c == 't' && strURL[pos+1] == 't')
			{
				pos++;
				state = 2;
			}
			else
			{
				done = true;
				state = -1;
			}
			break;
		case 2: 
			if(c == 'p' && strURL[pos+1] == 's' )
			{
				pos++;
				state = 3;
			}
			else if( c == 'p' && strURL[pos+1] == ':')
			{
				state = 3;
			}
			else
			{
				done = true;
				state = -1;
			}
			break;
		case 3: 
			if(c == ':' )
			{
				state = 4;
			}
			else
			{
				done = true;
				state = -1;
			}
			break;
		case 4: 
			if(c == '/' && strURL[pos+1] == '/' )
			{
				pos++;
				state = 5;
			}
			else
			{
				done = true;
				state = -1;
			}
			break;
		case 5: 
			if(c != '/')
			{
			 state = 5;
			}
			else
			{
				result[resultPos] = c;
				resultPos++;
				state = 6;
			}
			break;
		case 6: 
			result[resultPos] = c;
			resultPos++;
			break;

			 
		}
		
		pos++;
		done = done || pos == strURL.length(); 
	  }
	result.resize(resultPos);
	return result;
}
void  NetworkModel::HTTPget(std::string strDATA)
{
	HINTERNET Initialize,Connection,File;
    DWORD dwBytes;
	std::wstring urlPATH ;
	std::wstring urlCOMMAND = L"?cmd=put&Value=17,";
	std::wstring urlDATA = s2ws(strDATA);
    std::wstring htpPATH = HttpPath(siteURL);
	std::wstring urlDOMAIN = HttpDomain(siteURL);
	char ch;
    int i = 0;  
	FILE * fp;

	urlPATH.resize(strDATA.length() + htpPATH.length()+ urlCOMMAND.length()); 
	
	urlPATH = htpPATH + urlCOMMAND + urlDATA;
	
	Initialize = InternetOpen(L"HTTPGET",INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0);

	LPCWSTR domain= urlDOMAIN.c_str();
	Connection = InternetConnect(Initialize,domain //L"virtual.weltec.ac.nz"
											,INTERNET_DEFAULT_HTTP_PORT,NULL,NULL,INTERNET_SERVICE_HTTP,0,0);
 
/**/
	LPCWSTR path = urlPATH.c_str();
    File = HttpOpenRequest(Connection,
                                L"GET",
                                path,//L"/distance/wi/3Der.php",
                                L"HTTP/1.1",
                                NULL, NULL,
                                INTERNET_FLAG_RELOAD | INTERNET_FLAG_EXISTING_CONNECT, 0);

    if(HttpSendRequest(File,NULL,0,NULL,0))
    {
		fp = fopen("response.htm","w");
		
		fwprintf(fp,L"%s%s\n", domain,path);
        while(InternetReadFile(File,&ch,1,&dwBytes))
        {
            if(dwBytes != 1)break;
             fprintf(fp,"%c", ch);
        }
        fclose(fp);
    }

    InternetCloseHandle(File);
    InternetCloseHandle(Connection);
    InternetCloseHandle(Initialize);
}

// isIPaddress states and scan
#define NOT_IP 7
#define FIRST_NUMBER 0
#define SECOND_NUMBER 1
#define THIRD_NUMBER  2
#define FOURTH_NUMBER 3

bool NetworkModel::isNumber(char c)
{
	return c >= '0' & c <= '9';
}
bool NetworkModel::isAlpha( char c)
{
	return c >= 'a' & c <= 'z' ||  c >= 'A' & c <= 'Z';

}
void NetworkModel::numberState(char current , int & count, int & state , int nextState)
{
		if(isNumber(current))
		{
			count++;
			if(count >3)
			{
				state = NOT_IP;
			}
		}
		else
		{
			if(current == '.')
			{
				count = 0;
				state = nextState;
			}
			else
				state = NOT_IP;
		}
		
}
bool NetworkModel::isIPaddress(std::string address)
{
   bool done = false;
   bool result = false;
   int pos = 0;
   int state = 0;
   int len = address.length();
   int count = 0;

   while(! done)
   {
	char current =   address[pos];

	// DFA scans for IP number with 4 parts
    switch(state)
	{
	case(FIRST_NUMBER) :
		numberState(current,count,state,SECOND_NUMBER);
		break;
	case(SECOND_NUMBER) :
		numberState(current,count,state,THIRD_NUMBER);
		break;
	case(THIRD_NUMBER) :
		numberState(current,count,state,FOURTH_NUMBER);
		break;
	case(FOURTH_NUMBER) :// This state is a final state
		if(isNumber(current))
		{
			count++;
			if(count>3)
			{
				result = false;
				state = NOT_IP;
			}
			else
			{
				if(pos+1 == len)
					result = true;

			}
		}
		else
		{
			state = NOT_IP;
		}
		break;
	}
	
    pos ++;	
	done = state == NOT_IP || pos == len;
   } 


   return result;
}

bool NetworkModel::validURL(std::string strURL)
{
    std::wstring wStrURL = s2ws(strURL); 
	LPCWSTR conStr = wStrURL.c_str();
	HINTERNET hSession = InternetOpen(L"Test", 0,NULL, NULL, 0);
	 
	HINTERNET hOpenUrl = InternetOpenUrl(hSession, conStr, NULL,0, 1, 1);
	bool result = false;

	if( hOpenUrl == NULL)
	{
		DWORD rc = GetLastError ();
		if (rc == ERROR_INTERNET_NAME_NOT_RESOLVED)
		{
			//printf ("Invalid url. %d\n", rc);
			throw "Invalid url.";
		}
		throw "Some other error with InternetOpenUrl";
		//printf ("Some other error with InternetOpenUrl %d\n", rc);

		result = false;
	}
	else
	{
		result = true;
	}
	InternetCloseHandle(hOpenUrl);
	InternetCloseHandle(hSession);

	return result;
}

void NetworkModel::httpGetTest()
{
	HINTERNET Initialize,Connection,File;
    DWORD dwBytes;

    char ch;
    Initialize = InternetOpen(L"HTTPGET",INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0);

    Connection = InternetConnect(Initialize,L"virtual.weltec.ac.nz",INTERNET_DEFAULT_HTTP_PORT,
    NULL,NULL,INTERNET_SERVICE_HTTP,0,0);


 

/**/

    File = HttpOpenRequest(Connection,
                                L"GET",
                                L"/distance/wi/3Der.php",
                                L"HTTP/1.1",
                                NULL, NULL,
                                INTERNET_FLAG_RELOAD | INTERNET_FLAG_EXISTING_CONNECT, 0);

    if(HttpSendRequest(File,NULL,0,NULL,0))
    {

        while(InternetReadFile(File,&ch,1,&dwBytes))
        {
            if(dwBytes != 1)break;
             printf("%c", ch);
        }
        
    }

    InternetCloseHandle(File);
    InternetCloseHandle(Connection);
    InternetCloseHandle(Initialize);
}
