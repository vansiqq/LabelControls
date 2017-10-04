{ TLCSpinEdit }
procedure TLCSpinEdit.SetLabelSpacing(const lsValue: Integer);
begin
  FLabelSpacing := lsValue;
  SetLabelPosition(FLabelPosition);
end;

procedure TLCSpinEdit.SetAttributes(const AValue: TAttributes);
begin
  FAttributes.Assign(AValue);
end;

procedure TLCSpinEdit.DoEnter;
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

procedure TLCSpinEdit.DoExit;
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

procedure TLCSpinEdit.SetLabelPosition(const lpValue: TLabelPosition);
var
  P: TPoint;
begin
  if FEditLabel = nil then exit;
  FLabelPosition := lpValue;
  case lpValue of
    lpAbove: P := Point(Left, Top - FEditLabel.Height - FLabelSpacing);
    lpBelow: P := Point(Left, Top + Height + FLabelSpacing);
    lpLeft : P := Point(Left - FEditLabel.Width - FLabelSpacing,
                    Top + ((Height - FEditLabel.Height) div 2));
    lpRight: P := Point(Left + Width + FLabelSpacing,
                    Top + ((Height - FEditLabel.Height) div 2));
  end;
  FEditLabel.SetBounds(P.x, P.y, FEditLabel.Width, FEditLabel.Height);
end;

procedure TLCSpinEdit.KeyPress(var Key: Char);
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

procedure TLCSpinEdit.Change;
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

procedure TLCSpinEdit.CMBidimodechanged(var Message: TLMessage);
begin
  inherited;
  FEditLabel.BiDiMode := BiDiMode;
end;

procedure TLCSpinEdit.CMEnabledchanged(var Message: TLMessage);
begin
  inherited;
  FEditLabel.Enabled := Enabled;
end;

procedure TLCSpinEdit.CMVisiblechanged(var Message: TLMessage);
begin
  inherited;
  FEditLabel.Visible := Visible;
end;

procedure TLCSpinEdit.Notification(AComponent: TComponent;
  Operation: TOperation);
begin
  inherited Notification(AComponent, Operation);
  if (AComponent = FEditLabel) and (Operation = opRemove) then
    FEditLabel := nil;
end;

procedure TLCSpinEdit.SetBounds(ALeft: Integer; ATop: Integer; AWidth: Integer;
  AHeight: Integer);
begin
  inherited SetBounds(ALeft, ATop, AWidth, AHeight);
  SetLabelPosition(FLabelPosition);
end;

procedure TLCSpinEdit.SetName(const snValue: TComponentName);
begin
  if (csDesigning in ComponentState) and ((FEditlabel.GetTextLen = 0) or
     (CompareText(FEditLabel.Caption, Name) = 0)) then
    FEditLabel.Caption := snValue;
  inherited SetName(snValue);
  if csDesigning in ComponentState then
    Text := '';
end;

procedure TLCSpinEdit.SetParent(AParent: TWinControl);
begin
  inherited SetParent(AParent);
  if FEditLabel = nil then exit;
  FEditLabel.Parent := AParent;
  FEditLabel.Visible := True;
end;

procedure TLCSpinEdit.SetupInternalLabel;
begin
  if Assigned(FEditLabel) then exit;
  FEditLabel := TBoundLabel.Create(Self);
  FEditLabel.FreeNotification(Self);
  FEditLabel.FocusControl := Self;
end;

constructor TLCSpinEdit.Create(AOwner: TComponent);
begin
  FAttributes := TAttributes.Create(Self);
  FMarked := False;
  FOldValue := '';
  Alignment := taLeftJustify;
  FHilightChanges := True;
  FLabelPosition := lpAbove;
  FColor := clDefault;
  SetupInternalLabel;
  inherited Create(AOwner);
end;

{ TLCDBSpinEdit }

procedure TLCDBSpinEdit.DoCheckEnable;
begin
  Enabled:=FDataLink.Active and (FDataLink.Field<>nil) and (not FDataLink.Field.ReadOnly);
end;

function TLCDBSpinEdit.GetDataField: string;
begin
  Result:=FDataLink.FieldName;
end;

function TLCDBSpinEdit.GetDataSource: TDataSource;
begin
  Result:=FDataLink.DataSource;
end;

function TLCDBSpinEdit.GetReadOnly: Boolean;
begin
  Result:=FDataLink.ReadOnly;
end;

procedure TLCDBSpinEdit.SetDataField(const AValue: string);
begin
  try
    FDataLink.FieldName:=AValue;
  finally
    DoCheckEnable;
  end;
end;

procedure TLCDBSpinEdit.SetDataSource(const AValue: TDataSource);
begin
  FDataLink.DataSource:=AValue;
  DoCheckEnable;
end;

procedure TLCDBSpinEdit.SetReadOnly(const AValue: Boolean);
begin
  FDataLink.ReadOnly:=AValue;
end;

procedure TLCDBSpinEdit.ActiveChange(Sender: TObject);
begin
  DoCheckEnable;
end;

procedure TLCDBSpinEdit.DataChange(Sender: TObject);
begin
  if Assigned(FDataLink.Field) then
  begin
    if FDataLink.Field.IsNull then
      Text:=''
    else
      Self.Text:=FDataLink.Field.AsString;
  end else Text:='';
end;

procedure TLCDBSpinEdit.EditingChange(Sender: TObject);
begin
  inherited ReadOnly := not FDataLink.Editing;
end;

procedure TLCDBSpinEdit.UpdateData(Sender: TObject);
begin
  if Assigned(FDataLink.Field) then
  begin
    if Self.Text<>'' then
      FDataLink.Field.AsString := Self.Text
    else
      FDataLink.Field.Clear;
  end;
end;

procedure TLCDBSpinEdit.LMCutToClip(var Message: TLMessage);
begin
  FDataLink.Edit;
  inherited;
end;

procedure TLCDBSpinEdit.LMPasteFromClip(var Message: TLMessage);
begin
  FDataLink.Edit;
  inherited;
end;

procedure TLCDBSpinEdit.KeyDown(var Key: Word; Shift: TShiftState);
begin
  inherited KeyDown(Key, Shift);
  if Key=VK_ESCAPE then
  begin
    FDataLink.Reset;
    SelectAll;
    Key := VK_UNKNOWN;
  end
  else
  if (Key<>VK_UNKNOWN) then
  begin
    FDataLink.Edit;
  end;
end;

procedure TLCDBSpinEdit.Change;
begin
  FDataLink.Modified;
  inherited Change;
end;

procedure TLCDBSpinEdit.Notification(AComponent: TComponent;
  Operation: TOperation);
begin
  inherited Notification(AComponent, Operation);
  if (Operation=opRemove) then
  begin
    if (FDataLink<>nil) and (AComponent=DataSource) then
      DataSource:=nil;
  end;
end;

procedure TLCDBSpinEdit.EditingDone;
begin
  inherited EditingDone;
  if FDataLink.CanModify then
    FDataLink.UpdateRecord;
end;

constructor TLCDBSpinEdit.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  FDataLink:=TFieldDataLink.Create;
  FDataLink.Control:=Self;
  FDataLink.OnActiveChange:=@ActiveChange;
  FDataLink.OnDataChange:=@DataChange;
  FDataLink.OnUpdateData:=@UpdateData;
end;

destructor TLCDBSpinEdit.Destroy;
begin
  FreeAndNil(FDataLink);
  inherited Destroy;
end;


