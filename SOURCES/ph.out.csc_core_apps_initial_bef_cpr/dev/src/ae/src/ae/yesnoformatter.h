
#ifndef YESNOFORMATTER_H
#define YESNOFORMATTER_H


#include <libscgm_iformatter.h>

class YesNoFormatter : public scgui::IFormatter
{
    public:
        YesNoFormatter();
        virtual ~YesNoFormatter();

        virtual CString format(const CString& entry);

};

#endif