{ TLCDBMaskEdit }

procedure TLCDBMaskEdit.SetLabelPosition(const Value: TLabelPosition);
var
  P: TPoint;
begin
  if FEditLabel = nil then exit;
  FLabelPosition := Value;
  case Value of
    lpAbove: P := Point(Left, Top - FEditLabel.Height - FLabelSpacing);
    lpBelow: P := Point(Left, Top + Height + FLabelSpacing);
    lpLeft : P := Point(Left - FEditLabel.Width - FLabelSpacing,
                    Top + ((Height - FEditLabel.Height) div 2));
    lpRight: P := Point(Left + Width + FLabelSpacing,
                    Top + ((Height - FEditLabel.Height) div 2));
  end;
  FEditLabel.SetBounds(P.x, P.y, FEditLabel.Width, FEditLabel.Height);
end;

procedure TLCDBMaskEdit.SetLabelSpacing(const Value: Integer);
begin
  FLabelSpacing := Value;
  SetLabelPosition(FLabelPosition);
end;

procedure TLCDBMaskEdit.SetAttributes(const AValue: TAttributes);
begin
  FAttributes.Assign(AValue);
end;

procedure TLCDBMaskEdit.SetMask(const AValue: TMaskType);
var
  rLiterals: String;
begin
  case FSaveLiterals of
    True : rLiterals := '1';
    False: rLiterals := '0';
  end;

  FMaskType := AValue;

  case AValue of
    mtTelefone,
    mtTelFixo,
    mtCelular : EditMask := '(##)####-####;' + rLiterals + ';' + FCharForBlanks;
    mtCPF     : EditMask := '###.###.###-##;' + rLiterals + ';' + FCharForBlanks;
    mtCNPJ    : EditMask := '##.###.###/####-##;' + rLiterals + ';' + FCharForBlanks;
    mtPIS     : EditMask := '###.######-##;' + rLiterals + ';' + FCharForBlanks;
    mtData    :
    begin
      FSaveLiterals := True;
      EditMask := '##/##/####;1;' + FCharForBlanks;
    end;
    mtPlaca   :
    begin
      EditMask := 'AAA-9999;' + rLiterals + ';' + FCharForBlanks;
      SetCharCase(ecUppercase);
    end;
  end;
end;

procedure TLCDBMaskEdit.SetValidate(const AValue: Boolean);
begin
  if FValidate <> AValue then
    FValidate := AValue;

  if FValidate then
    FAttributes.Colorize := True;
end;

procedure TLCDBMaskEdit.SetParent(AParent: TWinControl);
begin
  if FEditLabel = nil then exit;
  FEditLabel.Parent := AParent;
  FEditLabel.Visible := True;
  inherited SetParent(AParent);
end;

procedure TLCDBMaskEdit.Notification(AComponent: TComponent; Operation: TOperation
  );
begin
  if (AComponent = FEditLabel) and (Operation = opRemove) then
    FEditLabel := nil;
  inherited Notification(AComponent, Operation);
end;

procedure TLCDBMaskEdit.SetName(const Value: TComponentName);
begin
  if (csDesigning in ComponentState) and ((FEditlabel.GetTextLen = 0) or
     (CompareText(FEditLabel.Caption, Name) = 0)) then
    FEditLabel.Caption := Value;
  inherited SetName(Value);
  if csDesigning in ComponentState then
    Text := '';
end;

procedure TLCDBMaskEdit.CMVisiblechanged(var Message: TLMessage);
begin
  inherited;
  FEditLabel.Visible := Visible;
end;

procedure TLCDBMaskEdit.CMEnabledchanged(var Message: TLMessage);
begin
  inherited;
  FEditLabel.Enabled := Enabled;
end;

procedure TLCDBMaskEdit.CMBidimodechanged(var Message: TLMessage);
begin
  inherited;
  FEditLabel.BiDiMode := BiDiMode;
end;

procedure TLCDBMaskEdit.DoEnter;
begin
  FColor := Color;
  if FAttributes.Colorize then
  begin
    Color := FAttributes.Colors.FocusColor;
    EditLabel.Font.Style := Font.Style + [fsBold];
  end;

  if not FMarked then
  begin
    FOldValue := Text;
    FMarked := True;
  end;
  inherited DoEnter;
end;

procedure TLCDBMaskEdit.DoExit;
var
  rStr1, rStr2: String;
  rData: TDate;
begin
  rStr1 := StringReplace(Text, '(', '', [rfReplaceAll]);
  rStr1 := StringReplace(rStr1, ')', '', [rfReplaceAll]);
  rStr1 := StringReplace(rStr1, '-', '', [rfReplaceAll]);
  rStr1 := StringReplace(rStr1, '.', '', [rfReplaceAll]);
  rStr1 := StringReplace(rStr1, '/', '', [rfReplaceAll]);

  if FAttributes.Required then
  begin
    case FMaskType of
      mtTelefone:
      begin
        try
          if rStr1 = '' then
          begin
            Color := FAttributes.Colors.WrongColor;
            Exit;
          end;

          rStr2 := Copy(rStr1, 1, 2);
          rStr1 := Copy(rStr1, 3, 8);

          if FValidate then
          begin
            if (StrToInt64(rStr1) > 20000000) and (DDDCheck(StrToInt(rStr2))) then
              Color := FAttributes.Colors.RightColor
            else
              begin
                Color := FAttributes.Colors.WrongColor;
                Exit;
              end;
          end;
        except
          on EConvertError do
          begin
            Color := FAttributes.Colors.WrongColor;
            Exit;
          end;
        end;
      end;
      mtTelFixo:
      begin
        try
          if rStr1 = '' then
          begin
            Color := FAttributes.Colors.WrongColor;
            Exit;
          end;

          rStr2 := Copy(rStr1, 1, 2);
          rStr1 := Copy(rStr1, 3, 8);

          if FValidate then
          begin
            if (StrToInt64(rStr1) > 20000000) and (StrToInt64(rStr1) < 69999999) and
               (DDDCheck(StrToInt(rStr2))) then
              Color := FAttributes.Colors.RightColor
            else
              begin
                Color := FAttributes.Colors.WrongColor;
                Exit;
              end;
          end;
        except
          on EConvertError do
          begin
            Color := FAttributes.Colors.WrongColor;
            Exit;
          end;
        end;
      end;
      mtCelular:
      begin
        try
          if rStr1 = '' then
          begin
            Color := FAttributes.Colors.WrongColor;
            Exit;
          end;

          rStr2 := Copy(rStr1, 1, 2);
          rStr1 := Copy(rStr1, 3, 8);

          if FValidate then
          begin
            if (StrToInt64(rStr1) > 70000000) and (DDDCheck(StrToInt(rStr2))) then
              Color := FAttributes.Colors.RightColor
            else
              begin
                Color := FAttributes.Colors.WrongColor;
                Exit;
              end;
          end;
        except
          on EConvertError do
          begin
            Color := FAttributes.Colors.WrongColor;
            Exit;
          end;
        end;
      end;
      mtCPF:
      begin
        if rStr1 = '' then
        begin
          Color := FAttributes.Colors.WrongColor;
          Exit;
        end;

        if FValidate then
        begin
          if CPFCheck(rStr1) then
            Color := FAttributes.Colors.RightColor
          else
            begin
              Color := FAttributes.Colors.WrongColor;
              Exit;
            end;
        end;
      end;
      mtCNPJ:
      begin
        if rStr1 = '' then
        begin
          Color := FAttributes.Colors.WrongColor;
          Exit;
        end;

        if FValidate then
        begin
          if CNPJCheck(rStr1) then
            Color := FAttributes.Colors.RightColor
          else
            begin
              Color := FAttributes.Colors.WrongColor;
              Exit;
            end;
        end;
      end;
      mtPIS:
      begin
        if rStr1 = '' then
        begin
          Color := FAttributes.Colors.WrongColor;
          Exit;
        end;

        if FValidate then
        begin
          if PISCheck(rStr1) then
            Color := FAttributes.Colors.RightColor
          else
            begin
              Color := FAttributes.Colors.WrongColor;
              Exit;
            end;
        end;
      end;
      mtData:
      begin
        rStr1 := Copy(rStr1, 1, 2) + '/' + Copy(rStr1, 3, 2) + '/' + Copy(rStr1, 5, 4);
        try
          rData := StrToDate(rStr1);
          Color := FAttributes.Colors.RightColor;
        except
          on EConvertError do
          begin
            Color := FAttributes.Colors.WrongColor;
            Exit;
          end;
        end;
      end;
    end;
  end
  else
    Color := FColor;
  if FAttributes.Colorize then
    EditLabel.Font.Style := Font.Style - [fsBold];
  inherited;
end;

procedure TLCDBMaskEdit.KeyPress(var Key: Char);
begin
  case Key of
    #13: if FAttributes.EnterAsTab then PerformTab(True);
    #27: case FAttributes.EscapeAction of
           eaBack     :PerformTab(False);
           eaClear    : Clear;
           eaClearBack: if Text <> '' then Clear else PerformTab(False);
           eaClose    : GetParentForm(TControl(Self)).Close;
         end;
  end;
  inherited KeyPress(Key);
end;

procedure TLCDBMaskEdit.Change;
begin
  if FHilightChanges and FMarked and Focused then
  begin
    if (Text <> FOldValue) and (FOldValue <> '') then
      Font.Style := Font.Style + [fsBold]
    else
      Font.Style := Font.Style - [fsBold];
  end;
  inherited Change;
end;

procedure TLCDBMaskEdit.KeyUp(var Key: Word; Shift: TShiftState);
var
  i: Byte;
begin
  if ssCtrl in Shift then
    Key := Key + 16384;

  if Key = FAlternableShortCut then
  begin
    i := FControlMask;
    while i <= 7 do
    begin
      if (i = 7) and (not (amPIS in FAlternate)) then
        i := 0;

      case i of
        0:
        begin
          if (FMaskType <> mtTelefone) and (amTelefone in FAlternate) then
          begin
            SetMask(mtTelefone);
            Break;
          end;
        end;
        1:
        begin
          if (FMaskType <> mtTelFixo) and (amTelFixo in FAlternate) then
          begin
            SetMask(mtTelFixo);
            Break;
          end;
        end;
        2:
        begin
          if (FMaskType <> mtCelular) and (amCelular in FAlternate) then
          begin
            SetMask(mtCelular);
            Break;
          end;
        end;
        3:
        begin
          if (FMaskType <> mtCPF) and (amCPF in FAlternate) then
          begin
            SetMask(mtCPF);
            Break;
          end;
        end;
        4:
        begin
          if (FMaskType <> mtCNPJ) and (amCNPJ in FAlternate) then
          begin
            SetMask(mtCNPJ);
            Break;
          end;
        end;
        5:
        begin
          if (FMaskType <> mtData) and (amData in FAlternate) then
          begin
            SetMask(mtData);
            Break;
          end;
        end;
        6:
        begin
          if (FMaskType <> mtPlaca) and (amPlaca in FAlternate) then
          begin
            SetMask(mtPlaca);
            FControlMask := 0;
            Break;
          end;
        end;
        7:
        begin
          if (FMaskType <> mtPIS) and (amPIS in FAlternate) then
          begin
            SetMask(mtPIS);
            FControlMask := 0;
            Break;
          end;
        end;
      end;

      inc(i);
      FControlMask := i;
    end;
  end;
  inherited KeyUp(Key, Shift);
end;

constructor TLCDBMaskEdit.Create(AOwner: TComponent);
begin
  FAttributes := TAttributes.Create(Self);
  FMarked := False;
  FOldValue := '';
  FHilightChanges := True;
  FCharForBlanks := #32;
  FSaveLiterals := False;
  FControlMask := 0;
  SetMask(mtCustom);
  SetValidate(True);
  FLabelPosition := lpAbove;
  FColor := clDefault;
  SetupInternalLabel;
  inherited Create(AOwner);
end;

procedure TLCDBMaskEdit.SetBounds(ALeft: Integer; ATop: Integer; AWidth: Integer;
  AHeight: Integer);
begin
  inherited SetBounds(ALeft, ATop, AWidth, AHeight);
  SetLabelPosition(FLabelPosition);
end;

procedure TLCDBMaskEdit.SetupInternalLabel;
begin
  if Assigned(FEditLabel) then exit;
  FEditLabel := TBoundLabel.Create(Self);
  FEditLabel.FreeNotification(Self);
  FEditLabel.FocusControl := Self;
end;


{ TLCMaskEdit }

procedure TLCMaskEdit.SetLabelPosition(const Value: TLabelPosition);
var
  P: TPoint;
begin
  if FEditLabel = nil then exit;
  FLabelPosition := Value;
  case Value of
    lpAbove: P := Point(Left, Top - FEditLabel.Height - FLabelSpacing);
    lpBelow: P := Point(Left, Top + Height + FLabelSpacing);
    lpLeft : P := Point(Left - FEditLabel.Width - FLabelSpacing,
                    Top + ((Height - FEditLabel.Height) div 2));
    lpRight: P := Point(Left + Width + FLabelSpacing,
                    Top + ((Height - FEditLabel.Height) div 2));
  end;
  FEditLabel.SetBounds(P.x, P.y, FEditLabel.Width, FEditLabel.Height);
end;

procedure TLCMaskEdit.SetLabelSpacing(const Value: Integer);
begin
  FLabelSpacing := Value;
  SetLabelPosition(FLabelPosition);
end;

procedure TLCMaskEdit.SetAttributes(const AValue: TAttributes);
begin
  FAttributes.Assign(AValue);
end;

procedure TLCMaskEdit.SetMask(const AValue: TMaskType);
var
  rLiterals: String;
begin
  case FSaveLiterals of
    True : rLiterals := '1';
    False: rLiterals := '0';
  end;

  FMaskType := AValue;

  case AValue of
    mtTelefone,
    mtTelFixo,
    mtCelular : EditMask := '(##)####-####;' + rLiterals + ';' + FCharForBlanks;
    mtCPF     : EditMask := '###.###.###-##;' + rLiterals + ';' + FCharForBlanks;
    mtCNPJ    : EditMask := '##.###.###/####-##;' + rLiterals + ';' + FCharForBlanks;
    mtPIS     : EditMask := '###.######-##;' + rLiterals + ';' + FCharForBlanks;
    mtData    :
    begin
      FSaveLiterals := True;
      EditMask := '##/##/####;1;' + FCharForBlanks;
    end;
    mtPlaca   :
    begin
      EditMask := 'AAA-9999;' + rLiterals + ';' + FCharForBlanks;
      SetCharCase(ecUppercase);
    end;
  end;
end;

procedure TLCMaskEdit.SetValidate(const AValue: Boolean);
begin
  if FValidate <> AValue then
    FValidate := AValue;

  if FValidate then
    FAttributes.Colorize := True;
end;

procedure TLCMaskEdit.SetParent(AParent: TWinControl);
begin
  if FEditLabel = nil then exit;
  FEditLabel.Parent := AParent;
  FEditLabel.Visible := True;
  inherited SetParent(AParent);
end;

procedure TLCMaskEdit.Notification(AComponent: TComponent; Operation: TOperation
  );
begin
  if (AComponent = FEditLabel) and (Operation = opRemove) then
    FEditLabel := nil;
  inherited Notification(AComponent, Operation);
end;

procedure TLCMaskEdit.SetName(const Value: TComponentName);
begin
  if (csDesigning in ComponentState) and ((FEditlabel.GetTextLen = 0) or
     (CompareText(FEditLabel.Caption, Name) = 0)) then
    FEditLabel.Caption := Value;
  inherited SetName(Value);
  if csDesigning in ComponentState then
    Text := '';
end;

procedure TLCMaskEdit.CMVisiblechanged(var Message: TLMessage);
begin
  inherited;
  FEditLabel.Visible := Visible;
end;

procedure TLCMaskEdit.CMEnabledchanged(var Message: TLMessage);
begin
  inherited;
  FEditLabel.Enabled := Enabled;
end;

procedure TLCMaskEdit.CMBidimodechanged(var Message: TLMessage);
begin
  inherited;
  FEditLabel.BiDiMode := BiDiMode;
end;

procedure TLCMaskEdit.DoEnter;
begin
  FColor := Color;
  if FAttributes.Colorize then
  begin
    Color := FAttributes.Colors.FocusColor;
    EditLabel.Font.Style := Font.Style + [fsBold];
  end;

  if not FMarked then
  begin
    FOldValue := Text;
    FMarked := True;
  end;
  inherited DoEnter;
end;

procedure TLCMaskEdit.DoExit;
var
  rStr1, rStr2: String;
  rData: TDate;
begin
  rStr1 := StringReplace(Text, '(', '', [rfReplaceAll]);
  rStr1 := StringReplace(rStr1, ')', '', [rfReplaceAll]);
  rStr1 := StringReplace(rStr1, '-', '', [rfReplaceAll]);
  rStr1 := StringReplace(rStr1, '.', '', [rfReplaceAll]);
  rStr1 := StringReplace(rStr1, '/', '', [rfReplaceAll]);

  if FAttributes.Required then
  begin
    case FMaskType of
      mtTelefone:
      begin
        try
          if rStr1 = '' then
          begin
            Color := FAttributes.Colors.WrongColor;
            Exit;
          end;

          rStr2 := Copy(rStr1, 1, 2);
          rStr1 := Copy(rStr1, 3, 8);

          if FValidate then
          begin
            if (StrToInt64(rStr1) > 20000000) and (DDDCheck(StrToInt(rStr2))) then
              Color := FAttributes.Colors.RightColor
            else
              begin
                Color := FAttributes.Colors.WrongColor;
                Exit;
              end;
          end;
        except
          on EConvertError do
          begin
            Color := FAttributes.Colors.WrongColor;
            Exit;
          end;
        end;
      end;
      mtTelFixo:
      begin
        try
          if rStr1 = '' then
          begin
            Color := FAttributes.Colors.WrongColor;
            Exit;
          end;

          rStr2 := Copy(rStr1, 1, 2);
          rStr1 := Copy(rStr1, 3, 8);

          if FValidate then
          begin
            if (StrToInt64(rStr1) > 20000000) and (StrToInt64(rStr1) < 69999999) and
               (DDDCheck(StrToInt(rStr2))) then
              Color := FAttributes.Colors.RightColor
            else
              begin
                Color := FAttributes.Colors.WrongColor;
                Exit;
              end;
          end;
        except
          on EConvertError do
          begin
            Color := FAttributes.Colors.WrongColor;
            Exit;
          end;
        end;
      end;
      mtCelular:
      begin
        try
          if rStr1 = '' then
          begin
            Color := FAttributes.Colors.WrongColor;
            Exit;
          end;

          rStr2 := Copy(rStr1, 1, 2);
          rStr1 := Copy(rStr1, 3, 8);

          if FValidate then
          begin
            if (StrToInt64(rStr1) > 70000000) and (DDDCheck(StrToInt(rStr2))) then
              Color := FAttributes.Colors.RightColor
            else
              begin
                Color := FAttributes.Colors.WrongColor;
                Exit;
              end;
          end;
        except
          on EConvertError do
          begin
            Color := FAttributes.Colors.WrongColor;
            Exit;
          end;
        end;
      end;
      mtCPF:
      begin
        if rStr1 = '' then
        begin
          Color := FAttributes.Colors.WrongColor;
          Exit;
        end;

        if FValidate then
        begin
          if CPFCheck(rStr1) then
            Color := FAttributes.Colors.RightColor
          else
            begin
              Color := FAttributes.Colors.WrongColor;
              Exit;
            end;
        end;
      end;
      mtCNPJ:
      begin
        if rStr1 = '' then
        begin
          Color := FAttributes.Colors.WrongColor;
          Exit;
        end;

        if FValidate then
        begin
          if CNPJCheck(rStr1) then
            Color := FAttributes.Colors.RightColor
          else
            begin
              Color := FAttributes.Colors.WrongColor;
              Exit;
            end;
        end;
      end;
      mtPIS:
      begin
        if rStr1 = '' then
        begin
          Color := FAttributes.Colors.WrongColor;
          Exit;
        end;

        if FValidate then
        begin
          if PISCheck(rStr1) then
            Color := FAttributes.Colors.RightColor
          else
            begin
              Color := FAttributes.Colors.WrongColor;
              Exit;
            end;
        end;
      end;
      mtData:
      begin
        rStr1 := Copy(rStr1, 1, 2) + '/' + Copy(rStr1, 3, 2) + '/' + Copy(rStr1, 5, 4);
        try
          rData := StrToDate(rStr1);
          Color := FAttributes.Colors.RightColor;
        except
          on EConvertError do
          begin
            Color := FAttributes.Colors.WrongColor;
            Exit;
          end;
        end;
      end;
    end;
  end
  else
    Color := FColor;
  if FAttributes.Colorize then
    EditLabel.Font.Style := Font.Style - [fsBold];
  inherited;
end;

procedure TLCMaskEdit.KeyPress(var Key: Char);
begin
  case Key of
    #13: if FAttributes.EnterAsTab then PerformTab(True);
    #27: case FAttributes.EscapeAction of
           eaBack     :PerformTab(False);
           eaClear    : Clear;
           eaClearBack: if Text <> '' then Clear else PerformTab(False);
           eaClose    : GetParentForm(TControl(Self)).Close;
         end;
  end;
  inherited KeyPress(Key);
end;

procedure TLCMaskEdit.Change;
begin
  if FHilightChanges and FMarked and Focused then
  begin
    if (Text <> FOldValue) and (FOldValue <> '') then
      Font.Style := Font.Style + [fsBold]
    else
      Font.Style := Font.Style - [fsBold];
  end;
  inherited Change;
end;

procedure TLCMaskEdit.KeyUp(var Key: Word; Shift: TShiftState);
var
  i: Byte;
begin
  if ssCtrl in Shift then
    Key := Key + 16384;

  if Key = FAlternableShortCut then
  begin
    i := FControlMask;
    while i <= 7 do
    begin
      if (i = 7) and (not (amPIS in FAlternate)) then
        i := 0;

      case i of
        0:
        begin
          if (FMaskType <> mtTelefone) and (amTelefone in FAlternate) then
          begin
            SetMask(mtTelefone);
            Break;
          end;
        end;
        1:
        begin
          if (FMaskType <> mtTelFixo) and (amTelFixo in FAlternate) then
          begin
            SetMask(mtTelFixo);
            Break;
          end;
        end;
        2:
        begin
          if (FMaskType <> mtCelular) and (amCelular in FAlternate) then
          begin
            SetMask(mtCelular);
            Break;
          end;
        end;
        3:
        begin
          if (FMaskType <> mtCPF) and (amCPF in FAlternate) then
          begin
            SetMask(mtCPF);
            Break;
          end;
        end;
        4:
        begin
          if (FMaskType <> mtCNPJ) and (amCNPJ in FAlternate) then
          begin
            SetMask(mtCNPJ);
            Break;
          end;
        end;
        5:
        begin
          if (FMaskType <> mtData) and (amData in FAlternate) then
          begin
            SetMask(mtData);
            Break;
          end;
        end;
        6:
        begin
          if (FMaskType <> mtPlaca) and (amPlaca in FAlternate) then
          begin
            SetMask(mtPlaca);
            FControlMask := 0;
            Break;
          end;
        end;
        7:
        begin
          if (FMaskType <> mtPIS) and (amPIS in FAlternate) then
          begin
            SetMask(mtPIS);
            FControlMask := 0;
            Break;
          end;
        end;
      end;

      inc(i);
      FControlMask := i;
    end;
  end;
  inherited KeyUp(Key, Shift);
end;

constructor TLCMaskEdit.Create(AOwner: TComponent);
begin
  FAttributes := TAttributes.Create(Self);
  FMarked := False;
  FOldValue := '';
  FHilightChanges := True;
  FCharForBlanks := #32;
  FSaveLiterals := False;
  FControlMask := 0;
  SetMask(mtCustom);
  SetValidate(True);
  FLabelPosition := lpAbove;
  SetupInternalLabel;
  inherited Create(AOwner);
end;

procedure TLCMaskEdit.SetBounds(ALeft: Integer; ATop: Integer; AWidth: Integer;
  AHeight: Integer);
begin
  inherited SetBounds(ALeft, ATop, AWidth, AHeight);
  SetLabelPosition(FLabelPosition);
end;

procedure TLCMaskEdit.SetupInternalLabel;
begin
  if Assigned(FEditLabel) then exit;
  FEditLabel := TBoundLabel.Create(Self);
  FEditLabel.FreeNotification(Self);
  FEditLabel.FocusControl := Self;
end;

