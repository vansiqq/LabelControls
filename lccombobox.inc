{ TLCDBCombobox }

procedure TLCDBCombobox.SetLabelSpacing(const Value: Integer);
begin
  FLabelSpacing := Value;
  SetLabelPosition(FLabelPosition);
end;

procedure TLCDBCombobox.SetAttributes(const AValue: TAttributes);
begin
  FAttributes.Assign(AValue);
end;

procedure TLCDBCombobox.DoEnter;
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

procedure TLCDBCombobox.DoExit;
begin
  if FAttributes.Required then
  begin
    if Text = '' then
      Color := FAttributes.Colors.WrongColor
    else
      Color := FAttributes.Colors.RightColor;
  end
  else
    Color := FColor;

  if FAttributes.Colorize then
    EditLabel.Font.Style := Font.Style - [fsBold];

  inherited DoExit;
end;

procedure TLCDBCombobox.SetLabelPosition(const Value: TLabelPosition);
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

procedure TLCDBCombobox.KeyPress(var Key: Char);
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

procedure TLCDBCombobox.Change;
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

procedure TLCDBCombobox.CMBidimodechanged(var Message: TLMessage);
begin
  inherited;
  FEditLabel.BiDiMode := BiDiMode;
end;

procedure TLCDBCombobox.CMEnabledchanged(var Message: TLMessage);
begin
  inherited;
  FEditLabel.Enabled := Enabled;
end;

procedure TLCDBCombobox.CMVisiblechanged(var Message: TLMessage);
begin
  inherited;
  FEditLabel.Visible := Visible;
end;

procedure TLCDBCombobox.Notification(AComponent: TComponent;
  Operation: TOperation);
begin
  inherited Notification(AComponent, Operation);
  if (AComponent = FEditLabel) and (Operation = opRemove) then
    FEditLabel := nil;
end;

procedure TLCDBCombobox.SetBounds(ALeft: Integer; ATop: Integer; AWidth: Integer;
  AHeight: Integer);
begin
  inherited SetBounds(ALeft, ATop, AWidth, AHeight);
  SetLabelPosition(FLabelPosition);
end;

procedure TLCDBCombobox.SetName(const Value: TComponentName);
begin
  if (csDesigning in ComponentState) and ((FEditlabel.GetTextLen = 0) or
     (CompareText(FEditLabel.Caption, Name) = 0)) then
    FEditLabel.Caption := Value;
  inherited SetName(Value);
  if csDesigning in ComponentState then
    Text := '';
end;

procedure TLCDBCombobox.SetParent(AParent: TWinControl);
begin
  inherited SetParent(AParent);
  if FEditLabel = nil then exit;
  FEditLabel.Parent := AParent;
  FEditLabel.Visible := True;
end;

procedure TLCDBCombobox.SetupInternalLabel;
begin
  if Assigned(FEditLabel) then exit;
  FEditLabel := TBoundLabel.Create(Self);
  FEditLabel.FreeNotification(Self);
  FEditLabel.FocusControl := Self;
end;

constructor TLCDBCombobox.Create(AOwner: TComponent);
begin
  FAttributes := TAttributes.Create(Self);
  FMarked := False;
  FOldValue := '';
  FHilightChanges := True;
  FLabelPosition := lpAbove;
  FColor := clDefault;
  SetupInternalLabel;
  inherited Create(AOwner);
end;

{ TLCCombobox }

procedure TLCCombobox.SetLabelSpacing(const Value: Integer);
begin
  FLabelSpacing := Value;
  SetLabelPosition(FLabelPosition);
end;

procedure TLCCombobox.SetAttributes(const AValue: TAttributes);
begin
  FAttributes.Assign(AValue);
end;

procedure TLCCombobox.DoEnter;
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

procedure TLCCombobox.DoExit;
begin
  if FAttributes.Required then
  begin
    if Text = '' then
      Color := FAttributes.Colors.WrongColor
    else
      Color := FAttributes.Colors.RightColor;
  end
  else
    Color := FColor;

  if FAttributes.Colorize then
    EditLabel.Font.Style := Font.Style - [fsBold];

  inherited DoExit;
end;

procedure TLCCombobox.SetLabelPosition(const Value: TLabelPosition);
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

procedure TLCCombobox.KeyPress(var Key: Char);
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

procedure TLCCombobox.Change;
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

procedure TLCCombobox.CMBidimodechanged(var Message: TLMessage);
begin
  inherited;
  FEditLabel.BiDiMode := BiDiMode;
end;

procedure TLCCombobox.CMEnabledchanged(var Message: TLMessage);
begin
  inherited;
  FEditLabel.Enabled := Enabled;
end;

procedure TLCCombobox.CMVisiblechanged(var Message: TLMessage);
begin
  inherited;
  FEditLabel.Visible := Visible;
end;

procedure TLCCombobox.Notification(AComponent: TComponent;
  Operation: TOperation);
begin
  inherited Notification(AComponent, Operation);
  if (AComponent = FEditLabel) and (Operation = opRemove) then
    FEditLabel := nil;
end;

procedure TLCCombobox.SetBounds(ALeft: Integer; ATop: Integer; AWidth: Integer;
  AHeight: Integer);
begin
  inherited SetBounds(ALeft, ATop, AWidth, AHeight);
  SetLabelPosition(FLabelPosition);
end;

procedure TLCCombobox.SetName(const Value: TComponentName);
begin
  if (csDesigning in ComponentState) and ((FEditlabel.GetTextLen = 0) or
     (CompareText(FEditLabel.Caption, Name) = 0)) then
    FEditLabel.Caption := Value;
  inherited SetName(Value);
  if csDesigning in ComponentState then
    Text := '';
end;

procedure TLCCombobox.SetParent(AParent: TWinControl);
begin
  inherited SetParent(AParent);
  if FEditLabel = nil then exit;
  FEditLabel.Parent := AParent;
  FEditLabel.Visible := True;
end;

procedure TLCCombobox.SetupInternalLabel;
begin
  if Assigned(FEditLabel) then exit;
  FEditLabel := TBoundLabel.Create(Self);
  FEditLabel.FreeNotification(Self);
  FEditLabel.FocusControl := Self;
end;

constructor TLCCombobox.Create(AOwner: TComponent);
begin
  FAttributes := TAttributes.Create(Self);
  FMarked := False;
  FOldValue := '';
  FHilightChanges := True;
  FLabelPosition := lpAbove;
  FColor := clDefault;
  SetupInternalLabel;
  inherited Create(AOwner);
end;

{ TLCDBLookupCombo }

procedure TLCDBLookupCombo.SetLabelSpacing(const Value: Integer);
begin
  FLabelSpacing := Value;
  SetLabelPosition(FLabelPosition);
end;

procedure TLCDBLookupCombo.SetAttributes(const AValue: TAttributes);
begin
  FAttributes.Assign(AValue);
end;

procedure TLCDBLookupCombo.DoEnter;
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

procedure TLCDBLookupCombo.DoExit;
begin
  if FAttributes.Required then
  begin
    if Text = '' then
      Color := FAttributes.Colors.WrongColor
    else
      Color := FAttributes.Colors.RightColor;
  end
  else
    Color := FColor;

  if FAttributes.Colorize then
    EditLabel.Font.Style := Font.Style - [fsBold];

  inherited DoExit;
end;

procedure TLCDBLookupCombo.SetLabelPosition(const Value: TLabelPosition);
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

procedure TLCDBLookupCombo.KeyPress(var Key: Char);
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

procedure TLCDBLookupCombo.Change;
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

procedure TLCDBLookupCombo.CMBidimodechanged(var Message: TLMessage);
begin
  inherited;
  FEditLabel.BiDiMode := BiDiMode;
end;

procedure TLCDBLookupCombo.CMEnabledchanged(var Message: TLMessage);
begin
  inherited;
  FEditLabel.Enabled := Enabled;
end;

procedure TLCDBLookupCombo.CMVisiblechanged(var Message: TLMessage);
begin
  inherited;
  FEditLabel.Visible := Visible;
end;

procedure TLCDBLookupCombo.Notification(AComponent: TComponent;
  Operation: TOperation);
begin
  inherited Notification(AComponent, Operation);
  if (AComponent = FEditLabel) and (Operation = opRemove) then
    FEditLabel := nil;
end;

procedure TLCDBLookupCombo.SetBounds(ALeft: Integer; ATop: Integer; AWidth: Integer;
  AHeight: Integer);
begin
  inherited SetBounds(ALeft, ATop, AWidth, AHeight);
  SetLabelPosition(FLabelPosition);
end;

procedure TLCDBLookupCombo.SetName(const Value: TComponentName);
begin
  if (csDesigning in ComponentState) and ((FEditlabel.GetTextLen = 0) or
     (CompareText(FEditLabel.Caption, Name) = 0)) then
    FEditLabel.Caption := Value;
  inherited SetName(Value);
  if csDesigning in ComponentState then
    Text := '';
end;

procedure TLCDBLookupCombo.SetParent(AParent: TWinControl);
begin
  inherited SetParent(AParent);
  if FEditLabel = nil then exit;
  FEditLabel.Parent := AParent;
  FEditLabel.Visible := True;
end;

procedure TLCDBLookupCombo.SetupInternalLabel;
begin
  if Assigned(FEditLabel) then exit;
  FEditLabel := TBoundLabel.Create(Self);
  FEditLabel.FreeNotification(Self);
  FEditLabel.FocusControl := Self;
end;

constructor TLCDBLookupCombo.Create(AOwner: TComponent);
begin
  FAttributes := TAttributes.Create(Self);
  FMarked := False;
  FOldValue := '';
  FHilightChanges := True;
  FLabelPosition := lpAbove;
  FColor := clDefault;
  SetupInternalLabel;
  inherited Create(AOwner);
end;


