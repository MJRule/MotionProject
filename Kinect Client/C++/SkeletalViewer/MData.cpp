// MData.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "MData.h"
#include "Nuiapi.h"
#include <stdio.h>
#include <wchar.h>
#include <string>
#include <iostream>
#include "Socket.h"

	NUI_SKELETON_DATA * skeletonData;
	std::string transformedData;
	int i;
	NUI_SKELETON_BONE_ORIENTATION bOrientations[ NUI_SKELETON_POSITION_COUNT ];

	NUI_SKELETON_DATA MData::getMovementData()
	{
		return skeletonData;
	}

	int MData::getI()
	{
		return i;
	}

	void MData::setMovementData( NUI_SKELETON_DATA &sData, int index )
	{
		skeletonData = sData;
		i = index;

		transformMovementData();
	}

	void MData::transformMovementData()
	{ 
		//transformedData has the model: startJoint, endJoint, absoluteRotation.rotationQuaternion, absoluteRotation.rotationMatrix, 
		//													hierarchicalRotation.rotationQuaternion, hierarchicalRotation.rotationMatrix.
		transformedData = "";

		char * cTemp = new char[ 1024 ];

		//take skeletonData.
		//Calculate Bone Orientations
		NuiSkeletonCalculateBoneOrientations( &skeletonData, bOrientations );

		transformedData.append( itoa( i, cTemp, 10 ) );

		for( int j = 0; j < NUI_SKELETON_POSITION_COUNT; j++ )
		{
			sprintf( cTemp, ",%i", bOrientations[ j ].startJoint );
			transformedData.append( cTemp );
			
			sprintf( cTemp, ",%i", bOrientations[ j ].endJoint );
			transformedData.append( cTemp );

			sprintf( cTemp, ",%f", bOrientations[ j ].absoluteRotation.rotationQuaternion.x );
			transformedData.append( cTemp );

			sprintf( cTemp, ",%f", bOrientations[ j ].absoluteRotation.rotationQuaternion.y );
			transformedData.append( cTemp );

			sprintf( cTemp, ",%f", bOrientations[ j ].absoluteRotation.rotationQuaternion.z );
			transformedData.append( cTemp );

			sprintf( cTemp, ",%f", bOrientations[ j ].absoluteRotation.rotationQuaternion.w );
			transformedData.append( cTemp );

			sprintf( cTemp, ",%f", bOrientations[ j ].absoluteRotation.rotationMatrix.M11 );
			transformedData.append( cTemp );

			sprintf( cTemp, ",%f", bOrientations[ j ].absoluteRotation.rotationMatrix.M12 );
			transformedData.append( cTemp );

			sprintf( cTemp, ",%f", bOrientations[ j ].absoluteRotation.rotationMatrix.M13 );
			transformedData.append( cTemp );

			sprintf( cTemp, ",%f", bOrientations[ j ].absoluteRotation.rotationMatrix.M14 );
			transformedData.append( cTemp );

			sprintf( cTemp, ",%f", bOrientations[ j ].absoluteRotation.rotationMatrix.M21 );
			transformedData.append( cTemp );

			sprintf( cTemp, ",%f", bOrientations[ j ].absoluteRotation.rotationMatrix.M22 );
			transformedData.append( cTemp );

			sprintf( cTemp, ",%f", bOrientations[ j ].absoluteRotation.rotationMatrix.M23 );
			transformedData.append( cTemp );

			sprintf( cTemp, ",%f", bOrientations[ j ].absoluteRotation.rotationMatrix.M24 );
			transformedData.append( cTemp );

			sprintf( cTemp, ",%f", bOrientations[ j ].absoluteRotation.rotationMatrix.M31 );
			transformedData.append( cTemp );

			sprintf( cTemp, ",%f", bOrientations[ j ].absoluteRotation.rotationMatrix.M32 );
			transformedData.append( cTemp );

			sprintf( cTemp, ",%f", bOrientations[ j ].absoluteRotation.rotationMatrix.M33 );
			transformedData.append( cTemp );

			sprintf( cTemp, ",%f", bOrientations[ j ].absoluteRotation.rotationMatrix.M34 );
			transformedData.append( cTemp );

			sprintf( cTemp, ",%f", bOrientations[ j ].absoluteRotation.rotationMatrix.M41 );
			transformedData.append( cTemp );

			sprintf( cTemp, ",%f", bOrientations[ j ].absoluteRotation.rotationMatrix.M42 );
			transformedData.append( cTemp );

			sprintf( cTemp, ",%f", bOrientations[ j ].absoluteRotation.rotationMatrix.M43 );
			transformedData.append( cTemp );

			sprintf( cTemp, ",%f", bOrientations[ j ].absoluteRotation.rotationMatrix.M44 );
			transformedData.append( cTemp );

			//----------------------

			sprintf( cTemp, ",%f", bOrientations[ j ].hierarchicalRotation.rotationQuaternion.x );
			transformedData.append( cTemp );

			sprintf( cTemp, ",%f", bOrientations[ j ].hierarchicalRotation.rotationQuaternion.y );
			transformedData.append( cTemp );

			sprintf( cTemp, ",%f", bOrientations[ j ].hierarchicalRotation.rotationQuaternion.z );
			transformedData.append( cTemp );

			sprintf( cTemp, ",%f", bOrientations[ j ].hierarchicalRotation.rotationQuaternion.w );
			transformedData.append( cTemp );

			sprintf( cTemp, ",%f", bOrientations[ j ].hierarchicalRotation.rotationMatrix.M11 );
			transformedData.append( cTemp );

			sprintf( cTemp, ",%f", bOrientations[ j ].hierarchicalRotation.rotationMatrix.M12 );
			transformedData.append( cTemp );

			sprintf( cTemp, ",%f", bOrientations[ j ].hierarchicalRotation.rotationMatrix.M13 );
			transformedData.append( cTemp );

			sprintf( cTemp, ",%f", bOrientations[ j ].hierarchicalRotation.rotationMatrix.M14 );
			transformedData.append( cTemp );

			sprintf( cTemp, ",%f", bOrientations[ j ].hierarchicalRotation.rotationMatrix.M21 );
			transformedData.append( cTemp );

			sprintf( cTemp, ",%f", bOrientations[ j ].hierarchicalRotation.rotationMatrix.M22 );
			transformedData.append( cTemp );

			sprintf( cTemp, ",%f", bOrientations[ j ].hierarchicalRotation.rotationMatrix.M23 );
			transformedData.append( cTemp );

			sprintf( cTemp, ",%f", bOrientations[ j ].hierarchicalRotation.rotationMatrix.M24 );
			transformedData.append( cTemp );

			sprintf( cTemp, ",%f", bOrientations[ j ].hierarchicalRotation.rotationMatrix.M31 );
			transformedData.append( cTemp );

			sprintf( cTemp, ",%f", bOrientations[ j ].hierarchicalRotation.rotationMatrix.M32 );
			transformedData.append( cTemp );

			sprintf( cTemp, ",%f", bOrientations[ j ].hierarchicalRotation.rotationMatrix.M33 );
			transformedData.append( cTemp );

			sprintf( cTemp, ",%f", bOrientations[ j ].hierarchicalRotation.rotationMatrix.M34 );
			transformedData.append( cTemp );

			sprintf( cTemp, ",%f", bOrientations[ j ].hierarchicalRotation.rotationMatrix.M41 );
			transformedData.append( cTemp );

			sprintf( cTemp, ",%f", bOrientations[ j ].hierarchicalRotation.rotationMatrix.M42 );
			transformedData.append( cTemp );

			sprintf( cTemp, ",%f", bOrientations[ j ].hierarchicalRotation.rotationMatrix.M43 );
			transformedData.append( cTemp );

			sprintf( cTemp, ",%f", bOrientations[ j ].hierarchicalRotation.rotationMatrix.M44 );
			transformedData.append( cTemp );
		}

		const char * c;
		c = transformedData.c_str();
		//MessageBoxA(NULL, c, "TEST INSIDE transformMovementData", MB_OK);
		//delete( c );//throwing assertion error, keep commented until fix is known

		//return string or send

		delete( cTemp );
	}

	std::string MData::getString()
	{
		return transformedData;
	}