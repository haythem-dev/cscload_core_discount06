using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace SalesWebCSCPlatformConsolidationTool
{
    public static class ToolConfiguration
    {
        #region Configuration
        static private string m_ConfigurationFile = @"./Configuration/CSCPlatformConsolidationToolConfig.xml";
        static private string m_ConfigurationAvailable = "";
        static private CSCPlatformConsolidationToolConfig m_Configuration = null;
        static public CSCPlatformConsolidationToolConfig Configuration
        {
            get
            {
                lock (m_ConfigurationAvailable)
                {
                    if (String.IsNullOrEmpty(m_ConfigurationAvailable))
                    {
                        m_Configuration = PHOENIXUtil.XML.Deserialize<CSCPlatformConsolidationToolConfig>(m_ConfigurationFile);
                        m_ConfigurationAvailable = String.Format("loaded at {0}", DateTime.Now.ToString("dd.MM.yyyy HH:mm:ss"));
                    }
                    return m_Configuration;
                }
            }

            private set
            {
                m_Configuration = value;
            }
        }
        #endregion

        #region Environment
        static private string m_Environment = null;
        static private string Environment
        {
            get
            {
                if( null == m_Environment )
                {
                    switch (Configuration.Environment)
                    {
                        case CSCPlatformConsolidationToolConfigEnvironment.Prod:
                            m_Environment = "";
                            break;
                        case CSCPlatformConsolidationToolConfigEnvironment.Test:
                        default:
                            m_Environment = "test";
                            break;
                    }
                }
                return m_Environment;
            }
        }
        #endregion Environment

        static public void PrepareWorkingDirectories()
        {
            PrepareDirectory(Configuration.Paths.BackupDir, false);
            PrepareServerDirectory();
        }

        static public void ActivateNewConfig()
        {
            Program.log("\t >>> ToolConfiguration.ActivateNewConfig started.");

            if( Directory.Exists(Configuration.Paths.TempDir))
            {
                foreach(var server in Configuration.Servers)
                {
                    Console.WriteLine("");
                    foreach (var application in Configuration.Applications)
                    {
                        var applicationDirectory = String.Format(@"{0}\{1}\{2}{3}{4}",
                            Configuration.Paths.TempDir, server, application.Value, getEnvironment(application), getVersion(application));

                        if (Directory.Exists(applicationDirectory))
                        {
                            Console.WriteLine("\nActivation for Server {0} Application {1}{2} Dir {3}", server, application.Value, application.ApplicationVersion, applicationDirectory);

                            foreach (var iFace in Configuration.Interfaces.MSV3v1Interfaces)
                            {
                                var iFaceConfig = String.Format(@"{0}\{1}\bin\Config\SalesWebConfig.xml", applicationDirectory, iFace);
                                if (File.Exists(iFaceConfig))
                                {
                                    Console.WriteLine("\t InterfaceConfig {0}", iFaceConfig);
                                    var remoteFile = String.Format(@"\\{0}\D$\Data\{1}{2}{3}\{4}\bin\Config\SalesWebConfig.xml",
                                        server, application.Value,
                                        getEnvironment(application),
                                        getVersion(application),
                                        iFace);
                                    File.Copy(remoteFile, remoteFile + ".BACKUP.xml", true);
                                    if (Configuration.Modus == CSCPlatformConsolidationToolConfigModus.Simulation)
                                    {
                                        remoteFile = String.Format("{0}.SIMULATION.xml", remoteFile);
                                    }
                                    Console.WriteLine("\t\t RemoteFile: {0}\n", remoteFile);
                                    File.Copy(iFaceConfig, remoteFile, true);
                                }
                            }

                            foreach (var iFace in Configuration.Interfaces.MSV3v2Interfaces)
                            {
                                var iFaceConfig = String.Format(@"{0}\{1}\bin\Config\SalesWebConfig.xml", applicationDirectory, iFace);
                                if (File.Exists(iFaceConfig))
                                {
                                    Console.WriteLine("\t InterfaceConfig {0}", iFaceConfig);
                                    var remoteFile = String.Format(@"\\{0}\D$\Data\{1}{2}{3}\{4}\bin\Config\SalesWebConfig.xml",
                                        server, application.Value,
                                        getEnvironment(application),
                                        getVersion(application),
                                        iFace);
                                    File.Copy(remoteFile, remoteFile + ".BACKUP.xml", true);
                                    if (Configuration.Modus == CSCPlatformConsolidationToolConfigModus.Simulation)
                                    {
                                        remoteFile = String.Format("{0}.SIMULATION.xml", remoteFile);
                                    }
                                    Console.WriteLine("\t\t RemoteFile: {0}\n", remoteFile);
                                    File.Copy(iFaceConfig, remoteFile, true);
                                }
                            }

                            foreach (var iFace in Configuration.Interfaces.SwimpInterfaces)
                            {
                                var iFaceConfig = String.Format(@"{0}\{1}\bin\Config\SalesWebConfig.xml", applicationDirectory, iFace);
                                if (File.Exists(iFaceConfig))
                                {
                                    Console.WriteLine("\t InterfaceConfig {0}", iFaceConfig);
                                    var remoteFile = String.Format(@"\\{0}\D$\Data\{1}\bin\Config\SalesWebConfig.xml", server, iFace);
                                    File.Copy(remoteFile, remoteFile + ".BACKUP.xml", true);
                                    if ( Configuration.Modus == CSCPlatformConsolidationToolConfigModus.Simulation )
                                    {
                                        remoteFile = String.Format("{0}.SIMULATION.xml", remoteFile);
                                    }
                                    Console.WriteLine("\t\t RemoteFile: {0}\n", remoteFile);
                                    File.Copy(iFaceConfig, remoteFile, true);
                                }
                            }
                        }
                    }
                    Console.WriteLine();
                }
            }

            Program.log("\t\t ToolConfiguration.ActivateNewConfig finished.");
        }

        static private string getEnvironment(CSCPlatformConsolidationToolConfigApplication application)
        {
            if (application.Value != "swimp")
            {
                if (Configuration.Environment == CSCPlatformConsolidationToolConfigEnvironment.Test)
                {
                    return "test";
                }
            }
            return "";
        }

        static private string getVersion(CSCPlatformConsolidationToolConfigApplication application)
        {
            if (!String.IsNullOrEmpty(application.ApplicationVersion))
            {
                return String.Format(@"\{0}", application.ApplicationVersion);
            }
            return "";
        }

        static public void PrepareTempDirectory()
        {
            try
            {
                Program.log("\t >>> ToolConfiguration.PrepareTempDirectory started.");
                if (Directory.Exists(Configuration.Paths.BackupDir))
                {
                    string[] files = Directory.GetFiles(Configuration.Paths.BackupDir, "*.*", SearchOption.AllDirectories);
                    Program.log(String.Format("\t\t Found {0} files.", files.Length));
                    foreach (var f in files)
                    {
                        try
                        {
                            //Program.log(f);
                            var fi = new FileInfo(f);
                            PrepareDirectory(fi.DirectoryName.Replace(Configuration.Paths.BackupDir, Configuration.Paths.TempDir), true);
                            var newFileName = f.Replace(Configuration.Paths.BackupDir, Configuration.Paths.TempDir);
                            File.Copy(f, newFileName);

                            var needleForMSV3v1 = String.Format(@"msv3{0}\v1.0\", "").ToLower();
                            var needleForMSV3v2 = String.Format(@"msv3{0}\v2.0\", "").ToLower();

                            if (newFileName.Contains(needleForMSV3v1))
                            {
                                try
                                {
                                    var move = SalesWebMove.Move.createMove(newFileName, "msv3", "v1.0");
                                    move.doMove(Configuration.Branches2BMoved.Direction, Configuration.Branches2BMoved.Branch, newFileName);
                                }
                                catch(Exception ex)
                                {
                                    throw new Exception(String.Format("Creating Move for MSV3v1 failed: {0}", ex.Message));
                                }
                            }
                            else if (newFileName.Contains(needleForMSV3v2))
                            {
                                try
                                {
                                    var move = SalesWebMove.Move.createMove(newFileName, "msv3", "v2.0");
                                    move.doMove(Configuration.Branches2BMoved.Direction, Configuration.Branches2BMoved.Branch, newFileName);
                                }
                                catch (Exception ex)
                                {
                                    throw new Exception(String.Format("Creating Move for MSV3v2 failed: {0}", ex.Message));
                                }
                            }
                            else if (newFileName.Contains(@"swimp\sw-b-de-"))
                            {
                                try
                                {
                                    var move = SalesWebMove.Move.createMove(newFileName, "swimp", "");
                                    move.doMove(Configuration.Branches2BMoved.Direction, Configuration.Branches2BMoved.Branch, newFileName);
                                }
                                catch (Exception ex)
                                {
                                    throw new Exception(String.Format("Creating Move for SWIMP failed: {0}", ex.Message));
                                }
                            }
                            else
                            {
                                Console.WriteLine("application not recognized: {0}", newFileName);
                                Console.WriteLine("\t {0}", needleForMSV3v1);
                                Console.WriteLine("\t {0}", needleForMSV3v2);
                                throw new Exception("Application not recognized!");
                            }
                            //Program.log("< " + newFileName);
                        }
                        catch(Exception ex)
                        {
                            Program.log("- - - Exception in ToolConfiguration.PrepareTempDirectory - - -");
                            Program.log(String.Format("File: {0}", f));
                            throw ex;
                        }
                    }
                }
                Program.log("\t\t ToolConfiguration.PrepareTempDirectory finished.");
            }
            catch(Exception ex)
            {
                Program.log("- - - Exception in ToolConfiguration.PrepareTempDirectory - - -");
                throw ex;
            }
        }

        #region Configuration Backup
        static public void BackupCurrentConfigurations()
        {
            try
            {
                Program.log("\t >>> ToolConfiguration.BackupCurrentConfigurations started.");
                foreach (var server in Configuration.Servers)
                {
                    foreach (var application in Configuration.Applications)
                    {
                        if ("msv3" == application.Value && "v1.0" == application.ApplicationVersion)
                        {
                            BackupConfigurationMSV3v1(server);
                        }
                        else if ("msv3" == application.Value && "v2.0" == application.ApplicationVersion)
                        {
                            BackupConfigurationMSV3v2(server);
                        }
                        else if ("swimp" == application.Value)
                        {
                            BackupConfigurationSWIMP(server);
                        }
                    }
                }
                Program.log("\t\t ToolConfiguration.BackupCurrentConfigurations finished.");
            }
            catch (Exception ex)
            {
                Program.log("- - - Exception in ToolConfiguration.BackupCurrentConfigurations - - -");
                throw ex;
            }
        }

        static private void BackupConfigurationMSV3v1(string server)
        {
            var localServerPath = String.Format(@"{0}\{1}", Configuration.Paths.BackupDir, server);
            var serverPath = String.Format(@"\\{0}\D$\Data", server);
            var applicationPath = String.Format(@"msv3{0}\v1.0", "");
            foreach( var iface in Configuration.Interfaces.MSV3v1Interfaces )
            {
                var ifaceConfigFile = String.Format(@"{0}\{1}\bin\Config\SalesWebConfig.xml", applicationPath, iface);
                var serverConfigFile = String.Format(@"{0}\{1}", serverPath, ifaceConfigFile);
                if (File.Exists(serverConfigFile))
                {
                    //Program.log(String.Format("Creating MSV3v1 Backupfile {0}", serverConfigFile.Replace(serverPath, localServerPath)));
                    PrepareDirectory(serverConfigFile.Replace(serverPath, localServerPath).Replace(@"\SalesWebConfig.xml", ""), true);
                    File.Copy(serverConfigFile, serverConfigFile.Replace(serverPath, localServerPath));
                }
            }
        }

        static private void BackupConfigurationMSV3v2(string server)
        {
            var localServerPath = String.Format(@"{0}\{1}", Configuration.Paths.BackupDir, server);
            var serverPath = String.Format(@"\\{0}\D$\Data", server);
            var applicationPath = String.Format(@"msv3{0}\v2.0", "");
            foreach (var iface in Configuration.Interfaces.MSV3v2Interfaces)
            {
                var ifaceConfigFile = String.Format(@"{0}\{1}\bin\Config\SalesWebConfig.xml", applicationPath, iface);
                var serverConfigFile = String.Format(@"{0}\{1}", serverPath, ifaceConfigFile);
                if (File.Exists(serverConfigFile))
                {
                    //Program.log(String.Format("Creating MSV3v2 Backupfile {0}", serverConfigFile.Replace(serverPath, localServerPath)));
                    PrepareDirectory(serverConfigFile.Replace(serverPath, localServerPath).Replace(@"\SalesWebConfig.xml", ""), true);
                    File.Copy(serverConfigFile, serverConfigFile.Replace(serverPath, localServerPath));
                }
            }
        }

        static private void BackupConfigurationSWIMP(string server)
        {
            var localServerPath = String.Format(@"{0}\{1}\swimp", Configuration.Paths.BackupDir, server);
            var serverPath = String.Format(@"\\{0}\D$\Data", server);
            var applicationPath = "";
            foreach (var iface in Configuration.Interfaces.SwimpInterfaces)
            {
                var ifaceConfigFile = String.Format(@"{0}\{1}\bin\Config\SalesWebConfig.xml", applicationPath, iface);
                var serverConfigFile = String.Format(@"{0}\{1}", serverPath, ifaceConfigFile);
                if (File.Exists(serverConfigFile))
                {
                    //Program.log(String.Format("Creating SWIMP Backupfile {0}", serverConfigFile.Replace(serverPath, localServerPath)));
                    PrepareDirectory(serverConfigFile.Replace(serverPath, localServerPath).Replace(@"\SalesWebConfig.xml", ""), true);
                    File.Copy(serverConfigFile, serverConfigFile.Replace(serverPath, localServerPath));
                }
            }
        }

        #endregion Configuration Backup

        #region Utilities
        static private void PrepareServerDirectory()
        {
            foreach (var server in Configuration.Servers)
            {
                PrepareDirectory(String.Format(@"{0}\{1}", Configuration.Paths.BackupDir, server), true);
            }
        }

        static private void PrepareDirectory(string path, bool deleteExisting)
        {
            TreatExistingDirectory(path, deleteExisting);
            CreateDirectory(path);
        }

        static private void CreateDirectory(string path)
        {
            DirectoryInfo di = new DirectoryInfo(path);
            di.Create();
            di = null;
        }

        static private void TreatExistingDirectory(string path, bool deleteExisting)
        {
            DirectoryInfo di = new DirectoryInfo(path);
            if (di.Exists)
            {
                if (deleteExisting)
                {
                    di.Delete(true);
                }
                else
                {
                    di.MoveTo(String.Format("{0}.{1}", path, DateTime.Now.ToString("yyyyMMdd_HHmmss")));
                }
            }
            di = null;
        }
        #endregion Utilities
    }
}
