/**
*   PicasoSerial Lib
*   14 Mars 2015
 */

#include "PicasoSerial.h"

#if (ARDUINO >= 100)
#include "Arduino.h" // for Arduino 1.0
#else
#include "WProgram.h" // for Arduino 23
#endif


PicasoSerial::PicasoSerial(Stream * virtualPort,byte pinReset)
{
    myPinReset=pinReset;

    pinMode(myPinReset,OUTPUT);
    digitalWrite(myPinReset,HIGH);

    TimeLimit4D=2000;
    //
    myVirtualPort = virtualPort;
    myVirtualPort->flush();

}
//**************************************
void PicasoSerial::reset(void)
{
    digitalWrite(myPinReset,LOW);
    delayMicroseconds(100);
    digitalWrite(myPinReset,HIGH);

    delay(5000);

}
//***************************************
void PicasoSerial::begin(void)
{
    this->reset();

    this->gfx_BGcolour(WHITE);

    this->touch_DetectRegion(0,0,240,320);

    this->touch_Set(TOUCH_ENABLE);

    this->gfx_Cls();
}
//****************************************
//*********************************************************************************************//
//**********************************Intrinsic 4D Routines**************************************//
//*********************************************************************************************//

void PicasoSerial::WriteChars(char * charsout)
{
    unsigned char wk ;
    do
    {
        wk = *charsout++ ;
        myVirtualPort->write(wk) ;
    }
    while (wk) ;
}
//***********************************************************
void PicasoSerial::WriteBytes(char * Source, int Size)
{
    unsigned char wk ;
    int i ;
    for (i = 0; i < Size; i++)
    {
        wk = *Source++ ;
        myVirtualPort->write(wk) ;
    }
}
//***********************************************************
void PicasoSerial::WriteWords(word * Source, int Size)
{
    word wk ;
    int i ;
    for (i = 0; i < Size; i++)
    {
        wk = *Source++ ;
        myVirtualPort->write(wk >> 8) ;
        myVirtualPort->write(wk) ;
    }
}
//*******************************************************
void PicasoSerial::getbytes(char * data, int size)
{
    int read ;
    unsigned long sttime ;
    int readc ;
    readc  = 0 ;
    sttime = millis() ;
    while ((readc != size) && (millis() - sttime < TimeLimit4D))
    {
        if(myVirtualPort->available())
        {
            data[readc++] = myVirtualPort->read() ;
        }
    }
    if (readc != size)
    {

    }
}
//************************************
void PicasoSerial::GetAck(void)
{
    int read ;
    unsigned char readx ;
    unsigned long sttime ;

    sttime  = millis();
    read    = 0 ;
    while ((read != 1) && (millis() - sttime < TimeLimit4D))
    {
        if(myVirtualPort->available() != 0)
        {
            readx = myVirtualPort->read() ;
            read = 1 ;
        }
    }

}
//**************************************
word PicasoSerial::GetWord(void)
{
    unsigned char readx[2] ;
    int readc ;
    unsigned long sttime ;


    sttime   = millis();
    readc    = 0 ;
    while ((readc != 2) && (millis() - sttime < TimeLimit4D))
    {
        if(myVirtualPort->available())
        {
            readx[readc++] = myVirtualPort->read() ;
        }
    }

    if (readc != 2)
    {
        return 0 ;
    }
    else
        return readx[0] << 8 | readx[1] ;
}
//************************************************************
void PicasoSerial::getString(char * outStr, int strLen)
{
    unsigned char readx[2] ;
    int readc ;
    unsigned long sttime ;


    sttime   = millis();
    readc    = 0 ;
    while ((readc != strLen) && (millis() - sttime < TimeLimit4D))
    {
        if(myVirtualPort->available())
        {
            outStr[readc++] = myVirtualPort->read() ;
        }
    }


    outStr[readc] = 0 ;
}
//*****************************************
word PicasoSerial::GetAckResp(void)
{
    GetAck() ;
    return GetWord() ;
}
//******************************************************************
word PicasoSerial::GetAckRes2Words(word * word1, word * word2)
{
    int Result ;
    GetAck() ;
    Result = GetWord() ;
    *word1 = GetWord() ;
    *word2 = GetWord() ;
    return Result ;
}
//****************************************************************
void PicasoSerial::GetAck2Words(word * word1, word * word2)
{
    GetAck() ;
    *word1 = GetWord() ;
    *word2 = GetWord() ;
}
//*********************************************************
word PicasoSerial::GetAckResSector(t4DSector Sector)
{
    int Result ;
    GetAck() ;
    Result = GetWord() ;
    getbytes(Sector, 512) ;
    return Result ;
}
//***************************************************
word PicasoSerial::GetAckResStr(char * OutStr)
{
    int Result ;
    GetAck() ;
    Result = GetWord() ;
    getString(OutStr, Result) ;
    return Result ;
}
//**********************************************************************
word PicasoSerial::GetAckResData(t4DByteArray OutData, word size)
{
    int Result ;
    GetAck() ;
    Result = GetWord() ;
    getbytes(OutData, size) ;
    return Result ;
}
//****************************************************
void PicasoSerial::SetThisBaudrate(int Newrate)
{
    int br ;
    myVirtualPort->flush() ;
//  _virtualPort->end() ;
    switch(Newrate)
    {
        /*   case BAUD_110    : br = 110 ;
             break ;
           case BAUD_300    : br = 300 ;
             break ;
           case BAUD_600    : br = 600 ;
             break ;
           case BAUD_1200   : br = 1200 ;
             break ;
           case BAUD_2400   : br = 2400 ;
             break ;
           case BAUD_4800   : br = 4800 ;
             break ;*/
    case BAUD_9600   :
        br = 9600 ;
        break ;
//   case BAUD_14400  : br = 14400 ;
//      break ;
    case BAUD_19200  :
        br = 19200 ;
        break ;
        /*   case BAUD_31250  : br = 31250 ;
             break ;
           case BAUD_38400  : br = 38400 ;
             break ;
           case BAUD_56000  : br = 56000 ;
             break ;
           case BAUD_57600  : br = 57600 ;
             break ;
           case BAUD_115200 : br = 115200 ;
             break ;
           case BAUD_128000 : br = 133928 ; // actual rate is not 128000 ;
             break ;
           case BAUD_256000 : br = 281250 ; // actual rate is not  256000 ;
             break ;
           case BAUD_300000 : br = 312500 ; // actual rate is not  300000 ;
             break ;
           case BAUD_375000 : br = 401785 ; // actual rate is not  375000 ;
             break ;
           case BAUD_500000 : br = 562500 ; // actual rate is not  500000 ;
             break ;
           case BAUD_600000 : br = 703125 ; // actual rate is not  600000 ;
             break ;*/
    }
//  _virtualPort->begin(br) ;
    delay(50) ; // Display sleeps for 100
    myVirtualPort->flush() ;
}

//*********************************************************************************************//
//**********************************Compound 4D Routines***************************************//
//*********************************************************************************************//
word PicasoSerial::bus_In()
{
    myVirtualPort->write(F_bus_In >> 8) ;
    myVirtualPort->write(F_bus_In) ;
    return GetAckResp() ;
}
//********************************************
void PicasoSerial::bus_Out(word Bits)
{
    myVirtualPort->write(F_bus_Out >> 8) ;
    myVirtualPort->write(F_bus_Out) ;
    myVirtualPort->write(Bits >> 8) ;
    myVirtualPort->write(Bits) ;
    GetAck() ;
}
//**********************************
word PicasoSerial::bus_Read()
{
    myVirtualPort->write(F_bus_Read >> 8) ;
    myVirtualPort->write(F_bus_Read) ;
    return GetAckResp() ;
}
//************************************
void PicasoSerial::bus_Set(word IOMap)
{
    myVirtualPort->write(F_bus_Set >> 8) ;
    myVirtualPort->write(F_bus_Set) ;
    myVirtualPort->write(IOMap >> 8) ;
    myVirtualPort->write(IOMap) ;
    GetAck() ;
}
//*************************************
void PicasoSerial::bus_Write(word Bits)
{
    myVirtualPort->write(F_bus_Write >> 8) ;
    myVirtualPort->write(F_bus_Write) ;
    myVirtualPort->write(Bits >> 8) ;
    myVirtualPort->write(Bits) ;
    GetAck() ;
}
//********************************************
word PicasoSerial::charheight(char  TestChar)
{
    myVirtualPort->print((char)(F_charheight >> 8));
    myVirtualPort->print((char)(F_charheight));
    myVirtualPort->print((char)(TestChar));
    return GetAckResp();
}
//*******************************************
word PicasoSerial::charwidth(char  TestChar)
{
    myVirtualPort->print((char)(F_charwidth >> 8));
    myVirtualPort->print((char)(F_charwidth));
    myVirtualPort->print((char)(TestChar));
    return GetAckResp();
}
//****************************************
word PicasoSerial::file_Close(word  Handle)
{
    myVirtualPort->print((char)(F_file_Close >> 8));
    myVirtualPort->print((char)(F_file_Close));
    myVirtualPort->print((char)(Handle >> 8));
    myVirtualPort->print((char)(Handle));
    return GetAckResp();
}
//**********************************************
word PicasoSerial::file_Count(char *  Filename)
{
    myVirtualPort->print((char)(F_file_Count >> 8));
    myVirtualPort->print((char)(F_file_Count));
    WriteChars(Filename);
    return GetAckResp();
}
//********************************************
word PicasoSerial::file_Dir(char *  Filename)
{
    myVirtualPort->print((char)(F_file_Dir >> 8));
    myVirtualPort->print((char)(F_file_Dir));
    WriteChars(Filename);
    return GetAckResp();
}
//*********************************************
word PicasoSerial::file_Erase(char *  Filename)
{
    myVirtualPort->print((char)(F_file_Erase >> 8));
    myVirtualPort->print((char)(F_file_Erase));
    WriteChars(Filename);
    return GetAckResp();
}
//******************************
word PicasoSerial::file_Error()
{
    myVirtualPort->print((char)(F_file_Error >> 8));
    myVirtualPort->print((char)(F_file_Error));
    return GetAckResp();
}
//*******************************************************************************
word PicasoSerial::file_Exec(char *  Filename, word  ArgCount, t4DWordArray  Args)
{
    myVirtualPort->print((char)(F_file_Exec >> 8));
    myVirtualPort->print((char)(F_file_Exec));
    WriteChars(Filename);
    myVirtualPort->print((char)(ArgCount >> 8));
    myVirtualPort->print((char)(ArgCount));
    WriteWords(Args, ArgCount);
    return GetAckResp();
}
//***********************************************
word PicasoSerial::file_Exists(char *  Filename)
{
    myVirtualPort->print((char)(F_file_Exists >> 8));
    myVirtualPort->print((char)(F_file_Exists));
    WriteChars(Filename);
    return GetAckResp();
}
//*************************************************
word PicasoSerial::file_FindFirst(char *  Filename)
{
    myVirtualPort->print((char)(F_file_FindFirst >> 8));
    myVirtualPort->print((char)(F_file_FindFirst));
    WriteChars(Filename);
    return GetAckResp();
}
//********************************
word PicasoSerial::file_FindNext()
{
    myVirtualPort->print((char)(F_file_FindNext >> 8));
    myVirtualPort->print((char)(F_file_FindNext));
    return GetAckResp();
}
//****************************************
char PicasoSerial::file_GetC(word  Handle)
{
    myVirtualPort->print((char)(F_file_GetC >> 8));
    myVirtualPort->print((char)(F_file_GetC));
    myVirtualPort->print((char)(Handle >> 8));
    myVirtualPort->print((char)(Handle));
    return GetAckResp();
}
//*********************************************************************
word PicasoSerial::file_GetS(char *  StringIn, word  Size, word  Handle)
{
    myVirtualPort->print((char)(F_file_GetS >> 8));
    myVirtualPort->print((char)(F_file_GetS));
    myVirtualPort->print((char)(Size >> 8));
    myVirtualPort->print((char)(Size));
    myVirtualPort->print((char)(Handle >> 8));
    myVirtualPort->print((char)(Handle));
    return GetAckResStr(StringIn);
}
//****************************************
word PicasoSerial::file_GetW(word  Handle)
{
    myVirtualPort->print((char)(F_file_GetW >> 8));
    myVirtualPort->print((char)(F_file_GetW));
    myVirtualPort->print((char)(Handle >> 8));
    myVirtualPort->print((char)(Handle));
    return GetAckResp();
}
//*************************************************************
word PicasoSerial::file_Image(word  X, word  Y, word  Handle)
{
    myVirtualPort->print((char)(F_file_Image >> 8));
    myVirtualPort->print((char)(F_file_Image));
    myVirtualPort->print((char)(X >> 8));
    myVirtualPort->print((char)(X));
    myVirtualPort->print((char)(Y >> 8));
    myVirtualPort->print((char)(Y));
    myVirtualPort->print((char)(Handle >> 8));
    myVirtualPort->print((char)(Handle));
    return GetAckResp();
}
//*************************************************************************************
word PicasoSerial::file_Index(word  Handle, word  HiSize, word  LoSize, word  Recordnum)
{
    myVirtualPort->print((char)(F_file_Index >> 8));
    myVirtualPort->print((char)(F_file_Index));
    myVirtualPort->print((char)(Handle >> 8));
    myVirtualPort->print((char)(Handle));
    myVirtualPort->print((char)(HiSize >> 8));
    myVirtualPort->print((char)(HiSize));
    myVirtualPort->print((char)(LoSize >> 8));
    myVirtualPort->print((char)(LoSize));
    myVirtualPort->print((char)(Recordnum >> 8));
    myVirtualPort->print((char)(Recordnum));
    return GetAckResp();
}
//****************************************************
word PicasoSerial::file_LoadFunction(char *  Filename)
{
    myVirtualPort->print((char)(F_file_LoadFunction >> 8));
    myVirtualPort->print((char)(F_file_LoadFunction));
    WriteChars(Filename);
    return GetAckResp();
}
//***********************************************************************************
word PicasoSerial::file_LoadImageControl(char *  Datname, char *  GCIName, word  Mode)
{
    myVirtualPort->print((char)(F_file_LoadImageControl >> 8));
    myVirtualPort->print((char)(F_file_LoadImageControl));
    WriteChars(Datname);
    WriteChars(GCIName);
    myVirtualPort->print((char)(Mode >> 8));
    myVirtualPort->print((char)(Mode));
    return GetAckResp();
}
//******************************
word PicasoSerial::file_Mount()
{
    myVirtualPort->print((char)(F_file_Mount >> 8));
    myVirtualPort->print((char)(F_file_Mount));
    return GetAckResp();
}
//*********************************************************
word PicasoSerial::file_Open(char *  Filename, char  Mode)
{
    myVirtualPort->print((char)(F_file_Open >> 8));
    myVirtualPort->print((char)(F_file_Open));
    WriteChars(Filename);
    myVirtualPort->print((char)(Mode));
    return GetAckResp();
}
//***********************************************
word PicasoSerial::file_PlayWAV(char *  Filename)
{
    myVirtualPort->print((char)(F_file_PlayWAV >> 8));
    myVirtualPort->print((char)(F_file_PlayWAV));
    WriteChars(Filename);
    return GetAckResp();
}
//*********************************************************
word PicasoSerial::file_PutC(char  Character, word  Handle)
{
    myVirtualPort->print((char)(F_file_PutC >> 8));
    myVirtualPort->print((char)(F_file_PutC));
    myVirtualPort->print((char)(Character));
    myVirtualPort->print((char)(Handle >> 8));
    myVirtualPort->print((char)(Handle));
    return GetAckResp();
}
//***********************************************************
word PicasoSerial::file_PutS(char *  StringOut, word  Handle)
{
    myVirtualPort->print((char)(F_file_PutS >> 8));
    myVirtualPort->print((char)(F_file_PutS));
    WriteChars(StringOut);
    myVirtualPort->print((char)(Handle >> 8));
    myVirtualPort->print((char)(Handle));
    return GetAckResp();
}
//****************************************************
word PicasoSerial::file_PutW(word  Word, word  Handle)
{
    myVirtualPort->print((char)(F_file_PutW >> 8));
    myVirtualPort->print((char)(F_file_PutW));
    myVirtualPort->print((char)(Word >> 8));
    myVirtualPort->print((char)(Word));
    myVirtualPort->print((char)(Handle >> 8));
    myVirtualPort->print((char)(Handle));
    return GetAckResp();
}
//************************************************************************
word PicasoSerial::file_Read(t4DByteArray  Data, word  Size, word  Handle)
{
    myVirtualPort->print((char)(F_file_Read >> 8));
    myVirtualPort->print((char)(F_file_Read));
    myVirtualPort->print((char)(Size >> 8));
    myVirtualPort->print((char)(Size));
    myVirtualPort->print((char)(Handle >> 8));
    myVirtualPort->print((char)(Handle));
    return GetAckResData(Data,Size);
}
//******************************************
word PicasoSerial::file_Rewind(word  Handle)
{
    myVirtualPort->print((char)(F_file_Rewind >> 8));
    myVirtualPort->print((char)(F_file_Rewind));
    myVirtualPort->print((char)(Handle >> 8));
    myVirtualPort->print((char)(Handle));
    return GetAckResp();
}
//*******************************************************************************
word PicasoSerial::file_Run(char *  Filename, word  ArgCount, t4DWordArray  Args)
{
    myVirtualPort->print((char)(F_file_Run >> 8));
    myVirtualPort->print((char)(F_file_Run));
    WriteChars(Filename);
    myVirtualPort->print((char)(ArgCount >> 8));
    myVirtualPort->print((char)(ArgCount));
    WriteWords(Args, ArgCount);
    return GetAckResp();
}
//**********************************************************************************************
word PicasoSerial::file_ScreenCapture(word  X, word  Y, word  Width, word  Height, word  Handle)
{
    myVirtualPort->print((char)(F_file_ScreenCapture >> 8));
    myVirtualPort->print((char)(F_file_ScreenCapture));
    myVirtualPort->print((char)(X >> 8));
    myVirtualPort->print((char)(X));
    myVirtualPort->print((char)(Y >> 8));
    myVirtualPort->print((char)(Y));
    myVirtualPort->print((char)(Width >> 8));
    myVirtualPort->print((char)(Width));
    myVirtualPort->print((char)(Height >> 8));
    myVirtualPort->print((char)(Height));
    myVirtualPort->print((char)(Handle >> 8));
    myVirtualPort->print((char)(Handle));
    return GetAckResp();
}
//*******************************************************************
word PicasoSerial::file_Seek(word  Handle, word  HiWord, word  LoWord)
{
    myVirtualPort->print((char)(F_file_Seek >> 8));
    myVirtualPort->print((char)(F_file_Seek));
    myVirtualPort->print((char)(Handle >> 8));
    myVirtualPort->print((char)(Handle));
    myVirtualPort->print((char)(HiWord >> 8));
    myVirtualPort->print((char)(HiWord));
    myVirtualPort->print((char)(LoWord >> 8));
    myVirtualPort->print((char)(LoWord));
    return GetAckResp();
}
//************************************************************************
word PicasoSerial::file_Size(word  Handle, word *  HiWord, word *  LoWord)
{
    myVirtualPort->print((char)(F_file_Size >> 8));
    myVirtualPort->print((char)(F_file_Size));
    myVirtualPort->print((char)(Handle >> 8));
    myVirtualPort->print((char)(Handle));
    return GetAckRes2Words(HiWord,LoWord);
}
//************************************************************************
word PicasoSerial::file_Tell(word  Handle, word *  HiWord, word *  LoWord)
{
    myVirtualPort->print((char)(F_file_Tell >> 8));
    myVirtualPort->print((char)(F_file_Tell));
    myVirtualPort->print((char)(Handle >> 8));
    myVirtualPort->print((char)(Handle));
    return GetAckRes2Words(HiWord,LoWord);
}
//********************************
void PicasoSerial::file_Unmount()
{
    myVirtualPort->print((char)(F_file_Unmount >> 8));
    myVirtualPort->print((char)(F_file_Unmount));
    GetAck();
}
//***************************************************************************
word PicasoSerial::file_Write(word  Size, t4DByteArray  Source, word  Handle)
{
    myVirtualPort->print((char)(F_file_Write >> 8));
    myVirtualPort->print((char)(F_file_Write));
    myVirtualPort->print((char)(Size >> 8));
    myVirtualPort->print((char)(Size));
    WriteBytes(Source, Size);
    myVirtualPort->print((char)(Handle >> 8));
    myVirtualPort->print((char)(Handle));
    return GetAckResp();
}
//**********************************************
word PicasoSerial::gfx_BevelShadow(word  Value)
{
    myVirtualPort->print((char)(F_gfx_BevelShadow >> 8));
    myVirtualPort->print((char)(F_gfx_BevelShadow));
    myVirtualPort->print((char)(Value >> 8));
    myVirtualPort->print((char)(Value));
    return GetAckResp();
}
//********************************************
word PicasoSerial::gfx_BevelWidth(word  Value)
{
    myVirtualPort->print((char)(F_gfx_BevelWidth >> 8));
    myVirtualPort->print((char)(F_gfx_BevelWidth));
    myVirtualPort->print((char)(Value >> 8));
    myVirtualPort->print((char)(Value));
    return GetAckResp();
}
//******************************************
word PicasoSerial::gfx_BGcolour(word  Color)
{
    myVirtualPort->print((char)(F_gfx_BGcolour >> 8));
    myVirtualPort->print((char)(F_gfx_BGcolour));
    myVirtualPort->print((char)(Color >> 8));
    myVirtualPort->print((char)(Color));
    return GetAckResp();
}
//********************************************************
void PicasoSerial::gfx_Button(word  Up, word  x, word  y, word  buttonColour, word  txtColour, word  font, word  txtWidth, word  txtHeight, char *   text)
{
    myVirtualPort->print((char)(F_gfx_Button >> 8));
    myVirtualPort->print((char)(F_gfx_Button));
    myVirtualPort->print((char)(Up >> 8));
    myVirtualPort->print((char)(Up));
    myVirtualPort->print((char)(x >> 8));
    myVirtualPort->print((char)(x));
    myVirtualPort->print((char)(y >> 8));
    myVirtualPort->print((char)(y));
    myVirtualPort->print((char)(buttonColour >> 8));
    myVirtualPort->print((char)(buttonColour));
    myVirtualPort->print((char)(txtColour >> 8));
    myVirtualPort->print((char)(txtColour));
    myVirtualPort->print((char)(font >> 8));
    myVirtualPort->print((char)(font));
    myVirtualPort->print((char)(txtWidth >> 8));
    myVirtualPort->print((char)(txtWidth));
    myVirtualPort->print((char)(txtHeight >> 8));
    myVirtualPort->print((char)(txtHeight));
    WriteChars(text);
    GetAck();
}
//*****************************************************************
void PicasoSerial::gfx_ChangeColour(word  OldColor, word  NewColor)
{
    myVirtualPort->print((char)(F_gfx_ChangeColour >> 8));
    myVirtualPort->print((char)(F_gfx_ChangeColour));
    myVirtualPort->print((char)(OldColor >> 8));
    myVirtualPort->print((char)(OldColor));
    myVirtualPort->print((char)(NewColor >> 8));
    myVirtualPort->print((char)(NewColor));
    GetAck();
}
//************************************************************************
void PicasoSerial::gfx_Circle(word  X, word  Y, word  Radius, word  Color)
{
    myVirtualPort->print((char)(F_gfx_Circle >> 8));
    myVirtualPort->print((char)(F_gfx_Circle));
    myVirtualPort->print((char)(X >> 8));
    myVirtualPort->print((char)(X));
    myVirtualPort->print((char)(Y >> 8));
    myVirtualPort->print((char)(Y));
    myVirtualPort->print((char)(Radius >> 8));
    myVirtualPort->print((char)(Radius));
    myVirtualPort->print((char)(Color >> 8));
    myVirtualPort->print((char)(Color));
    GetAck();
}
//******************************************************************************
void PicasoSerial::gfx_CircleFilled(word  X, word  Y, word  Radius, word  Color)
{
    myVirtualPort->print((char)(F_gfx_CircleFilled >> 8));
    myVirtualPort->print((char)(F_gfx_CircleFilled));
    myVirtualPort->print((char)(X >> 8));
    myVirtualPort->print((char)(X));
    myVirtualPort->print((char)(Y >> 8));
    myVirtualPort->print((char)(Y));
    myVirtualPort->print((char)(Radius >> 8));
    myVirtualPort->print((char)(Radius));
    myVirtualPort->print((char)(Color >> 8));
    myVirtualPort->print((char)(Color));
    GetAck();
}
//*******************************************
void PicasoSerial::gfx_Clipping(word  OnOff)
{
    myVirtualPort->print((char)(F_gfx_Clipping >> 8));
    myVirtualPort->print((char)(F_gfx_Clipping));
    myVirtualPort->print((char)(OnOff >> 8));
    myVirtualPort->print((char)(OnOff));
    GetAck();
}
//***********************************************************************
void PicasoSerial::gfx_ClipWindow(word  X1, word  Y1, word  X2, word  Y2)
{
    myVirtualPort->print((char)(F_gfx_ClipWindow >> 8));
    myVirtualPort->print((char)(F_gfx_ClipWindow));
    myVirtualPort->print((char)(X1 >> 8));
    myVirtualPort->print((char)(X1));
    myVirtualPort->print((char)(Y1 >> 8));
    myVirtualPort->print((char)(Y1));
    myVirtualPort->print((char)(X2 >> 8));
    myVirtualPort->print((char)(X2));
    myVirtualPort->print((char)(Y2 >> 8));
    myVirtualPort->print((char)(Y2));
    GetAck();
}
//***************************
void PicasoSerial::gfx_Cls()
{
    myVirtualPort->print((char)(F_gfx_Cls >> 8));
    myVirtualPort->print((char)(F_gfx_Cls));
    GetAck();
}
//**********************************************
word PicasoSerial::gfx_Contrast(word  Contrast)
{
    myVirtualPort->print((char)(F_gfx_Contrast >> 8));
    myVirtualPort->print((char)(F_gfx_Contrast));
    myVirtualPort->print((char)(Contrast >> 8));
    myVirtualPort->print((char)(Contrast));
    return GetAckResp();
}
//**********************************************************************************
void PicasoSerial::gfx_Ellipse(word  X, word  Y, word  Xrad, word  Yrad, word  Color)
{
    myVirtualPort->print((char)(F_gfx_Ellipse >> 8));
    myVirtualPort->print((char)(F_gfx_Ellipse));
    myVirtualPort->print((char)(X >> 8));
    myVirtualPort->print((char)(X));
    myVirtualPort->print((char)(Y >> 8));
    myVirtualPort->print((char)(Y));
    myVirtualPort->print((char)(Xrad >> 8));
    myVirtualPort->print((char)(Xrad));
    myVirtualPort->print((char)(Yrad >> 8));
    myVirtualPort->print((char)(Yrad));
    myVirtualPort->print((char)(Color >> 8));
    myVirtualPort->print((char)(Color));
    GetAck();
}
//*****************************************************************************************
void PicasoSerial::gfx_EllipseFilled(word  X, word  Y, word  Xrad, word  Yrad, word  Color)
{
    myVirtualPort->print((char)(F_gfx_EllipseFilled >> 8));
    myVirtualPort->print((char)(F_gfx_EllipseFilled));
    myVirtualPort->print((char)(X >> 8));
    myVirtualPort->print((char)(X));
    myVirtualPort->print((char)(Y >> 8));
    myVirtualPort->print((char)(Y));
    myVirtualPort->print((char)(Xrad >> 8));
    myVirtualPort->print((char)(Xrad));
    myVirtualPort->print((char)(Yrad >> 8));
    myVirtualPort->print((char)(Yrad));
    myVirtualPort->print((char)(Color >> 8));
    myVirtualPort->print((char)(Color));
    GetAck();
}
//*******************************************
word PicasoSerial::gfx_FrameDelay(word  Msec)
{
    myVirtualPort->print((char)(F_gfx_FrameDelay >> 8));
    myVirtualPort->print((char)(F_gfx_FrameDelay));
    myVirtualPort->print((char)(Msec >> 8));
    myVirtualPort->print((char)(Msec));
    return GetAckResp();
}
//************************************
word PicasoSerial::gfx_Get(word  Mode)
{
    myVirtualPort->print((char)(F_gfx_Get >> 8));
    myVirtualPort->print((char)(F_gfx_Get));
    myVirtualPort->print((char)(Mode >> 8));
    myVirtualPort->print((char)(Mode));
    return GetAckResp();
}
//************************************************
word PicasoSerial::gfx_GetPixel(word  X, word  Y)
{
    myVirtualPort->print((char)(F_gfx_GetPixel >> 8));
    myVirtualPort->print((char)(F_gfx_GetPixel));
    myVirtualPort->print((char)(X >> 8));
    myVirtualPort->print((char)(X));
    myVirtualPort->print((char)(Y >> 8));
    myVirtualPort->print((char)(Y));
    return GetAckResp();
}
//******************************************************************************
void PicasoSerial::gfx_Line(word  X1, word  Y1, word  X2, word  Y2, word  Color)
{
    myVirtualPort->print((char)(F_gfx_Line >> 8));
    myVirtualPort->print((char)(F_gfx_Line));
    myVirtualPort->print((char)(X1 >> 8));
    myVirtualPort->print((char)(X1));
    myVirtualPort->print((char)(Y1 >> 8));
    myVirtualPort->print((char)(Y1));
    myVirtualPort->print((char)(X2 >> 8));
    myVirtualPort->print((char)(X2));
    myVirtualPort->print((char)(Y2 >> 8));
    myVirtualPort->print((char)(Y2));
    myVirtualPort->print((char)(Color >> 8));
    myVirtualPort->print((char)(Color));
    GetAck();
}
//***********************************************
word PicasoSerial::gfx_LinePattern(word  Pattern)
{
    myVirtualPort->print((char)(F_gfx_LinePattern >> 8));
    myVirtualPort->print((char)(F_gfx_LinePattern));
    myVirtualPort->print((char)(Pattern >> 8));
    myVirtualPort->print((char)(Pattern));
    return GetAckResp();
}
//*********************************************
void PicasoSerial::gfx_LineTo(word  X, word  Y)
{
    myVirtualPort->print((char)(F_gfx_LineTo >> 8));
    myVirtualPort->print((char)(F_gfx_LineTo));
    myVirtualPort->print((char)(X >> 8));
    myVirtualPort->print((char)(X));
    myVirtualPort->print((char)(Y >> 8));
    myVirtualPort->print((char)(Y));
    GetAck();
}
//********************************************
void PicasoSerial::gfx_MoveTo(word  X, word  Y)
{
    myVirtualPort->print((char)(F_gfx_MoveTo >> 8));
    myVirtualPort->print((char)(F_gfx_MoveTo));
    myVirtualPort->print((char)(X >> 8));
    myVirtualPort->print((char)(X));
    myVirtualPort->print((char)(Y >> 8));
    myVirtualPort->print((char)(Y));
    GetAck();
}
//*************************************************************************************
word PicasoSerial::gfx_Orbit(word  Angle, word  Distance, word *  Xdest, word *  Ydest)
{
    myVirtualPort->print((char)(F_gfx_Orbit >> 8));
    myVirtualPort->print((char)(F_gfx_Orbit));
    myVirtualPort->print((char)(Angle >> 8));
    myVirtualPort->print((char)(Angle));
    myVirtualPort->print((char)(Distance >> 8));
    myVirtualPort->print((char)(Distance));
    GetAck2Words(Xdest,Ydest);
    return 0 ;
}
//************************************************
word PicasoSerial::gfx_OutlineColour(word  Color)
{
    myVirtualPort->print((char)(F_gfx_OutlineColour >> 8));
    myVirtualPort->print((char)(F_gfx_OutlineColour));
    myVirtualPort->print((char)(Color >> 8));
    myVirtualPort->print((char)(Color));
    return GetAckResp();
}
//**************************************************************************************************
void PicasoSerial::gfx_Panel(word  Raised, word  X, word  Y, word  Width, word  Height, word  Color)
{
    myVirtualPort->print((char)(F_gfx_Panel >> 8));
    myVirtualPort->print((char)(F_gfx_Panel));
    myVirtualPort->print((char)(Raised >> 8));
    myVirtualPort->print((char)(Raised));
    myVirtualPort->print((char)(X >> 8));
    myVirtualPort->print((char)(X));
    myVirtualPort->print((char)(Y >> 8));
    myVirtualPort->print((char)(Y));
    myVirtualPort->print((char)(Width >> 8));
    myVirtualPort->print((char)(Width));
    myVirtualPort->print((char)(Height >> 8));
    myVirtualPort->print((char)(Height));
    myVirtualPort->print((char)(Color >> 8));
    myVirtualPort->print((char)(Color));
    GetAck();
}
//***********************************************************************************************
void PicasoSerial::gfx_Polygon(word  n, t4DWordArray  Xvalues, t4DWordArray  Yvalues, word  Color)
{
    myVirtualPort->print((char)(F_gfx_Polygon >> 8));
    myVirtualPort->print((char)(F_gfx_Polygon));
    myVirtualPort->print((char)(n >> 8));
    myVirtualPort->print((char)(n));
    WriteWords(Xvalues, n);
    WriteWords(Yvalues, n);
    myVirtualPort->print((char)(Color >> 8));
    myVirtualPort->print((char)(Color));
    GetAck();
}
//******************************************************************************************************
void PicasoSerial::gfx_PolygonFilled(word  n, t4DWordArray  Xvalues, t4DWordArray  Yvalues, word  Color)
{
    myVirtualPort->print((char)(F_gfx_PolygonFilled >> 8));
    myVirtualPort->print((char)(F_gfx_PolygonFilled));
    myVirtualPort->print((char)(n >> 8));
    myVirtualPort->print((char)(n));
    WriteWords(Xvalues, n);
    WriteWords(Yvalues, n);
    myVirtualPort->print((char)(Color >> 8));
    myVirtualPort->print((char)(Color));
    GetAck();
}
//*************************************************************************************************
void PicasoSerial::gfx_Polyline(word  n, t4DWordArray  Xvalues, t4DWordArray  Yvalues, word  Color)
{
    myVirtualPort->print((char)(F_gfx_Polyline >> 8));
    myVirtualPort->print((char)(F_gfx_Polyline));
    myVirtualPort->print((char)(n >> 8));
    myVirtualPort->print((char)(n));
    WriteWords(Xvalues, n);
    WriteWords(Yvalues, n);
    myVirtualPort->print((char)(Color >> 8));
    myVirtualPort->print((char)(Color));
    GetAck();
}
//************************************************************
void PicasoSerial::gfx_PutPixel(word  X, word  Y, word  Color)
{
    myVirtualPort->print((char)(F_gfx_PutPixel >> 8));
    myVirtualPort->print((char)(F_gfx_PutPixel));
    myVirtualPort->print((char)(X >> 8));
    myVirtualPort->print((char)(X));
    myVirtualPort->print((char)(Y >> 8));
    myVirtualPort->print((char)(Y));
    myVirtualPort->print((char)(Color >> 8));
    myVirtualPort->print((char)(Color));
    GetAck();
}
//***********************************************************************************
void PicasoSerial::gfx_Rectangle(word  X1, word  Y1, word  X2, word  Y2, word  Color)
{
    myVirtualPort->print((char)(F_gfx_Rectangle >> 8));
    myVirtualPort->print((char)(F_gfx_Rectangle));
    myVirtualPort->print((char)(X1 >> 8));
    myVirtualPort->print((char)(X1));
    myVirtualPort->print((char)(Y1 >> 8));
    myVirtualPort->print((char)(Y1));
    myVirtualPort->print((char)(X2 >> 8));
    myVirtualPort->print((char)(X2));
    myVirtualPort->print((char)(Y2 >> 8));
    myVirtualPort->print((char)(Y2));
    myVirtualPort->print((char)(Color >> 8));
    myVirtualPort->print((char)(Color));
    GetAck();
}
//*****************************************************************************************
void PicasoSerial::gfx_RectangleFilled(word  X1, word  Y1, word  X2, word  Y2, word  Color)
{
    myVirtualPort->print((char)(F_gfx_RectangleFilled >> 8));
    myVirtualPort->print((char)(F_gfx_RectangleFilled));
    myVirtualPort->print((char)(X1 >> 8));
    myVirtualPort->print((char)(X1));
    myVirtualPort->print((char)(Y1 >> 8));
    myVirtualPort->print((char)(Y1));
    myVirtualPort->print((char)(X2 >> 8));
    myVirtualPort->print((char)(X2));
    myVirtualPort->print((char)(Y2 >> 8));
    myVirtualPort->print((char)(Y2));
    myVirtualPort->print((char)(Color >> 8));
    myVirtualPort->print((char)(Color));
    GetAck();
}
//******************************************************************************************************
void PicasoSerial::gfx_ScreenCopyPaste(word  Xs, word  Ys, word  Xd, word  Yd, word  Width, word  Height)
{
    myVirtualPort->print((char)(F_gfx_ScreenCopyPaste >> 8));
    myVirtualPort->print((char)(F_gfx_ScreenCopyPaste));
    myVirtualPort->print((char)(Xs >> 8));
    myVirtualPort->print((char)(Xs));
    myVirtualPort->print((char)(Ys >> 8));
    myVirtualPort->print((char)(Ys));
    myVirtualPort->print((char)(Xd >> 8));
    myVirtualPort->print((char)(Xd));
    myVirtualPort->print((char)(Yd >> 8));
    myVirtualPort->print((char)(Yd));
    myVirtualPort->print((char)(Width >> 8));
    myVirtualPort->print((char)(Width));
    myVirtualPort->print((char)(Height >> 8));
    myVirtualPort->print((char)(Height));
    GetAck();
}
//*************************************************
word PicasoSerial::gfx_ScreenMode(word  ScreenMode)
{
    myVirtualPort->print((char)(F_gfx_ScreenMode >> 8));
    myVirtualPort->print((char)(F_gfx_ScreenMode));
    myVirtualPort->print((char)(ScreenMode >> 8));
    myVirtualPort->print((char)(ScreenMode));
    return GetAckResp();
}
//*************************************************
void PicasoSerial::gfx_Set(word  Func, word  Value)
{
    myVirtualPort->print((char)(F_gfx_Set >> 8));
    myVirtualPort->print((char)(F_gfx_Set));
    myVirtualPort->print((char)(Func >> 8));
    myVirtualPort->print((char)(Func));
    myVirtualPort->print((char)(Value >> 8));
    myVirtualPort->print((char)(Value));
    GetAck();
}
//*************************************
void PicasoSerial::gfx_SetClipRegion()
{
    myVirtualPort->print((char)(F_gfx_SetClipRegion >> 8));
    myVirtualPort->print((char)(F_gfx_SetClipRegion));
    GetAck();
}
//**************************************************************************************
word PicasoSerial::gfx_Slider(word  Mode, word  X1, word  Y1, word  X2, word  Y2, word  Color, word  Scale, word  Value)
{
    myVirtualPort->print((char)(F_gfx_Slider >> 8));
    myVirtualPort->print((char)(F_gfx_Slider));
    myVirtualPort->print((char)(Mode >> 8));
    myVirtualPort->print((char)(Mode));
    myVirtualPort->print((char)(X1 >> 8));
    myVirtualPort->print((char)(X1));
    myVirtualPort->print((char)(Y1 >> 8));
    myVirtualPort->print((char)(Y1));
    myVirtualPort->print((char)(X2 >> 8));
    myVirtualPort->print((char)(X2));
    myVirtualPort->print((char)(Y2 >> 8));
    myVirtualPort->print((char)(Y2));
    myVirtualPort->print((char)(Color >> 8));
    myVirtualPort->print((char)(Color));
    myVirtualPort->print((char)(Scale >> 8));
    myVirtualPort->print((char)(Scale));
    myVirtualPort->print((char)(Value >> 8));
    myVirtualPort->print((char)(Value));
    return GetAckResp();
}
//*********************************************
word PicasoSerial::gfx_Transparency(word  OnOff)
{
    myVirtualPort->print((char)(F_gfx_Transparency >> 8));
    myVirtualPort->print((char)(F_gfx_Transparency));
    myVirtualPort->print((char)(OnOff >> 8));
    myVirtualPort->print((char)(OnOff));
    return GetAckResp();
}
//***************************************************
word PicasoSerial::gfx_TransparentColour(word  Color)
{
    myVirtualPort->print((char)(F_gfx_TransparentColour >> 8));
    myVirtualPort->print((char)(F_gfx_TransparentColour));
    myVirtualPort->print((char)(Color >> 8));
    myVirtualPort->print((char)(Color));
    return GetAckResp();
}
//******************************************************************************************************
void PicasoSerial::gfx_Triangle(word  X1, word  Y1, word  X2, word  Y2, word  X3, word  Y3, word  Color)
{
    myVirtualPort->print((char)(F_gfx_Triangle >> 8));
    myVirtualPort->print((char)(F_gfx_Triangle));
    myVirtualPort->print((char)(X1 >> 8));
    myVirtualPort->print((char)(X1));
    myVirtualPort->print((char)(Y1 >> 8));
    myVirtualPort->print((char)(Y1));
    myVirtualPort->print((char)(X2 >> 8));
    myVirtualPort->print((char)(X2));
    myVirtualPort->print((char)(Y2 >> 8));
    myVirtualPort->print((char)(Y2));
    myVirtualPort->print((char)(X3 >> 8));
    myVirtualPort->print((char)(X3));
    myVirtualPort->print((char)(Y3 >> 8));
    myVirtualPort->print((char)(Y3));
    myVirtualPort->print((char)(Color >> 8));
    myVirtualPort->print((char)(Color));
    GetAck();
}
//**********************************************************************************************
void PicasoSerial::gfx_TriangleFilled(word  X1, word  Y1, word  X2, word  Y2, word  X3, word  Y3, word  Color)
{
    myVirtualPort->print((char)(F_gfx_TriangleFilled >> 8));
    myVirtualPort->print((char)(F_gfx_TriangleFilled));
    myVirtualPort->print((char)(X1 >> 8));
    myVirtualPort->print((char)(X1));
    myVirtualPort->print((char)(Y1 >> 8));
    myVirtualPort->print((char)(Y1));
    myVirtualPort->print((char)(X2 >> 8));
    myVirtualPort->print((char)(X2));
    myVirtualPort->print((char)(Y2 >> 8));
    myVirtualPort->print((char)(Y2));
    myVirtualPort->print((char)(X3 >> 8));
    myVirtualPort->print((char)(X3));
    myVirtualPort->print((char)(Y3 >> 8));
    myVirtualPort->print((char)(Y3));
    myVirtualPort->print((char)(Color >> 8));
    myVirtualPort->print((char)(Color));
    GetAck();
}
//****************************************************************************
word PicasoSerial::img_ClearAttributes(word  Handle, word  Index, word  Value)
{
    myVirtualPort->print((char)(F_img_ClearAttributes >> 8));
    myVirtualPort->print((char)(F_img_ClearAttributes));
    myVirtualPort->print((char)(Handle >> 8));
    myVirtualPort->print((char)(Handle));
    myVirtualPort->print((char)(Index >> 8));
    myVirtualPort->print((char)(Index));
    myVirtualPort->print((char)(Value >> 8));
    myVirtualPort->print((char)(Value));
    return GetAckResp();
}
//*****************************************************
word PicasoSerial::img_Darken(word  Handle, word  Index)
{
    myVirtualPort->print((char)(F_img_Darken >> 8));
    myVirtualPort->print((char)(F_img_Darken));
    myVirtualPort->print((char)(Handle >> 8));
    myVirtualPort->print((char)(Handle));
    myVirtualPort->print((char)(Index >> 8));
    myVirtualPort->print((char)(Index));
    return GetAckResp();
}
//*******************************************************
word PicasoSerial::img_Disable(word  Handle, word  Index)
{
    myVirtualPort->print((char)(F_img_Disable >> 8));
    myVirtualPort->print((char)(F_img_Disable));
    myVirtualPort->print((char)(Handle >> 8));
    myVirtualPort->print((char)(Handle));
    myVirtualPort->print((char)(Index >> 8));
    myVirtualPort->print((char)(Index));
    return GetAckResp();
}
//******************************************************
word PicasoSerial::img_Enable(word  Handle, word  Index)
{
    myVirtualPort->print((char)(F_img_Enable >> 8));
    myVirtualPort->print((char)(F_img_Enable));
    myVirtualPort->print((char)(Handle >> 8));
    myVirtualPort->print((char)(Handle));
    myVirtualPort->print((char)(Index >> 8));
    myVirtualPort->print((char)(Index));
    return GetAckResp();
}
//**********************************************************************
word PicasoSerial::img_GetWord(word  Handle, word  Index, word  Offset )
{
    myVirtualPort->print((char)(F_img_GetWord >> 8));
    myVirtualPort->print((char)(F_img_GetWord));
    myVirtualPort->print((char)(Handle >> 8));
    myVirtualPort->print((char)(Handle));
    myVirtualPort->print((char)(Index >> 8));
    myVirtualPort->print((char)(Index));
    myVirtualPort->print((char)(Offset  >> 8));
    myVirtualPort->print((char)(Offset ));
    return GetAckResp();
}
//*******************************************************
word PicasoSerial::img_Lighten(word  Handle, word  Index)
{
    myVirtualPort->print((char)(F_img_Lighten >> 8));
    myVirtualPort->print((char)(F_img_Lighten));
    myVirtualPort->print((char)(Handle >> 8));
    myVirtualPort->print((char)(Handle));
    myVirtualPort->print((char)(Index >> 8));
    myVirtualPort->print((char)(Index));
    return GetAckResp();
}
//**************************************************************************
word PicasoSerial::img_SetAttributes(word  Handle, word  Index, word  Value)
{
    myVirtualPort->print((char)(F_img_SetAttributes >> 8));
    myVirtualPort->print((char)(F_img_SetAttributes));
    myVirtualPort->print((char)(Handle >> 8));
    myVirtualPort->print((char)(Handle));
    myVirtualPort->print((char)(Index >> 8));
    myVirtualPort->print((char)(Index));
    myVirtualPort->print((char)(Value >> 8));
    myVirtualPort->print((char)(Value));
    return GetAckResp();
}
//************************************************************************************
word PicasoSerial::img_SetPosition(word  Handle, word  Index, word  Xpos, word  Ypos)
{
    myVirtualPort->print((char)(F_img_SetPosition >> 8));
    myVirtualPort->print((char)(F_img_SetPosition));
    myVirtualPort->print((char)(Handle >> 8));
    myVirtualPort->print((char)(Handle));
    myVirtualPort->print((char)(Index >> 8));
    myVirtualPort->print((char)(Index));
    myVirtualPort->print((char)(Xpos >> 8));
    myVirtualPort->print((char)(Xpos));
    myVirtualPort->print((char)(Ypos >> 8));
    myVirtualPort->print((char)(Ypos));
    return GetAckResp();
}
//***********************************************************************************
word PicasoSerial::img_SetWord(word  Handle, word  Index, word  Offset , word  Word)
{
    myVirtualPort->print((char)(F_img_SetWord >> 8));
    myVirtualPort->print((char)(F_img_SetWord));
    myVirtualPort->print((char)(Handle >> 8));
    myVirtualPort->print((char)(Handle));
    myVirtualPort->print((char)(Index >> 8));
    myVirtualPort->print((char)(Index));
    myVirtualPort->print((char)(Offset  >> 8));
    myVirtualPort->print((char)(Offset ));
    myVirtualPort->print((char)(Word >> 8));
    myVirtualPort->print((char)(Word));
    return GetAckResp();
}
//****************************************************
word PicasoSerial::img_Show(word  Handle, word  Index)
{
    myVirtualPort->print((char)(F_img_Show >> 8));
    myVirtualPort->print((char)(F_img_Show));
    myVirtualPort->print((char)(Handle >> 8));
    myVirtualPort->print((char)(Handle));
    myVirtualPort->print((char)(Index >> 8));
    myVirtualPort->print((char)(Index));
    return GetAckResp();
}
//*******************************************************
word PicasoSerial::img_Touched(word  Handle, word  Index)
{
    myVirtualPort->print((char)(F_img_Touched >> 8));
    myVirtualPort->print((char)(F_img_Touched));
    myVirtualPort->print((char)(Handle >> 8));
    myVirtualPort->print((char)(Handle));
    myVirtualPort->print((char)(Index >> 8));
    myVirtualPort->print((char)(Index));
    return GetAckResp();
}
//******************************
word PicasoSerial::media_Flush()
{
    myVirtualPort->print((char)(F_media_Flush >> 8));
    myVirtualPort->print((char)(F_media_Flush));
    return GetAckResp();
}
//************************************************
void PicasoSerial::media_Image(word  X, word  Y)
{
    myVirtualPort->print((char)(F_media_Image >> 8));
    myVirtualPort->print((char)(F_media_Image));
    myVirtualPort->print((char)(X >> 8));
    myVirtualPort->print((char)(X));
    myVirtualPort->print((char)(Y >> 8));
    myVirtualPort->print((char)(Y));
    GetAck();
}
//*****************************
word PicasoSerial::media_Init()
{
    myVirtualPort->print((char)(F_media_Init >> 8));
    myVirtualPort->print((char)(F_media_Init));
    return GetAckResp();
}
//****************************************************
word PicasoSerial::media_RdSector(t4DSector  SectorIn)
{
    myVirtualPort->print((char)(F_media_RdSector >> 8));
    myVirtualPort->print((char)(F_media_RdSector));
    return GetAckResSector(SectorIn);
}
//*********************************
word PicasoSerial::media_ReadByte()
{
    myVirtualPort->print((char)(F_media_ReadByte >> 8));
    myVirtualPort->print((char)(F_media_ReadByte));
    return GetAckResp();
}
//*********************************
word PicasoSerial::media_ReadWord()
{
    myVirtualPort->print((char)(F_media_ReadWord >> 8));
    myVirtualPort->print((char)(F_media_ReadWord));
    return GetAckResp();
}
//*********************************************************
void PicasoSerial::media_SetAdd(word  HiWord, word  LoWord)
{
    myVirtualPort->print((char)(F_media_SetAdd >> 8));
    myVirtualPort->print((char)(F_media_SetAdd));
    myVirtualPort->print((char)(HiWord >> 8));
    myVirtualPort->print((char)(HiWord));
    myVirtualPort->print((char)(LoWord >> 8));
    myVirtualPort->print((char)(LoWord));
    GetAck();
}
//************************************************************
void PicasoSerial::media_SetSector(word  HiWord, word  LoWord)
{
    myVirtualPort->print((char)(F_media_SetSector >> 8));
    myVirtualPort->print((char)(F_media_SetSector));
    myVirtualPort->print((char)(HiWord >> 8));
    myVirtualPort->print((char)(HiWord));
    myVirtualPort->print((char)(LoWord >> 8));
    myVirtualPort->print((char)(LoWord));
    GetAck();
}
//**********************************************
void PicasoSerial::media_Video(word  X, word  Y)
{
    myVirtualPort->print((char)(F_media_Video >> 8));
    myVirtualPort->print((char)(F_media_Video));
    myVirtualPort->print((char)(X >> 8));
    myVirtualPort->print((char)(X));
    myVirtualPort->print((char)(Y >> 8));
    myVirtualPort->print((char)(Y));
    GetAck();
}
//***********************************************************************
void PicasoSerial::media_VideoFrame(word  X, word  Y, word  Framenumber)
{
    myVirtualPort->print((char)(F_media_VideoFrame >> 8));
    myVirtualPort->print((char)(F_media_VideoFrame));
    myVirtualPort->print((char)(X >> 8));
    myVirtualPort->print((char)(X));
    myVirtualPort->print((char)(Y >> 8));
    myVirtualPort->print((char)(Y));
    myVirtualPort->print((char)(Framenumber >> 8));
    myVirtualPort->print((char)(Framenumber));
    GetAck();
}
//********************************************
word PicasoSerial::media_WriteByte(word  Byte)
{
    myVirtualPort->print((char)(F_media_WriteByte >> 8));
    myVirtualPort->print((char)(F_media_WriteByte));
    myVirtualPort->print((char)(Byte >> 8));
    myVirtualPort->print((char)(Byte));
    return GetAckResp();
}
//*******************************************
word PicasoSerial::media_WriteWord(word  Word)
{
    myVirtualPort->print((char)(F_media_WriteWord >> 8));
    myVirtualPort->print((char)(F_media_WriteWord));
    myVirtualPort->print((char)(Word >> 8));
    myVirtualPort->print((char)(Word));
    return GetAckResp();
}
//****************************************************
word PicasoSerial::media_WrSector(t4DSector  SectorOut)
{
    myVirtualPort->print((char)(F_media_WrSector >> 8));
    myVirtualPort->print((char)(F_media_WrSector));
    WriteBytes(SectorOut, 512);
    return GetAckResp();
}
//*****************************************
word PicasoSerial::mem_Free(word  Handle)
{
    myVirtualPort->print((char)(F_mem_Free >> 8));
    myVirtualPort->print((char)(F_mem_Free));
    myVirtualPort->print((char)(Handle >> 8));
    myVirtualPort->print((char)(Handle));
    return GetAckResp();
}
//****************************
word PicasoSerial::mem_Heap()
{
    myVirtualPort->print((char)(F_mem_Heap >> 8));
    myVirtualPort->print((char)(F_mem_Heap));
    return GetAckResp();
}
//*********************************
word PicasoSerial::pin_HI(word Pin)
{
    myVirtualPort->write(F_pin_HI >> 8) ;
    myVirtualPort->write(F_pin_HI) ;
    myVirtualPort->write(Pin >> 8) ;
    myVirtualPort->write(Pin) ;
    return GetAckResp() ;
}
//*********************************
word PicasoSerial::pin_LO(word Pin)
{
    myVirtualPort->write(F_pin_LO >> 8) ;
    myVirtualPort->write(F_pin_LO) ;
    myVirtualPort->write(Pin >> 8) ;
    myVirtualPort->write(Pin) ;
    return GetAckResp() ;
}
//***********************************
word PicasoSerial::pin_Read(word Pin)
{
    myVirtualPort->write(F_pin_Read >> 8) ;
    myVirtualPort->write(F_pin_Read) ;
    myVirtualPort->write(Pin >> 8) ;
    myVirtualPort->write(Pin) ;
    return GetAckResp() ;
}
//*********************************************
word PicasoSerial::pin_Set(word Mode, word Pin)
{
    myVirtualPort->write(F_pin_Set >> 8) ;
    myVirtualPort->write(F_pin_Set) ;
    myVirtualPort->write(Mode >> 8) ;
    myVirtualPort->write(Mode) ;
    myVirtualPort->write(Pin >> 8) ;
    myVirtualPort->write(Pin) ;
    return GetAckResp() ;
}
//**************************************
void PicasoSerial::putCH(word  WordChar)
{
    myVirtualPort->print((char)(F_putCH >> 8)) ;
    myVirtualPort->print((char)(F_putCH)) ;
    myVirtualPort->print((char)(WordChar >> 8)) ;
    myVirtualPort->print((char)(WordChar)) ;
    GetAck() ;
}
//*****************************************
word PicasoSerial::putstr(char *  InString)
{
    myVirtualPort->print((char)(F_putstr >> 8));
    myVirtualPort->print((char)(F_putstr));
    WriteChars(InString);
    return GetAckResp();
}
//*******************************************
void PicasoSerial::snd_BufSize(word  Bufsize)
{
    myVirtualPort->print((char)(F_snd_BufSize >> 8));
    myVirtualPort->print((char)(F_snd_BufSize));
    myVirtualPort->print((char)(Bufsize >> 8));
    myVirtualPort->print((char)(Bufsize));
    GetAck();
}
//********************************
void PicasoSerial::snd_Continue()
{
    myVirtualPort->print((char)(F_snd_Continue >> 8));
    myVirtualPort->print((char)(F_snd_Continue));
    GetAck();
}
//****************************
void PicasoSerial::snd_Pause()
{
    myVirtualPort->print((char)(F_snd_Pause >> 8));
    myVirtualPort->print((char)(F_snd_Pause));
    GetAck();
}
//***************************************
word PicasoSerial::snd_Pitch(word  Pitch)
{
    myVirtualPort->print((char)(F_snd_Pitch >> 8));
    myVirtualPort->print((char)(F_snd_Pitch));
    myVirtualPort->print((char)(Pitch >> 8));
    myVirtualPort->print((char)(Pitch));
    return GetAckResp();
}
//*******************************
word PicasoSerial::snd_Playing()
{
    myVirtualPort->print((char)(F_snd_Playing >> 8));
    myVirtualPort->print((char)(F_snd_Playing));
    return GetAckResp();
}
//***************************
void PicasoSerial::snd_Stop()
{
    myVirtualPort->print((char)(F_snd_Stop >> 8));
    myVirtualPort->print((char)(F_snd_Stop));
    GetAck();
}
//*****************************************
void PicasoSerial::snd_Volume(word  Volume)
{
    myVirtualPort->print((char)(F_snd_Volume >> 8));
    myVirtualPort->print((char)(F_snd_Volume));
    myVirtualPort->print((char)(Volume >> 8));
    myVirtualPort->print((char)(Volume));
    GetAck();
}
//**************************************
word PicasoSerial::sys_Sleep(word  Units)
{
    myVirtualPort->print((char)(F_sys_Sleep >> 8));
    myVirtualPort->print((char)(F_sys_Sleep));
    myVirtualPort->print((char)(Units >> 8));
    myVirtualPort->print((char)(Units));
    return GetAckResp();
}
//**************************************************************************
void PicasoSerial::touch_DetectRegion(word  X1, word  Y1, word  X2, word  Y2)
{
    myVirtualPort->print((char)(F_touch_DetectRegion >> 8));
    myVirtualPort->print((char)(F_touch_DetectRegion));
    myVirtualPort->print((char)(X1 >> 8));
    myVirtualPort->print((char)(X1));
    myVirtualPort->print((char)(Y1 >> 8));
    myVirtualPort->print((char)(Y1));
    myVirtualPort->print((char)(X2 >> 8));
    myVirtualPort->print((char)(X2));
    myVirtualPort->print((char)(Y2 >> 8));
    myVirtualPort->print((char)(Y2));
    GetAck();
}
//***************************************
word PicasoSerial::touch_Get(word  Mode)
{
    myVirtualPort->print((char)(F_touch_Get >> 8));
    myVirtualPort->print((char)(F_touch_Get));
    myVirtualPort->print((char)(Mode >> 8));
    myVirtualPort->print((char)(Mode));
    return GetAckResp();
}
//**************************************
void PicasoSerial::touch_Set(word  Mode)
{
    myVirtualPort->print((char)(F_touch_Set >> 8));
    myVirtualPort->print((char)(F_touch_Set));
    myVirtualPort->print((char)(Mode >> 8));
    myVirtualPort->print((char)(Mode));
    GetAck();
}
//**********************************************
word PicasoSerial::txt_Attributes(word  Attribs)
{
    myVirtualPort->print((char)(F_txt_Attributes >> 8));
    myVirtualPort->print((char)(F_txt_Attributes));
    myVirtualPort->print((char)(Attribs >> 8));
    myVirtualPort->print((char)(Attribs));
    return GetAckResp();
}
//*******************************************
word PicasoSerial::txt_BGcolour(word  Color)
{
    myVirtualPort->print((char)(F_txt_BGcolour >> 8));
    myVirtualPort->print((char)(F_txt_BGcolour));
    myVirtualPort->print((char)(Color >> 8));
    myVirtualPort->print((char)(Color));
    return GetAckResp();
}
//**************************************
word PicasoSerial::txt_Bold(word  Bold)
{
    myVirtualPort->print((char)(F_txt_Bold >> 8));
    myVirtualPort->print((char)(F_txt_Bold));
    myVirtualPort->print((char)(Bold >> 8));
    myVirtualPort->print((char)(Bold));
    return GetAckResp();
}
//******************************************
word PicasoSerial::txt_FGcolour(word  Color)
{
    myVirtualPort->print((char)(F_txt_FGcolour >> 8));
    myVirtualPort->print((char)(F_txt_FGcolour));
    myVirtualPort->print((char)(Color >> 8));
    myVirtualPort->print((char)(Color));
    return GetAckResp();
}
//*********************************************
word PicasoSerial::txt_FontID(word  FontNumber)
{
    myVirtualPort->print((char)(F_txt_FontID >> 8));
    myVirtualPort->print((char)(F_txt_FontID));
    myVirtualPort->print((char)(FontNumber >> 8));
    myVirtualPort->print((char)(FontNumber));
    return GetAckResp();
}
//**********************************************
word PicasoSerial::txt_Height(word  Multiplier)
{
    myVirtualPort->print((char)(F_txt_Height >> 8));
    myVirtualPort->print((char)(F_txt_Height));
    myVirtualPort->print((char)(Multiplier >> 8));
    myVirtualPort->print((char)(Multiplier));
    return GetAckResp();
}
//*******************************************
word PicasoSerial::txt_Inverse(word  Inverse)
{
    myVirtualPort->print((char)(F_txt_Inverse >> 8));
    myVirtualPort->print((char)(F_txt_Inverse));
    myVirtualPort->print((char)(Inverse >> 8));
    myVirtualPort->print((char)(Inverse));
    return GetAckResp();
}
//******************************************
word PicasoSerial::txt_Italic(word  Italic)
{
    myVirtualPort->print((char)(F_txt_Italic >> 8));
    myVirtualPort->print((char)(F_txt_Italic));
    myVirtualPort->print((char)(Italic >> 8));
    myVirtualPort->print((char)(Italic));
    return GetAckResp();
}
//*********************************************************
void PicasoSerial::txt_MoveCursor(word  Line, word  Column)
{
    myVirtualPort->print((char)(F_txt_MoveCursor >> 8));
    myVirtualPort->print((char)(F_txt_MoveCursor));
    myVirtualPort->print((char)(Line >> 8));
    myVirtualPort->print((char)(Line));
    myVirtualPort->print((char)(Column >> 8));
    myVirtualPort->print((char)(Column));
    GetAck();
}
//*****************************************************
word PicasoSerial::txt_Opacity(word  TransparentOpaque)
{
    myVirtualPort->print((char)(F_txt_Opacity >> 8));
    myVirtualPort->print((char)(F_txt_Opacity));
    myVirtualPort->print((char)(TransparentOpaque >> 8));
    myVirtualPort->print((char)(TransparentOpaque));
    return GetAckResp();
}
//*************************************************
void PicasoSerial::txt_Set(word  Func, word  Value)
{
    myVirtualPort->print((char)(F_txt_Set >> 8));
    myVirtualPort->print((char)(F_txt_Set));
    myVirtualPort->print((char)(Func >> 8));
    myVirtualPort->print((char)(Func));
    myVirtualPort->print((char)(Value >> 8));
    myVirtualPort->print((char)(Value));
    GetAck();
}
//***********************************************
word PicasoSerial::txt_Underline(word  Underline)
{
    myVirtualPort->print((char)(F_txt_Underline >> 8));
    myVirtualPort->print((char)(F_txt_Underline));
    myVirtualPort->print((char)(Underline >> 8));
    myVirtualPort->print((char)(Underline));
    return GetAckResp();
}
//********************************************
word PicasoSerial::txt_Width(word  Multiplier)
{
    myVirtualPort->print((char)(F_txt_Width >> 8));
    myVirtualPort->print((char)(F_txt_Width));
    myVirtualPort->print((char)(Multiplier >> 8));
    myVirtualPort->print((char)(Multiplier));
    return GetAckResp();
}
//*****************************************
word PicasoSerial::txt_Wrap(word  Position)
{
    myVirtualPort->print((char)(F_txt_Wrap >> 8));
    myVirtualPort->print((char)(F_txt_Wrap));
    myVirtualPort->print((char)(Position >> 8));
    myVirtualPort->print((char)(Position));
    return GetAckResp();
}
//****************************************
word PicasoSerial::txt_Xgap(word  Pixels)
{
    myVirtualPort->print((char)(F_txt_Xgap >> 8));
    myVirtualPort->print((char)(F_txt_Xgap));
    myVirtualPort->print((char)(Pixels >> 8));
    myVirtualPort->print((char)(Pixels));
    return GetAckResp() ;
}
//*****************************************
word PicasoSerial::txt_Ygap(word  Pixels)
{
    myVirtualPort->print((char)(F_txt_Ygap >> 8));
    myVirtualPort->print((char)(F_txt_Ygap));
    myVirtualPort->print((char)(Pixels >> 8));
    myVirtualPort->print((char)(Pixels));
    return GetAckResp() ;
}
//************************************************************************************
word PicasoSerial::file_CallFunction(word  Handle, word  ArgCount, t4DWordArray  Args)
{
    myVirtualPort->print((char)(F_file_CallFunction >> 8));
    myVirtualPort->print((char)(F_file_CallFunction));
    myVirtualPort->print((char)(Handle >> 8));
    myVirtualPort->print((char)(Handle));
    myVirtualPort->print((char)(ArgCount >> 8));
    myVirtualPort->print((char)(ArgCount));
    WriteWords(Args, ArgCount);
    return GetAckResp();
}
//************************************************
word PicasoSerial::sys_GetModel(char *  ModelStr)
{
    myVirtualPort->print((char)(F_sys_GetModel >> 8));
    myVirtualPort->print((char)(F_sys_GetModel));
    return GetAckResStr(ModelStr);
}
//*********************************
word PicasoSerial::sys_GetVersion()
{
    myVirtualPort->print((char)(F_sys_GetVersion >> 8));
    myVirtualPort->print((char)(F_sys_GetVersion));
    return GetAckResp();
}
//******************************
word PicasoSerial::sys_GetPmmC()
{
    myVirtualPort->print((char)(F_sys_GetPmmC >> 8)) ;
    myVirtualPort->print((char)(F_sys_GetPmmC)) ;
    return GetAckResp() ;
}
//*************************************************************
word PicasoSerial::writeString(word  Handle, char *  StringOut)
{
    myVirtualPort->print((char)(F_writeString >> 8)) ;
    myVirtualPort->print((char)(F_writeString)) ;
    myVirtualPort->print((char)(Handle >> 8)) ;
    myVirtualPort->print((char)(Handle)) ;
    WriteChars(StringOut) ;
    return GetAckResp() ;
}
//************************************************************
word PicasoSerial::readString(word  Handle, char *  StringIn)
{
    myVirtualPort->print((char)(F_readString >> 8)) ;
    myVirtualPort->print((char)(F_readString)) ;
    myVirtualPort->print((char)(Handle >> 8)) ;
    myVirtualPort->print((char)(Handle)) ;
    return GetAckResStr(StringIn) ;
}
//*****************************************************************************************************
void PicasoSerial::blitComtoDisplay(word  X, word  Y, word  Width, word  Height, t4DByteArray  Pixels)
{
    myVirtualPort->print((char)(F_blitComtoDisplay >> 8)) ;
    myVirtualPort->print((char)(F_blitComtoDisplay)) ;
    myVirtualPort->print((char)(X >> 8)) ;
    myVirtualPort->print((char)(X)) ;
    myVirtualPort->print((char)(Y >> 8)) ;
    myVirtualPort->print((char)(Y)) ;
    myVirtualPort->print((char)(Width >> 8)) ;
    myVirtualPort->print((char)(Width)) ;
    myVirtualPort->print((char)(Height >> 8)) ;
    myVirtualPort->print((char)(Height)) ;
    WriteBytes(Pixels, Width*Height*2) ;
    GetAck() ;
}
//**********************************************************************
word PicasoSerial::file_FindFirstRet(char *  Filename, char *  StringIn)
{
    myVirtualPort->print((char)(F_file_FindFirstRet >> 8)) ;
    myVirtualPort->print((char)(F_file_FindFirstRet)) ;
    WriteChars(Filename) ;
    return GetAckResStr(StringIn) ;
}
//***************************************************
word PicasoSerial::file_FindNextRet(char *  StringIn)
{
    myVirtualPort->print((char)(F_file_FindNextRet >> 8)) ;
    myVirtualPort->print((char)(F_file_FindNextRet)) ;
    return GetAckResStr(StringIn) ;
}
//*******************************************
void PicasoSerial::setbaudWait(word  Newrate)
{
    myVirtualPort->print((char)(F_setbaudWait >> 8));
    myVirtualPort->print((char)(F_setbaudWait));
    myVirtualPort->print((char)(Newrate >> 8));
    myVirtualPort->print((char)(Newrate));
    SetThisBaudrate(Newrate); // change this systems baud rate to match new display rate, ACK is 100ms away
    GetAck() ;
}
//********************************************
