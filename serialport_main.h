//---------------------------------------------------------------------------

#ifndef serialport_mainH
#define serialport_mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <MPlayer.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class Tmain_form : public TForm
{
__published:	// IDE-managed Components
        TMemo *rx_memo;
        TEdit *tx_edit;
        TButton *settings_button;
        TCheckBox *CR_check;
        TCheckBox *LF_check;
        TStatusBar *StatusBar1;
        TTimer *RX_timer;
        TComboBox *main_baudrate_combobox;
        TCheckBox *delete_text;
        TSpeedButton *audio_btn;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall settings_buttonClick(TObject *Sender);
        void __fastcall tx_editKeyPress(TObject *Sender, char &Key);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall CR_checkClick(TObject *Sender);
        void __fastcall LF_checkClick(TObject *Sender);
        void __fastcall RX_timerTimer(TObject *Sender);
        void __fastcall main_baudrate_comboboxChange(TObject *Sender);
        void __fastcall audio_btnClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall Tmain_form(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tmain_form *main_form;

extern int first_try;
//---------------------------------------------------------------------------
#endif
