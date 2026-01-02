using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Phoenix;
using System.Diagnostics;
using System.IO;

namespace CSCServiceNClientBasics
{


    partial class Program
    {
        static void testATOrder()
        {
            var _CSCServiceConfig = new CscServiceConfig();
            _CSCServiceConfig.DeviceName = "XML";
            _CSCServiceConfig.Port = PortCSCService_Steffen;
            _CSCServiceConfig.Server = "zdev21.phoenix.loc";

            using (var client = new CscServiceClient(_CSCServiceConfig))
            {
                client.OpenAndConnect();
                client.Instance.setExplainOn();

                var req = new Csc.Order.PlaceOrderRequest();

                req.OpenRequest = new Csc.Order.OpenOrderRequest();
                req.OpenRequest.BookingType = "0";
                req.OpenRequest.BranchNo = 61;
                req.OpenRequest.CustomerNo = 1301100;
                req.OpenRequest.OrderType = "NO";
                req.OpenRequest.Reference = "TESTAUFTRAG";
                req.OpenRequest.ShipmentType = "0";

                req.Positions = new List<Csc.Order.OrderPositionRequest>();

                var testArticle = new Csc.Order.OrderPositionRequest();
                testArticle.ArticleCode = "187866";
                testArticle.QuantityOrdered = 1;
                testArticle.AcceptInterBranchDelivery = false;
                testArticle.AcceptRestDelivery = false;
                testArticle.AcceptDispoDelivery = false;
                req.Positions.Add(testArticle);

                req.CloseRequest = new Csc.Order.CloseOrderRequest();
                req.CloseRequest.CloseMode = Csc.Order.OrderCloseMode.CLOSE_MODE_CLOSE;


                Stopwatch sw = new Stopwatch();
                sw.Start();
                var resp = client.Instance.placeNewOrder(req);
                Console.WriteLine("Duration: {0} ms", sw.ElapsedMilliseconds);

                client.Instance.setExplainOff();
                client.Close();
            }
        }








































        #region Ports
        static int PortCSCServicePAT = 56191;
        static int PortCSCServicePCH = 56141;
        static int PortCSCServicePFR = 56131;
        static int PortCSCServiceAT  = 56111;
        static int PortCSCServiceBG  = 56161;
        static int PortCSCServiceCH  = 56101;
        static int PortCSCServiceDE  = 56001;
        static int PortCSCServiceFR  = 56121;
        static int PortCSCServiceHR  = 56201;
        static int PortCSCServiceRS  = 56711;

        static int PortCSCService_Steffen = 56075;
        #endregion Ports


        static void Main(string[] args)
        {
            //testXMLEnv();
            //testOrderFrance();
            //testArt0();
            //testPACHPROD();
            //testBatchAdvice();
            //testIBTSplittingForANNA();
            //testDocumentArchiveInfo();
            //testConnectionPerformance();
            //exceedMaxIfxConnections();
            //testDanielKrammersCSCService();
            //testMSV3PAProduction();
            //testMSV3PAProductionSQExplain();
            //testMassOrderLines();
            //testMassOrderLinesFrank();
            //testSlowerByRisingNumberOfPositions();
            //testMassOrders();
            //test_getArticleStockBulk();
            //testMSV3Order();
            //testMSV3OrderNL();
            testATOrder();

            Console.WriteLine("Hit any key to exit");
            Console.ReadLine();
        }


        static void testXMLEnv()
        {
            List<string> ServerList = new List<string>();
            //ServerList.Add("ode23.phoenix.loc");
            //ServerList.Add("ode24.phoenix.loc");
            //ServerList.Add("ode25.phoenix.loc");
            //ServerList.Add("ode26.phoenix.loc");
            ServerList.Add("ode27.phoenix.loc");

            List<int> PortList = new List<int>();
            PortList.Add(56001);
            PortList.Add(56670);
            PortList.Add(56671);
            PortList.Add(56672);
            PortList.Add(56673);
            PortList.Add(56674);
            PortList.Add(56675);
            PortList.Add(56676);
            PortList.Add(56677);

            foreach (string Server in ServerList)
            {
                Console.WriteLine("#########################################################################");
                Console.WriteLine($"# Server {Server}");
                Console.WriteLine("#########################################################################");

                foreach (int Port in PortList)
                {
                    try
                    {
                        using (var client = new CscServiceClient(new CscServiceConfig() { DeviceName = "MSV3", Port = Port, Server = Server }))
                        {
                            client.OpenAndConnect();
                            Csc.Inquiry.ArticleInquiryResponse response = client.Instance.getArticleInquiry(GetPARequest());
                            Console.WriteLine($"CSCService Port {Port} Response: {response.RetValue.ErrorCode} Tour:{response.Positions[0].TourInfo.TourId}");
                            client.Close();
                        }
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine($"CSCService {Server}:{Port} Response: {ex.Message}");
                    }
                }
            }
        }



        static void testMSV3OrderNL()
        {
            var _CSCServiceConfig = new CscServiceConfig();
            _CSCServiceConfig.DeviceName = "MSV3";
            _CSCServiceConfig.Port = 56001;
            _CSCServiceConfig.Server = "zdev21.phoenix.loc";

            using (var client = new CscServiceClient(_CSCServiceConfig))
            {


                client.OpenAndConnect();
                client.Instance.setExplainOn();

                var req = new Csc.Order.PlaceOrderRequest();

                req.OpenRequest = new Csc.Order.OpenOrderRequest();
                req.OpenRequest.BookingType = "0";
                req.OpenRequest.BranchNo = 51;
                req.OpenRequest.CustomerNo = 6617;
                req.OpenRequest.OrderType = "NO";
                req.OpenRequest.Reference = "NORMAL";
                req.OpenRequest.ShipmentType = "0";
                req.OpenRequest.MSV3OrderLabel = "NORMAL";

                req.Positions = new List<Csc.Order.OrderPositionRequest>();


                var testArticle = new Csc.Order.OrderPositionRequest();
                testArticle.ArticleCode = "1126111";
                testArticle.QuantityOrdered = 1;
                testArticle.AcceptInterBranchDelivery = true;
                testArticle.AcceptRestDelivery = false;
                testArticle.AcceptDispoDelivery = false;
                testArticle.MSV3OrderID = Guid.NewGuid().ToString();
                testArticle.MSV3OrderSupportID = "MSV3OrderSupportID";
                testArticle.MSV3RequestID = Guid.NewGuid().ToString();
                testArticle.MSV3RequestSupportID = "MSV3RequestSupportID";
                req.Positions.Add(testArticle);

                req.CloseRequest = new Csc.Order.CloseOrderRequest();
                req.CloseRequest.CloseMode = Csc.Order.OrderCloseMode.CLOSE_MODE_CLOSE;


                Stopwatch sw = new Stopwatch();
                sw.Start();
                var resp = client.Instance.placeNewOrder(req);
                sw.Stop();
                Console.WriteLine("Duration: {0} ms", sw.ElapsedMilliseconds);

                client.Instance.setExplainOff();
                client.Close();
            }


        }

        static void testOrderFrance()
        {
            var _CSCServiceConfig = new CscServiceConfig();
            _CSCServiceConfig.DeviceName = "XML";
            _CSCServiceConfig.Port = PortCSCService_Steffen;
            _CSCServiceConfig.Server = "zdev21.phoenix.loc";

            using (var client = new CscServiceClient(_CSCServiceConfig))
            {
                client.OpenAndConnect();

                var req = new Csc.Order.PlaceOrderRequest();

                req.OpenRequest = new Csc.Order.OpenOrderRequest();

                req.OpenRequest.BranchNo = 32;
                req.OpenRequest.CustomerNo = 4021878;
                req.OpenRequest.Reference = "TESTIBT";
                req.OpenRequest.OrderType = "NO";
                req.OpenRequest.ShipmentType = "0";
                req.OpenRequest.BookingType = "0";

                req.Positions = new List<Csc.Order.OrderPositionRequest>();

                var testArticle = new Csc.Order.OrderPositionRequest();
                testArticle.ArticleCode = "4194538";
                testArticle.QuantityOrdered = 1;
                //testArticle.AcceptInterBranchDelivery = true;
                req.Positions.Add(testArticle);

                req.CloseRequest = new Csc.Order.CloseOrderRequest();
                req.CloseRequest.CloseMode = Csc.Order.OrderCloseMode.CLOSE_MODE_CLOSE;


                Stopwatch sw = new Stopwatch();
                sw.Start();
                var resp = client.Instance.placeNewOrder(req);
                sw.Stop();
                Console.WriteLine("Duration: {0} ms", sw.ElapsedMilliseconds);

                client.Close();
            }
        }

        static void testArt0()
        {
            var _CSCServiceConfig = new CscServiceConfig();
            _CSCServiceConfig.DeviceName = "XML";
            _CSCServiceConfig.Port = 56001;
            _CSCServiceConfig.Server = "zdev21.phoenix.loc";

            using (var client = new CscServiceClient(_CSCServiceConfig))
            {
                client.OpenAndConnect();

                var req = new Csc.Inquiry.ArticleStockBulkRequest();
                req.BranchNo = 54;
                req.CustomerNo = 0;
                req.GetBatchAndExpiryDate = true;
                req.Positions = new List<string>();
                req.Positions.Add("13986037");
                req.Positions.Add("5850810");


                var resp = client.Instance.getArticleStockBulk(req);

                client.Close();
            }

        }

        static void testPACHPROD()
        {
            var _CSCServiceConfig = new CscServiceConfig();
            _CSCServiceConfig.DeviceName = "XML";
            _CSCServiceConfig.Port = 56101;
            _CSCServiceConfig.Server = "och21.phoenix.loc";

            using (var client = new CscServiceClient(_CSCServiceConfig))
            {
                client.OpenAndConnect();

                var req = new Csc.Inquiry.ArticleInquiryRequest();
                req.BranchNo = 12;
                req.CustomerNo = 344739;
                req.Positions = new List<Csc.Inquiry.ArticleInquiryPositionRequest>();

                var item = new Csc.Inquiry.ArticleInquiryPositionRequest();
                item.ArticleCode = "350987";
                item.QuantityOrdered = 7;
                req.Positions.Add(item);

                var resp = client.Instance.getArticleInquiry(req);


                client.Close();
            }

        }

        static void testMSV3Order()
        {
            var _CSCServiceConfig = new CscServiceConfig();
            _CSCServiceConfig.DeviceName = "MSV3";
            _CSCServiceConfig.Port = 56001;
            _CSCServiceConfig.Server = "zdev21.phoenix.loc";

            using (var client = new CscServiceClient(_CSCServiceConfig))
            {


                client.OpenAndConnect();
                client.Instance.setExplainOn();

                var req = new Csc.Order.PlaceOrderRequest();

                req.OpenRequest = new Csc.Order.OpenOrderRequest();
                req.OpenRequest.BookingType = "0";
                req.OpenRequest.BranchNo = 40;
                req.OpenRequest.CustomerNo = 4511157;
                req.OpenRequest.OrderType = "NO";
                req.OpenRequest.Reference = "NORMAL";
                req.OpenRequest.ShipmentType = "0";
                req.OpenRequest.MSV3OrderLabel = "NORMAL";

                req.Positions = new List<Csc.Order.OrderPositionRequest>();


                var testArticle = new Csc.Order.OrderPositionRequest();
                testArticle.ArticleCode = "12587826";
                testArticle.QuantityOrdered = 1;
                testArticle.AcceptInterBranchDelivery = true;
                testArticle.MSV3OrderID = Guid.NewGuid().ToString();
                testArticle.MSV3OrderSupportID = "MSV3OrderSupportID";
                testArticle.MSV3RequestID = Guid.NewGuid().ToString();
                testArticle.MSV3RequestSupportID = "MSV3RequestSupportID";
                req.Positions.Add(testArticle);

                req.CloseRequest = new Csc.Order.CloseOrderRequest();
                req.CloseRequest.CloseMode = Csc.Order.OrderCloseMode.CLOSE_MODE_CLOSE;


                Stopwatch sw = new Stopwatch();
                sw.Start();
                var resp = client.Instance.placeNewOrder(req);
                sw.Stop();
                Console.WriteLine("Duration: {0} ms", sw.ElapsedMilliseconds);

                client.Instance.setExplainOff();
                client.Close();
            }


        }

        static void testBatchAdvice()
        {
            var _CSCServiceConfig = new CscServiceConfig();
            _CSCServiceConfig.DeviceName = "XML";
            _CSCServiceConfig.Port = 56101;
            _CSCServiceConfig.Server = "zdev21.phoenix.loc";


            using (var client = new CscServiceClient(_CSCServiceConfig))
            {
                client.OpenAndConnect();

                var request = new Documents.BatchAdviceRequest();
                request.BatchCorrectionOnly = false;
                request.BranchNo = 12;

                Stopwatch sw = new Stopwatch();
                sw.Start();
                var resp = client.Instance.getDataForBatchAdviceCreation(request);
                sw.Stop();
                Console.WriteLine("Duration: {0} ms", sw.ElapsedMilliseconds);

                client.Close();
            }
        }


        static void testIBTSplittingForANNA()
        {
            var _CSCServiceConfig = new CscServiceConfig();
            _CSCServiceConfig.DeviceName = "MSV3";
            //_CSCServiceConfig.Port = 56075;
            //_CSCServiceConfig.Port = 56084; // Naumann
            _CSCServiceConfig.Port = 56001; // $WSS/de/
            _CSCServiceConfig.Server = "zdev21.phoenix.loc";

            using (var client = new CscServiceClient(_CSCServiceConfig))
            {


                client.OpenAndConnect();

                var req = new Csc.Order.PlaceOrderRequest();

                req.OpenRequest = new Csc.Order.OpenOrderRequest();
                req.OpenRequest.BookingType = "0";
                req.OpenRequest.BranchNo = 51;
                //req.OpenRequest.CustomerNo = 4422778;
                req.OpenRequest.CustomerNo = 248349;
                req.OpenRequest.OrderType = "NO";
                req.OpenRequest.Reference = "NORMAL";
                req.OpenRequest.ShipmentType = "0";
                req.OpenRequest.MSV3OrderLabel = "NORMAL";

                req.Positions = new List<Csc.Order.OrderPositionRequest>();


                var immediatelyAvailable = new Csc.Order.OrderPositionRequest();
                immediatelyAvailable.ArticleCode = "10203603";
                immediatelyAvailable.QuantityOrdered = 1;
                immediatelyAvailable.AcceptInterBranchDelivery = true;
                immediatelyAvailable.MSV3OrderID = Guid.NewGuid().ToString();
                immediatelyAvailable.MSV3OrderSupportID = "MSV3OrderSupportID";
                immediatelyAvailable.MSV3RequestID = Guid.NewGuid().ToString();
                immediatelyAvailable.MSV3RequestSupportID = "MSV3RequestSupportID";
                req.Positions.Add(immediatelyAvailable);


                var ibtHanau = new Csc.Order.OrderPositionRequest();
                ibtHanau.ArticleCode = "10026992";
                ibtHanau.QuantityOrdered = 1;
                ibtHanau.AcceptInterBranchDelivery = true;
                req.Positions.Add(ibtHanau);

                var privateAss = new Csc.Order.OrderPositionRequest();
                privateAss.ArticleCode = "5266116";
                privateAss.QuantityOrdered = 1;
                privateAss.AcceptInterBranchDelivery = true;
                req.Positions.Add(privateAss);

                var hopefullyBatchFrom56 = new Csc.Order.OrderPositionRequest();
                hopefullyBatchFrom56.ArticleCode = "10069205";
                hopefullyBatchFrom56.QuantityOrdered = 1;
                hopefullyBatchFrom56.AcceptInterBranchDelivery = true;
                req.Positions.Add(hopefullyBatchFrom56);


                var hopefullyBatchFrom52 = new Csc.Order.OrderPositionRequest();
                hopefullyBatchFrom52.ArticleCode = "657183";
                hopefullyBatchFrom52.QuantityOrdered = 1;
                hopefullyBatchFrom52.AcceptInterBranchDelivery = true;
                req.Positions.Add(hopefullyBatchFrom52);

                req.CloseRequest = new Csc.Order.CloseOrderRequest();
                req.CloseRequest.CloseMode = Csc.Order.OrderCloseMode.CLOSE_MODE_CLOSE;


                Stopwatch sw = new Stopwatch();
                sw.Start();
                var resp = client.Instance.placeNewOrder(req);
                sw.Stop();
                Console.WriteLine("Duration: {0} ms", sw.ElapsedMilliseconds);


                client.Close();
            }
        }

        static void testDocumentArchiveInfo()
        {
            var _CSCServiceConfig = new CscServiceConfig();
            _CSCServiceConfig.DeviceName = "XML";
            _CSCServiceConfig.Port = 56001;
            _CSCServiceConfig.Server = "zdev21.phoenix.loc";

            using (var client = new CscServiceClient(_CSCServiceConfig))
            {
                client.OpenAndConnect();
                client.Instance.setExplainOn();

                var request = new Documents.SetDocumentInformationRequest();
                request.BranchNo = 5;
                request.CustomerNo = 537;
                request.DocumentDate = new Csc.Base.Date();
                request.DocumentDate.Day = 9;
                request.DocumentDate.Month = 1;
                request.DocumentDate.Year = 2019;
                request.DocumentGuid = Guid.NewGuid().ToString();
                request.DocumentLink = "http://www.google.de/" + request.DocumentGuid;
                request.DocumentNo = "1234567";
                request.DocumentType = Documents.Types.DocumentTypeEnum.Invoice;

                Documents.SetDocumentInformationResponse response = client.Instance.setDocumentInformation(request);

                client.Instance.setExplainOff();
                client.Close();
            }

        }

        static void test_getArticleStockBulk()
        {
            var _CSCServiceConfig = new CscServiceConfig();
            _CSCServiceConfig.DeviceName = "XML";
            _CSCServiceConfig.Port = 56001;
            _CSCServiceConfig.Server = "zdev21.phoenix.loc";

            using (var client = new CscServiceClient(_CSCServiceConfig))
            {
                client.OpenAndConnect();
                client.Instance.setExplainOn();

                var request = new Csc.Inquiry.ArticleStockBulkRequest();
                request.BranchNo = 78;
                request.CustomerNo = 0;
                request.GetBatchAndExpiryDate = true;
                request.Positions = new List<string>();
                request.Positions.Add("10005412");
                request.Positions.Add("10005429");
                request.Positions.Add("10109672");
                request.Positions.Add("10109689");
                request.Positions.Add("10109695");
                request.Positions.Add("10114271");
                request.Positions.Add("10114012");
                request.Positions.Add("10131269");
                request.Positions.Add("10101535");
                request.Positions.Add("10071449");
                request.Positions.Add("10205499");
                request.Positions.Add("16461");
                request.Positions.Add("10201047");
                request.Positions.Add("10201047");
                request.Positions.Add("10212915");
                request.Positions.Add("10212938");
                request.Positions.Add("10116258");
                request.Positions.Add("10217019");
                request.Positions.Add("10217019");
                request.Positions.Add("10329706");
                request.Positions.Add("10329712");
                request.Positions.Add("10329712");
                request.Positions.Add("10329729");
                request.Positions.Add("10329735");
                request.Positions.Add("10385136");
                request.Positions.Add("10385165");
                request.Positions.Add("10385171");
                request.Positions.Add("10385188");
                request.Positions.Add("10385194");
                request.Positions.Add("10385461");
                request.Positions.Add("10385461");
                request.Positions.Add("10386667");
                request.Positions.Add("10385343");
                request.Positions.Add("10116413");
                request.Positions.Add("10179974");
                request.Positions.Add("10121785");
                request.Positions.Add("10626829");
                request.Positions.Add("10626829");

                var response = client.Instance.getArticleStockBulk(request);
                client.Instance.setExplainOff();

                client.Close();
            }
        }


        static void testMSV3PAProduction()
        {
            var _CSCServiceConfig = new CscServiceConfig();
            _CSCServiceConfig.DeviceName = "XML";
            _CSCServiceConfig.Port = 56001;
            _CSCServiceConfig.Server = "ode23.phoenix.loc";

            using (var client = new CscServiceClient(_CSCServiceConfig))
            {
                client.OpenAndConnect();
                client.Close();
            }
        }

        static void testSlowerByRisingNumberOfPositions()
        {
            var _CSCServiceConfig = new CscServiceConfig();
            _CSCServiceConfig.DeviceName = "MSV3";
            _CSCServiceConfig.Port = 56001;
            _CSCServiceConfig.Server = "zdev21.phoenix.loc";



            using (var client = new CscServiceClient(_CSCServiceConfig))
            {
                client.OpenAndConnect();

                for (int x = 0; x < 200; ++x)
                {
                    var req = new Csc.Order.PlaceOrderRequest();

                    req.OpenRequest = new Csc.Order.OpenOrderRequest();
                    req.OpenRequest.BookingType = "0";
                    req.OpenRequest.BranchNo = 78;
                    req.OpenRequest.CustomerNo = 9780695;
                    req.OpenRequest.OrderType = "VH";
                    req.OpenRequest.Reference = "VERSAND";
                    req.OpenRequest.ShipmentType = "0";
                    req.OpenRequest.MSV3OrderLabel = "VERSAND";

                    req.Positions = new List<Csc.Order.OrderPositionRequest>();
                    var pos = new Csc.Order.OrderPositionRequest();
                    pos.ArticleCode = "6313390";
                    pos.QuantityOrdered = 1;
                    req.Positions.Add(pos);

                    req.CloseRequest = new Csc.Order.CloseOrderRequest();
                    req.CloseRequest.CloseMode = Csc.Order.OrderCloseMode.CLOSE_MODE_CLOSE;


                    Stopwatch sw = new Stopwatch();
                    sw.Start();
                    var resp = client.Instance.placeNewOrder(req);
                    sw.Stop();
                    Console.WriteLine("Order: {1} Duration: {0} ms", sw.ElapsedMilliseconds, x);
                }

                client.Close();
            }

        }

        static void testMassOrderLines()
        {
            var _CSCServiceConfig = new CscServiceConfig();
            _CSCServiceConfig.DeviceName = "XML";
            _CSCServiceConfig.Port = 56001; // Frank: 56084
            _CSCServiceConfig.Server = "zdev21.phoenix.loc";

            using (var client = new CscServiceClient(_CSCServiceConfig))
            {
                client.OpenAndConnect();

                var req = new Csc.Order.PlaceOrderRequest();

                req.OpenRequest = new Csc.Order.OpenOrderRequest();
                req.OpenRequest.BookingType = "0";
                req.OpenRequest.BranchNo = 51;
                req.OpenRequest.CustomerNo = 9180630;
                req.OpenRequest.OrderType = "NO";
                req.OpenRequest.Reference = "TEST";
                req.OpenRequest.ShipmentType = "0";

                req.Positions = new List<Csc.Order.OrderPositionRequest>();
                for( int i = 0; i < 1000; ++i )
                {
                    var pos = new Csc.Order.OrderPositionRequest();
                    pos.ArticleCode = "6313390";
                    pos.QuantityOrdered = 1;
                    req.Positions.Add(pos);
                }

                req.CloseRequest = new Csc.Order.CloseOrderRequest();
                req.CloseRequest.CloseMode = Csc.Order.OrderCloseMode.CLOSE_MODE_CLOSE;


                Stopwatch sw = new Stopwatch();
                sw.Start();
                var resp = client.Instance.placeNewOrder(req);
                sw.Stop();
                Console.WriteLine("Duration: {0} ms", sw.ElapsedMilliseconds);


                client.Close();
            }
        }

        static void testMassOrderLinesFrank()
        {
            var _CSCServiceConfig = new CscServiceConfig();
            _CSCServiceConfig.DeviceName = "XML";
            _CSCServiceConfig.Port = 56084;
            _CSCServiceConfig.Server = "zdev21.phoenix.loc";

            using (var client = new CscServiceClient(_CSCServiceConfig))
            {
                client.OpenAndConnect();

                var req = new Csc.Order.PlaceOrderRequest();

                req.OpenRequest = new Csc.Order.OpenOrderRequest();
                req.OpenRequest.BookingType = "0";
                req.OpenRequest.BranchNo = 51;
                req.OpenRequest.CustomerNo = 9180630;
                req.OpenRequest.OrderType = "NO";
                req.OpenRequest.Reference = "TEST";
                req.OpenRequest.ShipmentType = "0";

                req.Positions = new List<Csc.Order.OrderPositionRequest>();
                for (int i = 0; i < 1000; ++i)
                {
                    var pos = new Csc.Order.OrderPositionRequest();
                    pos.ArticleCode = "6313390";
                    pos.QuantityOrdered = 1;
                    req.Positions.Add(pos);
                }

                req.CloseRequest = new Csc.Order.CloseOrderRequest();
                req.CloseRequest.CloseMode = Csc.Order.OrderCloseMode.CLOSE_MODE_CLOSE;


                Stopwatch sw = new Stopwatch();
                sw.Start();
                var resp = client.Instance.placeNewOrder(req);
                sw.Stop();
                Console.WriteLine("Frank´s Duration: {0} ms", sw.ElapsedMilliseconds);


                client.Close();
            }
        }

        static void testDanielKrammersCSCService()
        {
            var _CSCServiceConfig = new CscServiceConfig();
            _CSCServiceConfig.DeviceName = "XML";
            _CSCServiceConfig.Port = 56087;
            _CSCServiceConfig.Server = "zdev21";

            using (var client = new CscServiceClient(_CSCServiceConfig))
            {
                client.OpenAndConnect(10000);
                client.Close();
            }
        }

        static void testConnectionPerformance()
        {
            var _CSCServiceConfig = new CscServiceConfig();
            _CSCServiceConfig.DeviceName = "XML";
            _CSCServiceConfig.Port = 56121;
            _CSCServiceConfig.Server = "zdev21";

            Parallel.ForEach(getIntegerList(50), (serialNo) =>
            {
                using (var client = new CscServiceClient(_CSCServiceConfig))
                {
                    try
                    {
                        string guid = Guid.NewGuid().ToString();
                        DateTime started = DateTime.Now;
                        client.OpenAndConnect(10000);
                        client.Close();

                        string log = String.Format("{0}\t Started: {5} \t->\t Durations: {1} - {2} - {3} - {4}", guid
                            , client._DurationTransportOpen.ToString("00000")
                            , client._DurationOpenSession.ToString("00000")
                            , client._DurationCloseSession.ToString("00000")
                            , client._DurationTransportClose.ToString("00000")
                            , started.ToString("HH:mm:ss.ms")
                         );

                        Console.WriteLine(log);
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine(ex.Message);
                    }
                }
            });
        }

        static List<int> getIntegerList(int size)
        {
            List<int> retval = new List<int>();
            for( int i = 0; i < size; ++i)
            {
                retval.Add(i);
            }
            return retval;
        }

        static void exceedMaxIfxConnections()
        {
            /*
            # NETTYPE                    - The configuration of poll threads
            #                              for a specific protocol. The
            #                              format is:
            #                              NETTYPE <protocol>,<# poll threads>
            #                              ,<number of connections/thread>
            #                              ,(NET|CPU)
            #                              You can include multiple NETTYPE
            #                              entries for multiple protocols.
            NETTYPE ipcshm,4,200,CPU
            NETTYPE soctcp,4,200,NET
            NETTYPE ipcstr,4,200,NET
             */

            int numberOfConnections = 1100;

            var _CSCServiceConfig = new CscServiceConfig();
            _CSCServiceConfig.DeviceName = "XML";
            _CSCServiceConfig.Port = 56121;
            _CSCServiceConfig.Server = "zdev21";

            List<CscServiceClient> clnts = new List<CscServiceClient>();

            for (int i = 0; i < numberOfConnections; ++i)
            {
                clnts.Add(new CscServiceClient(_CSCServiceConfig));
            }

            int y = 0;
            foreach (var x in clnts)
            {
                ++y;
                x.OpenAndConnect(10000);
                Console.WriteLine(String.Format("No. {0}: {1} / {2} ", y, x._DurationTransportOpen
                    , x._DurationOpenSession));
            }

            foreach (var x in clnts)
            {
                x.Close();
            }
        }


        static void testMSV3PAProductionSQExplain()
        {
            var _CSCServiceConfig = new CscServiceConfig();
            _CSCServiceConfig.DeviceName = "MSV3";
            _CSCServiceConfig.Port = PortCSCServiceDE;
            _CSCServiceConfig.Server = "ode23.phoenix.loc";

            #region MSV3 PA Request
            Csc.Inquiry.ArticleInquiryRequest request = new Csc.Inquiry.ArticleInquiryRequest()
            {
                BranchNo = 51,
                CustomerNo = 4442083,
                Positions = new List<Csc.Inquiry.ArticleInquiryPositionRequest>()
                    {
                        /*new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "3056515", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "3083251", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "3083268", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "3173304", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "3177153", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "3209410", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "3295007", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "3295013", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "3313320", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "3399847", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "3435566", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "3440633", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "3451430", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "3470864", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "3515911", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "3540719", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "3630859", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "3677022", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "3691542", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "3691714", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "3716696", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "3799133", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "3830788", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "4356254", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "4443361", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "4472339", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "4751453", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "4751482", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "4782040", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "4782146", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "4928087", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "4928124", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "4955782", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "4973739", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "5010397", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "5028262", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "5369052", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "5371706", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "5454042", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "5454378", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "5542295", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "6313361", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "6313438", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "6313444", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "6434260", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "6434277", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "6616541", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "6873019", QuantityOrdered = 1 },
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "6874125", QuantityOrdered = 1 },*/
                        new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "6874131", QuantityOrdered = 1 }
                    }
            };
            #endregion MSV3 PA Request

            using (var client = new CscServiceClient(_CSCServiceConfig))
            {
                client.OpenAndConnect();
                client.Instance.setExplainOn();

                Csc.Inquiry.ArticleInquiryResponse response = client.Instance.getArticleInquiry(request);

                client.Instance.setExplainOff();
                client.Close();
            }
        }

        static Csc.Inquiry.ArticleInquiryRequest GetPARequest()
        {
            return new Csc.Inquiry.ArticleInquiryRequest()
            {
                BranchNo = 5,
                CustomerNo = 3325317,
                Positions = new List<Csc.Inquiry.ArticleInquiryPositionRequest>()
                { new Csc.Inquiry.ArticleInquiryPositionRequest(){ ArticleCode = "1126111", QuantityOrdered = 1 }}
            };
        }

    }
}
