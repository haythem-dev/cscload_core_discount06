using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSCServiceNClientBasics
{
    public class Customer
    {
        public short BranchNo = 0;
        public int CustomerNo = 0;

        public Customer(short branch, int idf)
        {
            BranchNo = branch;
            CustomerNo = idf;
        }
    }

    partial class Program
    {
        static object lockableObject = new object();

        #region Customer Queue

        static Queue<Customer> _CustomerQueue = null;

        static Customer getCustomer()
        {
            if (null == _CustomerQueue)
            {
                initializeCustomerQueue();
            }

            if (0 == _CustomerQueue.Count)
            {
                lock(lockableObject)
                {
                    initializeCustomerQueue();
                    if( 0 == _CustomerQueue.Count)
                    {
                        throw new Exception("No Customers available!");
                    }
                }

            }
            return _CustomerQueue.Dequeue();
        }

        static void initializeCustomerQueue()
        {
            // Create Queue if not available
            if (null == _CustomerQueue)
            {
                _CustomerQueue = new Queue<Customer>();
            }
            // Refill Queue if empty
            if (0 == _CustomerQueue.Count)
            {
                foreach (var line in File.ReadAllLines("customers.txt"))
                {
                    var data = line.Split(';');
                    if( 2 == data.Length )
                    {
                        _CustomerQueue.Enqueue(new Customer(Convert.ToInt16(data[0]), Convert.ToInt32(data[1])));
                    }
                }
            }
        }

        #endregion Customer Queue

        #region BTM Artikel

        static Queue<string> _BTMQueue = null;
        static string getBTMArticleCode()
        {
            // Create Queue if not available
            if (null == _BTMQueue)
            {
                _BTMQueue = new Queue<string>();
            }
            // Refill Queue if empty
            if (0 == _BTMQueue.Count)
            {
                lock(lockableObject)
                {
                    initializeBTMQueue();
                    if (0 == _BTMQueue.Count)
                    {
                        throw new Exception("No BTM Articles available!");
                    }
                }
            }
            return _BTMQueue.Dequeue();
        }

        static void initializeBTMQueue()
        {
            // Create Queue if not available
            if (null == _BTMQueue)
            {
                _BTMQueue = new Queue<string>();
            }
            // Refill Queue if empty
            if (0 == _BTMQueue.Count)
            {
                foreach (var line in File.ReadAllLines("btms.txt"))
                {
                    _BTMQueue.Enqueue(line.Trim());
                }
            }
        }

        #endregion BTM Artikel

        #region Normale Artikel

        static Queue<string> _PZNQueue = null;

        static string getPZNArticleCode()
        {
            /*
            select c.article_code
            from artikelzentral z
            join articlecodes c on c.articleno=z.artikel_nr and c.code_type=16
            join artikellokal l on l.artikel_nr=z.artikel_nr and l.filialnr=51
            where trunc(z.etartklasse1 / 512) - 2 * trunc(z.etartklasse1 / (512*2))=0
            and l.bestand>2 and l.artikelaktiv='1'
            */
            // Create Queue if not available
            if (null == _PZNQueue)
            {
                _PZNQueue = new Queue<string>();
            }
            // Refill Queue if empty
            if (0 == _PZNQueue.Count)
            {
                lock (lockableObject)
                {
                    if (0 == _PZNQueue.Count)
                    {
                        initializePZNQueue();
                        if (0 == _PZNQueue.Count)
                        {
                            throw new Exception("No Articles available");
                        }
                    }
                }
            }
            return _PZNQueue.Dequeue();
        }

        static void initializePZNQueue()
        {
            // Create Queue if not available
            if (null == _PZNQueue)
            {
                _PZNQueue = new Queue<string>();
            }
            // Refill Queue if empty
            if (0 == _PZNQueue.Count)
            {
                foreach (var line in File.ReadAllLines("normals.txt"))
                {
                    _PZNQueue.Enqueue(line.Trim());
                }
            }
        }

        #endregion Normale Artikel
    }
}
