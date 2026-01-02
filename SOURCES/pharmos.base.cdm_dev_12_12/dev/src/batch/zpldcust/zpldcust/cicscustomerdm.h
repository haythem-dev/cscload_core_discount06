//----------------------------------------------------------------------------
/*! \file   cicscustomerdm.h
 *  \brief  main interface for domain module (cics file VSAM.DKKUL)
 *  \author Frank Naumann
 *  \date   23.03.2010
 */
//----------------------------------------------------------------------------

#ifndef GUARD_CICSCUSTOMERDM_H
#define GUARD_CICSCUSTOMERDM_H

//---------------------------------------------------------------------------

namespace domMod {

//---------------------------------------------------------------------------
/*! \brief domain module class for cics customer (DKKUL).
 *          This is a final class.
 *  \throw no-throw
 */
class CicsCustomerDM
{
public:
//---------------------------------------------------------------------------
// global functions of ModuleDM
//---------------------------------------------------------------------------
  /*! \brief std constructor
   *  \throw no-throw
   */
  CicsCustomerDM();

  /*! \brief destructor.
   *  \throw no-throw
   */
  virtual ~CicsCustomerDM();

  /*! \brief This method inits the module.
   *  \param activeConn the Informix database connection.
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
	
//---------------------------------------------------------------------------
/////////////////////////// FINDS ///////////////////////////////////////////
//---------------------------------------------------------------------------
  /*! \brief finds cics customer entries (DKKUL) by given search criteria.
   *  \param yitSearch  yit containing values for where-statement.
   *  \return property table, containing all DKKUL data for given search criteria.
   *  \throw no-throw
   */
  AccessorPropertyTableRef findDKKULByPattern(AccessorPropertyTable_YIterator yitSearch);

//---------------------------------------------------------------------------
/////////////////////////// SAVES ///////////////////////////////////////////
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
/////////////////////////// PROPTABS / YITERATORS ///////////////////////////
//---------------------------------------------------------------------------
  /*! \brief Adds a new row into cics customer (DKKUL) property table.
   *  \return the new row which has been inserted into cics customer (DKKUL) property table.
   *  \throw no-throw
   */
  AccessorPropertyTable_YIterator addEmptyDKKUL();

private:
  /*! \brief copy constructor.
   *  \param r the domain module instance to copy.
   *  \throw no-throw
   */
  CicsCustomerDM(const CicsCustomerDM& r);

  /*! \brief assign operator
   *  \param r the domain module instance to assign.
   *  \throw no-throw
   */
  CicsCustomerDM& operator=(const CicsCustomerDM& r);

  //---------------------------------------------------------------------------
  // accessor instances ( created in init() )
  //---------------------------------------------------------------------------
  AccessorInstanceRef m_DKKULACC;    //!< accessor instance for select VSAM.DKKUL
  Int32               m_Initialized; //!< counter of init-calls	
};

//---------------------------------------------------------------------------

} // namespace domMod

//---------------------------------------------------------------------------

#endif  // GUARD_CICSCUSTOMERDM_H

//---------------------------------------------------------------------------

