//--------------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief      declaration of abstract connection base class
 *  \author     Bischof Bjoern
 *  \date       27.01.2009
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

inline std::ostream& operator<< ( std::ostream& strm, const basar::db::sql::DatabaseInfo::CicsCustom& cicsCustom )
{
    static basar::ConstString indentation = "\t";
    strm    << "CICS CUSTOM:"                                     << std::endl
            << indentation << "IP address: <"        << cicsCustom.ipAddr        << ">" << std::endl
            << indentation << "Port: <"              << cicsCustom.port          << ">" << std::endl
            << indentation << "Start transaction: <" << cicsCustom.startTransact << ">";

    return strm;
}

inline std::ostream& operator<< ( std::ostream& strm, const basar::db::sql::DatabaseInfo& dbInfo )
{
    static basar::ConstString indentation = "\t";
    strm    << "DATABASE INFO:"                                                                  << std::endl
            << indentation << "Database: <"               << dbInfo.database << ">"                             << std::endl
            << indentation << "Database server: <"        << dbInfo.dbServer << ">"                             << std::endl
            << indentation << "Connection Type: <"        << dbInfo.eConnectType << ">"                         << std::endl
            << indentation << "Password: <"               << dbInfo.passwd << ">"                               << std::endl
            << indentation << "User: <"                   << dbInfo.user << ">"                                 << std::endl
            << indentation << "Connection ID: <"          << dbInfo.connectionId << ">"                         << std::endl
            << indentation << "Concurrent Transaction: <" << std::boolalpha << dbInfo.concurrTransaction << ">" << std::endl
            << dbInfo.cicsCustom;

    return strm;
}
