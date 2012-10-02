using System;
using System.Net;
using System.IO;
//using System.Windows; //Commented as .Forms also provides MessageBox
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

        //implement HTTP requests etc
        public NetworkModel( string httpURL, string qid )
        {
            url = httpURL;
            queue = qid;

            attemptConnection( url, queue);

            //MessageBox.Show(transformedData);

            writeToFile();
        }

        public void attemptConnection(string u, string q)
        {
            try
            {
                wrGetUrl = WebRequest.Create(u + "?cmd=get&Value=" + q);

                objStream = wrGetUrl.GetResponse().GetResponseStream();

                objReader = new StreamReader(objStream);

                //assert here?
                //getDataFromNetwork();
            }
            catch (System.Net.WebException)
            {
                DialogResult dialogResult = MessageBox.Show("Could not establish connection to server\n\nDo you want to try again?", "Error", MessageBoxButtons.YesNo);
                //asserts in all the places?
                switch (dialogResult)
                {
                    case DialogResult.Yes:
                        attemptConnection(u, q);
                        break;
                    case DialogResult.No:
                        break;
                }
            }
        }

        public void getDataFromNetwork()
        {
            //assert harr?
            transformedData = objReader.ReadToEnd();
        }

        public void writeToFile()
        {
            //assert here?
            StreamWriter f = new StreamWriter("AvateeringData.txt");
            f.Write(transformedData);

            f.Close();
        }

        public void readFromFile()
        {
            //assert here?
            StreamReader fS = new StreamReader("AvateeringData.txt");
            string ss = fS.ReadToEnd();

            fS.Close();
        }

        public string getTransformedData()
        {
            return transformedData;
        }

    }
}