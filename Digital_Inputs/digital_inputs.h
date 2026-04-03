/*
 * digital_input.h
 *
 *  Created on: Aug 28, 2025
 *      Author: Chetan
 */

#ifndef MAX22190_DIGITAL_INPUTS_H_
#define MAX22190_DIGITAL_INPUTS_H_

#include "MAX22190.h"

/**
 * @def NUM_DI_DEVICES
 * @brief
 *
 */
#define NUM_DI_DEVICES 2

/**
 * @def DI_SPI
 * @brief
 *
 */
#define DI_SPI hspi3

/**
 * @var DI_FaultFlag
 * @brief
 *
 */
extern volatile bool DI_FaultFlag;

/**
 * @var DI_ReadyToRead
 * @brief
 *
 */
extern volatile bool DI_ReadyToRead;

/**
 * @var DI_ReadyToProcess
 * @brief
 *
 */
extern volatile bool DI_ReadyToProcess;

/**
 * @var DI_CrcError
 * @brief
 *
 */
extern volatile bool DI_CrcError;

/**
 * @name        DigitalInput_Init
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
void DigitalInput_Init(void);

/**
 * @name        DigitalInput_ReadInputTest
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
void DigitalInput_ReadInputTest(void);

/**
 * @name        Read_DigitalInput_DMA
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
void Read_DigitalInput_DMA(void);

/**
 * @name        DigitalInput_CheckFaultStatus
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
void DigitalInput_CheckFaultStatus(void);

/**
 * @name        DigitalInput_ReadFaultTest
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
void DigitalInput_ReadFaultTest(void);

/**
 * @name        DigitalInput_ReadFaults
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
void DigitalInput_ReadFaults(void);

/**
 * @name        DigitalInput_CrcErrorTest
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
void DigitalInput_CrcErrorTest(void);

/**
 * @name        DigitalInput_DMA_ReadCompleteCallback
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
void DigitalInput_DMA_ReadCompleteCallback(SPI_HandleTypeDef *hspi);

/**
 * @name        DigitalInput_HasFault
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
bool DigitalInput_IsOK(void);

#endif /* MAX22190_DIGITAL_INPUTS_H_ */
