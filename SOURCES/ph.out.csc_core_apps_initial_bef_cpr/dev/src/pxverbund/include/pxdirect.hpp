#ifndef PXDIRECT_INC
#define PXDIRECT_INC

#include "pxerrorloggable.hpp"

class pxSession;
class pxOrderItem;

class pxDirect : public pxErrorLoggable
{
public:
    pxDirect(pxSession *session, short FilialNr, pxOrderItem* Item);
    virtual ~pxDirect();

    long BookIBT  (const long q, const long IBTCustomerNo, const short nleveltypeid = 0);
    void UnBookIBT(const long q, const long IBTCustomerNo);

	bool IsRemQuotaExeeded() const { return RemQuotaExeeded_;}

private:
	long CheckRemArtQuota(const long Qty);
    void UndoRemArtQuota(const long Qty);

    short             FilialNr_;           // Filialnummer
    pxOrderItem*      Item_;               // Position
    pxSession*        Session_;
    bool              RemQuotaExeeded_;    // ArticleQouta exeeded
};

#endif
