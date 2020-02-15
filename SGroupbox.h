#ifndef SGROUPBOX_H
#define SGROUPBOX_H

class SGroupbox : public SButton
{
    public:
        SGroupbox(SWindow * pWindow, UINT uStyle = 0, UINT uId = 0, UINT uExStyle = 0);
        virtual ~SGroupbox();
};

#endif
