/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

 pxartcompack.hpp
 ARTCOMPACK   class

REVISION HISTORY

16 July 2009 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXARTCOMPACK_INC
#define PXARTCOMPACK_INC

#include "pxbase/pxrecord.hpp"

struct tARTCOMPACK;

class pxArtComPack : public pxDBRecord
{

public:

// constructors:
                pxArtComPack(pxArtComPack& src);
                pxArtComPack(pxSession *session);
                pxArtComPack(pxSession *session, tARTCOMPACK& src);
                pxArtComPack(pxSession *session, const pxArtComPack* src);

// destructor:
                virtual  ~pxArtComPack();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxArtComPack&   operator=(const pxArtComPack& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxArtComPack&   operator=(const tARTCOMPACK& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxArtComPack&
                Assign(pxArtComPack& dest, const tARTCOMPACK& src);
    friend   tARTCOMPACK&
                Assign(tARTCOMPACK& dest, const pxArtComPack& src);

    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;


//  Queries:
    long           ArticleNoPack()     {return ArticleNoPack_         ;}
    long           ArticleNoElement()  {return ArticleNoElement_      ;}
    long           Quantity()          {return Quantity_              ;}

// Set Methodes


protected:
    void       Init();

    long       ArticleNoPack_     ;      // Article number Pack(Steller(Pseudoartikelno)
    long       ArticleNoElement_  ;      // Article number Element
    long       Quantity_          ;      // Quantity to order of Article number Element

private:
    friend class pxArtComPackList;
};

class pxArtComPackList : public nDBRecordSet, public nDListCollect
{

public:

//  constructors:
                pxArtComPackList(pxSession *session);
//  destructor:
                virtual ~pxArtComPackList() {Clear();}
//  member functions:
                pxSession* Session()       { return (pxSession*) DataBase();}

    size_t      Select ( const int  count = 50 );
    size_t      Select ( const long  ArticleNoPack,
                         const int   count  = 100
                       );

    pxArtComPack* Find(const long ArticleNoElement );
// Some Queries
    void        Clear()        {nDBRecordSet::Clear();}


    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);


protected:

private:

    friend class pxArtComPackListIter;
};

class pxArtComPackListIter : public nDListCollectIter
{

public:
// constructors:
    pxArtComPackListIter(pxArtComPackList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxArtComPackListIter() {;}
};
#endif
