#include "mainuc.h"

#include "loggerpool/ibtorderimport_loggerpool.h"

#include <persistence/itransactionfactory.h>
#include <libutil/util.h>
#include <libutil/session.h>

#include <infrastructure/mail/imailalert.h>

#include <ibt/ibtrequest/iibtrequest.h>
#include <ibt/ibtrequest/iibtrequestrepository.h>
#include <ibt/ibtresponse/iibtresponse.h>
#include <ibt/ibtresponse/iibtresponserepository.h>

#include "iibtordergetter.h"
#include "ibtordermanagerptr.h"

#include "domainmodule/ipxorder.h"
#include "domainmodule/ipxtaskcontrol.h"
#include "domainmodule/ipxorderitemptr.h"
#include "domainmodule/ipxorderitem.h"
#include "domainmodule/ipxordertransmit.h"

//#include "inachlieferposwriter.h"

namespace ibtorderimport
{
namespace useCase
{
MainUC::MainUC()
: m_Logger( ibtorderimport::LoggerPool::getLoggerUseCases() )
{
    METHODNAME_DEF( MainUC, MainUC )
    BLOG_TRACE_METHOD( getLogger(), fun );
}

MainUC::~MainUC()
{
    METHODNAME_DEF( MainUC, ~MainUC )
    BLOG_TRACE_METHOD( getLogger(), fun );
}

void MainUC::injectTransactionFactory( libcsc::persistence::ITransactionFactoryPtr transactionFactory )
{
	m_TransactionFactory = transactionFactory;
}

void MainUC::injectMailAlert( infrastructure::mail::IMailAlertPtr mailAlert )
{
	METHODNAME_DEF( MainUC, injectMailAlert )
	BLOG_TRACE_METHOD( getLogger(), fun );

	m_MailAlert = mailAlert;
}

void MainUC::injectIbtOrderGetter( IIbtOrderGetterPtr ibtOrderGetter)
{
	METHODNAME_DEF( MainUC, injectIbtOrderGetter )
	BLOG_TRACE_METHOD( getLogger(), fun );

	m_IIbtOrderGetter = ibtOrderGetter;
}

void MainUC::injectIbtRequestRepository( libcsc::ibt::IIbtRequestRepositoryPtr repo )
{
	m_IbtRequestRepository = repo;
}

void MainUC::injectIbtResponseRepository( libcsc::ibt::IIbtResponseRepositoryPtr repo )
{
	m_IbtResponseRepository = repo;     
}

void MainUC::injectTaskControl( domMod::IPxTaskControlPtr taskCtrlPtr )
{
	METHODNAME_DEF( MainUC, injectTaskControl )
	BLOG_TRACE_METHOD( getLogger(), fun );

	m_TaskControl = taskCtrlPtr;
}

void MainUC::injectSession( libutil::infrastructure::session::ISessionPtr sess)
{
	METHODNAME_DEF( MainUC, injectSession )
	BLOG_TRACE_METHOD( getLogger(), fun );

	m_Session = sess;
}

//void MainUC::injectNachlieferPosWriter( INachlieferPosWriterPtr nachlieferPosWriter )
//{
	//m_NachlieferPosWriter = nachlieferPosWriter;
//}

void MainUC::setBranchNo( const basar::Int16 branchno )
{
	m_BranchNo = branchno;
}

infrastructure::mail::IMailAlertPtr MainUC::getMailAlert()
{
	CHECK_INSTANCE_EXCEPTION( m_MailAlert.get() );
	return m_MailAlert;
}

IIbtOrderGetterPtr MainUC::getIbtOrderGetter()
{
	CHECK_INSTANCE_EXCEPTION( m_IIbtOrderGetter.get() );
	return m_IIbtOrderGetter;
}

domMod::IPxOrderTransmitPtr	MainUC::getPxOrderTransmit()
{
	CHECK_INSTANCE_EXCEPTION( m_PxOrderTransmit.get() );
	return m_PxOrderTransmit;
}

void MainUC::injectPxOrderTransmit( domMod::IPxOrderTransmitPtr pxOrderTransmit )
{
	m_PxOrderTransmit = pxOrderTransmit;
}

domMod::IPxTaskControlPtr		MainUC::getTaskControl()
{
	CHECK_INSTANCE_EXCEPTION( m_TaskControl.get() );
	return m_TaskControl;
}

libutil::infrastructure::session::ISessionPtr		MainUC::getSession()
{
	CHECK_INSTANCE_EXCEPTION( m_Session.get() );
	return m_Session;
}

void MainUC::run()
{
    METHODNAME_DEF( MainUC, run )
    BLOG_TRACE_METHOD( getLogger(), fun );

	basar::cmnutil::CollBString msgList;
	std::stringstream s;

	try
	{
		getTaskControl()->setHeartBeat();

		BLOG_DEBUG( getLogger(), "looking for unprocessed ibt requests ..." );
		libcsc::ibt::IIbtRequestCollectionPtr collRequests = m_IbtRequestRepository->findByPattern( m_BranchNo, libcsc::ibt::ReadyForProcessing );

		if( collRequests->empty() )
		{
			BLOG_INFO( getLogger(), "NO unprocessed ibt requests found!" );
			return;
		}

		basar::Int32 counter = 0;

		domMod::IPxOrderPtr order;
		domMod::IPxOrderItemPtr item;

		
		libcsc::ibt::IIbtRequestCollection::iterator it = collRequests->begin();
		for( ; it != collRequests->end(); ++it )	// Schleife über alle unbooked- IBtRequestPos
		{
			libcsc::ibt::IIbtRequestPtr request( *it );
			++counter;

			getTaskControl()->setHeartBeat();

			s.str( "" );
			s << "--- processing ibt request < " << request->getIbtRequestId() << " > ...";
			BLOG_DEBUG( getLogger(), s.str() );

			if( true == getPxOrderTransmit()->isCustomerLocked( request ) )
			{
				// just don´t process this request / leave it as it is - and go on with other requests ...
				continue;
			}

			if ( ( request->getIbtTourDate() < basar::Date(9999, 12, 31) ) && ( request->getIbtTourDate() > basar::Date::getCurrent() ) )
			{
				// just don´t process this request / leave it as it is - and go on with other requests .
				continue;
			}
			
			libcsc::ibt::IIbtResponsePtr response = m_IbtResponseRepository->createResponse( request->getIbtRequestId() );
			if( request->hasToBeBooked() )
			{
				order = getIbtOrderGetter()->getOrder( request );
				item = order->addPosition( request );
				response->setIbtOrderNo( item->getPxVbOrderItem()->KdAuftragNr() );
				response->setIbtOrderPosNo( item->getPxVbOrderItem()->PosNr() );
				response->setIbtConfirmedQuantity( item->getPxVbOrderItem()->MengeBestaetigt() );
			}
			else
			{
				BLOG_DEBUG( getLogger(), "request is NOT booked due to qty = 0." );
				response->setNoBooking();
			}

			request->markAsBooked();

			libcsc::persistence::TransactionGuard guard = m_TransactionFactory->createTransaction();
			try
			{
				guard.begin();

				BLOG_DEBUG( getLogger(), "start saving (opening transaction) ..." );
				m_IbtRequestRepository->saveIbtRequest( request );
				m_IbtResponseRepository->saveIbtResponse( response );
				//m_NachlieferPosWriter->save( request, response, item->getPxVbOrderItem() );	// to be removed in future
				getIbtOrderGetter()->save();
				BLOG_DEBUG( getLogger(), "request processed (transaction committed) successfully." );
			
				guard.commit();
			}
			catch( const basar::Exception & e )
			{
				guard.rollback();
				BLOG_ERROR( getLogger(), e.what() );
				
				// Senden Error Mail
				msgList.push_back( e.what() );
				sendMail( msgList );
				msgList.clear();
			}
		}

		s.str( "" );
		s << "--- < " << counter << " > ibt requests processed successfully.";
		BLOG_INFO( getLogger(), s.str() );
	}
	catch( const basar::Exception & e )
	{
		BLOG_ERROR( getLogger(), e.what() );
				
		// Senden Error Mail
		msgList.push_back( e.what() );
		sendMail( msgList );
		throw e;
	}
}

void MainUC::sendMail( basar::cmnutil::CollBString & msgList )
{
	std::stringstream body;

	body << "ERROR while importing IBT orders" << std::endl;
	body << std::endl;

	basar::cmnutil::CollBString::const_iterator it = msgList.begin();
	while( it != msgList.end() )
	{
		body << (*it) << std::endl;
		++it;
	}

	std::stringstream subject;
			
	subject << "Error - IBT ORDER IMPORT in BRANCH <" << getSession()->getUser()->getAreaID() << ">" << std::endl;
			
	getMailAlert()->send( subject.str(), body.str() );
}

const log4cplus::Logger & MainUC::getLogger()
{
	return m_Logger;
}

} // namespace usecase
} // namespace ibtorderimport
