{ TLCDBEditButton }

procedure TLCDBEditButton.DoCheckEnable;
begin
  Enabled:=FDataLink.Active and (FDataLink.Field<>nil) and (not FDataLink.Field.ReadOnly);
end;

function TLCDBEditButton.GetDataField: string;
begin
  Result:=FDataLink.FieldName;
end;

function TLCDBEditButton.GetDataSource: TDataSource;
begin
  Result:=FDataLink.DataSource;
end;

function TLCDBEditButton.GetReadOnly: Boolean;
begin
  Result:=FDataLink.ReadOnly;
end;

procedure TLCDBEditButton.SetDataField(const AValue: string);
begin
  try
    FDataLink.FieldName:=AValue;
  finally
    DoCheckEnable;
  end;
end;

procedure TLCDBEditButton.SetDataSource(const AValue: TDataSource);
begin
  FDataLink.DataSource:=AValue;
  DoCheckEnable;
end;

procedure TLCDBEditButton.SetReadOnly(const AValue: Boolean);
begin
  FDataLink.ReadOnly:=AValue;
end;

procedure TLCDBEditButton.ActiveChange(Sender: TObject);
begin
  DoCheckEnable;
end;

procedure TLCDBEditButton.DataChange(Sender: TObject);
begin
  if Assigned(FDataLink.Field) then
  begin
    if FDataLink.Field.IsNull then
      Text:=''
    else
      Self.Text:=FDataLink.Field.AsString;
  end else Text:='';
end;

procedure TLCDBEditButton.EditingChange(Sender: TObject);
begin
  inherited ReadOnly := not FDataLink.Editing;
end;

procedure TLCDBEditButton.UpdateData(Sender: TObject);
begin
  if Assigned(FDataLink.Field) then
  begin
    if Self.Text<>'' then
      FDataLink.Field.AsString := Self.Text
    else
      FDataLink.Field.Clear;
  end;
end;

procedure TLCDBEditButton.LMCutToClip(var Message: TLMessage);
begin
  FDataLink.Edit;
  inherited;
end;

procedure TLCDBEditButton.LMPasteFromClip(var Message: TLMessage);
begin
  FDataLink.Edit;
  inherited;
end;

procedure TLCDBEditButton.KeyDown(var Key: Word; Shift: TShiftState);
begin
  inherited KeyDown(Key, Shift);
  if Key=VK_ESCAPE then
  begin
    //cancel out of editing by reset on esc
    FDataLink.Reset;
    SelectAll;
    Key := VK_UNKNOWN;
  end
  else
  if (Key<>VK_UNKNOWN) then
  begin
    //make sure we call edit to ensure the dataset is in edit,
    //this is for where the datasource is in autoedit, so we aren't
    //read only even though the dataset isn't realy in edit
    FDataLink.Edit;
  end;
end;

procedure TLCDBEditButton.Change;
begin
  FDataLink.Modified;
  inherited Change;
end;

procedure TLCDBEditButton.Notification(AComponent: TComponent;
  Operation: TOperation);
begin
  inherited Notification(AComponent, Operation);
  // if the datasource is being removed then we need to make sure
  // we are updated or we can get AV/Seg's *cough* as I foolishly
  // discovered firsthand....
  if (Operation=opRemove) then
  begin
    if (FDataLink<>nil) and (AComponent=DataSource) then
      DataSource:=nil;
  end;
end;

procedure TLCDBEditButton.EditingDone;
begin
  inherited EditingDone;
  if FDataLink.CanModify then
    FDataLink.UpdateRecord;
end;

constructor TLCDBEditButton.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  FDataLink:=TFieldDataLink.Create;
  FDataLink.Control:=Self;
  FDataLink.OnActiveChange:=@ActiveChange;
  FDataLink.OnDataChange:=@DataChange;
  FDataLink.OnUpdateData:=@UpdateData;
end;

destructor TLCDBEditButton.Destroy;
begin
  FreeAndNil(FDataLink);
  inherited Destroy;
end;

{ TLCEditButton }

procedure TLCEditButton.SetLabelSpacing(const Value: Integer);
begin
  FLabelSpacing := Value;
  SetLabelPosition(FLabelPosition);
end;

procedure TLCEditButton.SetAttributes(const AValue: TAttributes);
begin
  FAttributes.Assign(AValue);
end;

procedure TLCEditButton.DoEnter;
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

procedure TLCEditButton.DoExit;
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

procedure TLCEditButton.SetLabelPosition(const Value: TLabelPosition);
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

procedure TLCEditButton.KeyPress(var Key: Char);
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

procedure TLCEditButton.Change;
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

procedure TLCEditButton.CMBidimodechanged(var Message: TLMessage);
begin
  inherited;
  FEditLabel.BiDiMode := BiDiMode;
end;

procedure TLCEditButton.CMEnabledchanged(var Message: TLMessage);
begin
  inherited;
  FEditLabel.Enabled := Enabled;
end;

procedure TLCEditButton.CMVisiblechanged(var Message: TLMessage);
begin
  inherited;
  FEditLabel.Visible := Visible;
end;

procedure TLCEditButton.Notification(AComponent: TComponent;
  Operation: TOperation);
begin
  inherited Notification(AComponent, Operation);
  if (AComponent = FEditLabel) and (Operation = opRemove) then
    FEditLabel := nil;
end;

procedure TLCEditButton.SetBounds(ALeft: Integer; ATop: Integer; AWidth: Integer;
  AHeight: Integer);
begin
  inherited SetBounds(ALeft, ATop, AWidth, AHeight);
  SetLabelPosition(FLabelPosition);
end;

procedure TLCEditButton.SetName(const Value: TComponentName);
begin
  if (csDesigning in ComponentState) and ((FEditlabel.GetTextLen = 0) or
     (CompareText(FEditLabel.Caption, Name) = 0)) then
    FEditLabel.Caption := Value;
  inherited SetName(Value);
  if csDesigning in ComponentState then
    Text := '';
end;

procedure TLCEditButton.SetParent(AParent: TWinControl);
begin
  inherited SetParent(AParent);
  if FEditLabel = nil then exit;
  FEditLabel.Parent := AParent;
  FEditLabel.Visible := True;
end;

procedure TLCEditButton.SetupInternalLabel;
begin
  if Assigned(FEditLabel) then exit;
  FEditLabel := TBoundLabel.Create(Self);
  FEditLabel.FreeNotification(Self);
  FEditLabel.FocusControl := Self;
end;

constructor TLCEditButton.Create(AOwner: TComponent);
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


