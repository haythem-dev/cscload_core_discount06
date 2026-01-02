namespace Covid19XmlViewerBatch
{
    using System;
    using System.IO;
    
    /// <summary>
    ///
    /// </summary>
    public class Logger
    {
        /// <summary>
        ///
        /// </summary>
        public enum LogType { Error = -2, Warning = -1, Info = 0, None = 1 };

        /// <summary>
        ///
        /// </summary>
        private StreamWriter m_StreamWriter = null;

        /// <summary>
        ///
        /// </summary>
        private LogType m_LogType = LogType.Info;

        /// <summary>
        ///
        /// </summary>
        /// <param name="LogFile"></param>
        /// <param name="logtype"></param>
        public Logger(string LogFile, LogType logtype = LogType.Info)
        {
            m_LogType = logtype;
            m_StreamWriter = File.AppendText(LogFile);
            m_StreamWriter.AutoFlush = true;
        }

        /// <summary>
        ///
        /// </summary>
        ~Logger()
        {
            try
            {
                m_StreamWriter.Flush();
                m_StreamWriter.Close();
                m_StreamWriter.Dispose();
            }
            catch (Exception)
            {
            }
        }

        public void endLogging()
        {
            m_StreamWriter.Flush();
            m_StreamWriter.Close();
            m_StreamWriter.Dispose();
        }

        public string LogContent = "";

        /// <summary>
        ///
        /// </summary>
        /// <param name="logMessage"></param>
        /// <param name="type"></param>
        public void Log(string logMessage, LogType type = LogType.Info)
        {
            if (type <= m_LogType)
            {
                string typetext = "";
                switch (type)
                {
                    case LogType.Error:
                        typetext = "ERROR";
                        break;
                    case LogType.Warning:
                        typetext = "WARNING";
                        break;
                    case LogType.Info:
                        typetext = "INFO";
                        break;
                    case LogType.None:
                    default:
                        typetext = "";
                        break;
                }

                if (LogType.None == type)
                {
                    m_StreamWriter.WriteLine("{0}", logMessage);
                    LogContent = $"{LogContent}\r\n{logMessage}";
                }
                else
                {
                    string logtext = String.Format("{0} {1} {2}: {3}", DateTime.Now.ToLongDateString(), DateTime.Now.ToLongTimeString(), typetext, logMessage);
                    m_StreamWriter.WriteLine(logtext);
                    LogContent = $"{LogContent}\r\n{logtext}";
                }
            }
        }
    }
}
