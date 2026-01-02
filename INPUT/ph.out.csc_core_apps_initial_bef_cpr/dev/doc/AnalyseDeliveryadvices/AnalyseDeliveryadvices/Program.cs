using IBM.Data.Informix;
using System;
using System.Collections.Generic;
using System.IO;
using System.Threading.Tasks;

namespace AnalyseDeliveryadvices
{
    class Program
    {
        static void Main(string[] args)
        {
            int dateToCheck = 0;
            while (dateToCheck == 0)
            {
                Console.WriteLine("Welches Datum soll ausgewertet werden? (\"JHJJMMTT\"): ");
                string userInput = Console.ReadLine();
                if (!int.TryParse(userInput.Trim(), out dateToCheck))
                {
                    Console.WriteLine("Bitte im Format JHJJMMTT eingeben!");
                    dateToCheck = 0;
                }
            }


            bool completed = false;

            List<string> filesWritten = new List<string>();
            List<int> Branches2BChecked = new List<int>();

            #region Branches
            //////////////////////////////////////
            // Austria Branches:
            //////////////////////////////////////
            Branches2BChecked.Add(61);
            Branches2BChecked.Add(62);
            Branches2BChecked.Add(63);
            Branches2BChecked.Add(64);
            //////////////////////////////////////
            // Swiss Branches:
            //////////////////////////////////////
            Branches2BChecked.Add(12);
            Branches2BChecked.Add(13);
            //////////////////////////////////////
            // German Branches:
            //////////////////////////////////////
            Branches2BChecked.Add(5);
            Branches2BChecked.Add(6);
            Branches2BChecked.Add(8);
            Branches2BChecked.Add(9);
            Branches2BChecked.Add(21);
            Branches2BChecked.Add(31);
            Branches2BChecked.Add(33);
            Branches2BChecked.Add(40);
            Branches2BChecked.Add(44);
            Branches2BChecked.Add(46);
            Branches2BChecked.Add(51);
            Branches2BChecked.Add(52);
            Branches2BChecked.Add(54);
            Branches2BChecked.Add(56);
            Branches2BChecked.Add(57);
            Branches2BChecked.Add(58);
            Branches2BChecked.Add(59);
            Branches2BChecked.Add(70);
            Branches2BChecked.Add(78);
            Branches2BChecked.Add(81);
            Branches2BChecked.Add(82);
            #endregion


            Parallel.ForEach(Branches2BChecked, (branchToCheck, state, index) =>
            {
                string file = String.Format("out-{0}.csv", branchToCheck);
                filesWritten.Add(file);
                if (File.Exists(file)) File.Delete(file);
                File.AppendAllLines(file, new string[] { DeliveryAdvice.DataHeader() });

                using (IfxConnection outbound = InformixConnectionFactory.GetIfxConnectionByBranch(branchToCheck, InformixConnectionFactory.DBType.Outbound))
                {
                    outbound.Open();
                    InformixConnectionFactory.SwitchToDirtyRead(outbound);

                    using (IfxConnection warehouse = InformixConnectionFactory.GetIfxConnectionByBranch(branchToCheck, InformixConnectionFactory.DBType.Warehouse))
                    {
                        warehouse.Open();
                        InformixConnectionFactory.SwitchToDirtyRead(warehouse);
                        List<DeliveryAdvice> deliveryAdvices = DeliveryAdviceDataReader.GetDeliveryAdvices(dateToCheck, warehouse, completed);
                        foreach (DeliveryAdvice deliveryAdvice in deliveryAdvices)
                        {
                            if (deliveryAdvice.BranchNo == branchToCheck)
                            {
                                DeliveryAdviceDataReader.DetermineDetails(deliveryAdvice, warehouse, outbound);
                                File.AppendAllLines(file, new string[] { deliveryAdvice.ToData() });
                            }
                        }
                        warehouse.Close();
                    }
                    outbound.Close();
                }
            });

            if (File.Exists("data.csv")) File.Delete("data.csv");
            foreach(var file in filesWritten)
            {
                File.AppendAllText("data.csv", File.ReadAllText(file));
                File.Delete(file);
            }
        }
    }
}
