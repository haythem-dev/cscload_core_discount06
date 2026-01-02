#include "infrastructure/accessor/customerinvoice/customerinvoicingcollectionacc.h"
#include "infrastructure/accessor/customerinvoice/customerinvoicingcollectionacc_definitions.h"

#include "infrastructure/csvfile/csvfile.h"
#include "infrastructure/parameter/iaccparameter.h"

#include "loggerpool/libcsc_deli_loggerpool.h"
#include "domainmodule/libcsc_deli_properties_definitions.h"
#include "infrastructure/accessor/backup_settings.h"

#include "exception/filenotfoundexception.h"

#include <boost/filesystem.hpp>

namespace libcsc_deli
{
namespace infrastructure
{
namespace accessor
{
namespace customerInvoice
{
    CustomerInvoicingCollectionACC::CustomerInvoicingCollectionACC()
        : AccessorBase( lit::CUSTOMER_INVOICING_COLLECTION_ACC ), m_Logger( LoggerPool::getLoggerAccessors() )
    {
    }

    CustomerInvoicingCollectionACC::~CustomerInvoicingCollectionACC()
    {
    }

    void CustomerInvoicingCollectionACC::registerAccessorMethods( AccMethodCaller& accMethodCaller )
    {
        accMethodCaller.registerAccessMethod( lit::READ_CUSTOMER_INVOICING_COLLECTION, 
                                              &CustomerInvoicingCollectionACC::readCustomerInvoiceCollection, this );
        accMethodCaller.registerAccessMethod( lit::BACKUP_INVOICING, &CustomerInvoicingCollectionACC::backupFiles, this );
    }

    void CustomerInvoicingCollectionACC::setupPropertyDescriptionList( basar::property::PropertyDescriptionListRef pdl ) const
    {
        pdl.push_back( properties::BRANCH_NO   );
        pdl.push_back( properties::CUSTOMER_NO );
        pdl.push_back( properties::DOC_TYPE    );
        pdl.push_back( properties::DOC_NO      );
        pdl.push_back( properties::DATE        );
        pdl.push_back( properties::AMOUNT      );
        pdl.push_back( properties::TEXT_KEY    );
    }

    void CustomerInvoicingCollectionACC::checkFileExisting( const basar::VarString& filePath ) const
    {
        METHODNAME_DEF( CustomerInvoicingCollectionACC, checkFileExisting );

        std::fstream file( filePath.c_str(), std::fstream::in );
        const bool openable = file.is_open();
        file.close();

        if( ! openable )
        {
            basar::VarString reason = "File '" + filePath + "' not found!";
            throw exceptions::FileNotFoundException( basar::ExceptInfo( fun, reason, __FILE__, __LINE__ ) );
        }
    }

    void CustomerInvoicingCollectionACC::injectACCParameter( parameter::IACCParameterPtr accParam )
    {
        m_AccParameter = accParam;
    }

    parameter::IACCParameterPtr CustomerInvoicingCollectionACC::getAccParameter() const
    {
        CHECK_INSTANCE_EXCEPTION( m_AccParameter.get() );
        return m_AccParameter;
    }

    const log4cplus::Logger& CustomerInvoicingCollectionACC::getLogger() const
    {
        return m_Logger;
    }

    basar::VarString CustomerInvoicingCollectionACC::stripLeadingZeros( const basar::VarString& str ) const
    {
        basar::VarString ret = str;

        basar::VarString::size_type pos = str.find_first_not_of( '0' );
        if( pos != basar::VarString::npos )
        {
            ret = str.substr( pos );
        }

        return ret;
    }

    basar::db::aspect::ExecuteResultInfo CustomerInvoicingCollectionACC::readCustomerInvoiceCollectionFromFile( const basar::VarString& filePath )
    {
        METHODNAME_DEF( CustomerInvoicingCollectionACC, readCustomerInvoiceCollectionFromFile );
        BLOG_TRACE_METHOD( getLogger(), fun );

        basar::db::aspect::ExecuteResultInfo resInfo; resInfo.m_affectedRows = 0;
        BLOG_INFO( getLogger(), basar::VarString( "Importing file '" + filePath + "'" ) );
 
        infrastructure::csv::CSVFile invoiceImport( filePath, ';' );
        for( infrastructure::csv::CSVFile::iterator it = invoiceImport.begin(); it != invoiceImport.end(); ++it, ++resInfo.m_affectedRows )
        {
            const infrastructure::csv::CSVRow& row = *it;
            if( row.size() >= m_RowSize ) // adjust to file row size to avoid index failure which would cause abort() being called
            {
                try
                {
                    basar::db::aspect::AccessorPropertyTable_YIterator invoice = getPropertyTable().insert( basar::FOR_CLEAN );
                    int col = 0;
                    invoice.setInt16(   properties::BRANCH_NO,   static_cast< basar::Int16 >( row[ col++ ].stoi() ) );
                    invoice.setInt32(   properties::CUSTOMER_NO, row[ col++ ].stoi() );
                    invoice.setInt16(   properties::DOC_TYPE,    static_cast< basar::Int16 >( row[ col++ ].stoi() ) );
                    invoice.setString(  properties::DOC_NO,      stripLeadingZeros( row[ col++ ] ) );
                    invoice.setInt32(   properties::DATE,        row[ col++ ].stoi() );
                    invoice.setDecimal( properties::AMOUNT,      basar::Decimal( row[ col++ ] ) / basar::Decimal( 100 ) );
                    invoice.setString(  properties::TEXT_KEY,    stripLeadingZeros( row[ col++ ] ) );
                }
                catch( std::exception& e )
                {
                    std::ostringstream msg;
                    msg << "Error parsing line >" << resInfo.m_affectedRows + 1 << "<: " << e.what();
                    BLOG_ERROR( getLogger(), msg.str() ); // TODO use BLOG_WARN instead??
                }
            }
            else
            {
                std::ostringstream msg;
                msg << "Error parsing line >" << resInfo.m_affectedRows + 1 << "<: Row number doesn't match '" << m_RowSize <<"'!";
                BLOG_ERROR( getLogger(), msg.str() ); // TODO use BLOG_WARN instead??
            }
        }

        return resInfo;
    }

    const basar::db::aspect::ExecuteResultInfo CustomerInvoicingCollectionACC::readCustomerInvoiceCollection( basar::db::aspect::AccessorPropertyTable_YIterator, 
                                                                              bool /* flagExcept */ )
    {
        METHODNAME_DEF( CustomerInvoicingCollectionACC, readCustomerInvoiceCollectionFromFile );
        BLOG_TRACE_METHOD( getLogger(), fun );

        basar::db::aspect::ExecuteResultInfo resInfo;

        parameter::IACCParameter::ParameterValueCollection parameterValues = getAccParameter()->getParameterValues( lit::CUSTOMER_INVOICING_FILE );
        for( parameter::IACCParameter::ParameterValueCollection::const_iterator it = parameterValues.begin(); it != parameterValues.end(); ++it )
        {
            const basar::VarString& filePath = *it;
            try
            {
                checkFileExisting( filePath );
                resInfo.m_affectedRows += readCustomerInvoiceCollectionFromFile( filePath ).m_affectedRows;
            }
            catch( libutil::exceptions::BaseException& e )
            {
                BLOG_WARN( getLogger(), e.reason() );
            }
            catch( std::exception& e )
            {
                std::ostringstream msg;
                msg << "Exception occurred while parsing line '" << resInfo.m_affectedRows << "': " << e.what()
                    << "\n ABORT reading file '" << filePath << "'!";
                BLOG_ERROR( getLogger(), msg.str() );
            }
        }

        return resInfo;
    }

    const basar::db::aspect::ExecuteResultInfo CustomerInvoicingCollectionACC::backupFiles( basar::db::aspect::AccessorPropertyTable_YIterator, 
                                                 bool /* flagExcept */ )
    {
        METHODNAME_DEF( CustomerInvoicingCollectionACC, backupFiles );
        BLOG_TRACE_METHOD( getLogger(), fun );

        try
        {
            boost::filesystem::path backupDir = getAccParameter()->getParameterValue( UADM_BACKUP_DIR ).c_str();
            if( ! boost::filesystem::is_directory( backupDir ) )
            {
                BLOG_WARN( getLogger(), basar::VarString( backupDir.string().c_str() ) + basar::VarString( " doesn't exist!" ) );
                return basar::db::aspect::ExecuteResultInfo();
            }

            basar::DateTime dt = basar::DateTime::getCurrent();
            parameter::IACCParameter::ParameterValueCollection parameterValues = getAccParameter()->getParameterValues( lit::CUSTOMER_INVOICING_FILE );
            for( parameter::IACCParameter::ParameterValueCollection::const_iterator it = parameterValues.begin(); it != parameterValues.end(); ++it )
            {
                boost::filesystem::path filePath = it->c_str();
                if( boost::filesystem::is_regular_file( filePath ) )
                {
                    std::ostringstream dstFile;
                    dstFile << filePath.stem().string() << "_" << dt.getDate() << dt.getHour() << filePath.extension().string();
                    boost::filesystem::path dest = backupDir / boost::filesystem::path( dstFile.str() );

                    BLOG_INFO( getLogger(), basar::VarString( "Backup '" ) + *it + "' to '" + dest.string() + "'" );
                    boost::filesystem::copy_file( filePath, dest, boost::filesystem::copy_option::overwrite_if_exists );
                }
            }
        }
        catch( libutil::exceptions::BaseException& e )
        {
            BLOG_WARN( getLogger(), "Backup of invoicing files failed: " + e.reason() );
        }
        catch( std::exception& e )
        {
            BLOG_WARN( getLogger(), basar::VarString( "Backup of invoicing files failed: " ) + e.what() );
        }

        return basar::db::aspect::ExecuteResultInfo();
    }

} // end namespace customerInvoice
} // end namespace accessor
} // end namespace infrastructure
} // end namespace libcsc_deli
