
//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordprocesshelper.h"
#include "recordtypeclassifier_definitions.h"
#include "transactionrecordbaseptr.h"
#include "transactionrecordbase.h"
#include "recordtypebase.h"
#include "ipxvbdbconnectionptr.h"
#include "ipxvbsessionptr.h"
#include "ipxvborderentryparamchecker.h"
#include "pxtenderprogressptr.h"
#include "pvhx01_includes.h"
#include "pxartbaseptr.h"
#include "pxtenderpos.hpp"
#include "pxarticlecharge.hpp"
#include "stockbooking/componentmanager/stockbookingcomponentmanagerptr.h"
#include "stockbooking/componentmanager/stockbookingcomponentmanager.h"
#include "stockbooking/longtermlack/ilongtermlackdeleterptr.h"
#include "stockbooking/longtermlack/ilongtermlackdeleter.h"

#include <icsc_logger.h>
#include <libbasarcmnutil_logging.h>
//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//
namespace domMod
{
	namespace pharmosTransaction
	{
		namespace processing
		{
            struct null_deleter
            {
                void operator()(void const *) const
                {
                }
            };

			RecordProcessHelper::RecordProcessHelper(pxVerbund::IPXVBSessionPtr session, pxVerbund::IPXVBOrderEntryParamCheckerPtr oeparam, pxVerbund::IPXVBDBConnectionPtr connection, libcsc_utils::ICSC_LoggerPtr logger)
				: m_PXVBSession(session), m_pxOrderEntryParam( oeparam ), m_PXVBConnection(connection), m_CSC_Logger( logger )
			{
			}

			RecordProcessHelper::~RecordProcessHelper()
			{
			}

			void RecordProcessHelper::updateTenderProgress( const core::TransactionRecordBasePtr record )
			{
				try
				{
					basar::VarString message("");
					basar::Int32 articleno = record->getArticleNo();
					basar::Int32 cscorderno = record->getCSCOrderNo().stol();
					m_PXVBConnection->beginTransaction( pxVerbund::SINGLE_RECORD );

						pxTenderProgressList tplist(m_PXVBSession->get());
						nDate orderdate = record->getInvoiceDateTime().getDate();
						tplist.Select( articleno, cscorderno, orderdate );
						if( tplist.Entries() )
						{
							pxTenderProgressPtr tp = pxTenderProgressPtr(static_cast<pxTenderProgress*>(tplist.RemoveAt(0)));
							if( !tp->IsGoodState() )
							{
								m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "pxTenderProgress is not in GoodState", record );
								m_PXVBConnection->rollbackTransaction();
								return;
							}

							if( 0 != tp->Get(cDBGET_FORUPDATE) )
							{
								m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "pxTenderProgress get for update failed", record );
								m_PXVBConnection->rollbackTransaction();
								return;
							}

							pxTenderPos tpos  ( m_PXVBSession->get(), tp->TenderNo(), tp->ArticleNo() );
							if( !tpos.IsGoodState() )
							{
								m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "pxTenderPos is not in GoodState", record );
								m_PXVBConnection->rollbackTransaction();
								return;
							}

							if( 0 != tpos.Get(cDBGET_FORUPDATE) )
							{
								m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "pxTenderPos get for update failed", record );
								m_PXVBConnection->rollbackTransaction();
								return;
							}

							if( record->isTypeOf_TenderChangeCustomerReturn() )
							{
								basar::Int32 oldQty = tp->ReturnQty();
								basar::Int32 newQty = oldQty;
								if (record->getBookingType() != core::RecordTypeBase::ACCOUNT_SUB_QUANTITY)
								{
									newQty += record->getQuantity();	// returned quantities or lacks during picking (decreased delivery quantity)
								}
								tp->SetReturnQty( newQty );

								message.format("Change TenderProgress ReturnQty: old Qty:%d new Qty:%d (CSCOrderNo:%d ArticleNo:%d)", oldQty, newQty, record->getCSCOrderNo().stol(), record->getArticleNo() );
								m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, message.c_str(), record );
							}
							else if( record->isTypeOf_PickingLack() || record->isTypeOf_InvoiceCancellation() )
							{
								basar::Int32 oldQty = tp->DeliveryQty();
								basar::Int32 newQty = oldQty;

								if (record->getBookingType() == core::RecordTypeBase::ACCOUNT_SUB_QUANTITY)
								{
									newQty -= record->getQuantity();	// canceled lacks during picking (increased delivered quantity)
								}
								else
								{
									newQty += record->getQuantity();
								}

								tp->SetDeliveryQty( newQty );

								message.format("Change TenderProgress DeliveryQty: old Qty:%d new Qty:%d (CSCOrderNo:%d ArticleNo:%d)", oldQty, newQty, record->getCSCOrderNo().stol(), record->getArticleNo() );
								m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, message.c_str(), record );
							}

							if ((tpos.ContractQty() > (tplist.SumDeliveryQty() - tplist.SumReturnQty())) && (tpos.TenderState() == 8 || tpos.TenderState() == 9))
							{
								tpos.SetUnblocked();
								message.format("Unblock Tender: CSCOrderNo:%d ArticleNo:%d", record->getCSCOrderNo().stol(), record->getArticleNo() );
								m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, message.c_str(), record );
							}

							tp->Put();
							if( !tp->IsGoodState() )
							{
								m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "pxTenderProgress put failed", record );
								m_PXVBConnection->rollbackTransaction();
								m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text record process pxverbund rollback - tenderprogress put failed", record );
								return;
							}

							tpos.Put();
							if( !tpos.IsGoodState() )
							{
								m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "pxTenderPos put failed", record );
								m_PXVBConnection->rollbackTransaction();
								m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text record process pxverbund rollback - tenderpos put failed", record );
								return;
							}
						}
					m_PXVBConnection->commitTransaction( pxVerbund::SINGLE_RECORD );
				}
				catch( basar::Exception& ex )
				{
					m_CSC_Logger->logBasarException("RecordProcessHelper::updateTenderProgress : text basar exception caught", ex, record );
				}
				catch( ... )
				{
					m_CSC_Logger->logGenericException("RecordProcessHelper::updateTenderProgress : text generic exception caught", record );
				}
			} // void RecordProcessHelper::updateTenderProgress( const core::TransactionRecordBasePtr record )

			TransactionType RecordProcessHelper::getTransactionType(const core::TransactionRecordBasePtr record)
			{
				// record types with own implementation
				if (record->getType() == ::util::recordtypes::RECORDTYPE_GOODSIN)				// "WE"
					return TRANSACTIONTYPE_GOODSIN; 											// 'b'

				if (record->getType() == ::util::recordtypes::RECORDTYPE_CUSTOMERRETURN)		// "RK"
					return TRANSACTIONTYPE_CUSTOMERRETURNS;										// 'c'

				if (record->getType() == ::util::recordtypes::RECORDTYPE_CODEBLOCAGE)			// "CB"
					return TRANSACTIONTYPE_CODEBLOCAGE;											// 'y'

				if (record->getType() == ::util::recordtypes::RECORDTYPE_TRANSFERQUARANTINE)  	// "TR"
					return TRANSACTIONTYPE_TRANSFERQUARANTINE;									// 'z'


				// record type other (writing article account / narctransfer)
				if (record->getType() == ::util::recordtypes::RECORDTYPE_STORAGERECONCILIATION)	// "LR"
					return TRANSACTIONTYPE_STOCKRECONCILIATION;									// 'd'

				if (record->getType() == ::util::recordtypes::RECORDTYPE_BATCHINCONSISTENCY)  	// "WC"
					return TRANSACTIONTYPE_BATCHINCONSISTENCY;									// 'o'

				if (record->getType() == ::util::recordtypes::RECORDTYPE_PERPETUALSTOCKTAKING) 	// "PI"
					return TRANSACTIONTYPE_PERMANENTINVENTORY;									// 'e'

				if (record->getType() == ::util::recordtypes::RECORDTYPE_STORAGERECONCILIATIONPREWHOLESALE) 	// "BO"
					return TRANSACTIONTYPE_STOCKRECONCILIATION;									// 'd'

				return TRANSACTIONTYPE_DEBIT; 													// all other default to "a" SELLOFF
			}

			basar::Int32 RecordProcessHelper::getCustomerSupplierNo(const core::TransactionRecordBasePtr record)
			{
				if (record->getType() == ::util::recordtypes::RECORDTYPE_GOODSIN)
				{
					return record->getOrderSupplierNo();
				}
				else if( record->getType() == ::util::recordtypes::RECORDTYPE_CUSTOMERRETURN)
				{
					return record->getCustomerNo().stol();
				}
				return 0;
			}

			void RecordProcessHelper::writeNarcTransferEntries(pxArtBasePtr artBase, const core::TransactionRecordBasePtr record)
			{
				//----------------------------------------------------------------------------
				//  Add new narctransactiontransfer entry
				//  This feature is just temporary controled by an entry within table
				//  parameter, until the Narcotictransfer Logik is runnig
				//----------------------------------------------------------------------------
				if (artBase->ArtClass().IsOpiat() && m_pxOrderEntryParam->checkNarcoticsTransfer())
				{
					long qtyTotal    = m_PXVBSession->get()->getStockBooking()->GetTotalQtyInStock(*artBase);

					pxNarcTransfer narcEntry( m_PXVBSession->get(), artBase->FilialNr(), artBase->ArtikelNr(), 0, 0);
					nString transactionType = static_cast<unsigned char>(getTransactionType(record));
					narcEntry.TransactionType(transactionType);
					narcEntry.CustomerSupplierNo(getCustomerSupplierNo(record));
					narcEntry.QtyTransaction(record->getQuantity());
					narcEntry.QtyInStock(qtyTotal);
					narcEntry.PurchaseOrderNo(record->getPurchaseOrderNo().stol());
					narcEntry.CompletedFlag('2'); // CR-16D048 --> for all transactiontypes (except 'a' ==> treated in Corpha / Phadex) set completedflag=2, so that these entries are managed by narctransfer
					narcEntry.Put();
				}
			}

			void RecordProcessHelper::changeBatchSaleability(pxArtBasePtr artBase, const core::TransactionRecordBasePtr record)
			{
				BatchStatusEnum saleability;

				if (record->getBookingType() == core::RecordTypeBase::BATCH_RECALL)
				{
					saleability = BATCHSTATUS_BATCH_RECALL;
				}
				else if (record->getBookingType() == core::RecordTypeBase::CANCEL_BATCH_RECALL)
				{
					saleability = BATCHSTATUS_SALEABLE;
				}
				else
				{
					return;
				}

				m_PXVBConnection->beginTransaction( pxVerbund::SINGLE_RECORD );
				pxArticleCharge articleBatch(m_PXVBSession->get(), artBase->FilialNr(), artBase->ArtikelNr(), record->getBatch() );
				articleBatch.Get(cDBGET_FORUPDATE);
				articleBatch.SetStateCharge(saleability);
				articleBatch.Put();
				if( articleBatch.IsGoodState() )
				{
					m_PXVBConnection->commitTransaction( pxVerbund::SINGLE_RECORD );
				}
				else
				{
					m_PXVBConnection->rollbackTransaction();
				}
			}

            void RecordProcessHelper::deleteLongTermLack( const core::TransactionRecordBasePtr record )
            {
                static const basar::VarString fun = "RecordProcessHelper::deleteLongTermLack()";
                try
                {
                    if (0 < record->getQuantity())
                    {
                        m_PXVBSession->get()->getStockBookingComponentManager()->getLongTermLackDeleter()->deleteLongTermLack( record->getArticleNo() );
                    }
                }
                catch( basar::Exception& e )
                {
                    std::stringstream message; message << fun << ": Exception caught while deletion of LongTermLack Article: " << e.what() << ";";
                    m_CSC_Logger->log(log4cplus::ERROR_LOG_LEVEL, message.str(), record);
                }
                catch( ... )
                {
                    std::stringstream message; message << fun << ": Exception caught while deletion of LongTermLack Article;";
                    m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, message.str(), record);
                }
            }

			void RecordProcessHelper::calcArtBaseStock(pxArtBasePtr artBase, const core::TransactionRecordBasePtr record)
			{
				ArticleAccountInfo info;
				info.PurchaseOrderNo 	= record->getPurchaseOrderNo().stol();
				info.CustomerSupplierNo	= getCustomerSupplierNo(record);
				switch (record->getBookingType())
				{
					case core::RecordTypeBase::ACCOUNT_ADD_QUANTITY:
					{
						info.StockTransaction = StockReturn;
						bool checkReservation = true;
						if (record->hasFollowUpRecord() || record->hasCMIFlag())
						{
							checkReservation = false;
						}
						m_PXVBSession->get()->getStockBooking()->AddQtyInStock(*artBase, record->getQuantity(), getTransactionType(record), &info, checkReservation);
                        
						//if the CMI flag is set add it to the reservation
						if (record->hasCMIFlag())
						{
							m_PXVBSession->get()->getStockBooking()->AddArticleReservation(*artBase, RESTYPE_CMI, "CMI", record->getQuantity());
						}

						deleteLongTermLack( record );
						break;
					}
					case core::RecordTypeBase::ACCOUNT_SUB_QUANTITY:
					{
						info.StockTransaction = StockDebit;

						//if the CMI flag is set, subtract from reserved and add to free stock first
						if (record->hasCMIFlag())
						{
							m_PXVBSession->get()->getStockBooking()->ReleaseArticleReservation(*artBase, RESTYPE_CMI, "CMI", record->getQuantity());
						}

						m_PXVBSession->get()->getStockBooking()->SubQtyInStock(*artBase, record->getQuantity(), getTransactionType(record), &info);
						break;
					}
					case core::RecordTypeBase::ACCOUNT_SET_QUANTITY:
					{
						info.StockTransaction = StockAccountCorrection;
						m_PXVBSession->get()->getStockBooking()->SetQtyInStock(*artBase, record->getQuantity(), getTransactionType(record), &info);
                        deleteLongTermLack(record);
						break;
					}
					case core::RecordTypeBase::BATCH_RECALL:
					{
						m_PXVBSession->get()->getStockBooking()->AddArticleReservation(*artBase, RESTYPE_BATCH_RECALL, "999", record->getQuantity());
						break;
					}
					case core::RecordTypeBase::CANCEL_BATCH_RECALL:
					{
						m_PXVBSession->get()->getStockBooking()->ReleaseArticleReservation(*artBase, RESTYPE_BATCH_RECALL, "999", record->getQuantity());
						break;
					}
					case core::RecordTypeBase::CERTIFICATE_AVAILABLE:
					{
						m_PXVBSession->get()->getStockBooking()->ReleaseArticleReservation(*artBase, RESTYPE_NO_CERTIFICATE, "299", record->getQuantity());
						break;
					}
					case core::RecordTypeBase::CERTIFICATE_NOT_AVAILABLE:
					{
						m_PXVBSession->get()->getStockBooking()->AddArticleReservation(*artBase, RESTYPE_NO_CERTIFICATE, "299", record->getQuantity());
						break;
					}
					case core::RecordTypeBase::CERTIFICATE_UPDATE:
					{
						m_PXVBSession->get()->getStockBooking()->SetAbsoluteArticleReservation(*artBase, RESTYPE_NO_CERTIFICATE, "299", record->getQuantity());
						break;
					}
					case core::RecordTypeBase::PACKAGE_INSERT_NOT_AVAILABLE:
					{
						m_PXVBSession->get()->getStockBooking()->AddArticleReservation(*artBase, RESTYPE_NO_PACKAGE_INSERT, "299", record->getQuantity());
						break;
					}
					default:
					{
						break;
					}
				}
			}

		}//end namespace processing
	}//end namespace pharmosTransaction
}//end namespace domMod
