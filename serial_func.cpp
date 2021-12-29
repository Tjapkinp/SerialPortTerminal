//---------------------------------------------------------------------------


#pragma hdrstop

#include <Windows.h>
#include <stdio.h>
#include "serialport_main.h"
#include "serialport_settings.h"
#include "serial_func.h"
#include "files.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

DWORD dwBytesWritten;    // number of transmitted bytes
HANDLE serialport;
char COM_PORT[16];
int serial_port_connected;
int baudrate;
int stopbits_index;
int CR_symb;
int LF_symb;
// Initialize serial port
int serialport_open(char port[5])
{
	sprintf(COM_PORT, "\\\\.\\%s", port); // for WIN API
        //sprintf(COM_PORT, "\\\\.\\COM%c", port); // for WIN API
	serialport = CreateFile(COM_PORT,
        GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

	if (serialport == INVALID_HANDLE_VALUE){
		//MessageBox(NULL, "Cannot open serial port!", "Error", MB_OK);
                return 0;
        }
        else
                return 1;
}

void serial_port_close(void){
        PurgeComm(serialport, PURGE_RXCLEAR|PURGE_TXCLEAR);
        CloseHandle(serialport);
}

int serialport_settings_chg(int BaudRate, int Num_bits, int NumStopbits, int Parity)
{
        DCB dcbSerialParams = { 0 };
	COMMTIMEOUTS tm_outs;

	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

        if (!GetCommState(serialport, &dcbSerialParams))
                        return 0;
			//MessageBox(NULL, "SigB - getting serial port state error!", "Error", MB_OK);
        GetCommTimeouts(serialport, &tm_outs);

	if (BaudRate != 0) // 110,300,600,1200,2400,4800,9600,14400,19200,38400,56000,57600,115200,128000,256000
		dcbSerialParams.BaudRate = BaudRate;
	dcbSerialParams.ByteSize = Num_bits; // 4,5,6,7,8
	dcbSerialParams.StopBits = NumStopbits; // 0=ONESTOPBIT; 1=ONE5STOPBITS; 2=TWOSTOPBITS
	dcbSerialParams.Parity = Parity; // NOPARITY=0; ODDPARITY=1; EVENPARITY=2; MARKPARITY=3;SPACEPARITY=4

	// CommTimeouts
	tm_outs.ReadIntervalTimeout = 20;
	tm_outs.ReadTotalTimeoutMultiplier = 10;
	tm_outs.ReadTotalTimeoutConstant = 100;
	tm_outs.WriteTotalTimeoutMultiplier = 10;
	tm_outs.WriteTotalTimeoutConstant = 100;

        if (!SetCommState(serialport, &dcbSerialParams))
                return 0;
                //MessageBox(NULL, "SigA - setting serial port state error!", "Error", MB_OK);
        SetCommTimeouts(serialport, &tm_outs);

        return 1;
}

int baudrate_change(int BaudRate){
        DCB dcbSerialParams = { 0 };
        if (!GetCommState(serialport, &dcbSerialParams))
                        return 0;
	if (BaudRate != 0) // 110,300,600,1200,2400,4800,9600,14400,19200,38400,56000,57600,115200,128000,256000
		dcbSerialParams.BaudRate = BaudRate;
        if (!SetCommState(serialport, &dcbSerialParams))
                        return 0;
return 1;
}

void list_serialports_available(void){
        int i;
        int port_counter = 0;
        char port_chr;
        char com_name[6];
        for (i=0;i<20;i++){
                sprintf(com_name,"COM%d", i);
                if(serialport_open(com_name)){
                        serial_port_close();
                        //params_form->serialport_combobox->Items->Add(edit_item);
                        params_form->serialport_combobox->Items[port_counter].Text = com_name;
                        port_counter++;
                }

        }

        if (port_counter == 0){
                MessageBox(NULL, "COM-порты не были найдены на этом ПК!",
                 "Внимание!", MB_OK);
                 port_disconnected();
        }
        else
                params_form->serialport_combobox->ItemIndex = 0;
}

void tx_message(char *command)
{
	int command_length = strlen(command);
        if (CR_symb)
	        command[command_length++] = 13;
        if (LF_symb)
	        command[command_length++] = 10;
	//command[command_length++] = '\0';
	WriteFile(serialport, command, command_length, &dwBytesWritten, NULL);
}

void rx_message(void){
        int RXmode = 1;
	int symbCounter = 0;
	DWORD iSize;
	char sReceivedChar;
	AnsiString RX_Data;
        //char *RX_Data;
	while (RXmode)
	{
		ReadFile(serialport, &sReceivedChar, 1, &iSize, 0);
		if (iSize > 0){
                        RX_Data = RX_Data+sReceivedChar;
                        symbCounter++;
                }
		else
			RXmode = 0;
	}
        if (symbCounter != 0){
                main_form->rx_memo->Lines->Add(RX_Data);
                if (audiofiles)
                        PlaySoundA("Resources/im_recv.wav", NULL, SND_FILENAME | SND_ASYNC);
                }
}

void port_connected(void){
        params_form->status_label->Caption = "Подключено!";
        params_form->btn_set_params->Caption = "Отключить";
        params_form->status_label->Font->Color = clLime;
        params_form->status_light_img->Picture->LoadFromFile("Resources/GreenLight_img.jpg");
        main_form->rx_memo->Enabled = true;
        main_form->tx_edit->Enabled = true;
        serial_port_connected = true;
        params_form->serialport_combobox->Enabled = false;
        params_form->databits_combobox->Enabled = false;
        params_form->paritybits_combobox->Enabled = false;
        params_form->stopbits_combobox->Enabled = false;
        main_form->StatusBar1->Panels->Items[0]->Text = "Подключено";
        main_form->StatusBar1->Panels->Items[1]->Text = COM_PORT;
        main_form->StatusBar1->Panels->Items[2]->Text = IntToStr(baudrate);
        main_form->RX_timer->Enabled = true;
}

void port_disconnected(void){
        params_form->status_label->Caption = "Не подключено!";
        params_form->btn_set_params->Caption = "Подключить";
        params_form->status_label->Font->Color = clRed;
        params_form->status_light_img->Picture->LoadFromFile("Resources/RedLight_img.jpg");
        main_form->rx_memo->Enabled = false;
        main_form->tx_edit->Enabled = false;
        serial_port_connected = false;
        params_form->serialport_combobox->Enabled = true;
        params_form->databits_combobox->Enabled = true;
        params_form->paritybits_combobox->Enabled = true;
        params_form->stopbits_combobox->Enabled = true;
        main_form->RX_timer->Enabled = false;
}

void switch_LF(void){
        if(LF_symb){
                LF_symb = false;
                main_form->LF_check->Checked = false;
        }
        else{
                LF_symb = true;
                main_form->LF_check->Checked = true;
        }
}

void switch_CR(void){
        if(CR_symb){
                CR_symb = false;
                main_form->CR_check->Checked = false;
        }
        else{
                CR_symb = true;
                main_form->CR_check->Checked = true;
        }
}
