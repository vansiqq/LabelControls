unit LCTypes;

{$mode objfpc}{$H+}

interface

uses
  Forms, Classes, SysUtils, Graphics, Controls, StdCtrls;

type
  TEscapeAction = (eaBack, eaClear, eaClearBack, eaClose, eaNone);
  TLabelPosition = (lpAbove, lpBelow, lpLeft, lpRight);
  TMaskType = (mtData, mtTelefone, mtTelFixo, mtCelular, mtCPF, mtCNPJ, mtPIS, mtPlaca, mtCustom);
  TAlternableMask = set of (amData, amTelefone, amTelFixo, amCelular, amCPF, amCNPJ, amPIS, amPlaca);
  TEditType = (etInteger, etFloat, etCurrency, etPercent);

  { TBoundLabel }

  TBoundLabel = class(TCustomLabel)
  private
    function GetTop: Integer;
    function GetLeft: Integer;
    function GetWidth: Integer;
    function GetHeight: Integer;
    procedure SetHeight(const Value: Integer);
    procedure SetWidth(const Value: Integer);
  public
    constructor Create(AOwner: TComponent); override;
  published
    property Align;
    property Alignment;
    property Anchors;
    property AutoSize;
    property BiDiMode;
    property BorderSpacing;
    property Caption;
    property Color;
    property DragCursor;
    property DragKind;
    property DragMode;
    property Font;
    property Height: Integer read GetHeight write SetHeight;
    property Left: Integer read GetLeft;
    property ParentBiDiMode;
    property ParentColor;
    property ParentFont;
    property ParentShowHint;
    property PopupMenu;
    property ShowAccelChar;
    property ShowHint;
    property Top: Integer read GetTop;
    property Transparent;
    property Layout;
    property WordWrap;
    property Width: Integer read GetWidth write SetWidth;
    property OnClick;
    property OnContextPopup;
    property OnDblClick;
    property OnDragDrop;
    property OnDragOver;
    property OnEndDock;
    property OnEndDrag;
    property OnMouseDown;
    property OnMouseMove;
    property OnMouseUp;
    property OnStartDock;
    property OnStartDrag;
  end;

  { TColors }

  TColors = class(TPersistent)
  private
    FFocusColor,
    FRightColor,
    FWrongColor : TColor;
    function GetFocusColor: TColor;
    function GetRightColor: TColor;
    function GetWrongColor: TColor;
    procedure SetFocusColor(const AValue: TColor);
    procedure SetRightColor(const AValue: TColor);
    procedure SetWrongColor(const AValue: TColor);
  public
    constructor Create;
  published
    property FocusColor: TColor read GetFocusColor write SetFocusColor default $00FFEFDF;
    property RightColor: TColor read GetRightColor write SetRightColor default $00DFFFEF;
    property WrongColor: TColor read GetWrongColor write SetWrongColor default $00EFDFFF;
  end;

  { TAttributes }

  TAttributes = class(TPersistent)
  private
    FColors: TColors;
    FEscapeAction: TEscapeAction;
    FColorize,
    FEnterAsTab,
    FRequired    : Boolean;
    FParent      : TComponent;
    function GetColorize: Boolean;
    function GetEnterAsTab: Boolean;
    function GetEscapeAction: TEscapeAction;
    function GetRequired: Boolean;
    procedure SetColorize(const AValue: Boolean);
    procedure SetEnterAsTab(const AValue: Boolean);
    procedure SetEscapeAction(const AValue: TEscapeAction);
    procedure SetRequired(const AValue: Boolean);
  public
    constructor Create(TheParent: TComponent);
  published
    property Colors: TColors read FColors write FColors;
    property EscapeAction: TEscapeAction read GetEscapeAction write SetEscapeAction default eaBack;
    property Colorize: Boolean read GetColorize write SetColorize default True;
    property EnterAsTab: Boolean read GetEnterAsTab write SetEnterAsTab default True;
    property Required: Boolean read GetRequired write SetRequired default False;
  end;

  function  DDDCheck(ADDD: Byte): Boolean;
  function  CPFCheck(ACPF: String): Boolean;
  function  CNPJCheck(ACNPJ: String): Boolean;
  function  PISCheck(APIS: String): Boolean;

implementation

// Procedures e functions compartilhadas

function DDDCheck(ADDD: Byte): Boolean;
begin
  Result := ADDD in [11..19, 21, 22, 24, 27, 28, 31..35, 37, 38, 41..49, 51, 53..55, 61..69,
                     71, 73..77, 79, 81..89, 91..99];
end;

function CPFCheck(ACPF: String): Boolean;
var
  n1, n2, n3, n4, n5, n6, n7, n8, n9, d1, d2: Integer;
  rDigitado, rCalculado: String;
  rRet: Boolean;
begin
  rRet := True;
  ACPF := StringReplace(StringReplace(ACPF, '.', '', [rfReplaceAll]), '-', '', [rfReplaceAll]);
  n1 := StrToInt(ACPF[1]);
  n2 := StrToInt(ACPF[2]);
  n3 := StrToInt(ACPF[3]);
  n4 := StrToInt(ACPF[4]);
  n5 := StrToInt(ACPF[5]);
  n6 := StrToInt(ACPF[6]);
  n7 := StrToInt(ACPF[7]);
  n8 := StrToInt(ACPF[8]);
  n9 := StrToInt(ACPF[9]);

  d1 := n9* 2 + n8 * 3 + n7 * 4 + n6 * 5 + n5 * 6 + n4 * 7 + n3 * 8 + n2 * 9 + n1 * 10;
  d1 := 11 - (d1 mod 11);

  if d1 >= 10 then
    d1 := 0;

  d2 := d1 * 2 + n9 * 3 + n8 * 4 + n7 * 5 + n6 * 6 + n5 * 7 + n4 * 8 + n3 * 9 + n2 * 10 + n1 * 11;
  d2 := 11 - (d2 mod 11);

  if d2 >= 10 then
    d2 := 0;

  rRet := (ACPF <> '00000000000') and (ACPF <> '11111111111') and (ACPF <> '22222222222') and
          (ACPF <> '33333333333') and (ACPF <> '44444444444') and (ACPF <> '55555555555') and
          (ACPF <> '66666666666') and (ACPF <> '77777777777') and (ACPF <> '88888888888') and
          (ACPF <> '99999999999');

  rCalculado := IntToStr(d1) + IntToStr(d2);
  rDigitado := ACPF[10] + ACPF[11];

  Result := (rDigitado = rCalculado) and rRet;
end;

function CNPJCheck(ACNPJ: String): Boolean;
var
  rCNPJ: String;
  dg1, dg2, x, rTotal: Integer;
  rRet: Boolean;
begin
  rRet := False;
  rCNPJ := '';

  //Analisa os formatos
  if Length(ACNPJ) = 18 then
    if (Copy(ACNPJ, 3, 1) + Copy(ACNPJ, 7, 1) + Copy(ACNPJ, 11, 1) + Copy(ACNPJ, 16, 1) = '../-') then
    begin
      rCNPJ := Copy(ACNPJ, 1, 2) + Copy(ACNPJ, 4, 3) + Copy(ACNPJ, 8, 3) + Copy(ACNPJ, 12, 4) +
               Copy(ACNPJ, 17, 2);
      rRet := True;
    end;

  if Length(ACNPJ) = 14 then
  begin
    rCNPJ := ACNPJ;
    rRet := True;
  end;

  //Verifica
  if rRet then
  begin
    try
      //1° digito
      rTotal := 0;
      for x := 1 to 12 do
      begin
        if x < 5 then
          Inc(rTotal, StrToInt(Copy(rCNPJ, x, 1)) * (6 - x))
        else
          Inc(rTotal, StrToInt(Copy(rCNPJ, x, 1)) * (14 - x));
      end;

      dg1 := 11 - (rTotal mod 11);

      if dg1 > 9 then
        dg1 := 0;

      //2° digito
      rTotal := 0;
      for x := 1 to 13 do
      begin
        if x < 6 then
          Inc(rTotal, StrToInt(Copy(rCNPJ, x, 1)) * (7 - x))
        else
          Inc(rTotal, StrToInt(Copy(rCNPJ, x, 1)) * (15 - x));
      end;

      dg2 := 11 - (rTotal mod 11);

      if dg2 > 9 then
        dg2 := 0;

      //Validação final
      if (dg1 = StrToInt(Copy(rCNPJ, 13, 1))) and (dg2 = StrToInt(Copy(rCNPJ, 14, 1))) then
        rRet := True
      else
        rRet := False;
    except
      rRet := False;
    end;

    //Inválidos
    rRet := ((rCNPJ <> '00000000000000') and (rCNPJ <> '11111111111111') and (rCNPJ <> '22222222222222') and
             (rCNPJ <> '33333333333333') and (rCNPJ <> '44444444444444') and (rCNPJ <> '55555555555555') and
             (rCNPJ <> '66666666666666') and (rCNPJ <> '77777777777777') and (rCNPJ <> '88888888888888') and
             (rCNPJ <> '99999999999999')) and rRet;
  end;

  Result := rRet;
end;


function PISCheck(APIS: String): Boolean;
var
  i, rSoma, rM11, rDV, rDigito: Integer;
begin
  if Trim(APIS) <> '' then
  begin
    rDV := StrToInt(copy(APIS,11,1));
    rSoma := 0;
    rM11 := 2;

    for i := 1 to 10 do
    begin
      rSoma := rSoma + (rM11 * StrToInt(Copy(APIS,11 -i, 1)));

      if rM11 < 9 then
        rM11 := rM11+1
      else
        rM11 := 2;
    end;

    rDigito := 11 - (rSoma mod 11);

    if rDigito > 9 then
      rDigito := 0;

    Result := rDV = rDigito;
  end
  else
    Result := False;
end;


{ TBoundLabel }

constructor TBoundLabel.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  Name := 'SubLabel';
  SetSubComponent(True);
  if Assigned(AOwner) then
    Caption := AOwner.Name;
end;

function TBoundLabel.GetHeight: Integer;
begin
  Result := inherited Height;
end;

function TBoundLabel.GetLeft: Integer;
begin
  Result := inherited Left;
end;

function TBoundLabel.GetTop: Integer;
begin
  Result := inherited Top;
end;

function TBoundLabel.GetWidth: Integer;
begin
  Result := inherited Width;
end;

procedure TBoundLabel.SetHeight(const Value: Integer);
begin
  SetBounds(Left, Top, Width, Value);
end;

procedure TBoundLabel.SetWidth(const Value: Integer);
begin
  SetBounds(Left, Top, Value, Height);
end;

{ TColors }

function TColors.GetFocusColor: TColor;
begin
  Result := FFocusColor;
end;

function TColors.GetRightColor: TColor;
begin
  Result := FRightColor;
end;

function TColors.GetWrongColor: TColor;
begin
  Result := FWrongColor;
end;

procedure TColors.SetFocusColor(const AValue: TColor);
begin
  if FFocusColor <> AValue then
    FFocusColor := AValue;

end;

procedure TColors.SetRightColor(const AValue: TColor);
begin
  if FRightColor <> AValue then
    FRightColor := AValue;
end;

procedure TColors.SetWrongColor(const AValue: TColor);
begin
  if FWrongColor <> AValue then
    FWrongColor := AValue;
end;

constructor TColors.Create;
begin
  FFocusColor := $00FFEFDF;
  FRightColor := $00DFFFEF;
  FWrongColor := $00EFDFFF;
end;

{ TAttributes }

function TAttributes.GetColorize: Boolean;
begin
  Result := FColorize;
end;

function TAttributes.GetEnterAsTab: Boolean;
begin
  Result := FEnterAsTab;
end;

function TAttributes.GetEscapeAction: TEscapeAction;
begin
  Result := FEscapeAction;
end;

function TAttributes.GetRequired: Boolean;
begin
  Result := FRequired;
end;

procedure TAttributes.SetColorize(const AValue: Boolean);
begin
  if FColorize <> AValue then
  begin
    if FRequired then
      FColorize := True
    else
      FColorize := AValue;
  end;
end;

procedure TAttributes.SetEnterAsTab(const AValue: Boolean);
begin
  FEnterAsTab := AValue;
end;

procedure TAttributes.SetEscapeAction(const AValue: TEscapeAction);
begin
  if FEscapeAction <> AValue then
    FEscapeAction := AValue;
end;

procedure TAttributes.SetRequired(const AValue: Boolean);
begin
  if FRequired <> AValue then
  begin
    if AValue then
    begin
      FRequired := True;
      FColorize := True;
    end
    else
      FRequired := False;
  end;
end;

constructor TAttributes.Create(TheParent: TComponent);
begin
  FParent := TheParent;
  FColors := TColors.Create;
  FEnterAsTab := True;
  FEscapeAction := eaBack;
  FColorize := True;
  FRequired := False;
end;


end.

