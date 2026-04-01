/*******************************************************************************
 ************************* File Description Start ******************************
 ******************************************************************************/
/**
 * @addtogroup MAX22190
 * @{
 * @file        MAX22910_reg_structs.h
 * @brief       This file contains the necessary register structs and enums for
 *              initializing and managing the MAX22910 digital serializer.
 *
 * @details     The MAX22910 is a serializer that communicates over SPI. This header
 *              defines register addresses and offsets required for communication.
 *
 * @version     V0.1
 * @date        24/04/2024 23:03:00
 * @since       V0.1 - Initial version of the MAX22910_reg_structs.
 *
 * @author      Chetan S Harihar
 *
 * @bug         No known issues.
 * @warning
 * @note        This file is specific to MAX22910 and should not be reused for other serializers.
 * @todo
 * @copyright   © 2024 Your Company Name. All rights reserved.
 *
 */
 /******************************************************************************
 ************************** File Description End *******************************
 ******************************************************************************/

/*******************************************************************************
 *************************** Header Guard Start ********************************
 ******************************************************************************/
#ifndef MAX22190_REG_STRUCTS_H_
#define MAX22190_REG_STRUCTS_H_

/*******************************************************************************
 **************************** Private Includes *********************************
 ******************************************************************************/

/*******************************************************************************
 ********************************* Macros **************************************
 ******************************************************************************/

/*******************************************************************************
 **************************** Type Definitions *********************************
 ******************************************************************************/

typedef enum {
    // Individual Channel Enable Masks (same as before for completeness)
    MAX22190_CHANNEL_IN1_EN = (1 << 0), // Enables IN1 (CH0) - 0x01
    MAX22190_CHANNEL_IN2_EN = (1 << 1), // Enables IN2 (CH1) - 0x02
    MAX22190_CHANNEL_IN3_EN = (1 << 2), // Enables IN3 (CH2) - 0x04
    MAX22190_CHANNEL_IN4_EN = (1 << 3), // Enables IN4 (CH3) - 0x08
    MAX22190_CHANNEL_IN5_EN = (1 << 4), // Enables IN5 (CH4) - 0x10
    MAX22190_CHANNEL_IN6_EN = (1 << 5), // Enables IN6 (CH5) - 0x20
    MAX22190_CHANNEL_IN7_EN = (1 << 6), // Enables IN7 (CH6) - 0x40
    MAX22190_CHANNEL_IN8_EN = (1 << 7), // Enables IN8 (CH7) - 0x80

    // Common Configuration Masks
    MAX22190_ENABLE_ALL_CHANNELS   = 0xFF, // All channels IN1-IN8 enabled
    MAX22190_DISABLE_ALL_CHANNELS    = 0x00  // All channels IN1-IN8 disabled
} MAX22190_Channel_Config_Mask;

/*Data Types Related to MAX22190 FLTx Registers*/
/**
 * @enum FLTx_DELAY_e
 * @brief Enum represents different filter delay values for the filtering mechanism.
 *
 */
typedef enum
{
	FILTER_DELAY_50us    = 0,  /*!< 50 microseconds delay */
	FILTER_DELAY_100us   = 1,  /*!< 100 microseconds delay */
	FILTER_DELAY_400us   = 2,  /*!< 400 microseconds delay */
	FILTER_DELAY_800us   = 3,  /*!< 800 microseconds delay */
	FILTER_DELAY_1600us  = 4,  /*!< 1600 microseconds delay */
	FILTER_DELAY_3200us  = 5,  /*!< 3200 microseconds delay */
	FILTER_DELAY_12800us = 6,  /*!< 12800 microseconds delay */
	FILTER_DELAY_20000us = 7   /*!< 20000 microseconds delay */
} MAX22190_FLTx_DELAY_e;

/**
 * @enum FLTx_FBP_e
 * @brief  Enum defines the configuration for the input filtering mechanism.
 *          It specifies whether to use or bypass the filter in a particular system or component.
 */
typedef enum
{
	USE_IN_FLT = 0, BYPASS_IN_FLT = 1
} MAX22190_FLTx_FBP_e;


/**
 * @enum FLTx_WBE_e
 * @brief  Enum defines the configuration for enabling or disabling the wire break detection.
 *
 */
typedef enum
{
	WIRE_BREAK_DISABLED = 0, WIRE_BREAK_ENABLED = 1
} MAX22190_FLTx_WBE_e;

typedef enum
{
    MAX22190_WB_IN1  = (1U << 0), /**< Wire-break detected on input channel 1 */
    MAX22190_WB_IN2  = (1U << 1), /**< Wire-break detected on input channel 2 */
    MAX22190_WB_IN3  = (1U << 2), /**< Wire-break detected on input channel 3 */
    MAX22190_WB_IN4  = (1U << 3), /**< Wire-break detected on input channel 4 */
    MAX22190_WB_IN5  = (1U << 4), /**< Wire-break detected on input channel 5 */
    MAX22190_WB_IN6  = (1U << 5), /**< Wire-break detected on input channel 6 */
    MAX22190_WB_IN7  = (1U << 6), /**< Wire-break detected on input channel 7 */
    MAX22190_WB_IN8  = (1U << 7)  /**< Wire-break detected on input channel 8 */
} MAX22190_WBFlags_t;

typedef enum
{
    MAX22190_FAULT1_WBG    = (1U << 0), /**< Wire-break group (OR of WB[7:0]) */
    MAX22190_FAULT1_24VM   = (1U << 1), /**< 24V supply missing */
    MAX22190_FAULT1_24VL   = (1U << 2), /**< 24V supply low */
    MAX22190_FAULT1_ALRMT1 = (1U << 3), /**< Temperature alarm 1 threshold exceeded */
    MAX22190_FAULT1_ALRMT2 = (1U << 4), /**< Temperature alarm 2 threshold exceeded */
    MAX22190_FAULT1_FAULT2 = (1U << 5), /**< FAULT2 summary flag */
    MAX22190_FAULT1_POR    = (1U << 6), /**< Power-on-reset occurred (write 0 to clear) */
    MAX22190_FAULT1_CRC    = (1U << 7)  /**< SPI CRC error detected */
} MAX22190_FAULT1Flags_t;

typedef enum
{
    MAX22190_FAULT2_RFWBS    = (1U << 0), /**< REFWB short detected */
    MAX22190_FAULT2_RFWBO    = (1U << 1), /**< REFWB open detected */
    MAX22190_FAULT2_RFDIS    = (1U << 2), /**< REFDI short detected */
    MAX22190_FAULT2_RFDIO    = (1U << 3), /**< REFDI open detected */
    MAX22190_FAULT2_OTSHDN   = (1U << 4), /**< Over-temperature shutdown */
    MAX22190_FAULT2_FAULT8CK = (1U << 5)  /**< SPI clock count not a multiple of 8 */
} MAX22190_FAULT2Flags_t;

/**
 * @union WIRE_BREAK_u
 * @brief The WIRE_BREAK_u is a union that provides access to the Wire Break status information.
 *        It allows the status to be accessed either as a single byte (dataByte) or as
 *        individual fields defined by the WIRE_BREAK_s structure.
 *
 */
typedef union {
	struct {
		uint8_t WB_0 :1;
		uint8_t WB_1 :1;
		uint8_t WB_2 :1;
		uint8_t WB_3 :1;
		uint8_t WB_4 :1;
		uint8_t WB_5 :1;
		uint8_t WB_6 :1;
		uint8_t WB_7 :1;
	} bits;
	uint8_t dataByte;
} MAX22190_WB_REG_u;

/**
 * @union  DIGITAL_INPUT_u
 * @brief DIGITAL_INPUT_u is a union that provides access to the digital input status information.
 *        It allows the status to be accessed either as a single byte (dataByte) or as
 *        individual fields defined by the DIGITAL_INPUT_s structure.
 */
typedef union {
	struct {
		uint8_t DI_0 :1;
		uint8_t DI_1 :1;
		uint8_t DI_2 :1;
		uint8_t DI_3 :1;
		uint8_t DI_4 :1;
		uint8_t DI_5 :1;
		uint8_t DI_6 :1;
		uint8_t DI_7 :1;
	} bits;
	uint8_t dataByte;
} MAX22190_DI_REG_u;

/**
 * @union  FAULT_1_EN_u
 * @brief FAULT_1_EN_u is a union that provides access to the fault enable status information.
 *        It allows the fault enable status to be accessed either as a single byte (dataByte)
 *        or as individual fields defined by the FAULT_1_EN_s structure.
 */
typedef union {
	struct {
		uint8_t WBG_EN :1;
		uint8_t VM_24_EN :1;
		uint8_t VL_24_EN :1;
		uint8_t ALRMT1_EN :1;
		uint8_t ALRMT2_EN :1;
		uint8_t FAULT2_EN :1;
		uint8_t POR_FAULT_EN :1;
		uint8_t CRC_FAULT_EN :1;
	} bits;
	uint8_t dataByte;
} MAX22190_FAULT1EN_REG_u;

/**
 * @union  FAULT_1_u
 * @brief FAULT_1_u is a union that provides access to the fault status information.
 *        It allows the fault status to be accessed either as a single byte (dataByte)
 *        or as individual fields defined by the FAULT_1_s structure.
 */
typedef union {
	struct {
		uint8_t WBG :1;
		uint8_t VM_24 :1;
		uint8_t VL_24 :1;
		uint8_t ALRMT1 :1;
		uint8_t ALRMT2 :1;
		uint8_t FAULT2 :1;
		uint8_t POR_FAULT :1;
		uint8_t CRC_FAULT :1;
	} bits;
	uint8_t dataByte;
} MAX22190_FAULT1_REG_u;

/**
 * @union  FAULT_2_EN_u
 * @brief FAULT_2_EN_u is a union that provides access to the fault 2 enable status information.
 *        It allows the fault 2 enable status to be accessed either as a single byte (dataByte)
 *        or as individual fields defined by the FAULT_2_EN_s structure.
 *
 */
typedef union {
	struct {
		uint8_t RFWBS_EN :1;
		uint8_t RFWBO_EN :1;
		uint8_t RFDIS_EN :1;
		uint8_t RFDIO_EN :1;
		uint8_t OTSHDN_EN :1;
		uint8_t FAULT8CK_EN :1;
		uint8_t RESERVED :2;
	} bits;
	uint8_t dataByte;
} MAX22190_FAULT2EN_REG_u;

typedef union {
	struct {
		uint8_t RFWBS :1;
		uint8_t RFWBO :1;
		uint8_t RFDIS :1;
		uint8_t RFDIO :1;
		uint8_t OTSHDN :1;
		uint8_t FAULT8CK :1;
		uint8_t RESERVED :2;
	} bits;
	uint8_t dataByte;
} MAX22190_FAULT2_REG_u;

/**
 * @union  FLTx_u
 * @brief FLTx_u union  provides access to the FLTx status information.
 *        It allows the status to be accessed either as a single byte
 *        or as individual fields defined by the FLTx_s structure.
 *
 */
typedef union {
	struct {
		uint8_t DELAY :3;
		uint8_t FBP :1;
		uint8_t WBE :1;
		uint8_t RESERVED :3;
	} bits;
	uint8_t dataByte;
} MAX22190_FLTx_REG_u;

/**
 * @union  CFG_u
 * @brief CFG_u is a union that provides access to the configuration status information.
 *        It allows the configuration status to be accessed either as a single byte (dataByte)
 *        or as individual fields defined by the CFG_s structure.
 */
typedef union {
	struct {
		uint8_t REFDI_SH_ENA :1;
		uint8_t RESERVED_1 :2;
		uint8_t CLRF :1;
		uint8_t VF_24 :1;
		uint8_t RESERVED_2 :3;
	} bits;
	uint8_t dataByte;
} MAX22190_CFG_REG_u;

typedef union {
	struct {
		uint8_t IN_0 :1;
		uint8_t IN_1 :1;
		uint8_t IN_2 :1;
		uint8_t IN_3 :1;
		uint8_t IN_4 :1;
		uint8_t IN_5 :1;
		uint8_t IN_6 :1;
		uint8_t IN_7 :1;
	} bits;
	uint8_t dataByte;
} MAX22190_INEN_REG_u;

/**
 * @union MAX22190_GPO_u
 * @brief
 *
 */
typedef union {
	struct {
		uint8_t RESERVED :7;
		uint8_t STK :1;
	} bits;
	uint8_t dataByte;
} MAX22190_GPO_REG_u;

/**
 * @struct MAX22190_Registers_s
 * @brief convenient grouping of commonly used registers.
 *
 */
typedef struct {
	MAX22190_WB_REG_u         WB;
	MAX22190_FAULT1_REG_u     FAULT1;
	MAX22190_FAULT2_REG_u     FAULT2;
} MAX22190_Registers_s;

/*******************************************************************************
 *********************** Global Variable Declaration ***************************
 ******************************************************************************/

/*******************************************************************************
 *********************** Static Variable Declaration ***************************
 ******************************************************************************/

/*******************************************************************************
 ******************** Function Prototypes (Declarations) ***********************
 ******************************************************************************/

/**
 * MAX22190 @}
 */

/*******************************************************************************
 *************************** Header Guard End **********************************
 ******************************************************************************/

#endif /* MAX22190_REG_STRUCTS_H_ */
