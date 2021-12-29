//---------------------------------------------------------------------------

#ifndef filesH
#define filesH
//---------------------------------------------------------------------------
void config_file_save(void);
int config_file_exist(void);
void audiofiles_search(void);

extern int databits;
extern int paritybits;
extern int stopbits;
extern char *serialport_name;
extern bool CR_enabled;
extern bool LF_enabled;
extern bool audiofiles;

#endif
