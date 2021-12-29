//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "serial_func.h"
#include "files.h"
#include "serialport_main.h"
#include "serialport_settings.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tparams_form *params_form;
//---------------------------------------------------------------------------
__fastcall Tparams_form::Tparams_form(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall Tparams_form::FormCreate(TObject *Sender)
{
        if (!serial_port_connected){
                list_serialports_available();
        }
        paritybits_combobox->ItemIndex = 0;
        stopbits_combobox->ItemIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall Tparams_form::btn_set_paramsClick(TObject *Sender)
{
        if (serial_port_connected){
              serial_port_close();
              port_disconnected();
        }
        else
        {
                AnsiString com_port = serialport_combobox->Text;
                baudrate = StrToInt(baudrate_combobox->Text);
                // 0=ONESTOPBIT; 1=ONE5STOPBITS; 2=TWOSTOPBITS
                int stopbits_index = stopbits_combobox->ItemIndex;
                int numbits = StrToInt(databits_combobox->Text);  // 4,5,6,7,8
                // NOPARITY=0; ODDPARITY=1; EVENPARITY=2; MARKPARITY=3;SPACEPARITY=4
                int paritybits_index = paritybits_combobox->ItemIndex;

                serialport_open(com_port.c_str());
                if (serialport_settings_chg(baudrate, numbits, stopbits_index, paritybits_index)){
                        port_connected();
                        audiofiles_search();
                        params_form->Close();
                }
                else
                        port_disconnected();
        }
}
//---------------------------------------------------------------------------

