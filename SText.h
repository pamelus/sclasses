#ifndef STEXT_H
#define STEXT_H

class SText : public SWindow
{
    public:
        SText(SWindow * pWin, UINT uStyle);
        virtual ~SText();
};

class STextLeft : public SText
{
    public:
        STextLeft(SWindow * pWin);
        virtual ~STextLeft();
};

class STextCenter : public SText
{
    public:
        STextCenter(SWindow * pWin);
        virtual ~STextCenter();
};

class STextRight : public SText
{
    public:
        STextRight(SWindow * pWin);
        virtual ~STextRight();
};

#endif
