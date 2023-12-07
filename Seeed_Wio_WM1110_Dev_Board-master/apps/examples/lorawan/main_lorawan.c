
#if 1

/*!

* @file      main_lorawan.c

*

* @brief     LoRa Basics Modem Class A/C device implementation

*

* @copyright

* The Clear BSD License

* Copyright Semtech Corporation 2021. All rights reserved.

*

* Redistribution and use in source and binary forms, with or without

* modification, are permitted (subject to the limitations in the disclaimer

* below) provided that the following conditions are met:

*     * Redistributions of source code must retain the above copyright

*       notice, this list of conditions and the following disclaimer.

*     * Redistributions in binary form must reproduce the above copyright

*       notice, this list of conditions and the following disclaimer in the

*       documentation and/or other materials provided with the distribution.

*     * Neither the name of the Semtech corporation nor the

*       names of its contributors may be used to endorse or promote products

*       derived from this software without specific prior written permission.

*

* NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY

* THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND

* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT

* NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A

* PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SEMTECH CORPORATION BE

* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR

* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF

* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS

* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN

* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)

* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE

* POSSIBILITY OF SUCH DAMAGE.

*/
 
/*

* -----------------------------------------------------------------------------

* --- DEPENDENCIES ------------------------------------------------------------

*/
 
#include "main_lorawan.h"

#include "lorawan_key_config.h"

#include "smtc_board.h"

#include "smtc_hal.h"

#include "apps_modem_common.h"

#include "apps_modem_event.h"

#include "smtc_modem_api.h"

#include "device_management_defs.h"

#include "smtc_board_ralf.h"

#include "apps_utilities.h"

#include "smtc_modem_utilities.h"

#include "ral.h"

#include "lr11xx_radio.h"

#include "lr11xx_regmem.h"

#include "lr11xx_radio_types.h"

#include "smtc_shield_lr11xx_common_if.h"

#include "lr11xx_system_types.h"

#include "lr11xx_system.h"

#include "lr11xx_hal_context.h"

#include "modem_pinout.h"
#include "lr11xx_lr_fhss.h"

 
 
/*

* -----------------------------------------------------------------------------

* --- PRIVATE MACROS-----------------------------------------------------------

*/

#ifndef RF_FREQ_IN_HZ

#define RF_FREQ_IN_HZ 490000000U

#endif

#ifndef TX_OUTPUT_POWER_DBM

#define TX_OUTPUT_POWER_DBM 13  // range [-17, +22] for sub-G, range [-18, 13] for 2.4G ( HF_PA )

#endif
 
#ifndef PA_RAMP_TIME

#define PA_RAMP_TIME LR11XX_RADIO_RAMP_48_US

#endif

#ifndef FALLBACK_MODE

#define FALLBACK_MODE LR11XX_RADIO_FALLBACK_STDBY_RC

#endif

#ifndef ENABLE_RX_BOOST_MODE

#define ENABLE_RX_BOOST_MODE false

#endif

#ifndef PAYLOAD_LENGTH

#define PAYLOAD_LENGTH 7

#endif

#ifndef PACKET_TYPE

#define PACKET_TYPE LR11XX_RADIO_PKT_TYPE_LORA

#endif
 
#define FREQUENCY 868100000
 
#ifndef RECEIVER

#define RECEIVER 1

#endif
 
/**

* @brief LR11xx interrupt mask used by the application

*/

#define IRQ_MASK ( LR11XX_SYSTEM_IRQ_TX_DONE | LR11XX_SYSTEM_IRQ_RX_DONE | LR11XX_SYSTEM_IRQ_TIMEOUT | LR11XX_SYSTEM_IRQ_PREAMBLE_DETECTED | LR11XX_SYSTEM_IRQ_HEADER_ERROR | LR11XX_SYSTEM_IRQ_FSK_LEN_ERROR |  LR11XX_SYSTEM_IRQ_CRC_ERROR )
 
/*!

* @brief Spreading factor for test mode \see smtc_modem_test_sf_t

*/

#define SPREADING_FACTOR_USED SMTC_MODEM_TEST_LORA_SF7
 
/*!

* @brief bandwidth for test mode \see smtc_modem_test_bw_t

*/

#define BANDWIDTH_USED SMTC_MODEM_TEST_BW_125_KHZ
 
/*!

* @brief Coding rate for test mode \see smtc_modem_test_cr_t

*/

#define CODING_RATE_USED SMTC_MODEM_TEST_CR_4_5
 
/*!

* @brief Stringify constants

*/

#define xstr( a ) str( a )

#define str( a ) #a
 
/*

* -----------------------------------------------------------------------------

* --- PRIVATE CONSTANTS -------------------------------------------------------

*/
 
/*

* -----------------------------------------------------------------------------

* --- PRIVATE TYPES -----------------------------------------------------------

*/ 

lr11xx_radio_mod_params_lora_t lora_mod_params = {

     .sf = LR11XX_RADIO_LORA_SF7,

     .bw = LR11XX_RADIO_LORA_BW_125,

     .cr = LR11XX_RADIO_LORA_CR_4_5,

     .ldro = 0,

};

lr11xx_radio_pkt_params_lora_t lora_pkt_params = {

    .preamble_len_in_symb = 8,

    .header_type          = LR11XX_RADIO_LORA_PKT_EXPLICIT,

    .pld_len_in_bytes     = PAYLOAD_LENGTH,

    .crc                  = LR11XX_RADIO_LORA_CRC_ON,

    .iq                   = LR11XX_RADIO_LORA_IQ_INVERTED,

};

/*

* -----------------------------------------------------------------------------

* --- PRIVATE VARIABLES -------------------------------------------------------

*/

const uint8_t *uSampleBuf = "First Lora Message";

uint8_t uSampleRxBuf[LORAWAN_APP_DATA_MAX_SIZE] = {0};
 
 
static volatile bool irq_fired = false;
 
static uint32_t rx_timeout = 1000;
 
static lr11xx_hal_context_t context = {

    .nss    = SMTC_RADIO_NSS,

    .busy   = SMTC_RADIO_BUSY,

    .reset  = SMTC_RADIO_NRST,

    .spi_id = 3,

};

/*!

* @brief Stack identifier

*/

static uint8_t stack_id = 0;
 
static uint8_t buffer[7];
 
static uint16_t per_index      = 0;
 
static uint16_t nb_ok            = 0;

/*!

* @brief User application data

*/

static uint8_t app_data_buffer[LORAWAN_APP_DATA_MAX_SIZE];
 
/*

* -----------------------------------------------------------------------------

* --- PRIVATE FUNCTIONS DECLARATION -------------------------------------------

*/

#if 1

bool SendLoRaPayload(const void *pContext, const uint8_t *upBuffer, const uint8_t uLen);

bool WriteNxtBufToRegMeM(const void *ctx, const uint8_t *upBuf, const uint8_t uLen);

bool ReadBufFromRegMem(const void *ctx, const uint8_t *upBuf, const uint8_t uLen, uint8_t *RxDataSize);
 
bool InitLoRaSystem(const void *context);

bool LoraRadioInit(const void *context);
 
void lr11xxIrqProcess(const void *context, lr11xx_system_irq_mask_t);
 
void radio_on_dio_irq( void* context );
 
void testing(void);
 
void  almanac_update( smtc_modem_event_almanac_update_status_t status );
 
void join_fail( void );
 
void link_status( smtc_modem_event_link_check_status_t status, uint8_t margin, uint8_t gw_cnt );
 
void mute( smtc_modem_event_mute_status_t status );
 
void new_link_adr( void );
 
void set_conf( smtc_modem_event_setconf_tag_t tag );
 
void stream_done ( void );
 
void time_updated_alc_sync ( smtc_modem_event_time_status_t status );
 
void upload_done( smtc_modem_event_uploaddone_status_t status );
 
#endif

/*!

* @brief   Send an application frame on LoRaWAN port defined by LORAWAN_APP_PORT

*

* @param [in] buffer     Buffer containing the LoRaWAN buffer

* @param [in] length     Payload length

* @param [in] confirmed  Send a confirmed or unconfirmed uplink [false : unconfirmed / true : confirmed]

*/

static void send_frame( const uint8_t* buffer, const uint8_t length, const bool confirmed );
 
/*!

* @brief Parse the received downlink

*

* @remark Demonstrates how a TLV-encoded command sequence received by downlink can control the state of an LED. It can

* easily be extended to handle other commands received on the same port or another port.

*

* @param [in] port LoRaWAN port

* @param [in] payload Payload Buffer

* @param [in] size Payload size

*/

static void parse_downlink_frame( uint8_t port, const uint8_t* payload, uint8_t size );
 
/*!

* @brief Reset event callback

*

* @param [in] reset_count reset counter from the modem

*/

static void on_modem_reset( uint16_t reset_count );
 
/*!

* @brief Network Joined event callback

*/

static void on_modem_network_joined( void );
 
/*!

* @brief Alarm event callback

*/

static void on_modem_alarm( void );
 
/*!

* @brief Tx done event callback

*

* @param [in] status tx done status @ref smtc_modem_event_txdone_status_t

*/

static void on_modem_tx_done( smtc_modem_event_txdone_status_t status );
 
/*!

* @brief Downlink data event callback.

*

* @param [in] rssi       RSSI in signed value in dBm + 64

* @param [in] snr        SNR signed value in 0.25 dB steps

* @param [in] rx_window  RX window

* @param [in] port       LoRaWAN port

* @param [in] payload    Received buffer pointer

* @param [in] size       Received buffer size

*/

static void on_modem_down_data( int8_t rssi, int8_t snr, smtc_modem_event_downdata_window_t rx_window, uint8_t port,

                                const uint8_t* payload, uint8_t size );
 
/*

* -----------------------------------------------------------------------------

* --- PUBLIC FUNCTIONS DEFINITION ---------------------------------------------

*/
 
/**

* @brief Main application entry point.

*/

int main( void )

{

    uint8_t uSizeOfRxBuff = 0;
    lr11xx_system_stat1_t stat1;
    lr11xx_system_stat2_t stat2;
    lr11xx_system_irq_mask_t irq_status;
    uint16_t hop_sequence_id;

    char buf[] = "HI";

    irq_status = IRQ_MASK;

    const lr11xx_lr_fhss_params_t lr_fhss_params = {

    .lr_fhss_params.bw = LR_FHSS_V1_BW_386719_HZ,
    .lr_fhss_params.cr = LR_FHSS_V1_CR_1_2,
    .lr_fhss_params.enable_hopping = false,
    .lr_fhss_params.modulation_type = LR_FHSS_V1_MODULATION_TYPE_GMSK_488,
    .lr_fhss_params.grid = LR_FHSS_V1_GRID_3906_HZ
};

    static apps_modem_event_callback_t smtc_event_callback = {

        .adr_mobile_to_static  = testing,

        .alarm                 = on_modem_alarm,

        .almanac_update        = almanac_update,

        .down_data             = on_modem_down_data,

        .join_fail             = join_fail,

        .joined                = on_modem_network_joined,

        .link_status           = link_status,

        .mute                  = mute,

        .new_link_adr          = new_link_adr,

        .reset                 = on_modem_reset,

        .set_conf              = set_conf,

        .stream_done           = stream_done,

        .time_updated_alc_sync = time_updated_alc_sync,

        .tx_done               = on_modem_tx_done,

        .upload_done           = upload_done,

    };
    smtc_board_init_periph();
    smtc_shield_lr11xx_init();

    ralf_t *modem_radio = smtc_board_initialise_and_get_ralf();
    const lr11xx_system_reg_mode_t regulator = smtc_shield_lr11xx_get_reg_mode();
    lr11xx_system_set_reg_mode( modem_radio->ral.context, regulator );

    const lr11xx_system_rfswitch_cfg_t rf_switch_setup = smtc_shield_lr11xx_get_rf_switch_cfg( );
    lr11xx_system_set_dio_as_rf_switch( modem_radio->ral.context, &rf_switch_setup );

    const smtc_shield_lr11xx_pa_pwr_cfg_t* pa_pwr_cfg = smtc_shield_lr11xx_get_pa_pwr_cfg(RF_FREQ_IN_HZ, TX_OUTPUT_POWER_DBM );
 
    if( lr11xx_radio_set_tx_params( modem_radio->ral.context, pa_pwr_cfg->power, PA_RAMP_TIME ) )
    {
 
        printf("Failed to set TX params");
 
    }

      lr11xx_lr_fhss_init(modem_radio->ral.context);
    lr11xx_radio_set_pkt_type( modem_radio->ral.context, PACKET_TYPE );
    lr11xx_radio_set_rf_freq( modem_radio->ral.context, RF_FREQ_IN_HZ );

    //lr11xx_radio_set_pa_cfg( modem_radio->ral.context, &( pa_pwr_cfg->pa_config ));

    //lr11xx_radio_set_tx_params( modem_radio->ral.context, pa_pwr_cfg->power, PA_RAMP_TIME );

    lr11xx_lr_fhss_build_frame(modem_radio->ral.context, &lr_fhss_params, 0, buf, sizeof(buf));

    //lr11xx_radio_set_lora_mod_params( modem_radio->ral.context, &lora_mod_params );
    //lr11xx_radio_set_lora_pkt_params( modem_radio->ral.context, &lora_pkt_params );

    lr11xx_system_set_dio_irq_params(modem_radio->ral.context, IRQ_MASK, 0 );

    if(lr11xx_system_get_status(modem_radio->ral.context, &stat1, &stat2, &irq_status))
    {
        printf("System get status failed");
    }
    printf("status : %d, status 2 : %d, irq_status %d, ",stat1,stat2,irq_status);
    lr11xx_radio_set_tx( modem_radio->ral.context, 0 );



}
 
/*

* -----------------------------------------------------------------------------

* --- PRIVATE FUNCTIONS DEFINITION --------------------------------------------

*/
 
static void on_modem_reset( uint16_t reset_count )

{

    printf( "Application parameters:\n" );

    printf( "  - LoRaWAN uplink Fport = %d\n", LORAWAN_APP_PORT );

    printf( "  - DM report interval   = %d\n", APP_TX_DUTYCYCLE );

    printf( "  - Confirmed uplink     = %s\n", ( LORAWAN_CONFIRMED_MSG_ON == true ) ? "Yes" : "No" );
 
    apps_modem_common_configure_lorawan_params( stack_id );
 
    ASSERT_SMTC_MODEM_RC( smtc_modem_join_network( stack_id ) );

}
 
static void on_modem_network_joined( void )

{

    ASSERT_SMTC_MODEM_RC( smtc_modem_alarm_start_timer( APP_TX_DUTYCYCLE ) );
 
    ASSERT_SMTC_MODEM_RC( smtc_modem_adr_set_profile( stack_id, LORAWAN_DEFAULT_DATARATE, adr_custom_list ) );

}
 
static void on_modem_alarm( void )

{

    smtc_modem_status_mask_t modem_status;

    uint32_t                 charge        = 0;

    uint8_t                  app_data_size = 0;
 
    /* Schedule next packet transmission */

    ASSERT_SMTC_MODEM_RC( smtc_modem_alarm_start_timer( APP_TX_DUTYCYCLE ) );

    printf( "smtc_modem_alarm_start_timer: %d s\n\n", APP_TX_DUTYCYCLE );
 
    ASSERT_SMTC_MODEM_RC( smtc_modem_get_status( stack_id, &modem_status ) );

    modem_status_to_string( modem_status );
 
    ASSERT_SMTC_MODEM_RC( smtc_modem_get_charge( &charge ) );
 
    app_data_buffer[app_data_size++] = ( uint8_t ) ( charge );

    app_data_buffer[app_data_size++] = ( uint8_t ) ( charge >> 8 );

    app_data_buffer[app_data_size++] = ( uint8_t ) ( charge >> 16 );

    app_data_buffer[app_data_size++] = ( uint8_t ) ( charge >> 24 );
 
    //send_frame( app_data_buffer, app_data_size, LORAWAN_CONFIRMED_MSG_ON );

}
 
static void on_modem_tx_done( smtc_modem_event_txdone_status_t status )

{

    static uint32_t uplink_count = 0;
 
    printf( "Uplink count: %d\n", ++uplink_count );

}
 
static void on_modem_down_data( int8_t rssi, int8_t snr, smtc_modem_event_downdata_window_t rx_window, uint8_t port,

                                const uint8_t* payload, uint8_t size )

{

    printf( "Downlink received:\n" );

    printf( "  - LoRaWAN Fport = %d\n", port );

    printf( "  - Payload size  = %d\n", size );

    printf( "  - RSSI          = %d dBm\n", rssi - 64 );

    printf( "  - SNR           = %d dB\n", snr >> 2 );
 
    switch( rx_window )

    {

    case SMTC_MODEM_EVENT_DOWNDATA_WINDOW_RX1:

    {

        printf( "  - Rx window     = %s\n", xstr( SMTC_MODEM_EVENT_DOWNDATA_WINDOW_RX1 ) );

        break;

    }

    case SMTC_MODEM_EVENT_DOWNDATA_WINDOW_RX2:

    {

        printf( "  - Rx window     = %s\n", xstr( SMTC_MODEM_EVENT_DOWNDATA_WINDOW_RX2 ) );

        break;

    }

    case SMTC_MODEM_EVENT_DOWNDATA_WINDOW_RXC:

    {

        printf( "  - Rx window     = %s\n", xstr( SMTC_MODEM_EVENT_DOWNDATA_WINDOW_RXC ) );

        break;

    }

    }
 
    if( size != 0 )

    {

        HAL_DBG_TRACE_ARRAY( "Payload", payload, size );

    }

}
 
static void send_frame( const uint8_t* buffer, const uint8_t length, bool tx_confirmed )

{

    uint8_t tx_max_payload;

    int32_t duty_cycle;
 
    /* Check if duty cycle is available */

    ASSERT_SMTC_MODEM_RC( smtc_modem_get_duty_cycle_status( &duty_cycle ) );

    if( duty_cycle < 0 )

    {

        printf( "Duty-cycle limitation - next possible uplink in %d ms \n\n", duty_cycle );

        return;

    }
 
    ASSERT_SMTC_MODEM_RC( smtc_modem_get_next_tx_max_payload( stack_id, &tx_max_payload ) );

    if( length > tx_max_payload )

    {

        printf( "Not enough space in buffer - send empty uplink to flush MAC commands \n" );

        ASSERT_SMTC_MODEM_RC( smtc_modem_request_empty_uplink( stack_id, true, LORAWAN_APP_PORT, tx_confirmed ) );

    }

    else

    {

        printf( "Request uplink\n" );

        ASSERT_SMTC_MODEM_RC( smtc_modem_request_uplink( stack_id, LORAWAN_APP_PORT, tx_confirmed, buffer, length ) );

    }

}
 
/* --- EOF ------------------------------------------------------------------ */
 
#endif 

//ral_lr11xx_lr_fhss_get_time_on_air_in_ms
 
 
#if 1

bool SendLoRaPayload(const void *pContext, const uint8_t *upBuffer, const uint8_t uLen)

{

    bool RetVal = false;

    lr11xx_regmem_write_buffer8(pContext, upBuffer, uLen);
 
    if(!lr11xx_radio_set_tx(pContext, 0))

    {

        printf("\n\rINFO: Send Message Success\n\r");

    }

    //WriteNxtBufToRegMeM(pContext, upBuffer, uLen);
 
 
}
 
bool WriteNxtBufToRegMeM(const void *ctx, const uint8_t *upBuf, const uint8_t uLen)

{
 
    if(lr11xx_regmem_write_buffer8(ctx, upBuf, uLen))

    {

        printf("\n\rFailed to Add buffer to a Register Memory\n\r");

    }
 
 
    if(!lr11xx_radio_set_tx(ctx, 0))

    {

        printf("\n\rINFO: Send Message Success\n\r");

    }
 
 
}
 
bool ReadBufFromRegMem(const void *ctx, const uint8_t *upBuf, const uint8_t uLen,  uint8_t *RxDataSize)

{

    bool RetVal = false;

    lr11xx_radio_rx_buffer_status_t RxBufferStatus;

    lr11xx_radio_pkt_status_lora_t  PktStatusLoRa;

    lr11xx_radio_pkt_status_gfsk_t  PktStatusGFSK;
 
    lr11xx_radio_get_rx_buffer_status( ctx, &RxBufferStatus);

    *RxDataSize = RxBufferStatus.pld_len_in_bytes;

    printf("\n\rRxDataSize: %d\n\r", RxBufferStatus.pld_len_in_bytes);
 
    if( *RxDataSize > uLen )

    {

        printf( "\n\rReceived payload (size: %d) is bigger than the buffer (size: %d)!\n", *RxDataSize,

                             uLen );

        RetVal = false;

        return RetVal;

    }

    memset(upBuf, 0, uLen);

    if(!lr11xx_regmem_read_buffer8( ctx, upBuf, RxBufferStatus.buffer_start_pointer,

                                      *RxDataSize ))

    {

        printf( "\n\rPacket content : %s\n\rPacket content size %d: \n\r", upBuf, *RxDataSize );

        RetVal = true;

    }

    else

    {

        RetVal = false;

        printf("\n\rERROR : Read Failed");

    }
 
}

bool InitLoRaSystem(const void *context)

{

    bool RetVal = false;

    uint16_t errors;
 
 
    if(lr11xx_system_reset( context ) )

    {

        printf("\n\rsystem Reset Failed\n\r");

    }
 
    const lr11xx_system_reg_mode_t regulator = smtc_shield_lr11xx_get_reg_mode();

    if(lr11xx_system_set_reg_mode(context, regulator))

    {

        printf("\n\rFailed to set sysytem regulated mode\n\r");

    }
 
    const lr11xx_system_rfswitch_cfg_t rf_switch_setup = smtc_shield_lr11xx_get_rf_switch_cfg();

    if(lr11xx_system_set_dio_as_rf_switch( context, &rf_switch_setup ))

    {

        printf("\n\rFailed to set DIO RF switch\n\r");

    }
 
    if(lr11xx_system_clear_errors( context ))

    {

        printf("\n\rFailed to clear errors\n\r");

    }

    if(lr11xx_system_calibrate( context, 0x3F ))

    {

        printf("\n\rFailed to calibrate system\n\r");

    }
 
    if(lr11xx_system_get_errors( context, &errors ))

    {

        printf("\n\rFailed to get errors\n\r");

    }
 
    if(lr11xx_system_clear_errors( context ))

    {

        printf("\n\rFailed to clear errors\n\r");

    }

}
 
bool LoraRadioInit(const void *context)

{

    bool RetVal = false;
 
 
    const smtc_shield_lr11xx_pa_pwr_cfg_t* pa_pwr_cfg =

        smtc_shield_lr11xx_get_pa_pwr_cfg(RF_FREQ_IN_HZ, TX_OUTPUT_POWER_DBM );
 
    if( pa_pwr_cfg == NULL )

    {

        printf( "\n\rInvalid target frequency or power level\n\r" );

        while( true )

        {
 
        }

     }
 
     //print_common_configuration( );
 
    if( lr11xx_radio_set_pkt_type( context, PACKET_TYPE ))

    {

        printf("Failed to set packet type");

    }
 
    if( lr11xx_radio_set_rf_freq( context, RF_FREQ_IN_HZ ) )

    {

        printf("Failed to set RF Frequency");

    }
 
    if( lr11xx_radio_set_rssi_calibration(

        context, smtc_shield_lr11xx_get_rssi_calibration_table( RF_FREQ_IN_HZ ) ) )

    {

        printf("Failed to set rssi");

    }

    if( lr11xx_radio_set_pa_cfg( context, &( pa_pwr_cfg->pa_config ) ) )

    {

        printf("Failed to set Power amplification");

    }

    if( lr11xx_radio_set_tx_params( context, pa_pwr_cfg->power, PA_RAMP_TIME ) )

    {

        printf("Failed to set TX params");

    }

    if( lr11xx_radio_set_rx_tx_fallback_mode( context, FALLBACK_MODE ) )

    {

        printf("Failed to set Chip Mode");

    }

    if( lr11xx_radio_cfg_rx_boosted( context, ENABLE_RX_BOOST_MODE ) )

    {

        printf("Failed to Set Rx cfg ");

    }
 
    if( PACKET_TYPE == LR11XX_RADIO_PKT_TYPE_LORA )

    {

        //print_lora_configuration( );

        lr11xx_status_t Ret;
 
 
        //lora_mod_params.ldro = apps_common_compute_lora_ldro( LORA_SPREADING_FACTOR, LORA_BANDWIDTH );

        Ret = lr11xx_radio_set_lora_mod_params( context, &lora_mod_params );

        if( Ret )

        {

            printf("Failed to set Modulation configuration for LoRa packet%d",Ret);

        }

        if( lr11xx_radio_set_lora_pkt_params( context, &lora_pkt_params ) )

        {

            printf("Failed to set Packet parameter configuration for LoRa packets");

        }

        if( lr11xx_radio_set_lora_sync_word( context, 0x34 ) ) //0x12 Private Network, 0x34 Public Network

        {

        }

    }

}
 
 
void lr11xxIrqProcess(const void *context, lr11xx_system_irq_mask_t irq_filter_mask)

{

    char buf[] = "Jeslin";

    if( irq_fired == true )

    {

        //irq_fired = false;
 
        lr11xx_system_irq_mask_t irq_regs;

        lr11xx_system_get_and_clear_irq_status( context, &irq_regs );
 
        //printf( "Interrupt flags = 0x%08X\n", irq_regs );
 
        irq_regs &= irq_filter_mask;
 
        //printf( "Interrupt flags (after filtering) = 0x%08X\n", irq_regs );
 
        if( ( irq_regs & LR11XX_SYSTEM_IRQ_TX_DONE ) == LR11XX_SYSTEM_IRQ_TX_DONE )

        {

            printf( "Tx done\n" );

            WriteNxtBufToRegMeM(context, buf, strlen(buf));

        }
 
        if( ( irq_regs & LR11XX_SYSTEM_IRQ_PREAMBLE_DETECTED ) == LR11XX_SYSTEM_IRQ_PREAMBLE_DETECTED )

        {

            printf( "Preamble detected\n" );

           // on_preamble_detected( );

        }
 
        if( ( irq_regs & LR11XX_SYSTEM_IRQ_HEADER_ERROR ) == LR11XX_SYSTEM_IRQ_HEADER_ERROR )

        {

            printf( "Header error\n" );

            //on_header_error( );

        }
 
        if( ( irq_regs & LR11XX_SYSTEM_IRQ_SYNC_WORD_HEADER_VALID ) == LR11XX_SYSTEM_IRQ_SYNC_WORD_HEADER_VALID )

        {

            printf( "Syncword or header valid\n" );

            //on_syncword_header_valid( );

        }
 
        if( ( irq_regs & LR11XX_SYSTEM_IRQ_RX_DONE ) == LR11XX_SYSTEM_IRQ_RX_DONE )

        {

            if( ( irq_regs & LR11XX_SYSTEM_IRQ_CRC_ERROR ) == LR11XX_SYSTEM_IRQ_CRC_ERROR )

            {

                printf( "CRC error\n" );

                //on_rx_crc_error( );

            }

            else if( ( irq_regs & LR11XX_SYSTEM_IRQ_FSK_LEN_ERROR ) == LR11XX_SYSTEM_IRQ_FSK_LEN_ERROR )

            {

                printf( "FSK length error\n" );

                //on_fsk_len_error( );

            }

            else

            {

                printf( "Rx done\n" );

               // on_rx_done( );

               uint8_t size = 0;

               ReadBufFromRegMem(context, buf, sizeof(buf), &size);

            }

        }
 
        if( ( irq_regs & LR11XX_SYSTEM_IRQ_CAD_DONE ) == LR11XX_SYSTEM_IRQ_CAD_DONE )

        {

            printf( "CAD done\n" );

            if( ( irq_regs & LR11XX_SYSTEM_IRQ_CAD_DETECTED ) == LR11XX_SYSTEM_IRQ_CAD_DETECTED )

            {

                printf( "Channel activity detected\n" );

                //on_cad_done_detected( );

            }

            else

            {

                printf( "No channel activity detected\n" );

                //on_cad_done_undetected( );

            }

        }
 
        if( ( irq_regs & LR11XX_SYSTEM_IRQ_TIMEOUT ) == LR11XX_SYSTEM_IRQ_TIMEOUT )

        {

            printf( "Rx timeout\n" );

            //on_rx_timeout( );

        }

/*

        if( ( irq_regs & LR11XX_SYSTEM_IRQ_LORA_RX_TIMESTAMP ) == LR11XX_SYSTEM_IRQ_LORA_RX_TIMESTAMP )

        {

            printf( "LoRa Rx timestamp\n" );

            //on_lora_rx_timestamp( );

        }
 
        if( ( irq_regs & LR11XX_SYSTEM_IRQ_RANGING_REQ_VALID ) == LR11XX_SYSTEM_IRQ_RANGING_REQ_VALID )

        {

            printf( "Ranging request valid\n" );

            //on_ranging_request_valid( );

        }
 
        if( ( irq_regs & LR11XX_SYSTEM_IRQ_RANGING_REQ_DISCARDED ) == LR11XX_SYSTEM_IRQ_RANGING_REQ_DISCARDED )

        {

            printf( "Ranging request discarded\n" );

            //on_ranging_request_discarded( );

        }
 
        if( ( irq_regs & LR11XX_SYSTEM_IRQ_RANGING_RESP_DONE ) == LR11XX_SYSTEM_IRQ_RANGING_RESP_DONE )

        {

            printf( "Ranging response done\n" );

            //on_ranging_response_done( );

        }
 
        if( ( irq_regs & LR11XX_SYSTEM_IRQ_RANGING_EXCH_VALID ) == LR11XX_SYSTEM_IRQ_RANGING_EXCH_VALID )

        {

            printf( "Ranging exchange valid\n" );

            //on_ranging_exchange_valid( );

        }
 
        if( ( irq_regs & LR11XX_SYSTEM_IRQ_RANGING_TIMEOUT ) == LR11XX_SYSTEM_IRQ_RANGING_TIMEOUT )

        {

            HAL_DBG_TRACE_INFO( "Ranging timeout\n" );

            //on_ranging_timeout( );

        }

*/

        if( ( irq_regs & LR11XX_SYSTEM_IRQ_WIFI_SCAN_DONE ) == LR11XX_SYSTEM_IRQ_WIFI_SCAN_DONE )

        {

            printf( "Wi-Fi scan done\n" );

            //on_wifi_scan_done( );

        }
 
        if( ( irq_regs & LR11XX_SYSTEM_IRQ_GNSS_SCAN_DONE ) == LR11XX_SYSTEM_IRQ_GNSS_SCAN_DONE )

        {

            printf( "GNSS scan done\n" );

            //on_gnss_scan_done( );

        }
 
        //printf( "\n" );

    }

}
 
void radio_on_dio_irq( void* context )

{

    irq_fired = true;

    printf("IRQ succeed");

}
 
void testing(void)

{

   printf("IRQ succeed"); 

}

void  almanac_update( smtc_modem_event_almanac_update_status_t status )

{

    printf("IRQ succeed");
 
}
 
void join_fail( void )

{

   printf("IRQ succeed"); 

}
 
void link_status( smtc_modem_event_link_check_status_t status, uint8_t margin, uint8_t gw_cnt )

{

   printf("IRQ succeed"); 

}

void mute( smtc_modem_event_mute_status_t status )

{

   printf("IRQ succeed"); 

}

void new_link_adr( void )

{

   printf("IRQ succeed");

}

void set_conf( smtc_modem_event_setconf_tag_t tag )

{

   printf("IRQ succeed"); 

}

void stream_done ( void )

{

   printf("IRQ succeed"); 

}

void time_updated_alc_sync ( smtc_modem_event_time_status_t status )

{

   printf("IRQ succeed"); 

}

void upload_done( smtc_modem_event_uploaddone_status_t status )

{

   printf("IRQ succeed"); 

}

//}
 
#endif