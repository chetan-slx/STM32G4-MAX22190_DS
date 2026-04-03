/*******************************************************************************
 ************************* File Description Start ******************************
 ******************************************************************************/
/**
 * @addtogroup MAX22190
 * @{
 * @file       MAX22190.h
 * @brief      MAX22190 - The file contains all the necessary function required to interface with the MAX22190
 * 			   serializer module.
 * Layer.
 * @author     Chetan S Harihar
 * @version    V0.1
 * @date       26/08/2025 11:24:00
 * @since
 * V0.1 - Initial Version of MAX22190 Serializer module.
 * @test
 * @bug
 * @warning
 * @note
 * @todo
 * @copyright
 *
 */
/******************************************************************************
 ************************** File Description End *******************************
 ******************************************************************************/

/*******************************************************************************
 *************************** Header Guard Start ********************************
 ******************************************************************************/
#ifndef MAX22190_H_
#define MAX22190_H_

/*******************************************************************************
 **************************** Private Includes *********************************
 ******************************************************************************/
#include "main.h"
#include "stm32g4xx_hal_spi.h"
#include "stm32g4xx_hal_def.h"
#include "MAX22190_reg_structs.h"
#include "MAX22190_regs.h"
#include "stdbool.h"

/*******************************************************************************
 ********************************* Macros **************************************
 ******************************************************************************/

/**
 * @def MAX22190_WRITE_CMD
 * @brief
 *
 */
#define MAX22190_WRITE_CMD      0x80

/**
 * @def MAX22190_SPI_BUFFER_SIZE
 * @brief
 *
 */
#define MAX22190_SPI_BUFFER_SIZE  3

/*******************************************************************************
 **************************** Type Definitions *********************************
 ******************************************************************************/

typedef enum
{
    MAX22190_OK = 0,
    MAX22190_ERROR
} MAX22190_Status_t;

/**
 * @struct MAX22190_GPIO_t
 * @brief
 *
 */
typedef struct {
    uint16_t pin_number;
    GPIO_TypeDef *port;
} MAX22190_GPIO_t;

/**
 * @struct MAX22190_Device_t
 * @brief
 *
 */
typedef struct {
    SPI_HandleTypeDef     *hspi;
    MAX22190_Registers_s  regs;
    MAX22190_GPIO_t       CS_Pin;
    MAX22190_GPIO_t       Fault_Pin;
    uint8_t               DB_Index;
    volatile uint8_t      DI_Status;
    volatile bool         faultFlag;
    volatile bool         CrcError;
} MAX22190_Device_t;

/*******************************************************************************
 *********************** Global Variable Declaration ***************************
 ******************************************************************************/
extern uint8_t MAX22190_TxBuffer[MAX22190_SPI_BUFFER_SIZE];
extern uint8_t MAX22190_RxBuffer[MAX22190_SPI_BUFFER_SIZE];

/*******************************************************************************
 *********************** Static Variable Declaration ***************************
 ******************************************************************************/

/*******************************************************************************
 ******************** Function Prototypes (Declarations) ***********************
 ******************************************************************************/

/**
 * @name        MAX22190_InitDevice
 *
 * @brief       Insert Function Brief Description Here
 *
 * @param[in]   Insert Function Brief Description of the input arguments of the
 *              function here in separated lines
 *
 * @param[out]  Insert Function Brief Description of the output arguments of the
 *              function here in separated lines
 *
 * @return       Insert Function Return Parameter Descriptions Here
 *
 * @retval       Insert Descriptions for the values and indications Here
 *
 * @author       Insert Author Name Here
 *
 * @date         Insert Timestamp here - Example: $06/12/2024 01:15:00$
 *
 * @since        Insert all changes from initial version here in
 *              separate lines
 *
 * @note         Insert any notes for usage of the function Here
 *
 * @bug          Insert known Bugs for the function here
 *
 * @warning      Insert usage warnings for the function here
 *
 * @todo         Insert to do actions for the function here
 *
 * @test         Insert test cases related to the function here
 *
 * @example      Insert Examples for Implementation or Usage of the Function
 *              Here or provide links
 */
void MAX22190_InitDevice(MAX22190_Device_t *dev,
                         SPI_HandleTypeDef *hspi,
						 MAX22190_GPIO_t *CS_GPIO,
						 MAX22190_GPIO_t *Fault_GPIO,
                         uint8_t DB_index);

/**
 * @name        MAX22190_WriteRegister
 *
 * @brief       Insert Function Brief Description Here
 *
 * @param[in]   Insert Function Brief Description of the input arguments of the
 *              function here in separated lines
 *
 * @param[out]  Insert Function Brief Description of the output arguments of the
 *              function here in separated lines
 *
 * @return       Insert Function Return Parameter Descriptions Here
 *
 * @retval       Insert Descriptions for the values and indications Here
 *
 * @author       Insert Author Name Here
 *
 * @date         Insert Timestamp here - Example: $06/12/2024 01:15:00$
 *
 * @since        Insert all changes from initial version here in
 *              separate lines
 *
 * @note         Insert any notes for usage of the function Here
 *
 * @bug          Insert known Bugs for the function here
 *
 * @warning      Insert usage warnings for the function here
 *
 * @todo         Insert to do actions for the function here
 *
 * @test         Insert test cases related to the function here
 *
 * @example      Insert Examples for Implementation or Usage of the Function
 *              Here or provide links
 */
MAX22190_Status_t MAX22190_WriteRegister(MAX22190_Device_t *dev,
										 uint8_t regAddr,
										 uint8_t data);

/**
 * @name        MAX22190_ReadRegister
 *
 * @brief       Insert Function Brief Description Here
 *
 * @param[in]   Insert Function Brief Description of the input arguments of the
 *              function here in separated lines
 *
 * @param[out]  Insert Function Brief Description of the output arguments of the
 *              function here in separated lines
 *
 * @return       Insert Function Return Parameter Descriptions Here
 *
 * @retval       Insert Descriptions for the values and indications Here
 *
 * @author       Insert Author Name Here
 *
 * @date         Insert Timestamp here - Example: $06/12/2024 01:15:00$
 *
 * @since        Insert all changes from initial version here in
 *              separate lines
 *
 * @note         Insert any notes for usage of the function Here
 *
 * @bug          Insert known Bugs for the function here
 *
 * @warning      Insert usage warnings for the function here
 *
 * @todo         Insert to do actions for the function here
 *
 * @test         Insert test cases related to the function here
 *
 * @example      Insert Examples for Implementation or Usage of the Function
 *              Here or provide links
 */
MAX22190_Status_t MAX22190_ReadRegister(MAX22190_Device_t *dev,
										uint8_t regAddr);

/**
 * @name        MAX22190_ReadInputs
 *
 * @brief       Insert Function Brief Description Here
 *
 * @param[in]   Insert Function Brief Description of the input arguments of the
 *              function here in separated lines
 *
 * @param[out]  Insert Function Brief Description of the output arguments of the
 *              function here in separated lines
 *
 * @return       Insert Function Return Parameter Descriptions Here
 *
 * @retval       Insert Descriptions for the values and indications Here
 *
 * @author       Insert Author Name Here
 *
 * @date         Insert Timestamp here - Example: $06/12/2024 01:15:00$
 *
 * @since        Insert all changes from initial version here in
 *              separate lines
 *
 * @note         Insert any notes for usage of the function Here
 *
 * @bug          Insert known Bugs for the function here
 *
 * @warning      Insert usage warnings for the function here
 *
 * @todo         Insert to do actions for the function here
 *
 * @test         Insert test cases related to the function here
 *
 * @example      Insert Examples for Implementation or Usage of the Function
 *              Here or provide links
 */
MAX22190_Status_t MAX22190_ReadInputs_DMA(MAX22190_Device_t *dev);

/**
 * @name        MAX22190_ConfigureChannels
 *
 * @brief       Insert Function Brief Description Here
 *
 * @param[in]   Insert Function Brief Description of the input arguments of the
 *              function here in separated lines
 *
 * @param[out]  Insert Function Brief Description of the output arguments of the
 *              function here in separated lines
 *
 * @return       Insert Function Return Parameter Descriptions Here
 *
 * @retval       Insert Descriptions for the values and indications Here
 *
 * @author       Insert Author Name Here
 *
 * @date         Insert Timestamp here - Example: $06/12/2024 01:15:00$
 *
 * @since        Insert all changes from initial version here in
 *              separate lines
 *
 * @note         Insert any notes for usage of the function Here
 *
 * @bug          Insert known Bugs for the function here
 *
 * @warning      Insert usage warnings for the function here
 *
 * @todo         Insert to do actions for the function here
 *
 * @test         Insert test cases related to the function here
 *
 * @example      Insert Examples for Implementation or Usage of the Function
 *              Here or provide links
 */
MAX22190_Status_t MAX22190_ConfigureChannels(MAX22190_Device_t *dev, uint8_t channel_config_mask);

/**
 * @name        MAX22190_CheckCRC
 *
 * @brief       Insert Function Brief Description Here
 *
 * @param[in]   Insert Function Brief Description of the input arguments of the
 *              function here in separated lines
 *
 * @param[out]  Insert Function Brief Description of the output arguments of the
 *              function here in separated lines
 *
 * @return       Insert Function Return Parameter Descriptions Here
 *
 * @retval       Insert Descriptions for the values and indications Here
 *
 * @author       Insert Author Name Here
 *
 * @date         Insert Timestamp here - Example: $06/12/2024 01:15:00$
 *
 * @since        Insert all changes from initial version here in
 *              separate lines
 *
 * @note         Insert any notes for usage of the function Here
 *
 * @bug          Insert known Bugs for the function here
 *
 * @warning      Insert usage warnings for the function here
 *
 * @todo         Insert to do actions for the function here
 *
 * @test         Insert test cases related to the function here
 *
 * @example      Insert Examples for Implementation or Usage of the Function
 *              Here or provide links
 */
MAX22190_Status_t MAX22190_CheckCRC(const uint8_t *data);

/**
 * @name        MAX22190_ClearPORFault
 *
 * @brief       Insert Function Brief Description Here
 *
 * @param[in]   Insert Function Brief Description of the input arguments of the
 *              function here in separated lines
 *
 * @param[out]  Insert Function Brief Description of the output arguments of the
 *              function here in separated lines
 *
 * @return       Insert Function Return Parameter Descriptions Here
 *
 * @retval       Insert Descriptions for the values and indications Here
 *
 * @author       Insert Author Name Here
 *
 * @date         Insert Timestamp here - Example: $06/12/2024 01:15:00$
 *
 * @since        Insert all changes from initial version here in
 *              separate lines
 *
 * @note         Insert any notes for usage of the function Here
 *
 * @bug          Insert known Bugs for the function here
 *
 * @warning      Insert usage warnings for the function here
 *
 * @todo         Insert to do actions for the function here
 *
 * @test         Insert test cases related to the function here
 *
 * @example      Insert Examples for Implementation or Usage of the Function
 *              Here or provide links
 */
MAX22190_Status_t MAX22190_ClearPORFault(MAX22190_Device_t *dev);

/**
 * @name        MAX22190_ConfigureInputFilter
 *
 * @brief       Insert Function Brief Description Here
 *
 * @param[in]   Insert Function Brief Description of the input arguments of the
 *              function here in separated lines
 *
 * @param[out]  Insert Function Brief Description of the output arguments of the
 *              function here in separated lines
 *
 * @return       Insert Function Return Parameter Descriptions Here
 *
 * @retval       Insert Descriptions for the values and indications Here
 *
 * @author       Insert Author Name Here
 *
 * @date         Insert Timestamp here - Example: $06/12/2024 01:15:00$
 *
 * @since        Insert all changes from initial version here in
 *              separate lines
 *
 * @note         Insert any notes for usage of the function Here
 *
 * @bug          Insert known Bugs for the function here
 *
 * @warning      Insert usage warnings for the function here
 *
 * @todo         Insert to do actions for the function here
 *
 * @test         Insert test cases related to the function here
 *
 * @example      Insert Examples for Implementation or Usage of the Function
 *              Here or provide links
 */
MAX22190_Status_t MAX22190_ConfigureInputFilter(MAX22190_Device_t *dev, uint8_t FILTER_INx, MAX22190_FLTx_DELAY_e delay, MAX22190_FLTx_FBP_e filter_bypass_en, MAX22190_FLTx_WBE_e wire_break_en);

/**
 * @name        MAX22190_EnableFaultPinSticky
 *
 * @brief       Insert Function Brief Description Here
 *
 * @param[in]   Insert Function Brief Description of the input arguments of the
 *              function here in separated lines
 *
 * @param[out]  Insert Function Brief Description of the output arguments of the
 *              function here in separated lines
 *
 * @return       Insert Function Return Parameter Descriptions Here
 *
 * @retval       Insert Descriptions for the values and indications Here
 *
 * @author       Insert Author Name Here
 *
 * @date         Insert Timestamp here - Example: $06/12/2024 01:15:00$
 *
 * @since        Insert all changes from initial version here in
 *              separate lines
 *
 * @note         Insert any notes for usage of the function Here
 *
 * @bug          Insert known Bugs for the function here
 *
 * @warning      Insert usage warnings for the function here
 *
 * @todo         Insert to do actions for the function here
 *
 * @test         Insert test cases related to the function here
 *
 * @example      Insert Examples for Implementation or Usage of the Function
 *              Here or provide links
 */
MAX22190_Status_t MAX22190_EnableFaultPinSticky(MAX22190_Device_t *dev);

/**
 * @name        MAX22190_ConfigureFault1EN
 *
 * @brief       Insert Function Brief Description Here
 *
 * @param[in]   Insert Function Brief Description of the input arguments of the
 *              function here in separated lines
 *
 * @param[out]  Insert Function Brief Description of the output arguments of the
 *              function here in separated lines
 *
 * @return       Insert Function Return Parameter Descriptions Here
 *
 * @retval       Insert Descriptions for the values and indications Here
 *
 * @author       Insert Author Name Here
 *
 * @date         Insert Timestamp here - Example: $06/12/2024 01:15:00$
 *
 * @since        Insert all changes from initial version here in
 *              separate lines
 *
 * @note         Insert any notes for usage of the function Here
 *
 * @bug          Insert known Bugs for the function here
 *
 * @warning      Insert usage warnings for the function here
 *
 * @todo         Insert to do actions for the function here
 *
 * @test         Insert test cases related to the function here
 *
 * @example      Insert Examples for Implementation or Usage of the Function
 *              Here or provide links
 */
MAX22190_Status_t MAX22190_ConfigureFault1EN(MAX22190_Device_t *dev, uint8_t regConfig);

/**
 * @name        MAX22190_ConfigureFault2EN
 *
 * @brief       Insert Function Brief Description Here
 *
 * @param[in]   Insert Function Brief Description of the input arguments of the
 *              function here in separated lines
 *
 * @param[out]  Insert Function Brief Description of the output arguments of the
 *              function here in separated lines
 *
 * @return       Insert Function Return Parameter Descriptions Here
 *
 * @retval       Insert Descriptions for the values and indications Here
 *
 * @author       Insert Author Name Here
 *
 * @date         Insert Timestamp here - Example: $06/12/2024 01:15:00$
 *
 * @since        Insert all changes from initial version here in
 *              separate lines
 *
 * @note         Insert any notes for usage of the function Here
 *
 * @bug          Insert known Bugs for the function here
 *
 * @warning      Insert usage warnings for the function here
 *
 * @todo         Insert to do actions for the function here
 *
 * @test         Insert test cases related to the function here
 *
 * @example      Insert Examples for Implementation or Usage of the Function
 *              Here or provide links
 */
MAX22190_Status_t MAX22190_ConfigureFault2EN(MAX22190_Device_t *dev, uint8_t regConfig);

/**
 * @name        MAX22190_ConfigureCFG
 *
 * @brief       Insert Function Brief Description Here
 *
 * @param[in]   Insert Function Brief Description of the input arguments of the
 *              function here in separated lines
 *
 * @param[out]  Insert Function Brief Description of the output arguments of the
 *              function here in separated lines
 *
 * @return       Insert Function Return Parameter Descriptions Here
 *
 * @retval       Insert Descriptions for the values and indications Here
 *
 * @author       Insert Author Name Here
 *
 * @date         Insert Timestamp here - Example: $06/12/2024 01:15:00$
 *
 * @since        Insert all changes from initial version here in
 *              separate lines
 *
 * @note         Insert any notes for usage of the function Here
 *
 * @bug          Insert known Bugs for the function here
 *
 * @warning      Insert usage warnings for the function here
 *
 * @todo         Insert to do actions for the function here
 *
 * @test         Insert test cases related to the function here
 *
 * @example      Insert Examples for Implementation or Usage of the Function
 *              Here or provide links
 */
MAX22190_Status_t MAX22190_ConfigureCFG(MAX22190_Device_t *dev, uint8_t regConfig);

/**
 * @name        MAX22190_CheckFaultStatus
 *
 * @brief       Insert Function Brief Description Here
 *
 * @param[in]   Insert Function Brief Description of the input arguments of the
 *              function here in separated lines
 *
 * @param[out]  Insert Function Brief Description of the output arguments of the
 *              function here in separated lines
 *
 * @return       Insert Function Return Parameter Descriptions Here
 *
 * @retval       Insert Descriptions for the values and indications Here
 *
 * @author       Insert Author Name Here
 *
 * @date         Insert Timestamp here - Example: $06/12/2024 01:15:00$
 *
 * @since        Insert all changes from initial version here in
 *              separate lines
 *
 * @note         Insert any notes for usage of the function Here
 *
 * @bug          Insert known Bugs for the function here
 *
 * @warning      Insert usage warnings for the function here
 *
 * @todo         Insert to do actions for the function here
 *
 * @test         Insert test cases related to the function here
 *
 * @example      Insert Examples for Implementation or Usage of the Function
 *              Here or provide links
 */
void MAX22190_CheckFaultStatus(MAX22190_Device_t *dev);

/**
 * @name        MAX22190_Read_FAULT1
 *
 * @brief       Insert Function Brief Description Here
 *
 * @param[in]   Insert Function Brief Description of the input arguments of the
 *              function here in separated lines
 *
 * @param[out]  Insert Function Brief Description of the output arguments of the
 *              function here in separated lines
 *
 * @return       Insert Function Return Parameter Descriptions Here
 *
 * @retval       Insert Descriptions for the values and indications Here
 *
 * @author       Insert Author Name Here
 *
 * @date         Insert Timestamp here - Example: $06/12/2024 01:15:00$
 *
 * @since        Insert all changes from initial version here in
 *              separate lines
 *
 * @note         Insert any notes for usage of the function Here
 *
 * @bug          Insert known Bugs for the function here
 *
 * @warning      Insert usage warnings for the function here
 *
 * @todo         Insert to do actions for the function here
 *
 * @test         Insert test cases related to the function here
 *
 * @example      Insert Examples for Implementation or Usage of the Function
 *              Here or provide links
 */
MAX22190_Status_t MAX22190_Read_FAULT1(MAX22190_Device_t *dev);

/**
 * @name        MAX22190_Read_FAULT2
 *
 * @brief       Insert Function Brief Description Here
 *
 * @param[in]   Insert Function Brief Description of the input arguments of the
 *              function here in separated lines
 *
 * @param[out]  Insert Function Brief Description of the output arguments of the
 *              function here in separated lines
 *
 * @return       Insert Function Return Parameter Descriptions Here
 *
 * @retval       Insert Descriptions for the values and indications Here
 *
 * @author       Insert Author Name Here
 *
 * @date         Insert Timestamp here - Example: $06/12/2024 01:15:00$
 *
 * @since        Insert all changes from initial version here in
 *              separate lines
 *
 * @note         Insert any notes for usage of the function Here
 *
 * @bug          Insert known Bugs for the function here
 *
 * @warning      Insert usage warnings for the function here
 *
 * @todo         Insert to do actions for the function here
 *
 * @test         Insert test cases related to the function here
 *
 * @example      Insert Examples for Implementation or Usage of the Function
 *              Here or provide links
 */
MAX22190_Status_t MAX22190_Read_FAULT2(MAX22190_Device_t *dev);

/**
 * @name        MAX22190_Read_WB
 *
 * @brief       Insert Function Brief Description Here
 *
 * @param[in]   Insert Function Brief Description of the input arguments of the
 *              function here in separated lines
 *
 * @param[out]  Insert Function Brief Description of the output arguments of the
 *              function here in separated lines
 *
 * @return       Insert Function Return Parameter Descriptions Here
 *
 * @retval       Insert Descriptions for the values and indications Here
 *
 * @author       Insert Author Name Here
 *
 * @date         Insert Timestamp here - Example: $06/12/2024 01:15:00$
 *
 * @since        Insert all changes from initial version here in
 *              separate lines
 *
 * @note         Insert any notes for usage of the function Here
 *
 * @bug          Insert known Bugs for the function here
 *
 * @warning      Insert usage warnings for the function here
 *
 * @todo         Insert to do actions for the function here
 *
 * @test         Insert test cases related to the function here
 *
 * @example      Insert Examples for Implementation or Usage of the Function
 *              Here or provide links
 */
MAX22190_Status_t MAX22190_Read_WB(MAX22190_Device_t *dev);

/**
 * @name        MAX22190_ReadDigitalInputs
 *
 * @brief       Insert Function Brief Description Here
 *
 * @param[in]   Insert Function Brief Description of the input arguments of the
 *              function here in separated lines
 *
 * @param[out]  Insert Function Brief Description of the output arguments of the
 *              function here in separated lines
 *
 * @return       Insert Function Return Parameter Descriptions Here
 *
 * @retval       Insert Descriptions for the values and indications Here
 *
 * @author       Insert Author Name Here
 *
 * @date         Insert Timestamp here - Example: $06/12/2024 01:15:00$
 *
 * @since        Insert all changes from initial version here in
 *              separate lines
 *
 * @note         Insert any notes for usage of the function Here
 *
 * @bug          Insert known Bugs for the function here
 *
 * @warning      Insert usage warnings for the function here
 *
 * @todo         Insert to do actions for the function here
 *
 * @test         Insert test cases related to the function here
 *
 * @example      Insert Examples for Implementation or Usage of the Function
 *              Here or provide links
 */
MAX22190_Status_t MAX22190_ReadDigitalInputs(MAX22190_Device_t *dev);

/**
 * @name        MAX22190_CS_Deselect
 *
 * @brief       Insert Function Brief Description Here
 *
 * @param[in]   Insert Function Brief Description of the input arguments of the
 *              function here in separated lines
 *
 * @param[out]  Insert Function Brief Description of the output arguments of the
 *              function here in separated lines
 *
 * @return       Insert Function Return Parameter Descriptions Here
 *
 * @retval       Insert Descriptions for the values and indications Here
 *
 * @author       Insert Author Name Here
 *
 * @date         Insert Timestamp here - Example: $06/12/2024 01:15:00$
 *
 * @since        Insert all changes from initial version here in
 *              separate lines
 *
 * @note         Insert any notes for usage of the function Here
 *
 * @bug          Insert known Bugs for the function here
 *
 * @warning      Insert usage warnings for the function here
 *
 * @todo         Insert to do actions for the function here
 *
 * @test         Insert test cases related to the function here
 *
 * @example      Insert Examples for Implementation or Usage of the Function
 *              Here or provide links
 */
void MAX22190_CS_Deselect(MAX22190_Device_t *dev);

/**
 * @name        MAX22190_CS_Select
 *
 * @brief       Insert Function Brief Description Here
 *
 * @param[in]   Insert Function Brief Description of the input arguments of the
 *              function here in separated lines
 *
 * @param[out]  Insert Function Brief Description of the output arguments of the
 *              function here in separated lines
 *
 * @return       Insert Function Return Parameter Descriptions Here
 *
 * @retval       Insert Descriptions for the values and indications Here
 *
 * @author       Insert Author Name Here
 *
 * @date         Insert Timestamp here - Example: $06/12/2024 01:15:00$
 *
 * @since        Insert all changes from initial version here in
 *              separate lines
 *
 * @note         Insert any notes for usage of the function Here
 *
 * @bug          Insert known Bugs for the function here
 *
 * @warning      Insert usage warnings for the function here
 *
 * @todo         Insert to do actions for the function here
 *
 * @test         Insert test cases related to the function here
 *
 * @example      Insert Examples for Implementation or Usage of the Function
 *              Here or provide links
 */
void MAX22190_CS_Select(MAX22190_Device_t *dev);

/**
 * MAX22190 @}
 */

/*******************************************************************************
 *************************** Header Guard End **********************************
 ******************************************************************************/
#endif /* MAX22190_H_ */
