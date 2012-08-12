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



//end PPS
private:

};
