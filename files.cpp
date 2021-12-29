//---------------------------------------------------------------------------


#pragma hdrstop

#include <stdio.h>
#include <Windows.h>
#include "files.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

FILE *configF;
int databits;
int paritybits;
int stopbits;
char *serialport_name;
bool CR_enabled;
bool LF_enabled;
bool audiofiles;

void config_file_save(void){
        configF = fopen("Serial_configuration.txt", "w");
        fprintf(configF, "Config file for Serial port configurator contents:");
        fprintf(configF, "\nSerial port: ");
        fprintf(configF, "\nBaud Rate: ");
        fprintf(configF, "\nData Bits: ");
        fprintf(configF, "\nStop Bits: ");
        fprintf(configF, "\nParity: ");
        fprintf(configF, "\nCR: ");
        fprintf(configF, "\nLF: ");
}

int config_file_exist(void){
        configF = fopen("Serial_configuration.txt", "rb"); // looking for file "MainConfig.cfg"
	if (!configF)
                return false;
        else
                return true;
}

void audiofiles_search(void){
   if ( GetFileAttributes("Resources/send_im.wav") != INVALID_FILE_ATTRIBUTES)
        if ( GetFileAttributes("Resources/im_recv.wav") != INVALID_FILE_ATTRIBUTES)
                audiofiles = true;
}






