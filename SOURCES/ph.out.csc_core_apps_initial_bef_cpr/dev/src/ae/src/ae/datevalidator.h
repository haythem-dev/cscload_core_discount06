#ifndef DATEVALIDATOR_H
#define DATEVALIDATOR_H

#include <libscgm_ivalidator.h>

class DateValidator : public scgui::IValidator
{
    public:
        DateValidator();
        virtual ~DateValidator();

        virtual bool isEntryValid(const CString& entry);
        virtual void showPostValidationMessage();
    
    private:
        void MessageWrongDate();

};


#endif