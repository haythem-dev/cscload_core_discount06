//----------------------------------------------------------------------------
/*! \file   kscclientdm.h
 *  \brief  Domain module for access to KSC server.
 *  \author Klaus Hinz
 *  \date   03.01.2008
 */
//----------------------------------------------------------------------------

#ifndef GUARD_KSCCLIENTDM_H
#define GUARD_KSCCLIENTDM_H

#include <libbasar_definitions.h>
#include <libbasardbaspect_accessor.h>
#include "kscclientorderacc.h"
#include "kscclientorderinfoacc.h"
#include "kscclientitemacc.h"
#include "kscclientiteminfoacc.h"
#include "kscclientwrapper.h"

namespace domMod
{
  /*!  \brief  Domain module for access to KSC server. */
	class KSCClientDM
	{
  public:
    /*! \brief  Default constructor. */
    KSCClientDM( log4cplus::Logger logger );

    /*! \brief  Destructor. */
    virtual ~KSCClientDM();

  	/*! \brief  This method inits the module.
    
      Includes establishing a connection to KSC-Server.
      \param  branchNo Branch number
      \param  connParams Parameters necessary to establish a connection to KSC-Server
      \n      (application, port and server)
		  \throw  KSCClientDMException */
    void init(basar::Int16 branchNo, const KSCClientDMConnParams& connParams); 

	  /*! 
      \brief  Call this function to clear all accessor instances and the contents of property tables.
      Includes closing the connection to KSC-Server.
		  \throw  KSCClientDMException */
	  void shutdown();

    /*! \brief  Return a reference to the order property table. */
    basar::db::aspect::AccessorPropertyTableRef getOrderPropTab();

    /*! \brief  Add an empty line to order property table. */
    basar::db::aspect::AccessorPropertyTable_YIterator addEmptyOrder();

    /*! \brief  Return a reference to the orderInfo property table. */
    basar::db::aspect::AccessorPropertyTableRef getOrderInfoPropTab();

    /*! \brief  Add an empty line to orderInfo property table. */
    basar::db::aspect::AccessorPropertyTable_YIterator addEmptyOrderInfo();

    /*! \brief  Return a reference to the item property table. */
    basar::db::aspect::AccessorPropertyTableRef getItemPropTab();

    /*! \brief  Add an empty line to item property table. */
    basar::db::aspect::AccessorPropertyTable_YIterator addEmptyItem();

    /*! \brief  Return a reference to the itemInfo property table. */
    basar::db::aspect::AccessorPropertyTableRef getItemInfoPropTab();

    /*! \brief  Add an empty line to itemInfo property table. */
    basar::db::aspect::AccessorPropertyTable_YIterator addEmptyItemInfo();

    /*! \brief  Open a new order.
		  \pre	A connection to KSC-Server is established, see init(...).
      \n  No other order is opened.
      \n  Call is within operating time of KSC server.
      \param  iter  Specifies the order to be opened. Properties:
                - branchno (optional - see also: init (...))
                - customerno (mandatory)
                - ordertype (see below, length 2)
                - subordertype (see below, length 3)
                - pickingtype (see below, length 1)
                - bookingtype (see below, length 1)
                - deliverydate (optional)
                - orderheadline1 (optional, max length 30)
                - orderheadline2 (optional, max length 30)
                - orderheadline3 (optional, max length 30)
                - ordernote (optional, max length 30)
                - callback (optional, true/false)
                - reference (optional, max length ?)
              \n\n allowed combinations:
                     - none of ordertype, bookingtype, pickingtype, subordertype is set
                     - ordertype, bookingtpye, pickingtype are set, subordertpye is not set
                     - ordertype, bookingtype, pickingtype, subordertype are set
      \param  clearBeforeSelect Clear order info property table yes/no
      \retval stateInfo Execution status
      \retval textInfo Additional infos about execution
      \retval itInfo YIterator with infos about the opened order. Properties:
                - orderno
                - pharmacyname (max length 30)
		  \throw  KSCClientDMException */
    KSCClientDMReturn openOrder(
      const basar::db::aspect::AccessorPropertyTable_YIterator iter,
      bool clearBeforeSelect = true);

    /*! \brief  Add an item to the opened order.
		  \pre	An order is opened.
      \param  iter  Specifies the item to be added. Properties:
                - articleno (either articleno or ean must be set; if both are set, articleno is used)
                - ean (see articleno)
                - orderqty (mandatory)
                - interbranchtransfer (mandatory, true/false)
                - subsequentdelivery (mandatory, true/false)
                - articlerequirementpurchase (mandatory, true/false)
                - partialdelivery (mandatory, true/false)
                - sequenceno (optional)
                - itemnote (optional, max length 30)
      \param  clearBeforeSelect Clear item info property table yes/no
      \retval stateInfo Execution status
      \retval textInfo Additional infos about execution
      \retval itInfo YIterator with infos about the added item. Properties:
                - articleno
                - ean
                - qtylack
                - lackreason
                - auxqty
                - articleunit (max length 9)
                - articlename (max length 30)
                - handout (max length 3)
                - auxbranchno
                - codeblocage (max length 1)
                - restdeliveryqty
                - deliveryqty 
                - lackreasonctycode (max length 10)
                - pharmpurchprice
                - custpurchprice
                - pharmsellprice
                - taxrate
                - expirydate
                - lpprprice
                - seracode (max length 20)
                - xmlcode (max length 5)
                - xmltext (max length 100)
                - articleunitorg (max length 9)
                - articlenameorg (max length 30)
                - handoutorg (max length 3)
                - pharmpurchpriceorg
                - custpurchpriceorg
                - pharmsellpriceorg
                - taxrateorg
                - lpprpriceorg
                - articlenoorg
                - codeblocageorg (max length 1)
                - seracodeorg (max length 20)
                - xmlcodeorg (max length 5)
                - xmltextorg (max length 100)
		  \throw  KSCClientDMException */
    KSCClientDMReturn addItem(
      const basar::db::aspect::AccessorPropertyTable_YIterator itItem,
      bool clearBeforeSelect = true);


    KSCClientDMReturn addItemCodeRab(
      const basar::db::aspect::AccessorPropertyTable_YIterator itItem,
      bool clearBeforeSelect = true);

	KSCClientDMReturn addItemCodeBatch(
      const basar::db::aspect::AccessorPropertyTable_YIterator itItem,
      bool clearBeforeSelect = true);

	/*! \brief  Close the opened order.
		  \pre	An order is opened.
      \param  clearBeforeSelect Clear order info property table yes/no
      \retval stateInfo Execution status
      \retval textInfo Additional infos about execution
      \retval itInfo YIterator with infos about the closed order. Properties:
                - tourid (length 6)
                - tourdate
                - valueoforder
                - linesoforder
                - lacklines
                - textlines
                - deliverybranchno
		  \throw  KSCClientDMException */

	KSCClientDMReturn addTextItem(const basar::db::aspect::AccessorPropertyTable_YIterator itItem, bool clearBeforeSelect);

	KSCClientDMReturn closeOrder(bool clearBeforeSelect = true);

    /*! \brief  Cancel the opened order.
      \retval stateInfo Execution status
      \retval textInfo Additional infos about execution
      \retval itInfo Not set
		  \throw  KSCClientDMException */
    KSCClientDMReturn cancelOrder();

    /*! \brief  Postpone the opened order.
      \retval stateInfo Execution status
      \retval textInfo Additional infos about execution
      \retval itInfo Not set
		  \throw  KSCClientDMException */
    KSCClientDMReturn postponeOrder(bool clearBeforeSelect = true);

	KSCClientDMReturn setBatchValueDate( const basar::db::aspect::AccessorPropertyTable_YIterator iter );

	KSCClientDMReturn setOrderRelationNo( const basar::Int32 no, const basar::Int16 type);

	void kscSetNoRouting();


  protected:

  private:
    /*! \brief  Copy constructor. */
    KSCClientDM(const KSCClientDM& KSCClientDM);

    /*! \brief  Assignment operator. */
    KSCClientDM& operator= (const KSCClientDM& KSCClientDM);

	log4cplus::Logger m_Logger;
    basar::Int32 m_initialized;  //!< Counter for the number of initializations

    basar::db::aspect::AccessorInstanceRef m_orderACC;  //!< Accessor instance for order
    basar::db::aspect::AccessorInstanceRef m_orderInfoACC;  //!< Accessor instance for order infos
    basar::db::aspect::AccessorInstanceRef m_itemACC;  //!< Accessor instance for item
    basar::db::aspect::AccessorInstanceRef m_itemInfoACC;  //!< Accessor instance for item infos

    KSCClientWrapper m_kscClientWrapper;  //!< KSCClient wrapper instance
	};
}

#endif
