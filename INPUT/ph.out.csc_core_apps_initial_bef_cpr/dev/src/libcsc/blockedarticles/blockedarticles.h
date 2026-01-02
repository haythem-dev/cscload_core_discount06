#ifndef GUARD_LIBCSC_BLOCKEDARTICLES_BLOCKEDARTICLES_H
#define GUARD_LIBCSC_BLOCKEDARTICLES_BLOCKEDARTICLES_H

#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/varstring.h>

namespace libcsc {
namespace blockedarticles {

	class BlockedArticles
	{
		friend class BlockedArticlesMapperBase;
		friend class BlockedArticlesRepository;

	public:
		BlockedArticles();
		virtual ~BlockedArticles();

		virtual       basar::Int16		getBranchNo() const;
		virtual       basar::Int32		getArticleNo() const;
		virtual       basar::Int32		getBlockedID() const;
		virtual const basar::VarString&	getStorageLocation() const;
		virtual	      basar::Int32		getQuantity() const;
		virtual	      basar::Int16		getBookingType() const;
		virtual	      basar::Int32		getCreationTime() const;
		virtual	      basar::Int32		getCreationDate() const;
		virtual		  basar::Int32		getProcessedDate() const;
		virtual		  basar::Int32		getProcessedTime() const;


		virtual void					setBranchNo(const basar::Int16);
		virtual void					setArticleNo(const basar::Int32);
		virtual	void					setBlockedID(const basar::Int32);
		virtual	void					setStorageLocation(const basar::VarString&);
		virtual	void					setQuantity(const basar::Int32);
		virtual	void					setBookingType(const basar::Int16);
		virtual	void					setCreationTime(const basar::Int32);
		virtual void					setCreationDate(const basar::Int32);
		virtual void					setProcessedDate(const basar::Int32);
		virtual void					setProcessedTime(const basar::Int32);

	private:
		libcsc::Int16		m_BranchNo;
		libcsc::Int32		m_ArticleNo;
		libcsc::Int32		m_BlockedID;
		libcsc::VarString	m_StorageLocation;
		libcsc::Int32		m_Quantity;
		libcsc::Int16		m_BookingType;
		libcsc::Int32		m_CreationTime;
		libcsc::Int32		m_CreationDate;
		libcsc::Int32		m_ProcessedDate;
		libcsc::Int32		m_ProcessedTime;
	};

} // namespace blockedarticles
} // namespace libcsc

#endif // !GUARD_LIBCSC_BLOCKEDARTICLES_BLOCKEDARTICLES_H
