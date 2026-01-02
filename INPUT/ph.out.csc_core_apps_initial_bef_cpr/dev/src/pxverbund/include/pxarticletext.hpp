/*(c)
 ********************* PHARMX Customer Order Entry Server *********************

pxarticletext.hüü
pxArticleText Class.

REVISION HISTORY

29 April 2005 V1.00 REV 00 written by Ysbrand Bouma.
*/

#ifndef PXARTICLETEXT_INC
   #define PXARTICLETEXT_INC

#include "pxbase/pxrecord.hpp"

struct tARTICLETEXT;

class pxArticleText : public pxDBRecord
{

public:


// constructors:
                pxArticleText(pxArticleText& src);
                pxArticleText(pxSession *session);
                pxArticleText(pxSession *session, tARTICLETEXT& src);
                pxArticleText(pxSession *session, const short TextKey);
// destructor:
                virtual  ~pxArticleText();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxArticleText&   operator=(const pxArticleText& src);
//  Assigns the values of 'src' to self and returns a reference to it.

    pxArticleText&   operator=(const tARTICLETEXT& src);
//  Assigns the values of the record structure 'src' to self and returns a
//  reference to self.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    friend   pxArticleText&
                Assign(pxArticleText& dest, const tARTICLETEXT& src);
    friend   tARTICLETEXT&
                Assign(tARTICLETEXT& dest, const pxArticleText& src);

    virtual  int     Get(DBAccessMode mode = cDBGET_READONLY);
    virtual  int     Put();
    virtual  int     Delete();

    virtual  int     Read(const void *record);
    virtual  int     ReadLock(const void *record);
    virtual  int     Insert(const void *record);
    virtual  int     Update(const void *record);
    virtual  int     Delete(const void *record);

//  Queries:
    short            BranchNo()           {return BranchNo_           ;}
    short            TextKey()            {return TextKey_            ;}
    nString&          Text ()              {return Text_               ;}
    char             DisplayOnScreen()    {return DisplayOnScreen_    ;}
protected:
    void        Init();

    short      BranchNo_          ;      // Branchnumber
    short      TextKey_           ;      // Textkey
    nString     Text_              ;      // Text
    char       DisplayOnScreen_   ;      // KZ

private:

};
#endif
