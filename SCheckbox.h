#ifndef SCHECKBOX_H
#define SCHECKBOX_H

class SCheckbox : public SButton
{
    public:
        SCheckbox(SWindow * pWindow, UINT uStyle = 0, UINT uId = 0, UINT uExStyle = 0);
        virtual ~SCheckbox();
        
        virtual BOOL IsChecked();
        virtual DWORD SetChecked(BOOL isCheck);
};    

#endif
