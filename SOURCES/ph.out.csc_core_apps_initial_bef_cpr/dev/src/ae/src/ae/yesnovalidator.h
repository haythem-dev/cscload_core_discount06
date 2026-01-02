#ifndef YESNOVALIDATOR_H
#define YESNOVALIDATOR_H

#include <libscgm_ivalidator.h>

class YesNoValidator : public scgui::IValidator
{
    public:
        YesNoValidator();
        virtual ~YesNoValidator();

        virtual bool isEntryValid(const CString& entry);
        virtual void showPostValidationMessage();
    
    private:
        void MessageWrongYesNo();

};


#endif