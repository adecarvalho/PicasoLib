
/**
* PicasoSerial Lib
* for LibGfxArduino
* A Decarvalho
* 11 mars 2015
*/
#ifndef Picaso_Serial_h
#define Picaso_Serial_h

#include "Arduino.h" // for Arduino 1.0
#include "Picaso_Const.h"

//--------------
//TouchEvent
//--------------
enum TouchEvent
{
    EVENT_NO_ACTIVITY=0x0000,
    EVENT_PRESSED=0x0001,
    EVENT_RELEASED=0x0002,
    EVENT_MOVE=0x0003
};
//
//---------------------------------
//
struct GraphicMessage{
word event;
word objetId;
word posiX;
word posiY;
};
//------------
// the states
//------------
enum State
{
    //widget
    BUTTON_STATE_PRESSED=1,
    BUTTON_STATE_RELEASED,
//
    LED_STATE_ON,
    LED_STATE_OFF,
//
    SWITCHER_STATE_ON,
    SWITCHER_STATE_OFF,
//
    SLIDER_STATE_MOVE,
    SLIDER_STATE_RELEASED,
//
    SCALER_STATE_PRESSED_UP,
    SCALER_STATE_PRESSED_DOWN,
    SCALER_STATE_RELEASED,
    
    STATE_ON,
    STATE_OFF
};
//---------
// the Font
//---------
enum Font
{
  FONT1=0x0000,  //5x7
  FONT2=0x0001,  //8x8
  FONT3=0x0002  //8x12
};
//-------------
//the Color
//-------------
enum Color
{
    ALICEBLUE=0xF7DF,ANTIQUEWHITE=0xFF5A,AQUA=0x07FF,
    AQUAMARINE=0x7FFA,AZURE=0xF7FF,
    BEIGE=0xF7BB,BISQUE=0xFF38,BLACK=0x0000,
    BLANCHEDALMOND=0xFF59,BLUE=0x001F,BLUEVIOLET=0x895C,
    BROWN=0xA145,BURLYWOOD=0xDDD0,
    CADETBLUE=0x5CF4,CHARTREUSE=0x7FE0,CHOCOLATE=0xD343,
    CORAL=0xFBEA,CORNFLOWERBLUE=0x64BD,
    CORNSILK=0xFFDB,CRIMSON=0xD8A7,CYAN=0x07FF,
    DARKBLUE=0x0011,DARKCYAN=0x0451,
    DARKGOLDENROD=0xBC21,DARKGRAY=0xAD55,DARKGREEN=0x0320,
    DARKKHAKI=0xBDAD,DARKMAGENTA=0x8811,
    DARKOLIVEGREEN=0x5345,DARKORANGE=0xFC60,
    DARKORCHID=0x9999,DARKRED=0x8800,
    DARKSALMON=0xECAF,DARKSEAGREEN=0x8DF1,
    DARKSLATEBLUE=0x49F1,DARKSLATEGRAY=0x2A69,
    DARKTURQUOISE=0x067A,DARKVIOLET=0x901A,
    DEEPPINK=0xF8B2,DEEPSKYBLUE=0x05FF,
    DIMGRAY=0x6B4D,DODGERBLUE=0x1C9F,
    FIREBRICK=0xB104,FLORALWHITE=0xFFDE,
    FORESTGREEN=0x2444,FUCHSIA=0xF81F,
    GAINSBORO=0xDEFB,GHOSTWHITE=0xFFDF,
    GOLD=0xFEA0,GOLDENROD=0xDD24,
    GRAY=0x8410,GREEN=0x0400,
    GREENYELLOW=0xAFE5,HONEYDEW=0xF7FE,
    HOTPINK=0xFB56,INDIANRED=0xCAEB,
    INDIGO=0x4810,IVORY=0xFFFE,
    KHAKI=0xF731,LAVENDER=0xE73F,
    LAVENDERBLUSH=0xFF9E,LAWNGREEN=0x7FE0,
    LEMONCHIFFON=0xFFD9,LIGHTBLUE=0xAEDC,
    LIGHTCORAL=0xF410,LIGHTCYAN=0xE7FF,
    LIGHTGOLD=0xFFDA,LIGHTGREEN=0x9772,
    LIGHTGREY=0xD69A,LIGHTPINK=0xFDB8,
    LIGHTSALMON=0xFD0F,LIGHTSEAGREEN=0x2595,
    LIGHTSKYBLUE=0x867F,LIGHTSLATEGRAY=0x7453,
    LIGHTSTEELBLUE=0xB63B,LIGHTYELLOW=0xFFFC,
    LIME=0x07E0,LIMEGREEN=0x3666,
    LINEN=0xFF9C,MAGENTA=0xF81F,
    MAROON=0x8000,MEDIUMAQUAMARINE=0x6675,
    MEDIUMBLUE=0x0019,MEDIUMORCHID=0xBABA,
    MEDIUMPURPLE=0x939B,MEDIUMSEAGREEN=0x3D8E,
    MEDIUMSLATEBLUE=0x7B5D,MEDIUMSPRINGGREEN=0x07D3,
    MEDIUMTURQUOISE=0x4E99,MEDIUMVIOLETRED=0xC0B0,
    MIDNIGHTBLUE=0x18CE,MINTCREAM=0xF7FF,
    MISTYROSE=0xFF3C,MOCCASIN=0xFF36,
    NAVY=0x0010,OLDLACE=0xFFBC,
    OLIVEDRAB=0x6C64,ORANGE=0xFD20,
    ORANGERED=0xFA20,ORCHID=0xDB9A,
    PALEGOLDENROD=0xEF55,PALEGREEN=0x9FD3,
    PALETURQUOISE=0xAF7D,PALEVIOLETRED=0xDB92,
    PAPAYAWHIP=0xFF7A,PEACHPUFF=0xFED7,
    PERU=0xCC27,PINKY=0xFE19,
    PLUM=0xDD1B,POWDERBLUE=0xB71C,
    PURPLE=0x8010,RED=0xF800,
    ROSYBROWN=0xBC71,ROYALBLUE=0x435C,
    SADDLEBROWN=0x8A22,SALMON=0xFC0E,
    SANDYBROWN=0xF52C,SEAGREEN=0x2C4A,
    SEASHELL=0xFFBD,SIENNA=0xA285,
    SILVER=0xC618,SKYBLUE=0x867D,
    SLATEBLUE=0x6AD9,SLATEGRAY=0x7412,
    SNOW=0xFFDF,SPRINGGREEN=0x07EF,
    STEELBLUE=0x4416,TAN=0xD5B1,
    TEAL=0x0410,THISTLE=0xDDFB,
    TOMATO=0xFB08,TURQUOISE=0x471A,
    VIOLET=0xEC1D,WHEAT=0xF6F6,
    WHITE=0xFFFF,WHITESMOKE=0xF7BE,
    YELLOW=0xFFE0,YELLOWGREEN=0x9E66
};
//--------------------------------------------
enum WIDGET_TYPE{
    OBJ_BUTTON=1,
    OBJ_LED,
    OBJ_LABEL,
    OBJ_SCALER,
    OBJ_SLIDER,
    OBJ_SWITCHER,
    OBJ_DIGIT_LED,
    OBJ_DIGIT_3_LED,
	OBJ_DIGIT_4_LED,
	OBJ_PANEL,
    OBJ_NONE
};
//--------------------------------------------
class PicasoSerial
{
public:
    PicasoSerial(Stream * virtualPort,byte pinReset=2);

    //Compound 4D Routines
    word bus_In();
    void bus_Out(word Bits);
    word bus_Read();
    void bus_Set(word IOMap);
    void bus_Write(word Bits);
    word charheight(char  TestChar);
    word charwidth(char  TestChar);
    word file_Close(word  Handle);
    word file_Count(char *  Filename);
    word file_Dir(char *  Filename);
    word file_Erase(char *  Filename);
    word file_Error();
    word file_Exec(char *  Filename, word  ArgCount, t4DWordArray  Args);
    word file_Exists(char *  Filename);
    word file_FindFirst(char *  Filename);
    word file_FindNext();
    char file_GetC(word  Handle);
    word file_GetS(char *  StringIn, word  Size, word  Handle);
    word file_GetW(word  Handle);
    word file_Image(word  X, word  Y, word  Handle);
    word file_Index(word  Handle, word  HiSize, word  LoSize, word  Recordnum);
    word file_LoadFunction(char *  Filename);
    word file_LoadImageControl(char *  Datname, char *  GCIName, word  Mode);
    word file_Mount();
    word file_Open(char *  Filename, char  Mode);
    word file_PlayWAV(char *  Filename);
    word file_PutC(char  Character, word  Handle);
    word file_PutS(char *  StringOut, word  Handle);
    word file_PutW(word  Word, word  Handle);
    word file_Read(t4DByteArray  Data, word  Size, word  Handle);
    word file_Rewind(word  Handle);
    word file_Run(char *  Filename, word  ArgCount, t4DWordArray  Args);
    word file_ScreenCapture(word  X, word  Y, word  Width, word  Height, word  Handle);
    word file_Seek(word  Handle, word  HiWord, word  LoWord);
    word file_Size(word  Handle, word *  HiWord, word *  LoWord);
    word file_Tell(word  Handle, word *  HiWord, word *  LoWord);
    void file_Unmount();
    word file_Write(word  Size, t4DByteArray  Source, word  Handle);
    //
    word gfx_BevelShadow(word  Value);
    word gfx_BevelWidth(word  Value);
    word gfx_BGcolour(word  Color);
    void gfx_Button(word  Up, word  x, word  y, word  buttonColour, word  txtColour, word  font, word  txtWidth, word  txtHeight, char *   text);
    void gfx_ChangeColour(word  OldColor, word  NewColor);
    void gfx_Circle(word  X, word  Y, word  Radius, word  Color);
    void gfx_CircleFilled(word  X, word  Y, word  Radius, word  Color);
    void gfx_Clipping(word  OnOff);
    void gfx_ClipWindow(word  X1, word  Y1, word  X2, word  Y2);
    void gfx_Cls();
    word gfx_Contrast(word  Contrast);
    void gfx_Ellipse(word  X, word  Y, word  Xrad, word  Yrad, word  Color);
    void gfx_EllipseFilled(word  X, word  Y, word  Xrad, word  Yrad, word  Color);
    word gfx_FrameDelay(word  Msec);
    word gfx_Get(word  Mode);
    word gfx_GetPixel(word  X, word  Y);
    void gfx_Line(word  X1, word  Y1, word  X2, word  Y2, word  Color);
    word gfx_LinePattern(word  Pattern);
    void gfx_LineTo(word  X, word  Y);
    void gfx_MoveTo(word  X, word  Y);
    word gfx_Orbit(word  Angle, word  Distance, word *  Xdest, word *  Ydest);
    word gfx_OutlineColour(word  Color);
    void gfx_Panel(word  Raised, word  X, word  Y, word  Width, word  Height, word  Color);
    void gfx_Polygon(word  n, t4DWordArray  Xvalues, t4DWordArray  Yvalues, word  Color);
    void gfx_PolygonFilled(word  n, t4DWordArray  Xvalues, t4DWordArray  Yvalues, word  Color);
    void gfx_Polyline(word  n, t4DWordArray  Xvalues, t4DWordArray  Yvalues, word  Color);
    void gfx_PutPixel(word  X, word  Y, word  Color);
    void gfx_Rectangle(word  X1, word  Y1, word  X2, word  Y2, word  Color);
    void gfx_RectangleFilled(word  X1, word  Y1, word  X2, word  Y2, word  Color);
    void gfx_ScreenCopyPaste(word  Xs, word  Ys, word  Xd, word  Yd, word  Width, word  Height);
    word gfx_ScreenMode(word  ScreenMode);
    void gfx_Set(word  Func, word  Value);
    void gfx_SetClipRegion();
    word gfx_Slider(word  Mode, word  X1, word  Y1, word  X2, word  Y2, word  Color, word  Scale, word  Value);
    word gfx_Transparency(word  OnOff);
    word gfx_TransparentColour(word  Color);
    void gfx_Triangle(word  X1, word  Y1, word  X2, word  Y2, word  X3, word  Y3, word  Color);
    void gfx_TriangleFilled(word  X1, word  Y1, word  X2, word  Y2, word  X3, word  Y3, word  Color);
    //
    word img_ClearAttributes(word  Handle, word  Index, word  Value);
    word img_Darken(word  Handle, word  Index);
    word img_Disable(word  Handle, word  Index);
    word img_Enable(word  Handle, word  Index);
    word img_GetWord(word  Handle, word  Index, word  Offset );
    word img_Lighten(word  Handle, word  Index);
    word img_SetAttributes(word  Handle, word  Index, word  Value);
    word img_SetPosition(word  Handle, word  Index, word  Xpos, word  Ypos);
    word img_SetWord(word  Handle, word  Index, word  Offset , word  Word);
    word img_Show(word  Handle, word  Index);
    word img_Touched(word  Handle, word  Index);
    word media_Flush();
    void media_Image(word  X, word  Y);
    word media_Init();
    word media_RdSector(t4DSector  SectorIn);
    word media_ReadByte();
    word media_ReadWord();
    void media_SetAdd(word  HiWord, word  LoWord);
    void media_SetSector(word  HiWord, word  LoWord);
    void media_Video(word  X, word  Y);
    void media_VideoFrame(word  X, word  Y, word  Framenumber);
    word media_WriteByte(word  Byte);
    word media_WriteWord(word  Word);
    word media_WrSector(t4DSector  SectorOut);
    word mem_Free(word  Handle);
    word mem_Heap();
    word pin_HI(word Pin);
    word pin_LO(word Pin);
    word pin_Read(word Pin);
    word pin_Set(word Mode, word Pin);
    void putCH(word  WordChar);
    word putstr(char *  InString);
    void snd_BufSize(word  Bufsize);
    void snd_Continue();
    void snd_Pause();
    word snd_Pitch(word  Pitch);
    word snd_Playing();
    void snd_Stop();
    void snd_Volume(word  Volume);
    word sys_Sleep(word  Units);
    //
    void touch_DetectRegion(word  X1, word  Y1, word  X2, word  Y2);
    word touch_Get(word  Mode);
    void touch_Set(word  Mode);
    //
    word txt_Attributes(word  Attribs);
    word txt_BGcolour(word  Color);
    word txt_Bold(word  Bold);
    word txt_FGcolour(word  Color);
    word txt_FontID(word  FontNumber);
    word txt_Height(word  Multiplier);
    word txt_Inverse(word  Inverse);
    word txt_Italic(word  Italic);
    void txt_MoveCursor(word  Line, word  Column);
    word txt_Opacity(word  TransparentOpaque);
    void txt_Set(word  Func, word  Value);
    word txt_Underline(word  Underline);
    word txt_Width(word  Multiplier);
    word txt_Wrap(word  Position);
    word txt_Xgap(word  Pixels);
    word txt_Ygap(word  Pixels);
    //
    word file_CallFunction(word  Handle, word  ArgCount, t4DWordArray  Args);
    word sys_GetModel(char *  ModelStr);
    word sys_GetVersion();
    word sys_GetPmmC();
    word writeString(word  Handle, char *  StringOut);
    word readString(word  Handle, char *  StringIn);
    void blitComtoDisplay(word  X, word  Y, word  Width, word  Height, t4DByteArray  Pixels);
    word file_FindFirstRet(char *  Filename, char *  StringIn);
    word file_FindNextRet(char *  StringIn);
    void setbaudWait(word  Newrate);
    void GetAck(void);

    //mes fonctions
    void reset(void);
    void begin(void);

    //4D Global Variables Used

    unsigned long TimeLimit4D;	// time limit in ms for total serial command duration, 2000 (2 seconds) should be adequate for most commands
    // assuming a reasonable baud rate AND low latency AND 0 for the Serial Delay Parameter
    // temporary increase might be required for very long (bitmap write, large image file opens)
    // or indeterminate (eg file_exec, file_run, file_callFunction) commands

private:
    Stream * myVirtualPort;

    byte myPinReset;

    //Intrinsic 4D Routines
    void WriteChars(char * charsout);
    void WriteBytes(char * Source, int Size);
    void WriteWords(word * Source, int Size);
    void getbytes(char * data, int size);
    word GetWord(void);
    void getString(char * outStr, int strLen);
    word GetAckResp(void);
    word GetAckRes2Words(word * word1, word * word2);
    void GetAck2Words(word * word1, word * word2);
    word GetAckResSector(t4DSector Sector);
    word GetAckResStr(char * OutStr);
    word GetAckResData(t4DByteArray OutData, word size);
    void SetThisBaudrate(int Newrate);
    //

};

#endif
