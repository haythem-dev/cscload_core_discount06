#ifndef COLLECT_INC
#define COLLECT_INC

#include "ndefs.h"

class nCollectable
{

public:

                      nCollectable()    {; }
    virtual           ~nCollectable()   {; }
    virtual int       CompareTo(const nCollectable * c, 
                                void *               /*p*/       = NULL,
                                const long           /*lparm*/   = 0   ) const
                      {
                          // avoid compiler warning "unused"
                          //if (lparm)
                          //    p = p;

                          return this == c ? 0 : (this > c ? 1 : -1);
                      }

    virtual unsigned int Hash() const      { return 0; }
    virtual bool     IsEqual(const nCollectable* c) const { return this == c; }
};

#endif
