#ifndef PXTTYPE_INC
#define PXTTYPE_INC

#include "pxbase/pxrecord.hpp"
#include <clock.hpp>

struct tZEITARTEN;

/*----------------------------------------------------------------------------*/
/*  Enumeration of Time Types                                                 */
/*----------------------------------------------------------------------------*/
    enum TimeType                       // time type definition
    {
        TypeNotUsed,                        // never use Null
        Type_ADS_Customer,                  // Customer Altern. Delivery Service Time
        Type_ADS_Company,                   // Company  Altern. Delivery Service Time
        Type_ADS_OPEN_FOR_ORDER_ENTRY = 5,  // Distributors opening times for order entry
        Type_ADS_NO_RESERVATION  =    6,    // No Stockreservation during this time.
        Type_ADS_ORD_DOUBLECONT  =    7,    // No Order doublecontrol during this Time
        Type_ADS_CLOSE_FOR_AOCL  =    8,    // Close times for aaorderclose
        Type_ADS_END_CONSOLIDATION  = 9,    // End time for order consolidation
        Type_ADS_REBATE_ORDER       = 11,   // Order Entry Time for order type RO(rebate order)
        Type_ADS_DEFER_ORDER        = 12,    // Order Entry Time for defer order
		TYPE_ADS_TIME_TRANSFER_ORDER = 13
    };


class pxTimeType : public pxDBRecord
{

public:
//  Constructors:
                      pxTimeType(pxSession *session);
//  Normal constructor
                      pxTimeType(pxTimeType& src);
//  Copy constructor
                      pxTimeType(pxSession *session, tZEITARTEN& src);
//  Constructs instance with values stored in src record
                      pxTimeType(pxSession *session,
                                          long    ZeitArt,
                                          const nString& ZeitSchluessel,
                                          const short WeekDay,
                                          short VertriebszentrumNr,
                                          DBAccessMode mode = cDBGET_READONLY);
//  Constructs instance by reading record from database

//  destructor:
                virtual  ~pxTimeType();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxTimeType&   operator=(const pxTimeType& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxTimeType&   operator=(const tZEITARTEN& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxTimeType&
                      Assign(pxTimeType& dest,
                             const tZEITARTEN& src);
    friend   tZEITARTEN&
                      Assign(tZEITARTEN& dest,
                             const pxTimeType& src);
//  Functions for data exchange between object and record.

    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;
//  Compare function for sorting pxTimeTypeList.

    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
//  Reads data from database

    virtual  int     Put();
//  Writes data to database


//  Queries:
    bool              IsForAllCustomer()         const
                      {return ( ZeitZusatz_ == '0');}
    bool              IsForAuxCustomer()           const
                      {return ( ZeitZusatz_ == '1');}
    bool              IsForOwnCustomer()           const
                      {return ( ZeitZusatz_ == '2');}

    bool              TimeInWindow();

    long             LFDNr    ()   const    {return LfdNr_;          }
    long             TimeType ()   const    {return ZeitArt_;        }
    const nString&    TimeKey  ()   const    {return ZeitSchluessel_; }
    const nString&    DayType  ()   const    {return TagesTyp_;       }
    const nClock&     WindowStart() const    {return ZeitBegin_;      }
    const nClock&     WindowEnd ()  const    {return ZeitEnde_;       }
    char             TimeInfo  ()  const    {return ZeitZusatz_;     }
    short            WeekDay()     const    {return WeekDay_;        }
protected:
    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);
    virtual  int     Insert(const void *record);
    virtual  int     Update(const void *record);
//  Database access functions.

    void              Init();
//  Initiates object's values.

    long             LfdNr_;           // Laufender Nummer
    long             ZeitArt_;         // Zeitart
    nString           ZeitSchluessel_;  // Zeitschluessel
    nString           TagesTyp_;        // Tagestyp
    nClock            ZeitBegin_;       // Zeit Betriebsanfang morgens
    nClock            ZeitEnde_;        // Zeit Betriebsende morgens
    char             ZeitZusatz_;      // Zeit Zusatz Info
    short            VertriebszentrumNr_;
    short            WeekDay_           ; // Day of Week

private:
    friend class pxTimeTypeList;
};

class pxTimeTypeList : public nDBRecordSet, public nDListCollect
{

public:
//  constructor:
                      pxTimeTypeList(pxSession *session);

//  destructor:
    virtual           ~pxTimeTypeList() {Clear();}

//  member functions:
             pxSession*
                      Session()      { return (pxSession*) DataBase();}

             size_t   Select ( const long type, const nString& key, short VertriebszentrumNr, const int count = 50 );

//  Reads all table entries with matching timetype,timekey and daytype into
//  the list.

             void     Clear()        {nDBRecordSet::Clear();}

//  Removes and deletes all list entries


             bool     TimeInWindow();
//  Check for current time within window.
       pxTimeType*    Find(const short FilialNr);
//  Check for current time within window.
             bool     FindDayOfWeek(const short dow);
//  Check for current time within window.

protected:

    virtual  nCollectable*
                      AddToList(const void *record, const int row);
    virtual  int     GetNext(const void* record, const int cursorid);
    virtual  int     StartBrowse(const void *keys, const int cursorid);
    virtual  int     EndBrowse(const int cursorid);

private:
    friend class pxTimeTypeListIter;
};

class pxTimeTypeListIter : public nDListCollectIter
{

public:
// constructors:
                      pxTimeTypeListIter(pxTimeTypeList& list)
                         : nDListCollectIter(list) {;}
// destructor:
    virtual           ~pxTimeTypeListIter() {;}


};
#endif
