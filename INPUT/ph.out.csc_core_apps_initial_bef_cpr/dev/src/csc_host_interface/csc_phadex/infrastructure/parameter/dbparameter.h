//-----------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief      declaration of database login class
 *  \author     Bischof Bjoern
 *  \date       15.06.2015
 *  \version    00.00.00.01 first version
 */ 
//-----------------------------------------------------------------------------------------------//
#ifndef GUARD_CSC_PHADEX_INFRASTRUCTURE_PARAMETER_DBPARAMETER_H
#define GUARD_CSC_PHADEX_INFRASTRUCTURE_PARAMETER_DBPARAMETER_H

//-----------------------------------------------------------------------------------------------//
// include section
//-----------------------------------------------------------------------------------------------//
#include <libbasar_definitions.h>
#include <libutil/parameter.h>

//-----------------------------------------------------------------------------------------------//
//  forward declaration section
//-----------------------------------------------------------------------------------------------//
namespace log4cplus 
{
    class Logger;
}

//-----------------------------------------------------------------------------------------------//
//  class declaration section
//-----------------------------------------------------------------------------------------------//
namespace csc_phadex
{
	namespace infrastructure
	{
		namespace parameter
		{
			class DBParameter : public libutil::infrastructure::parameter::IParameterGateway
			{
			public:
				DBParameter();
				~DBParameter();

                void injectParameterGateway( libutil::infrastructure::parameter::IParameterGatewayPtr );

				virtual bool  getParameterValue(  const basar::I18nString& parameterName,  basar::I18nString& value ) const;
				virtual bool  getParameterValue(  const basar::I18nString& parameter1,     const basar::I18nString& parameterName, 
														basar::I18nString& value ) const;
				virtual bool  getParameterValue(  const basar::Int16 parameter1,           const basar::I18nString& parameterName, 
														basar::I18nString& value ) const;
				virtual bool  getParameterValue(  const basar::I18nString& parameter1,     const basar::I18nString& parameter2, 
														const basar::I18nString& parameterName,  basar::I18nString& value ) const;
			private:
				////////////////////////////////
				// methods
				////////////////////////////////
				DBParameter( const DBParameter& r );
				DBParameter& operator = ( const DBParameter& r );

                basar::I18nString getParameterName( const basar::I18nString& ) const;

				////////////////////////////////
				// variables
				////////////////////////////////
	            const log4cplus::Logger&                                    m_Logger;
                libutil::infrastructure::parameter::IParameterGatewayPtr    m_ParameterGateway;
			};

		} // end namespace parameter
	} // end namespace infrastructure
} // end namespace libutil

#endif
