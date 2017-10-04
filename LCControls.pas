unit LCControls;

{$mode objfpc}{$H+}

interface

uses
  Classes, SysUtils, LCLType, Controls, StdCtrls, Forms, Graphics, LMessages,
  LCTypes, DBCtrls, db, LResources, ExtCtrls, maskedit, DBMaskEdit, EditBtn,
  Spin;

type

   { TLCDBLookupCombo }
   TLCDBLookupCombo = class(TDBLookupCombobox)
   private
     FColor         : TColor;
     FAttributes    : TAttributes;
     FMarked,
     FHilightChanges: Boolean;
     FOldValue      : String;
     FEditLabel: TBoundLabel;
     FLabelPosition: TLabelPosition;
     FLabelSpacing: Integer;
     procedure SetLabelPosition(const Value: TLabelPosition);
     procedure SetLabelSpacing(const Value: Integer);
     procedure SetAttributes(const AValue: TAttributes);
   protected
     procedure SetParent(AParent: TWinControl); override;
     procedure Notification(AComponent: TComponent; Operation: TOperation); override;
     procedure SetName(const Value: TComponentName); override;
     procedure CMVisiblechanged(var Message: TLMessage);
       message CM_VISIBLECHANGED;
     procedure CMEnabledchanged(var Message: TLMessage);
       message CM_ENABLEDCHANGED;
     procedure CMBidimodechanged(var Message: TLMessage);
       message CM_BIDIMODECHANGED;
     procedure DoEnter; override;
     procedure DoExit; override;
     procedure KeyPress(var Key: Char); override;
     procedure Change; override;
   public
     constructor Create(AOwner: TComponent); override;
   published
     property Attributes: TAttributes read FAttributes write SetAttributes;
     property HilightChanges: Boolean read FHilightChanges write FHilightChanges default True;
     procedure SetBounds(ALeft: Integer; ATop: Integer; AWidth: Integer; AHeight: Integer); override;
     procedure SetupInternalLabel;
     property EditLabel: TBoundLabel read FEditLabel;
     property LabelPosition: TLabelPosition read FLabelPosition write SetLabelPosition;
     property LabelSpacing: Integer read FLabelSpacing write SetLabelSpacing default 2;
   end;

   { TLCListbox }
   TLCListbox = class(TListbox)
   private
     FColor         : TColor;
     FAttributes    : TAttributes;
     FMarked,
     FHilightChanges: Boolean;
     FOldValue      : String;
     FEditLabel: TBoundLabel;
     FLabelPosition: TLabelPosition;
     FLabelSpacing: Integer;
     procedure SetLabelPosition(const Value: TLabelPosition);
     procedure SetLabelSpacing(const Value: Integer);
     procedure SetAttributes(const AValue: TAttributes);
   protected
     procedure SetParent(AParent: TWinControl); override;
     procedure Notification(AComponent: TComponent; Operation: TOperation); override;
     procedure SetName(const Value: TComponentName); override;
     procedure CMVisiblechanged(var Message: TLMessage);
       message CM_VISIBLECHANGED;
     procedure CMEnabledchanged(var Message: TLMessage);
       message CM_ENABLEDCHANGED;
     procedure CMBidimodechanged(var Message: TLMessage);
       message CM_BIDIMODECHANGED;
     procedure DoEnter; override;
     procedure DoExit; override;
     procedure KeyPress(var Key: Char); override;
   public
     constructor Create(AOwner: TComponent); override;
   published
     property Attributes: TAttributes read FAttributes write SetAttributes;
     property HilightChanges: Boolean read FHilightChanges write FHilightChanges default True;
     procedure SetBounds(ALeft: Integer; ATop: Integer; AWidth: Integer; AHeight: Integer); override;
     procedure SetupInternalLabel;
     property EditLabel: TBoundLabel read FEditLabel;
     property LabelPosition: TLabelPosition read FLabelPosition write SetLabelPosition;
     property LabelSpacing: Integer read FLabelSpacing write SetLabelSpacing default 2;
   end;

   { TLCDBLookupList }
   TLCDBLookupList = class(TDBLookupListbox)
   private
     FColor         : TColor;
     FAttributes    : TAttributes;
     FMarked,
     FHilightChanges: Boolean;
     FOldValue      : String;
     FEditLabel: TBoundLabel;
     FLabelPosition: TLabelPosition;
     FLabelSpacing: Integer;
     procedure SetLabelPosition(const Value: TLabelPosition);
     procedure SetLabelSpacing(const Value: Integer);
     procedure SetAttributes(const AValue: TAttributes);
   protected
     procedure SetParent(AParent: TWinControl); override;
     procedure Notification(AComponent: TComponent; Operation: TOperation); override;
     procedure SetName(const Value: TComponentName); override;
     procedure CMVisiblechanged(var Message: TLMessage);
       message CM_VISIBLECHANGED;
     procedure CMEnabledchanged(var Message: TLMessage);
       message CM_ENABLEDCHANGED;
     procedure CMBidimodechanged(var Message: TLMessage);
       message CM_BIDIMODECHANGED;
     procedure DoEnter; override;
     procedure DoExit; override;
     procedure KeyPress(var Key: Char); override;
   public
     constructor Create(AOwner: TComponent); override;
   published
     property Attributes: TAttributes read FAttributes write SetAttributes;
     property HilightChanges: Boolean read FHilightChanges write FHilightChanges default True;
     procedure SetBounds(ALeft: Integer; ATop: Integer; AWidth: Integer; AHeight: Integer); override;
     procedure SetupInternalLabel;
     property EditLabel: TBoundLabel read FEditLabel;
     property LabelPosition: TLabelPosition read FLabelPosition write SetLabelPosition;
     property LabelSpacing: Integer read FLabelSpacing write SetLabelSpacing default 2;
   end;

   { TLCDBListbox }
   TLCDBListbox = class(TDBListbox)
   private
     FColor         : TColor;
     FAttributes    : TAttributes;
     FMarked,
     FHilightChanges: Boolean;
     FOldValue      : String;
     FEditLabel: TBoundLabel;
     FLabelPosition: TLabelPosition;
     FLabelSpacing: Integer;
     procedure SetLabelPosition(const Value: TLabelPosition);
     procedure SetLabelSpacing(const Value: Integer);
     procedure SetAttributes(const AValue: TAttributes);
   protected
     procedure SetParent(AParent: TWinControl); override;
     procedure Notification(AComponent: TComponent; Operation: TOperation); override;
     procedure SetName(const Value: TComponentName); override;
     procedure CMVisiblechanged(var Message: TLMessage);
       message CM_VISIBLECHANGED;
     procedure CMEnabledchanged(var Message: TLMessage);
       message CM_ENABLEDCHANGED;
     procedure CMBidimodechanged(var Message: TLMessage);
       message CM_BIDIMODECHANGED;
     procedure DoEnter; override;
     procedure DoExit; override;
     procedure KeyPress(var Key: Char); override;
   public
     constructor Create(AOwner: TComponent); override;
   published
     property Attributes: TAttributes read FAttributes write SetAttributes;
     property HilightChanges: Boolean read FHilightChanges write FHilightChanges default True;
     procedure SetBounds(ALeft: Integer; ATop: Integer; AWidth: Integer; AHeight: Integer); override;
     procedure SetupInternalLabel;
     property EditLabel: TBoundLabel read FEditLabel;
     property LabelPosition: TLabelPosition read FLabelPosition write SetLabelPosition;
     property LabelSpacing: Integer read FLabelSpacing write SetLabelSpacing default 2;
   end;

   { TLCCombobox }
   TLCCombobox = class(TCombobox)
   private
     FColor         : TColor;
     FAttributes    : TAttributes;
     FMarked,
     FHilightChanges: Boolean;
     FOldValue      : String;
     FEditLabel: TBoundLabel;
     FLabelPosition: TLabelPosition;
     FLabelSpacing: Integer;
     procedure SetLabelPosition(const Value: TLabelPosition);
     procedure SetLabelSpacing(const Value: Integer);
     procedure SetAttributes(const AValue: TAttributes);
   protected
     procedure SetParent(AParent: TWinControl); override;
     procedure Notification(AComponent: TComponent; Operation: TOperation); override;
     procedure SetName(const Value: TComponentName); override;
     procedure CMVisiblechanged(var Message: TLMessage);
       message CM_VISIBLECHANGED;
     procedure CMEnabledchanged(var Message: TLMessage);
       message CM_ENABLEDCHANGED;
     procedure CMBidimodechanged(var Message: TLMessage);
       message CM_BIDIMODECHANGED;
     procedure DoEnter; override;
     procedure DoExit; override;
     procedure KeyPress(var Key: Char); override;
     procedure Change; override;
   public
     constructor Create(AOwner: TComponent); override;
   published
     property Attributes: TAttributes read FAttributes write SetAttributes;
     property HilightChanges: Boolean read FHilightChanges write FHilightChanges default True;
     procedure SetBounds(ALeft: Integer; ATop: Integer; AWidth: Integer; AHeight: Integer); override;
     procedure SetupInternalLabel;
     property EditLabel: TBoundLabel read FEditLabel;
     property LabelPosition: TLabelPosition read FLabelPosition write SetLabelPosition;
     property LabelSpacing: Integer read FLabelSpacing write SetLabelSpacing default 2;
   end;

   { TLCDBCombobox }
   TLCDBCombobox = class(TDBCombobox)
   private
     FColor         : TColor;
     FAttributes    : TAttributes;
     FMarked,
     FHilightChanges: Boolean;
     FOldValue      : String;
     FEditLabel: TBoundLabel;
     FLabelPosition: TLabelPosition;
     FLabelSpacing: Integer;
     procedure SetLabelPosition(const Value: TLabelPosition);
     procedure SetLabelSpacing(const Value: Integer);
     procedure SetAttributes(const AValue: TAttributes);
   protected
     procedure SetParent(AParent: TWinControl); override;
     procedure Notification(AComponent: TComponent; Operation: TOperation); override;
     procedure SetName(const Value: TComponentName); override;
     procedure CMVisiblechanged(var Message: TLMessage);
       message CM_VISIBLECHANGED;
     procedure CMEnabledchanged(var Message: TLMessage);
       message CM_ENABLEDCHANGED;
     procedure CMBidimodechanged(var Message: TLMessage);
       message CM_BIDIMODECHANGED;
     procedure DoEnter; override;
     procedure DoExit; override;
     procedure KeyPress(var Key: Char); override;
     procedure Change; override;
   public
     constructor Create(AOwner: TComponent); override;
   published
     property Attributes: TAttributes read FAttributes write SetAttributes;
     property HilightChanges: Boolean read FHilightChanges write FHilightChanges default True;
     procedure SetBounds(ALeft: Integer; ATop: Integer; AWidth: Integer; AHeight: Integer); override;
     procedure SetupInternalLabel;
     property EditLabel: TBoundLabel read FEditLabel;
     property LabelPosition: TLabelPosition read FLabelPosition write SetLabelPosition;
     property LabelSpacing: Integer read FLabelSpacing write SetLabelSpacing default 2;
   end;

  { TLCMemo }
  TLCMemo = class(TMemo)
  private
    FColor         : TColor;
    FAttributes    : TAttributes;
    FMarked,
    FHilightChanges: Boolean;
    FOldValue      : String;
    FEditLabel: TBoundLabel;
    FLabelPosition: TLabelPosition;
    FLabelSpacing: Integer;
    procedure SetLabelPosition(const Value: TLabelPosition);
    procedure SetLabelSpacing(const Value: Integer);
    procedure SetAttributes(const AValue: TAttributes);
  protected
    procedure SetParent(AParent: TWinControl); override;
    procedure Notification(AComponent: TComponent; Operation: TOperation); override;
    procedure SetName(const Value: TComponentName); override;
    procedure CMVisiblechanged(var Message: TLMessage);
      message CM_VISIBLECHANGED;
    procedure CMEnabledchanged(var Message: TLMessage);
      message CM_ENABLEDCHANGED;
    procedure CMBidimodechanged(var Message: TLMessage);
      message CM_BIDIMODECHANGED;
    procedure DoEnter; override;
    procedure DoExit; override;
    procedure KeyPress(var Key: Char); override;
    procedure Change; override;
  public
    constructor Create(AOwner: TComponent); override;
  published
    property Attributes: TAttributes read FAttributes write SetAttributes;
    property HilightChanges: Boolean read FHilightChanges write FHilightChanges default True;
    procedure SetBounds(ALeft: Integer; ATop: Integer; AWidth: Integer; AHeight: Integer); override;
    procedure SetupInternalLabel;
    property EditLabel: TBoundLabel read FEditLabel;
    property LabelPosition: TLabelPosition read FLabelPosition write SetLabelPosition;
    property LabelSpacing: Integer read FLabelSpacing write SetLabelSpacing default 2;
  end;

  { TLCDBMemo }
  TLCDBMemo = class(TDBMemo)
  private
    FColor         : TColor;
    FAttributes    : TAttributes;
    FMarked,
    FHilightChanges: Boolean;
    FOldValue      : String;
    FEditLabel: TBoundLabel;
    FLabelPosition: TLabelPosition;
    FLabelSpacing: Integer;
    procedure SetLabelPosition(const Value: TLabelPosition);
    procedure SetLabelSpacing(const Value: Integer);
    procedure SetAttributes(const AValue: TAttributes);
  protected
    procedure SetParent(AParent: TWinControl); override;
    procedure Notification(AComponent: TComponent; Operation: TOperation); override;
    procedure SetName(const Value: TComponentName); override;
    procedure CMVisiblechanged(var Message: TLMessage);
      message CM_VISIBLECHANGED;
    procedure CMEnabledchanged(var Message: TLMessage);
      message CM_ENABLEDCHANGED;
    procedure CMBidimodechanged(var Message: TLMessage);
      message CM_BIDIMODECHANGED;
    procedure DoEnter; override;
    procedure DoExit; override;
    procedure KeyPress(var Key: Char); override;
    procedure Change; override;
  public
    constructor Create(AOwner: TComponent); override;
  published
    property Attributes: TAttributes read FAttributes write SetAttributes;
    property HilightChanges: Boolean read FHilightChanges write FHilightChanges default True;
    procedure SetBounds(ALeft: Integer; ATop: Integer; AWidth: Integer; AHeight: Integer); override;
    procedure SetupInternalLabel;
    property EditLabel: TBoundLabel read FEditLabel;
    property LabelPosition: TLabelPosition read FLabelPosition write SetLabelPosition;
    property LabelSpacing: Integer read FLabelSpacing write SetLabelSpacing default 2;
  end;

 { LCSpinEdit }
  TLCSpinEdit = class(TSpinEdit)
  private
    FColor         : TColor;
    FAttributes    : TAttributes;
    FMarked,
    FHilightChanges: Boolean;
    FOldValue      : String;
    FEditLabel: TBoundLabel;
    FLabelPosition: TLabelPosition;
    FLabelSpacing: Integer;
    procedure SetLabelPosition(const lpValue: TLabelPosition);
    procedure SetLabelSpacing(const lsValue: Integer);
    procedure SetAttributes(const AValue: TAttributes);
  protected
    procedure SetParent(AParent: TWinControl); override;
    procedure Notification(AComponent: TComponent; Operation: TOperation); override;
    procedure SetName(const snValue: TComponentName); override;
    procedure CMVisiblechanged(var Message: TLMessage);
      message CM_VISIBLECHANGED;
    procedure CMEnabledchanged(var Message: TLMessage);
      message CM_ENABLEDCHANGED;
    procedure CMBidimodechanged(var Message: TLMessage);
      message CM_BIDIMODECHANGED;
    procedure DoEnter; override;
    procedure DoExit; override;
    procedure KeyPress(var Key: Char); override;
    procedure Change; override;
  public
    constructor Create(AOwner: TComponent); override;
  published
    property Attributes: TAttributes read FAttributes write SetAttributes;
    property HilightChanges: Boolean read FHilightChanges write FHilightChanges default True;
    procedure SetBounds(ALeft: Integer; ATop: Integer; AWidth: Integer; AHeight: Integer); override;
    procedure SetupInternalLabel;
    property EditLabel: TBoundLabel read FEditLabel;
    property LabelPosition: TLabelPosition read FLabelPosition write SetLabelPosition;
    property LabelSpacing: Integer read FLabelSpacing write SetLabelSpacing default 2;
  end;

  { TLCDBSpinEdit }
  TLCDBSpinEdit = class(TLCSpinEdit)
  private
    { Private declarations }
    FDataLink: TFieldDataLink;
    procedure DoCheckEnable;
    function GetDataField: string;
    function GetDataSource: TDataSource;
    function GetReadOnly: Boolean;
    procedure SetDataField(const AValue: string);
    procedure SetDataSource(const AValue: TDataSource);
    procedure SetReadOnly(const AValue: Boolean);
  protected
    { Protected declarations }
    procedure ActiveChange(Sender:TObject);
    procedure DataChange(Sender:TObject);
    procedure EditingChange(Sender: TObject);
    procedure UpdateData(Sender:TObject);
    procedure LMCutToClip(var Message: TLMessage); message LM_CUT;
    procedure LMPasteFromClip(var Message: TLMessage); message LM_PASTE;
    procedure KeyDown(var Key: Word; Shift: TShiftState); override;
    procedure Change; override;
    procedure Notification(AComponent: TComponent; Operation: TOperation); override;
    procedure EditingDone; override;
  public
    { Public declarations }
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  published
    { Published declarations }
    property DataField: string read GetDataField write SetDataField;
    property DataSource: TDataSource read GetDataSource write SetDataSource;
    property ReadOnly: Boolean read GetReadOnly write SetReadOnly default False;
  end;

  { TLCFloatSpinEdit }
  TLCFloatSpinEdit = class(TFloatSpinEdit)
  private
    FColor         : TColor;
    FAttributes    : TAttributes;
    FMarked,
    FHilightChanges: Boolean;
    FOldValue      : String;
    FEditLabel: TBoundLabel;
    FLabelPosition: TLabelPosition;
    FLabelSpacing: Integer;
    procedure SetLabelPosition(const lpValue: TLabelPosition);
    procedure SetLabelSpacing(const lsValue: Integer);
    procedure SetAttributes(const AValue: TAttributes);
  protected
    procedure SetParent(AParent: TWinControl); override;
    procedure Notification(AComponent: TComponent; Operation: TOperation); override;
    procedure SetName(const snValue: TComponentName); override;
    procedure CMVisiblechanged(var Message: TLMessage);
      message CM_VISIBLECHANGED;
    procedure CMEnabledchanged(var Message: TLMessage);
      message CM_ENABLEDCHANGED;
    procedure CMBidimodechanged(var Message: TLMessage);
      message CM_BIDIMODECHANGED;
    procedure DoEnter; override;
    procedure DoExit; override;
    procedure KeyPress(var Key: Char); override;
    procedure Change; override;
  public
    constructor Create(AOwner: TComponent); override;
  published
    property Attributes: TAttributes read FAttributes write SetAttributes;
    property HilightChanges: Boolean read FHilightChanges write FHilightChanges default True;
    procedure SetBounds(ALeft: Integer; ATop: Integer; AWidth: Integer; AHeight: Integer); override;
    procedure SetupInternalLabel;
    property EditLabel: TBoundLabel read FEditLabel;
    property LabelPosition: TLabelPosition read FLabelPosition write SetLabelPosition;
    property LabelSpacing: Integer read FLabelSpacing write SetLabelSpacing default 2;
  end;

  { TLCDBFloatSpinEdit }
  TLCDBFloatSpinEdit = class(TLCFloatSpinEdit)
  private
    { Private declarations }
    FDataLink: TFieldDataLink;
    procedure DoCheckEnable;
    function GetDataField: string;
    function GetDataSource: TDataSource;
    function GetReadOnly: Boolean;
    procedure SetDataField(const AValue: string);
    procedure SetDataSource(const AValue: TDataSource);
    procedure SetReadOnly(const AValue: Boolean);
  protected
    { Protected declarations }
    procedure ActiveChange(Sender:TObject);
    procedure DataChange(Sender:TObject);
    procedure EditingChange(Sender: TObject);
    procedure UpdateData(Sender:TObject);
    procedure LMCutToClip(var Message: TLMessage); message LM_CUT;
    procedure LMPasteFromClip(var Message: TLMessage); message LM_PASTE;
    procedure KeyDown(var Key: Word; Shift: TShiftState); override;
    procedure Change; override;
    procedure Notification(AComponent: TComponent; Operation: TOperation); override;
    procedure EditingDone; override;
  public
    { Public declarations }
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  published
    { Published declarations }
    property DataField: string read GetDataField write SetDataField;
    property DataSource: TDataSource read GetDataSource write SetDataSource;
    property ReadOnly: Boolean read GetReadOnly write SetReadOnly default False;
  end;

  { TLCCalcEdit }
  TLCCalcEdit = class(TCalcEdit)
  private
    FColor         : TColor;
    FAttributes    : TAttributes;
    FMarked,
    FHilightChanges: Boolean;
    FOldValue      : String;
    FEditLabel: TBoundLabel;
    FLabelPosition: TLabelPosition;
    FLabelSpacing: Integer;
    procedure SetLabelPosition(const Value: TLabelPosition);
    procedure SetLabelSpacing(const Value: Integer);
    procedure SetAttributes(const AValue: TAttributes);
  protected
    procedure SetParent(AParent: TWinControl); override;
    procedure Notification(AComponent: TComponent; Operation: TOperation); override;
    procedure SetName(const Value: TComponentName); override;
    procedure CMVisiblechanged(var Message: TLMessage);
      message CM_VISIBLECHANGED;
    procedure CMEnabledchanged(var Message: TLMessage);
      message CM_ENABLEDCHANGED;
    procedure CMBidimodechanged(var Message: TLMessage);
      message CM_BIDIMODECHANGED;
    procedure DoEnter; override;
    procedure DoExit; override;
    procedure KeyPress(var Key: Char); override;
    procedure Change; override;
  public
    constructor Create(AOwner: TComponent); override;
  published
    property Alignment;
    property Attributes: TAttributes read FAttributes write SetAttributes;
    property HilightChanges: Boolean read FHilightChanges write FHilightChanges default True;
    procedure SetBounds(ALeft: Integer; ATop: Integer; AWidth: Integer; AHeight: Integer); override;
    procedure SetupInternalLabel;
    property EditLabel: TBoundLabel read FEditLabel;
    property LabelPosition: TLabelPosition read FLabelPosition write SetLabelPosition;
    property LabelSpacing: Integer read FLabelSpacing write SetLabelSpacing default 2;
  end;

  { TLCDBCalcEdit }
  TLCDBCalcEdit = class(TLCCalcEdit)
  private
    { Private declarations }
    FDataLink: TFieldDataLink;
    procedure DoCheckEnable;
    function GetDataField: string;
    function GetDataSource: TDataSource;
    function GetReadOnly: Boolean;
    procedure SetDataField(const AValue: string);
    procedure SetDataSource(const AValue: TDataSource);
    procedure SetReadOnly(const AValue: Boolean);
  protected
    { Protected declarations }
    procedure ActiveChange(Sender:TObject);
    procedure DataChange(Sender:TObject);
    procedure EditingChange(Sender: TObject);
    procedure UpdateData(Sender:TObject);
    procedure LMCutToClip(var Message: TLMessage); message LM_CUT;
    procedure LMPasteFromClip(var Message: TLMessage); message LM_PASTE;
    procedure KeyDown(var Key: Word; Shift: TShiftState); override;
    procedure Change; override;
    procedure Notification(AComponent: TComponent; Operation: TOperation); override;
    procedure EditingDone; override;
  public
    { Public declarations }
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  published
    { Published declarations }
    property DataField: string read GetDataField write SetDataField;
    property DataSource: TDataSource read GetDataSource write SetDataSource;
    property ReadOnly: Boolean read GetReadOnly write SetReadOnly default False;
  end;

  { TLCDateEdit }
  TLCDateEdit = class(TDateEdit)
  private
    FColor         : TColor;
    FAttributes    : TAttributes;
    FMarked,
    FHilightChanges: Boolean;
    FOldValue      : String;
    FEditLabel: TBoundLabel;
    FLabelPosition: TLabelPosition;
    FLabelSpacing: Integer;
    procedure SetLabelPosition(const Value: TLabelPosition);
    procedure SetLabelSpacing(const Value: Integer);
    procedure SetAttributes(const AValue: TAttributes);
  protected
    procedure SetParent(AParent: TWinControl); override;
    procedure Notification(AComponent: TComponent; Operation: TOperation); override;
    procedure SetName(const Value: TComponentName); override;
    procedure CMVisiblechanged(var Message: TLMessage);
      message CM_VISIBLECHANGED;
    procedure CMEnabledchanged(var Message: TLMessage);
      message CM_ENABLEDCHANGED;
    procedure CMBidimodechanged(var Message: TLMessage);
      message CM_BIDIMODECHANGED;
    procedure DoEnter; override;
    procedure DoExit; override;
    procedure KeyPress(var Key: Char); override;
    procedure Change; override;
  public
    constructor Create(AOwner: TComponent); override;
  published
    property Attributes: TAttributes read FAttributes write SetAttributes;
    property HilightChanges: Boolean read FHilightChanges write FHilightChanges default True;
    procedure SetBounds(ALeft: Integer; ATop: Integer; AWidth: Integer; AHeight: Integer); override;
    procedure SetupInternalLabel;
    property EditLabel: TBoundLabel read FEditLabel;
    property LabelPosition: TLabelPosition read FLabelPosition write SetLabelPosition;
    property LabelSpacing: Integer read FLabelSpacing write SetLabelSpacing default 2;
  end;

  { TLCDBDateEdit }
  TLCDBDateEdit = class(TLCDateEdit)
  private
    { Private declarations }
    FDataLink: TFieldDataLink;
    procedure DoCheckEnable;
    function GetDataField: string;
    function GetDataSource: TDataSource;
    function GetReadOnly: Boolean;
    procedure SetDataField(const AValue: string);
    procedure SetDataSource(const AValue: TDataSource);
    procedure SetReadOnly(const AValue: Boolean);
  protected
    { Protected declarations }
    procedure ActiveChange(Sender:TObject);
    procedure DataChange(Sender:TObject);
    procedure EditingChange(Sender: TObject);
    procedure UpdateData(Sender:TObject);
    procedure LMCutToClip(var Message: TLMessage); message LM_CUT;
    procedure LMPasteFromClip(var Message: TLMessage); message LM_PASTE;
    procedure KeyDown(var Key: Word; Shift: TShiftState); override;
    procedure Change; override;
    procedure Notification(AComponent: TComponent; Operation: TOperation); override;
    procedure EditingDone; override;
  public
    { Public declarations }
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  published
    { Published declarations }
    property DataField: string read GetDataField write SetDataField;
    property DataSource: TDataSource read GetDataSource write SetDataSource;
    property ReadOnly: Boolean read GetReadOnly write SetReadOnly default False;
  end;

  { TLCEditButton }
  TLCEditButton = class(TEditButton)
  private
    FColor         : TColor;
    FAttributes    : TAttributes;
    FMarked,
    FHilightChanges: Boolean;
    FOldValue      : String;
    FEditLabel: TBoundLabel;
    FLabelPosition: TLabelPosition;
    FLabelSpacing: Integer;
    procedure SetLabelPosition(const Value: TLabelPosition);
    procedure SetLabelSpacing(const Value: Integer);
    procedure SetAttributes(const AValue: TAttributes);
  protected
    procedure SetParent(AParent: TWinControl); override;
    procedure Notification(AComponent: TComponent; Operation: TOperation); override;
    procedure SetName(const Value: TComponentName); override;
    procedure CMVisiblechanged(var Message: TLMessage);
      message CM_VISIBLECHANGED;
    procedure CMEnabledchanged(var Message: TLMessage);
      message CM_ENABLEDCHANGED;
    procedure CMBidimodechanged(var Message: TLMessage);
      message CM_BIDIMODECHANGED;
    procedure DoEnter; override;
    procedure DoExit; override;
    procedure KeyPress(var Key: Char); override;
    procedure Change; override;
  public
    constructor Create(AOwner: TComponent); override;
  published
    property Attributes: TAttributes read FAttributes write SetAttributes;
    property HilightChanges: Boolean read FHilightChanges write FHilightChanges default True;
    procedure SetBounds(ALeft: Integer; ATop: Integer; AWidth: Integer; AHeight: Integer); override;
    procedure SetupInternalLabel;
    property EditLabel: TBoundLabel read FEditLabel;
    property LabelPosition: TLabelPosition read FLabelPosition write SetLabelPosition;
    property LabelSpacing: Integer read FLabelSpacing write SetLabelSpacing default 2;
   end;

  { TLCDBEditButton }
  TLCDBEditButton = class(TLCEditButton)
  private
    { Private declarations }
    FDataLink: TFieldDataLink;
    procedure DoCheckEnable;
    function GetDataField: string;
    function GetDataSource: TDataSource;
    function GetReadOnly: Boolean;
    procedure SetDataField(const AValue: string);
    procedure SetDataSource(const AValue: TDataSource);
    procedure SetReadOnly(const AValue: Boolean);
  protected
    { Protected declarations }
    procedure ActiveChange(Sender:TObject);
    procedure DataChange(Sender:TObject);
    procedure EditingChange(Sender: TObject);
    procedure UpdateData(Sender:TObject);
    procedure LMCutToClip(var Message: TLMessage); message LM_CUT;
    procedure LMPasteFromClip(var Message: TLMessage); message LM_PASTE;
    procedure KeyDown(var Key: Word; Shift: TShiftState); override;
    procedure Change; override;
    procedure Notification(AComponent: TComponent; Operation: TOperation); override;
    procedure EditingDone; override;
  public
    { Public declarations }
    constructor Create(AOwner: TComponent); override;
    destructor Destroy; override;
  published
    { Published declarations }
    property DataField: string read GetDataField write SetDataField;
    property DataSource: TDataSource read GetDataSource write SetDataSource;
    property ReadOnly: Boolean read GetReadOnly write SetReadOnly default False;
  end;

  { TLCEdit }
  TLCEdit = class(TEdit)
  private
    FColor         : TColor;
    FAttributes    : TAttributes;
    FMarked,
    FHilightChanges: Boolean;
    FOldValue      : String;
    FEditLabel: TBoundLabel;
    FLabelPosition: TLabelPosition;
    FLabelSpacing: Integer;
    procedure SetLabelPosition(const Value: TLabelPosition);
    procedure SetLabelSpacing(const Value: Integer);
    procedure SetAttributes(const AValue: TAttributes);
  protected
    procedure SetParent(AParent: TWinControl); override;
    procedure Notification(AComponent: TComponent; Operation: TOperation); override;
    procedure SetName(const Value: TComponentName); override;
    procedure CMVisiblechanged(var Message: TLMessage);
      message CM_VISIBLECHANGED;
    procedure CMEnabledchanged(var Message: TLMessage);
      message CM_ENABLEDCHANGED;
    procedure CMBidimodechanged(var Message: TLMessage);
      message CM_BIDIMODECHANGED;
    procedure DoEnter; override;
    procedure DoExit; override;
    procedure KeyPress(var Key: Char); override;
    procedure Change; override;
  public
    constructor Create(AOwner: TComponent); override;
  published
    property Attributes: TAttributes read FAttributes write SetAttributes;
    property HilightChanges: Boolean read FHilightChanges write FHilightChanges default True;
    procedure SetBounds(ALeft: Integer; ATop: Integer; AWidth: Integer; AHeight: Integer); override;
    procedure SetupInternalLabel;
    property EditLabel: TBoundLabel read FEditLabel;
    property LabelPosition: TLabelPosition read FLabelPosition write SetLabelPosition;
    property LabelSpacing: Integer read FLabelSpacing write SetLabelSpacing default 2;
  end;

  { TLCDBEdit }
  TLCDBEdit = class(TDBEdit)
  private
    FColor         : TColor;
    FAttributes    : TAttributes;
    FMarked,
    FHilightChanges: Boolean;
    FOldValue      : String;
    FEditLabel: TBoundLabel;
    FLabelPosition: TLabelPosition;
    FLabelSpacing: Integer;
    procedure SetLabelPosition(const Value: TLabelPosition);
    procedure SetLabelSpacing(const Value: Integer);
    procedure SetAttributes(const AValue: TAttributes);
  protected
    procedure SetParent(AParent: TWinControl); override;
    procedure Notification(AComponent: TComponent; Operation: TOperation); override;
    procedure SetName(const Value: TComponentName); override;
    procedure CMVisiblechanged(var Message: TLMessage);
      message CM_VISIBLECHANGED;
    procedure CMEnabledchanged(var Message: TLMessage);
      message CM_ENABLEDCHANGED;
    procedure CMBidimodechanged(var Message: TLMessage);
      message CM_BIDIMODECHANGED;
    procedure DoEnter; override;
    procedure DoExit; override;
    procedure KeyPress(var Key: Char); override;
    procedure Change; override;
  public
    constructor Create(AOwner: TComponent); override;
  published
    property Attributes: TAttributes read FAttributes write SetAttributes;
    property HilightChanges: Boolean read FHilightChanges write FHilightChanges default True;
    procedure SetBounds(ALeft: Integer; ATop: Integer; AWidth: Integer; AHeight: Integer); override;
    procedure SetupInternalLabel;
    property EditLabel: TBoundLabel read FEditLabel;
    property LabelPosition: TLabelPosition read FLabelPosition write SetLabelPosition;
    property LabelSpacing: Integer read FLabelSpacing write SetLabelSpacing default 2;
  end;

  { TLCNumericEdit }
  TLCNumericEdit = class(TLCEdit)
  private
    FEditType        : TEditType;
    FDecimals        : Byte;
    FCurrencySymbol,
    FDecimalSeparator: String;
    FNegativeColor,
    FFontColor       : TColor;
    function GetEditType: TEditType;
    function GetCurrencySymbol: String;
    function GetDecimals: Byte;
    function GetDecimalSeparator: String;
    function GetFloatValue: Extended;
    function GetIntValue: Integer;
    function GetNegativeColor: TColor;
    procedure SetEditType(const AValue: TEditType);
    procedure SetCurrencySymbol(const AValue: String);
    procedure SetDecimals(const AValue: Byte);
    procedure SetAttributes(const AValue: TAttributes);
    procedure SetFloatValue(const AValue: Extended);
    procedure SetNegativeColor(const AValue: TColor);
    procedure WhenExit;
  protected
    procedure DoEnter; override;
    procedure DoExit; override;
    procedure KeyPress(var Key: Char); override;
    procedure Change; override;
  public
    constructor Create(AOwner: TComponent); override;
  published
    property Alignment;
    property EditType: TEditType read GetEditType write SetEditType default etInteger;
    property CurrencySymbol: String read GetCurrencySymbol write SetCurrencySymbol;
    property Decimals: Byte read GetDecimals write SetDecimals default 2;
    property NegativeColor: TColor read GetNegativeColor write SetNegativeColor default clRed;
    property DecimalSeparator: String read GetDecimalSeparator;
    property IntValue: Integer read GetIntValue;
    property FloatValue: Extended read GetFloatValue;
    property Value: Extended read GetFloatValue write SetFloatValue;
  end;

  { TLCDBNumericEdit }
  TLCDBNumericEdit = class(TLCDBEdit)
  private
    FEditType        : TEditType;
    FDecimals        : Byte;
    FCurrencySymbol,
    FDecimalSeparator: String;
    FNegativeColor,
    FFontColor       : TColor;
    function GetEditType: TEditType;
    function GetCurrencySymbol: String;
    function GetDecimals: Byte;
    function GetDecimalSeparator: String;
    function GetFloatValue: Extended;
    function GetIntValue: Integer;
    function GetNegativeColor: TColor;
    procedure SetEditType(const AValue: TEditType);
    procedure SetCurrencySymbol(const AValue: String);
    procedure SetDecimals(const AValue: Byte);
    procedure SetAttributes(const AValue: TAttributes);
    procedure SetFloatValue(const AValue: Extended);
    procedure SetNegativeColor(const AValue: TColor);
    procedure WhenExit;
  protected
    procedure DoEnter; override;
    procedure DoExit; override;
    procedure KeyPress(var Key: Char); override;
    procedure Change; override;
  public
    constructor Create(AOwner: TComponent); override;
  published
    property Alignment;
    property EditType: TEditType read GetEditType write SetEditType default etInteger;
    property CurrencySymbol: String read GetCurrencySymbol write SetCurrencySymbol;
    property Decimals: Byte read GetDecimals write SetDecimals default 2;
    property NegativeColor: TColor read GetNegativeColor write SetNegativeColor default clRed;
    property DecimalSeparator: String read GetDecimalSeparator;
    property IntValue: Integer read GetIntValue;
    property FloatValue: Extended read GetFloatValue;
    property Value: Extended read GetFloatValue write SetFloatValue;
  end;

 { TLCMaskEdit }
  TLCMaskEdit = class(TMaskEdit)
  private
    FColor             : TColor;
    FAttributes        : TAttributes;
    FSaveLiterals,
    FValidate,
    FMarked,
    FHilightChanges    : Boolean;
    FOldValue          : String;
    FMaskType          : TMaskType;
    FAlternate         : TAlternableMask;
    FCharForBlanks     : Char;
    FControlMask       : Byte;
    FAlternableShortCut: TShortCut;
    FEditLabel: TBoundLabel;
    FLabelPosition: TLabelPosition;
    FLabelSpacing: Integer;
    procedure SetLabelPosition(const Value: TLabelPosition);
    procedure SetLabelSpacing(const Value: Integer);
    procedure SetAttributes(const AValue: TAttributes);
    procedure SetMask(const AValue: TMaskType);
    procedure SetValidate(const AValue: Boolean);
  protected
    procedure SetParent(AParent: TWinControl); override;
    procedure Notification(AComponent: TComponent; Operation: TOperation); override;
    procedure SetName(const Value: TComponentName); override;
    procedure CMVisiblechanged(var Message: TLMessage);
    message CM_VISIBLECHANGED;
    procedure CMEnabledchanged(var Message: TLMessage);
    message CM_ENABLEDCHANGED;
    procedure CMBidimodechanged(var Message: TLMessage);
    message CM_BIDIMODECHANGED;
    procedure DoEnter; override;
    procedure DoExit; override;
    procedure KeyPress(var Key: Char); override;
    procedure Change; override;
    procedure KeyUp(var Key: Word; Shift: TShiftState); override;
  public
    constructor Create(AOwner: TComponent); override;
  published
    property Attributes: TAttributes
    read FAttributes write SetAttributes;
    property HilightChanges: Boolean read FHilightChanges write FHilightChanges default True;
    property Validate: Boolean
    read FValidate write SetValidate default True;
    property SaveLiterals: Boolean
    read FSaveLiterals write FSaveLiterals default False;
    property MaskType: TMaskType read FMaskType write SetMask;
    property AlternableMasks: TAlternableMask  read FAlternate write FAlternate;
    property CharForBlanks: Char read FCharForBlanks write FCharForBlanks;
    property AlternableShortCut: TShortCut read FAlternableShortCut write FAlternableShortCut;
    procedure SetBounds(ALeft: Integer; ATop: Integer; AWidth: Integer; AHeight: Integer); override;
    procedure SetupInternalLabel;
    property EditLabel: TBoundLabel read FEditLabel;
    property LabelPosition: TLabelPosition read FLabelPosition write SetLabelPosition;
    property LabelSpacing: Integer read FLabelSpacing write SetLabelSpacing default 2;
  end;

  { TLCDBMaskEdit }
  TLCDBMaskEdit = class(TDBMaskEdit)
   private
     FColor             : TColor;
     FAttributes        : TAttributes;
     FSaveLiterals,
     FValidate,
     FMarked,
     FHilightChanges    : Boolean;
     FOldValue          : String;
     FMaskType          : TMaskType;
     FAlternate         : TAlternableMask;
     FCharForBlanks     : Char;
     FControlMask       : Byte;
     FAlternableShortCut: TShortCut;
     FEditLabel: TBoundLabel;
     FLabelPosition: TLabelPosition;
     FLabelSpacing: Integer;
     procedure SetLabelPosition(const Value: TLabelPosition);
     procedure SetLabelSpacing(const Value: Integer);
     procedure SetAttributes(const AValue: TAttributes);
     procedure SetMask(const AValue: TMaskType);
     procedure SetValidate(const AValue: Boolean);
   protected
     procedure SetParent(AParent: TWinControl); override;
     procedure Notification(AComponent: TComponent; Operation: TOperation); override;
     procedure SetName(const Value: TComponentName); override;
     procedure CMVisiblechanged(var Message: TLMessage);
     message CM_VISIBLECHANGED;
     procedure CMEnabledchanged(var Message: TLMessage);
     message CM_ENABLEDCHANGED;
     procedure CMBidimodechanged(var Message: TLMessage);
     message CM_BIDIMODECHANGED;
     procedure DoEnter; override;
     procedure DoExit; override;
     procedure KeyPress(var Key: Char); override;
     procedure Change; override;
     procedure KeyUp(var Key: Word; Shift: TShiftState); override;
   public
     constructor Create(AOwner: TComponent); override;
   published
     property Attributes: TAttributes
     read FAttributes write SetAttributes;
     property HilightChanges: Boolean read FHilightChanges write FHilightChanges default True;
     property Validate: Boolean
     read FValidate write SetValidate default True;
     property SaveLiterals: Boolean
     read FSaveLiterals write FSaveLiterals default False;
     property MaskType: TMaskType read FMaskType write SetMask;
     property AlternableMasks: TAlternableMask  read FAlternate write FAlternate;
     property CharForBlanks: Char read FCharForBlanks write FCharForBlanks;
     property AlternableShortCut: TShortCut read FAlternableShortCut write FAlternableShortCut;
     procedure SetBounds(ALeft: Integer; ATop: Integer; AWidth: Integer; AHeight: Integer); override;
     procedure SetupInternalLabel;
     property EditLabel: TBoundLabel read FEditLabel;
     property LabelPosition: TLabelPosition read FLabelPosition write SetLabelPosition;
     property LabelSpacing: Integer read FLabelSpacing write SetLabelSpacing default 2;
   end;

  procedure Register;

implementation

{$I lcedit.inc}
{$I lcmaskedit.inc}
{$I lceditbutton.inc}
{$I lcdateedit.inc}
{$I lccalcedit.inc}
{$I lcspinedit.inc}
{$I lcfloatspinedit.inc}
{$I lcnumericedit.inc}
{$I lcmemo.inc}
{$I lccombobox.inc}
{$I lclistbox.inc}

procedure Register;
begin
  RegisterComponents('Label Controls', [TLCEdit, TLCMaskEdit, TLCEditButton,
    TLCDateEdit, TLCCalcEdit, TLCSpinEdit, TLCFloatSpinEdit, TLCNumericEdit,
    TLCMemo, TLCCombobox, TLCListbox, TLCDBEdit, TLCDBMaskEdit, TLCDBEditButton,
    TLCDBDateEdit, TLCDBCalcEdit, TLCDBSpinEdit, TLCDBFloatSpinEdit,
    TLCDBNumericEdit, TLCDBMemo, TLCDBCombobox, TLCDBListbox, TLCDBLookupCombo,
    TLCDBLookupList]);
end;

initialization
  {$I ./icons/labelcontrols.lrs}

end.

