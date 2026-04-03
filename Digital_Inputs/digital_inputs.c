/*
 * digital_input.c
 *
 *  Created on: Aug 28, 2025
 *      Author: Chetan
 */


#include "digital_inputs.h"
#include "main.h"
#include "spi.h"
#include "stdbool.h"

MAX22190_Device_t DI_Devices[NUM_DI_DEVICES];

volatile uint8_t DI_DB[NUM_DI_DEVICES] = {0};

volatile uint8_t DI_DeviceIndex = 0;

volatile bool DI_FaultFlag      = false;
volatile bool DI_ReadyToRead    = false;
volatile bool DI_ReadyToProcess = false;
volatile bool DI_CrcError       = false;

/**
 * @name        DigitalInput_Deselect_all_CS
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
static void DigitalInput_Deselect_all_CS(void);

/**
 * @name        DigitalInputs_Config
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
static void DigitalInputs_Config(void);

/**
 * @name        DigitalInput_UpdateDatabase
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
static void DigitalInput_UpdateDatabase(void);

MAX22190_GPIO_t DS1_fault_gpio = { DS1_FAULT_Pin, DS1_FAULT_GPIO_Port };
MAX22190_GPIO_t DS2_fault_gpio = { DS2_FAULT_Pin, DS2_FAULT_GPIO_Port };

MAX22190_GPIO_t DS1_cs_gpio    = { DS1_CS_Pin, DS1_CS_GPIO_Port };
MAX22190_GPIO_t DS2_cs_gpio    = { DS2_CS_Pin, DS2_CS_GPIO_Port };

/* Set all CS pins high in this function */
static void DigitalInput_Deselect_all_CS(void) {
	for (int i = 0; i < NUM_DI_DEVICES; i++) {
		MAX22190_Device_t *dev = &DI_Devices[i];
		MAX22190_CS_Deselect(dev);
	}
}

void DigitalInput_Init(void) {
	// Init SPI
	MX_SPI3_Init();

	// Enable SPI register callback
	HAL_SPI_RegisterCallback(&DI_SPI, HAL_SPI_TX_RX_COMPLETE_CB_ID, DigitalInput_DMA_ReadCompleteCallback);

	// Init DI devices
	MAX22190_InitDevice(&DI_Devices[0], &DI_SPI, &DS1_cs_gpio, &DS1_fault_gpio, 0);
	MAX22190_InitDevice(&DI_Devices[1], &DI_SPI, &DS2_cs_gpio, &DS2_fault_gpio, 1);

	// Deselect all CS
	DigitalInput_Deselect_all_CS();

	// Clear POR bit
	MAX22190_ClearPORFault(&DI_Devices[0]);

	// Clear POR bit
	MAX22190_ClearPORFault(&DI_Devices[1]);

	// Config DI devices
	DigitalInputs_Config();

	// After setup enable DMA read flag
	DI_ReadyToRead = true;
}

static void DigitalInputs_Config(void)
{
	MAX22190_FAULT2EN_REG_u FAULT2EN;
	MAX22190_FAULT1EN_REG_u FAULT1EN;
	MAX22190_CFG_REG_u CFG;

	// ----------------------------------------------------------------------
	// Device 1 Config
	// ----------------------------------------------------------------------
	// Config channels
	MAX22190_ConfigureChannels(&DI_Devices[0], MAX22190_ENABLE_ALL_CHANNELS);

	// Config Filters
	MAX22190_ConfigureInputFilter(&DI_Devices[0], MAX22190_FLT1_ADDR, FILTER_DELAY_20000us, USE_IN_FLT, WIRE_BREAK_ENABLED);
	MAX22190_ConfigureInputFilter(&DI_Devices[0], MAX22190_FLT2_ADDR, FILTER_DELAY_20000us, USE_IN_FLT, WIRE_BREAK_ENABLED);
	MAX22190_ConfigureInputFilter(&DI_Devices[0], MAX22190_FLT3_ADDR, FILTER_DELAY_20000us, USE_IN_FLT, WIRE_BREAK_ENABLED);
	MAX22190_ConfigureInputFilter(&DI_Devices[0], MAX22190_FLT4_ADDR, FILTER_DELAY_20000us, USE_IN_FLT, WIRE_BREAK_ENABLED);
	MAX22190_ConfigureInputFilter(&DI_Devices[0], MAX22190_FLT5_ADDR, FILTER_DELAY_20000us, USE_IN_FLT, WIRE_BREAK_ENABLED);
	MAX22190_ConfigureInputFilter(&DI_Devices[0], MAX22190_FLT6_ADDR, FILTER_DELAY_20000us, USE_IN_FLT, WIRE_BREAK_ENABLED);
	MAX22190_ConfigureInputFilter(&DI_Devices[0], MAX22190_FLT7_ADDR, FILTER_DELAY_20000us, USE_IN_FLT, WIRE_BREAK_ENABLED);
	MAX22190_ConfigureInputFilter(&DI_Devices[0], MAX22190_FLT8_ADDR, FILTER_DELAY_20000us, USE_IN_FLT, WIRE_BREAK_ENABLED);

	// Config Fault Enables
	FAULT2EN.dataByte = 0x3F;
	MAX22190_ConfigureFault2EN(&DI_Devices[0], FAULT2EN.dataByte);

	FAULT1EN.dataByte = 0xC0;
	FAULT1EN.bits.FAULT2_EN = 1;
	FAULT1EN.bits.VL_24_EN = 1;
	FAULT1EN.bits.VM_24_EN = 1;
	MAX22190_ConfigureFault1EN(&DI_Devices[0], FAULT1EN.dataByte);

	CFG.dataByte = 0x00;
	CFG.bits.VF_24 = 1;
	MAX22190_ConfigureCFG(&DI_Devices[0], CFG.dataByte);

	// Enable Fault pin sticky
//	MAX22190_EnableFaultPinSticky(&DI_Devices[0]);

	// ----------------------------------------------------------------------
	// Device 2 Config
	// ----------------------------------------------------------------------
	// Config channels
	MAX22190_ConfigureChannels(&DI_Devices[1], MAX22190_ENABLE_ALL_CHANNELS);

	// Config Filters
	MAX22190_ConfigureInputFilter(&DI_Devices[1], MAX22190_FLT1_ADDR, FILTER_DELAY_20000us, USE_IN_FLT, WIRE_BREAK_ENABLED);
	MAX22190_ConfigureInputFilter(&DI_Devices[1], MAX22190_FLT2_ADDR, FILTER_DELAY_20000us, USE_IN_FLT, WIRE_BREAK_ENABLED);
	MAX22190_ConfigureInputFilter(&DI_Devices[1], MAX22190_FLT3_ADDR, FILTER_DELAY_20000us, USE_IN_FLT, WIRE_BREAK_ENABLED);
	MAX22190_ConfigureInputFilter(&DI_Devices[1], MAX22190_FLT4_ADDR, FILTER_DELAY_20000us, USE_IN_FLT, WIRE_BREAK_ENABLED);
	MAX22190_ConfigureInputFilter(&DI_Devices[1], MAX22190_FLT5_ADDR, FILTER_DELAY_20000us, USE_IN_FLT, WIRE_BREAK_ENABLED);
	MAX22190_ConfigureInputFilter(&DI_Devices[1], MAX22190_FLT6_ADDR, FILTER_DELAY_20000us, USE_IN_FLT, WIRE_BREAK_ENABLED);
	MAX22190_ConfigureInputFilter(&DI_Devices[1], MAX22190_FLT7_ADDR, FILTER_DELAY_20000us, USE_IN_FLT, WIRE_BREAK_ENABLED);
	MAX22190_ConfigureInputFilter(&DI_Devices[1], MAX22190_FLT8_ADDR, FILTER_DELAY_20000us, USE_IN_FLT, WIRE_BREAK_ENABLED);

	// Config Fault Enables
	FAULT2EN.dataByte = 0x3F;
	MAX22190_ConfigureFault2EN(&DI_Devices[1], FAULT2EN.dataByte);

	FAULT1EN.dataByte = 0xC0;
	FAULT1EN.bits.FAULT2_EN = 1;
	FAULT1EN.bits.VL_24_EN = 1;
	FAULT1EN.bits.VM_24_EN = 1;
	MAX22190_ConfigureFault1EN(&DI_Devices[1], FAULT1EN.dataByte);

	CFG.dataByte = 0x00;
	CFG.bits.VF_24 = 1;
	MAX22190_ConfigureCFG(&DI_Devices[1], CFG.dataByte);

	// Enable Fault pin sticky
//	MAX22190_EnableFaultPinSticky(&DI_Devices[1]);
}

void DigitalInput_ReadInputTest(void) {
	MAX22190_Device_t *dev = &DI_Devices[1];
	MAX22190_ReadDigitalInputs(dev);
}

void DigitalInput_ReadFaultTest(void) {
	MAX22190_Device_t *dev = &DI_Devices[DI_DeviceIndex];
	MAX22190_Read_FAULT1(dev);
	MAX22190_Read_FAULT2(dev);
	MAX22190_Read_WB(dev);
}

void DigitalInput_CrcErrorTest(void) {
	MAX22190_Device_t *dev = &DI_Devices[DI_DeviceIndex];

	MAX22190_TxBuffer[0] = 0x1E;
	MAX22190_TxBuffer[1] = 0xFF;
	MAX22190_TxBuffer[2] = 0x00;

	MAX22190_CS_Select(dev);
    HAL_SPI_TransmitReceive(dev->hspi, MAX22190_TxBuffer, MAX22190_RxBuffer, MAX22190_SPI_BUFFER_SIZE, 100);
    MAX22190_CS_Deselect(dev);
}

void Read_DigitalInput_DMA(void) {
	if (DI_ReadyToRead)
	{
		if (DI_DeviceIndex == 0)
		{
			MAX22190_ReadInputs_DMA(&DI_Devices[DI_DeviceIndex]);
		}
		else
		{
			// Check the CRC and store the read data
			if (MAX22190_CheckCRC(MAX22190_RxBuffer) == MAX22190_OK)
			{
				DI_Devices[DI_DeviceIndex - 1].DI_Status = MAX22190_RxBuffer[1];
				DI_Devices[DI_DeviceIndex - 1].CrcError = false;
			}
			else {
				DI_Devices[DI_DeviceIndex - 1].CrcError = true;
			}

			if (DI_DeviceIndex < NUM_DI_DEVICES)
			{
				MAX22190_ReadInputs_DMA(&DI_Devices[DI_DeviceIndex]);
			}
			else
			{
				DI_DeviceIndex = 0;
				DigitalInput_UpdateDatabase();
				DI_ReadyToProcess = true;

				// Check for CRC Errors in all devices
				for (int i = 0; i < NUM_DI_DEVICES; i++) {
					MAX22190_Device_t *dev = &DI_Devices[i];
					if (dev->CrcError == true) {
						DI_CrcError = true;
					}
				}
			}
		}
	}
}

void DigitalInput_DMA_ReadCompleteCallback(SPI_HandleTypeDef *hspi) {

	if (hspi->Instance == DI_SPI.Instance)
	{
		DigitalInput_Deselect_all_CS();

		DI_DeviceIndex++;

		// Update the flag
		DI_ReadyToRead = true;
	}
}

static void DigitalInput_UpdateDatabase(void) {
	for (int i = 0; i < NUM_DI_DEVICES; i++) {
		MAX22190_Device_t *dev = &DI_Devices[i];
		uint8_t dev_DI_idx = dev->DB_Index;
		uint8_t dev_DI_status = dev->DI_Status;
		DI_DB[dev_DI_idx] = dev_DI_status;
	}
//	DI_DB[0] = DI_Devices[0].DI_Status;
//	DI_DB[1] = DI_Devices[1].DI_Status;
}

void DigitalInput_CheckFaultStatus(void) {
	bool tempFaultFlag = false;
	for (int i = 0; i < NUM_DI_DEVICES; i++) {
		MAX22190_Device_t *dev = &DI_Devices[i];
		MAX22190_CheckFaultStatus(dev);
		if (dev->faultFlag == true)
		{
			tempFaultFlag = true;
			break;
		}
	}
	DI_FaultFlag = tempFaultFlag;
}

void DigitalInput_ReadFaults(void) {
	for (int i = 0; i < NUM_DI_DEVICES; i++) {
		MAX22190_Device_t *dev = &DI_Devices[i];
		if (dev->faultFlag == true)
		{
			MAX22190_Read_FAULT1(dev);
			MAX22190_Read_FAULT2(dev);
			MAX22190_Read_WB(dev);
		}
	}
}

void DigitalInput_VerifyConfiguration(void) {
	MAX22190_Device_t *dev = &DI_Devices[DI_DeviceIndex];
	MAX22190_ReadRegister(dev, MAX22190_FAULT1EN_ADDR);
	MAX22190_ReadRegister(dev, MAX22190_FAULT2EN_ADDR);
	MAX22190_ReadRegister(dev, MAX22190_CFG_ADDR);
	MAX22190_ReadRegister(dev, MAX22190_GPO_ADDR);
}

bool DigitalInput_IsOK(void) {
	// Return true only if BOTH are false
	return !DI_FaultFlag && !DI_CrcError;
}
