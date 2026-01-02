using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AnalyseDeliveryadvices
{
    public static class DeliveryAdviceQueries
    {
        public static string GetQueryNumberOfLinesWithDeliveredQty(DeliveryAdvice dh)
        {
            StringBuilder sb = new StringBuilder();
            sb = sb.Append("select count(*)::int as records ");
            sb = sb.Append("from deliveryadvicehead h ");
            sb = sb.Append("join deliveryadviceline l on l.branchno = h.branchno and l.customerno = h.customerno and l.deliveryadvicedate = h.deliveryadvicedate and l.deliveryadviceno = h.deliveryadviceno ");
            sb = sb.AppendFormat("where h.deliveryadvicedate = {0} ", dh.DeliveryAdviceDate);
            sb = sb.AppendFormat("and h.branchno = {0} ", dh.BranchNo);
            sb = sb.AppendFormat("and h.customerno = {0} ", dh.CustomerNo);
            sb = sb.AppendFormat("and h.deliveryadviceno = {0} ", dh.DeliveryAdviceNo);
            sb = sb.Append("and l.qty_confirmed > 0 and h.pickingtype != '2';");
            return sb.ToString();
        }

        public static string GetQueryNumberOfLineDetails(DeliveryAdvice dh)
        {
            StringBuilder sb = new StringBuilder();
            sb = sb.Append("select count(*)::int as records ");
            sb = sb.Append("from deliveryadvicehead h ");
            sb = sb.Append("join deliveryadviceline l on l.branchno = h.branchno and l.customerno = h.customerno and l.deliveryadvicedate = h.deliveryadvicedate and l.deliveryadviceno = h.deliveryadviceno ");
            sb = sb.Append("join deliveryadvicelinedetails d on d.branchno = h.branchno and d.customerno = h.customerno and d.deliveryadvicedate = h.deliveryadvicedate and d.pharmosorderno = h.pharmosorderno and d.pharmosorderposno = l.pharmosorderposno ");
            sb = sb.AppendFormat("where h.deliveryadvicedate = {0} ", dh.DeliveryAdviceDate);
            sb = sb.AppendFormat("and h.branchno = {0} ", dh.BranchNo);
            sb = sb.AppendFormat("and h.customerno = {0} ", dh.CustomerNo);
            sb = sb.AppendFormat("and h.deliveryadviceno = {0};", dh.DeliveryAdviceNo);
            return sb.ToString();
        }

        public static string GetQueryShuttleOrderRecordtype4(DeliveryAdvice dh)
        {
            StringBuilder sb = new StringBuilder();
            sb = sb.Append("SELECT SUBSTR(x.data, 0, 3) AS K004_SA, SUBSTR(x.data, 4, 6) AS K004_PROG, SUBSTR(x.data, 10, 7) AS K004_IDF ");
            sb = sb.Append(", SUBSTR(x.data, 17, 7) AS K004_KSCAUFTRAG, SUBSTR(x.data, 24, 10) AS K004_INVOICENO, SUBSTR(x.data, 34, 1) AS K004_MODE_1_SHUTTLE_0_KUNDE ");
            sb = sb.Append(", (CAST(TO_CHAR(x.transferdatetime, '%Y%m%d') AS INTEGER)) AS TRANSFERDATE, (CAST(TO_CHAR(x.transferdatetime, '%H%M%S') AS INTEGER)) AS TRANSFERTIME, x.recordno ");
            sb = sb.Append("FROM aphadextransaction x ");
            sb = sb.Append("WHERE x.recordtype = 4 AND substr(x.data, 34, 1)= '1' ");
            sb = sb.AppendFormat("AND (CAST(TO_CHAR(archivedate, '%Y%m%d') AS INTEGER)) = {0} ", dh.DeliveryAdviceDate);
            sb = sb.AppendFormat("AND x.branchno = {0} ", dh.BranchNo);
            sb = sb.AppendFormat("AND SUBSTR(x.data, 24, 10)::INT = {0} ", dh.DeliveryAdviceNo);
            sb = sb.AppendFormat("AND SUBSTR(x.data, 17,  7)::INT = {0};", dh.CscOrderNo);
            return sb.ToString();
        }

        public static string GetQueryIBTCustomerOrderRecordtype4(DeliveryAdvice dh)
        {
            StringBuilder sb = new StringBuilder();
            sb = sb.Append("SELECT SUBSTR(x.data, 0, 3) AS K004_SA, SUBSTR(x.data, 4, 6) AS K004_PROG, SUBSTR(x.data, 10, 7) AS K004_IDF ");
            sb = sb.Append(", SUBSTR(x.data, 17, 7) AS K004_KSCAUFTRAG, SUBSTR(x.data, 24, 10) AS K004_INVOICENO, SUBSTR(x.data, 34, 1) AS K004_MODE_1_SHUTTLE_0_KUNDE ");
            sb = sb.Append(", (CAST(TO_CHAR(x.transferdatetime, '%Y%m%d') AS INTEGER)) AS TRANSFERDATE, (CAST(TO_CHAR(x.transferdatetime, '%H%M%S') AS INTEGER)) AS TRANSFERTIME, x.recordno ");
            sb = sb.Append("FROM aphadextransaction x ");
            sb = sb.Append("WHERE x.recordtype = 4 AND substr(x.data, 34, 1)= '0' ");
            sb = sb.AppendFormat("AND (CAST(TO_CHAR(archivedate, '%Y%m%d') AS INTEGER)) = {0} ", dh.DeliveryAdviceDate);
            sb = sb.AppendFormat("AND x.branchno = {0} ", dh.BranchNo);
            sb = sb.AppendFormat("AND SUBSTR(x.data, 24, 10)::INT = {0} ", dh.DeliveryAdviceNo);
            sb = sb.AppendFormat("AND SUBSTR(x.data, 17,  7)::INT = {0};", dh.CscOrderNo);
            return sb.ToString();
        }

        public static string GetQueryNumberOfOrdersForTour(DeliveryAdvice dh)
        {
            StringBuilder sb = new StringBuilder();
            sb = sb.Append("SELECT count(*)::int as orders FROM akdauftrag a ");
            sb = sb.AppendFormat("WHERE a.datum = {0} AND a.filialnr = {1} AND a.kdauftragnrfiliale > 0 AND a.tourid = '{2}';", dh.DeliveryAdviceDate, dh.BranchNo, dh.TourId.Trim());
            return sb.ToString();
        }

        public static string GetQueryIncompleteDeliveryAdvices(int date)
        {
            StringBuilder sb = new StringBuilder();
            sb = sb.Append("SELECT h.branchno, h.customerno, h.deliveryadvicedate, h.deliveryadviceno, h.cscorderno, h.pharmosorderno, h.completed, h.ordertype, h.pickingtype, h.bookingtype ");
            sb = sb.Append("FROM deliveryadvicehead h ");
            sb = sb.AppendFormat("where h.deliveryadvicedate = {0} and h.completed = 0 ", date);
            sb = sb.Append("ORDER BY h.branchno, h.deliveryadviceno;");
            return sb.ToString();
        }

        public static string GetQueryCompleteDeliveryAdvices(int date)
        {
            StringBuilder sb = new StringBuilder();
            sb = sb.Append("SELECT h.branchno, h.customerno, h.deliveryadvicedate, h.deliveryadviceno, h.cscorderno, h.pharmosorderno, h.completed, h.ordertype, h.pickingtype, h.bookingtype ");
            sb = sb.Append("FROM deliveryadvicehead h ");
            sb = sb.AppendFormat("where h.deliveryadvicedate = {0} and h.completed = 1 ", date);
            sb = sb.Append("ORDER BY h.branchno, h.deliveryadviceno;");
            return sb.ToString();
        }

        public static string GetQueryCollectCSCPositionsForDeliveryAdvice(DeliveryAdvice dh)
        {
            StringBuilder sb = new StringBuilder();
            sb = sb.Append("SELECT l.cscorderposno ");
            sb = sb.Append("FROM deliveryadviceline l ");
            sb = sb.AppendFormat("WHERE l.branchno = {0} AND l.customerno = {1} ", dh.BranchNo, dh.CustomerNo);
            sb = sb.AppendFormat("AND l.deliveryadvicedate = {0} AND l.deliveryadviceno = {1} ", dh.DeliveryAdviceDate, dh.DeliveryAdviceNo);
            sb = sb.Append("ORDER BY l.cscorderposno; ");
            return sb.ToString();
        }

        public static string GetQueryOrderProcessingPeriod(DeliveryAdvice dh)
        {
            StringBuilder sb = new StringBuilder();
            sb = sb.Append("SELECT e.datum as startdate, e.datum_rechnung as enddate, a.batchschreiben, a.tourid FROM akdauftragereignis e ");
            sb = sb.Append("JOIN akdauftrag a ON a.datum=e.datum_rechnung AND a.kdauftragnr=e.kdauftragnr ");
            sb = sb.AppendFormat("WHERE e.datum_rechnung = {0} AND e.kdauftragnr = {1} AND e.ereignisart=110;", dh.DeliveryAdviceDate, dh.CscOrderNo);
            return sb.ToString();
        }

        public static string GetQueryIBTPositionsForDeliveryAdvice(DeliveryAdvice dh)
        {
            var start = String.Format("{0}", dh.OrderProcessingStart);
            start = start.Substring(0, 4) + "-" + start.Substring(4, 2) + "-" + start.Substring(6, 2);

            var ende = String.Format("{0}", dh.OrderProcessingEnd);
            ende = ende.Substring(0, 4) + "-" + ende.Substring(4, 2) + "-" + ende.Substring(6, 2);

            StringBuilder sb = new StringBuilder();
            sb = sb.Append("SELECT r.cscorderposno, r.ibtbranchno, rr.ibtorderno, rr.ibtorderposno FROM ibtrequest r ");
            sb = sb.Append("JOIN ibtresponse rr ON rr.ibtrequestid = r.ibtrequestid ");
            sb = sb.AppendFormat("WHERE r.creationdatetime BETWEEN '{0} 00:00:00' AND '{1} 23:59:59' ", start, ende);
            sb = sb.AppendFormat("AND r.branchno = {0} and r.cscorderno = {1} and r.cscorderposno in (0 ", dh.BranchNo, dh.CscOrderNo);
            foreach( var posNo in dh.CscPositions )
            {
                sb = sb.AppendFormat(", {0} ", posNo);
            }
            sb = sb.Append(");");
            return sb.ToString();
        }


    }
}
