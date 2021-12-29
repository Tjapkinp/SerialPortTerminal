//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("serialport_main.cpp", main_form);
USEFORM("serialport_about.cpp", about_form);
USEFORM("serialport_settings.cpp", params_form);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "¬заимодействие с последовательным портом";
                 Application->CreateForm(__classid(Tmain_form), &main_form);
                 Application->CreateForm(__classid(Tabout_form), &about_form);
                 Application->CreateForm(__classid(Tparams_form), &params_form);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
