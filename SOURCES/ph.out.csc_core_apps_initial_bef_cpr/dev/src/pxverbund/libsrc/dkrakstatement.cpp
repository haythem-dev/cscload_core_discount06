#include "dkrakstatement.hpp"

#include "pxtcadef.h"
#include "pxtcarecord.h"

#include <string.hpp>
#include <date.hpp>
#include <money.hpp>
#include <nntypes.h>

#include <cstring>
#include <sstream>
#include <iomanip>
#include <boost/numeric/conversion/cast.hpp>

DKRAKStatement::DKRAKStatement() : StatementBuffer_( new char[ sizeof(tVI52) ] )
{
    // initialize buffer
    VK52 = (tVI52P) StatementBuffer_;
    InitBuf( &VK52->callstmt, sizeof(tTCACALLSTMT) );
    InitBuf( &VK52->header,   sizeof(tTCAHEADER) );
    InitBuf( &VK52->restend,  sizeof(VK52->restend) );
    InitBuf( &VK52->line,     sizeof(tCVI522_RECORD) );

    // fill in static data which is always the same
    CopyToBuf( VK52->callstmt.statement,  nString(cTCA_CALL_STMT),       mSIZEOF(tTCACALLSTMT, statement) );
    VK52->callstmt.quoteleft = '\'';
    CopyToBuf( VK52->callstmt.ModuleName, nString(cTCA_PROGRAM_DKRAK),   mSIZEOF(tTCACALLSTMT, ModuleName) );
    CopyToBuf( VK52->callstmt.sepright,   nString(cTCA_SEPK),            mSIZEOF(tTCACALLSTMT, sepright) );

    CopyToBuf( VK52->header.BufLen,       nString(cTCA_BUFFERLGT_DKRAK), mSIZEOF(tTCAHEADER, BufLen) );
    CopyToBuf( VK52->restend,             nString(cTCA_CALL_END),        mSIZEOF(tVI52, restend) );
    VK52->line.LockSwitch = cTCA_LOCKSWITCHCODE;
}

DKRAKStatement::~DKRAKStatement()
{
    delete[] StatementBuffer_;
}

void DKRAKStatement::SetBranchNo(short branchNo)
{
    CopyToBuf( VK52->line.BranchNo, branchNo, mSIZEOF(tCVI522_RECORD, BranchNo) );
}

void DKRAKStatement::SetCustomerNo(long customerNo)
{
    CopyToBuf( VK52->line.IDFNr, customerNo, mSIZEOF(tCVI522_RECORD, IDFNr) );
}

void DKRAKStatement::SetDateFrom(const nDate& date)
{
    CopyToBuf( VK52->line.DateFrom, date.GetYYYYMMDD() - cTCA_CENTURY_DEF, mSIZEOF(tCVI522_RECORD, DateFrom) );
}

void DKRAKStatement::SetOrderNo( long orderNo )
{
    CopyToBuf( VK52->line.OriginOrderNo, orderNo, mSIZEOF(tCVI522_RECORD, OriginOrderNo) );
}

nString DKRAKStatement::ToString()
{
    return StatementBuffer_;
}

void DKRAKStatement::InitBuf( void* position, size_t length)
{
    memset( position, '0', length);
}

void DKRAKStatement::CopyToBuf( char* position, const nString& source, size_t length )
{
    std::ostringstream tmp;
    tmp << std::setw(boost::numeric_cast<int>(length)) << std::setfill('0') << source;
    memcpy( position, tmp.str().c_str(), length);
}

void DKRAKStatement::CopyToBuf( char* position, long source, size_t length )
{
    std::ostringstream tmp;
    tmp << std::setw(length) << std::setfill('0') << source;
    memcpy( position, tmp.str().c_str(), length );
}

void  DKRAKStatement::CopyToBuf( char* position, const nMoney& source, size_t length )
{
    char temp[20];
    sprintf(temp,"%09.f",static_cast<double>( source ) * 100 );

    //std::ostringstream tmp;
    //tmp << std::setw(length) << std::setfill('0') << ( static_cast<double>( source ) * 100 );
    memcpy( position, (char*)temp, length );
}
