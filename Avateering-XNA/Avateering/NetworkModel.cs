using System;
using System.Net;
using System.IO;
//using System.Windows; //PeePeeSpeed - Commented as .Forms also provides MessageBox
using System.Windows.Forms;

namespace Microsoft.Samples.Kinect.Avateering
{
    public class NetworkModel
    {
        string url;
        string queue;
        
        WebRequest wrGetUrl;
        Stream objStream;
        StreamReader objReader;

        string transformedData;

        //---------------------------------------------------
        // @Name:		NetworkModel
        // @Author:		Lane - PeePeeSpeed
        // @Inputs:		string - url, string queue
        // @Outputs:	NULL
        // 
        // @Desc:		Class constructor for NetworkModel
        //---------------------------------------------------
        public NetworkModel( string httpURL, string qid )
        {
            url = httpURL;
            queue = qid;

            attemptConnection( url, queue);
        }

        //---------------------------------------------------
        // @Name:		attemptConnection
        // @Author:		Lane - PeePeeSpeed
        // @Inputs:		string url, string queue
        // @Outputs:	NULL
        // 
        // @Desc:		Attempts to create a connection
        //			    to the server for data transfer.
        //---------------------------------------------------
        public void attemptConnection(string u, string q)
        {
            try
            {
                wrGetUrl = WebRequest.Create(u + "?cmd=get&Value=" + q);
                objStream = wrGetUrl.GetResponse().GetResponseStream();
                objReader = new StreamReader(objStream);

                //assert here?
            }
            catch (System.Net.WebException)
            {
                DialogResult dialogResult = MessageBox.Show("Could not establish connection to server\n\nDo you want to try again? System will exit on No.", "Error", MessageBoxButtons.YesNo);

                switch (dialogResult)
                {
                    case DialogResult.Yes:
                        attemptConnection(u, q);
                        break;
                    case DialogResult.No:
                        System.Environment.Exit(0);
                        break;
                }
            }
        }

        //---------------------------------------------------
        // @Name:		getDataFromNetwork
        // @Author:		Lane - PeePeeSpeed
        // @Inputs:		NULL
        // @Outputs:	NULL
        // 
        // @Desc:		Attempts to pull the latest
        //			    string of data from the server.
        //---------------------------------------------------
        public void getDataFromNetwork()
        {
            //assert harr?
            wrGetUrl = WebRequest.Create(url + "?cmd=get&Value=" + queue);
            objStream = wrGetUrl.GetResponse().GetResponseStream();
            objReader = new StreamReader(objStream);
            transformedData = objReader.ReadToEnd();
            objReader.Close();
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
            //assert here?
            StreamWriter f = new StreamWriter("AvateeringData.txt");
            f.Write(transformedData);
            f.Close();
        }

        //---------------------------------------------------
        // @Name:		readFromFile
        // @Author:		Lane - PeePeeSpeed
        // @Inputs:		NULL
        // @Outputs:	NULL
        // 
        // @Desc:		Reads a string of data from 
        //			    the AvateeringData.txt file.
        //			    Used for testing only.
        //---------------------------------------------------
        public void readFromFile()
        {
            //assert here?
            StreamReader fS = new StreamReader("AvateeringData.txt");
            string ss = fS.ReadToEnd();
            fS.Close();
        }

        //---------------------------------------------------
        // @Name:		getTransformedData
        // @Author:		Lane - PeePeeSpeed
        // @Inputs:		NULL
        // @Outputs:	string transformedData
        // 
        // @Desc:		This GET method returns the string
        //			    transformedData.
        //---------------------------------------------------
        public string getTransformedData()
        {
            return transformedData;
        }
    }
}