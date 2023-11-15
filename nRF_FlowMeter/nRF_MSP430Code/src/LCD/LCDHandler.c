// /**
//  * @file    GPSHandler.c
//  * @brief   GPS related functions are handled here
//  * @author  Adhil
//  * @date    14-10-2023
//  * @see     GSPHandler.h
// */

// /***************************INCLUDES*********************************/
// #include "LCDHandler.h"

// /***************************MACROS***********************************/
// #define LCD_WR_ADDR     0x4E
// #define LCD_RD_ADDR     0x4F
// #define LCD_DEV_ADDR    0x27

// /****************************TYPEDEFS********************************/

// /****************************GLOBALS*********************************/
// static const struct device *psI2CHandle = DEVICE_DT_GET(DT_NODELABEL(i2c0));
// unsigned char RS = 0;
// unsigned char BackLight_State = LCD_NOBACKLIGHT;

// /***************************FUNCTION DECLARATION*********************/

// /*****************************FUNCTION DEFINITION***********************/

// void InitLCD(void) 
// {
//   IOExpanderWrite(0x00);
//   k_msleep(30);
//   WriteLCDCmd(0x03);
//   k_msleep(5);
//   WriteLCDCmd(0x03);
//   k_msleep(5);
//   WriteLCDCmd(0x03);
//   k_msleep(5);
//   WriteLCDCmd(LCD_RETURN_HOME);
//   k_msleep(5);
//   WriteLCDCmd(0x20 | (LCD_TYPE << 2));
//   k_msleep(50);
//   WriteLCDCmd(LCD_TURN_ON);
//   k_msleep(50);
//   WriteLCDCmd(LCD_CLEAR);
//   k_msleep(50);
//   WriteLCDCmd(LCD_ENTRY_MODE_SET | LCD_RETURN_HOME);
//   k_msleep(50);
//   Backlight();
// }

// void IOExpanderWrite(unsigned char Data) 
// {

//     if (!device_is_ready(psI2CHandle))
//     {
//         printk("Error: I2C not ready\n");
//         return;
//     }

//     Data = Data | LCD_BACKLIGHT;
//     i2c_write(psI2CHandle, &Data, 1, LCD_DEV_ADDR);
// }

// void WriteNibbleToLCD(unsigned char Nibble, unsigned char RS) 
// {
//   // Get The RS Value To LSB OF Data  
//   Nibble |= RS;
//   IOExpanderWrite(Nibble | 0x04);
//   IOExpanderWrite(Nibble & 0xFB);
//   k_usleep(50);
// }

// void WriteLCDCmd(unsigned char CMD) 
// {
//   RS = 0; // Command Register Select
//   WriteNibbleToLCD(CMD & 0xF0, RS);
//   WriteNibbleToLCD((CMD << 4) & 0xF0, RS);
// }

// void WriteCharacterToLCD(char Data)
// {
//   RS = 1;  // Data Register Select
//   WriteNibbleToLCD(Data & 0xF0, RS);
//   WriteNibbleToLCD((Data << 4) & 0xF0, RS);
// }

// void WriteStringToLCD(char* Str)
// {
//     for(int i=0; Str[i]!='\0'; i++)
//        WriteCharacterToLCD(Str[i]); 
// }

// void SetLCDCursor(unsigned char ROW, unsigned char COL) 
// {    
//   switch(ROW) 
//   {
//     case 2:
//       WriteLCDCmd(0xC0 + COL-1);
//       break;
//     case 3:
//       WriteLCDCmd(0x94 + COL-1);
//       break;
//     case 4:
//       WriteLCDCmd(0xD4 + COL-1);
//       break;
//     // Case 1  
//     default:
//       WriteLCDCmd(0x80 + COL-1);
//   }
// }

// void Backlight() 
// {
//   BackLight_State = LCD_BACKLIGHT;
//   IOExpanderWrite(0);
// }

// void noBacklight() 
// {
//   BackLight_State = LCD_NOBACKLIGHT;
//   IOExpanderWrite(0);
// }


// void ClearLCD()
// {
//   WriteLCDCmd(0x01); 
//   k_usleep(40);
// }


// struct device *GetI2CDevice()
// {
//   if (psI2CHandle)
//   {
//       return psI2CHandle;
//   }
// }