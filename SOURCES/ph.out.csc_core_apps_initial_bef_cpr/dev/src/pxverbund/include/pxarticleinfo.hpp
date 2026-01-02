/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

PXARTICLEINFO.HPP

REVISION HISTORY

30 March 2007 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXARTICLEINFO_INC
#define PXARTICLEINFO_INC

#include "database.hpp"
#include "money.hpp"

class pxSession;
class pxArtBase;
class pxArtPrice;

class pxArticleInfo
{

public:

// constructors:
                      pxArticleInfo(pxSession *session,short BranchNo,
                                    long ArticleNo, long Qty);

// destructor:
    virtual           ~pxArticleInfo();

// public member operators
    pxArticleInfo&    operator=(const pxArticleInfo& src);

// public member functions
    int  Build(nString& Sprache);
    bool IsGoodState();

    pxSession * Session();

//  Field updates

// Queries:
             short       BranchNo           () const {return BranchNo_             ;}
             long        ArticleNo          () const {return ArticleNo_            ;}
             long        Qty                () const {return Qty_                  ;}
             pxArtBase*  ArtBase            () const {return ArtBase_              ;}
             pxArtPrice* ArtPrice           () const {return ArtPrice_             ;}
             nMoney      PreisEKApo         ();
             nMoney      PreisVKApo         ();
             nMoney      PreisEKGrosso      ();
             nMoney      PreisEKGrossoNA    ();
             long        ArticleExpireDate  ();
             nMoney      SalesTaxRate       () {return SalesTaxRate_;               }
             char        CodeBlocage        () const {return CodeBlocage_         ; }
protected:
                      pxArticleInfo();

    void              Init();
    void              SalesTaxRate(const short TaxLevel);
/*----------------------------------------------------------------------------*/
/*  Data members.                                                             */
/*----------------------------------------------------------------------------*/
    short             BranchNo_;           // BranchNo
    long              ArticleNo_;          // Articlenumber
    long              Qty_;                // Articlenumber
    pxArtBase         *ArtBase_;           // ArtBase object
    pxArtPrice        *ArtPrice_;          // ArtPrice object
    pxSession*        Session_;            // Session
    nMoney            SalesTaxRate_;       // Sales Tax Rate
    char              CodeBlocage_;         // Code Blocage
private:
};
#endif
