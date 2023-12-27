/**
 * @file    GPSHandler.c
 * @brief   GPS related functions are handled here
 * @author  Adhil
 * @date    14-10-2023
 * @see     GSPHandler.h
*/

/***************************INCLUDES*********************************/
#include "LCDHandler.h"
#include "SystemHandler.h"

/***************************MACROS***********************************/
#define LCD_WR_ADDR     0x4E
#define LCD_RD_ADDR     0x4F
#define LCD_DEV_ADDR    0x27

/****************************TYPEDEFS********************************/

/****************************GLOBALS*********************************/
unsigned char RS = 0;
unsigned char BackLight_State = LCD_NOBACKLIGHT;
struct device *psI2CHandle = DEVICE_DT_GET(DT_NODELABEL(i2c0));


/***************************FUNCTION DECLARATION*********************/

/*****************************FUNCTION DEFINITION***********************/
/**
 * @brief Initialise LCD
 * @param None
 * @return None
*/
void InitLCD(void) 
{
  IOExpanderWrite(0x00);
  k_msleep(30);
  WriteLCDCmd(0x03);
  k_msleep(5);
  WriteLCDCmd(0x03);
  k_msleep(5);
  WriteLCDCmd(0x03);
  k_msleep(5);
  WriteLCDCmd(LCD_RETURN_HOME);
  k_msleep(5);
  WriteLCDCmd(0x20 | (LCD_TYPE << 2));
  k_msleep(50);
  WriteLCDCmd(LCD_TURN_ON);
  k_msleep(50);
  WriteLCDCmd(LCD_CLEAR);
  k_msleep(50);
  WriteLCDCmd(LCD_ENTRY_MODE_SET | LCD_RETURN_HOME);
  k_msleep(50);
  Backlight();
}

/**
 * @brief Write to IO expander of LCD
 * @param Data : byte to write
 * @return None
*/
void IOExpanderWrite(unsigned char Data) 
{
    uint32_t *pDiagData = NULL;
    pDiagData = GetDiagnosticData();
    if (!device_is_ready(psI2CHandle))
    {
        printk("Error: I2C not ready\n");
        return;
    }

    Data = Data | LCD_BACKLIGHT;
   if(i2c_write(psI2CHandle, &Data, 1, LCD_DEV_ADDR)) 
   {
      printk("Error: I2C write failed\n");
     *pDiagData = *pDiagData | LCD_WRITE_FAILED; 
   } 
   else 
   {
      *pDiagData = *pDiagData & LCD_WRITE_OK; 
   }                          
}

/**
 * @brief write bytes as upper and lower nibbles to LCD
 * @param Nibble : byte to write
 * @param RS     : To switch between data and command
 * @return None
*/
void WriteNibbleToLCD(unsigned char Nibble, unsigned char RS) 
{
  // Get The RS Value To LSB OF Data  
  Nibble |= RS;
  IOExpanderWrite(Nibble | 0x04);
  IOExpanderWrite(Nibble & 0xFB);
  k_usleep(10);
}

/**
 * @brief Write command to LCD
 * @param CMD : Command to LCD
 * @return : None
*/
void WriteLCDCmd(unsigned char CMD) 
{
  RS = 0; // Command Register Select
  WriteNibbleToLCD(CMD & 0xF0, RS);
  WriteNibbleToLCD((CMD << 4) & 0xF0, RS);
}

/**
 * @brief Write character to LCD
 * @param Data : Single byte to write
 * @param None
*/
void WriteCharacterToLCD(char Data)
{
  RS = 1;  // Data Register Select
  WriteNibbleToLCD(Data & 0xF0, RS);
  WriteNibbleToLCD((Data << 4) & 0xF0, RS);
}

/**
 * @brief Write string to LCD
 * @param Str : String to write
 * @return None
*/
void WriteStringToLCD(char* Str)
{
  int i;
    for(i=0; Str[i]!='\0'; i++)
       WriteCharacterToLCD(Str[i]); 
}

/**
 * @brief Set LCD cursor position
 * @param ROW : Row position of LCD
 * @param COL : Colum position of LCD
 * @return None
*/
void SetLCDCursor(unsigned char ROW, unsigned char COL) 
{    
  switch(ROW) 
  {
    case 2:
      WriteLCDCmd(0xC0 + COL-1);
      break;
    case 3:
      WriteLCDCmd(0x94 + COL-1);
      break;
    case 4:
      WriteLCDCmd(0xD4 + COL-1);
      break;
    // Case 1  
    default:
      WriteLCDCmd(0x80 + COL-1);
  }
}

/**
 * @brief Enable backlight command
 * @param None
 * @return None
*/
void Backlight() 
{
  BackLight_State = LCD_BACKLIGHT;
  IOExpanderWrite(0);
}

/**
 * @brief Disable backlight command
 * @param None
 * @return None
*/
void noBacklight() 
{
  BackLight_State = LCD_NOBACKLIGHT;
  IOExpanderWrite(0);
}

/**
 * @brief Clear LCD display
 * @param None
 * @return None
*/
void ClearLCD()
{
  WriteLCDCmd(0x01); 
  k_usleep(40);
}

/**
 * @brief Get I2C handle
 * @param None
 * @return I2C handle
*/
struct device *GetI2CDevice()
{
  if (psI2CHandle)
  {
      return psI2CHandle;
  }
  else
  {
    return NULL;
  }
}