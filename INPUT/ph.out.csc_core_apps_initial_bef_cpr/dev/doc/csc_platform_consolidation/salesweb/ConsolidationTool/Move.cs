using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace SalesWebMove
{
    public class Move
    {
        private SalesWebConfigStrategy ConfigStrategy;

        public static Move createMove(string configFileFullName, string application, string version = "")
        {
            try
            {
                Move retval = null;
                if ("msv3" == application.ToLower())
                {
                    if ("v1.0" == version.ToLower())
                    {
                        retval = new Move(new MSV3v1ConfigStrategy());
                    }
                    else if ("v2.0" == version.ToLower())
                    {
                        retval = new Move(new MSV3v2ConfigStrategy());
                    }

                }
                else if ("swimp" == application.ToLower())
                {
                    retval = new Move(new SwimpConfigStrategy());
                }
                retval.loadConfig(configFileFullName);

                if( null == retval )
                {
                    throw new Exception("No Configuration created.");
                }

                return retval;
            }
            catch(Exception ex)
            {
                var sb = new StringBuilder();
                sb.Append("Exception in SalesWebMove.Move.createMove");
                sb.AppendFormat("\nConfigFile : {0}", configFileFullName);
                sb.AppendFormat("\nApplication: {0}", application);
                sb.AppendFormat("\nVersion    : {0}", version);
                sb.AppendFormat("\nMessage    : {0}", ex.Message);
                var e = new Exception(sb.ToString());
                throw e;
            }
        }

        public Move(SalesWebConfigStrategy strategy)
        {
            ConfigStrategy = strategy;
        }

        public void loadConfig(string ConfigFullName)
        {
            try
            {
                ConfigStrategy.loadConfig(ConfigFullName);
            }
            catch(Exception ex)
            {
                throw new Exception(String.Format("Exception in Move.loadConfig for file {0} \n Exception: {1}", ConfigFullName, ex.Message));
            }
        }

        public void moveBranchesFromNorthToSouth(int[] branches, string newConfigFileFullName)
        {
            try
            {
                ConfigStrategy.moveBranchesFromNorthToSouth(branches);
                createDirectory(newConfigFileFullName);
                ConfigStrategy.writeConfiguration(newConfigFileFullName);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Exception in moveBranchesFromNorthToSouth for File {0}", newConfigFileFullName);
                throw ex;
            }
        }

        public void doMove(CSCPlatformConsolidationToolConfigBranches2BMovedDirection direction, int[] branches, string newFileName)
        {
            switch (direction)
            {
                case CSCPlatformConsolidationToolConfigBranches2BMovedDirection.ActivateInNorth:
                    activateBranchesInNorth(branches, newFileName);
                    break;
                case CSCPlatformConsolidationToolConfigBranches2BMovedDirection.ActivateInSouth:
                    activateBranchesInSouth(branches, newFileName);
                    break;
                case CSCPlatformConsolidationToolConfigBranches2BMovedDirection.DeactivateCompletely:
                    deactivateCompletely(branches, newFileName);
                    break;
                case CSCPlatformConsolidationToolConfigBranches2BMovedDirection.DeactivateNorth:
                    deactivateNorth(branches, newFileName);
                    break;
                case CSCPlatformConsolidationToolConfigBranches2BMovedDirection.DeactivateSouth:
                    deactivateSouth(branches, newFileName);
                    break;
                case CSCPlatformConsolidationToolConfigBranches2BMovedDirection.North2South:
                    moveBranchesFromNorthToSouth(branches, newFileName);
                    break;
                case CSCPlatformConsolidationToolConfigBranches2BMovedDirection.South2North:
                    moveBranchesFromSouthToNorth(branches, newFileName);
                    break;
                default:
                    throw new NotImplementedException();
            }
        }
        public void deactivateSouth(int[] branches, string newConfigFileFullName)
        {
            try
            {
                ConfigStrategy.deactivateSouth(branches);
                createDirectory(newConfigFileFullName);
                ConfigStrategy.writeConfiguration(newConfigFileFullName);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Exception in deactivateSouth for File {0}", newConfigFileFullName);
                throw ex;
            }
        }

        public void deactivateNorth(int[] branches, string newConfigFileFullName)
        {
            try
            {
                ConfigStrategy.deactivateNorth(branches);
                createDirectory(newConfigFileFullName);
                ConfigStrategy.writeConfiguration(newConfigFileFullName);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Exception in deactivateNorth for File {0}", newConfigFileFullName);
                throw ex;
            }
        }

        public void deactivateCompletely(int[] branches, string newConfigFileFullName)
        {
            try
            {
                ConfigStrategy.deactivateCompletely(branches);
                createDirectory(newConfigFileFullName);
                ConfigStrategy.writeConfiguration(newConfigFileFullName);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Exception in deactivateCompletely for File {0}", newConfigFileFullName);
                throw ex;
            }
        }

        public void activateBranchesInNorth(int[] branches, string newConfigFileFullName)
        {
            try
            {
                ConfigStrategy.activateNorth(branches);
                createDirectory(newConfigFileFullName);
                ConfigStrategy.writeConfiguration(newConfigFileFullName);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Exception in activateBranchesInNorth for File {0}", newConfigFileFullName);
                throw ex;
            }
        }

        public void activateBranchesInSouth(int[] branches, string newConfigFileFullName)
        {
            try
            {
                ConfigStrategy.activateSouth(branches);
                createDirectory(newConfigFileFullName);
                ConfigStrategy.writeConfiguration(newConfigFileFullName);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Exception in activateBranchesInSouth for File {0}", newConfigFileFullName);
                throw ex;
            }
        }

        public void moveBranchesFromSouthToNorth(int[] branches, string newConfigFileFullName)
        {
            try
            {
                ConfigStrategy.moveBranchesFromSouthToNorth(branches);
                createDirectory(newConfigFileFullName);
                ConfigStrategy.writeConfiguration(newConfigFileFullName);
            }
            catch(Exception ex)
            {
                Console.WriteLine("Exception in moveBranchesFromSouthToNorth for File {0}", newConfigFileFullName);
                throw ex;
            }
        }

        private void createDirectory(string fileFullName)
        {
            FileInfo fi = new FileInfo(fileFullName);
            DirectoryInfo di = new DirectoryInfo(fi.DirectoryName);
            if (!di.Exists)
            {
                di.Create();
            }
        }
    }
}
