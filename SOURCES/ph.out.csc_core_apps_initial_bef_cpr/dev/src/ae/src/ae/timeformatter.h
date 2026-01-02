#ifndef TIMEFORMATTER_H
#define TIMEFORMATTER_H

#include <libscgm_iformatter.h>

class TimeFormatter : public scgui::IFormatter
{
    public:
        TimeFormatter();
        virtual ~TimeFormatter();

        CString format(const CString& entry);

};


#endif