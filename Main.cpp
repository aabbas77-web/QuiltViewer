//---------------------------------------------------------------------------
#include <vcl.h>
#include <math.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain *FormMain;
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::SolveEllipse(TPoint Start,TPoint End,TPoint Center,TPoint &Radius)
{
	double Sx,Sy,Ex,Ey,Tx,Ty;
    double MakamX,MakamY;
    double ValueX,ValueY;
    Sx = Start.x;
    Sy = Start.y;
    Ex = End.x;
    Ey = End.y;
    Tx = Center.x;
    Ty = Center.y;

    MakamX = 2*Ey*Ty-Ey*Ey+Sy*Sy-2*Sy*Ty;
    MakamY = -Ex*Ex+2*Ex*Tx+Sx*Sx-2*Sx*Tx;
    ValueX = -(-
		Ex*Ex*Sy*Sy+2*Ex*Ex*Sy*Ty-Ex*Ex*Ty*Ty+Sx*Sx*Ty*Ty+2*Ex*Tx*Sy*Sy-
		4*Ex*Tx*Sy*Ty+2*Ex*Tx*Ty*Ty-2*Ey*Ey*Sx*Tx-
		Tx*Tx*Sy*Sy+2*Tx*Tx*Sy*Ty+Ey*Ey*Sx*Sx-2*Tx*Tx*Ey*Ty+Tx*Tx*Ey*Ey-
		2*Ey*Ty*Sx*Sx+4*Ey*Ty*Sx*Tx-2*Sx*Tx*Ty*Ty);
    ValueY = (-
		Ex*Ex*Sy*Sy+2*Ex*Ex*Sy*Ty-Ex*Ex*Ty*Ty+Sx*Sx*Ty*Ty+2*Ex*Tx*Sy*Sy-
		4*Ex*Tx*Sy*Ty+2*Ex*Tx*Ty*Ty-2*Ey*Ey*Sx*Tx-
		Tx*Tx*Sy*Sy+2*Tx*Tx*Sy*Ty+Ey*Ey*Sx*Sx-2*Tx*Tx*Ey*Ty+Tx*Tx*Ey*Ey-
		2*Ey*Ty*Sx*Sx+4*Ey*Ty*Sx*Tx-2*Sx*Tx*Ty*Ty); 

    Radius.x = 0;
    Radius.y = 0;

    if((MakamX <= 0.0) || (MakamY <= 0.0) || (ValueX <= 0.0) || (ValueY <= 0.0))
    {
	    Radius.x = sqrt((Sx-Tx)*(Sx-Tx)+(Sy-Ty)*(Sy-Ty));
    	Radius.y = Radius.x;
        return;
    }

    if((MakamX != 0.0) && (MakamY != 0.0))
    {
	    if(ValueX/MakamX >= 0.0)
        {
        	Radius.x = sqrt(ValueX/MakamX);
        }
	    if(ValueY/MakamY >= 0.0)
        {
        	Radius.y = sqrt(ValueY/MakamY);
        }
        return;
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::LoadQuiltingFile(AnsiString strFileName)
{
	TStringList *m_pList;
	m_pList = new TStringList();

    m_pList->LoadFromFile(strFileName);
    for(int i=0;i<m_pList->Count;)
    {
        if(m_pList->Strings[i] == "")
        {
            m_pList->Delete(i);
        }
        else
        {
            i++;
        }
    }

	QuiltingFile.clear();
	AnsiString strText;
    ql_Stitch QuiltingStitch;
    int nPos;
	for(int i=0;i<m_pList->Count;i++)
    {
    	strText = m_pList->Strings[i].Trim();

		// Type
		nPos = strText.Pos(' ');
        if(nPos < 0)	break;
		QuiltingStitch.Type = StrToInt(strText.SubString(1,nPos-1));
        strText.Delete(1,nPos);

		// X1
		nPos = strText.Pos(' ');
        if(nPos < 0)	break;
		QuiltingStitch.Start.x = StrToInt(strText.SubString(1,nPos-1));
        strText.Delete(1,nPos);

		// Y1
		nPos = strText.Pos(' ');
        if(nPos < 0)	break;
		QuiltingStitch.Start.y = StrToInt(strText.SubString(1,nPos-1));
        strText.Delete(1,nPos);

		// X2
		nPos = strText.Pos(' ');
        if(nPos < 0)	break;
		QuiltingStitch.End.x = StrToInt(strText.SubString(1,nPos-1));
        strText.Delete(1,nPos);

		// Y2
		nPos = strText.Pos(' ');
        if(nPos < 0)	break;
		QuiltingStitch.End.y = StrToInt(strText.SubString(1,nPos-1));
        strText.Delete(1,nPos);

		// X3
		nPos = strText.Pos(' ');
        if(nPos < 0)	break;
		QuiltingStitch.Center.x = StrToInt(strText.SubString(1,nPos-1));
        strText.Delete(1,nPos);

		// Y3
		nPos = strText.Pos(' ');
        if(nPos < 0)	break;
		QuiltingStitch.Center.y = StrToInt(strText.SubString(1,nPos-1));
        strText.Delete(1,nPos);

		// Direction
		nPos = strText.Pos(' ');
        if(nPos < 0)	break;
		QuiltingStitch.Direction = StrToInt(strText.SubString(1,nPos-1));
        strText.Delete(1,nPos);

		// Speed
		QuiltingStitch.Speed = StrToInt(strText);

        QuiltingFile.push_back(QuiltingStitch);
    }

	if(m_pList)
    {
     	delete m_pList;
        m_pList = NULL;
    }

    Ax = 0.02;
    Bx = 0.0;
    Ay = 0.02;
    By = 0.0;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ClearImage()
{
	Image->Canvas->Brush->Style = bsSolid;
	Image->Canvas->Brush->Color = clWhite;
	Image->Canvas->Pen->Color = clWhite;
    Image->Canvas->FillRect(Rect(0,0,Image->Width,Image->Height));
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Draw()
{
	ClearImage();
    Image->Picture->Bitmap->Width = 1024;
    Image->Picture->Bitmap->Height = 768;
    dHeight = Image->Picture->Bitmap->Height;                      
    ql_Stitch QuiltingStitch;
	for(UINT i=0;i<QuiltingFile.size();i++)
    {
		QuiltingStitch = QuiltingFile[i];
        switch(QuiltingStitch.Type)
        {
         	case -1:// End Of File
            {
             	break;
            }
         	case 0:// Continous Line
            {
				Image->Canvas->Pen->Color = clBlack;
				Image->Canvas->Pen->Style = psSolid;
				Image->Canvas->MoveTo(Ax*QuiltingStitch.Start.x+Bx,dHeight-1-Ay*QuiltingStitch.Start.y+By);
				Image->Canvas->LineTo(Ax*QuiltingStitch.End.x+Bx,dHeight-1-Ay*QuiltingStitch.End.y+By);
             	break;
            }
         	case 1:// Continous Arc
            {
                TPoint Radius;
                TPoint P1,P2,P3,P4;

            	SolveEllipse(QuiltingStitch.Start,QuiltingStitch.End,QuiltingStitch.Center,Radius);
				P1.x = QuiltingStitch.Center.x - Radius.x;
				P1.y = QuiltingStitch.Center.y - Radius.y;
				P2.x = QuiltingStitch.Center.x + Radius.x;
				P2.y = QuiltingStitch.Center.y + Radius.y;

                if(!QuiltingStitch.Direction)
                {
	                P3.x = QuiltingStitch.Start.x;
	                P3.y = QuiltingStitch.Start.y;
	                P4.x = QuiltingStitch.End.x;
	                P4.y = QuiltingStitch.End.y;
                }
                else
				{
	                P3.x = QuiltingStitch.End.x;
	                P3.y = QuiltingStitch.End.y;
	                P4.x = QuiltingStitch.Start.x;
	                P4.y = QuiltingStitch.Start.y;
				}
				Image->Canvas->Pen->Color = clBlack;
				Image->Canvas->Pen->Style = psSolid;
                Image->Canvas->Arc(Ax*P1.x+Bx,dHeight-1-Ay*P1.y+By,Ax*P2.x+Bx,dHeight-1-Ay*P2.y+By,Ax*P3.x+Bx,dHeight-1-Ay*P3.y+By,Ax*P4.x+Bx,dHeight-1-Ay*P4.y+By);
             	break;
            }
         	case 2:// Discret Line
            {
				Image->Canvas->Pen->Color = clBlack;
				Image->Canvas->Pen->Style = psDot;
				Image->Canvas->MoveTo(Ax*QuiltingStitch.Start.x+Bx,dHeight-1-Ay*QuiltingStitch.Start.y+By);
				Image->Canvas->LineTo(Ax*QuiltingStitch.End.x+Bx,dHeight-1-Ay*QuiltingStitch.End.y+By);
             	break;
            }
        }
//        Application->ProcessMessages();
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Open1Click(TObject *Sender)
{
	if(OpenDialogDat->Execute())
    {
    	LoadQuiltingFile(OpenDialogDat->FileName);
    	Caption = "Designer ["+OpenDialogDat->FileName+"]";
        Draw();
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Exit1Click(TObject *Sender)
{
	Close();	
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormCreate(TObject *Sender)
{
	Left = 0;
    Top = 0;
    Width = Screen->Width;
    Height = Screen->Height;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::FormDestroy(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

