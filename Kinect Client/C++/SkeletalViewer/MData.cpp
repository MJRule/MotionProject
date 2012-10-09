// MData.cpp
//

#include "stdafx.h"
#include "MData.h"
#include "Nuiapi.h"
#include <stdio.h>
#include <wchar.h>
#include <string>
#include <iostream>
#include "Socket.h"
#include <sstream>

//---------------------------------------------------
// Name:	getMovementData()	
// Author:	Lane Cotgrove - PeePeeSpeed
// Inputs:	NULL	
// Outputs:	NUI_SKELETON_DATA
// 
// Desc:	This function retreives the skeleton data from an MData object
//---------------------------------------------------
	NUI_SKELETON_DATA MData::getMovementData()
	{
		return *skeletonData;
	}
//---------------------------------------------------
// Name:	getI()	
// Author:	Lane Cotgrove - PeePeeSpeed
// Inputs:	NULL	
// Outputs:	INT i
// 
// Desc:	This function returns the skeleton number of the skeleton frame stored within an MData object
//---------------------------------------------------
	int MData::getI()
	{
		return i;
	}

//---------------------------------------------------
// Name:	setMovementData()	
// Author:	Lane Cotgrove - PeePeeSpeed
// Inputs:	NUI_SKELETON_DATA	
// Outputs:	NULL
// 
// Desc:	This function allows you to set an MData object's skeleton data
//---------------------------------------------------
	void MData::setMovementData( NUI_SKELETON_DATA * sData, int index )
	{
		skeletonData = sData;
		i = index;

		transformMovementData();
	}
//---------------------------------------------------
// Name:	transformMovementData()	
// Author:	Lane Cotgrove - PeePeeSpeed
// Inputs:	NULL	
// Outputs:	NULL
// 
// Desc:	This function transforms an MData object's skeleton data into a string to be stored in transformedData
//---------------------------------------------------
	void MData::transformMovementData()
	{ 
		transformedData = ""; 

		std::stringstream ss;
		ss.precision( 2 );

		//take skeletonData.
		//Calculate Bone Orientations
		NuiSkeletonCalculateBoneOrientations( skeletonData, bOrientations );//This transforms the data, it calculates the bone orientations (not the points) from the skeleton.

		ss << i;//i is Skeleton Index // THIS IS FIRST IN THE TRANSFORMEDDATA STRING

		ss << "," << skeletonData->eTrackingState;
		ss << "," << skeletonData->dwTrackingID;
		
		ss << "," << skeletonData->Position.x;
		ss << "," << skeletonData->Position.y;
		ss << "," << skeletonData->Position.z;

		for( int k = 0; k < NUI_SKELETON_POSITION_COUNT; k++ )
		{
			ss << "," << skeletonData->SkeletonPositions[ k ].x;
			ss << "," << skeletonData->SkeletonPositions[ k ].y;
			ss << "," << skeletonData->SkeletonPositions[ k ].z;

			ss << "," << skeletonData->eSkeletonPositionTrackingState[ k ];
		}

		for( int j = 0; j < NUI_SKELETON_POSITION_COUNT; j++ )
		{
			ss << "," << bOrientations[ j ].absoluteRotation.rotationQuaternion.x;
			ss << "," << bOrientations[ j ].absoluteRotation.rotationQuaternion.y;
			ss << "," << bOrientations[ j ].absoluteRotation.rotationQuaternion.z;
			ss << "," << bOrientations[ j ].absoluteRotation.rotationQuaternion.w;
			
			ss << "," << bOrientations[ j ].absoluteRotation.rotationMatrix.M11;
			ss << "," << bOrientations[ j ].absoluteRotation.rotationMatrix.M12;
			ss << "," << bOrientations[ j ].absoluteRotation.rotationMatrix.M13;
			ss << "," << bOrientations[ j ].absoluteRotation.rotationMatrix.M14;
			ss << "," << bOrientations[ j ].absoluteRotation.rotationMatrix.M21;
			ss << "," << bOrientations[ j ].absoluteRotation.rotationMatrix.M22;
			ss << "," << bOrientations[ j ].absoluteRotation.rotationMatrix.M23;
			ss << "," << bOrientations[ j ].absoluteRotation.rotationMatrix.M24;
			ss << "," << bOrientations[ j ].absoluteRotation.rotationMatrix.M31;
			ss << "," << bOrientations[ j ].absoluteRotation.rotationMatrix.M32;
			ss << "," << bOrientations[ j ].absoluteRotation.rotationMatrix.M33;
			ss << "," << bOrientations[ j ].absoluteRotation.rotationMatrix.M34;
			ss << "," << bOrientations[ j ].absoluteRotation.rotationMatrix.M41;
			ss << "," << bOrientations[ j ].absoluteRotation.rotationMatrix.M42;
			ss << "," << bOrientations[ j ].absoluteRotation.rotationMatrix.M43;
			ss << "," << bOrientations[ j ].absoluteRotation.rotationMatrix.M44;

			ss << "," << bOrientations[ j ].hierarchicalRotation.rotationQuaternion.x;
			ss << "," << bOrientations[ j ].hierarchicalRotation.rotationQuaternion.y;
			ss << "," << bOrientations[ j ].hierarchicalRotation.rotationQuaternion.z;
			ss << "," << bOrientations[ j ].hierarchicalRotation.rotationQuaternion.w;

			ss << "," << bOrientations[ j ].hierarchicalRotation.rotationMatrix.M11;
			ss << "," << bOrientations[ j ].hierarchicalRotation.rotationMatrix.M12;
			ss << "," << bOrientations[ j ].hierarchicalRotation.rotationMatrix.M13;
			ss << "," << bOrientations[ j ].hierarchicalRotation.rotationMatrix.M14;
			ss << "," << bOrientations[ j ].hierarchicalRotation.rotationMatrix.M21;
			ss << "," << bOrientations[ j ].hierarchicalRotation.rotationMatrix.M22;
			ss << "," << bOrientations[ j ].hierarchicalRotation.rotationMatrix.M23;
			ss << "," << bOrientations[ j ].hierarchicalRotation.rotationMatrix.M24;
			ss << "," << bOrientations[ j ].hierarchicalRotation.rotationMatrix.M31;
			ss << "," << bOrientations[ j ].hierarchicalRotation.rotationMatrix.M32;
			ss << "," << bOrientations[ j ].hierarchicalRotation.rotationMatrix.M33;
			ss << "," << bOrientations[ j ].hierarchicalRotation.rotationMatrix.M34;
			ss << "," << bOrientations[ j ].hierarchicalRotation.rotationMatrix.M41;
			ss << "," << bOrientations[ j ].hierarchicalRotation.rotationMatrix.M42;
			ss << "," << bOrientations[ j ].hierarchicalRotation.rotationMatrix.M43;
			ss << "," << bOrientations[ j ].hierarchicalRotation.rotationMatrix.M44;
		}

		transformedData = ss.str();
		
		//const char * c;
		//c = transformedData.c_str();
		//MessageBoxA(NULL, c, "TEST INSIDE transformMovementData", MB_OK);

		//return string or send
	}

//---------------------------------------------------
// Name:	getString()
// Author:	Lane Cotgrove - PeePeeSpeed
// Inputs:	NULL	
// Outputs:	STRING transformedData
// 
// Desc:	This function returns the string transformData from an MData object. This string contains transformed movement data
//---------------------------------------------------
	std::string MData::getString()
	{
		return transformedData;
	}

//---------------------------------------------------
// Name:	normaliseX	
// Author:	Todd Cochrane
// Inputs:	FLOAT x	
// Outputs:	FLOAT x
// 
// Desc:	This function normalises the value of x for an external application
//---------------------------------------------------

	float normaliseX( float x )
	{
		return (x + 2.2) / 4.4;
	}

//---------------------------------------------------
// Name:	normaliseY	
// Author:	Todd Cochrane
// Inputs:	FLOAT y	
// Outputs:	FLOAT y
// 
// Desc:	This function normalises the value of y for an external application
//---------------------------------------------------
	float normaliseY( float y )
	{
		return (y + 1.6) / 3.6;
	}
//---------------------------------------------------
// Name:	normaliseZ	
// Author:	Todd Cochrane
// Inputs:	FLOAT z	
// Outputs:	FLOAT z
// 
// Desc:	This function normalises the value of z for an external application
//---------------------------------------------------
	float normaliseZ( float z )
	{
		return z/ 4;
	}
//---------------------------------------------------
// Name:	transformHeadHands()	
// Author:	Todd Cochrane/Lane Cotgrove - PeePeeSpeed
// Inputs:	NULL	
// Outputs:	NULL
// 
// Desc:	This function transforms the point data for the head and hands into a string.
//---------------------------------------------------
	void MData::transformHeadHands()
	{
		//transformedData has the model: { skeletonIndex, head x, head y, head z, L hand x, L hand y, L hand z, 
		//									 R hand x, R hand y, R hand z, skeletonTrackingID }

		// TODD HACK HERE!
		// http://msdn.microsoft.com/en-us/library/nuisensor.nui_skeleton_data.aspx
		// http://msdn.microsoft.com/en-us/library/nuisensor.nui_skeleton_position_index.aspx
		// http://www.instructables.com/id/Arduino-Basics-Making-Sound/step4/The-Simple-Keyboard/
		// I'm interesrted in the HEAD , and hands
			
		std::stringstream ss;

		ss << i; // i is index.

		ss << "," << skeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HEAD].x;
		ss << "," << skeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HEAD].y;
		ss << "," << skeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HEAD].z;

		ss << "," << skeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HAND_LEFT].x;
		ss << "," << skeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HAND_LEFT].y;
		ss << "," << skeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HAND_LEFT].z;

		ss << "," << skeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT].x;
		ss << "," << skeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT].y;
		ss << "," << skeletonData[i].SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT].z;

		ss << "," << skeletonData[0].dwTrackingID;

		transformedData = ss.str();

		//const char * c;
		//c = transformedData.c_str();
		//MessageBoxA(NULL, c, "TEST INSIDE transformMovementData", MB_OK);
	}