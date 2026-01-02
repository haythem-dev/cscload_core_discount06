//-------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief Domain module article
 *  \author
 *  \date
 */
//-------------------------------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PREPARATION_CICSPHARMOSTRANSACTIONRECORD_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PREPARATION_CICSPHARMOSTRANSACTIONRECORD_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include "transactionrecordbase.h"

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
namespace basar
{
	namespace db
	{
		namespace aspect
		{
            //class AccessorInstanceRef;
			//class ConnectionRef;
			class AccessorPropertyTable_YIterator;
			//class AccessorPropertyTableRef;
		}
	}
}

//-------------------------------------------------------------------------------------------------//
// namespace section
//-------------------------------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace preparation
{
    //-------------------------------------------------------------------------------------------------//
    // class declaration section
    //-------------------------------------------------------------------------------------------------//
    /*!\brief  */
	class CICSPharmosTransactionRecord : public core::TransactionRecordBase
	{

		public:
			struct ProcessingStatus
			{
				static basar::ConstString OPEN; // ( " " );
			};
        //--------------------------------------------------------------------------------------------------//
        // object declaration section
        //--------------------------------------------------------------------------------------------------//
	    public:

			CICSPharmosTransactionRecord( basar::db::aspect::AccessorPropertyTable_YIterator yitTransactionRecord, AccessorInstanceRefWrapper& acc, libcsc_utils::ICSC_LoggerPtr csc_logger );
		    ~CICSPharmosTransactionRecord();

            virtual void                                        startProcessing();
            virtual void                                        finishProcessing();

            virtual void                                        log();

			virtual basar::DateTime						getKbvzDX01DateTime() const;
			virtual basar::Int32							getKbvzDX01Date() const;
			virtual basar::Int32							getKbvzOffset() const;
			virtual basar::VarString						getKbvzKSC() const;
			virtual basar::Int32							getKbvzKSCTime() const;
			virtual basar::Int32							getKbvzDX01Time() const;
			virtual basar::Int32							getKbvzLfdNr() const;
			virtual basar::Int16							getKbvzFil() const;
			virtual basar::Int32							getKbvzPZN() const;
			virtual basar::Int32							getKbvzMeng() const;
			virtual basar::Int16							getKbvzBukz() const;
			virtual basar::Int32							getKbvzTime() const;
			virtual basar::Int32							getKbvzDate() const;
			virtual basar::VarString						getKbvzLgfnr() const;
			virtual basar::Int32							getKbvzKSCAnr() const;
			virtual basar::VarString						getKbvzLgnr() const;
			virtual basar::VarString						getKbvzStat() const;
			virtual basar::VarString						getKbvzET3() const;
			virtual basar::VarString						getKbvzWber() const;
			virtual basar::Int32							getKbvzVerf() const;
			virtual basar::Int32							getKbvzP1Pos() const;
			virtual basar::Decimal						getKbvzGEP() const;
			virtual basar::Decimal						getKbvzAEP() const;
			virtual basar::Decimal						getKbvzAVP() const;
			virtual basar::VarString						getKbvzKVerf() const;
			virtual basar::VarString						getKbvzKLgfnr() const;
			virtual basar::VarString						getKbvzKGEP() const;
			virtual basar::VarString						getKbvzKAEP() const;
			virtual basar::VarString						getKbvzKAVP() const;
			virtual basar::Int16							getKbvzMFil() const;
			virtual basar::VarString						getKbvzStatus() const;
			virtual basar::VarString						getKbvzExport() const;
			virtual basar::Decimal						getKbvzWert() const;
			virtual basar::VarString						getKbvzCloSa() const;
			virtual basar::VarString						getKbvzCloZeit() const;
			virtual basar::Int32							getKbvzCloAnr() const;
			virtual basar::Int32							getKbvzCloPos() const;
			virtual basar::VarString						getKbvzCharge() const;
			virtual basar::VarString						getKbvzBatch() const;
			virtual basar::Int32							getKbvzDailyClosing() const;
			virtual basar::Int32							getKbvzBeslaNr() const;

			virtual basar::VarString						getType() const;

		protected:
			virtual const basar::VarString&						getSaveAccessMethod() const;

	    private:

		    CICSPharmosTransactionRecord( const CICSPharmosTransactionRecord& );
		    CICSPharmosTransactionRecord& operator= ( const CICSPharmosTransactionRecord& );

			virtual basar::VarString						getKbvzArt() const;
	};

} // namespace preparation
} // namespace pharmosTransaction
} // end namespace domMod

#endif // GUARD_DOMMOD_PHARMOSTRANSACTION_PREPARATION_CICSPHARMOSTRANSACTIONRECORD_H

