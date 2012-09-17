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
	NUI_SKELETON_DATA * skeletonData;

	std::string transformedData;
	int i;
	NUI_SKELETON_BONE_ORIENTATION bOrientations[ NUI_SKELETON_POSITION_COUNT ];

public:
	
	NUI_SKELETON_DATA getMovementData();
	void setMovementData( NUI_SKELETON_DATA * sData, int i );   //private
	void transformMovementData();
	int getI();
	std::string MData::getString();
	float normaliseX( float x );
	float normaliseY( float y );
	float normaliseZ( float z );

	void MData::transformHeadHands();
};
