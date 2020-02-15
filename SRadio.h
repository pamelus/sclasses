#ifndef SRADIO_H
#define SRADIO_H

class SRadio : public SButton
{
    public:
        SRadio(SWindow * pWindow, UINT uStyle = 0, UINT uId = 0, UINT uExStyle = 0);
        virtual ~SRadio();
        
        virtual BOOL IsChecked();
        virtual DWORD SetChecked(BOOL isCheck);
};    

#endif
