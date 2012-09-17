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

	NUI_SKELETON_DATA MData::getMovementData()
	{
		return *skeletonData;
	}

	int MData::getI()
	{
		return i;
	}

	void MData::setMovementData( NUI_SKELETON_DATA * sData, int index )
	{
		skeletonData = sData;
		i = index;

		transformMovementData();
	}

	void MData::transformMovementData()
	{ 
		//transformedData has the model: { [ skeletonIndex, startJoint[ j ], endJoint[ j ], absoluteRotation.rotationQuaternion[ j ], 
		//									absoluteRotation.rotationMatrix[ j ], hierarchicalRotation.rotationQuaternion[ j ], 
		//										hierarchicalRotation.rotationMatrix[ j ] ] [ NUI_SKELETON_POSITION_INDEX, 
		//											skeletonData.SkeletonPositions[ j ], skeletalData.eSkeletonTrackingState[ j ] ] 
		//												[ skeletonData.Position ] [ skeletonData.dwTrackingID ] 
		//													[ skeletonData.eTrackingState ] }
		transformedData = ""; 

		std::stringstream ss;
		ss.precision( 2 );

		//take skeletonData.
		//Calculate Bone Orientations
		NuiSkeletonCalculateBoneOrientations( skeletonData, bOrientations );

		ss << i;//i is Skeleton Index

		for( int j = 0; j < NUI_SKELETON_POSITION_COUNT; j++ )
		{
			ss << "," << bOrientations[ j ].startJoint;
			ss << "," << bOrientations[ j ].endJoint;

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

		for( int k = 0; k < NUI_SKELETON_POSITION_COUNT; k++ )
		{
			ss << "," << k;

			ss << "," << skeletonData->SkeletonPositions[ k ].x;
			ss << "," << skeletonData->SkeletonPositions[ k ].y;
			ss << "," << skeletonData->SkeletonPositions[ k ].z;

			ss << "," << skeletonData->eSkeletonPositionTrackingState[ k ];
		}

		ss << "," << skeletonData->Position.x;
		ss << "," << skeletonData->Position.y;
		ss << "," << skeletonData->Position.z;

		ss << "," << skeletonData->dwTrackingID;

		ss << "," << skeletonData->eTrackingState;

		transformedData = ss.str();
		
		//const char * c;
		//c = transformedData.c_str();
		//MessageBoxA(NULL, c, "TEST INSIDE transformMovementData", MB_OK);

		//return string or send
	}

	std::string MData::getString()
	{
		return transformedData;
	}

	float normaliseX( float x )
	{
		return (x + 2.2) / 4.4;
	}

	float normaliseY( float y )
	{
		return (y + 1.6) / 3.6;
	}

	float normaliseZ( float z )
	{
		return z/ 4;
	}

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