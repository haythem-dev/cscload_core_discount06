using IBM.Data.Informix;
using System;
using System.Collections.Generic;

namespace AnalyseDeliveryadvices
{
    public static class DeliveryAdviceDataReader
    {
        public static void DetermineDetails(DeliveryAdvice deliveryAdvice, IfxConnection warehouse, IfxConnection outbound)
        {
            DetermineAffectedCSCPositions(deliveryAdvice, warehouse);
            DetermineOrderProcessingPeriod(deliveryAdvice, outbound);
            DetermineIBTPositions(deliveryAdvice, outbound);
            DetermineNumberOfOrdersForTour(deliveryAdvice, outbound);
            DetermineShuttleOrderRecordType4(deliveryAdvice, outbound);
            DetermineIBTCustomerOrderRecordType4(deliveryAdvice, outbound);
            DetermineNumberOfDetailsLines(deliveryAdvice, warehouse);
            DetermineNumberOfLinesWithDelivery(deliveryAdvice, warehouse);
        }

        public static List<DeliveryAdvice> GetDeliveryAdvices(int date, IfxConnection warehouse, bool completed)
        {
            string query = "";
            if (completed)
            {
                query = DeliveryAdviceQueries.GetQueryCompleteDeliveryAdvices(date);
            }
            else
            {
                query = DeliveryAdviceQueries.GetQueryIncompleteDeliveryAdvices(date);
            }

            List<DeliveryAdvice> incompleteDeliveryAdvices = new List<DeliveryAdvice>();
            using (IfxCommand cmd = new IfxCommand(query, warehouse))
            {
                using (IfxDataReader rdr = cmd.ExecuteReader())
                {
                    while (rdr.Read())
                    {
                        try
                        {
                            incompleteDeliveryAdvices.Add(new DeliveryAdvice
                            {
                                BranchNo = rdr.GetInt16(0),
                                CustomerNo = rdr.GetInt32(1),
                                DeliveryAdviceDate = rdr.GetInt32(2),
                                DeliveryAdviceNo = Convert.ToInt32(rdr.GetString(3).Trim()),
                                CscOrderNo = rdr.GetInt32(4),
                                PharmosOrderNo = rdr.GetInt32(5),
                                Completed = Convert.ToInt32(rdr.GetString(6).Trim()),
                                OrderType = rdr.GetString(7).Trim(),
                                PickingType = rdr.GetString(8).Trim(),
                                BookingType = rdr.GetString(9).Trim()
                            });
                        }
                        catch (Exception ex)
                        {
                            Console.WriteLine("EXCEPTION:");
                            Console.WriteLine(InformixConnectionFactory.AnalyseDataReaderItem(rdr));
                            Console.WriteLine(ex.Message);
                            Console.WriteLine(ex.InnerException?.Message);
                        }

                    }
                }
            }
            return incompleteDeliveryAdvices;
        }

        public static void DetermineAffectedCSCPositions(DeliveryAdvice deliveryAdvice, IfxConnection warehouse)
        {
            deliveryAdvice.CscPositions = new List<int>();
            using (IfxCommand cmd = new IfxCommand(DeliveryAdviceQueries.GetQueryCollectCSCPositionsForDeliveryAdvice(deliveryAdvice), warehouse))
            {
                using (IfxDataReader rdr = cmd.ExecuteReader())
                {
                    while (rdr.Read())
                    {
                        deliveryAdvice.CscPositions.Add(rdr.GetInt32(0));
                    }
                }
            }
        }

        public static void DetermineOrderProcessingPeriod(DeliveryAdvice deliveryAdvice, IfxConnection outbound)
        {
            using (IfxCommand cmd = new IfxCommand(DeliveryAdviceQueries.GetQueryOrderProcessingPeriod(deliveryAdvice), outbound))
            {
                using (IfxDataReader rdr = cmd.ExecuteReader())
                {
                    while (rdr.Read())
                    {
                        deliveryAdvice.OrderProcessingStart = rdr.GetInt32(0);
                        deliveryAdvice.OrderProcessingEnd = rdr.GetInt32(1);
                        deliveryAdvice.BatchSchreiben = rdr.GetInt32(2);
                        deliveryAdvice.TourId = rdr.GetString(3);
                    }
                }
            }
        }

        public static void DetermineIBTPositions(DeliveryAdvice deliveryAdvice, IfxConnection outbound)
        {
            deliveryAdvice.IBTPositionList = new List<DeliveryAdviceIBTPos>();
            using (IfxCommand cmd = new IfxCommand(DeliveryAdviceQueries.GetQueryIBTPositionsForDeliveryAdvice(deliveryAdvice), outbound))
            {
                using (IfxDataReader rdr = cmd.ExecuteReader())
                {
                    while (rdr.Read())
                    {
                        deliveryAdvice.IBTPositionList.Add(new DeliveryAdviceIBTPos
                        {
                            CSCOrderPosNo = rdr.GetInt32(0),
                            IBTBranchNo = rdr.GetInt16(1),
                            IBTCSCOrderNo = rdr.GetInt32(2),
                            IBTCSCOrderPosNo = rdr.GetInt32(3)
                        });
                    }
                }
            }
        }

        public static void DetermineNumberOfOrdersForTour(DeliveryAdvice deliveryAdvice, IfxConnection outbound)
        {
            deliveryAdvice.NumberOfOrdersForTour = 0;
            using (IfxCommand cmd = new IfxCommand(DeliveryAdviceQueries.GetQueryNumberOfOrdersForTour(deliveryAdvice), outbound))
            {
                using (IfxDataReader rdr = cmd.ExecuteReader())
                {
                    while (rdr.Read())
                    {
                        deliveryAdvice.NumberOfOrdersForTour = rdr.GetInt32(0);
                    }
                }
            }
        }

        public static void DetermineShuttleOrderRecordType4(DeliveryAdvice deliveryAdvice, IfxConnection outbound)
        {
            deliveryAdvice.PhadexRecordType4ForShuttleOrder = false;
            deliveryAdvice.PhadexRecordType4ForShuttleOrderTransferDate = 0;
            deliveryAdvice.PhadexRecordType4ForShuttleOrderTransferTime = 0;
            if (deliveryAdvice.IsIBTShuttleOrder)
            {
                deliveryAdvice.PhadexRecordType4ForShuttleOrderTransferDate = -1;
                deliveryAdvice.PhadexRecordType4ForShuttleOrderTransferTime = -1;
                using (IfxCommand cmd = new IfxCommand(DeliveryAdviceQueries.GetQueryShuttleOrderRecordtype4(deliveryAdvice), outbound))
                {
                    using (IfxDataReader rdr = cmd.ExecuteReader())
                    {
                        while (rdr.Read())
                        {
                            deliveryAdvice.PhadexRecordType4ForShuttleOrder = true;
                            deliveryAdvice.PhadexRecordType4ForShuttleOrderTransferDate = rdr.GetInt32(6);
                            deliveryAdvice.PhadexRecordType4ForShuttleOrderTransferTime = rdr.GetInt32(7);
                        }
                    }
                }
            }
        }

        public static void DetermineIBTCustomerOrderRecordType4(DeliveryAdvice deliveryAdvice, IfxConnection outbound)
        {
            deliveryAdvice.PhadexRecordType4ForCustomerOrder = false;
            deliveryAdvice.PhadexRecordType4ForCustomerOrderTransferDate = 0;
            deliveryAdvice.PhadexRecordType4ForCustomerOrderTransferTime = 0;
            if (deliveryAdvice.HasIBTPositions)
            {
                deliveryAdvice.PhadexRecordType4ForCustomerOrderTransferDate = -1;
                deliveryAdvice.PhadexRecordType4ForCustomerOrderTransferTime = -1;
                using (IfxCommand cmd = new IfxCommand(DeliveryAdviceQueries.GetQueryIBTCustomerOrderRecordtype4(deliveryAdvice), outbound))
                {
                    using (IfxDataReader rdr = cmd.ExecuteReader())
                    {
                        while (rdr.Read())
                        {
                            deliveryAdvice.PhadexRecordType4ForCustomerOrder = true;
                            deliveryAdvice.PhadexRecordType4ForCustomerOrderTransferDate = rdr.GetInt32(6);
                            deliveryAdvice.PhadexRecordType4ForCustomerOrderTransferTime = rdr.GetInt32(7);
                        }
                    }
                }
            }
        }

        public static void DetermineNumberOfLinesWithDelivery(DeliveryAdvice deliveryAdvice, IfxConnection warehouse)
        {
            deliveryAdvice.NumberOfLinesWithDeliveredQty = 0;
            using (IfxCommand cmd = new IfxCommand(DeliveryAdviceQueries.GetQueryNumberOfLinesWithDeliveredQty(deliveryAdvice), warehouse))
            {
                using (IfxDataReader rdr = cmd.ExecuteReader())
                {
                    while (rdr.Read())
                    {
                        deliveryAdvice.NumberOfLinesWithDeliveredQty = rdr.GetInt32(0);
                    }
                }
            }
        }

        public static void DetermineNumberOfDetailsLines(DeliveryAdvice deliveryAdvice, IfxConnection warehouse)
        {
            deliveryAdvice.NumberOfDetailLines = 0;
            using (IfxCommand cmd = new IfxCommand(DeliveryAdviceQueries.GetQueryNumberOfLineDetails(deliveryAdvice), warehouse))
            {
                using (IfxDataReader rdr = cmd.ExecuteReader())
                {
                    while (rdr.Read())
                    {
                        deliveryAdvice.NumberOfDetailLines = rdr.GetInt32(0);
                    }
                }
            }
        }


    }
}
