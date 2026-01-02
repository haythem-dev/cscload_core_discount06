//-------------------------------------------------------------------------------------------------//
/*! \file   loadcustomerappl.h
 *  \brief  application class (main) for zpldcust (load customer)
 *  \author Frank Naumann
 *  \date   31.03.2010
 */
//-------------------------------------------------------------------------------------------------//

#ifndef GUARD_LOADCUSTOMERAPPL_H
#define GUARD_LOADCUSTOMERAPPL_H

//-------------------------------------------------------------------------------------------------//

#include "connection.h"
#include "loadcustomeruc.h" 

#include "customerdm.h"
#include "cicscustomerdm.h"
#include "generalbranchparameterdm.h"

//-------------------------------------------------------------------------------------------------//

namespace zpldcust {

//-------------------------------------------------------------------------------------------------//

class LoadCustomerAppl;

//-------------------------------------------------------------------------------------------------//
/*! \brief One and only instance for control LoadCutomerAppl application.
 *         This is a final class.
 */
class LoadCustomerApplBase
{
	friend class useCase::LoadCustomerUC;	//!< use case classes need private access to current YIterators / propertyTables
	friend class basar::cmnutil::Singleton<LoadCustomerApplBase>; //!< singleton as friend for construction!

public:
  /*! \brief destructor.
   *  \throw no-throw
   */
	virtual ~LoadCustomerApplBase();

  /*! \brief main entrance, called from main()
   *  \param rSource source where event is thrown.
   *  \param yitSearch search criteria from source.
   *	\throw no-throw
   */
  EventReturnType run(IEventSource& rSource, AccessorPropertyTable_YIterator yitSearch);

private:
  /*! \brief std constructor, protected because of singleton.
   *  \throw no-throw
   */
  LoadCustomerApplBase();

  /*! \brief forbidden copy constructor.
   *  \param r The application instance to copy.
   *  \throw no-throw
   */
  LoadCustomerApplBase(const LoadCustomerApplBase& r);

  /*! \brief forbidden assignment operator.
   *  \param r The application instance to assign.
   *  \throw no-throw
   */
  LoadCustomerApplBase& operator=(const LoadCustomerApplBase& r);

  /*! \brief initialize members.
   *  \param yitSearch search criteria from source.
   *  \return true if initialization was ok
   *  \throw no-throw
   */
  bool init(const AccessorPropertyTable_YIterator yitSearch);

  /*! \brief de-initialize members, so that not all value members have to be held the whole time!
   *  \throw no-throw
   */
  void shutdown();
	
	//---------------------------------------------------------//
	// UseCases
	//---------------------------------------------------------//
	useCase::LoadCustomerUC	m_LoadCustomerUC;	//!< use case class for load customer
	
	//---------------------------------------------------------//
	// DomainModules
	//---------------------------------------------------------//
  domMod::CustomerDM               m_CustomerDM;               //!< domain module intance for customer.
  domMod::CicsCustomerDM           m_CicsCustomerDM;           //!< domain module intance for Cics customer DKKUL.
  domMod::GeneralBranchParameterDM m_GeneralBranchParameterDM; //!< domain module intance for general parameter (public holidays!).

	//---------------------------------------------------------//
	// Connection
	//---------------------------------------------------------//
	Connection							m_Connection;	//!< connection for load customer
};

//---------------------------------------------------------------------------------------//
/*! \brief Derived class from LoadCustomerApplBase.
 *         This is a final class. Singleton
 *  \note  class is necessary for dll exporting Singleton\<LoadCustomerApplBase\>
 */
class LoadCustomerAppl : public basar::cmnutil::Singleton<LoadCustomerApplBase>
{
  friend class dummy;	//!< prevents pedantic compiler warning

private:
  /*! \brief standard constructor 
   *  \throw no-throw
   */
  LoadCustomerAppl();

  /*! \brief copy constructor.
   *  \param r The application instance to copy.
   *  \throw no-throw
   */
  LoadCustomerAppl(const LoadCustomerAppl& r);

  /*! \brief assign operator 
   *  \param r The application instance to assign.
   *  \throw no-throw
   */
  LoadCustomerAppl& operator=(const LoadCustomerAppl& r);
};

//-------------------------------------------------------------------------------------------------//

}	// namespace zpldcust

//-------------------------------------------------------------------------------------------------//
/*! \ingroup DIFF_WIN_UNIX 
#ifdef WIN32
using basar::cmnutil::Singleton;
using zpldcust::LoadCustomerApplBase;

//! \brief explicit template instantiation for singleton 
Singleton<LoadCustomerApplBase>::InstancePtr Singleton<LoadCustomerApplBase>::m_Instance;
#endif	// WIN32 */

//-------------------------------------------------------------------------------------------------//

#endif	// GUARD_LOADCUSTOMERAPPL_H

//-------------------------------------------------------------------------------------------------//
