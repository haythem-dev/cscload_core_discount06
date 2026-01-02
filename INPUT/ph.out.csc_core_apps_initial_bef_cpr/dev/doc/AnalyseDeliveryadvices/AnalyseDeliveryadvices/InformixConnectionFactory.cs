using IBM.Data.Informix;
using System.Linq;
using System.Text;

namespace AnalyseDeliveryadvices
{
    static class InformixConnectionFactory
    {
        #region default values
        private static string m_Port = "53004";
        private static string m_Username = "produser";
        private static string m_Password = "redR8-Wo3";
        #endregion default values

        #region branch lists
        public static int[] AustriaBranches = new int[] { 61, 62, 63, 64 };
        public static int[] GermanBranches = new int[] { 5, 6, 8, 9, 21, 31, 33, 40, 44, 46, 51, 52, 54, 56, 57, 58, 59, 70, 78, 81, 82 };
        public static int[] SwissBranches = new int[] { 12, 13 };
        #endregion

        public enum DBType { Outbound, Warehouse }
        private static IfxConnectionStringBuilder GetConnectionStringWithDefaults( string db )
        {
            IfxConnectionStringBuilder cstrBldr = new IfxConnectionStringBuilder();
            cstrBldr.Pwd = m_Password;
            cstrBldr.UID = m_Username;
            cstrBldr.Service = m_Port;
            cstrBldr.Database = db;
            cstrBldr.Host = db + ".phoenix.loc";
            cstrBldr.Server = db + "_tcp";
            return cstrBldr;
        }
        public static IfxConnection GetOutboundAustria()
        {
            return new IfxConnection(GetConnectionStringWithDefaults("oat21").ConnectionString);
        }
        public static IfxConnection GetOutboundGermany()
        {
            return new IfxConnection(GetConnectionStringWithDefaults("ode21").ConnectionString);
        }
        public static IfxConnection GetOutboundSwitzerland()
        {
            return new IfxConnection(GetConnectionStringWithDefaults("och21").ConnectionString);
        }
        public static IfxConnection GetWarehouseAustria()
        {
            return new IfxConnection(GetConnectionStringWithDefaults("wat21").ConnectionString);
        }
        public static IfxConnection GetWarehouseGermany()
        {
            return new IfxConnection(GetConnectionStringWithDefaults("wde21").ConnectionString);
        }
        public static IfxConnection GetWarehouseSwitzerland()
        {
            return new IfxConnection(GetConnectionStringWithDefaults("wch21").ConnectionString);
        }
        public static void SwitchToDirtyRead(IfxConnection c)
        {
            using (IfxCommand cmd = new IfxCommand("SET ISOLATION TO DIRTY READ;", c))
            {
                cmd.ExecuteNonQuery();
            }
        }
        public static string AnalyseDataReaderItem(IfxDataReader rdr)
        {
            StringBuilder sb = new StringBuilder();
            for( int i = 0; i < rdr.FieldCount; ++i )
            {
                sb = sb.AppendFormat("{0} | {1} | {2}\n", rdr.GetName(i), rdr[i].GetType(), rdr.GetValue(i));
            }
            return sb.ToString();
        }
        public static IfxConnection GetIfxConnectionByBranch(int branchNo, DBType dbType)
        {
            if (InformixConnectionFactory.AustriaBranches.Contains<int>(branchNo))
            {
                switch (dbType)
                {
                    case DBType.Outbound:
                        return InformixConnectionFactory.GetOutboundAustria();
                    case DBType.Warehouse:
                        return InformixConnectionFactory.GetWarehouseAustria();
                }
            }

            if (InformixConnectionFactory.GermanBranches.Contains<int>(branchNo))
            {
                switch (dbType)
                {
                    case DBType.Outbound:
                        return InformixConnectionFactory.GetOutboundGermany();
                    case DBType.Warehouse:
                        return InformixConnectionFactory.GetWarehouseGermany();
                }
            }

            if (InformixConnectionFactory.SwissBranches.Contains<int>(branchNo))
            {
                switch (dbType)
                {
                    case DBType.Outbound:
                        return InformixConnectionFactory.GetOutboundSwitzerland();
                    case DBType.Warehouse:
                        return InformixConnectionFactory.GetWarehouseSwitzerland();
                }
            }

            return null;
        }

    }
}
