#ifndef GUARD_MSV3ORDERLABELPROCESSOR
#define GUARD_MSV3ORDERLABELPROCESSOR

#include <libbasarcmnutil_bstring.h>
#include <set>

class pxOrderTransmit;

class MSV3OrderLabelProcessor
{
public:
	MSV3OrderLabelProcessor();
	virtual ~MSV3OrderLabelProcessor();

	void init(pxOrderTransmit* xmit, const basar::VarString& ordertype, const long orderperiodid);

	const basar::VarString		processLabel(const basar::VarString& label);
	
private:
	unsigned long				m_MaxNumberOfOrderLabels;
	basar::VarString			m_DefaultOrderLabel;
	std::set<basar::VarString>	m_UsedOrderLabels;
	bool						m_UsageOfCustomOrderLabelsAllowed;

};


#endif // GUARD_MSV3ORDERLABELPROCESSOR
