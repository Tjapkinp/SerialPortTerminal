//---------------------------------------------------------------------------

#ifndef serialport_settingsH
#define serialport_settingsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class Tparams_form : public TForm
{
__published:	// IDE-managed Components
        TLabel *port_label;
        TComboBox *serialport_combobox;
        TLabel *baudrate_label;
        TComboBox *baudrate_combobox;
        TLabel *databits_label;
        TComboBox *databits_combobox;
        TLabel *paritybits_label;
        TComboBox *paritybits_combobox;
        TLabel *stopbits_label;
        TComboBox *stopbits_combobox;
        TImage *status_light_img;
        TButton *btn_set_params;
        TLabel *status_label;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall btn_set_paramsClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall Tparams_form(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tparams_form *params_form;
//---------------------------------------------------------------------------
#endif
