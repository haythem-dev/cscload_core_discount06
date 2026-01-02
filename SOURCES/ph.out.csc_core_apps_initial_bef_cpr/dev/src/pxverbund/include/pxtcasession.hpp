#ifndef PXTCASESSION_DOTH
#define PXTCASESSION_DOTH

#include "tcawrap.h"


class pxTcaSession : public nCollectable
{

public:
// constructors:
                pxTcaSession(const short  BranchNo);

                pxTcaSession(const pxTcaSession &src);

// destructor:
                virtual  ~pxTcaSession();
/*@DS
PUBLIC MEMBER OPERATORS
*/
    pxTcaSession&   operator=(const pxTcaSession& src);
//  Assigns the values of 'src' to self and returns a reference to it.


/*@DS
PUBLIC MEMBER FUNCTIONS
*/
    virtual  int      CompareTo(const nCollectable *that, void *p,
                                const long lparm) const;

// Some Queries
    short             BranchNo()        const    { return BranchNo_;          }
    const nString&    TcaConfigName()   const    { return TcaConfigName_;     }
    const nString&    TcaHostIp()       const    { return TcaHostIp_;         }
    const nString&    TcaHostPort()     const    { return TcaHostPort_;       }
    const nString&    TcaStartTransId() const    { return TcaStartTransId_;   }
    const nString&    TcaUser()         const    { return TcaUser_;           }
    const nString&    TcaPassWord()     const    { return TcaPassWord_;       }

    CicsConnParam& conn() { return conn_;}

// some set methodes
   void         SetBranchNo( const short BranchNo)
                { BranchNo_ = BranchNo;        }
   void         SetTcaConfigName( const nString& Name)
                { TcaConfigName_ = Name;       }
   void         SetTcaHostIp( const nString& IP)
                { TcaHostIp_ = IP;            }
   void         SetTcaHostPort( const nString& Port)
                { TcaHostPort_ = Port;         }
   void         SetTcaStartTransId( const nString& TransId)
                { TcaStartTransId_ = TransId;  }
   void         SetTcaUser( const nString& User)
                { TcaUser_ = User;             }
   void         SetTcaPassWord( const nString& PassWord)
                { TcaPassWord_ = PassWord;     }

// some Tcaccess Methodes
   int          ConnectToCics();
   int          DisconnectFromCics();
   int          SendDataToCics(const nString& callstmt, char* result, long resultsize);
   int          IsCicsAvailable();
   nString      GetErrorMessage();

protected:
    void        Init();
    void        ClearError() const;

    short       BranchNo_;            // Branchno

    nString     TcaConfigName_;       // TcaConfigName
    nString     TcaHostIp_;           // TcaHostIp adress
    nString     TcaHostPort_;         // TcaHostPort
    nString     TcaStartTransId_;     // TcaStartTransaction Id
    nString     TcaUser_;             // TcaUser
    nString     TcaPassWord_;         // TcaPassWord

// some Tcaccess members
    CicsConnParam   conn_;
    mutable char ErrorMsg_[256];

private:
    friend class pxTcaSessionList;
};

class pxTcaSessionList : public nDListCollect
{

public:
// constructors:

// destructor:
                virtual  ~pxTcaSessionList() {Clear();}
// member functions:
    void        Clear();
    pxTcaSession*    Find(const short BranchNo);

protected:
private:
    friend class pxTcaSessionListIter;
};

class pxTcaSessionListIter : public nDListCollectIter
{

public:
// constructors:
    pxTcaSessionListIter(pxTcaSessionList& list) : nDListCollectIter(list) {;}
// destructor:
    virtual  ~pxTcaSessionListIter() {;}
};
#endif
