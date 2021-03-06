{$ifdef nnnn}begin end;{$endif}

function DoToolbar_GetToolbarFromId(const Str: string): TATFlatToolbar;
var
  N: PtrInt;
begin
  Result:= nil;

  if Str='top' then
    exit(fmMain.ToolbarMain);

  N:= StrToInt64Def(Str, 0);
  if N<>0 then
    exit(TATFlatToolbar(N));
end;


procedure DoToolbar_Clear(AToolbar: TATFlatToolbar);
var
  i: integer;
begin
  for i:= AToolbar.ButtonCount-1 downto 0 do
    AToolbar.Buttons[i].Free;
  AToolbar.UpdateControls;
end;

procedure DoToolbar_DeleteButton(AToolbar: TATFlatToolbar; AButtonIndex: integer);
begin
  if (AButtonIndex>=0) and (AButtonIndex<AToolbar.ButtonCount) then
    AToolbar.Buttons[AButtonIndex].Free;
  AToolbar.UpdateControls;
end;

function DoToolbar_GetChecked(AToolbar: TATFlatToolbar; AButtonIndex: integer): boolean;
begin
  if (AButtonIndex>=0) and (AButtonIndex<AToolbar.ButtonCount) then
    Result:= AToolbar.Buttons[AButtonIndex].Checked
  else
    Result:= false;
end;


procedure DoToolbar_AddMenu(
  AToolbar: TATFlatToolbar;
  const ACaption: string;
  const ACommand: string;
  const AHint: string;
  AButtonIndex: integer;
  AImageIndex: integer);
var
  mi: TMenuItem;
  mnu: TPopupMenu;
begin
  mi:= TMenuItem.Create(fmMain);
  mi.Caption:= '('+ACommand+')';
  mnu:= TPopupMenu.Create(fmMain);
  mnu.Items.Add(mi);
  AToolbar.AddDropdown(AImageIndex, mnu, nil, ACaption, AHint, ACommand);
end;


procedure DoToolbar_AddButton(
  AToolbar: TATFlatToolbar;
  const ACaption: string;
  const ACommand: string;
  const AHint: string;
  AButtonIndex: integer;
  AImageIndex: integer);
begin
  if ACaption='-' then
  begin
    AToolbar.AddSep;
  end
  else
  if SBeginsWith(ACommand, 'toolmenu:') then
  begin
    DoToolbar_AddMenu(AToolbar, ACaption, ACommand, AHint, AButtonIndex, AImageIndex);
  end
  else
  begin
    AToolbar.AddButton(
      AImageIndex,
      @fmMain.DoToolbarClick,
      ACaption,
      AHint,
      ACommand,
      ACaption<>''
      );
  end;

  if (AButtonIndex>=0) and (AButtonIndex<AToolbar.ButtonCount) then
    AToolbar.SetControlIndex(
      AToolbar.Controls[AToolbar.ControlCount-1],
      AButtonIndex);

  //AToolbar.UpdateControls;
  //API must call TOOLBAR_UPDATE
end;


