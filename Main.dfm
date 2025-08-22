object FormMain: TFormMain
  Left = 181
  Top = 119
  Width = 696
  Height = 472
  Caption = 'Designer'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object ScrollBox1: TScrollBox
    Left = 0
    Top = 0
    Width = 680
    Height = 413
    Align = alClient
    TabOrder = 0
    object Image: TImage
      Left = 0
      Top = 0
      Width = 105
      Height = 105
      AutoSize = True
    end
  end
  object OpenDialogDat: TOpenDialog
    DefaultExt = 'dat'
    Filter = 'Dat Files (*.dat)|*.dat'
    Left = 204
    Top = 108
  end
  object MainMenu1: TMainMenu
    Left = 172
    Top = 140
    object File1: TMenuItem
      Caption = '&File'
      object Open1: TMenuItem
        Caption = '&Open...'
        OnClick = Open1Click
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Exit1: TMenuItem
        Caption = 'E&xit'
        ShortCut = 16472
        OnClick = Exit1Click
      end
    end
  end
end
