/*******************************************************************************
 ************************* File Description Start ******************************
 ******************************************************************************/
/**
 * @addtogroup MAX22190
 * @{
 * @file       MAX22190.c
 * @brief      MAX22190 - The file contains all the necessary function required to interface with the MAX22190
 * 			   serializer module.
 * Layer.
 * @author     Chetan S Harihar
 * @version    V0.1
 * @date       04/10/2024 11:24:00
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
 **************************** Private Includes *********************************
 ******************************************************************************/
#include "MAX22190_CRC.h"
#include "MAX22190.h"
#include "string.h"

/*******************************************************************************
 **************************** Type Definitions *********************************
 ******************************************************************************/

/*******************************************************************************
 ********************************* Macros **************************************
 ******************************************************************************/

/*******************************************************************************
 ************************** Constants Definitions ******************************
 ******************************************************************************/

/*******************************************************************************
 *********************** Global Variable Definitions ***************************
 ******************************************************************************/
uint8_t MAX22190_TxBuffer[MAX22190_SPI_BUFFER_SIZE];
uint8_t MAX22190_RxBuffer[MAX22190_SPI_BUFFER_SIZE];

/*******************************************************************************
 *********************** Static Variable Definitions ***************************
 ******************************************************************************/

/*******************************************************************************
 ************************** Function Prototypes ********************************
 ******************************************************************************/

void MAX22190_InitDevice(MAX22190_Device_t *dev,
                         SPI_HandleTypeDef *hspi,
						 MAX22190_GPIO_t *CS_GPIO,
						 MAX22190_GPIO_t *Fault_GPIO,
                         uint8_t DB_index)
{
    dev->hspi = hspi;
    dev->CS_Pin.port = CS_GPIO->port;
    dev->CS_Pin.pin_number = CS_GPIO->pin_number;
    dev->Fault_Pin.port = Fault_GPIO->port;
    dev->Fault_Pin.pin_number = Fault_GPIO->pin_number;
    dev->DB_Index = DB_index;
    dev->faultFlag = false;
    dev->CrcError = false;
}

MAX22190_Status_t MAX22190_WriteRegister(MAX22190_Device_t *dev,
										 uint8_t regAddr,
										 uint8_t data)
{
	MAX22190_TxBuffer[0] = regAddr | MAX22190_WRITE_CMD;
	MAX22190_TxBuffer[1] = data;
	MAX22190_TxBuffer[2] = 0x00;

	uint8_t crc = MAX22190_CalculateCRC(MAX22190_TxBuffer);
	MAX22190_TxBuffer[2] = crc & 0x1F;

	MAX22190_CS_Select(dev);
	HAL_StatusTypeDef hal_status = HAL_SPI_TransmitReceive(dev->hspi, MAX22190_TxBuffer, MAX22190_RxBuffer, MAX22190_SPI_BUFFER_SIZE, 100);
	MAX22190_CS_Deselect(dev);

    if (hal_status != HAL_OK)
    {
        return MAX22190_ERROR;
    }

    return MAX22190_OK;
}

MAX22190_Status_t MAX22190_ReadRegister(MAX22190_Device_t *dev,
										uint8_t regAddr)
{
	MAX22190_TxBuffer[0] = regAddr;
	MAX22190_TxBuffer[1] = 0x00;
	MAX22190_TxBuffer[2] = 0x00;

	uint8_t crc = MAX22190_CalculateCRC(MAX22190_TxBuffer);
	MAX22190_TxBuffer[2] = crc & 0x1F;

	MAX22190_CS_Select(dev);
    HAL_StatusTypeDef hal_status = HAL_SPI_TransmitReceive(dev->hspi, MAX22190_TxBuffer, MAX22190_RxBuffer, MAX22190_SPI_BUFFER_SIZE, 100);
    MAX22190_CS_Deselect(dev);

    if (hal_status != HAL_OK)
    {
        return MAX22190_ERROR;
    }

    // check CRC of the data received
    return MAX22190_CheckCRC(MAX22190_RxBuffer);
}

/**
 * Verify CRC of a received 24-bit SDO frame.
 * SDO frame: [Input data(8b)] [Reg/WB data(8b)] [24VL|24VM|WBG(3b)] [CRC(5b)]
 *
 * @param sdo   3-byte received frame [byte2, byte1, byte0]
 * @return      1 if CRC valid, 0 if mismatch
 */
MAX22190_Status_t MAX22190_CheckCRC(const uint8_t *data)
{
    /* Extract the received CRC from lower 5 bits of byte 0 */
    uint8_t received_crc = data[2] & 0x1F;

    /* Zero out the CRC field, keep the 3 fill bits as-is (they are 0) */
    uint8_t frame_for_calc[3];
    frame_for_calc[0] = data[0];
    frame_for_calc[1] = data[1];
    frame_for_calc[2] = data[2] & 0xE0;   /* clear lower 5 bits, preserve upper 3 */

    /* Recalculate CRC */
    uint8_t calc_crc = MAX22190_CalculateCRC(frame_for_calc);

    if (calc_crc == received_crc) {
    	return MAX22190_OK;
    }

    return MAX22190_ERROR;
}

MAX22190_Status_t MAX22190_ClearPORFault(MAX22190_Device_t *dev) {
	HAL_StatusTypeDef status;

	status = MAX22190_WriteRegister(dev, MAX22190_FAULT1_ADDR, 0x00);
	if (status != HAL_OK)
	{
		return status;
	}

	return MAX22190_OK;
}

MAX22190_Status_t MAX22190_ReadInputs_DMA(MAX22190_Device_t *dev) {
	MAX22190_TxBuffer[0] = MAX22190_DI_ADDR;
	MAX22190_TxBuffer[1] = 0x00;
	MAX22190_TxBuffer[2] = 0x00;

	uint8_t crc = MAX22190_CalculateCRC(MAX22190_TxBuffer);
	MAX22190_TxBuffer[2] = crc & 0x1F;

	MAX22190_CS_Select(dev);
    HAL_StatusTypeDef hal_status = HAL_SPI_TransmitReceive_DMA(dev->hspi, MAX22190_TxBuffer, MAX22190_RxBuffer, MAX22190_SPI_BUFFER_SIZE);
    /* Deselect CS in DMA complete callback */
	if (hal_status != HAL_OK)
	{
		return MAX22190_ERROR;
	}

	return MAX22190_OK;
}

MAX22190_Status_t MAX22190_ConfigureChannels(MAX22190_Device_t *dev, uint8_t channel_config_mask) {
	HAL_StatusTypeDef hal_status = MAX22190_WriteRegister(dev, MAX22190_INEN_ADDR, channel_config_mask);
	if (hal_status != HAL_OK)
	{
		return MAX22190_ERROR;
	}

	return MAX22190_OK;
}

MAX22190_Status_t MAX22190_ConfigureInputFilter(MAX22190_Device_t *dev, uint8_t FILTER_INx, MAX22190_FLTx_DELAY_e delay, MAX22190_FLTx_FBP_e filter_bypass_en, MAX22190_FLTx_WBE_e wire_break_en) {
	MAX22190_FLTx_REG_u reg = {0};
	reg.bits.DELAY = delay;
	reg.bits.FBP = filter_bypass_en;
	reg.bits.WBE = wire_break_en;

	HAL_StatusTypeDef hal_status = MAX22190_WriteRegister(dev, FILTER_INx, reg.dataByte);
	if (hal_status != HAL_OK)
	{
		return MAX22190_ERROR;
	}

	return MAX22190_OK;
}

MAX22190_Status_t MAX22190_EnableFaultPinSticky(MAX22190_Device_t *dev) {
	MAX22190_GPO_REG_u reg = {0};
	reg.bits.STK = 1;

	HAL_StatusTypeDef hal_status = MAX22190_WriteRegister(dev, MAX22190_GPO_ADDR, reg.dataByte);
	if (hal_status != HAL_OK)
	{
		return MAX22190_ERROR;
	}

	return MAX22190_OK;
}

MAX22190_Status_t MAX22190_ConfigureFault1EN(MAX22190_Device_t *dev, uint8_t regConfig) {
	/*
	 * FAULT1EN Register
	 * Enables the FAULT pin to assert low for corresponding status bits in FAULT1.
	 * CRCE    : 1 = Enable FAULT pin for CRC Error.
	 * PORE    : 1 = Enable FAULT pin for Power-On-Reset.
	 * FAULT2E : 1 = Enable FAULT pin if any FAULT2 event is active.
	 * ALRMT2E : 1 = Enable FAULT pin assertion for Temperature Alarm 2.
	 * ALRMT1E : 1 = Enable FAULT pin assertion for Temperature Alarm 1.
	 * 24VLE   : 1 = Enable FAULT pin assertion for 24V Supply Low.
	 * 24VME   : 1 = Enable FAULT pin assertion for 24V Supply Missing.
	 * WBGE    : 1 = Enable FAULT pin assertion for Wire-Break Group error.
	 */

	return MAX22190_WriteRegister(dev, MAX22190_FAULT1EN_ADDR, regConfig);
}

MAX22190_Status_t MAX22190_ConfigureFault2EN(MAX22190_Device_t *dev, uint8_t regConfig) {
	/*
	 * FAULT2EN Register
	 * Enables internal diagnostic events to set the summary FAULT2 bit (D5) in FAULT1.
	 * FAULT8CKE : 1 = Enable fault if SPI clock count is not a multiple of 8.
	 * OTSHDNE   : 1 = Enable fault if Over temperature Shutdown occurs.
	 * RFDIOE    : 1 = Enable FAULT2 bit assertion if REFDI Open is detected.
	 * RFDISE    : 1 = Enable FAULT2 bit assertion if REFDI Short is detected
	 * RFWBOE    : 1 = Enable FAULT2 bit assertion if REFWB Open is detected.
	 * RFWBSE    : 1 = Enable FAULT2 bit assertion if REFWB Short is detected.
	 */

	return MAX22190_WriteRegister(dev, MAX22190_FAULT2EN_ADDR, regConfig);
}

MAX22190_Status_t MAX22190_ConfigureCFG(MAX22190_Device_t *dev, uint8_t regConfig) {
	/*
	 * CFG Register
	 * Controls filter behavior and how 24V supply faults are cleared.
	 * 24VF         : 0 = 24V faults (24VL/24VM) clear on SPI transaction (Modes 0/2) OR FAULT1 read.
	 * 24VF         : 1 = 24V faults (24VL/24VM) clear ONLY on FAULT1 read.
	 * CLRF         : 0 = Filters operate normally.
	 * CLRF         : 1 = All input/wire-break filters fixed at mid-scale.
	 * REFDI_SH_ENA : 0 = Disable REFDI short detection; 1=Enable REFDI short detection.
	 */

	return MAX22190_WriteRegister(dev, MAX22190_CFG_ADDR, regConfig);
}

void MAX22190_CheckFaultStatus(MAX22190_Device_t *dev) {
	if (HAL_GPIO_ReadPin(dev->Fault_Pin.port, dev->Fault_Pin.pin_number) == GPIO_PIN_RESET) {
		dev->faultFlag = true;
	}
	else
	{
		dev->faultFlag = false;
	}
}

MAX22190_Status_t MAX22190_Read_FAULT1(MAX22190_Device_t *dev, uint8_t *fault_data) {
	HAL_StatusTypeDef hal_status = MAX22190_ReadRegister(dev, MAX22190_FAULT1_ADDR);
	if (hal_status != HAL_OK)
	{
		return MAX22190_ERROR;
	}

	*fault_data = MAX22190_RxBuffer[1];

	return MAX22190_OK;
}

MAX22190_Status_t MAX22190_Read_FAULT2(MAX22190_Device_t *dev, uint8_t *fault_data) {
	HAL_StatusTypeDef hal_status = MAX22190_ReadRegister(dev, MAX22190_FAULT2_ADDR);
	if (hal_status != HAL_OK)
	{
		return MAX22190_ERROR;
	}

	*fault_data = MAX22190_RxBuffer[1];

	return MAX22190_OK;
}

MAX22190_Status_t MAX22190_Read_WB(MAX22190_Device_t *dev, uint8_t *WB_data) {
	HAL_StatusTypeDef hal_status = MAX22190_ReadRegister(dev, MAX22190_WB_ADDR);
	if (hal_status != HAL_OK)
	{
		return MAX22190_ERROR;
	}

	*WB_data = MAX22190_RxBuffer[1];

	return MAX22190_OK;
}

MAX22190_Status_t MAX22190_ReadDigitalInputs(MAX22190_Device_t *dev) {
	HAL_StatusTypeDef hal_status = MAX22190_ReadRegister(dev, MAX22190_DI_ADDR);
	if (hal_status != HAL_OK)
	{
		return MAX22190_ERROR;
	}

	dev->DI_Status = MAX22190_RxBuffer[1];

	return MAX22190_OK;
}

void MAX22190_CS_Deselect(MAX22190_Device_t *dev)
{
	HAL_GPIO_WritePin(dev->CS_Pin.port, dev->CS_Pin.pin_number, GPIO_PIN_SET);
}

void MAX22190_CS_Select(MAX22190_Device_t *dev)
{
	HAL_GPIO_WritePin(dev->CS_Pin.port, dev->CS_Pin.pin_number, GPIO_PIN_RESET);
}

/**
 * MAX22190 @}
 */
