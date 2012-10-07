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

        public MData(string networkString)
        {
            transformedData = networkString;
            transformMDataToSkeleton();
        }

        public MData()
        { }

        public Skeleton getSkeletonData()
        {
            return skeleton;
        }

        public void setSkeletonData(Skeleton s)
        {
            skeleton = s;
        }

        public string getTransMData()
        {
            return transformedData;
        }

        public void setTransMData(string s)
        {
            transformedData = s;
            transformMDataToSkeleton();
        }

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
                //MessageBox.Show("There is no data being retreived from the server!", "Error");
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
                //MessageBox.Show("There is no data being retreived from the server!", "Error");//system seems to be pulling "" only from server.FIX THIS
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

                /* Test for reference ID, they are the same. */
                //MessageBox.Show(bO.GetHashCode().ToString());
                //MessageBox.Show(skeleton.BoneOrientations[j].GetHashCode().ToString());

                absoluteV4[iterator].X = (float)Convert.ToDouble(splitString[count]);
                count++;
                absoluteV4[iterator].Y = (float)Convert.ToDouble(splitString[count]);
                count++;
                absoluteV4[iterator].Z = (float)Convert.ToDouble(splitString[count]);
                count++;
                absoluteV4[iterator].W = (float)Convert.ToDouble(splitString[count]);
                count++;

                /*MessageBox.Show(absoluteV4[iterator].X.ToString() + " " + absoluteV4[iterator].Y.ToString()
                    + " " + absoluteV4[iterator].Z.ToString(), "absoluteV4" );*/

                bO.AbsoluteRotation.Quaternion = absoluteV4[iterator];

                /*MessageBox.Show(bO.AbsoluteRotation.Quaternion.X.ToString() + " " + bO.AbsoluteRotation.Quaternion.Y.ToString()
                    + " " + bO.AbsoluteRotation.Quaternion.Z.ToString());*/

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

            //Tested absoluteV4[0] and [1]'s Hashcodes. They were different.

            /*foreach (JointType j in jointTypeValues)
            {
                Joint jOr = skeleton.Joints[j];
                MessageBox.Show(jOr.Position.X.ToString() + " " + jOr.Position.Y.ToString()
                    + " " + jOr.Position.Z.ToString(), "Joint Position");
            }

            foreach (JointType j in jointTypeValues)
            {
                BoneOrientation bOr = skeleton.BoneOrientations[j];
                MessageBox.Show(bOr.AbsoluteRotation.Quaternion.X.ToString() + " " +  bOr.AbsoluteRotation.Quaternion.Y.ToString()
                    + " " + bOr.AbsoluteRotation.Quaternion.Z.ToString(), "skeleton Rotation");
            }*/

            /*TEST Split into array for distribution*/
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

        public int getSkeletonIndex()
        {
            return skeletonIndex;
        }
        
        public void writeToFile()//For Testing Purposes.
        {
            StreamWriter f = new StreamWriter("AvateeringData.txt");
            f.Write(writeString);

            f.Close();
        }
    }
}
