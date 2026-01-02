#ifndef GUARD_IBTORDERIMPORT_DOMMOD_IPXTASKCONTROL_H
#define GUARD_IBTORDERIMPORT_DOMMOD_IPXTASKCONTROL_H

//----------------------------------------------------------------------------//
// class declaration setcion
//----------------------------------------------------------------------------//
namespace ibtorderimport {
namespace domMod {

class IPxTaskControl
{			
    public:		
        virtual ~IPxTaskControl(){};

		virtual void setHeartBeat() = 0;		
};

}
}

#endif  // GUARD_IBTORDERIMPORT_DOMMOD_IPXTASKCONTROL_H
