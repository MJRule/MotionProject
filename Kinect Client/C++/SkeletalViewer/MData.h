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

class MData
{

private:
	NUI_SKELETON_DATA skeletonData;

	std::string transformedData;

public:
	
	NUI_SKELETON_DATA getMovementData();
	void setMovementData( NUI_SKELETON_DATA & sData, int i );
	void transformMovementData();
	int getI();
	std::string MData::getString();
};
