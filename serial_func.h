//---------------------------------------------------------------------------

#ifndef serial_funcH
#define serial_funcH

int serialport_open(char port[5]);
void serial_port_close(void);
int serialport_settings_chg(int BaudRate, int Num_bits, int NumStopbits, int Parity);
int baudrate_change(int BaudRate);
void list_serialports_available(void);
void tx_message(char command[256]);
void rx_message(void);
void port_connected(void);
void port_disconnected(void);
void switch_CR(void);
void switch_LF(void);

extern HANDLE serialport;
extern char COM_PORT[16];
extern int serial_port_connected;
extern int CR_symb;
extern int baudrate;
extern int LF_symb;
//---------------------------------------------------------------------------
#endif
