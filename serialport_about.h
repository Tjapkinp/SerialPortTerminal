//---------------------------------------------------------------------------

#ifndef serialport_aboutH
#define serialport_aboutH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class Tabout_form : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
private:	// User declarations
public:		// User declarations
        __fastcall Tabout_form(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tabout_form *about_form;
//---------------------------------------------------------------------------
#endif
