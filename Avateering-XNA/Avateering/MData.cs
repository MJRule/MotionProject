using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Kinect;
using System.Windows;
using System.IO;

namespace Microsoft.Samples.Kinect.Avateering
{
    public class MData
    {
        private Skeleton skeleton;
        private string transformedData;
        private string[] splitString;
        private int skeletonIndex;

        private string writeString;

        //---------------------------------------------------
        // @Name:		MData
        // @Author:		Lane - PeePeeSpeed
        // @Inputs:		string networkString
        // @Outputs:	NULL
        // 
        // @Desc:		Class constructor for MData.
        //			    Takes a string for the data
        //			    to be transformed into a Skeleton.
        //---------------------------------------------------
        public MData(string networkString)
        {
            transformedData = networkString;
            transformMDataToSkeleton();
        }

        //---------------------------------------------------
        // @Name:		getSkeletonData
        // @Author:		Lane - PeePeeSpeed
        // @Inputs:		NULL
        // @Outputs:	Microsoft.Kinect.Skeleton skeleton
        // 
        // @Desc:		This GET method returns a completed
        //			    Skeleton ready to be drawn.
        //---------------------------------------------------
        public Skeleton getSkeletonData()
        {
            return skeleton;
        }

        //---------------------------------------------------
        // @Name:		setSkeletonData
        // @Author:		Lane - PeePeeSpeed
        // @Inputs:		Microsoft.Kinect.Skeleton skeleton
        // @Outputs:	NULL
        // 
        // @Desc:		This SET method sets the MData
        //			    Skeleton to an inputted Skeleton.
        //---------------------------------------------------
        public void setSkeletonData(Skeleton s)
        {
            skeleton = s;
        }

        //---------------------------------------------------
        // @Name:		getTransMData
        // @Author:		Lane - PeePeeSpeed
        // @Inputs:		NULL
        // @Outputs:	string transformedData
        // 
        // @Desc:		This GET method returns the
        //			    unedited transformedData string.
        //---------------------------------------------------
        public string getTransMData()
        {
            return transformedData;
        }

        //---------------------------------------------------
        // @Name:		setTransMData
        // @Author:		Lane - PeePeeSpeed
        // @Inputs:		string transformedData
        // @Outputs:	NULL
        // 
        // @Desc:		This SET method sets the MData
        //			    transformedData string to an
        //			    inputted string.
        //---------------------------------------------------
        public void setTransMData(string s)
        {
            transformedData = s;
            transformMDataToSkeleton();
        }

        //---------------------------------------------------
        // @Name:		transformMDataToSkeleton
        // @Author:		Lane - PeePeeSpeed
        // @Inputs:		NULL
        // @Outputs:	NULL
        // 
        // @Desc:		Takes the string received from
        //			    the server and splits it into
        //			    tokens based on the comma delimiter.
        //			    Then sets each index in the splitString
        //			    array into the correct value
        //			    within a Microsoft.Kinect.Skeleton.
        //---------------------------------------------------
        public void transformMDataToSkeleton()
        {
            if (null == skeleton)
            {
                skeleton = new Skeleton();
            }

            int count = 0;
            int iterator = 0;
            int jIterator = 0;
            Array jointTypeValues = Enum.GetValues(typeof(JointType));

            try
            {
                splitString = transformedData.Split(',');
            }
            catch (System.NullReferenceException)
            {
                return;
            }

            Matrix4[] absoluteM4 = new Matrix4[20];
            Vector4[] absoluteV4 = new Vector4[20];
            Matrix4[] hierarchicalM4 = new Matrix4[20];
            Vector4[] hierarchicalV4 = new Vector4[20];
            SkeletonPoint[] sPoint = new SkeletonPoint[21];

            //assert here?
            if (splitString[0].Equals("\r\nnull") || splitString[0].Equals(""))//this is what defines null from 3Der.php
            {
                return;
            }

            skeletonIndex = Convert.ToInt32(splitString[0]);
            count++;

            skeleton.TrackingState = (SkeletonTrackingState)Convert.ToInt32(splitString[count]);
            count++;
            skeleton.TrackingId = Convert.ToInt32(splitString[count]);
            count++;

            sPoint[0].X = (float)Convert.ToDouble(splitString[count]);
            count++;
            sPoint[0].Y = (float)Convert.ToDouble(splitString[count]);
            count++;
            sPoint[0].Z = (float)Convert.ToDouble(splitString[count]);
            count++;

            jIterator++;

            skeleton.Position = sPoint[0];
            skeleton.ClippedEdges = 0;

            foreach (JointType j in jointTypeValues)
            {
                Joint temp = skeleton.Joints[j];
                
                sPoint[jIterator].X = (float)Convert.ToDouble(splitString[count]);
                count++;
                sPoint[jIterator].Y = (float)Convert.ToDouble(splitString[count]);
                count++;
                sPoint[jIterator].Z = (float)Convert.ToDouble(splitString[count]);
                count++;

                temp.Position = sPoint[jIterator];

                temp.TrackingState = (JointTrackingState)Convert.ToInt32(splitString[count]);
                count++;

                skeleton.Joints[j] = temp;
            }

            foreach (JointType j in jointTypeValues)
            {
                BoneOrientation bO = skeleton.BoneOrientations[j];

                absoluteV4[iterator].X = (float)Convert.ToDouble(splitString[count]);
                count++;
                absoluteV4[iterator].Y = (float)Convert.ToDouble(splitString[count]);
                count++;
                absoluteV4[iterator].Z = (float)Convert.ToDouble(splitString[count]);
                count++;
                absoluteV4[iterator].W = (float)Convert.ToDouble(splitString[count]);
                count++;

                bO.AbsoluteRotation.Quaternion = absoluteV4[iterator];

                absoluteM4[iterator].M11 = (float)Convert.ToDouble(splitString[count]);
                count++;
                absoluteM4[iterator].M12 = (float)Convert.ToDouble(splitString[count]);
                count++;
                absoluteM4[iterator].M13 = (float)Convert.ToDouble(splitString[count]);
                count++;
                absoluteM4[iterator].M14 = (float)Convert.ToDouble(splitString[count]);
                count++;
                absoluteM4[iterator].M21 = (float)Convert.ToDouble(splitString[count]);
                count++;
                absoluteM4[iterator].M22 = (float)Convert.ToDouble(splitString[count]);
                count++;
                absoluteM4[iterator].M23 = (float)Convert.ToDouble(splitString[count]);
                count++;
                absoluteM4[iterator].M24 = (float)Convert.ToDouble(splitString[count]);
                count++;
                absoluteM4[iterator].M31 = (float)Convert.ToDouble(splitString[count]);
                count++;
                absoluteM4[iterator].M32 = (float)Convert.ToDouble(splitString[count]);
                count++;
                absoluteM4[iterator].M33 = (float)Convert.ToDouble(splitString[count]);
                count++;
                absoluteM4[iterator].M34 = (float)Convert.ToDouble(splitString[count]);
                count++;
                absoluteM4[iterator].M41 = (float)Convert.ToDouble(splitString[count]);
                count++;
                absoluteM4[iterator].M42 = (float)Convert.ToDouble(splitString[count]);
                count++;
                absoluteM4[iterator].M43 = (float)Convert.ToDouble(splitString[count]);
                count++;
                absoluteM4[iterator].M44 = (float)Convert.ToDouble(splitString[count]);
                count++;

                bO.AbsoluteRotation.Matrix = absoluteM4[iterator];

                hierarchicalV4[iterator].X = (float)Convert.ToDouble(splitString[count]);
                count++;
                hierarchicalV4[iterator].Y = (float)Convert.ToDouble(splitString[count]);
                count++;
                hierarchicalV4[iterator].Z = (float)Convert.ToDouble(splitString[count]);
                count++;
                hierarchicalV4[iterator].W = (float)Convert.ToDouble(splitString[count]);
                count++;

                bO.HierarchicalRotation.Quaternion = hierarchicalV4[iterator];

                hierarchicalM4[iterator].M11 = (float)Convert.ToDouble(splitString[count]);
                count++;
                hierarchicalM4[iterator].M12 = (float)Convert.ToDouble(splitString[count]);
                count++;
                hierarchicalM4[iterator].M13 = (float)Convert.ToDouble(splitString[count]);
                count++;
                hierarchicalM4[iterator].M14 = (float)Convert.ToDouble(splitString[count]);
                count++;
                hierarchicalM4[iterator].M21 = (float)Convert.ToDouble(splitString[count]);
                count++;
                hierarchicalM4[iterator].M22 = (float)Convert.ToDouble(splitString[count]);
                count++;
                hierarchicalM4[iterator].M23 = (float)Convert.ToDouble(splitString[count]);
                count++;
                hierarchicalM4[iterator].M24 = (float)Convert.ToDouble(splitString[count]);
                count++;
                hierarchicalM4[iterator].M31 = (float)Convert.ToDouble(splitString[count]);
                count++;
                hierarchicalM4[iterator].M32 = (float)Convert.ToDouble(splitString[count]);
                count++;
                hierarchicalM4[iterator].M33 = (float)Convert.ToDouble(splitString[count]);
                count++;
                hierarchicalM4[iterator].M34 = (float)Convert.ToDouble(splitString[count]);
                count++;
                hierarchicalM4[iterator].M41 = (float)Convert.ToDouble(splitString[count]);
                count++;
                hierarchicalM4[iterator].M42 = (float)Convert.ToDouble(splitString[count]);
                count++;
                hierarchicalM4[iterator].M43 = (float)Convert.ToDouble(splitString[count]);
                count++;
                hierarchicalM4[iterator].M44 = (float)Convert.ToDouble(splitString[count]);
                count++;

                bO.HierarchicalRotation.Matrix = hierarchicalM4[iterator];

                skeleton.BoneOrientations[j] = bO;

                iterator++;
            }

            /*TEST Split into array and write to file.*/
            //writeString = "";
            //int i = 0;
            //foreach (string s in splitString)
            //{
            //    System.Diagnostics.Debug.Write(s + " " );
            //    i++;
            //    writeString += s + " ";
            //}
            //MessageBox.Show(i.ToString());

            //writeToFile();
        }

        //---------------------------------------------------
        // @Name:		getSkeletonIndex
        // @Author:		Lane - PeePeeSpeed
        // @Inputs:		NULL
        // @Outputs:	int skeletonIndex
        // 
        // @Desc:		This GET method returns the index
        //			    of the Skeleton. (0 - 5).
        //---------------------------------------------------
        public int getSkeletonIndex()
        {
            return skeletonIndex;
        }

        //---------------------------------------------------
        // @Name:		writeToFile
        // @Author:		Lane - PeePeeSpeed
        // @Inputs:		NULL
        // @Outputs:	NULL
        // 
        // @Desc:		Writes a string of data to the
        //			    AvateeringData.txt file. Used
        //			    for testing only.
        //---------------------------------------------------
        public void writeToFile()
        {
            StreamWriter f = new StreamWriter("AvateeringData.txt");
            f.Write(writeString);

            f.Close();
        }
    }
}