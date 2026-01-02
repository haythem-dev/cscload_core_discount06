/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

Implementation of class pxArticleText  methods.

REVISION HISTORY

29 March 2005 V1.00 REV 00 written by Ysbrand Bouma.
*/

#include "pxarticletext.hpp"
#include <pxdbxx.h>
#include "pxsess.hpp"

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxArticleText :: pxArticleText
(
    pxSession   *session
)
    : pxDBRecord(session)
{
    Init();
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxArticleText :: pxArticleText
(
    pxArticleText& src
)
    : pxDBRecord(src.Session())
{
    Init();
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Use tARTICLETEXT structure to construct this instance.                    */
/*----------------------------------------------------------------------------*/
pxArticleText :: pxArticleText
(
    pxSession   *session,
    tARTICLETEXT& src
)
    : pxDBRecord(session)
{
    Init();
    (*this) = src;
}
/*----------------------------------------------------------------------------*/
/*  Construct this object                                                     */
/*----------------------------------------------------------------------------*/
pxArticleText :: pxArticleText
(
    pxSession      *session,
    const short   TextKey
)
    : pxDBRecord(session)
{
    Init();
    TextKey_       = TextKey;
}
/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxArticleText :: ~pxArticleText()
{
    ;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' object to a tARTICLETEXT structure.      */
/*----------------------------------------------------------------------------*/
tARTICLETEXT&
Assign
(
    tARTICLETEXT&           dest,
    const pxArticleText&       src
)
{
    dest.BranchNo                  = src.BranchNo_       ;
    dest.TextKey                   = src.TextKey_        ;
    dest.DisplayOnScreen           = src.DisplayOnScreen_;
    dest.Text[0] = ' ';
    src.Text_.GetData(dest.Text);

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' tARTICLETEXT structure to                    */
/*  a pxArticleText object.                                                     */
/*----------------------------------------------------------------------------*/
pxArticleText&
Assign
(
    pxArticleText&              dest,
    const tARTICLETEXT&    src
)
{
    dest.BranchNo_                 = src.BranchNo        ;
    dest.TextKey_                  = src.TextKey         ;
    dest.DisplayOnScreen_          = src.DisplayOnScreen ;
    dest.Text_                     = src.Text            ;

    return dest;
}

/*----------------------------------------------------------------------------*/
/*  Initialize object.                                                        */
/*----------------------------------------------------------------------------*/
void
pxArticleText :: Init()
{
    tARTICLETEXT    record;
    memset(&record, 0 , sizeof(tARTICLETEXT));
    Assign(*this, record);
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*  The values of the source instance are exported to the                     */
/*  tARTICLETEXT struct and then imported to self.                       */
/*----------------------------------------------------------------------------*/
pxArticleText&
pxArticleText :: operator=( const pxArticleText& src)
{
    tARTICLETEXT record;               // used to export the data of 'src'
    Assign(*this, Assign(record, src));
    return *this;
}

/*----------------------------------------------------------------------------*/
/*  Assign the values of the tARTICLETEXT structure 'src' to             */
/*  this instance.                                                            */
/*----------------------------------------------------------------------------*/
pxArticleText&
pxArticleText :: operator=( const tARTICLETEXT& src)
{
    return Assign(*this, src);
}

/*----------------------------------------------------------------------------*/
/*  Get an object from the data source.                                       */
/*----------------------------------------------------------------------------*/
int
pxArticleText :: Get
(
    DBAccessMode mode
)

{
    tARTICLETEXT record;
    memset(&record, 0, sizeof(tARTICLETEXT));
    record.TextKey        = TextKey_ ;
    int retval = ( mode == cDBGET_FORUPDATE ) ?
                    nDBReadLock(&record) : nDBRead(&record);
    if (!retval)
       (*this)= record;        // import the data from tARTICLETEXT struct
    //else if ( retval > cDBXR_NORMAL )
    //   ExternalCondition(CMsgStream(),
    //                     CMSG_AD_DELPOS_NOTFOUND, KdAuftragNr_,PosNr_);
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  Put this object into the data source.                                     */
/*----------------------------------------------------------------------------*/
int
pxArticleText :: Put
(
)
{
    tARTICLETEXT record;
    memset(&record, 0, sizeof(tARTICLETEXT));
    Assign(record, *this);
    return nDBWrite(&record, sizeof(tARTICLETEXT));
}
/*----------------------------------------------------------------------------*/
/*  Delete this object from the data source.                                  */
/*----------------------------------------------------------------------------*/
int
pxArticleText :: Delete
(
)
{
    tARTICLETEXT record;
    memset(&record, 0, sizeof(tARTICLETEXT));
    Assign(record, *this);
    return nDBDelete(&record);
}

/*----------------------------------------------------------------------------*/
/*  Redefine virtual functions inherited from pxDBRecord.                      */
/*----------------------------------------------------------------------------*/
int
pxArticleText :: Read
(
    const void  *record
)
{
    return pxArticleTextRead((tARTICLETEXT*)record);
}

int
pxArticleText :: ReadLock
(
    const void  *record
)
{
    return pxArticleTextReadLock((tARTICLETEXT*)record);
}

int
pxArticleText :: Update
(
    const void  *record
)
{
    return pxArticleTextUpdate((tARTICLETEXT*)record);
}

int
pxArticleText :: Delete
(
    const void  *record
)
{
    return pxArticleTextDelete((tARTICLETEXT*)record);
}

int
pxArticleText :: Insert
(
    const void  *record
)
{
    return pxArticleTextInsert((tARTICLETEXT*)record);
}


