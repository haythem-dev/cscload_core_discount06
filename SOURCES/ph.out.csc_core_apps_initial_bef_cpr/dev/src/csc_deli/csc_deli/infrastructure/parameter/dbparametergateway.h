#ifndef GUARD_CSC_DELI_INFRASTRUCTURE_PARAMETER_PARAMETERGATEWAY_H
#define GUARD_CSC_DELI_INFRASTRUCTURE_PARAMETER_PARAMETERGATEWAY_H

#include <libutil/parameter.h>

namespace log4cplus
{
    class Logger;
}

namespace csc_deli
{
namespace infrastructure
{
namespace parameter
{

    class DBParameterGateway : public libutil::infrastructure::parameter::IParameterGateway
    {
    public:
        DBParameterGateway( libutil::infrastructure::parameter::IParameterGatewayPtr );
        ~DBParameterGateway();

        void setAreaId( basar::Int16 );

        // from IParameterGateway interface
        bool getParameterValue( const basar::I18nString& parameterName, basar::I18nString& value )                                         const;
        bool getParameterValue( const basar::I18nString& parameter1,    const basar::I18nString& parameterName, basar::I18nString& value ) const;
        bool getParameterValue( const basar::Int16 parameter1,          const basar::I18nString& parameterName, basar::I18nString& value ) const;
        
        bool getParameterValue( const basar::I18nString& parameter1,    const basar::I18nString& parameter2, 
                                const basar::I18nString& parameterName,  basar::I18nString& value ) const;

    private:
        // forbidden
        DBParameterGateway();
        DBParameterGateway( const DBParameterGateway& );
        DBParameterGateway& operator = ( const DBParameterGateway& );

        basar::Int16 getAreaId() const;

    private:
        const log4cplus::Logger&                                 m_Logger;
        libutil::infrastructure::parameter::IParameterGatewayPtr m_ParameterGateway;
        basar::Int16                                             m_AreaId;
    };

} // end namespace parameter
} // end namespace infrastructure
} // end namespace csc_deli

#endif // GUARD_CSC_DELI_INFRASTRUCTURE_PARAMETER_PARAMETERGATEWAY_H
