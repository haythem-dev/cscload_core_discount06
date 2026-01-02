/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

PXDONEPROMOQUOTAS

REVISION HISTORY

08 May 2012 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXDONEPROMOQUOTAS_DOTH
   #define PXDONEPROMOQUOTAS_DOTH

class pxDonePromoQuotas : public nCollectable
{

public:
// constructors:
                pxDonePromoQuotas(const short  PromotionNo,
                                  const long   ArticleNo
                                  );

                pxDonePromoQuotas(const pxDonePromoQuotas &src);

// destructor:
                virtual  ~pxDonePromoQuotas();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxDonePromoQuotas&   operator=(const pxDonePromoQuotas& src);
//  Assigns the values of 'src' to self and returns a reference to it.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;


// Some Queries
    short      PromotionNo()         { return PromotionNo_       ;}
    long       ArticleNo()           { return ArticleNo_         ;}

// Field updates
    void        SetArticleNo(long artno)
                {ArticleNo_ = artno;}
    void        SetPromotionNo(short no)
                {PromotionNo_ = no;}

protected:
    short      PromotionNo_;         // PromotionNo
    long       ArticleNo_;           // Articlenumber

private:
    friend class pxDonePromoQuotasList;
};

class pxDonePromoQuotasList : public nDListCollect
{

public:
// constructors:

// destructor:
    virtual  ~pxDonePromoQuotasList() {Clear();}
// member functions:
    void            Clear();
    bool            Find(const short PromotionNo, const long ArticleNo);
    int             DeleteEntry(const short PromotionNo, const long ArticleNo);

private:
    friend class pxDonePromoQuotasListIter;
};

class pxDonePromoQuotasListIter : public nDListCollectIter
{
public:
// constructors:
    pxDonePromoQuotasListIter(pxDonePromoQuotasList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxDonePromoQuotasListIter() {;}
};
#endif
