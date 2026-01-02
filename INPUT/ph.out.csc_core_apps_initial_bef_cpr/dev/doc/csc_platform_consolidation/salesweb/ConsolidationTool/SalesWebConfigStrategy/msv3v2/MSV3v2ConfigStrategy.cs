namespace SalesWebMove
{
    using System;
    using System.IO;

    public class MSV3v2ConfigStrategy : SalesWebConfigStrategy
    {
        public override void loadConfig(string configFileFullName)
        {
            WhatAmI = "MSV3v2";
            ConfigFile = configFileFullName;
            Configuration = PHOENIXUtil.XML.DeSerializeString<msv3v2.Phoenix.Types.Config.SalesWebConfig>(File.ReadAllText(configFileFullName));
        }

        public override void writeConfiguration(string configFileFullName)
        {
            PHOENIXUtil.XML.Serialize<msv3v2.Phoenix.Types.Config.SalesWebConfig>(
                Configuration as msv3v2.Phoenix.Types.Config.SalesWebConfig, configFileFullName, true);
        }

        public override void moveBranchesFromSouthToNorth(int[] branches)
        {
            var cfg = Configuration as msv3v2.Phoenix.Types.Config.SalesWebConfig;
            foreach (var branch in branches)
            {
                foreach (var cscsrv in cfg.Backend.CSCServices)
                {
                    cscsrv.Branches = changeBranchesFromSouth2North(branches, cscsrv.Branches, cscsrv.Region);
                }
            }
            Configuration = cfg;
        }

        public override void moveBranchesFromNorthToSouth(int[] branches)
        {
            var cfg = Configuration as msv3v2.Phoenix.Types.Config.SalesWebConfig;
            foreach (var branch in branches)
            {
                foreach (var cscsrv in cfg.Backend.CSCServices)
                {
                    cscsrv.Branches = changeBranchesFromNorth2South(branches, cscsrv.Branches, cscsrv.Region);
                }
            }
            Configuration = cfg;
        }

        public override void activateNorth(int[] branches)
        {
            var cfg = Configuration as msv3v2.Phoenix.Types.Config.SalesWebConfig;
            foreach (var branch in branches)
            {
                foreach (var kscsrv in cfg.Backend.CSCServices)
                {
                    kscsrv.Branches = activateBranches(branches, kscsrv.Branches, AffectedBranches.North, kscsrv.Region);
                }
            }
            Configuration = cfg;
        }

        public override void activateSouth(int[] branches)
        {
            var cfg = Configuration as msv3v2.Phoenix.Types.Config.SalesWebConfig;
            foreach (var branch in branches)
            {
                foreach (var kscsrv in cfg.Backend.CSCServices)
                {
                    kscsrv.Branches = activateBranches(branches, kscsrv.Branches, AffectedBranches.South, kscsrv.Region);
                }
            }
            Configuration = cfg;
        }

        public override void deactivateCompletely(int[] branches)
        {
            var cfg = Configuration as msv3v2.Phoenix.Types.Config.SalesWebConfig;
            foreach (var branch in branches)
            {
                foreach (var kscsrv in cfg.Backend.CSCServices)
                {
                    kscsrv.Branches = deactivateBranches(branches, kscsrv.Branches, AffectedBranches.Everywhere, kscsrv.Region);
                }
            }
            Configuration = cfg;
        }

        public override void deactivateNorth(int[] branches)
        {
            var cfg = Configuration as msv3v2.Phoenix.Types.Config.SalesWebConfig;
            foreach (var branch in branches)
            {
                foreach (var kscsrv in cfg.Backend.CSCServices)
                {
                    kscsrv.Branches = deactivateBranches(branches, kscsrv.Branches, AffectedBranches.North, kscsrv.Region);
                }
            }
            Configuration = cfg;
        }

        public override void deactivateSouth(int[] branches)
        {
            var cfg = Configuration as msv3v2.Phoenix.Types.Config.SalesWebConfig;
            foreach (var branch in branches)
            {
                foreach (var kscsrv in cfg.Backend.CSCServices)
                {
                    kscsrv.Branches = deactivateBranches(branches, kscsrv.Branches, AffectedBranches.South, kscsrv.Region);
                }
            }
            Configuration = cfg;
        }
    }
}
