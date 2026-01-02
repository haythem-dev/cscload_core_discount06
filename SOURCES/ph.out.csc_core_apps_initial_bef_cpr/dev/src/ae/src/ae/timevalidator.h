#ifndef TIMEVALIDATOR_H
#define TIMEVALIDATOR_H

#include <libscgm_ivalidator.h>

class TimeValidator : public scgui::IValidator
{
    public:
        TimeValidator();
        virtual ~TimeValidator();

        virtual bool isEntryValid(const CString& entry);
        virtual void showPostValidationMessage();

};



#endif