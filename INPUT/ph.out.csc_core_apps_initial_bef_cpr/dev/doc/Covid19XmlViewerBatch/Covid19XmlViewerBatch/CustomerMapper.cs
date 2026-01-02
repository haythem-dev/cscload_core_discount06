using System;
using System.IO;

namespace Covid19XmlViewerBatch
{
    public class CustomerMapper
    {
        public string CustomerID { get; private set; }

        private int BranchNo = 0;
        public int Branch { get { return BranchNo; } }

        private int CustomerNo = 0;
        public int Customer { get { return CustomerNo; } }

        public void MapCustomer(string customerid, string customerMappingFile = "CustomerMapping.csv")
        {
            CustomerID = customerid.Trim();
            foreach(string line in File.ReadAllLines(customerMappingFile) )
            {
                string[] fields = line.Split(';');
                if( fields[0].Trim() == CustomerID )
                {
                    int.TryParse(fields[1], out BranchNo);
                    int.TryParse(fields[2], out CustomerNo);
                    break;
                }
            }
        }
    }
}
