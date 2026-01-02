#ifndef ARTICLESUBSTITUTIONUTIL_HPP
#define ARTICLESUBSTITUTIONUTIL_HPP

#include "pxerrorloggable.hpp"

class pxSession;
class pxOrder;
class pxOrderItem;
class pxArtBase;
class pxArtReImportList;

/*############################################################################################################################*/
/*                                       C L A S S                                                                            */
/*############################################################################################################################*/
class ArticleSubstitutionUtil : public pxErrorLoggable
{
    /*############################################################################################################################*/
    /*                                       P U B L I C                                                                          */
    /*############################################################################################################################*/
    public:
        enum  ActionCodes
        {
            SUBSTITUTE_NEWPRODUCT  = 1,         // france application code blocage 9
            SUBSTITUTE_REVERSE        ,         // france application reverse substitution
            SUBSTITUTE_FORWARD        ,         // general alternate substitution
            SUBSTITUTE_FORIBT         ,         // france application try to book substitue article for IBT
            SUBSTITUTE_REIMPORT                 // ReImport - Substitution
        };

                                    ArticleSubstitutionUtil( pxOrderItem* item );

        virtual                     ~ArticleSubstitutionUtil();

        bool                        isSubstitutionNecessary(  pxArtBase* article );
        bool                        isSubstituteNewProduct();
        bool                        isSubstituteReverse();
        bool                        isSubstituteForward();
        bool                        isSubstituteForIBT();
        bool                        isSubstituteReImport();


        long                        getSubstituteArticleNo() const;
        bool                        isSubstitutionArticleNoPassive() const;
        char                        getCodeBlocage() const;
        void                        injectOrder(pxOrder* order);
        void                        injectBookingFlags( int flags);
        void                        injectBookingType( int btype);
        void                        injectRequiredQuantity(long quantity);

        void                        injectActionCode( short actioncode);
        void                        resetVars();



    /*############################################################################################################################*/
    /*                                       P R I V A T E                                                                        */
    /*############################################################################################################################*/

    private:

        bool                        NewProductSubtitution( long ArticleNo);
        bool                        ReverseSubstitution( long ArticleNo);
        bool                        ForwardSubstitution( long ArticleNo);
        bool                        IBTSubstitution( long ArticleNo);
        bool                        ReImportSubstitution(long articleno);

        bool                        isReverseSubstitutionNecessary( pxArtBase* article);
        bool                        isNewProductSubstitutionNecessary( pxArtBase* article);
        bool                        isForwardSubstitutionNecessary( pxArtBase* article);
        bool                        isIBTSubstitutionNecessary( pxArtBase* article);
        bool                        isReImportSubstitutionNecessary(pxArtBase* article);

        bool                        findReImportArticle(pxArtReImportList& riplist);
        bool                        getArticleBookInformation( const long articleno, const short branchno);
        bool                        checkSubstitutionArticle( const long articleno, const  short branchno );

        pxOrder*                    m_Order;
        pxOrderItem*                m_Item;
        pxSession*                  m_Session;
        int                         m_BookingFlags;
        int                         m_BookingType;
        long                        m_SubstituteArticleNo;
        bool                        m_bSubstitutionArticleNoPassive;
        char                        m_CodeBlocage;
        short                       m_ActionCode;
        long                        m_RequiredQuantity;
};

#endif // ARTICLESUBSTITUTIONUTIL_HPP
