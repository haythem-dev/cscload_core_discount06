using Phoenix;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

namespace CSCServiceNClientBasics
{
    partial class Program
    {
        static void testMassOrders()
        {
            var _CSCServiceConfig = new CscServiceConfig();
            _CSCServiceConfig.DeviceName = "MSV3";
            //_CSCServiceConfig.Port = 56001; // Land!
            //_CSCServiceConfig.Port = 56075; // Steffen: 56075
            _CSCServiceConfig.Port = 56084; // Frank: 56084
            _CSCServiceConfig.Server = "zdev21.phoenix.loc";

            int numberofOrders = 50;
            int numberofNormalArticles = 1;

            #region preparation
            initializeCustomerQueue();
            initializeBTMQueue();
            initializePZNQueue();

            List<Csc.Order.PlaceOrderRequest> orderList = new List<Csc.Order.PlaceOrderRequest>();
            for (int i = 0; i < numberofOrders; ++i)
            {
                //var customer = getCustomer();

                var customer = new Customer(51, 4654684);

                var req = new Csc.Order.PlaceOrderRequest();

                req.OpenRequest = new Csc.Order.OpenOrderRequest();
                req.OpenRequest.BranchNo = customer.BranchNo;
                req.OpenRequest.CustomerNo = customer.CustomerNo;
                req.OpenRequest.MSV3OrderLabel = "NORMAL";
                req.OpenRequest.OrderType = "NO";
                req.OpenRequest.BookingType = "0";
                req.OpenRequest.ShipmentType = "0";

                req.Positions = new List<Csc.Order.OrderPositionRequest>();

                for (int y = 0; y < numberofNormalArticles; ++y)
                {
                    var posNormal = new Csc.Order.OrderPositionRequest();
                    posNormal.ArticleCode = getPZNArticleCode();
                    posNormal.QuantityOrdered = 1;
                    req.Positions.Add(posNormal);
                }

                var posNarc = new Csc.Order.OrderPositionRequest();
                posNarc.ArticleCode = getBTMArticleCode();
                posNarc.QuantityOrdered = 1;
                req.Positions.Add(posNarc);

                req.CloseRequest = new Csc.Order.CloseOrderRequest();
                req.CloseRequest.CloseMode = Csc.Order.OrderCloseMode.CLOSE_MODE_CLOSE;

                orderList.Add(req);
            }
            #endregion preparation

            Parallel.ForEach(orderList, (order, state, index) =>
            {
                using (var client = new CscServiceClient(_CSCServiceConfig))
                {
                    try
                    {
                        client.OpenAndConnect(10000);

                        //if( index == 4 ) client.Instance.setExplainOn();

                        Stopwatch sw = new Stopwatch();
                        sw.Start();
                        var resp = client.Instance.placeNewOrder(order);
                        sw.Stop();

                        //if (index == 4) client.Instance.setExplainOff();

                        order.OpenRequest.OrderText = String.Format("Customer: {3:00}-{4:0000000} Order: {0:000} ({1:000000}) Duration: {2} ms", index, resp.OpenOrder.OrderNo, sw.ElapsedMilliseconds, order.OpenRequest.BranchNo, order.OpenRequest.CustomerNo);
                    }
                    catch (Exception ex)
                    {
                        order.OpenRequest.OrderText = ex.Message;
                    }
                }
            });

            foreach (var order in orderList)
            {
                Console.WriteLine(order.OpenRequest.OrderText);
            }

        }
    }
}
