REM set OPT=/GS- /TP /analyze- /W3 /Zc:wchar_t /I"../" /Gm- /O1 /Ob1 /Fd".\bin\release\" /Zc:inline /fp:fast /Zp1 /D "WINDOWS" /D "A32BITS" /D "SIMD" /D "NDEBUG" /D "_CRT_SECURE_NO_WARNINGS" /D "_VC80_UPGRADE=0x0600" /errorReport:prompt /GF- /WX- /Zc:forScope /Gz /Oy /Oi /MT /Fa".\bin\release\" /nologo /Zl /Fo".\bin\release\" /FAs /Os /Fp".\bin/Release/Leviathan.pch"
set OPT=/GS- /TP /analyze- /W3 /Zc:wchar_t /I"../" /Gm- /O1 /Ob1 /D "WINDOWS" -c /D "A32BITS" /D "SIMD" /D "NDEBUG" /D "_CRT_SECURE_NO_WARNINGS" /D "_VC80_UPGRADE=0x0600" /errorReport:prompt /GF- /WX- /Zc:forScope /Gz /Oy /Oi /MT
set LINK_OPT=/OUT:".\bin\release\Leviathan 2.0.exe" /MANIFEST:NO /PDB:".\bin\release\Leviathan 2.0.pdb" /DYNAMICBASE:NO "opengl32.lib" "winmm.lib" "src/4klang/4klang.obj" "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib" "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib" "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib" /MACHINE:X86 /ENTRY:"entrypoint" /SAFESEH /INCREMENTAL:NO /PGD:".\bin\release\Leviathan 2.0.pgd" /SUBSYSTEM:WINDOWS /MANIFESTUAC:NO /ManifestFile:".\bin\release\Leviathan 2.0.exe.intermediate.manifest" /ERRORREPORT:PROMPT /NOLOGO /NODEFAULTLIB /TLBID:1 
set CRINKLER_OPT=/CRINKLER  /RANGE:opengl32 /HASHTRIES:100 /COMPMODE:FAST /ORDERTRIES:100 /REPORT:out.html /PROGRESSGUI /HASHSIZE:1000 /UNSAFEIMPORT /UNALIGNCODE /SATURATE /NOINITIALIZERS /TRANSFORM:CALLS /TRUNCATEFLOATS:32 
cl %OPT% src\main.cpp
cl %OPT% src\song.cpp
link main.obj song.obj %LINK_OPT% %CRINKLER_OPT%