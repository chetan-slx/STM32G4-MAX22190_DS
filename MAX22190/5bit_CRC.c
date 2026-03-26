/*
 * 5bit_CRC.c
 *
 *  Created on: Aug 26, 2025
 *      Author: Chetan
 */


#include "5bit_CRC.h"


uint8_t calculate_crc5(const uint8_t *data) {
	int length = 19;             // number of bits to process
	uint8_t crc_step, tmp;
	uint8_t crc_init = 0x7;      // initial CRC seed = 00111b
	uint8_t crc_poly = 0x35;     // polynomial representation (x^5+x^4+x^2+1)
	int i;

	// Build 24-bit stream from 3 bytes (addr + data + placeholder)
	uint32_t datainput = (uint32_t)((data[0] << 16) | (data[1] << 8) | data[2]);

	// Clear last 5 bits and insert initial CRC seed
	datainput = (datainput & 0xFFFFE0) + crc_init;

	// Initialize first 6 bits for CRC step
	tmp = (uint8_t)((datainput & 0xFC0000) >> 18);

	if (tmp & 0x20)   // if MSB=1, apply polynomial
		crc_step = (uint8_t)(tmp ^ crc_poly);
	else
		crc_step = tmp;

	// Process remaining (length-1) = 18 bits
	for (i = 0; i < length - 1; i++) {
		// Shift CRC left and add next message bit
		tmp = (uint8_t)(((crc_step & 0x1F) << 1) +
				((datainput >> (length - 2 - i)) & 0x01));

		// Apply polynomial if MSB=1
		if (tmp & 0x20)
			crc_step = (uint8_t)(tmp ^ crc_poly);
		else
			crc_step = tmp;
	}

	// Return final 5-bit CRC value
	return (uint8_t)(crc_step & 0x1F);
}
