#ifndef SPROGRESS_H
#define SPROGRESS_H

class SProgress : public SWindow
{
    public:
        SProgress(SWindow * pWin);
        virtual ~SProgress();
        
        virtual DWORD SetRange(DWORD dwRange);
        virtual DWORD MoveTo(DWORD iPos);
        virtual DWORD Move(DWORD iMove);
        virtual DWORD StepIt();
        
        virtual DWORD GetRange() const;
        virtual DWORD GetCurrentPosition() const;
};    

#endif
