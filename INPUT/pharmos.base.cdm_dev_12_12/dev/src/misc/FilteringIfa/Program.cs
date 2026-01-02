using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace FilteringIfa
{
    class Program
    {
        static void Main(string[] args)
        {
            FileStream m_stream = File.OpenRead("liefd002.ild");
            StreamReader m_StreamReader = new StreamReader(m_stream);
            StreamWriter m_StreamWriter = null;

            string outputFile = "IFA_20219_A11VERIHOC.csv";

            File.Delete(outputFile);
            m_StreamWriter = File.AppendText(outputFile);
            m_StreamWriter.AutoFlush = true;
            
            int line_counter = 0;
            string[] stringArr;

            string line = m_StreamReader.ReadLine();
            
            while (line != null)
            {
//                stringArr = line.Split(new[] { "¤" }, StringSplitOptions.None);
                stringArr = line.Split(new[] { ";" }, StringSplitOptions.None);

                if (stringArr.Length > 20 && stringArr[117] != "00000000")
                    //)
                    m_StreamWriter.WriteLine(stringArr[2] + ";" + stringArr[117] + ";");

                ++line_counter;
                
                line = m_StreamReader.ReadLine();
             }

            // Aufräumen
            m_StreamWriter.Flush();
            m_StreamWriter.Close();
            m_StreamWriter.Dispose();
            
            m_StreamReader.Close();
            m_StreamReader.Dispose();
        }
    }
}
