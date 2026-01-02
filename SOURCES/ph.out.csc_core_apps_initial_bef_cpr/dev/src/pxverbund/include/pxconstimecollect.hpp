/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

PXCONSTIMECOLLECT

REVISION HISTORY

05 May 2006 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXCONSTIMECOLLECT_DOTH
#define PXCONSTIMECOLLECT_DOTH

#include <dlistcol.hpp>
#include <string.hpp>
#include <date.hpp>
#include <clock.hpp>

class pxConsTimeCollect : public nCollectable
{

public:
// constructors:
                pxConsTimeCollect(const short   BranchNo,
                                  const long    CustomerNo,
                                  const nString& TourId,
                                  const nDate&   DatumKommi,
                                  const nClock&  ConsTime
                              );

                pxConsTimeCollect(const pxConsTimeCollect &src);

// destructor:
                virtual  ~pxConsTimeCollect();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxConsTimeCollect&   operator=(const pxConsTimeCollect& src);
//  Assigns the values of 'src' to self and returns a reference to it.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;


// Some Queries
    short      BranchNo()            { return BranchNo_;          }
    long       CustomerNo()          { return CustomerNo_;        }
    nString&    TourId()              { return TourId_;            }
    nDate&      DatumKommi()          { return DatumKommi_;        }
    nClock&     ConsTime()            { return ConsTime_;          }

protected:
    short      BranchNo_;            // Branchno
    long       CustomerNo_;          // Customernumber
    nString     TourId_;              // Route number
    nDate       DatumKommi_;          // Datumkommi
    nClock      ConsTime_;            // Consolidation Time

private:
    friend class pxConsTimeCollectList;
};

class pxConsTimeCollectList : public nDListCollect
{

public:
// constructors:

// destructor:
                virtual  ~pxConsTimeCollectList() {Clear();}
// member functions:
    void        Clear();
    bool        Find(const long CustomerNo, const nString& TourId, const nClock& ConsTime);

protected:
private:
    friend class pxConsTimeCollectListIter;
};

class pxConsTimeCollectListIter : public nDListCollectIter
{

public:
// constructors:
    pxConsTimeCollectListIter(pxConsTimeCollectList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxConsTimeCollectListIter() {;}
};
#endif
