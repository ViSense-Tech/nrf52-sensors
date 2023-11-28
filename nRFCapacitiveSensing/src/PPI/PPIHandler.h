/**
 * @file    : PPIHandler.h
 * @brief   : File containing functions related to PPI
 * @author  : Adhil
 * @date    : 09-11-2023
 * @note 
*/

/***************************************INCLUDES*********************************/
#include <helpers/nrfx_gppi.h>
#if defined(DPPI_PRESENT)
#include <nrfx_dppi.h>
#else
#include <nrfx_ppi.h>
#endif
/***************************************MACROS**********************************/

/***************************************TYPEDEFS*********************************/

/***************************************GLOBALS*********************************/

/***************************************FUNCTION DECLARTAION*********************/
bool InitPPI();
bool EnablePPIChannels();
