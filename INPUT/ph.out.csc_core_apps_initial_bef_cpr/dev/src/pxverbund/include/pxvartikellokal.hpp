#ifndef PXVARTIKELLOKAL_HPP
#define PXVARTIKELLOKAL_HPP

#include "pxbase/pxrecord.hpp"
#include <date.hpp>

class pxOrder;
struct tVARTIKELLOKAL;

class pxVartikelLokal : public pxDBRecord
{
	public:
								pxVartikelLokal();

								pxVartikelLokal( pxSession *session );

								pxVartikelLokal( pxVartikelLokal& src );

								pxVartikelLokal( pxSession *session, tVARTIKELLOKAL& src );

								pxVartikelLokal( pxSession *session, long ArtikelNr, short FilialNr, DBAccessMode mode = cDBGET_READONLY );

		virtual					~pxVartikelLokal();
						
		pxVartikelLokal&		operator=( const tVARTIKELLOKAL& src );                  

		pxVartikelLokal&		operator=( const pxVartikelLokal& src );                  
                      
		virtual int				Get( DBAccessMode mode = cDBGET_READONLY );                 						
    
		short					FilialNr() const;
		long					ArtikelNr() const;
		long					Bestand() const;
		char					VerbundArtikel() const;
		short					getIBTType() const;
		short					getNLevelIBTTypeId() const;
		short					getIBTQtyAvailabilityPercentage() const;		
		nDate					getIBTDeliveryDateTime( pxOrder* order );
		nDate					getIBTDeliveryDateTime( pxOrder* order, bool& deliverypossible  );		

protected:

	bool						matchesIBTQtyAvailabilityPercentage(const long requestedQty) const;

	void						applyArticleQuota(const short branchno);

	friend pxVartikelLokal&		Assign(pxVartikelLokal& dest, const tVARTIKELLOKAL& src);

    friend tVARTIKELLOKAL&		Assign(tVARTIKELLOKAL& dest, const pxVartikelLokal& src);

	virtual long				SetQuantity(const long q);

    virtual int					CompareTo(const nCollectable *that, void *p, const long lparm) const;

    void						Init();

    short						FilialNr_;
    long						ArtikelNr_;
    long						Bestand_;
    char						Artikelaktiv_;
    char						VerbundArtikel_;
	short						NLevelIBTTypeID_;
	short						IBTQtyAvailabilityPercentage_;
	nDate						DeliveryDateTime_;

private:

    friend class pxVartikelLokalList;
};

#endif /* PXVARTIKELLOKAL_HPP */
