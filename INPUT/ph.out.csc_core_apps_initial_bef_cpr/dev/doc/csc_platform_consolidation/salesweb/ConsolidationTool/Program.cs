using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace SalesWebCSCPlatformConsolidationTool
{
    class Program
    {
        static void Main()
        {
            try
            {
                logWhatWillBeDone();
                ToolConfiguration.PrepareWorkingDirectories();
                ToolConfiguration.BackupCurrentConfigurations();
                ToolConfiguration.PrepareTempDirectory();
                ToolConfiguration.ActivateNewConfig();
            }
            catch(Exception ex)
            {
                log(String.Format("Unexpected Exception of Type {0}", ex.GetType().ToString()));
                log(ex.Message);
            }

            log("--- FINISHED ---");
            Console.ReadLine();
        }

        static public void log(string message)
        {
            Console.WriteLine(String.Format("{0} > {1}", DateTime.Now.ToString("dd.MM.yyyy HH:mm:ss"), message));
        }

        static public void logWhatWillBeDone()
        {
            var sb = new StringBuilder();
            sb.AppendLine();
            sb.AppendLine();
            sb.AppendFormat("Changing the [{0}] environment.", ToolConfiguration.Configuration.Environment);
            sb.AppendLine();
            sb.AppendFormat("Moving the following branches in direction {0}: ", ToolConfiguration.Configuration.Branches2BMoved.Direction);
            sb.AppendLine();
            foreach ( var branch in ToolConfiguration.Configuration.Branches2BMoved.Branch )
            {
                sb.AppendFormat("\t{0}", branch);
            }
            sb.AppendLine();
            sb.AppendLine("The Following Servers will be changed: ");
            foreach( var server in ToolConfiguration.Configuration.Servers)
            {
                sb.AppendFormat("\t{0}", server);
                sb.AppendLine();
            }

            log(sb.ToString());
        }



    }
}
