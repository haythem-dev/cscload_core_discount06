#include "narcoticarchivesqlmapper.h"
#include "narcoticarchive.h"
#include "narcoticarchiveselectsqlparameterbinder.h"
#include "narcoticarchiveselectbycontributionvouchernosqlparameterbinder.h"
#include "narcoticarchiveinsertsqlparameterbinder.h"
#include <logger/loggerpool.h>


namespace libcsc 
{
	namespace document 
	{
		NarcoticArchiveSQLMapper::NarcoticArchiveSQLMapper(NarcoticArchivePtr narcoticArchivePtr, const basar::db::sql::ResultsetRef resultSet) :
			NarcoticArchiveMapperBase(narcoticArchivePtr),	m_ResultSet(resultSet)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveSQLMapper::NarcoticArchiveSQLMapper()");
		}

		NarcoticArchiveSQLMapper::NarcoticArchiveSQLMapper(NarcoticArchivePtr narcoticArchivePtr) :
			NarcoticArchiveMapperBase(narcoticArchivePtr)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveSQLMapper::NarcoticArchiveSQLMapper");
		}

		NarcoticArchiveSQLMapper::~NarcoticArchiveSQLMapper()
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveSQLMapper::~NarcoticArchiveSQLMapper()");
		}

		/// <summary>
		/// getSelectSQL
		/// </summary>
		/// <param name="documentDate"></param>
		/// <returns></returns>
		const basar::VarString NarcoticArchiveSQLMapper::getSelectSQL(const basar::Int32 transactionDate)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveSQLMapper::getSelectSQL()");
			std::stringstream sSql;

			sSql <<
				"SELECT TOP 10"
					"AcknowledgementStatus, "
					"ArticleNo, "
					"BranchNo, "
					"CatalogId, "
					"ContributionVoucherNo, "
					"ContributionVoucherTransferDate, "
					"ContributionVoucherTransferStatus, "
					"CustomerSupplierCip, "
					"CustomerSupplierCity, "
					"CustomerSupplierName, "
					"CustomerSupplierNo, "
					"CustomerSupplierStreet, "
					"DeletedFlag, "
					"DeliveryNoteCopyTransferDate, "
					"DeliveryNoteCopyTransferStatus, "
					"ForeName, "
					"InvoiceNo, "
					"NarcFactor, "
					"NarcGroup, "
					"NarcName, "
					"NarcPotency, "
					"NarcUnit, "
					"PrintedDate, "
					"PrintedTime, "
					"ProcessedFlag, "
					"PurchaseOrderNo, "
					"QtyInstock, "
					"QtyTransaction, "
					"Surname, "
					"TourId, "
					"TransactionDate, "
					"TransactionTime, "
					"TransactionType, "
					"Username, "
					"WarehouseOrderNo "
				"FROM narctransactioncatalog "
				"WHERE "
					"branchno = ?"
					"and customerSupplierNo = ?";

			if (transactionDate == 0)
			{
				sSql << " order by transactionDate desc";
			}
			else
			{
				sSql << " and transactionDate = ?";
			}

			return sSql.str();
		}

		void NarcoticArchiveSQLMapper::bindSelectSQL(basar::db::sql::PreparedStatementRef prepStmt, const basar::Int16 branchNo, const basar::Int32 customerSupplierNo, basar::Int32 transactionDate)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveSQLMapper::bindSelectSQL()");

			static basar::Int16 _branchNo = basar::Int16();
			static basar::Int32 _customerSupplierNo = basar::Int32();
			static basar::Int32 _transactionDate = basar::Int32();

			_branchNo = branchNo;
			_customerSupplierNo = customerSupplierNo;
			_transactionDate = transactionDate;

			basar::UInt32 counter = 0;

			prepStmt.setInt16(counter++, _branchNo);
			prepStmt.setInt32(counter++, _customerSupplierNo);

			if (transactionDate != 0)
			{
				prepStmt.setInt32(counter++, _transactionDate);
			}
		}

		const libcsc::persistence::ISqlParameterBinderPtr NarcoticArchiveSQLMapper::getSelectSqlParameterBinder(const basar::Int16 branchNo, const basar::Int32 customerSupplierNo, const basar::Int32 transactionDate)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveSQLMapper::getSelectSqlParameterBinder()");
			return libcsc::persistence::ISqlParameterBinderPtr(new NarcoticArchiveSelectSqlParameterBinder(branchNo, customerSupplierNo, transactionDate));
		}

		/// <summary>
		/// getSelectByContributionVoucherNoSQL
		/// </summary>
		/// <returns></returns>
		const basar::VarString NarcoticArchiveSQLMapper::getSelectByContributionVoucherNoSQL()
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveSQLMapper::getSelectByGuidSQL()");
			std::stringstream sSql;

			sSql <<
				"SELECT "
					"AcknowledgementStatus, "
					"ArticleNo, "
					"BranchNo, "
					"CatalogId, "
					"ContributionVoucherNo, "
					"ContributionVoucherTransferDate, "
					"ContributionVoucherTransferStatus, "
					"CustomerSupplierCip, "
					"CustomerSupplierCity, "
					"CustomerSupplierName, "
					"CustomerSupplierNo, "
					"CustomerSupplierStreet, "
					"DeletedFlag, "
					"DeliveryNoteCopyTransferDate, "
					"DeliveryNoteCopyTransferStatus, "
					"ForeName, "
					"InvoiceNo, "
					"NarcFactor, "
					"NarcGroup, "
					"NarcName, "
					"NarcPotency, "
					"NarcUnit, "
					"PrintedDate, "
					"PrintedTime, "
					"ProcessedFlag, "
					"PurchaseOrderNo, "
					"QtyInstock, "
					"QtyTransaction, "
					"Surname, "
					"TourId, "
					"TransactionDate, "
					"TransactionTime, "
					"TransactionType, "
					"Username, "
					"WarehouseOrderNo "
					"FROM narctransactioncatalog "
				"WHERE "
					"branchno = ? "
					"and contributionvoucherno = ? ";

			return sSql.str();
		}

		void NarcoticArchiveSQLMapper::bindSelectByContributionVoucherNoSQL(basar::db::sql::PreparedStatementRef prepStmt, const basar::Int16 branchNo, const basar::Int32 contributionVoucherNo)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveSQLMapper::bindSelectByContributionVoucherNoSQL()");
			static basar::Int16 _branchNo = basar::Int16();
			static basar::Int32 _contributionVoucherNo = basar::Int32();

			_branchNo = branchNo;
			_contributionVoucherNo = contributionVoucherNo;

			basar::UInt32 counter = 0;

			prepStmt.setInt16(counter++, _branchNo);
			prepStmt.setInt32(counter++, _contributionVoucherNo);
		}

		const libcsc::persistence::ISqlParameterBinderPtr NarcoticArchiveSQLMapper::getSelectByContributionVoucherNoSqlParameterBinder(const basar::Int16 branchNo, const basar::Int32 contributionVoucherNo)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveSQLMapper::getSelectByContributionVoucherNoSqlParameterBinder()");
			return libcsc::persistence::ISqlParameterBinderPtr(new NarcoticArchiveSelectByContributionVoucherNoSqlParameterBinder(branchNo, contributionVoucherNo));
		}

		//----------------------------------------------------------------------------------
		// INSERT
		//----------------------------------------------------------------------------------
		const basar::VarString NarcoticArchiveSQLMapper::getInsertSQL()
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveSQLMapper::getInsertSQL()");
			std::stringstream sSql;
			sSql <<
				"INSERT INTO nartransactioncatalog "
				"( "
					"acknowledgementStatus, "
					"articleNo, "
					"branchNo, "
					"catalogId, "
					"contributionVoucherNo, "
					"contributionVoucherTransferDate, "
					"contributionVoucherTransferStatus, "
					"customerSupplierCip, "
					"customerSupplierCity, "
					"customerSupplierName, "
					"customerSupplierNo, "
					"customerSupplierStreet, "
					"deletedFlag, "
					"deliveryNoteCopyTransferDate, "
					"deliveryNoteCopyTransferStatus, "
					"foreName, "
					"invoiceNo, "
					"narcFactor, "
					"narcGroup, "
					"narcName, "
					"narcPotency, "
					"narcUnit, "
					"printedDate, "
					"printedTime, "
					"processedFlag, "
					"purchaseOrderNo, "
					"qtyInstock, "
					"qtyTransaction, "
					"surname, "
					"tourId, "
					"transactionDate, "
					"transactionTime, "
					"transactionType, "
					"username, "
					"warehouseOrderNo "
				") "
				"VALUES "
				"( "
					"?, "
					"?, "
					"?, "
					"?, "
					"?, "
					"?, "
					"?, "
					"?, "
					"?, "
					"?, "
					"?, "
					"?, "
					"?, "
					"?, "
					"?, "
					"?, "
					"?, "
					"?, "
					"?, "
					"?, "
					"?, "
					"?, "
					"?, "
					"?, "
					"?, "
					"?, "
					"?, "
					"?, "
					"?, "
					"?, "
					"?, "
					"?, "
					"?, "
					"?, "
					"?"
				" )";
			return sSql.str();
		}

		void NarcoticArchiveSQLMapper::bindInsertSQL(basar::db::sql::PreparedStatementRef prepStmt, const NarcoticArchivePtr narcoticArchivePtr)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveSQLMapper::bindInsertSQL()");
			// Prepared statement setters take a reference and only move the address to the client sdk layer.
			// We have to take sure, variables are still existent at that moment execute() ist called!

			static basar::Int16 acknowledgementStatus = 0;
			static basar::Int32 articleNo = 0;
			static basar::Int16 branchNo = 0;
			static basar::Int32 catalogId = 0;
			static basar::Int32 contributionVoucherNo = 0;
			static basar::DateTime contributionVoucherTransferDate = basar::DateTime();
			static basar::Int16 contributionVoucherTransferStatus = 0;
			static basar::VarString customerSupplierCip = basar::VarString();
			static basar::VarString customerSupplierCity = basar::VarString();
			static basar::VarString customerSupplierName = basar::VarString();
			static basar::Int32 customerSupplierNo = 0;
			static basar::VarString customerSupplierStreet = basar::VarString();
			static basar::VarString deletedFlag = basar::VarString();
			static basar::DateTime deliveryNoteCopyTransferDate = basar::DateTime();
			static basar::Int16 deliveryNoteCopyTransferStatus = 0;
			static basar::VarString foreName = basar::VarString();
			static basar::Int32 invoiceNo = 0;
			static basar::Decimal narcFactor(0.0);
			static basar::VarString narcGroup = basar::VarString();
			static basar::VarString narcName = basar::VarString();
			static basar::Decimal narcPotency(0.0);
			static basar::VarString narcUnit = basar::VarString();
			static basar::Int32 printedDate = 0;
			static basar::Int32 printedTime = 0;
			static basar::VarString processedFlag = basar::VarString();
			static basar::Int32 purchaseOrderNo = 0;
			static basar::Int32 qtyInstock = 0;
			static basar::Int32 qtyTransaction = 0;
			static basar::VarString surname = basar::VarString();
			static basar::VarString tourId = basar::VarString();
			static basar::Int32 transactionDate = 0;
			static basar::Int32 transactionTime = 0;
			static basar::Int16 transactionType = 0;
			static basar::VarString username = basar::VarString();
			static basar::Int32 warehouseOrderNo = 0;

			acknowledgementStatus = narcoticArchivePtr->getAcknowledgementStatus();
			articleNo = narcoticArchivePtr->getArticleNo();
			branchNo = narcoticArchivePtr->getBranchNo();
			catalogId = narcoticArchivePtr->getCatalogId();
			contributionVoucherNo = narcoticArchivePtr->getContributionVoucherNo();
			contributionVoucherTransferDate = narcoticArchivePtr->getContributionVoucherTransferDate();
			contributionVoucherTransferStatus = narcoticArchivePtr->getContributionVoucherTransferStatus();
			customerSupplierCip = narcoticArchivePtr->getCustomerSupplierCip();
			customerSupplierCity = narcoticArchivePtr->getCustomerSupplierCity();
			customerSupplierName = narcoticArchivePtr->getCustomerSupplierName();
			customerSupplierNo = narcoticArchivePtr->getCustomerSupplierNo();
			customerSupplierStreet = narcoticArchivePtr->getCustomerSupplierStreet();
			deletedFlag = narcoticArchivePtr->getDeletedFlag();
			deliveryNoteCopyTransferDate = narcoticArchivePtr->getDeliveryNoteCopyTransferDate();
			deliveryNoteCopyTransferStatus = narcoticArchivePtr->getDeliveryNoteCopyTransferStatus();
			foreName = narcoticArchivePtr->getForeName();
			invoiceNo = narcoticArchivePtr->getInvoiceNo();
			narcFactor = narcoticArchivePtr->getNarcFactor();
			narcGroup = narcoticArchivePtr->getNarcGroup();
			narcName = narcoticArchivePtr->getNarcName();
			narcPotency = narcoticArchivePtr->getNarcPotency();
			narcUnit = narcoticArchivePtr->getNarcUnit();
			printedDate = narcoticArchivePtr->getPrintedDate();
			printedTime = narcoticArchivePtr->getPrintedTime();
			processedFlag = narcoticArchivePtr->getProcessedFlag();
			purchaseOrderNo = narcoticArchivePtr->getPurchaseOrderNo();
			qtyInstock = narcoticArchivePtr->getQtyInstock();
			qtyTransaction = narcoticArchivePtr->getQtyTransaction();
			surname = narcoticArchivePtr->getSurname();
			tourId = narcoticArchivePtr->getTourId();
			transactionDate = narcoticArchivePtr->getTransactionDate();
			transactionTime = narcoticArchivePtr->getTransactionTime();
			transactionType = static_cast<basar::Int16>(narcoticArchivePtr->getTransactionType());
			username = narcoticArchivePtr->getUsername();
			warehouseOrderNo = narcoticArchivePtr->getWarehouseOrderNo();

			basar::UInt32 counter = 0;

			prepStmt.setInt16(counter++, acknowledgementStatus);
			prepStmt.setInt32(counter++, articleNo);
			prepStmt.setInt16(counter++, branchNo);
			prepStmt.setInt32(counter++, catalogId);
			prepStmt.setInt32(counter++, contributionVoucherNo);
			prepStmt.setDateTime(counter++, contributionVoucherTransferDate);
			prepStmt.setInt16(counter++, contributionVoucherTransferStatus);
			prepStmt.setString(counter++, customerSupplierCip.c_str());
			prepStmt.setString(counter++, customerSupplierCity.c_str());
			prepStmt.setString(counter++, customerSupplierName.c_str());
			prepStmt.setInt32(counter++, customerSupplierNo);
			prepStmt.setString(counter++, customerSupplierStreet.c_str());
			prepStmt.setString(counter++, deletedFlag.c_str());
			prepStmt.setDateTime(counter++, deliveryNoteCopyTransferDate);
			prepStmt.setInt16(counter++, deliveryNoteCopyTransferStatus);
			prepStmt.setString(counter++, foreName.c_str());
			prepStmt.setInt32(counter++, invoiceNo);
			prepStmt.setDecimal(counter++, narcFactor);
			prepStmt.setString(counter++, narcGroup.c_str());
			prepStmt.setString(counter++, narcName.c_str());
			prepStmt.setDecimal(counter++, narcPotency);
			prepStmt.setString(counter++, narcUnit.c_str());
			prepStmt.setInt32(counter++, printedDate);
			prepStmt.setInt32(counter++, printedTime);
			prepStmt.setString(counter++, processedFlag.c_str());
			prepStmt.setInt32(counter++, purchaseOrderNo);
			prepStmt.setInt32(counter++, qtyInstock);
			prepStmt.setInt32(counter++, qtyTransaction);
			prepStmt.setString(counter++, surname.c_str());
			prepStmt.setString(counter++, tourId.c_str());
			prepStmt.setInt32(counter++, transactionDate);
			prepStmt.setInt32(counter++, transactionTime);
			prepStmt.setInt16(counter++, transactionType);
			prepStmt.setString(counter++, username.c_str());
			prepStmt.setInt32(counter++, warehouseOrderNo);
		}

		const libcsc::persistence::ISqlParameterBinderPtr NarcoticArchiveSQLMapper::getInsertSqlParameterBinder(const NarcoticArchivePtr narcoticArchivePtr)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveSQLMapper::getInsertSqlParameterBinder()");
			return libcsc::persistence::ISqlParameterBinderPtr(new NarcoticArchiveInsertSqlParameterBinder(narcoticArchivePtr));
		}

		//----------------------------------------------------------------------------------
		// UPDATE
		//----------------------------------------------------------------------------------
		const basar::VarString NarcoticArchiveSQLMapper::getUpdateAcknowledgementStatusSQL(const NarcoticArchivePtr narcoticArchivePtr)
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveSQLMapper::getUpdateAcknowledgementStatusSQL()");
			std::stringstream sSql;
			sSql << "UPDATE " << "narctransactioncatalog SET AcknowledgementStatus = " << narcoticArchivePtr->getAcknowledgementStatus();

			sSql << " WHERE ContributionVoucherNo = " << narcoticArchivePtr->getContributionVoucherNo();

			return sSql.str();
		}

		//----------------------------------------------------------------------------------
		// Mapping from database
		//----------------------------------------------------------------------------------
		void NarcoticArchiveSQLMapper::doMap()
		{
			LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "NarcoticArchiveSQLMapper::doMap()");
			if (m_ResultSet.isNull())
			{
				throw;
			}
			
			// transactionType is stored as a single char in DB and must be convertet to Int/Enum
			setTransactionType(static_cast<TransactionTypeEnum>((int)m_ResultSet.getString("transactiontype")[0]));
			setContributionVoucherTransferDate(m_ResultSet.getDateTime("contributionvouchertransferdate"));
			setDeliveryNoteCopyTransferDate(m_ResultSet.getDateTime("deliverynotecopytransferdate"));
			setNarcFactor(m_ResultSet.getDecimal("narcfactor"));
			setNarcPotency(m_ResultSet.getDecimal("narcpotency"));
			setAcknowledgementStatus(m_ResultSet.getInt16("acknowledgementstatus"));
			setBranchNo(m_ResultSet.getInt16("branchno"));
			setContributionVoucherTransferStatus(m_ResultSet.getInt16("contributionvouchertransferstatus"));
			setDeliveryNoteCopyTransferStatus(m_ResultSet.getInt16("deliverynotecopytransferstatus"));
			setArticleNo(m_ResultSet.getInt32("articleno"));
			setContributionVoucherNo(m_ResultSet.getInt32("contributionvoucherno"));
			setCustomerSupplierNo(m_ResultSet.getInt32("customersupplierno"));
			setInvoiceNo(m_ResultSet.getInt32("invoiceno"));
			setPrintedDate(m_ResultSet.getInt32("printeddate"));
			setPrintedTime(m_ResultSet.getInt32("printedtime"));
			setPurchaseOrderNo(m_ResultSet.getInt32("purchaseorderno"));
			setQtyInstock(m_ResultSet.getInt32("qtyinstock"));
			setQtyTransaction(m_ResultSet.getInt32("qtytransaction"));
			setTransactionDate(m_ResultSet.getInt32("transactiondate"));
			setTransactionTime(m_ResultSet.getInt32("transactiontime"));
			setWarehouseOrderNo(m_ResultSet.getInt32("warehouseorderno"));
			setCatalogId(m_ResultSet.getInt32("catalogid"));
			setCustomerSupplierCip(m_ResultSet.getString("customersuppliercip"));
			setCustomerSupplierCity(m_ResultSet.getString("customersuppliercity"));
			setCustomerSupplierName(m_ResultSet.getString("customersuppliername"));
			setCustomerSupplierStreet(m_ResultSet.getString("customersupplierstreet"));
			setDeletedFlag(m_ResultSet.getString("deletedflag"));
			setForeName(m_ResultSet.getString("forename"));
			setNarcGroup(m_ResultSet.getString("narcgroup"));
			setNarcName(m_ResultSet.getString("narcname"));
			setNarcUnit(m_ResultSet.getString("narcunit"));
			setProcessedFlag(m_ResultSet.getString("processedflag"));
			setSurname(m_ResultSet.getString("surname"));
			setTourId(m_ResultSet.getString("tourid"));
			setUsername(m_ResultSet.getString("username"));
		}

	} // end namespace document
} // end namespace libcsc
