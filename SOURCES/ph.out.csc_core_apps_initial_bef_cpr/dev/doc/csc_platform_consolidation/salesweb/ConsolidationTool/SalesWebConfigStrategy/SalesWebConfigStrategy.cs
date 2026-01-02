namespace SalesWebMove
{
    using System;
    using System.Collections.Generic;
    using System.IO;
    using System.Text;

    public abstract class SalesWebConfigStrategy
    {
        public enum AffectedBranches { North, South, Everywhere }

        public string WhatAmI = "SalesWebConfigStrategy";

        public abstract void loadConfig(string configFileFullName);

        public abstract void activateNorth(int[] branches);
        public abstract void activateSouth(int[] branches);
        public abstract void deactivateCompletely(int[] branches);
        public abstract void deactivateNorth(int[] branches);
        public abstract void deactivateSouth(int[] branches);
        public abstract void moveBranchesFromNorthToSouth(int[] branches);
        public abstract void moveBranchesFromSouthToNorth(int[] branches);

        public abstract void writeConfiguration(string configFileFullName);

        public int[] activateBranches(int[] branchesToBeActivated, int[] branchesInConfig, AffectedBranches affected, string configRegion)
        {
            List<int> tempBranchesForConfig = new List<int>(branchesInConfig);
            foreach( var branchActivate in branchesToBeActivated )
            {
                if( !tempBranchesForConfig.Contains(branchActivate) )
                {
                    switch (affected)
                    {
                        case AffectedBranches.North:
                            if (configRegion.ToLower().Contains("north"))
                            {
                                tempBranchesForConfig.Add(branchActivate);
                            }
                            break;
                        case AffectedBranches.South:
                            if (configRegion.ToLower().Contains("south"))
                            {
                                tempBranchesForConfig.Add(branchActivate);
                            }
                            break;
                        default:
                            throw new InvalidDataException();
                    }
                }
            }
            return tempBranchesForConfig.ToArray();
        }

        public int[] deactivateBranches(int[] branchesToBeDeactivated, int[] branchesInConfig, AffectedBranches affected, string configRegion)
        {
            List<int> tempBranchesForConfig = new List<int>(branchesInConfig);
            foreach( var branchDeactivate in branchesToBeDeactivated )
            {
                switch (affected)
                {
                    case AffectedBranches.Everywhere:
                        tempBranchesForConfig.Remove(branchDeactivate);
                        break;
                    case AffectedBranches.North:
                        if (configRegion.ToLower().Contains("north"))
                        {
                            tempBranchesForConfig.Remove(branchDeactivate);
                        }
                        break;
                    case AffectedBranches.South:
                        if (configRegion.ToLower().Contains("south"))
                        {
                            tempBranchesForConfig.Remove(branchDeactivate);
                        }
                        break;
                    default:
                        throw new InvalidDataException();
                }
            }
            return tempBranchesForConfig.ToArray();
        }

        public int[] changeBranchesFromSouth2North(int[] branchesToBeMoved, int[] branchesInConfig, string configRegion)
        {
            //Console.WriteLine("South -> North / " + configRegion + " / " + serializeIntArray(branchesToBeMoved) + " / " + serializeIntArray(branchesInConfig));
            var retval = changeBranches(branchesToBeMoved, branchesInConfig, configRegion, "south", "north");
            //Console.WriteLine(WhatAmI + " South -> North: " + serializeIntArray(retval));
            return retval;
        }

        public int[] changeBranchesFromNorth2South(int[] branchesToBeMoved, int[] branchesInConfig, string configRegion)
        {
            //Console.WriteLine("North -> South / " + configRegion + " / " + serializeIntArray(branchesToBeMoved) + " / " + serializeIntArray(branchesInConfig) );
            var retval = changeBranches(branchesToBeMoved, branchesInConfig, configRegion, "north", "south");
            //Console.WriteLine(WhatAmI + " North -> South: " + serializeIntArray(retval));
            return retval;
        }

        private string serializeIntArray(int[] ints)
        {
            var sb = new StringBuilder();
            foreach( var i in ints )
            {
                sb.AppendFormat("{0} ", i);
            }
            return sb.ToString().Trim();
        }

        private int[] changeBranches(int[] branchesToBeMoved, int[] branchesInConfig, string configRegion, string regionMovedFrom, string regionMovedTo)
        {
            List<int> tempBranchesForConfig = new List<int>();
            foreach (var branchNo in branchesInConfig)
            {
                tempBranchesForConfig.Add(branchNo);
            }

            foreach (var branchForMove in branchesToBeMoved)
            {
                if (configRegion.Contains(regionMovedTo) && !tempBranchesForConfig.Contains(branchForMove))
                {
                    tempBranchesForConfig.Add(branchForMove);
                }

                if (configRegion.Contains(regionMovedFrom) && tempBranchesForConfig.Contains(branchForMove))
                {
                    tempBranchesForConfig.Remove(branchForMove);
                }
            }

            return tempBranchesForConfig.ToArray();
        }



        private string m_ConfigFile = "";
        public string ConfigFile
        {
            protected set { m_ConfigFile = value; }
            get { return m_ConfigFile; }
        }

        private object m_Configuration = null;
        public object Configuration
        {
            protected set { m_Configuration = value; }
            get { return m_Configuration; }
        }

    }
}
