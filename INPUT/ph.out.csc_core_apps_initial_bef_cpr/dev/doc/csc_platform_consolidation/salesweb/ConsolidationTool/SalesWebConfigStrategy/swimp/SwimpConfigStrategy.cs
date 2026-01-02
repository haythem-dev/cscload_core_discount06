namespace SalesWebMove
{
    using System;
    using System.IO;

    public class SwimpConfigStrategy : SalesWebConfigStrategy
    {
        public override void loadConfig(string configFileFullName)
        {
            WhatAmI = "SWIMP";
            ConfigFile = configFileFullName;
            Configuration = PHOENIXUtil.XML.DeSerializeString<swimp.Phoenix.Types.Config.SalesWebConfig>(File.ReadAllText(configFileFullName));
        }

        public override void writeConfiguration(string configFileFullName)
        {
            PHOENIXUtil.XML.Serialize<swimp.Phoenix.Types.Config.SalesWebConfig>(Configuration as swimp.Phoenix.Types.Config.SalesWebConfig, configFileFullName, true);
        }


        public override void moveBranchesFromSouthToNorth(int[] branches)
        {
            var cfg = Configuration as swimp.Phoenix.Types.Config.SalesWebConfig;
            foreach (var branch in branches)
            {
                foreach (var kscsrv in cfg.Backend.KscServers)
                {
                    kscsrv.Branches = changeBranchesFromSouth2North(branches, kscsrv.Branches, kscsrv.Region);
                }
            }
            Configuration = cfg;
        }

        public override void moveBranchesFromNorthToSouth(int[] branches)
        {
            var cfg = Configuration as swimp.Phoenix.Types.Config.SalesWebConfig;
            foreach (var branch in branches)
            {
                foreach (var kscsrv in cfg.Backend.KscServers)
                {
                    kscsrv.Branches = changeBranchesFromNorth2South(branches, kscsrv.Branches, kscsrv.Region);
                }
            }
            Configuration = cfg;
        }

        public override void activateNorth(int[] branches)
        {
            var cfg = Configuration as swimp.Phoenix.Types.Config.SalesWebConfig;
            foreach( var branch in branches )
            {
                foreach( var kscsrv in cfg.Backend.KscServers )
                {
                    kscsrv.Branches = activateBranches(branches, kscsrv.Branches, AffectedBranches.North, kscsrv.Region);
                }
            }
            Configuration = cfg;
        }

        public override void activateSouth(int[] branches)
        {
            var cfg = Configuration as swimp.Phoenix.Types.Config.SalesWebConfig;
            foreach (var branch in branches)
            {
                foreach (var kscsrv in cfg.Backend.KscServers)
                {
                    kscsrv.Branches = activateBranches(branches, kscsrv.Branches, AffectedBranches.South, kscsrv.Region);
                }
            }
            Configuration = cfg;
        }

        public override void deactivateCompletely(int[] branches)
        {
            var cfg = Configuration as swimp.Phoenix.Types.Config.SalesWebConfig;
            foreach (var branch in branches)
            {
                foreach (var kscsrv in cfg.Backend.KscServers)
                {
                    kscsrv.Branches = deactivateBranches(branches, kscsrv.Branches, AffectedBranches.Everywhere, kscsrv.Region);
                }
            }
            Configuration = cfg;
        }

        public override void deactivateNorth(int[] branches)
        {
            var cfg = Configuration as swimp.Phoenix.Types.Config.SalesWebConfig;
            foreach (var branch in branches)
            {
                foreach (var kscsrv in cfg.Backend.KscServers)
                {
                    kscsrv.Branches = deactivateBranches(branches, kscsrv.Branches, AffectedBranches.North, kscsrv.Region);
                }
            }
            Configuration = cfg;
        }

        public override void deactivateSouth(int[] branches)
        {
            var cfg = Configuration as swimp.Phoenix.Types.Config.SalesWebConfig;
            foreach (var branch in branches)
            {
                foreach (var kscsrv in cfg.Backend.KscServers)
                {
                    kscsrv.Branches = deactivateBranches(branches, kscsrv.Branches, AffectedBranches.South, kscsrv.Region);
                }
            }
            Configuration = cfg;
        }
    }
}
