#include "pxrecord.h"
#include "pxsess.hpp"
#include "pxdevice.hpp"
#include "pxartbas.hpp"
#include "pxitem.hpp"
#include "pxorder.hpp"
#include "pxstktra.hpp"
#include "pxcomtyp.hpp"
#include "pxordtyp.hpp"
#include "pxcstot.hpp"
#include "pxcstbas.hpp"
#include "pxtcasession.hpp"
#include <logger/loggerpool.h>

extern bool pxGlobalInitTcaccess;

/*----------------------------------------------------------------------------*/
/*  Normal constructor.                                                       */
/*----------------------------------------------------------------------------*/
pxTcaSession :: pxTcaSession
(
    const short BranchNo               // Branchnumber
)
{
    Init();
    BranchNo_         = BranchNo;
}

/*----------------------------------------------------------------------------*/
/*  Copy constructor.                                                         */
/*----------------------------------------------------------------------------*/
pxTcaSession :: pxTcaSession
(
    const pxTcaSession& src
)
{
    (*this) = src;
}

/*----------------------------------------------------------------------------*/
/*  Destructor.                                                               */
/*----------------------------------------------------------------------------*/
pxTcaSession :: ~pxTcaSession()
{
    ;
}
/*----------------------------------------------------------------------------*/
/*  Assign the values of the 'src' instance to self.                          */
/*----------------------------------------------------------------------------*/
pxTcaSession&
pxTcaSession :: operator=( const pxTcaSession& src)
{
    BranchNo_         = src.BranchNo_       ;
    TcaConfigName_    = src.TcaConfigName_  ;
    TcaHostIp_        = src.TcaHostIp_      ;
    TcaHostPort_      = src.TcaHostPort_    ;
    TcaStartTransId_  = src.TcaStartTransId_;
    TcaUser_          = src.TcaUser_        ;
    TcaPassWord_      = src.TcaPassWord_    ;
    return *this;
}
/*----------------------------------------------------------------------------*/
/*  CompareTo function redefined from nCollectable.                           */
/*  Ensures pxRangeCollec list objects being inserted in the following        */
/*  ascending  sequence:                                                      */
/*  BranchNo                                                                  */
/*----------------------------------------------------------------------------*/
int
pxTcaSession :: CompareTo
(
    const nCollectable   *That,
          void           *,
    const long
)   const
{
    pxTcaSession *that = (pxTcaSession*)That;
    int retval = (BranchNo_ == that->BranchNo_) ? 0
                  : (BranchNo_ > that->BranchNo_ ? 1 : -1);

    return retval;
}
/*----------------------------------------------------------------------------*/
/*  Init                                                                      */
/*----------------------------------------------------------------------------*/
void
pxTcaSession :: Init
(
)
{
    BranchNo_ = 0;
    memset(conn_.config,0,sizeof(conn_.config));
    memset(conn_.ipaddr,0,sizeof(conn_.ipaddr));
    memset(conn_.port,0,sizeof(conn_.port));
    memset(conn_.starttrans,0,sizeof(conn_.starttrans));
    memset(conn_.user,0,sizeof(conn_.user));
    memset(conn_.passwd,0,sizeof(conn_.passwd));
    memset(conn_.cicsname,0,sizeof(conn_.cicsname));
    conn_.slot = 0;
    conn_.open = 0;

}

/*----------------------------------------------------------------------------*/
/*  Clear entire list.                                                        */
/*----------------------------------------------------------------------------*/
void
pxTcaSessionList :: Clear()
{

    pxTcaSession  *curp;
    pxTcaSessionListIter cursor(*this);
    while ( (curp = (pxTcaSession*) ++cursor) != NULL )
    {
       cursor.Remove();
       delete curp;
    }
}

/*----------------------------------------------------------------------------*/
/*  Find returns pxTcaSession pointer or NULLP                                */
/*----------------------------------------------------------------------------*/
pxTcaSession*
pxTcaSessionList :: Find
(
    const short BranchNo
)
{
    pxTcaSession  *curp;
    pxTcaSessionListIter cursor(*this);
    while ( (curp = (pxTcaSession*) ++cursor) != NULL )
    {
       if (curp->BranchNo() == BranchNo )
       {
          break;
       }
    }
    return curp;
}
/*----------------------------------------------------------------------------*/
/*  ConnectToCics                                                             */
/*----------------------------------------------------------------------------*/
int
pxTcaSession :: ConnectToCics
(
)
{
    int retval = 0;
    int  Max_Open_Count = 3;

    // Init Tcaccess
    if ( !pxGlobalInitTcaccess )
    {
       initTcaChild();
       pxGlobalInitTcaccess = true;
    }

    if (ErrorMsg_  && strlen(ErrorMsg_))
    {
       retval = DisconnectFromCics();
       Init();
       ClearError();
    }


    if (  isConnOpen(&conn_) )
    {
       retval = IsCicsAvailable();
       return retval;
    }

    setConnParam((char*)TcaConfigName_,
                 (char*)TcaHostIp_,
                 (char*)TcaHostPort_,
                 (char*)TcaStartTransId_,
                 (char*)TcaUser_,
                 (char*)TcaPassWord_,
                 &conn_);

    // Connection to CICS
    retval = IsCicsAvailable();
    if (retval == 0 )
    {
       return retval;
    }

    retval = isConnOpen(&conn_);
    if (retval != 0)
       return retval;


    for ( int Open_Count = 0; Open_Count <= Max_Open_Count; Open_Count++ )
    {
       retval = openConn(&conn_, ErrorMsg_);
       if ( retval == 0 )
       {
          #ifdef unix
          {
             sleep( 1 );
          }
          #endif
       }
       else
       {
          break;
       }
    }

    if (ErrorMsg_  && strlen(ErrorMsg_))
    {
        std::stringstream ss;
        ss << "pxTcaSession::ConnectToCics()" << ErrorMsg_;
        BLOG_ERROR(libcsc::LoggerPool::getLoggerTcaSession(), ss.str());
    }
    retval = isConnOpen(&conn_);

    return retval;
}
/*----------------------------------------------------------------------------*/
/*  SendDataToCics                                                            */
/*----------------------------------------------------------------------------*/
int
pxTcaSession :: SendDataToCics
(
    const nString&  CallStmt,
    char *   Result,
    long     ResultLen
)
{
    int retval = 0;
    ClearError();

    std::stringstream ss0;
    ss0 << "pxTcaSession::SendDataToCics(CallStmt:" << CallStmt() << ")";
    BLOG_DEBUG(libcsc::LoggerPool::getLoggerTcaSession(), ss0.str());

    if ( isConnOpen(&conn_) )
    {
       retval = callCics(&conn_, CallStmt, Result, ResultLen, ErrorMsg_);

        std::stringstream ss1;
        ss1 << "pxTcaSession::SendDataToCics(Result:" << Result << ")";
        BLOG_DEBUG(libcsc::LoggerPool::getLoggerTcaSession(), ss1.str());

       if ( retval == 0  && ErrorMsg_  && strlen(ErrorMsg_))
        {
            std::stringstream ss2;
            ss2 << "pxTcaSession::SendDataToCics()" << ErrorMsg_;
            BLOG_ERROR(libcsc::LoggerPool::getLoggerTcaSession(), ss2.str());
        }
    }
    return retval;
}
/*----------------------------------------------------------------------------*/
/*  DisconnectFromCics                                                        */
/*----------------------------------------------------------------------------*/
int
pxTcaSession :: DisconnectFromCics
(
)
{
    int retval = 0;

    ClearError();

    if ( isConnOpen(&conn_) )
        retval = closeConn(&conn_, ErrorMsg_);

    if (ErrorMsg_  && strlen(ErrorMsg_))
    {
        std::stringstream ss;
        ss << "pxTcaSession::DisconnectFromCics()" << ErrorMsg_;
        BLOG_ERROR(libcsc::LoggerPool::getLoggerTcaSession(), ss.str());
        retval=0;
    }
    return retval;
}
/*----------------------------------------------------------------------------*/
/*  IsCicsAvailable                                                           */
/*----------------------------------------------------------------------------*/
int
pxTcaSession :: IsCicsAvailable
(
)
{
    int  retval = 0;
    int  cDelay = 6;          // delay of 6 seconds

    retval = isCicsAvail(&conn_, cDelay, ErrorMsg_);

    if (ErrorMsg_  && strlen(ErrorMsg_))
    {
        std::stringstream ss;
        ss << "pxTcaSession::IsCicsAvailable()" << ErrorMsg_;
        BLOG_ERROR(libcsc::LoggerPool::getLoggerTcaSession(), ss.str());
        retval = 0;
    }
    return retval;
}

/*----------------------------------------------------------------------------*/
/*  GetErrorMessage                                                           */
/*----------------------------------------------------------------------------*/
nString
pxTcaSession :: GetErrorMessage
(
)
{
    nString msg;
    if (ErrorMsg_  && strlen(ErrorMsg_))
    {
      msg = ErrorMsg_;
    }
    return msg;	
}

void pxTcaSession::ClearError() const
{
    if (ErrorMsg_  && strlen(ErrorMsg_))
    {
       memset(ErrorMsg_,0,sizeof(ErrorMsg_));
    }
}

