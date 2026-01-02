/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

PXGOODSDELIVERY.HPP
Goods Delivery class.

REVISION HISTORY

18 April 2005 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXGOODSDELIVERY_DOTH
   #define PXGOODSDELIVERY_DOTH
#ifndef PXDELPOS_INC
   #include "pxdelpos.hpp"
#endif


class pxGoodsDelivery : public nCollectable
{

public:
// constructors:
                pxGoodsDelivery(pxVerbund::subsequentDelivery::pxDeliveryPos* delpos, const nString& KzKdKlasse, char NachLieferTyp );

                pxGoodsDelivery(const pxGoodsDelivery &src);

// destructor:
                virtual  ~pxGoodsDelivery();
/*@DS
PUBLIC MEMBER OPERATORS
*/
 //   pxGoodsDelivery&   operator=(const pxGoodsDelivery& src);
//  Assigns the values of 'src' to self and returns a reference to it.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    virtual  int     CompareTo(const nCollectable *that, void *p, const long lparm) const;
    pxVerbund::subsequentDelivery::pxDeliveryPos*   DeliveryPos()  {return DeliveryPos_;    }
    short            FilialNr()     {return FilialNr_;       }
    long             IDFNr()        {return IDFNr_;          }
    long             ArtikelNr()    {return ArtikelNr_;      }
    bool             IsArtReservation()  {return ArtReservation_;  }
    void             SetArtReservation() { ArtReservation_ = true;}
    char             NachLieferTyp()     {return NachLieferTyp_;   }
    bool             IsAvailableForOrderProcessing( pxSession* session, long kdauftragnr );

protected:
    pxVerbund::subsequentDelivery::pxDeliveryPos* DeliveryPos_;
    short          FilialNr_;
    long           IDFNr_;
    long           ArtikelNr_;
    nString        KzKdKlasse_;
    char           NachLieferTyp_;
    nDate          date_;
    bool           ArtReservation_;

private:
    friend class pxGoodsDeliveryList;
};

class pxGoodsDeliveryList : public nDListCollect
{
public:
// constructors:
                pxGoodsDeliveryList(pxSession* session, long ArtikelNr, short FilialNr);
                pxGoodsDeliveryList(pxSession* session, long ArtikelNr, short FilialNr, nString& KdAuftraArt);
                pxGoodsDeliveryList(pxSession* session, long kdAuftragNr, short FilialNr, long IdfNr, nString& KdAuftraArt);
// destructor:
                virtual  ~pxGoodsDeliveryList() {Clear();}
                
// member functions:
    void        Clear();
    long       ArtikelNr() const       {return ArtikelNr_;}
    pxSession*  Session()               {return session_;}
    short      FilialNr()              {return FilialNr_;}
    std::ifstream*   CMsgStream()      {return Session()->CMsgStream();}

protected:

private:
    pxSession   *session_;
    long        ArtikelNr_;
    short       FilialNr_;
    friend class pxDisInKindListIter;
};

class pxGoodsDeliveryListIter : public nDListCollectIter
{

public:
// constructors:
    pxGoodsDeliveryListIter(pxGoodsDeliveryList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxGoodsDeliveryListIter() {;}
};
#endif
