//-------------------------------------------------------------------------------------------------//
/*! \file   loadcustomeruc.h
 *  \brief  use case class for load customer.
 *  \author Frank Naumann
 *  \date   25.03.2010
 */
//-------------------------------------------------------------------------------------------------//

#ifndef GUARD_LOADCUSTOMERUC_H
#define GUARD_LOADCUSTOMERUC_H

//-------------------------------------------------------------------------------------------------//

#include <libbasarappl_eventmacros.h>

//-------------------------------------------------------------------------------------------------//

namespace zpldcust {
class LoadCustomerApplBase;

/*! \brief Namespace for use cases in zpldcust application.
 */
namespace useCase {

//-------------------------------------------------------------------------------------------------//
/*! \brief Use Case class. This is a final class.
 */
class LoadCustomerUC
{
public:
  /*! \brief std-constructor.
   *  \throw no-throw
   */
  LoadCustomerUC();
	
  /*! \brief std-destructor.
   *  \throw no-throw
   */
  virtual ~LoadCustomerUC();

  /*! \brief This method returns a reference to the application controller.
   *  \throw no-throw
   */
  LoadCustomerApplBase& getManager();

  /*! \brief This method starts the use case.
   *  \param rSource source where event is thrown.
   *  \param yitSearch search criteria from source.
   *  \throw no-throw
   */
  EventReturnType run(IEventSource& rSource, AccessorPropertyTable_YIterator yitSearch);

  /*! \brief std method; has to be the first call in run() if events should be caught.
   *  \param forSave register = true / deregister = false.
   *  \throw no-throw
   */
  virtual void registerEventHandlers(const bool forSave);
	
  /*! \brief System event to handle load customer event.
   *  \param rSource The event source of the event (not used).
   *  \param yitFromEvSrc Search criteria from source.
   *  \return EventReturnStruct OK/ERROR.
   *  \throw no-throw
   */
  SYSTEM_EVENT_HANDLER_DECLARATION(LoadCustomer)

//-------------------------------------------------------------------------------------------------//
	
private :

  /*! \brief Chechs if customer needs an update and perform the update.
   *  \param yitCicsCustomer DKKUL customer data set.
   *  \return EventReturnStruct OK/ERROR.
   *  \throw no-throw
   */
 EventReturnType checkCustomerUpdate(AccessorPropertyTable_YIterator yitCicsCustomer);

  /*! \brief copy constructor - forbidden.
 	 *  \throw no-throw
   */
  LoadCustomerUC(const LoadCustomerUC&);

  /*! \brief assign operator - forbidden.
   *  \throw no-throw
   */
  LoadCustomerUC& operator=(const LoadCustomerUC&);

  /*! \brief logs the start of loading.
   *  \param branchno
   *  \param mode
   *  \throw no-throw
   */
  void logStart(basar::Int16 branchno, basar::I18nString mode);

  /*! \brief logs the end of loading and amount of loaded data.
   *  \param branchno
   *  \param mode
   *  \throw no-throw
   */
  void logEnd(basar::Int16 branchno, basar::I18nString mode);

  Int32 m_NewRows;    //!< Number of new created customers.
  Int32 m_Updated;    //!< Number of updated customers.
  Int32 m_DiffBranch; //!< Number of customers with differences between branches.
};

//-------------------------------------------------------------------------------------------------//

} // useCase
} // zpldcust

//-------------------------------------------------------------------------------------------------//

#endif //GUARD_LOADCUSTOMERUC_H

//-------------------------------------------------------------------------------------------------//
