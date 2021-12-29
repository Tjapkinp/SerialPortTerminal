//---------------------------------------------------------------------------

#include <vcl.h>
#include <Windows.h>
#pragma hdrstop

#include "serialport_main.h"
#include "serialport_settings.h"
#include "files.h"
#include "serial_func.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

Tmain_form *main_form;

int config_changed;
int first_try;

//---------------------------------------------------------------------------
__fastcall Tmain_form::Tmain_form(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Tmain_form::FormCreate(TObject *Sender)
{
   serial_port_connected = false;
   config_changed = false;
   first_try = true;
   RX_timer->Enabled = false;
   audiofiles = false;
}
//---------------------------------------------------------------------------
void __fastcall Tmain_form::FormClose(TObject *Sender,TCloseAction &Action)
{
   if(config_changed)
        config_file_save();
}
//---------------------------------------------------------------------------
void __fastcall Tmain_form::settings_buttonClick(TObject *Sender)
{
      params_form->Show();
}
//---------------------------------------------------------------------------
void __fastcall Tmain_form::tx_editKeyPress(TObject *Sender, char &Key)
{
        char *tx_char;

        if(Key == VK_RETURN){
                if (audiofiles)
                        PlaySoundA("Resources/send_im.wav", NULL, SND_FILENAME | SND_ASYNC);
                Key = 0; // избавление от надоедливого звука BEEP
                AnsiString str_text = main_form->tx_edit->Text;
                tx_char = str_text.c_str();
                tx_message(tx_char);
                if (delete_text->Checked == true) // удаление после ввода
                        main_form->tx_edit->Text = "";
        }
}
//---------------------------------------------------------------------------


void __fastcall Tmain_form::Timer1Timer(TObject *Sender)
{
        params_form->Show();
}
//---------------------------------------------------------------------------

void __fastcall Tmain_form::FormActivate(TObject *Sender)
{
        if(first_try){
                first_try = false;
                params_form->Show();
        }
}

//---------------------------------------------------------------------------

void __fastcall Tmain_form::CR_checkClick(TObject *Sender)
{
        switch_CR();        
}
//---------------------------------------------------------------------------

void __fastcall Tmain_form::LF_checkClick(TObject *Sender)
{
        switch_LF();
}
//---------------------------------------------------------------------------


void __fastcall Tmain_form::RX_timerTimer(TObject *Sender)
{
        rx_message();        
}
//---------------------------------------------------------------------------

void __fastcall Tmain_form::main_baudrate_comboboxChange(TObject *Sender)
{
       baudrate = StrToInt(main_baudrate_combobox->Text);
       if (baudrate_change(baudrate))
                        port_connected();
       else
                        port_disconnected();
       tx_edit->SetFocus();
}
//---------------------------------------------------------------------------



void __fastcall Tmain_form::audio_btnClick(TObject *Sender)
{
        if (audiofiles){
            audiofiles = false;
            audio_btn->Down = true;
            }
            else{
            audiofiles = true;
            audio_btn->Down = false;
            }
}
//---------------------------------------------------------------------------

