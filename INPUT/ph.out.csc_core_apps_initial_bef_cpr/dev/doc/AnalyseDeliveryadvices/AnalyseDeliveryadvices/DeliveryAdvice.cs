using System;
using System.Collections.Generic;

namespace AnalyseDeliveryadvices
{
    public class DeliveryAdvice
    {
        public int BranchNo { get; set; }
        public int CustomerNo { get; set; }
        public int DeliveryAdviceDate { get; set; }
        public int DeliveryAdviceNo { get; set; }
        public int CscOrderNo { get; set; }
        public int PharmosOrderNo { get; set; }
        public int Completed { get; set; }
        public int BatchSchreiben { get; set; }
        public string TourId { get; set; }
        public int OrderProcessingStart { get; set; }
        public int OrderProcessingEnd { get; set; }
        public int NumberOfOrdersForTour { get; set; }
        public int NumberOfDetailLines { get; set;  }
        public int NumberOfLinesWithDeliveredQty { get; set; }
        public string OrderType { get; set; }
        public string PickingType { get; set; }
        public string BookingType { get; set; }
        public bool PhadexRecordType4ForShuttleOrder { get; set; }
        public int PhadexRecordType4ForShuttleOrderTransferDate;
        public int PhadexRecordType4ForShuttleOrderTransferTime;

        public bool PhadexRecordType4ForCustomerOrder { get; set;  }
        public int PhadexRecordType4ForCustomerOrderTransferDate;
        public int PhadexRecordType4ForCustomerOrderTransferTime;

        public IList<int> CscPositions { get; set; }
        public IList<DeliveryAdviceIBTPos> IBTPositionList { get; set; }

        public bool HasIBTPositions { get { return (this.IBTPositionList.Count > 0); } }

        public bool IsIBTShuttleOrder { get { return (this.BatchSchreiben == 1); } }

        public static string DataHeader()
        {
            return String.Format("Branch;Customer;DeliveryAdviceDate;DeliveryAdviceNo;CSCOrderNo;PharmosOrderNo;OrderType;TourID;NumberOfOrdersOnTour;ShuttleAuftrag;ShuttleAuftragDRKSC;IBTPositions;IBTCustomerOrderDRKSC;NumberOfLinesWithDelivery;NumberOfDetailLines");
        }

        public string ToData()
        {
            return String.Format("{0};{1};{2};{3};{4};{5};{6}{7}{8};{9};{10};{11};{12};{13};{14};{15};{16}",
                BranchNo, // 0
                CustomerNo, // 1
                DeliveryAdviceDate, // 2
                DeliveryAdviceNo, // 3
                CscOrderNo, // 4
                PharmosOrderNo, // 5
                OrderType, PickingType, BookingType, // 6,7,8
                TourId, // 9
                NumberOfOrdersForTour, // 10
                IsIBTShuttleOrder, // 11
                PhadexRecordType4ForShuttleOrderTransferTime, // 12
                HasIBTPositions, // 13
                PhadexRecordType4ForCustomerOrderTransferTime, // 14
                NumberOfLinesWithDeliveredQty, // 15
                NumberOfDetailLines); // 16
        }
    }
}
