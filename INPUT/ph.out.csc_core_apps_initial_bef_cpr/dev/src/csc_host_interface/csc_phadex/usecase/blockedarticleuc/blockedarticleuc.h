#ifndef GUARD_CSC_PHADEX_USECASE_BLOCKEDARTICLE_UC_H
#define GUARD_CSC_PHADEX_USECASE_BLOCKEDARTICLE_UC_H

#include "iblockedarticleuc.h"
#include <domainmodule/phadextransaction/transactionrecord/blockedarticlerecord/iblockedarticlerecordptr.h>
#include <pxordertransmitptr.h>
#include <libbasar_definitions.h>

namespace log4cplus
{
    class Logger;
}

namespace csc_phadex
{
namespace useCase
{
class BlockedArticleUC : public IBlockedArticleUC
{
public:
	BlockedArticleUC();
    virtual ~BlockedArticleUC();

    virtual void run();
    virtual void setBlockedArticleRecord( csc_phadex::domMod::phadexTransaction::IBlockedArticleRecordPtr tr );
    virtual void injectPxOrderTransmit( pxOrderTransmitPtr xmit );
	enum bookingtype
	{
		ACCOUNT_ADD_QUANTITY = 1, // Bestand zubuchen
		ACCOUNT_SUB_QUANTITY = 2, // Bestand abbuchen
		ACCOUNT_SET_QUANTITY = 8 // Bestand auf festen Wert setzen
	};

private:
	BlockedArticleUC( const BlockedArticleUC & );
	BlockedArticleUC & operator= ( const BlockedArticleUC & );

    csc_phadex::domMod::phadexTransaction::IBlockedArticleRecordPtr m_BlockedArticleRecord;
    pxOrderTransmitPtr          m_pxOrderTransmit;
    const log4cplus::Logger&    m_Logger;
};

} // namespace useCase
} // namespace csc_phadex

#endif //end GUARD_CSC_PHADEX_USECASE_BLOCKEDARTICLE_UC_H
