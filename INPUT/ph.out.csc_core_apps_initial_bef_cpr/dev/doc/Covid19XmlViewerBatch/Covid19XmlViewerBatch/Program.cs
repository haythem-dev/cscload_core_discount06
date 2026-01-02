using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace Covid19XmlViewerBatch
{
    partial class Program
    {
        #region vars   
        static readonly string DownloadDirectory = "xmlDownload";
        static readonly string CsvDirectory = "csvData";
        static readonly string Logfile = "covid19xmlviewerbatch.log";

        static Logger Log = null;
        static int AlreadyOnDisk = 0;
        static int Downloaded = 0;        
        static List<string> NewXmlFiles = new List<string>();
        #endregion vars

        // Scheduled on denu00dt0105.phoenix.loc (Aufgabenplanung)
        // KSC-Report:          \\denu00dt0105\C$\Schedules\Covid19AT\Covid19XmlViewerBatch_KSC
        // Vertriebs-Report:    \\denu00dt0105\C$\Schedules\Covid19AT\Covid19XmlViewerBatch_Vertrieb

        static void Main(string[] args)
        {
            try
            {
                Initialize();
                GetNewFilesFromFtp();
                GenerateCSVFile();
                Log.Log("Program finished", Logger.LogType.Info);
            }
            catch(Exception ex)
            {
                Console.WriteLine($"{ex.Message}. {ex.InnerException?.Message}");
            }            
        }

        /// <summary>
        /// Download new XML files from BBG FTP server
        /// </summary>
        static void GetNewFilesFromFtp()
        {
            Log.Log($"@ @ @ @ @ @ @ @ @ @   GetNewFilesFromFtp   @ @ @ @ @ @ @ @ @ @");            
            using (var client = new Renci.SshNet.SftpClient("pictureserver.e-shop.gv.at", 8022, "psuser.109252", "30a49bb5"))
            {
                client.Connect();
                Log.Log($"Connected to SFTP Server {client.ConnectionInfo.Host}:{client.ConnectionInfo.Port} as {client.ConnectionInfo.Username}");
                foreach (var entry in client.ListDirectory("prod/out/order"))
                {
                    if (!entry.IsDirectory)
                    {
                        string DownloadFile = $"{DownloadDirectory}/{entry.Name}";
                        if (!File.Exists(DownloadFile)) // check if XML file from FTP is already available on the local disc...
                        {
                            // if the XML file is not available on the local disc... download it
                            Log.Log($"{entry.FullName} - ");
                            using (FileStream fs = new FileStream(DownloadFile, FileMode.Create)) 
                            {
                                Log.Log("Downloading...");
                                client.DownloadFile(entry.FullName, fs);
                                Log.Log("...done.");
                                ++Downloaded;
                                NewXmlFiles.Add(DownloadFile); // add name of new XML files in list of new XML files...
                            }
                        }
                        else
                        {                            
                            ++AlreadyOnDisk;
                        }
                    }
                }
                client.Disconnect();
            }
            Log.Log($"Files found {Downloaded + AlreadyOnDisk} - {Downloaded} new file(s) downloaded.");            
        }

        static void GenerateCSVFile()
        {
            bool AddBuyerPartyData = false;
            bool AddSellerPartyData = false;
            bool AddShipToPartyData = false;
            bool AddBillToPartyData = false;

            Log.Log($"@ @ @ @ @ @ @ @ @ @   GenerateCSVFile   @ @ @ @ @ @ @ @ @ @");
            
            string OutputFile = $"{CsvDirectory}/{DateTime.Now.ToString("yyyy.MM.dd_HHmmss")}-out.csv";
            int y = 1;
            while (File.Exists(OutputFile))
            {
                OutputFile = $"{CsvDirectory}/{DateTime.Now.ToString("yyyy.MM.dd_HHmmss")}-{y}-out.csv";
                ++y;
            }

            StringBuilder output = new StringBuilder();
            output.Clear();
            output.Append($"Geschaeftszahl;");
            output.Append($"bestellnummer;");
            output.Append($"aufnahmedatum;");
            output.Append($"anlieferung;");            
            output.Append($"einrichtung;");
            output.Append($"vails;");
            output.Append($"produkt;");            
            output.Append($"PZN;");            
            output.Append($"plz;");
            output.Append($"ort;");            
            output.Append($"xmldatei;");

            PartyShipTo.AddLieferadresseColumnTitles(ref output);

            if (AddShipToPartyData)
            {
                PartyShipTo.AddLieferadresseTitle(ref output);
                PartyShipTo.AddTitles(ref output);
            }
            if (AddBuyerPartyData)
            {
                PartyBuyer.AddKaeuferTitle(ref output);
                PartyBuyer.AddTitles(ref output);
            }
            if (AddBillToPartyData)
            {
                PartyBillTo.AddPartnerTitle(ref output);
                PartyBillTo.AddRechnungsadresseTitle(ref output);
                PartyBillTo.AddTitles(ref output);
            }
            if (AddSellerPartyData) { PartySeller.AddTitles(ref output); }

            //output.Append($"Positionsnr.;");            
            output.Append($"zubehoer;");

            output.AppendLine();
            File.AppendAllText(OutputFile, output.ToString(), Encoding.UTF8);

            int filesProcessed = 0;

            int VACFiles = 0;
            int OtherFiles = 0;

            foreach (string file in NewXmlFiles)
            {
                ++filesProcessed;
                FileInfo fi = new FileInfo(file);
                try
                {
                    string content = File.ReadAllText(fi.FullName);

                    content = content.Replace("<Order>",
                    "<Order xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"rrn:org.xcbl:schemas/xcbl/v3_5/xcbl35.xsd xsdcblsingleroot35r1/Order.xsd\" xmlns= \"rrn:org.xcbl:schemas/xcbl/v3_5/xcbl35.xsd\">");

                    content = content.Replace("<ListOfNameValueSet/>", "<ListOfNameValueSet><NameValueSet><SetName>String</SetName><ListOfNameValuePair><NameValuePair><Name>String</Name><Value>String</Value></NameValuePair></ListOfNameValuePair></NameValueSet></ListOfNameValueSet>");

                    content = content.Replace("<TaxPercent/>", "<TaxPercent>0.00</TaxPercent>");


                    Order order = XML.DeSerializeString<Order>(content);

                    string kundenid = order.OrderHeader.OrderParty.ShipToParty.Party.NameAddress.Identifier.Ident;

                    CustomerMapper cm = new CustomerMapper();
                    cm.MapCustomer(kundenid);

                    string branchNo = $"{cm.Branch}";
                    string customerNo = $"{cm.Customer}";


                    string bestellnummerbbg = order.OrderHeader.OrderNumber.BuyerOrderNumber;
                    string aufnahmedatum = $"{order.OrderHeader.OrderIssueDate.Substring(6, 2)}.{order.OrderHeader.OrderIssueDate.Substring(4, 2)}.{order.OrderHeader.OrderIssueDate.Substring(0, 4)}";
                    string einrichtung = order.OrderHeader.OrderParty.ShipToParty.Party.NameAddress.Name1;
                    string vails = "";
                    string anlieferung = "";
                    string productid = "";
                    string produkt = "";
                    string strasse = "";
                    string plz = "";
                    string ort = "";
                    string ansprechpartner = "";
                    string telefon = "";
                    string email = "";
                    string Geschaeftszahl = "";
                    string zubehoer = "";
                    //string positionsnummer = "";

                    // check if it´s an COVID relevant XML file...

                    foreach( Contract c in order.OrderHeader.OrderReferences.ContractReferences.ListOfContract )
                    {
                        Geschaeftszahl = c.ContractID.Identifier.Ident;                        
                    }

                    if( !Geschaeftszahl.StartsWith( "VAC" ) )
                    {
                        ++OtherFiles;
                        Log.Log($"File {fi.Name}: File nicht relevant! Geschäftszahl '{Geschaeftszahl}' beginnt nicht mit 'VAC'");
                        continue;
                    }
                    ++VACFiles;

                    PartyShipTo.DetermineValues(order.OrderHeader.OrderParty.ShipToParty, fi.Name, ref Log); 
                    PartyBuyer.DetermineValues(order.OrderHeader.OrderParty.BuyerParty, fi.Name, ref Log); 
                    PartyBillTo.DetermineValues(order.OrderHeader.OrderParty.BillToParty, fi.Name, ref Log); 
                    PartySeller.DetermineValues(order.OrderHeader.OrderParty.SellerParty, fi.Name, ref Log);                    

                    foreach (ItemDetail item in order.OrderDetail.ListOfItemDetail)
                    {
                        #region item details
                        try { einrichtung = item.BaseItemDetail.FinalRecipient.Party.NameAddress.Name1; }
                        catch { Log.Log($"File {fi.Name}: Fehler beim ermitteln von {nameof(einrichtung)}"); }

                        try { productid = item.BaseItemDetail.ItemIdentifiers.PartNumbers.SellerPartNumber.PartNum.PartID; }
                        catch { Log.Log($"File {fi.Name}: Fehler beim ermitteln von {nameof(productid)}"); }

                        try { produkt = item.BaseItemDetail.ItemIdentifiers.ItemDescription; }
                        catch { Log.Log($"File {fi.Name}: Fehler beim ermitteln von {nameof(produkt)}"); }

                        try { strasse = item.BaseItemDetail.FinalRecipient.Party.NameAddress.Street; }
                        catch { Log.Log($"File {fi.Name}: Fehler beim ermitteln von {nameof(strasse)}"); }

                        try { plz = item.BaseItemDetail.FinalRecipient.Party.NameAddress.PostalCode; }
                        catch { Log.Log($"File {fi.Name}: Fehler beim ermitteln von {nameof(plz)}"); }

                        try { ort = item.BaseItemDetail.FinalRecipient.Party.NameAddress.City; }
                        catch { Log.Log($"File {fi.Name}: Fehler beim ermitteln von {nameof(ort)}"); }

                        try { ansprechpartner = item.BaseItemDetail.FinalRecipient.Party.ReceivingContact.Contact.ContactName; }
                        catch { Log.Log($"File {fi.Name}: Fehler beim ermitteln von {nameof(ansprechpartner)}"); }

                        //try { positionsnummer = $"{item.BaseItemDetail.LineItemNum.BuyerLineItemNum}"; }
                        //catch { Log.Log($"File {fi.Name}: Fehler beim ermitteln von {nameof(positionsnummer)}"); }
                        
                        try
                        {
                            if (null != item.BaseItemDetail.FinalRecipient.Party.ReceivingContact.Contact.ListOfContactNumber)
                            {
                                foreach (ContactNumber cn in item.BaseItemDetail.FinalRecipient.Party.ReceivingContact.Contact.ListOfContactNumber)
                                {
                                    try
                                    {
                                        if (cn.ContactNumberTypeCoded == ContactNumberTypeCode.TelephoneNumber)
                                        {
                                            telefon = cn.ContactNumberValue;
                                        }

                                        if (cn.ContactNumberTypeCoded == ContactNumberTypeCode.EmailAddress)
                                        {
                                            email = cn.ContactNumberValue;
                                        }
                                    }
                                    catch { Log.Log($"File {fi.Name}: Fehler beim ermitteln von EmailAddress oder TelephoneNumber"); }
                                }
                            }
                        }
                        catch { Log.Log($"File {fi.Name}: Fehler beim ermitteln von EmailAddress oder TelephoneNumber"); }

                        //get zubehoer
                        try
                        {
                            if (item.ListOfNameValueSet == null) throw new Exception();

                            foreach (var nameValueSet in item.ListOfNameValueSet)
                            {
                                if (nameValueSet.SetName != "VARIABLE_PRODUCT_ATTRIBUTES") continue;

                                foreach (var nameValuePair in nameValueSet.ListOfNameValuePair)
                                {
                                    if (!nameValuePair.Name.Contains("Zubehör")) continue;

                                    zubehoer = nameValuePair.Value;
                                    break;
                                }
                            }
                        }
                        catch
                        {
                            Log.Log($"File {fi.Name}: Fehler beim ermitteln von {nameof(zubehoer)}");
                        }
                        #endregion item details

                        #region vails
                        try
                        {
                            if (item.BaseItemDetail.TotalQuantity.Quantity.Item.GetType() == typeof(QuantityValue))
                            {
                                QuantityValue q = item.BaseItemDetail.TotalQuantity.Quantity.Item as QuantityValue;
                                vails = $"{Decimal.ToInt32(q.Value)}";
                            }
                        }
                        catch { Log.Log($"File {fi.Name}: Fehler beim ermitteln von {nameof(vails)}"); }
                        #endregion vails

                        #region anlieferungsdatum
                        try
                        {
                            foreach (var scheduleline in item.DeliveryDetail.ListOfScheduleLine)
                            {
                                anlieferung = $"{scheduleline.RequestedDeliveryDate.Substring(6, 2)}.{scheduleline.RequestedDeliveryDate.Substring(4, 2)}.{scheduleline.RequestedDeliveryDate.Substring(0, 4)}";
                            }
                        }
                        catch { Log.Log($"File {fi.Name}: Fehler beim ermitteln von {nameof(anlieferung)}"); }
                        #endregion anlieferungsdatum

                        ArticleMapper am = new ArticleMapper();
                        am.MapArticles(productid);

                        output.Clear();

                        if (am.ArticleNumbers.Count == 0)
                        {
                            // build output string                
                            output.Append($"\"{Geschaeftszahl}\";");
                            output.Append($"\"{bestellnummerbbg}\";");
                            output.Append($"\"{aufnahmedatum}\";");
                            output.Append($"\"{anlieferung}\";");
                            output.Append($"\"{einrichtung}\";");
                            output.Append($"\"{vails}\";");
                            output.Append($"\"{produkt}\";");
                            output.Append($"no mapping for productid {productid};");
                            output.Append($"\"{plz}\";");
                            output.Append($"\"{ort}\";");
                            output.Append($"\"{fi.Name}\";");

                            PartyShipTo.AddLieferadresseColumns(ref output);

                            if (AddShipToPartyData)
                            {
                                PartyShipTo.AddLieferadresseValues(ref output);
                                PartyShipTo.AddValues(ref output);
                            }
                            if (AddBuyerPartyData)
                            {
                                PartyBuyer.AddKaeuferValues(ref output);
                                PartyBuyer.AddValues(ref output);
                            }
                            if (AddBillToPartyData)
                            {
                                PartyBillTo.AddPartnerValue(ref output);
                                PartyBillTo.AddRechnungsadresseValue(ref output);
                                PartyBillTo.AddValues(ref output);
                            }
                            if (AddSellerPartyData)
                            {
                                PartySeller.AddValues(ref output);
                            }

                            output.Append($"\"{zubehoer}\";");
                            //output.Append($"{positionsnummer};");                            
                            output.AppendLine();
                        }
                        else
                        {
                            foreach (int pzn in am.ArticleNumbers)
                            {
                                // build output string   
                                output.Append($"\"{Geschaeftszahl}\";");
                                output.Append($"\"{bestellnummerbbg}\";");
                                output.Append($"\"{aufnahmedatum}\";");
                                output.Append($"\"{anlieferung}\";");
                                output.Append($"\"{einrichtung}\";");
                                output.Append($"\"{vails}\";");
                                output.Append($"\"{produkt}\";");
                                output.Append($"\"{pzn}\";");
                                output.Append($"\"{plz}\";");
                                output.Append($"\"{ort}\";");
                                output.Append($"\"{fi.Name}\";");

                                PartyShipTo.AddLieferadresseColumns(ref output);


                                if (AddShipToPartyData)
                                {
                                    PartyShipTo.AddLieferadresseValues(ref output);
                                    PartyShipTo.AddValues(ref output);
                                }
                                if (AddBuyerPartyData)
                                {
                                    PartyBuyer.AddKaeuferValues(ref output);
                                    PartyBuyer.AddValues(ref output);
                                }
                                if (AddBillToPartyData)
                                {
                                    PartyBillTo.AddPartnerValue(ref output);
                                    PartyBillTo.AddRechnungsadresseValue(ref output);
                                    PartyBillTo.AddValues(ref output);
                                }
                                if (AddSellerPartyData)
                                {
                                    PartySeller.AddValues(ref output);
                                }

                                output.Append($"\"{zubehoer}\";");
                                //output.Append($"{positionsnummer};");                                
                                output.AppendLine();
                            }
                        }
                        
                        File.AppendAllText(OutputFile, output.ToString(), Encoding.UTF8);
                    }
                }
                catch (Exception ex)
                {
                    Log.Log($"Error in GenerateCSVFile for file {fi.Name}: {ex.Message}", Logger.LogType.Error);
                }
            }
            
            if (filesProcessed > 0)
            {
                Log.Log($"CSVFile generated for {filesProcessed} XML files: {OutputFile}");
                Log.Log($"VACFiles: {VACFiles}");
                Log.Log($"OtherFiles: {OtherFiles}");

                if (VACFiles > 0)
                {
                    SendCSVMail(OutputFile, Logfile);
                }
                else
                {
                    SendNoNewOrdersMail();
                }
            }
            else
            {
                Log.Log($"0 Files processed. No CSVFile generated!");
                SendNoNewOrdersMail();
            }            
        }

        static void SendNoNewOrdersMail()
        {
            try
            {
                MailConfiguration mailconfig = null;
                mailconfig = XML.Deserialize<MailConfiguration>("MailConfigurationNoOrder.xml");
                
                string subject = $"{mailconfig.Subject}";
                foreach (string r in mailconfig.Recipients)
                {
                    Log.Log($"Send mail to {r} with subject {subject} (no new orders)");
                }

                PHOENIXUtil.Mail.sendMailWithoutAuth(
                    ref mailconfig.SMTPServer,
                    ref mailconfig.Sender,
                    ref mailconfig.Recipients,
                    ref subject,
                    ref mailconfig.Body,
                    null
                    );

                Log.Log($"Mail was sent successfully (no new orders).");
            }
            catch (Exception ex)
            {
                Log.Log($"Problems in SendNoNewOrdersMail! {ex.Message} {ex.InnerException?.Message}", Logger.LogType.Error);
            }
        }

        static void SendCSVMail(string fileName, string logFileName)
        {
            try
            {
                MailConfiguration mailconfig = null;
                mailconfig = XML.Deserialize<MailConfiguration>("MailConfiguration.xml");

                FileInfo fi = new FileInfo(fileName);
                string subject = $"{mailconfig.Subject} - {fi.Name}";
                foreach (string r in mailconfig.Recipients)
                {
                    Log.Log($"Send mail to {r} with subject {subject}");
                }

                string body = $"{mailconfig.Body} \r\n\r\n================================================================\r\n\r\n {Log.LogContent}";
                
                PHOENIXUtil.Mail.sendMailWithoutAuth(
                    ref mailconfig.SMTPServer,
                    ref mailconfig.Sender,
                    ref mailconfig.Recipients,
                    ref subject,
                    ref body,
                    fileName
                    );

                Log.Log($"Mail was sent successfully.");
            }
            catch(Exception ex)
            {
                Log.Log($"Problems in SendCSVMail! {ex.Message} {ex.InnerException?.Message}", Logger.LogType.Error);
            }
        }

        static void Initialize()
        {
            if( File.Exists(Logfile) )
            {
                File.Delete(Logfile);
            }

            // initialize logger
            Log = new Logger(Logfile);
            Log.Log("Program started", Logger.LogType.Info);

            // create download directory if it´s not there already
            if (!Directory.Exists(DownloadDirectory))
            {
                Directory.CreateDirectory(DownloadDirectory);
                Log.Log($"Create download directory {DownloadDirectory}");
            }

            // create csv directory if it´s not there already
            if (!Directory.Exists(CsvDirectory))
            {
                Directory.CreateDirectory(CsvDirectory);
                Log.Log($"Create CSV directory {CsvDirectory}");
            }                        
        }
    }
}
