**What is CSEL(and it's other names... OSEL/..)**

CSEL(Console Skyrim Extension Library) is a Script/Mod framework, it allows for the same thing as SKSE and aims to document the structure differences in the PS4 version of the game and act as a SKSE replacement for the console version of skyrim(and more!).

*Q/A:*

Q: When the game boots with the PRX the graphics are all broken... why?

A: if you are using a PS4 PRO the game detects this and swaps it's resolution, the default supplied in the INI are for non-pros.. to fix this edit iWidth && iHeight && iPitch under [VideoOut] to 3840x2160(iWidth=3840, iHeight=2160, iPitch=3840)

*Note:*

DO NOT EDIT runtime/Version.h THIS WILL BREAK VERSION.exe

Update 1.09 IS REQUIRED for this PRX to function, later down the line ill add support for other versions but as of now it's limited to 1.09.

some SKSE code is used and said code is in it's own header "EXTERNAL/SKSE.h", "source/Helper.h" and is provided inside the static library linked(Trampoline, Relocation and RelocationManager), the plugin system was also based of the SKSE code.

CommonLibSSE was used as a reference for types and names and some code has been used, and it's workspace was also used as a reference.

not all the headers inside source are fully defined/complete, unless there's a "static_assert(sizeof(T) == 0xDEADBEEF)" do not consider it complete or fully accurate.

*NO COPYRIGHT INFRINGEMENT IS INTENDED... PLEASE DON'T HURT ME I BEG :(*