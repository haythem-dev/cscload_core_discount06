#include "infrastructure/accessor/sap/sapbalancecollectionacc.h"
#include "infrastructure/accessor/sap/sapbalancecollectionacc_definitions.h"
#include "infrastructure/accessor/sap/sap_definitions.h"
#include "infrastructure/accessor/backup_settings.h"

#include "infrastructure/parameter/iaccparameter.h"

#include "loggerpool/libcsc_deli_loggerpool.h"
#include "domainmodule/libcsc_deli_properties_definitions.h"

#include <boost/filesystem.hpp>
#include <fstream>

namespace libcsc_deli
{
namespace infrastructure
{
namespace accessor
{
namespace sap
{
    SAPBalanceCollectionACC::SAPBalanceCollectionACC()
        : AccessorBase( lit::SAP_BALANCE_COLLECTION_ACC )
    {
    }

    SAPBalanceCollectionACC::~SAPBalanceCollectionACC()
    {
    }

    void SAPBalanceCollectionACC::registerAccessorMethods( AccMethodCaller& accMethodCaller )
    {
        accMethodCaller.registerAccessMethod( lit::READ_SAP_BALANCE_COLLECTION, &SAPBalanceCollectionACC::readSAPBalanceFromFile, this );
        accMethodCaller.registerAccessMethod( lit::BACKUP_SAP_BALANCE, &SAPBalanceCollectionACC::backupSAPBalanceFile, this );
    }

    void SAPBalanceCollectionACC::setupPropertyDescriptionList( basar::property::PropertyDescriptionListRef pdl ) const
    {
        pdl.push_back( properties::PARTNER_NO     );
        pdl.push_back( properties::CUSTOMER_NO    );
        pdl.push_back( properties::SUM_DEBIT_SIDE );
        pdl.push_back( properties::DATE           );
    }

    void SAPBalanceCollectionACC::injectACCParameter( parameter::IACCParameterPtr accParam )
    {
        m_AccParameter = accParam;
    }

    parameter::IACCParameterPtr SAPBalanceCollectionACC::getAccParameter() const
    {
        CHECK_INSTANCE_EXCEPTION( m_AccParameter.get() );
        return m_AccParameter;
    }

    const basar::db::aspect::ExecuteResultInfo SAPBalanceCollectionACC::readSAPBalanceFromFile( basar::db::aspect::AccessorPropertyTable_YIterator, 
                                                                                                bool /* flagExcept */ )
    {
        METHODNAME_DEF( SAPBalanceCollectionACC, readSAPBalanceFromFile );
        static const log4cplus::Logger& logger = libcsc_deli::LoggerPool::getLoggerAccessors();
        BLOG_TRACE_METHOD( logger, fun );

        const basar::VarString accArea = getAccParameter()->getParameterValue( lit::SAP_ACCOUNTING_AREA );

        std::ifstream file( getAccParameter()->getParameterValue( lit::SAP_BALANCE_FILE ).c_str(), std::ifstream::in );
        basar::db::aspect::ExecuteResultInfo resInfo;
        for( basar::VarString line; std::getline( file, line ); resInfo.m_affectedRows++ )
        {
            if( line.length() >= m_LineLength )  // ignore lines not matching length
            {
                try
                {
                    const basar::VarString accountingArea = line.substr(  0,  4 );
                    // orig. DEBNR  = line.substr(  4, 10 ).stoi()
                    // orig. BRANCH = line.substr( 14,  2 ).stoi()
                    const basar::Int32 customerNo         = line.substr( 16,  7 ).stoi();
                    basar::VarString partnerNo            = line.substr( 23,  9 ); partnerNo.trim( basar::VarString::ALL );
                    basar::VarString sumDebitSide         = line.substr( 32, 17 ); sumDebitSide.trim( basar::VarString::ALL );
                    // orig PDATE = line.substr( 49, 8 )
                    basar::VarString dDate                = line.substr( 57,  8 );

                    if( accountingArea == accArea )
                    {
                        basar::db::aspect::AccessorPropertyTable_YIterator yit = getPropertyTable().insert( basar::FOR_CLEAN );
                    
                        yit.setInt32  ( properties::CUSTOMER_NO,    customerNo );
                        yit.setInt32  ( properties::DATE,           dDate.stoi() );
                        yit.setDecimal( properties::SUM_DEBIT_SIDE, basar::Decimal( sumDebitSide ) );

                        if( ! partnerNo.empty() ) // store partner no if set
                        {
                            yit.setInt32( properties::PARTNER_NO, partnerNo.stoi() );
                        }
                    }
                }
                catch( std::exception& e )
                {
                    std::ostringstream msg;
                    msg << "Exception parsing string '" << line << "': " << e.what();
                    BLOG_ERROR( logger, msg.str() );
                }
            } // end if
        } // end for

        return resInfo;
    }

    const basar::db::aspect::ExecuteResultInfo SAPBalanceCollectionACC::backupSAPBalanceFile( basar::db::aspect::AccessorPropertyTable_YIterator,
                                                                                              bool /* flagExcept */ )
    {
        METHODNAME_DEF( SAPBalanceCollectionACC, backupSAPBalanceFile );
        static const log4cplus::Logger& logger = libcsc_deli::LoggerPool::getLoggerAccessors();
        BLOG_TRACE_METHOD( logger, fun );

        try
        {
            boost::filesystem::path backupDir = getAccParameter()->getParameterValue( UADM_BACKUP_DIR ).c_str();
            if( ! boost::filesystem::is_directory( backupDir ) )
            {
                BLOG_WARN( logger, basar::VarString( backupDir.string().c_str() ) + basar::VarString( " doesn't exist!" ) );
                return basar::db::aspect::ExecuteResultInfo();
            }

            basar::DateTime dt = basar::DateTime::getCurrent();
            boost::filesystem::path filePath = getAccParameter()->getParameterValue( lit::SAP_BALANCE_FILE ).c_str();
            if( boost::filesystem::is_regular_file( filePath ) )
            {
                std::ostringstream dstFile;
                dstFile << filePath.stem().string() << "_" << dt.getDate() << dt.getHour() << filePath.extension().string();
                boost::filesystem::path dest = backupDir / boost::filesystem::path( dstFile.str() );

                BLOG_INFO( logger, basar::VarString( "Backup '" ) + filePath.string() + "' to '" + dest.string() + "'" );
                boost::filesystem::copy_file( filePath, dest, boost::filesystem::copy_option::overwrite_if_exists );
            }
        }
        catch( libutil::exceptions::BaseException& e )
        {
            BLOG_WARN( logger, "Backup of SAP balance file failed: " + e.reason() );
        }
        catch( std::exception& e )
        {
            BLOG_WARN( logger, basar::VarString( "Backup of SAP balance file failed: " ) + e.what() );
        }

        return basar::db::aspect::ExecuteResultInfo();
    }

} // end namespace sap
} // end namespace accessor
} // end namespace infrastructure
} // end namespace libcsc_deli

