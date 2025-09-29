[Setup]
AppName=Timer
AppVersion=1.0
DefaultDirName={pf}\Timer
DefaultGroupName=Timer
OutputBaseFilename=TimerInstaller
Compression=lzma
SolidCompression=yes

[Languages]
Name: "italian"; MessagesFile: "compiler:Languages\Italian.isl"

[Files]
; File principale
Source: "Timer.exe"; DestName: "Timer.exe"; DestDir: "{app}"; Flags: ignoreversion

; Config
Source: "config"; DestDir: "{app}"; Flags: ignoreversion

; Librerie nella root
Source: "D3Dcompiler_47.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Qt6Core.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Qt6Gui.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Qt6Network.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Qt6Svg.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "Qt6Widgets.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "opengl32sw.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "libgcc_s_seh-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "libstdc++-6.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "libwinpthread-1.dll"; DestDir: "{app}"; Flags: ignoreversion

; Secondo programma e risorse
Source: "executable\*"; DestDir: "{app}\executable"; Flags: ignoreversion recursesubdirs createallsubdirs

Source: "config"; DestDir: "{userappdata}\Timer"; Flags: ignoreversion

; Plugin Qt
Source: "generic\qtuiotouchplugin.dll"; DestDir: "{app}\generic"; Flags: ignoreversion
Source: "iconengines\qsvgicon.dll"; DestDir: "{app}\iconengines"; Flags: ignoreversion
Source: "imageformats\qgif.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion
Source: "imageformats\qico.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion
Source: "imageformats\qjpeg.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion
Source: "imageformats\qsvg.dll"; DestDir: "{app}\imageformats"; Flags: ignoreversion
Source: "platforms\qwindows.dll"; DestDir: "{app}\platforms"; Flags: ignoreversion
Source: "styles\qmodernwindowsstyle.dll"; DestDir: "{app}\styles"; Flags: ignoreversion
Source: "tls\qcertonlybackend.dll"; DestDir: "{app}\tls"; Flags: ignoreversion
Source: "tls\qschannelbackend.dll"; DestDir: "{app}\tls"; Flags: ignoreversion

; Traduzioni
Source: "translations\*.qm"; DestDir: "{app}\translations"; Flags: ignoreversion

; Lingua italiana della tua app
Source: "Timer1_it_IT.qm"; DestDir: "{app}"; Flags: ignoreversion

[Icons]
Name: "{group}\Timer"; Filename: "{app}\Timer.exe"
Name: "{commondesktop}\Timer"; Filename: "{app}\Timer.exe"; Tasks: desktopicon

[Tasks]
Name: "desktopicon"; Description: "Crea un'icona sul desktop"; GroupDescription: "Icone aggiuntive:"

[Run]
Filename: "{app}\Timer.exe"; Description: "Avvia Timer"; Flags: nowait postinstall skipifsilent
