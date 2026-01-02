#include "blockedarticles.h"
#include <logger/loggerpool.h>
#include <boost/make_shared.hpp>

namespace libcsc {
namespace blockedarticles {

	BlockedArticles::BlockedArticles()
	{
	}

	BlockedArticles::~BlockedArticles()
	{
	}

	basar::Int16 BlockedArticles::getBranchNo() const
	{
		return m_BranchNo;
	}

	basar::Int32 BlockedArticles::getArticleNo() const
	{
		return m_ArticleNo;
	}

	basar::Int32 BlockedArticles::getBlockedID() const
	{
		return m_BlockedID;
	}

	const basar::VarString& BlockedArticles::getStorageLocation() const
	{
		return m_StorageLocation;
	}

	basar::Int32 BlockedArticles::getQuantity() const
	{
		return m_Quantity;
	}

	basar::Int16 BlockedArticles::getBookingType() const
	{
		return m_BookingType;
	}

	basar::Int32 BlockedArticles::getCreationTime() const
	{
		return m_CreationTime;
	}

	basar::Int32 BlockedArticles::getCreationDate() const
	{
		return m_CreationDate;
	}

	basar::Int32 BlockedArticles::getProcessedDate() const
	{
		return m_ProcessedDate;
	}

	basar::Int32 BlockedArticles::getProcessedTime() const
	{
		return m_ProcessedTime;
	}


	void BlockedArticles::setBranchNo(const basar::Int16 branchNo)
	{
		m_BranchNo = branchNo;
	}

	void BlockedArticles::setArticleNo(const basar::Int32 articleNo)
	{
		m_ArticleNo = articleNo;
	}

	void BlockedArticles::setBlockedID(const basar::Int32 blockedID)
	{
		m_BlockedID = blockedID;
	}

	void BlockedArticles::setStorageLocation(const basar::VarString& storageLocation)
	{
		m_StorageLocation = storageLocation;
	}

	void BlockedArticles::setQuantity(const basar::Int32 quantity)
	{
		m_Quantity = quantity;
	}

	void BlockedArticles::setBookingType(const basar::Int16 bookingType)
	{
		m_BookingType = bookingType;
	}

	void BlockedArticles::setCreationTime(const basar::Int32 creationTime)
	{
		m_CreationTime = creationTime;
	}

	void BlockedArticles::setCreationDate(const basar::Int32 creationDate)
	{
		m_CreationDate = creationDate;
	}

	void BlockedArticles::setProcessedDate(const basar::Int32 processedDate)
	{
		m_ProcessedDate = processedDate;
	}

	void BlockedArticles::setProcessedTime(const basar::Int32 processedTime)
	{
		m_ProcessedTime = processedTime;
	}

} // namespace returns
} // namespace libcsc
