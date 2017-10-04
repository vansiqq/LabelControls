{ TLCNumericEdit }

procedure TLCNumericEdit.SetAttributes(const AValue: TAttributes);
begin
  FAttributes.Assign(AValue);
end;

procedure TLCNumericEdit.SetFloatValue(const AValue: Extended);
begin
  Text := FloatToStr(AValue);
  WhenExit;
end;

procedure TLCNumericEdit.SetNegativeColor(const AValue: TColor);
begin
  if FNegativeColor <> AValue then
    FNegativeColor := AValue;
end;

procedure TLCNumericEdit.WhenExit;
var
  eValue: Extended;
  sFormat: String;
  bLenght: Byte;
begin
  if Text = '' then
    Text := '0';

  bLenght := Length(Text);

  if FDecimals > 0 then
  begin
    if AnsiPos(',', Text) = 0 then
      Text := Text + ',';

    while Length(Text) < bLenght + FDecimals do
      Text := Text + '0';

    sFormat := '######0.';

    while Length(sFormat) < 8 + FDecimals do
      sFormat := sFormat + '0';
  end;

  eValue := StrToFloat(Text);

  case FEditType of
    etCurrency: Text := FCurrencySymbol + ' ' + FormatFloat(sFormat, eValue);
    etPercent : Text := FormatFloat(sFormat, eValue) + '%';
    etFloat   : Text := FormatFloat(sFormat, eValue);
    etInteger : Text := FormatFloat('#########0', eValue);
  end;

  if GetFloatValue < 0 then
    Font.Color := FNegativeColor
  else
    Font.Color := FFontColor;
end;

procedure TLCNumericEdit.DoEnter;
begin
  case FEditType of
    etCurrency:
    begin
      Text := Trim(StringReplace(Text, FCurrencySymbol, '', [rfReplaceAll]));
      SelStart := 0;
      SelLength := Length(Text);
    end;
    etPercent :
    begin
      Text := Trim(StringReplace(Text, '%', '', [rfReplaceAll]));
      SelStart := 0;
      SelLength := Length(Text);
    end;
  end;

  FOldValue := Text;

  inherited DoEnter;
end;

procedure TLCNumericEdit.DoExit;
begin
  WhenExit;
  inherited DoExit;
end;

procedure TLCNumericEdit.KeyPress(var Key: Char);
begin
  case FEditType of
    etInteger : if (not (Key in ['0'..'9', #8, #13, #27, '-'])) then
                  Key := #0;
    etFloat,
    etCurrency,
    etPercent :
    begin
      if (not (Key in ['0'..'9', #8, #13, #27, ',', '-'])) then
        Key := #0;

      if (AnsiPos(',', Text) > 0) and (Key = ',') then
        Key := #0;
    end;
  end;

  if Key = '-' then
  begin
    if SelLength = Length(Text) then
    begin
      inherited KeyPress(Key);
      Exit;
    end;

    if AnsiPos('-', Text) > 0 then
      Key := #0
    else
      if Length(Text) > 0 then
        Key := #0;
  end;

  inherited KeyPress(Key);
end;

procedure TLCNumericEdit.Change;
var
  extValue, extOldValue: Extended;
  strTmp: String;
begin
  extValue := 0;
  extOldValue := 0;

  strTmp := StringReplace(Text, FCurrencySymbol, '', [rfReplaceAll]);
  strTmp := StringReplace(strTmp, '%', '', [rfReplaceAll]);
  strTmp := Trim(strTmp);

  if strTmp = '' then
    strTmp := '0';

  try
    try
      if Text <> '' then
      begin
        extValue := StrToFloat(strTmp);

        if FOldValue = '' then
          extOldValue := 0
        else
          extOldValue := StrToFloat(FOldValue);
      end;
    except
    end;
  finally
    if FHilightChanges and Focused then
    begin
      if (extValue <> extOldValue) and (extOldValue <> 0) and
         ((AnsiPos(FCurrencySymbol, Text) > 0) or (AnsiPos('%', Text) > 0)) then
        Font.Style := Font.Style + [fsBold]
      else
        Font.Style := Font.Style - [fsBold];
    end;

    inherited Change;
  end;
end;

constructor TLCNumericEdit.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  FFontColor := Font.Color;
  FDecimalSeparator := ',';
  SetCurrencySymbol('R$');
  SetDecimals(0);
  SetEditType(etInteger);
  Alignment := taRightJustify;
  SetNegativeColor(clRed);
  FColor := clDefault;
  SetFloatValue(0);
end;

function TLCNumericEdit.GetEditType: TEditType;
begin
  Result := FEditType;
end;

procedure TLCNumericEdit.SetEditType(const AValue: TEditType);
begin
  if FEditType <> AValue then
  begin
    FEditType := AValue;
    case FEditType of
      etInteger : SetDecimals(0);
      etFloat,
      etCurrency,
      etPercent : SetDecimals(2);
    end;

    case FEditType of
      etInteger: Text := '0';
    end;
  end;
end;

function TLCNumericEdit.GetCurrencySymbol: String;
begin
  Result := FCurrencySymbol;
end;

function TLCNumericEdit.GetDecimals: Byte;
begin
  Result := FDecimals;
end;

function TLCNumericEdit.GetDecimalSeparator: String;
begin
  Result := FDecimalSeparator;
end;

function TLCNumericEdit.GetFloatValue: Extended;
var
  sValue: String;
begin
  try
    case FEditType of
      etInteger,
      etFloat   : sValue := Text;
      etCurrency: sValue := Trim(StringReplace(Text, FCurrencySymbol, '', [rfReplaceAll]));
      etPercent : sValue := Trim(StringReplace(Text, '%', '', [rfReplaceAll]));
    end;

    if sValue = '' then
      sValue := '0';

    Result := StrToFloat(sValue);

    if Result < 0 then
      Font.Color := FNegativeColor
    else
      Font.Color := FFontColor;
  except
    Result := 0;
  end;
end;

function TLCNumericEdit.GetIntValue: Integer;
var
  sValue: String;
  eValue: Extended;
begin
  try
    case FEditType of
      etInteger,
      etFloat   : sValue := Text;
      etCurrency: sValue := Trim(StringReplace(Text, FCurrencySymbol, '', [rfReplaceAll]));
      etPercent : sValue := Trim(StringReplace(Text, '%', '', [rfReplaceAll]));
    end;

    if sValue = '' then
      sValue := '0';

    eValue := Int(StrToFloat(sValue));
    Result := StrToInt(FormatFloat('#########0', eValue));
  except
    Result := 0;
  end;
end;

function TLCNumericEdit.GetNegativeColor: TColor;
begin
  Result := FNegativeColor;
end;

procedure TLCNumericEdit.SetCurrencySymbol(const AValue: String);
begin
  if FCurrencySymbol <> AValue then
  begin
    if Length(AValue) > 3 then
      Exit;

    if AnsiPos('$', AValue) = 0 then
      FCurrencySymbol := AValue + '$'
    else
      FCurrencySymbol := AValue;
  end;

  if FEditType = etCurrency then
  begin
    case FDecimals of
      2: Text := FCurrencySymbol + ' 0,00';
      3: Text := FCurrencySymbol + ' 0,000';
    end;
  end;
end;

procedure TLCNumericEdit.SetDecimals(const AValue: Byte);
begin
  if FDecimals <> AValue then
  begin
    if FEditType = etInteger then
    begin
      FDecimals := 0;
      Text := '0';
      Exit;
    end;

    if (AValue < 2) and (FEditType = etCurrency) then
      FDecimals := 2
    else if (AValue > 3) and (FEditType = etCurrency) then
      FDecimals := 3
    else
      FDecimals := AValue;
  end;

  case FEditType of
    etCurrency: case FDecimals of
                  2: Text := FCurrencySymbol + ' 0,00';
                  3: Text := FCurrencySymbol + ' 0,000';
                end;
    etFloat   :
    begin
      Text := '0';

      if FDecimals > 0 then
        Text := Text + ',';

      while Length(Text) < 2 + FDecimals do
        Text := Text + '0';
    end;
    etPercent :
    begin
      Text := '0';

      if FDecimals > 0 then
        Text := Text + ',';

      while Length(Text) < 2 + FDecimals do
        Text := Text + '0';

      Text := Text + '%';
    end;
  end;
end;

{ TLCDBNumericEdit }

procedure TLCDBNumericEdit.SetAttributes(const AValue: TAttributes);
begin
  FAttributes.Assign(AValue);
end;

procedure TLCDBNumericEdit.SetFloatValue(const AValue: Extended);
begin
  Text := FloatToStr(AValue);
  WhenExit;
end;

procedure TLCDBNumericEdit.SetNegativeColor(const AValue: TColor);
begin
  if FNegativeColor <> AValue then
    FNegativeColor := AValue;
end;

procedure TLCDBNumericEdit.WhenExit;
var
  eValue: Extended;
  sFormat: String;
  bLenght: Byte;
begin
  if Text = '' then
    Text := '0';

  bLenght := Length(Text);

  if FDecimals > 0 then
  begin
    if AnsiPos(',', Text) = 0 then
      Text := Text + ',';

    while Length(Text) < bLenght + FDecimals do
      Text := Text + '0';

    sFormat := '######0.';

    while Length(sFormat) < 8 + FDecimals do
      sFormat := sFormat + '0';
  end;

  eValue := StrToFloat(Text);

  case FEditType of
    etCurrency: Text := FCurrencySymbol + ' ' + FormatFloat(sFormat, eValue);
    etPercent : Text := FormatFloat(sFormat, eValue) + '%';
    etFloat   : Text := FormatFloat(sFormat, eValue);
    etInteger : Text := FormatFloat('#########0', eValue);
  end;

  if GetFloatValue < 0 then
    Font.Color := FNegativeColor
  else
    Font.Color := FFontColor;
end;

procedure TLCDBNumericEdit.DoEnter;
begin
  case FEditType of
    etCurrency:
    begin
      Text := Trim(StringReplace(Text, FCurrencySymbol, '', [rfReplaceAll]));
      SelStart := 0;
      SelLength := Length(Text);
    end;
    etPercent :
    begin
      Text := Trim(StringReplace(Text, '%', '', [rfReplaceAll]));
      SelStart := 0;
      SelLength := Length(Text);
    end;
  end;

  FOldValue := Text;

  inherited DoEnter;
end;

procedure TLCDBNumericEdit.DoExit;
begin
  WhenExit;
  inherited DoExit;
end;

procedure TLCDBNumericEdit.KeyPress(var Key: Char);
begin
  case FEditType of
    etInteger : if (not (Key in ['0'..'9', #8, #13, #27, '-'])) then
                  Key := #0;
    etFloat,
    etCurrency,
    etPercent :
    begin
      if (not (Key in ['0'..'9', #8, #13, #27, ',', '-'])) then
        Key := #0;

      if (AnsiPos(',', Text) > 0) and (Key = ',') then
        Key := #0;
    end;
  end;

  if Key = '-' then
  begin
    if SelLength = Length(Text) then
    begin
      inherited KeyPress(Key);
      Exit;
    end;

    if AnsiPos('-', Text) > 0 then
      Key := #0
    else
      if Length(Text) > 0 then
        Key := #0;
  end;

  inherited KeyPress(Key);
end;

procedure TLCDBNumericEdit.Change;
var
  extValue, extOldValue: Extended;
  strTmp: String;
begin
  extValue := 0;
  extOldValue := 0;

  strTmp := StringReplace(Text, FCurrencySymbol, '', [rfReplaceAll]);
  strTmp := StringReplace(strTmp, '%', '', [rfReplaceAll]);
  strTmp := Trim(strTmp);

  if strTmp = '' then
    strTmp := '0';

  try
    try
      if Text <> '' then
      begin
        extValue := StrToFloat(strTmp);

        if FOldValue = '' then
          extOldValue := 0
        else
          extOldValue := StrToFloat(FOldValue);
      end;
    except
    end;
  finally
    if FHilightChanges and Focused then
    begin
      if (extValue <> extOldValue) and (extOldValue <> 0) and
         ((AnsiPos(FCurrencySymbol, Text) > 0) or (AnsiPos('%', Text) > 0)) then
        Font.Style := Font.Style + [fsBold]
      else
        Font.Style := Font.Style - [fsBold];
    end;

    inherited Change;
  end;
end;

constructor TLCDBNumericEdit.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  FFontColor := Font.Color;
  FDecimalSeparator := ',';
  SetCurrencySymbol('R$');
  SetDecimals(0);
  SetEditType(etInteger);
  Alignment := taRightJustify;
  SetNegativeColor(clRed);
  SetFloatValue(0);
end;

function TLCDBNumericEdit.GetEditType: TEditType;
begin
  Result := FEditType;
end;

procedure TLCDBNumericEdit.SetEditType(const AValue: TEditType);
begin
  if FEditType <> AValue then
  begin
    FEditType := AValue;
    case FEditType of
      etInteger : SetDecimals(0);
      etFloat,
      etCurrency,
      etPercent : SetDecimals(2);
    end;

    case FEditType of
      etInteger: Text := '0';
    end;
  end;
end;

function TLCDBNumericEdit.GetCurrencySymbol: String;
begin
  Result := FCurrencySymbol;
end;

function TLCDBNumericEdit.GetDecimals: Byte;
begin
  Result := FDecimals;
end;

function TLCDBNumericEdit.GetDecimalSeparator: String;
begin
  Result := FDecimalSeparator;
end;

function TLCDBNumericEdit.GetFloatValue: Extended;
var
  sValue: String;
begin
  try
    case FEditType of
      etInteger,
      etFloat   : sValue := Text;
      etCurrency: sValue := Trim(StringReplace(Text, FCurrencySymbol, '', [rfReplaceAll]));
      etPercent : sValue := Trim(StringReplace(Text, '%', '', [rfReplaceAll]));
    end;

    if sValue = '' then
      sValue := '0';

    Result := StrToFloat(sValue);

    if Result < 0 then
      Font.Color := FNegativeColor
    else
      Font.Color := FFontColor;
  except
    Result := 0;
  end;
end;

function TLCDBNumericEdit.GetIntValue: Integer;
var
  sValue: String;
  eValue: Extended;
begin
  try
    case FEditType of
      etInteger,
      etFloat   : sValue := Text;
      etCurrency: sValue := Trim(StringReplace(Text, FCurrencySymbol, '', [rfReplaceAll]));
      etPercent : sValue := Trim(StringReplace(Text, '%', '', [rfReplaceAll]));
    end;

    if sValue = '' then
      sValue := '0';

    eValue := Int(StrToFloat(sValue));
    Result := StrToInt(FormatFloat('#########0', eValue));
  except
    Result := 0;
  end;
end;

function TLCDBNumericEdit.GetNegativeColor: TColor;
begin
  Result := FNegativeColor;
end;

procedure TLCDBNumericEdit.SetCurrencySymbol(const AValue: String);
begin
  if FCurrencySymbol <> AValue then
  begin
    if Length(AValue) > 3 then
      Exit;

    if AnsiPos('$', AValue) = 0 then
      FCurrencySymbol := AValue + '$'
    else
      FCurrencySymbol := AValue;
  end;

  if FEditType = etCurrency then
  begin
    case FDecimals of
      2: Text := FCurrencySymbol + ' 0,00';
      3: Text := FCurrencySymbol + ' 0,000';
    end;
  end;
end;

procedure TLCDBNumericEdit.SetDecimals(const AValue: Byte);
begin
  if FDecimals <> AValue then
  begin
    if FEditType = etInteger then
    begin
      FDecimals := 0;
      Text := '0';
      Exit;
    end;

    if (AValue < 2) and (FEditType = etCurrency) then
      FDecimals := 2
    else if (AValue > 3) and (FEditType = etCurrency) then
      FDecimals := 3
    else
      FDecimals := AValue;
  end;

  case FEditType of
    etCurrency: case FDecimals of
                  2: Text := FCurrencySymbol + ' 0,00';
                  3: Text := FCurrencySymbol + ' 0,000';
                end;
    etFloat   :
    begin
      Text := '0';

      if FDecimals > 0 then
        Text := Text + ',';

      while Length(Text) < 2 + FDecimals do
        Text := Text + '0';
    end;
    etPercent :
    begin
      Text := '0';

      if FDecimals > 0 then
        Text := Text + ',';

      while Length(Text) < 2 + FDecimals do
        Text := Text + '0';

      Text := Text + '%';
    end;
  end;
end;


