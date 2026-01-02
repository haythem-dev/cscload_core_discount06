using IBM.Data.Informix;

namespace CSCTestUserCreator
{
    class ConnectionFactory
    {
        public enum DBList
        {
            oat21,
            oat21pre,
            obg21,
            och21,
            och21pre,
            ode21,
            ode22,
            ofr21,
            ofr21pre,
            ohr21,
            ors21,
        }
        public static IfxConnection getConnection(ConnectionFactory.DBList db)
        {
            switch (db)
            {
                case DBList.oat21:      return getOAT21();
                case DBList.oat21pre:   return getOAT21Pre();
                case DBList.obg21:      return getOBG21();
                case DBList.och21:      return getOCH21();
                case DBList.och21pre:   return getOCH21Pre();
                case DBList.ode21:      return getODE21();
                case DBList.ode22:      return getODE22();
                case DBList.ofr21:      return getOFR21();
                case DBList.ofr21pre:   return getOFR21Pre();
                case DBList.ohr21:      return getOHR21();
                case DBList.ors21:      return getORS21();
            }
            return null;
        }

        private static IfxConnection getOAT21()
        {
            IfxConnectionStringBuilder cstrbldr = new IfxConnectionStringBuilder();
            cstrbldr.Database = "oat21";
            cstrbldr.Host = "zdev21";
            cstrbldr.Pwd = "phosix+";
            cstrbldr.Server = "zdev21_tcp";
            cstrbldr.Service = "53004";
            cstrbldr.UID = "devuser";
            return new IfxConnection(cstrbldr.ConnectionString);
        }

        private static IfxConnection getOAT21Pre()
        {
            IfxConnectionStringBuilder cstrbldr = new IfxConnectionStringBuilder();
            cstrbldr.Database = "oat21pre";
            cstrbldr.Host = "zdev21";
            cstrbldr.Pwd = "phosix+";
            cstrbldr.Server = "zdev21_tcp";
            cstrbldr.Service = "53004";
            cstrbldr.UID = "devuser";
            return new IfxConnection(cstrbldr.ConnectionString);
        }

        private static IfxConnection getOBG21()
        {
            IfxConnectionStringBuilder cstrbldr = new IfxConnectionStringBuilder();
            cstrbldr.Database = "obg21";
            cstrbldr.Host = "zdev21";
            cstrbldr.Pwd = "phosix+";
            cstrbldr.Server = "zdev21_tcp";
            cstrbldr.Service = "53004";
            cstrbldr.UID = "devuser";
            cstrbldr.ClientLocale = "bg_bg.1251";
            cstrbldr.DbLocale = "bg_bg.915";
            return new IfxConnection(cstrbldr.ConnectionString);
        }

        private static IfxConnection getOCH21()
        {
            IfxConnectionStringBuilder cstrbldr = new IfxConnectionStringBuilder();
            cstrbldr.Database = "och21";
            cstrbldr.Host = "zdev21";
            cstrbldr.Pwd = "phosix+";
            cstrbldr.Server = "zdev21_tcp";
            cstrbldr.Service = "53004";
            cstrbldr.UID = "devuser";
            return new IfxConnection(cstrbldr.ConnectionString);
        }

        private static IfxConnection getOCH21Pre()
        {
            IfxConnectionStringBuilder cstrbldr = new IfxConnectionStringBuilder();
            cstrbldr.Database = "och21pre";
            cstrbldr.Host = "zdev21";
            cstrbldr.Pwd = "phosix+";
            cstrbldr.Server = "zdev21_tcp";
            cstrbldr.Service = "53004";
            cstrbldr.UID = "devuser";
            return new IfxConnection(cstrbldr.ConnectionString);
        }

        private static IfxConnection getODE21()
        {
            IfxConnectionStringBuilder cstrbldr = new IfxConnectionStringBuilder();
            cstrbldr.Database = "ode21";
            cstrbldr.Host = "zdev21";
            cstrbldr.Pwd = "phosix+";
            cstrbldr.Server = "zdev21_tcp";
            cstrbldr.Service = "53004";
            cstrbldr.UID = "devuser";
            return new IfxConnection(cstrbldr.ConnectionString);
        }

        private static IfxConnection getODE22()
        {
            IfxConnectionStringBuilder cstrbldr = new IfxConnectionStringBuilder();
            cstrbldr.Database = "ode22";
            cstrbldr.Host = "zdev21";
            cstrbldr.Pwd = "phosix+";
            cstrbldr.Server = "zdev21_tcp";
            cstrbldr.Service = "53004";
            cstrbldr.UID = "devuser";
            return new IfxConnection(cstrbldr.ConnectionString);
        }

        private static IfxConnection getOFR21()
        {
            IfxConnectionStringBuilder cstrbldr = new IfxConnectionStringBuilder();
            cstrbldr.Database = "ofr21";
            cstrbldr.Host = "zdev21";
            cstrbldr.Pwd = "phosix+";
            cstrbldr.Server = "zdev21_tcp";
            cstrbldr.Service = "53004";
            cstrbldr.UID = "devuser";
            return new IfxConnection(cstrbldr.ConnectionString);
        }

        private static IfxConnection getOFR21Pre()
        {
            IfxConnectionStringBuilder cstrbldr = new IfxConnectionStringBuilder();
            cstrbldr.Database = "ofr21pre";
            cstrbldr.Host = "zdev21";
            cstrbldr.Pwd = "phosix+";
            cstrbldr.Server = "zdev21_tcp";
            cstrbldr.Service = "53004";
            cstrbldr.UID = "devuser";
            return new IfxConnection(cstrbldr.ConnectionString);
        }

        private static IfxConnection getOHR21()
        {
            IfxConnectionStringBuilder cstrbldr = new IfxConnectionStringBuilder();
            cstrbldr.Database = "ohr21";
            cstrbldr.Host = "zdev21";
            cstrbldr.Pwd = "phosix+";
            cstrbldr.Server = "zdev21_tcp";
            cstrbldr.Service = "53004";
            cstrbldr.UID = "devuser";
            return new IfxConnection(cstrbldr.ConnectionString);
        }

        private static IfxConnection getORS21()
        {
            IfxConnectionStringBuilder cstrbldr = new IfxConnectionStringBuilder();
            cstrbldr.Database = "ors21";
            cstrbldr.Host = "zdev21";
            cstrbldr.Pwd = "phosix+";
            cstrbldr.Server = "zdev21_tcp";
            cstrbldr.Service = "53004";
            cstrbldr.UID = "devuser";
            return new IfxConnection(cstrbldr.ConnectionString);
        }
    }
}
