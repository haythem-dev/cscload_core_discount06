//----------------------------------------------------------------------------
/*! \file   generalbranchparameterdm.h
 *  \brief  main interface for generalbranchparameter domain module 
 *  \author Frank Naumann
 *  \date	  25.03.2010
 */
//----------------------------------------------------------------------------
#ifndef GUARD_GENERALBRANCHPARAMETERDM_H
#define GUARD_GENERALBRANCHPARAMETERDM_H

//---------------------------------------------------------------------------

/*! \brief Namespace for all domain modules.
 */
namespace domMod {

//---------------------------------------------------------------------------
/*! \brief domain module class for general branch parameter.
 *         This is a final class.
 *  \throw no-throw
 */
class GeneralBranchParameterDM
{
public:
  /*! \brief std constructor.
   *  \throw no-throw
   */
  GeneralBranchParameterDM();

  /*! \brief std destructor.
   *  \throw no-throw
   */
  virtual ~GeneralBranchParameterDM();

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

  /*! \brief check if the specified day is a work day or not.
   *  \param date the date to check for work day.
   *  \return true if it is a work day, false otherwise.
   *  \throw no-throw
   */
  bool isWorkDay(Date date);

  /*! \brief returns the last work day BEFORE the specified day.
   *  \param date the date to check.
   *  \return the last work day before the specified day.
   *  \throw no-throw
   */
  Date getLastWorkDayBefore(Date date);

//---------------------------------------------------------------------------
// INTERFACE - METHODS
//---------------------------------------------------------------------------
/////////////////////////// FINDS ///////////////////////////////////////////
//---------------------------------------------------------------------------

  /*! \brief Selects all public holidays for branchno.
   *         The methode builds a query that selects all entries from the table
   *         feiertag for branchno given as default parameter
   *  \return Property table containing all branch holidays.
   */
  AccessorPropertyTableRef findAllPublicHolidaysByBranchno();
	
/////////////////////////// PROPTABS / YITERATORS ///////////////////////////
//---------------------------------------------------------------------------
  
private:
  /*! \brief copy constructor.
   *  \param r the domain module instance to copy.
   *  \throw no-throw
   */
  GeneralBranchParameterDM(const GeneralBranchParameterDM& r);

  /*! \brief assign operator.
   *  \param r the domain module instance to copy.
   *  \throw no-throw
   */
  GeneralBranchParameterDM& operator=(const GeneralBranchParameterDM& r);

//---------------------------------------------------------------------------
// accessor definition name 
//---------------------------------------------------------------------------
  AccessorInstanceRef m_PublicHolidayACC; //!< accessor instance for select publicHoliday
  Int32               m_Initialized;      //!< counter of init-calls	
};

//---------------------------------------------------------------------------

} // namespace domMod

//---------------------------------------------------------------------------

#endif // GUARD_GENERALBRANCHPARAMETERDM_H

//---------------------------------------------------------------------------
