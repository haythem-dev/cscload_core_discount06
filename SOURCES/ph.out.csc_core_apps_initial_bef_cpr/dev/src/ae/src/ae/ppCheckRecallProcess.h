#pragma once

//(c)---------- CustomerOrderSetting ClassModel ------------------------//
/*
   Source: ppCheckRecallProcess.h
   Author: A.Schmidt-Rehschuh
   made  : 26.09.2000
                            >No changes in this text may be made<
   declaration:

*/

#include "ppcustomercallplanday.h"
#include "ppdatatypes.h"
#include "pperror.h"

class CMCUSTOMERCALLPLANRECALLINWORK;

class ppCheckRecallProcess : virtual public ppError
{
public:
    enum t_check
    {
        is_ok          = 0,
        is_error       = 1,
        is_in_use      = 2,
        is_used_by_own = 3,
        is_deleted     = 4
    };

public: //constructor
    ppCheckRecallProcess(const ppCustomerCallPlanDay* pCallPlan,
                         const long lUID,
                         const short sBranchNo);
    ~ppCheckRecallProcess();

public: //unique selection from data
    bool CheckEntry();
    bool DeleteEntry();
    bool UpdateEntry();

public: //Data: Set- and Getmethodes
    void SetUID(const long l);
    const t_check GetCheckState() const;

protected: //data-members
    const ppCustomerCallPlanDay*    m_pCallPlan;
    CMCUSTOMERCALLPLANRECALLINWORK* m_srvPlan;
    CMCUSTOMERCALLPLANRECALLINWORK* m_srvPlanUP;
    t_check                         m_eCheck;

protected: //methodes
    bool SetEntry();
    bool IsInitialized();
};
