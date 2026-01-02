//----------------------------------------------------------------------------
/*! \file   customerdm.h
 *  \brief  main interface for domain module customer.
 *  \author Frank Naumann
 *  \date   31.03.2010
 */
//----------------------------------------------------------------------------

#ifndef GUARD_CUSTOMERDM_H
#define GUARD_CUSTOMERDM_H

//---------------------------------------------------------------------------

namespace domMod {

//---------------------------------------------------------------------------
/*! \brief domain module class for customer.
 *         This is a final class.
 *  \throw no-throw
 */
class CustomerDM
{
public:
  /*! \brief std constructor.
   *  \throw no-throw
   */
  CustomerDM();

  /*! \brief destructor.
   *  \throw no-throw
   */
  virtual ~CustomerDM();

  /*! \brief This method inits the module.
   *  \param activeConn the connection.
   *  \param branchNo the branch number.
   *  \throw no-throw
   */
  void init(const ConnectionRef activeConn, const Int16 branchNo);

  /*! \brief call this function to clear all accessor instances and the contents of property tables.
   *  \throw no-throw
   */
  void shutdown();

//---------------------------------------------------------------------------
// INTERFACE - METHODS
//---------------------------------------------------------------------------
	/////////////////////////// FINDS ///////////////////////////////////////////
	//---------------------------------------------------------------------------
  /*! \brief Finds a customer entry specified by customerno.
   *  \param yitSearch YIterator containing search criteria (customerno).
   *  \return YIterator containing customer data.
   *  \throw no-throw
   */
  AccessorPropertyTable_YIterator findCustomer(const AccessorPropertyTable_YIterator yitSearch);

  //---------------------------------------------------------------------------
	/////////////////////////// SAVES ///////////////////////////////////////////
	//---------------------------------------------------------------------------
  /*! \brief Saves a customer entry to tabel ccustomermaindata (INSERT or UPDATE).
   *  \param yitCustomer YIterator containing customer data.
   *  \return ExecuteResultInfo OK/ERROR.
   *  \throw no-throw
   */
  ExecuteResultInfo saveCustomer(AccessorPropertyTable_YIterator yitCustomer);

	//---------------------------------------------------------------------------
	/////////////////////////// PROPTABS / YITERATORS ///////////////////////////
	//---------------------------------------------------------------------------
  /*! \brief Adds a new row into customer property table.
   *  \return the new row which has been inserted into customer property table.
   *  \throw no-throw
   */
  AccessorPropertyTable_YIterator addEmptyCustomer();

private:
  /*! \brief copy constructor.
   *  \param r the domain module instance to copy.
 	 *  \throw no-throw
   */
  CustomerDM(const CustomerDM& r);

  /*! \brief assign operator.
   *  \param r the domain module instance to assign.
   *  \throw no-throw
   */
  CustomerDM& operator=(const CustomerDM& r);

//---------------------------------------------------------------------------
// accessor instances ( created in init() )
//---------------------------------------------------------------------------
  AccessorInstanceRef m_CustomerACC;  //!< accessor instance for customer
  Int32               m_Initialized; //!< counter of init-calls	
};

//---------------------------------------------------------------------------

} // namespace domMod

//---------------------------------------------------------------------------

#endif // GUARD_CUSTOMERDM_H

//---------------------------------------------------------------------------
