using Phoenix;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CSCServiceSWIMPFrance
{
    public static class SWIMPOrder
    {
        private static string m_Server = "zdev21";
        private static string m_Device = "XML";
        private static int m_CSCServicePort_FR = 56121;
        private static int m_CSCServicePort_PFR = 56131;
        private static CscServiceConfig m_CSCServiceConfig = null;
        private static SWIMP.FR.orderRequest m_XMLRequest = null;

        private static Csc.Order.OrderPositionRequest transformXMLOrderPosition2CSCOrderPosition(SWIMP.FR.orderRequestOrder xmlOrder, SWIMP.FR.orderRequestOrderOrderLine xmlPosition )
        {
            Csc.Order.OrderPositionRequest retval = new Csc.Order.OrderPositionRequest();

            retval.XmlOrderReference = xmlOrder.orderHeader.referenceNumber.Trim();

            retval.QuantityOrdered = Convert.ToInt32(xmlPosition.orderQuantity.Trim());

            // TODO!!! xmlPosition.OrderDiscount

            retval.AcceptInterBranchDelivery = true;
            retval.AcceptInterBranchDelivery = xmlPosition.interbranchTransferDesired;

            retval.AcceptRestDelivery = true;
            retval.AcceptRestDelivery = xmlPosition.subsequentDeliveryDesired;

            retval.AcceptDispoDelivery = false;
            retval.AcceptDispoDelivery = xmlPosition.articleRequirementPurchaseOrderDesired;

            retval.AcceptPartialDelivery = true;
            retval.AcceptPartialDelivery = xmlPosition.partialQuantity;

            if (!String.IsNullOrEmpty(xmlPosition.lineNumber))
            {
                retval.XmlLineReference = xmlPosition.lineNumber.Trim();
            }

            if (xmlPosition.FixPriceSpecified)
            {
                retval.PriceFree = xmlPosition.FixPrice;
            }

            if( xmlPosition.FixDiscountPercentageSpecified )
            {
                retval.DiscountPercentFree = xmlPosition.FixDiscountPercentage;
            }

            if ( xmlPosition.FixCatalogPriceSpecified )
            {
                retval.PriceAep = xmlPosition.FixCatalogPrice;
            }

            if (typeof(SWIMP.FR.orderRequestOrderOrderLineByArticleNumber) == xmlPosition.Item.GetType())
            {
                SWIMP.FR.orderRequestOrderOrderLineByArticleNumber artNo = xmlPosition.Item as SWIMP.FR.orderRequestOrderOrderLineByArticleNumber;
                retval.ArticleCode = artNo.articleNumber.Trim();
            }

            if (typeof(SWIMP.FR.orderRequestOrderOrderLineByEAN) == xmlPosition.Item.GetType() )
            {
                SWIMP.FR.orderRequestOrderOrderLineByEAN artNo = xmlPosition.Item as SWIMP.FR.orderRequestOrderOrderLineByEAN;
                retval.ArticleCode = artNo.EAN.Trim();
            }

            return retval;
        }

        private static Csc.Order.OpenOrderRequest transformXMLOrder2CSCOpenOrderRequest(SWIMP.FR.orderRequestOrder xmlOrder)
        {
            Csc.Order.OpenOrderRequest retval = new Csc.Order.OpenOrderRequest();

            retval.BranchNo = Convert.ToInt16(xmlOrder.orderHeader.branchNumber.Trim());
            retval.CustomerNo = Convert.ToInt32(xmlOrder.orderHeader.customerNumber.Trim());
            retval.Reference = xmlOrder.orderHeader.referenceNumber.Trim();
            retval.OrderText = xmlOrder.orderHeader.referenceNumber.Trim();

            if (!String.IsNullOrEmpty(xmlOrder.orderHeader.orderType))
            {
                retval.OrderType = xmlOrder.orderHeader.orderType.Trim();
            }

            if (!String.IsNullOrEmpty(xmlOrder.orderHeader.subOrderType))
            {
                retval.SubOrderType = xmlOrder.orderHeader.subOrderType.Trim();
            }

            if (xmlOrder.orderHeader.desiredDeliveryDateSpecified)
            {
                retval.DeliveryDate = Convert.ToInt32(xmlOrder.orderHeader.desiredDeliveryDate.ToString("yyyyMMdd"));
            }

            if (xmlOrder.orderHeader.isLaboratoryOrder)
            {
                retval.TurnoverOrigin = true;
            }

            return retval;
        }

        private static Csc.Order.PlaceOrderRequest transformXMLOrder2CSCOrder( SWIMP.FR.orderRequestOrder xmlOrder )
        {
            Csc.Order.PlaceOrderRequest retval = new Csc.Order.PlaceOrderRequest();

            #region order head information
            retval.OpenRequest = transformXMLOrder2CSCOpenOrderRequest(xmlOrder);
            #endregion order head information

            #region order lines information
            retval.Positions = new List<Csc.Order.OrderPositionRequest>();
            foreach ( var xmlPosition in xmlOrder.orderLine)
            {
                retval.Positions.Add(transformXMLOrderPosition2CSCOrderPosition(xmlOrder, xmlPosition));
            }
            #endregion order lines information

            #region order close information
            retval.CloseRequest = new Csc.Order.CloseOrderRequest();
            retval.CloseRequest.CloseMode = Csc.Order.OrderCloseMode.CLOSE_MODE_CLOSE;
            #endregion order close information


            return retval;
        }

        public static void Example1_Normal()
        {
            #region CSCService Configuration
            m_CSCServiceConfig = new CscServiceConfig();
            m_CSCServiceConfig.DeviceName = m_Device;
            m_CSCServiceConfig.Port = m_CSCServicePort_FR;
            m_CSCServiceConfig.Server = m_Server;
            #endregion CSCService Configuration

            #region Build XMLRequest

            /*
<?xml version="1.0"?>
<orderRequest xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" language="fr" version="1.0">
	<order>
		<orderHeader customerNumber="4086317" branchNumber="30" referenceNumber="2018051700001" orderType="A1" desiredDeliveryDate="2018-05-17" />
		<orderLine orderQuantity="10" Type_Codification="EAN13" Code_Produit="3400932421756" interbranchTransferDesired="false" subsequentDeliveryDesired="false" articleRequirementPurchaseOrderDesired="false" partialQuantity="true" lineNumber="1">
			<byEAN EAN="3400932421756" />
		</orderLine>
	</order>
</orderRequest>
            */

            m_XMLRequest = new SWIMP.FR.orderRequest();
            m_XMLRequest.language = SWIMP.FR.languageType.fr;

            List<SWIMP.FR.orderRequestOrder> orders = new List<SWIMP.FR.orderRequestOrder>();
            var order = new SWIMP.FR.orderRequestOrder();
            order.orderHeader = new SWIMP.FR.orderRequestOrderOrderHeader();
            order.orderHeader.customerNumber = "4086317";
            order.orderHeader.branchNumber = "30";
            order.orderHeader.referenceNumber = "2018051700001"; // Guid.NewGuid().ToString().Substring(0, 20);
            order.orderHeader.orderType = "A1";
            order.orderHeader.desiredDeliveryDate = DateTime.Now;

            List<SWIMP.FR.orderRequestOrderOrderLine> lines = new List<SWIMP.FR.orderRequestOrderOrderLine>();

            var line1 = new SWIMP.FR.orderRequestOrderOrderLine();
            line1.orderQuantity = "10";
            line1.Type_CodificationSpecified = true;
            line1.Type_Codification = SWIMP.FR.stPmlLine_CodificationProduit.EAN13;
            line1.Code_Produit = "3400932421756";
            line1.interbranchTransferDesired = false;
            line1.subsequentDeliveryDesired = false;
            line1.articleRequirementPurchaseOrderDesired = false;
            line1.partialQuantity = true;
            line1.lineNumber = "1";
            var item1 = new SWIMP.FR.orderRequestOrderOrderLineByEAN();
            item1.EAN = line1.Code_Produit;
            line1.Item = item1;
            lines.Add(line1);

            order.orderLine = lines.ToArray();
            orders.Add(order);
            m_XMLRequest.order = orders.ToArray();

            #endregion Build XMLRequest

            using (var client = new CscServiceClient(m_CSCServiceConfig))
            {
                client.OpenAndConnect();

                foreach( var xmlOrder in m_XMLRequest.order)
                {
                    Csc.Order.PlaceOrderRequest placeOrderRequest = transformXMLOrder2CSCOrder(xmlOrder);
                    Csc.Order.PlaceOrderResponse placeOrderResponse = client.Instance.placeNewOrder(placeOrderRequest);
                }

                client.Close();
            }
        }

        public static void Example2_FixPrice_FixDiscount()
        {
            #region CSCService Configuration
            m_CSCServiceConfig = new CscServiceConfig();
            m_CSCServiceConfig.DeviceName = m_Device;
            m_CSCServiceConfig.Port = m_CSCServicePort_PFR;
            m_CSCServiceConfig.Server = m_Server;
            #endregion CSCService Configuration

            #region Build XMLRequest

            /*
<?xml version="1.0"?>
<orderRequest xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" language="fr" version="1.0">
	<order>
		<orderHeader customerNumber="6002454" branchNumber="48" referenceNumber="OPNUTRIAVRIL2018_4" orderType="RL" desiredDeliveryDate="2018-06-11" />
		<orderLine orderQuantity="12" Type_Codification="EAN13" Code_Produit="3700937901391" interbranchTransferDesired="false" subsequentDeliveryDesired="true" articleRequirementPurchaseOrderDesired="false" partialQuantity="true" lineNumber="10" FixPrice="9.4" FixDiscountPercentage="5">
			<byEAN EAN="3700937901391" />
		</orderLine>
		<orderLine orderQuantity="12" Type_Codification="EAN13" Code_Produit="3700937901407" interbranchTransferDesired="false" subsequentDeliveryDesired="true" articleRequirementPurchaseOrderDesired="false" partialQuantity="true" lineNumber="20" FixPrice="8.8" FixDiscountPercentage="5" FixCatalogPrice="9.99">
			<byEAN EAN="3700937901407" />
		</orderLine>
	</order>
</orderRequest>
            */

            m_XMLRequest = new SWIMP.FR.orderRequest();
            m_XMLRequest.language = SWIMP.FR.languageType.fr;

            List<SWIMP.FR.orderRequestOrder> orders = new List<SWIMP.FR.orderRequestOrder>();

            var order = new SWIMP.FR.orderRequestOrder();
            order.orderHeader = new SWIMP.FR.orderRequestOrderOrderHeader();
            order.orderHeader.customerNumber = "6002454";
            order.orderHeader.branchNumber = "48";
            order.orderHeader.referenceNumber = "OPNUTRIAVRIL2018_4"; // Guid.NewGuid().ToString().Substring(0, 20);
            order.orderHeader.orderType = "RL";
            order.orderHeader.desiredDeliveryDate = DateTime.Now;

            List<SWIMP.FR.orderRequestOrderOrderLine> lines = new List<SWIMP.FR.orderRequestOrderOrderLine>();
            {
                var line1 = new SWIMP.FR.orderRequestOrderOrderLine();
                line1.orderQuantity = "12";
                line1.Type_CodificationSpecified = true;
                line1.Type_Codification = SWIMP.FR.stPmlLine_CodificationProduit.EAN13;
                line1.Code_Produit = "3700937901391";
                line1.interbranchTransferDesired = false;
                line1.subsequentDeliveryDesired = true;
                line1.articleRequirementPurchaseOrderDesired = false;
                line1.partialQuantity = true;
                line1.lineNumber = "10";
                line1.FixPriceSpecified = true;
                line1.FixPrice = 9.4;
                line1.FixDiscountPercentageSpecified = true;
                line1.FixDiscountPercentage = 5.0;
                var item1 = new SWIMP.FR.orderRequestOrderOrderLineByEAN();
                item1.EAN = line1.Code_Produit;
                line1.Item = item1;
                lines.Add(line1);
            }
            {
                var line2 = new SWIMP.FR.orderRequestOrderOrderLine();
                line2.orderQuantity = "12";
                line2.Type_CodificationSpecified = true;
                line2.Type_Codification = SWIMP.FR.stPmlLine_CodificationProduit.EAN13;
                line2.Code_Produit = "3700937901407";
                line2.interbranchTransferDesired = false;
                line2.subsequentDeliveryDesired = true;
                line2.articleRequirementPurchaseOrderDesired = false;
                line2.partialQuantity = true;
                line2.lineNumber = "20";
                line2.FixPriceSpecified = true;
                line2.FixPrice = 8.8;
                line2.FixDiscountPercentageSpecified = true;
                line2.FixDiscountPercentage = 5.0;
                line2.FixCatalogPriceSpecified = true;
                line2.FixCatalogPrice = 9.99;
                var item2 = new SWIMP.FR.orderRequestOrderOrderLineByEAN();
                item2.EAN = line2.Code_Produit;
                line2.Item = item2;
                lines.Add(line2);
            }

            order.orderLine = lines.ToArray();
            orders.Add(order);
            m_XMLRequest.order = orders.ToArray();

            #endregion Build XMLRequest

            using (var client = new CscServiceClient(m_CSCServiceConfig))
            {
                client.OpenAndConnect();

                foreach (var xmlOrder in m_XMLRequest.order)
                {
                    Csc.Order.PlaceOrderRequest placeOrderRequest = transformXMLOrder2CSCOrder(xmlOrder);
                    Csc.Order.PlaceOrderResponse placeOrderResponse = client.Instance.placeNewOrder(placeOrderRequest);
                }

                client.Close();
            }
        }

        public static void Example2_FixPrice_FixDiscount_DKRAMMER()
        {
            #region CSCService Configuration
            m_CSCServiceConfig = new CscServiceConfig();
            m_CSCServiceConfig.DeviceName = m_Device;
            m_CSCServiceConfig.Port = 56087;
            m_CSCServiceConfig.Server = m_Server;
            #endregion CSCService Configuration

            #region Build XMLRequest

            /*
<?xml version="1.0"?>
<orderRequest xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" language="fr" version="1.0">
	<order>
		<orderHeader customerNumber="6002454" branchNumber="48" referenceNumber="OPNUTRIAVRIL2018_4" orderType="RL" desiredDeliveryDate="2018-06-11" />
		<orderLine orderQuantity="12" Type_Codification="EAN13" Code_Produit="3700937901391" interbranchTransferDesired="false" subsequentDeliveryDesired="true" articleRequirementPurchaseOrderDesired="false" partialQuantity="true" lineNumber="10" FixPrice="9.4" FixDiscountPercentage="5">
			<byEAN EAN="3700937901391" />
		</orderLine>
		<orderLine orderQuantity="12" Type_Codification="EAN13" Code_Produit="3700937901407" interbranchTransferDesired="false" subsequentDeliveryDesired="true" articleRequirementPurchaseOrderDesired="false" partialQuantity="true" lineNumber="20" FixPrice="8.8" FixDiscountPercentage="5" FixCatalogPrice="9.99">
			<byEAN EAN="3700937901407" />
		</orderLine>
	</order>
</orderRequest>
            */

            m_XMLRequest = new SWIMP.FR.orderRequest();
            m_XMLRequest.language = SWIMP.FR.languageType.fr;

            List<SWIMP.FR.orderRequestOrder> orders = new List<SWIMP.FR.orderRequestOrder>();

            var order = new SWIMP.FR.orderRequestOrder();
            order.orderHeader = new SWIMP.FR.orderRequestOrderOrderHeader();
            order.orderHeader.customerNumber = "6002661";
            order.orderHeader.branchNumber = "48";
            order.orderHeader.referenceNumber = "OPNUTRIAVRIL2018_4"; // Guid.NewGuid().ToString().Substring(0, 20);
            order.orderHeader.orderType = "RL";
            order.orderHeader.desiredDeliveryDate = DateTime.Now;

            List<SWIMP.FR.orderRequestOrderOrderLine> lines = new List<SWIMP.FR.orderRequestOrderOrderLine>();
            {
                var line1 = new SWIMP.FR.orderRequestOrderOrderLine();
                line1.orderQuantity = "12";
                line1.Type_CodificationSpecified = true;
                line1.Type_Codification = SWIMP.FR.stPmlLine_CodificationProduit.EAN13;
                line1.Code_Produit = "3700937901391";
                line1.interbranchTransferDesired = false;
                line1.subsequentDeliveryDesired = true;
                line1.articleRequirementPurchaseOrderDesired = false;
                line1.partialQuantity = true;
                line1.lineNumber = "10";
                line1.FixPriceSpecified = true;
                line1.FixPrice = 9.4;
                line1.FixDiscountPercentageSpecified = true;
                line1.FixDiscountPercentage = 5.0;
                var item1 = new SWIMP.FR.orderRequestOrderOrderLineByEAN();
                item1.EAN = line1.Code_Produit;
                line1.Item = item1;
                lines.Add(line1);
            }
            {
                var line2 = new SWIMP.FR.orderRequestOrderOrderLine();
                line2.orderQuantity = "12";
                line2.Type_CodificationSpecified = true;
                line2.Type_Codification = SWIMP.FR.stPmlLine_CodificationProduit.EAN13;
                line2.Code_Produit = "3700937901407";
                line2.interbranchTransferDesired = false;
                line2.subsequentDeliveryDesired = true;
                line2.articleRequirementPurchaseOrderDesired = false;
                line2.partialQuantity = true;
                line2.lineNumber = "20";
                line2.FixPriceSpecified = true;
                line2.FixPrice = 8.8;
                line2.FixDiscountPercentageSpecified = true;
                line2.FixDiscountPercentage = 5.0;
                line2.FixCatalogPriceSpecified = true;
                line2.FixCatalogPrice = 9.99;
                var item2 = new SWIMP.FR.orderRequestOrderOrderLineByEAN();
                item2.EAN = line2.Code_Produit;
                line2.Item = item2;
                lines.Add(line2);
            }

            order.orderLine = lines.ToArray();
            orders.Add(order);
            m_XMLRequest.order = orders.ToArray();

            #endregion Build XMLRequest

            using (var client = new CscServiceClient(m_CSCServiceConfig))
            {
                client.OpenAndConnect();

                foreach (var xmlOrder in m_XMLRequest.order)
                {
                    Csc.Order.PlaceOrderRequest placeOrderRequest = transformXMLOrder2CSCOrder(xmlOrder);
                    Csc.Order.PlaceOrderResponse placeOrderResponse = client.Instance.placeNewOrder(placeOrderRequest);
                }

                client.Close();
            }
        }
    }
}
