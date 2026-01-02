#ifndef IBTBRANCHARTICLECONFIG_H
#define IBTBRANCHARTICLECONFIG_H

#include "pxbase/pxrecord.hpp"
#include "pxrecord.h"

struct tIBTBRANCHARTICLECONFIG;

// --------------------------------------------------------------------------------------------------- //
class IBTBranchArticleConfig : public pxDBRecord
{	
	public:
		enum IBTAssortmentTypes
		{
			eGeneralAssortment = 0,
			ePrivateAssortment = 1,
			eVeterinaryAssortment = 2			
		};

		enum IBTTypes
		{
			eIBTNotAvailable = 0,
			eIBTNational = 1,
			eIBTRegional = 2,
			eIBTLocal = 3
		};

	public:
												IBTBranchArticleConfig( pxSession* session, short branchno, long articleno );												
		virtual									~IBTBranchArticleConfig();

		IBTBranchArticleConfig&					operator=( const IBTBranchArticleConfig& src );
		IBTBranchArticleConfig&					operator=( const tIBTBRANCHARTICLECONFIG& src );		
		
		bool 									Get();

		short									getBranchNo() const;
		long									getArticleNo() const;
		short									getIBTAssortmentTypeID() const;
		
		bool									isIBTNotAvailable() const;
		bool									isIBTNational() const;
		bool									isIBTRegional() const;
		bool									isIBTLocal() const;
		
		bool									isAssortmentGeneral() const;
		bool									isAssortmentPrivate() const;
		bool									isAssortmentVeterinary() const;
		
	protected:
		void									Init();		

		short									getIBTTypeID() const;
		IBTTypes								getIBTType() const;

		//short									getIBTAssortmentTypeID() const;
		IBTAssortmentTypes						getIBTAssortmentType() const;

	private:		
		short									BranchNo;
		long									ArticleNo;	

		tIBTBRANCHARTICLECONFIG					m_Values;

		virtual  int							Read( const void *record );		
		IBTBranchArticleConfig&					Assign( IBTBranchArticleConfig& dest, const tIBTBRANCHARTICLECONFIG& src );
		tIBTBRANCHARTICLECONFIG&				Assign( tIBTBRANCHARTICLECONFIG& dest, const IBTBranchArticleConfig& src);		
};

#endif // IBTBRANCHARTICLECONFIG_H
