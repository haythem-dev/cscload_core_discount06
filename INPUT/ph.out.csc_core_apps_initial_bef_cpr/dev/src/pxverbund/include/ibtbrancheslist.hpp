#ifndef IBTBRANCHESLIST_HPP
#define IBTBRANCHESLIST_HPP

#include "pxartvza.hpp"
#include "pxttype.hpp"

class IBTBranches;

/*############################################################################################################################*/
/*                                       C L A S S                                                                            */
/*############################################################################################################################*/
class IBTBranchesList : public nDBRecordSet, public nDListCollect
{

        /*############################################################################################################################*/
        /*                                       P U B L I C                                                                          */
        /*############################################################################################################################*/
    public:
        /*
        	IBTType in Tabelle ibtbranches:
        		0 = Normalverbund
        		1 = Privatsortiment
        		2 = Veterinär
        		3 = Regional
        		5 = Nationalverbund
        */

        enum IBTransferType
        {
            IBTTransferNone						= -1,	// Verbund nicht möglich
            IBTransferNormal					= 0,	// Verbund Normal						ibtbranches.ibttype = 0
            IBTransferPrivateAssortment			= 1,	// Verbund Privatsortiment				ibtbranches.ibttype = 1
            IBTransferVeterinary				= 2,	// Verbund Tierarznei					ibtbranches.ibttype = 2
            IBTransferRegional					= 3,	// Verbund Regional						ibtbranches.ibttype = 3
            IBTransferNational					= 5,	// Verbund National						ibtbranches.ibttype = 5
            IBTransferNationalAndRegional		= 6,	// Verbund National und Regional		ibtbranches.ibttype = 3,5
            IBTransferNationalAndNormal         = 7,	// Verbund National und Normal			ibtbranches.ibttype = 0,5
            IBTransferRegionalAndNormal			= 8,	// Verbund Regional und Normal			ibtbranches.ibttype = 0,3
            IBTransferAll                       = 9		// Verbund alle Typen					ibtbranches.ibttype = 0,3,5
        };

        static pxArtFiliale::IBTProduct	getIBTProductValue( char ibtarticle );


        IBTBranchesList( pxSession* session);

        virtual						~IBTBranchesList();

		bool						getIBTBranchesByArticleNoForNLevelIBT( const short& branchno, const short& ibtbranchno, const long& articleno );
        bool						getRelevantNLevelIBTBranches( const short& branchno, const long& articleno );		
        bool						getIBTBranchesByIBTType( const short& branchno, const short& ibtbranchno, pxArtFiliale::IBTProduct ibttypearticle );
		bool						getIBTBranchesByNLevelIBTType( const short& branchno, const short& ibtbranchno, short NLevelIBTType );
        bool						isIBTPossibleNow( short localbranchno, short ibtbranchno );

        /*############################################################################################################################*/
        /*                                       P R O T E C T E D                                                                    */
        /*############################################################################################################################*/
    protected:

        nCollectable*				AddToList( const void* record, const int row );

        void						Clear();

        virtual int 				EndBrowse( const int cursorid );

        virtual int 				GetNext( const void* record, const int cursorid );

        virtual int 				StartBrowse( const void *keys, const int cursorid );

        /*############################################################################################################################*/
        /*                                       P R I V A T E                                                                        */
        /*############################################################################################################################*/
    private:

        IBTransferType				getIBTransferTypeForArticleIBTType( pxArtFiliale::IBTProduct ibttypearticle ) const;

        pxTimeTypeList				getIBTTimeListByBranch(  short localbranchno, short ibtbranchno );

        pxSession*					getSession();

        short						m_BranchNo;
        short						m_IBTBranchNo;

        friend class IBTBranchesListIter;
};


/*############################################################################################################################*/
/*                                       C L A S S                                                                            */
/*############################################################################################################################*/
class IBTBranchesListIter : public nDListCollectIter
{
        /*############################################################################################################################*/
        /*                                       P U B L I C                                                                          */
        /*############################################################################################################################*/
    public:
        IBTBranchesListIter( IBTBranchesList& list ) : nDListCollectIter(list)
        {
            ;
        }

        virtual	~IBTBranchesListIter()
        {
            ;
        }
};


#endif /* IBTBRANCHESLIST_HPP */
