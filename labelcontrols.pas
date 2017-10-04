{ This file was automatically created by Lazarus. Do not edit!
  This source is only used to compile and install the package.
 }

unit labelcontrols;

interface

uses
  LCControls, LazarusPackageIntf;

implementation

procedure Register;
begin
  RegisterUnit('LCControls', @LCControls.Register);
end;

initialization
  RegisterPackage('labelcontrols', @Register);
end.
