#ifndef NERROR_INC
#define NERROR_INC


#include "string.hpp"
#include "message.hpp"


enum nErrorState
{
    nSTATE_GOOD       =  0,
    nSTATE_CONDITION  =  4,             // just pay attention
    nSTATE_ERROR      =  8,             // this is an error, but it may be recovered
    nSTATE_FATALERROR = 12,             // unrecoverable fatal error, abend recommended
    nSTATE_ABEND      = 16              // abend exit performed
};

class nError
{

public:

                nError()                { ClearError(); }
                nError(const nError& src);
                ~nError();

enum nErrorType
{
    nERRTYPE_UNKNOWN ,                  // unknown error type
    nERRTYPE_ALLOC   ,                  // memory allocation error
    nERRTYPE_FILE    ,                  // file error
    nERRTYPE_DATABASE,                  // data base error
    nERRTYPE_EXTERNAL,                  // external error, i.e. an invalid call
    nERRTYPE_INTERNAL,                  // internal system error
    nERRTYPE_EVENTLOG = 4096            // no error, just an event log message
};

protected:
    int         SetError(   const nMessage& msg,
                            const int num,
                            nErrorType t,
                            nErrorState s = nSTATE_ERROR
                        );

public:
// overloaded assignment:
    nError&     operator=(const nError& src);
    int         AllocError(const nMessage& msg, const int errornum = 0)
                                        {return SetError(msg, errornum, nERRTYPE_ALLOC,
                                                         nSTATE_FATALERROR);}
    void        ClearError();

    int         DBCondition(const nMessage& msg, const int errornum = 0)
                                        {return SetError(msg, errornum, nERRTYPE_DATABASE,
                                                         nSTATE_CONDITION);}
    int         DBError(const nMessage& msg, const int errornum = 0)
                                        {return SetError(msg, errornum, nERRTYPE_DATABASE);}

    int         ExternalCondition(const nMessage& msg, const int errornum = 0)
                                        {return SetError(msg, errornum, nERRTYPE_EXTERNAL,
                                                         nSTATE_CONDITION);}
    int         ExternalCondition(std::ifstream *stream, const int errornum, ...);

    int         ExternalError(const nMessage& msg, const int errornum = 0)
                                        {return SetError(msg, errornum, nERRTYPE_EXTERNAL);}
    int         ExternalError(std::ifstream *stream, const int errornum, ...);

    int         FileCondition(const nMessage& msg, const int errornum = 0)
                                        {return SetError(msg, errornum, nERRTYPE_FILE,
                                                         nSTATE_CONDITION);}
    int         FileError(const nMessage& msg, const int errornum = 0)
                                        {return SetError(msg, errornum, nERRTYPE_FILE);}

    int         InternalCondition(const nMessage& msg, const int errornum = 0)
                                        {return SetError(msg, errornum, nERRTYPE_INTERNAL,
                                                         nSTATE_CONDITION);}
    int         InternalError(const nMessage& msg, const int errornum = 0)
                                        {return SetError(msg, errornum, nERRTYPE_INTERNAL);}
    int         InternalError(std::ifstream *stream, const int errornum, ...);

    int         LogEvent(const nMessage& msg, const int errornum = 0)
                                        {return SetError(msg, errornum, nERRTYPE_EVENTLOG,
                                                         nSTATE_GOOD);}
    int         LogEvent(std::ifstream *stream, const int errornum, ...);

	virtual     void WriteLog(const nString& /*message*/, nErrorState /*state*/, int /*msgid*/) {}

    nError&     Error()                 { return *this;}
    int         ErrorNumber() const     { return errornum_; }
    const char* ErrorMsg()    const     { return msg_(); }
    const nString& ErrorString() const  { return msg_;}
    int         ErrorState()  const     { return state_; }
    int         ErrorState(nErrorState s)  {return (state_ = s);}
    int         ErrorType()   const     { return type_; }
    bool        IsBadState()  const     { return state_ >  nSTATE_CONDITION; }
    bool        IsConditionState() const { return state_ == nSTATE_CONDITION; }
    bool        IsGoodState() const     { return state_ == nSTATE_GOOD; }
    bool        IsFatalErrorState() const { return state_ >= nSTATE_FATALERROR; }
    bool        IsAbendState() const    { return state_ >= nSTATE_ABEND; }

private:
    nString     msg_;                   // Error message text
    int         errornum_;              // error number
    nErrorState state_;                 // error state code
    nErrorType  type_;                  // error type

};

inline std::ostream& operator<<(std::ostream& strm, nError& e)
                                        { return (strm << e.ErrorString());}
#endif
