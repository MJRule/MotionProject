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
	NetworkModel(void);
	~NetworkModel(void);
	bool connect( std::string port, std::string IP );
	void sendMData( MData pendingMdata );
	bool testConnection();
private:

};

