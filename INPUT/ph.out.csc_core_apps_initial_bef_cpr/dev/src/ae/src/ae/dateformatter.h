
#ifndef DATEFORMATTER_H
#define DATEFORMATTER_H


#include <libscgm_iformatter.h>

class DateFormatter : public scgui::IFormatter
{
    public:
        DateFormatter();
        virtual ~DateFormatter();

        virtual CString format(const CString& entry);

};

#endif