#include <string>
#include <vector>
#include <algorithm>



enum Base
{
    dec = 10,
    hex = 16
};



extern inline std::string VirtualKeysDescription(Base base = Base::dec);



inline char HexDigit(uint16_t value)
{
    return (value < 10 ? 48 : 55) + value;
}



struct VirtualKey
{
    VirtualKey(const std::string &tag,
               const uint8_t value,
               const std::string &comment)
               :
               tag(tag),
               value(value),
               comment(comment)
               {}



    const std::string
        tag;

    const uint8_t
        value;

    const std::string
        comment;



    std::string
        Description(Base base = Base::dec) const;
};



std::string VirtualKey::Description(Base base) const
{
    std::string
        reversed,
        result;

    uint16_t
        handle = this->value;



    result = this->tag.empty() ? "N/A; " : this->tag + "; ";

    switch (base)
    {
        case Base::dec:
        {
            if (handle)
            {
                while (handle)
                {
                    reversed.push_back(48 + handle % 10);
                    handle /= 10;
                }

                std::reverse(reversed.begin(), reversed.end());
            }
            else
            {
                reversed = '0';
            }

            result += reversed;

            break;
        }

        case Base::hex:
        {
            ((result += "0x") += HexDigit(this->value / 16)) += HexDigit(this->value % 16);

            break;
        }
    }

    (result += "; ") += this->comment;

    return result;
}



std::vector<VirtualKey>
    virutalKey =
{
    { "", 0x00, "Undefined" }
   ,{ "VK_LBUTTON", 0x01, "Left mouse button" }
   ,{ "VK_RBUTTON", 0x02, "Right mouse button" }
   ,{ "VK_CANCEL", 0x03, "Control-break processing" }
   ,{ "VK_MBUTTON", 0x04, "Middle mouse button (three-button mouse)" }
   ,{ "VK_XBUTTON1", 0x05, "X1 mouse button" }
   ,{ "VK_XBUTTON2", 0x06, "X2 mouse button" }
   ,{ "-", 0x07, "Undefined" }
   ,{ "VK_BACK", 0x08, "BACKSPACE key" }
   ,{ "VK_TAB", 0x09, "TAB key" }
   ,{ "-", 0x0A, "Reserved" }
   ,{ "-", 0x0B, "Reserved" }
   ,{ "VK_CLEAR", 0x0C, "CLEAR key" }
   ,{ "VK_RETURN", 0x0D, "ENTER key" }
   ,{ "-", 0x0E, "Undefined" }
   ,{ "-", 0x0F, "Undefined" }
   ,{ "VK_SHIFT", 0x10, "SHIFT key" }
   ,{ "VK_CONTROL", 0x11, "CTRL key" }
   ,{ "VK_MENU", 0x12, "ALT key" }
   ,{ "VK_PAUSE", 0x13, "PAUSE key" }
   ,{ "VK_CAPITAL", 0x14, "CAPS LOCK key" }
   ,{ "VK_KANA", 0x15, "IME Kana/Hangul mode / Hanguel mode (maintained for compatibility; use VK_HANGUL)" }
   ,{ "VK_IME_ON", 0x16, "IME On" }
   ,{ "VK_JUNJA", 0x17, "IME Junja mode" }
   ,{ "VK_FINAL", 0x18, "IME final mode" }
   ,{ "VK_HANJA", 0x19, "IME Hanja/Kanji mode" }
   ,{ "VK_IME_OFF", 0x1A, "IME Off" }
   ,{ "VK_ESCAPE", 0x1B, "ESC key" }
   ,{ "VK_CONVERT", 0x1C, "IME convert" }
   ,{ "VK_NONCONVERT", 0x1D, "IME nonconvert" }
   ,{ "VK_ACCEPT", 0x1E, "IME accept" }
   ,{ "VK_MODECHANGE", 0x1F, "IME mode change request" }
   ,{ "VK_SPACE", 0x20, "SPACEBAR" }
   ,{ "VK_PRIOR", 0x21, "PAGE UP key" }
   ,{ "VK_NEXT", 0x22, "PAGE DOWN key" }
   ,{ "VK_END", 0x23, "END key" }
   ,{ "VK_HOME", 0x24, "HOME key" }
   ,{ "VK_LEFT", 0x25, "LEFT ARROW key" }
   ,{ "VK_UP", 0x26, "UP ARROW key" }
   ,{ "VK_RIGHT", 0x27, "RIGHT ARROW key" }
   ,{ "VK_DOWN", 0x28, "DOWN ARROW key" }
   ,{ "VK_SELECT", 0x29, "SELECT key" }
   ,{ "VK_PRINT", 0x2A, "PRINT key" }
   ,{ "VK_EXECUTE", 0x2B, "EXECUTE key" }
   ,{ "VK_SNAPSHOT", 0x2C, "PRINT SCREEN key" }
   ,{ "VK_INSERT", 0x2D, "INS key" }
   ,{ "VK_DELETE", 0x2E, "DEL key" }
   ,{ "VK_HELP", 0x2F, "HELP key" }
   ,{ "", 0x30, "0 key" }
   ,{ "", 0x31, "1 key" }
   ,{ "", 0x32, "2 key" }
   ,{ "", 0x33, "3 key" }
   ,{ "", 0x34, "4 key" }
   ,{ "", 0x35, "5 key" }
   ,{ "", 0x36, "6 key" }
   ,{ "", 0x37, "7 key" }
   ,{ "", 0x38, "8 key" }
   ,{ "", 0x39, "9 key" }
   ,{ "-", 0x3A, "Undefined" }
   ,{ "-", 0x3B, "Undefined" }
   ,{ "-", 0x3C, "Undefined" }
   ,{ "-", 0x3D, "Undefined" }
   ,{ "-", 0x3E, "Undefined" }
   ,{ "-", 0x3F, "Undefined" }
   ,{ "-", 0x40, "Undefined" }
   ,{ "", 0x41, "A key" }
   ,{ "", 0x42, "B key" }
   ,{ "", 0x43, "C key" }
   ,{ "", 0x44, "D key" }
   ,{ "", 0x45, "E key" }
   ,{ "", 0x46, "F key" }
   ,{ "", 0x47, "G key" }
   ,{ "", 0x48, "H key" }
   ,{ "", 0x49, "I key" }
   ,{ "", 0x4A, "J key" }
   ,{ "", 0x4B, "K key" }
   ,{ "", 0x4C, "L key" }
   ,{ "", 0x4D, "M key" }
   ,{ "", 0x4E, "N key" }
   ,{ "", 0x4F, "O key" }
   ,{ "", 0x50, "P key" }
   ,{ "", 0x51, "Q key" }
   ,{ "", 0x52, "R key" }
   ,{ "", 0x53, "S key" }
   ,{ "", 0x54, "T key" }
   ,{ "", 0x55, "U key" }
   ,{ "", 0x56, "V key" }
   ,{ "", 0x57, "W key" }
   ,{ "", 0x58, "X key" }
   ,{ "", 0x59, "Y key" }
   ,{ "", 0x5A, "Z key" }
   ,{ "VK_LWIN", 0x5B, "Left Windows key (Natural keyboard)" }
   ,{ "VK_RWIN", 0x5C, "Right Windows key (Natural keyboard)" }
   ,{ "VK_APPS", 0x5D, "Applications key (Natural keyboard)" }
   ,{ "-", 0x5E, "Reserved" }
   ,{ "VK_SLEEP", 0x5F, "Computer Sleep key" }
   ,{ "VK_NUMPAD0", 0x60, "Numeric keypad 0 key" }
   ,{ "VK_NUMPAD1", 0x61, "Numeric keypad 1 key" }
   ,{ "VK_NUMPAD2", 0x62, "Numeric keypad 2 key" }
   ,{ "VK_NUMPAD3", 0x63, "Numeric keypad 3 key" }
   ,{ "VK_NUMPAD4", 0x64, "Numeric keypad 4 key" }
   ,{ "VK_NUMPAD5", 0x65, "Numeric keypad 5 key" }
   ,{ "VK_NUMPAD6", 0x66, "Numeric keypad 6 key" }
   ,{ "VK_NUMPAD7", 0x67, "Numeric keypad 7 key" }
   ,{ "VK_NUMPAD8", 0x68, "Numeric keypad 8 key" }
   ,{ "VK_NUMPAD9", 0x69, "Numeric keypad 9 key" }
   ,{ "VK_MULTIPLY", 0x6A, "Multiply key" }
   ,{ "VK_ADD", 0x6B, "Add key" }
   ,{ "VK_SEPARATOR", 0x6C, "Separator key" }
   ,{ "VK_SUBTRACT", 0x6D, "Subtract key" }
   ,{ "VK_DECIMAL", 0x6E, "Decimal key" }
   ,{ "VK_DIVIDE", 0x6F, "Divide key" }
   ,{ "VK_F1", 0x70, "F1 key" }
   ,{ "VK_F2", 0x71, "F2 key" }
   ,{ "VK_F3", 0x72, "F3 key" }
   ,{ "VK_F4", 0x73, "F4 key" }
   ,{ "VK_F5", 0x74, "F5 key" }
   ,{ "VK_F6", 0x75, "F6 key" }
   ,{ "VK_F7", 0x76, "F7 key" }
   ,{ "VK_F8", 0x77, "F8 key" }
   ,{ "VK_F9", 0x78, "F9 key" }
   ,{ "VK_F10", 0x79, "F10 key" }
   ,{ "VK_F11", 0x7A, "F11 key" }
   ,{ "VK_F12", 0x7B, "F12 key" }
   ,{ "VK_F13", 0x7C, "F13 key" }
   ,{ "VK_F14", 0x7D, "F14 key" }
   ,{ "VK_F15", 0x7E, "F15 key" }
   ,{ "VK_F16", 0x7F, "F16 key" }
   ,{ "VK_F17", 0x80, "F17 key" }
   ,{ "VK_F18", 0x81, "F18 key" }
   ,{ "VK_F19", 0x82, "F19 key" }
   ,{ "VK_F20", 0x83, "F20 key" }
   ,{ "VK_F21", 0x84, "F21 key" }
   ,{ "VK_F22", 0x85, "F22 key" }
   ,{ "VK_F23", 0x86, "F23 key" }
   ,{ "VK_F24", 0x87, "F24 key" }
   ,{ "-", 0x88, "Unassigned" }
   ,{ "-", 0x89, "Unassigned" }
   ,{ "-", 0x8A, "Unassigned" }
   ,{ "-", 0x8B, "Unassigned" }
   ,{ "-", 0x8C, "Unassigned" }
   ,{ "-", 0x8D, "Unassigned" }
   ,{ "-", 0x8E, "Unassigned" }
   ,{ "-", 0x8F, "Unassigned" }
   ,{ "VK_NUMLOCK", 0x90, "NUM LOCK key" }
   ,{ "VK_SCROLL", 0x91, "SCROLL LOCK key" }
   ,{ "", 0x92, "OEM specific" }
   ,{ "", 0x93, "OEM specific" }
   ,{ "", 0x94, "OEM specific" }
   ,{ "", 0x95, "OEM specific" }
   ,{ "", 0x96, "OEM specific" }
   ,{ "-", 0x97, "Unassigned" }
   ,{ "-", 0x98, "Unassigned" }
   ,{ "-", 0x99, "Unassigned" }
   ,{ "-", 0x9A, "Unassigned" }
   ,{ "-", 0x9B, "Unassigned" }
   ,{ "-", 0x9C, "Unassigned" }
   ,{ "-", 0x9D, "Unassigned" }
   ,{ "-", 0x9E, "Unassigned" }
   ,{ "-", 0x9F, "Unassigned" }
   ,{ "VK_LSHIFT", 0xA0, "Left SHIFT key" }
   ,{ "VK_RSHIFT", 0xA1, "Right SHIFT key" }
   ,{ "VK_LCONTROL", 0xA2, "Left CONTROL key" }
   ,{ "VK_RCONTROL", 0xA3, "Right CONTROL key" }
   ,{ "VK_LMENU", 0xA4, "Left ALT key" }
   ,{ "VK_RMENU", 0xA5, "Right ALT key" }
   ,{ "VK_BROWSER_BACK", 0xA6, "Browser Back key" }
   ,{ "VK_BROWSER_FORWARD", 0xA7, "Browser Forward key" }
   ,{ "VK_BROWSER_REFRESH", 0xA8, "Browser Refresh key" }
   ,{ "VK_BROWSER_STOP", 0xA9, "Browser Stop key" }
   ,{ "VK_BROWSER_SEARCH", 0xAA, "Browser Search key" }
   ,{ "VK_BROWSER_FAVORITES", 0xAB, "Browser Favorites key" }
   ,{ "VK_BROWSER_HOME", 0xAC, "Browser Start and Home key" }
   ,{ "VK_VOLUME_MUTE", 0xAD, "Volume Mute key" }
   ,{ "VK_VOLUME_DOWN", 0xAE, "Volume Down key" }
   ,{ "VK_VOLUME_UP", 0xAF, "Volume Up key" }
   ,{ "VK_MEDIA_NEXT_TRACK", 0xB0, "Next Track key" }
   ,{ "VK_MEDIA_PREV_TRACK", 0xB1, "Previous Track key" }
   ,{ "VK_MEDIA_STOP", 0xB2, "Stop Media key" }
   ,{ "VK_MEDIA_PLAY_PAUSE", 0xB3, "Play/Pause Media key" }
   ,{ "VK_LAUNCH_MAIL", 0xB4, "Start Mail key" }
   ,{ "VK_LAUNCH_MEDIA_SELECT", 0xB5, "Select Media key" }
   ,{ "VK_LAUNCH_APP1", 0xB6, "Start Application 1 key" }
   ,{ "VK_LAUNCH_APP2", 0xB7, "Start Application 2 key" }
   ,{ "-", 0xB8, "Reserved" }
   ,{ "-", 0xB9, "Reserved" }
   ,{ "VK_OEM_1", 0xBA, "Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the ';:' key" }
   ,{ "VK_OEM_PLUS", 0xBB, "For any country/region, the '+' key" }
   ,{ "VK_OEM_COMMA", 0xBC, "For any country/region, the ',' key" }
   ,{ "VK_OEM_MINUS", 0xBD, "For any country/region, the '-' key" }
   ,{ "VK_OEM_PERIOD", 0xBE, "For any country/region, the '.' key" }
   ,{ "VK_OEM_2", 0xBF, "Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '/?' key" }
   ,{ "VK_OEM_3", 0xC0, "Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '`~' key" }
   ,{ "-", 0xC1, "Reserved" }
   ,{ "-", 0xC2, "Reserved" }
   ,{ "-", 0xC3, "Reserved" }
   ,{ "-", 0xC4, "Reserved" }
   ,{ "-", 0xC5, "Reserved" }
   ,{ "-", 0xC6, "Reserved" }
   ,{ "-", 0xC7, "Reserved" }
   ,{ "-", 0xC8, "Reserved" }
   ,{ "-", 0xC9, "Reserved" }
   ,{ "-", 0xCA, "Reserved" }
   ,{ "-", 0xCB, "Reserved" }
   ,{ "-", 0xCC, "Reserved" }
   ,{ "-", 0xCD, "Reserved" }
   ,{ "-", 0xCE, "Reserved" }
   ,{ "-", 0xCF, "Reserved" }
   ,{ "-", 0xD0, "Reserved" }
   ,{ "-", 0xD1, "Reserved" }
   ,{ "-", 0xD2, "Reserved" }
   ,{ "-", 0xD3, "Reserved" }
   ,{ "-", 0xD4, "Reserved" }
   ,{ "-", 0xD5, "Reserved" }
   ,{ "-", 0xD6, "Reserved" }
   ,{ "-", 0xD7, "Reserved" }
   ,{ "-", 0xD8, "Unassigned" }
   ,{ "-", 0xD9, "Unassigned" }
   ,{ "-", 0xDA, "Unassigned" }
   ,{ "VK_OEM_4", 0xDB, "Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '[{' key" }
   ,{ "VK_OEM_5", 0xDC, "Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the '\\|' key" }
   ,{ "VK_OEM_6", 0xDD, "Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the ']}' key" }
   ,{ "VK_OEM_7", 0xDE, "Used for miscellaneous characters; it can vary by keyboard. For the US standard keyboard, the 'single-quote/double-quote' key" }
   ,{ "VK_OEM_8", 0xDF, "Used for miscellaneous characters; it can vary by keyboard." }
   ,{ "-", 0xE0, "Reserved" }
   ,{ "", 0xE1, "OEM specific" }
   ,{ "VK_OEM_102", 0xE2, "The <> keys on the US standard keyboard, or the \\| key on the non-US 102-key keyboard" }
   ,{ "", 0xE3, "OEM specific" }
   ,{ "", 0xE4, "OEM specific" }
   ,{ "VK_PROCESSKEY", 0xE5, "IME PROCESS key" }
   ,{ "", 0xE6, "OEM specific" }
   ,{ "VK_PACKET", 0xE7, "Used to pass Unicode characters as if they were keystrokes. The VK_PACKET key is the low word of a 32-bit Virtual Key value used for non-keyboard input methods. For more information, see Remark in KEYBDINPUT, SendInput, WM_KEYDOWN, and WM_KEYUP" }
   ,{ "-", 0xE8, "Unassigned" }
   ,{ "", 0xE9, "OEM specific" }
   ,{ "", 0xEA, "OEM specific" }
   ,{ "", 0xEB, "OEM specific" }
   ,{ "", 0xEC, "OEM specific" }
   ,{ "", 0xED, "OEM specific" }
   ,{ "", 0xEE, "OEM specific" }
   ,{ "", 0xEF, "OEM specific" }
   ,{ "", 0xF0, "OEM specific" }
   ,{ "", 0xF1, "OEM specific" }
   ,{ "", 0xF2, "OEM specific" }
   ,{ "", 0xF3, "OEM specific" }
   ,{ "", 0xF4, "OEM specific" }
   ,{ "", 0xF5, "OEM specific" }
   ,{ "VK_ATTN", 0xF6, "Attn key" }
   ,{ "VK_CRSEL", 0xF7, "CrSel key" }
   ,{ "VK_EXSEL", 0xF8, "ExSel key" }
   ,{ "VK_EREOF", 0xF9, "Erase EOF key" }
   ,{ "VK_PLAY", 0xFA, "Play key" }
   ,{ "VK_ZOOM", 0xFB, "Zoom key" }
   ,{ "VK_NONAME", 0xFC, "Reserved" }
   ,{ "VK_PA1", 0xFD, "PA1 key" }
   ,{ "VK_OEM_CLEAR", 0xFE, "Clear key" }
   ,{ "", 0xFF, "Undefined" }
};



inline std::string VirtualKeysDescription(Base base)
{
    std::string
        result;



    for (const VirtualKey &parse : virutalKey)
    {
        result += parse.Description(base) + '\n';
    }



    return result;
}



#define VIRTUAL_A_KEY   0x41
#define VIRTUAL_D_KEY   0x44
#define VIRTUAL_G_KEY   0x47
#define VIRTUAL_V_KEY   0x56
#define VIRTUAL_X_KEY   0x58
#define VIRTUAL_0_KEY   0x30
#define VIRTUAL_1_KEY   0x31
#define VIRTUAL_2_KEY   0x32
#define VIRTUAL_3_KEY   0x33
#define VIRTUAL_4_KEY   0x34
#define VIRTUAL_5_KEY   0x35
#define VIRTUAL_6_KEY   0x36
#define VIRTUAL_7_KEY   0x37
#define VIRTUAL_8_KEY   0x38
#define VIRTUAL_9_KEY   0x39
#define VIRTUAL_ALT_KEY VK_MENU

#define KEY_PRESS            0
#define KEY_RELEASE          KEYEVENTF_KEYUP
//#define KEY_PRESS            KEYEVENTF_SCANCODE
//#define KEY_RELEASE          KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP
#define LEFT_CLICK_PRESS     MOUSEEVENTF_LEFTDOWN
#define LEFT_CLICK_RELEASE   MOUSEEVENTF_LEFTUP
#define RIGHT_CLICK_PRESS    MOUSEEVENTF_RIGHTDOWN
#define RIGHT_CLICK_RELEASE  MOUSEEVENTF_RIGHTUP
#define MIDDLE_CLICK_PRESS   MOUSEEVENTF_MIDDLEDOWN
#define MIDDLE_CLICK_RELEASE MOUSEEVENTF_MIDDLEUP

#define MOUSE_KEY VK_LBUTTON: case VK_RBUTTON: case VK_MBUTTON: case VK_XBUTTON1: case VK_XBUTTON2



inline uint8_t Complement(uint8_t key)
{
    static uint8_t
        result;

    switch (key)
    {
        case LEFT_CLICK_PRESS:
        {
            result = LEFT_CLICK_RELEASE;
            break;
        }

        case LEFT_CLICK_RELEASE:
        {
            result = LEFT_CLICK_PRESS;
            break;
        }

        case RIGHT_CLICK_PRESS:
        {
            result = RIGHT_CLICK_RELEASE;
            break;
        }

        case RIGHT_CLICK_RELEASE:
        {
            result = RIGHT_CLICK_PRESS;
            break;
        }

        case MIDDLE_CLICK_PRESS:
        {
            result = MIDDLE_CLICK_RELEASE;
            break;
        }

        case MIDDLE_CLICK_RELEASE:
        {
            result = MIDDLE_CLICK_PRESS;
            break;
        }
    }

    return result;
}

void PrepareInputKeyboard(INPUT &input)
{
    ZeroMemory(&input, sizeof(input));

    input.type           = INPUT_KEYBOARD;
    input.ki.wScan       = 0;
    input.ki.time        = 0;
    input.ki.dwExtraInfo = 0;
}

void SetKey(INPUT &input, WORD key)
{
    input.ki.wVk = key;
}

void KeyState(INPUT &input, DWORD keyState)
{
    input.ki.dwFlags = keyState;
}

void PrepareInputMouse(INPUT &input)
{
    ZeroMemory(&input, sizeof(input));

    input.type = INPUT_MOUSE;
}

DWORD State(uint8_t key)
{
    DWORD
        state;

    switch (key)
    {
        case VK_LBUTTON:
        {
            state = LEFT_CLICK_PRESS;

            break;
        }

        case VK_RBUTTON:
        {
            state = RIGHT_CLICK_PRESS;

            break;
        }

        case VK_MBUTTON:
        {
            state = MIDDLE_CLICK_PRESS;

            break;
        }
    }

    return state;
}

void MouseState(INPUT &input, DWORD mouseState)
{
    input.mi.dwFlags = mouseState;
}

void ConsoleCursor(SHORT xCursor, SHORT yCursor)
{
    static HANDLE
        consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    static COORD
        cursorCoordinates;

    cursorCoordinates.X = xCursor;
    cursorCoordinates.Y = yCursor;

    SetConsoleCursorPosition(consoleHandle,
                             cursorCoordinates);
}

int HighOrder(int value)
{
    return value >> 15;
}

int LowOrder(int value)
{
    return value & 1;
}

SHORT PressingKey(int targetKey)
{
    /*
    In the case of the SHORT GetKeyState(int) function, the return value works this way (according to docs.microsoft.com):
    "If the high-order bit is 1, the key is down; otherwise, it is up."
    */

    return HighOrder(GetKeyState(targetKey));
}

void SetupKeyInputHold(INPUT &input, uint8_t key)
{
    PrepareInputKeyboard(input);

    KeyState(input, KEY_PRESS);

    SetKey(input, key);
}

void SetupKeyInputRelease(INPUT &input, uint8_t key)
{
    PrepareInputKeyboard(input);

    KeyState(input, KEY_RELEASE);

    SetKey(input, key);
}

void SetupMouseInputHold(INPUT &input, uint8_t key)
{
    PrepareInputMouse(input);

    MouseState(input, State(key));
}

void SetupMouseInputRelease(INPUT &input, uint8_t key)
{
    PrepareInputMouse(input);

    MouseState(input, Complement(State(key)));
}

std::string CheckMouse(const INPUT *input)
{
    static std::string
        result;

    switch (input->mi.dwFlags)
    {
        case LEFT_CLICK_PRESS:
        {
            result = "LEFT_CLICK_PRESS";
            break;
        }

        case LEFT_CLICK_RELEASE:
        {
            result = "LEFT_CLICK_RELEASE";
            break;
        }

        case RIGHT_CLICK_PRESS:
        {
            result = "RIGHT_CLICK_PRESS";
            break;
        }

        case RIGHT_CLICK_RELEASE:
        {
            result = "RIGHT_CLICK_RELEASE";
            break;
        }

        case MIDDLE_CLICK_PRESS:
        {
            result = "MIDDLE_CLICK_PRESS";
            break;
        }

        case MIDDLE_CLICK_RELEASE:
        {
            result = "MIDDLE_CLICK_RELEASE";
            break;
        }
    }

    return result;
}

#ifndef PrintInstructions
#define PrintInstructions(base)\
std::string instructions;\
(instructions += "\n\nLocalize crafting grid to place the bucket:\n") += virutalKey[craftGridLocalize].Description(base);\
(instructions += "\n\nLocalize crafting result where fresh water is gathered:\n") += virutalKey[craftResultLocalize].Description(base);\
(instructions += "\n\nActivate script:\n") += virutalKey[activateKey].Description(base);\
std::cout << instructions;
#endif // PrintInstructions



namespace VK
{
    clock_t
        holdTimer = 24;

    std::vector<INPUT>
        inputHold,
        inputRelease;

    bool
        pressing[256],
        pressed [256];

    class Initialization
    {
    public:
        Initialization()
        {
            VK::inputHold   .resize(256);
            VK::inputRelease.resize(256);

            for (int key = 0; key < 256; ++key)
            {
                switch (key)
                {
                    case MOUSE_KEY:
                    {
                        SetupMouseInputHold(VK::inputHold[key], key);
                        SetupMouseInputRelease(VK::inputRelease[key], key);

                        break;
                    }

                    default:
                    {
                        SetupKeyInputHold(VK::inputHold[key], key);
                        SetupKeyInputRelease(VK::inputRelease[key], key);

                        break;
                    }
                }
            }



            ZeroMemory(VK::pressing, sizeof(VK::pressing) / sizeof(VK::pressing[0]));



            SetWindowPos(GetConsoleWindow()
                        ,0
                        ,3 * GetSystemMetrics(SM_CXSCREEN) / 2 - 320
                        ,GetSystemMetrics(SM_CYSCREEN) / 2 - 240
                        ,0
                        ,0
                        ,SWP_NOSIZE
                        );
        }
    } _Initialization;
}



inline bool Holding(uint8_t key)
{
    return VK::pressing[key];
}

inline bool Tapped(uint8_t key)
{
    return VK::pressing[key] && !VK::pressed[key];
}

inline void GetAllKeyStatus()
{
    CopyMemory(VK::pressed, VK::pressing, sizeof(VK::pressing) / sizeof(VK::pressing[0]));

    for (int unsigned index = 0; index < 256; index++)
    {
        if (PressingKey(index))
        {
            VK::pressing[index] = true;
        }
        else
        {
            VK::pressing[index] = false;
        }
    }
}

inline void Hold(uint8_t key)
{
    SendInput(1, &VK::inputHold[key], sizeof(INPUT));
}

inline void Release(uint8_t key)
{
    SendInput(1, &VK::inputRelease[key], sizeof(INPUT));
}

inline void Press(uint8_t key)
{
    Hold(key);
    Sleep(VK::holdTimer);
    Release(key);
}



































