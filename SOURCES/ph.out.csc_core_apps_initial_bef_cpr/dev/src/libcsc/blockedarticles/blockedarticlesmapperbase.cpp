#include "blockedarticlesmapperbase.h"
#include "blockedarticles.h"

namespace libcsc {
namespace blockedarticles {

	BlockedArticlesMapperBase::BlockedArticlesMapperBase(BlockedArticlesPtr blockedArticles)
		: m_BlockedArticles(blockedArticles)
	{
	}

	BlockedArticlesMapperBase::~BlockedArticlesMapperBase()
	{
	}

	void BlockedArticlesMapperBase::map()
	{
		doMap();
	}

	void BlockedArticlesMapperBase::setBranchNo(const basar::Int16 branchNo)
	{
		m_BlockedArticles->m_BranchNo = branchNo;
		m_BlockedArticles->m_BranchNo.setClean();
	}

	void BlockedArticlesMapperBase::setArticleNo(const basar::Int32 articleNo)
	{
		m_BlockedArticles->m_ArticleNo = articleNo;
		m_BlockedArticles->m_ArticleNo.setClean();
	}

	void BlockedArticlesMapperBase::setBlockedID(const basar::Int32 blockedID)
	{
		m_BlockedArticles->m_BlockedID = blockedID;
		m_BlockedArticles->m_BlockedID.setClean();
	}

	void BlockedArticlesMapperBase::setStorageLocation(const basar::VarString& storageLocation)
	{
		m_BlockedArticles->m_StorageLocation = storageLocation;
		m_BlockedArticles->m_StorageLocation.setClean();
	}

	void BlockedArticlesMapperBase::setQuantity(const basar::Int32 quantity)
	{
		m_BlockedArticles->m_Quantity = quantity;
		m_BlockedArticles->m_Quantity.setClean();
	}

	void BlockedArticlesMapperBase::setBookingType(const basar::Int16 bookingType)
	{
		m_BlockedArticles->m_BookingType = bookingType;
		m_BlockedArticles->m_BookingType.setClean();
	}

	void BlockedArticlesMapperBase::setCreationTime(const basar::Int32 creationTime)
	{
		m_BlockedArticles->m_CreationTime = creationTime;
		m_BlockedArticles->m_CreationTime.setClean();
	}

	void BlockedArticlesMapperBase::setCreationDate(const basar::Int32 creationDate)
	{
		m_BlockedArticles->m_CreationDate = creationDate;
		m_BlockedArticles->m_CreationDate.setClean();
	}

	void BlockedArticlesMapperBase::setProcessedDate(const basar::Int32 processedDate)
	{
		m_BlockedArticles->m_ProcessedDate = processedDate;
		m_BlockedArticles->m_ProcessedDate.setClean();
	}

	void BlockedArticlesMapperBase::setProcessedTime(const basar::Int32 processedTime)
	{
		m_BlockedArticles->m_ProcessedTime = processedTime;
		m_BlockedArticles->m_ProcessedTime.setClean();
	}

} // namespace returns
} // namespace libcsc
