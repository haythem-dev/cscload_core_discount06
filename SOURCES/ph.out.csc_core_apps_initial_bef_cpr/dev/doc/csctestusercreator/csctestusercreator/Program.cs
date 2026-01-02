using System;
using System.Collections.Generic;
using System.Text;
using IBM.Data.Informix;
using System.IO;

namespace CSCTestUserCreator
{
    class Program
    {
        #region class vars
        static List<ConnectionFactory.DBList> m_DBList = new List<ConnectionFactory.DBList>();

        static List<string> m_Usernames = new List<string>();

        static string m_DefaultPassword = "dpC}OUKQ";
        static string m_DefaultAA = "11111111111111111111111101111111111111110111011111";
        static string m_DefaultAA2 = "1111111111111111111111111111111111010000";
        static string m_TerminalID = "";

        static IfxConnection m_Connection = null;
        #endregion class vars


        static void Main()
        {
            initialize();

            #region Create Users
            foreach (var db in m_DBList)
            {
                try
                {
                    using (m_Connection = ConnectionFactory.getConnection(db))
                    {
                        m_Connection.Open(); Console.WriteLine("\nconnected to {0}", m_Connection.ConnectionString);

                        foreach(int branch in getBranches())
                        {
                            var users = getUsers(branch);
                            foreach (var user in m_Usernames)
                            {
                                if (users.Contains(user))
                                {
                                    Console.WriteLine("User {0} already available for branch {1}", user, branch);
                                    continue;
                                }

                                m_TerminalID = getNewTerminalID(branch);

                                StringBuilder sb = new StringBuilder();
                                sb = sb.Append("INSERT INTO passwd (filialnr,username,termid,password,uid,dat_anlage,aa,aa2) VALUES (");
                                sb = sb.AppendFormat("{0}", branch);
                                sb = sb.AppendFormat(", '{0}'", user);
                                sb = sb.AppendFormat(", '{0}'", m_TerminalID);
                                sb = sb.AppendFormat(", '{0}'", m_DefaultPassword);
                                sb = sb.AppendFormat(", {0}", getMaxUid());
                                sb = sb.AppendFormat(", {0}", DateTime.Now.ToString("yyyyMMdd"));
                                sb = sb.AppendFormat(", '{0}'", m_DefaultAA);
                                sb = sb.AppendFormat(", '{0}');", m_DefaultAA2);
                                Console.WriteLine(sb.ToString());

                                using (IfxCommand cmd = new IfxCommand(sb.ToString(), m_Connection))
                                {
                                    try
                                    {
                                        var result = cmd.ExecuteNonQuery();
                                    }
                                    catch(Exception ex)
                                    {
                                        Console.WriteLine("Error: {0}", ex.Message);
                                    }
                                }
                            }
                        }

                        m_Connection.Close(); Console.WriteLine("disconnected from {0}\n", m_Connection.ConnectionString);
                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine("Error: {0}", ex.Message);
                }
            }
            #endregion Create Users

            Console.WriteLine("--- Finished - Hit any key to exit ---");
            Console.ReadLine();
        }

        #region utilities

        static void initialize()
        {
            initializeDBList();
            initializeUserList();
        }

        static void initializeUserList()
        {
            m_Usernames.Clear();
            foreach( var user in File.ReadAllLines("Users.txt"))
            {
                var userName = user.Trim();
                if (userName.Length == 0) continue;
                if (userName.Length > 8)
                {
                    Console.WriteLine("Username {0} is invalid. Max. length for username is 8 characters!", userName);
                    continue;
                }
                m_Usernames.Add(userName);
                Console.WriteLine("Added username {0}", userName);
            }
        }

        static void initializeDBList()
        {
            m_DBList.Clear();
            foreach( var db in File.ReadAllLines("Databases.txt") )
            {
                var dbname = db.Trim().ToLower();
                switch(dbname)
                {
                    case "oat21":
                        m_DBList.Add(ConnectionFactory.DBList.oat21);
                        Console.WriteLine("added database {0}", dbname);
                        break;
                    case "oat21pre":
                        m_DBList.Add(ConnectionFactory.DBList.oat21pre);
                        Console.WriteLine("added database {0}", dbname);
                        break;
                    case "obg21":
                        m_DBList.Add(ConnectionFactory.DBList.obg21);
                        Console.WriteLine("added database {0}", dbname);
                        break;
                    case "och21":
                        m_DBList.Add(ConnectionFactory.DBList.och21);
                        Console.WriteLine("added database {0}", dbname);
                        break;
                    case "och21pre":
                        m_DBList.Add(ConnectionFactory.DBList.och21pre);
                        Console.WriteLine("added database {0}", dbname);
                        break;
                    case "ode21":
                        m_DBList.Add(ConnectionFactory.DBList.ode21);
                        Console.WriteLine("added database {0}", dbname);
                        break;
                    case "ode22":
                        m_DBList.Add(ConnectionFactory.DBList.ode22);
                        Console.WriteLine("added database {0}", dbname);
                        break;
                    case "ofr21":
                        m_DBList.Add(ConnectionFactory.DBList.ofr21);
                        Console.WriteLine("added database {0}", dbname);
                        break;
                    case "ofr21pre":
                        m_DBList.Add(ConnectionFactory.DBList.ofr21pre);
                        Console.WriteLine("added database {0}", dbname);
                        break;
                    case "ohr21":
                        m_DBList.Add(ConnectionFactory.DBList.ohr21);
                        Console.WriteLine("added database {0}", dbname);
                        break;
                    case "ors21":
                        m_DBList.Add(ConnectionFactory.DBList.ors21);
                        Console.WriteLine("added database {0}", dbname);
                        break;
                    default:
                        break;
                }
            }
        }

        static int getMaxUid()
        {
            int retval = 0;
            string query = "select CAST(max(uid)+1 as integer) from passwd;";
            using (IfxCommand cmd = new IfxCommand(query, m_Connection))
            {
                using (IfxDataReader rdr = cmd.ExecuteReader())
                {
                    while (rdr.Read())
                    {
                        retval = rdr.GetInt32(0);
                    }
                    rdr.Close();
                }
            }
            return retval;
        }

        static string getNewTerminalID(int branch)
        {
            string retval = branch.ToString("").PadLeft(2, '0');
            string txt = Guid.NewGuid().ToString().ToUpper().Substring(0, 2);
            while(isTerminalIDAlreadyThere(txt))
            {
                txt = Guid.NewGuid().ToString().ToUpper().Substring(0, 2);
            }
            retval += txt;
            return retval;
        }

        static bool isTerminalIDAlreadyThere(string terminalid)
        {
            bool retval = false;
            string query = String.Format("select CAST(count(*) as integer) from passwd where termid='{0}'", terminalid);
            using (IfxCommand cmd = new IfxCommand(query, m_Connection))
            {
                using (IfxDataReader rdr = cmd.ExecuteReader())
                {
                    while (rdr.Read())
                    {
                        if (rdr.GetInt32(0) > 0)
                        {
                            retval = true;
                        }
                    }
                    rdr.Close();
                }
            }
            return retval;
        }

        static List<int> getBranches()
        {
            List<int> retval = new List<int>();
            string query = "select distinct filialnr from rechner where datenbank_name like '%_shm' and filialnr>0 order by filialnr;";
            using (IfxCommand cmd = new IfxCommand(query, m_Connection))
            {
                using (IfxDataReader rdr = cmd.ExecuteReader())
                {
                    while(rdr.Read())
                    {
                        retval.Add(rdr.GetInt16(0));
                    }
                    rdr.Close();
                }
            }
            return retval;
        }

        static List<string> getUsers(int branchNo)
        {
            List<string> retval = new List<string>();
            string query = String.Format("select distinct username from passwd where filialnr={0};", branchNo);
            using (IfxCommand cmd = new IfxCommand(query, m_Connection))
            {
                using (IfxDataReader rdr = cmd.ExecuteReader())
                {
                    while (rdr.Read())
                    {
                        retval.Add(rdr.GetString(0).Trim());
                    }
                    rdr.Close();
                }
            }
            return retval;
        }

        #endregion utilities
    }
}