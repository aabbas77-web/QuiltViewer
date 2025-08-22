//---------------------------------------------------------------------------
#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#include <vector.h>
//---------------------------------------------------------------------------
//----------------------------Quilting---------------------------------------
//---------------------------------------------------------------------------
struct ql_Stitch
{
	int Type;
	TPoint Start;
    TPoint End;
    TPoint Center;
    int Direction;
    int Speed;    
};
//---------------------------------------------------------------------------
typedef vector<ql_Stitch> ql_File; 
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
__published:	// IDE-managed Components
        TOpenDialog *OpenDialogDat;
        TMainMenu *MainMenu1;
        TMenuItem *File1;
        TMenuItem *Open1;
        TMenuItem *N1;
        TMenuItem *Exit1;
	TScrollBox *ScrollBox1;
	TImage *Image;
	void __fastcall Open1Click(TObject *Sender);
	void __fastcall Exit1Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormMain(TComponent* Owner);
		void __fastcall LoadQuiltingFile(AnsiString strFileName);
		void __fastcall ClearImage();
		void __fastcall Draw();
		void __fastcall SolveEllipse(TPoint Start,TPoint End,TPoint Center,TPoint &Radius);
        ql_File QuiltingFile;
        double Ax,Bx;
        double Ay,By;
        double dHeight;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain *FormMain;
//---------------------------------------------------------------------------
#endif
