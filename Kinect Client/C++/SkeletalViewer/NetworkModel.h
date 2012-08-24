#pragma once

#include "resource.h"
#include "stdafx.h"
#include "MData.h"
#include "Nuiapi.h"
#include <stdio.h>
#include <wchar.h>
#include <string>
#include <iostream>
#include "Socket.h"

#include <wininet.h>
#include <fstream>

class NetworkModel
{
public:
	NetworkModel();
	~NetworkModel(void);
	bool connect(std::string IPaddress, int port);
	bool disconnect();
	void sendString(std::string);

	void sendMData( MData pendingMdata );
	bool testConnection();
	bool isConnected();


//end PPS
private:
	SocketClient *socketClient;
	std::wstring siteURL;
    bool isHTTP;
	bool isIPaddress(std::string address);
	bool isNumber(char c);
	bool isAlpha(char c);
	void numberState(char current , int & count, int & state , int nextState);

	void httpGetTest();
	void  HTTPget(std::string strURL);
	std::wstring HttpDomain(std::wstring strURL);
	std::wstring NetworkModel::HttpPath(std::wstring strURL);
	bool validURL(std::string strURL);


	bool connected;

};
