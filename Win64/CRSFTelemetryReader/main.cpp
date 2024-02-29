/*
 * Copyright (C) Rustam Iskenderov
 *
 * Based on code named
 *   edgetx - https://github.com/EdgeTX/edgetx
 *
 * License GPLv2: http://www.gnu.org/licenses/gpl-2.0.html
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <Windows.h>
#include <iostream>

#include "crossfire.h"

LPCTSTR pcCommPortWin32DevicePath = TEXT("\\\\.\\COM14");

void processCrossfireTelemetryValue(uint8_t index, int32_t value)
{
	const CrossfireSensor& sensor = crossfireSensors[index];
	std::cout << '\t' << sensor.name << " " << value << std::endl;
}

int main() {
	HANDLE hSerial;
	DCB dcbSerialParams = { 0 };
	COMMTIMEOUTS timeouts = { 0 };

	// Open the serial port
	hSerial = CreateFile(pcCommPortWin32DevicePath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hSerial == INVALID_HANDLE_VALUE)
	{
		if (GetLastError() == ERROR_FILE_NOT_FOUND)
			std::cerr << "Error: COM port not available" << std::endl;
		else
			std::cerr << "Error: Unable to open COM port" << std::endl;
		return 1;
	}

	// Set device parameters (baud rate, etc.)
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	if (!GetCommState(hSerial, &dcbSerialParams))
	{
		std::cerr << "Error: Unable to get serial port state" << std::endl;
		CloseHandle(hSerial);
		return 1;
	}

	dcbSerialParams.BaudRate = CBR_9600; // Set baud rate to 9600
	dcbSerialParams.ByteSize = 8; // 8 data bits
	dcbSerialParams.StopBits = ONESTOPBIT; // 1 stop bit
	dcbSerialParams.Parity = NOPARITY; // No parity
	if (!SetCommState(hSerial, &dcbSerialParams))
	{
		std::cerr << "Error: Unable to set serial port state" << std::endl;
		CloseHandle(hSerial);
		return 1;
	}

	// Set timeouts
	timeouts.ReadIntervalTimeout = 50;
	timeouts.ReadTotalTimeoutConstant = 50;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 50;
	timeouts.WriteTotalTimeoutMultiplier = 10;

	if (!SetCommTimeouts(hSerial, &timeouts))
	{
		std::cerr << "Error: Unable to set serial port timeouts" << std::endl;
		CloseHandle(hSerial);
		return 1;
	}

	// Read data from the serial port	
	DWORD bytesRead;
	uint8_t buf[1024];
	if (!ReadFile(hSerial, buf, sizeof(buf), &bytesRead, NULL))
	{
		std::cerr << "Error: Unable to read from serial port" << std::endl;
		CloseHandle(hSerial);
		return 1;
	}

	CloseHandle(hSerial);

	uint32_t idx = 0;
	while (idx < bytesRead)
	{
		uint8_t* rxBuffer = buf + idx;

		// rxBuffer structure
		// 0 - RADIO_ADDRESS
		// 1 - len
		// 2 - id
		// (len + 1) - crc, crc8(&rxBuffer[2], len - 1);

		if (rxBuffer[0] != RADIO_ADDRESS)
		{
			++idx;
			continue;
		}

		int len = rxBuffer[1];

		if (len < MIN_FRAME_LEN)
		{
			std::cerr << "Error: incorrent length" << std::endl;
			break;
		}

		int32_t value;

		switch (rxBuffer[2])
		{
		case LINK_ID:
			std::cout << "LINK_ID" << std::endl;

			for (unsigned int i = 0; i <= TX_SNR_INDEX; i++) {
				if (getCrossfireTelemetryValue<1>(3 + i, value, rxBuffer)) {
					if (i == TX_POWER_INDEX) {
						static const int32_t power_values[] = { 0,    10,   25,  100, 500,
															   1000, 2000, 250, 50 };
						value =
							((unsigned)value < DIM(power_values) ? power_values[value] : 0);
					}
					processCrossfireTelemetryValue(i, value);
				}
			}

			break;
		case GPS_ID:
			std::cout << "GPS_ID" << std::endl;

			if (getCrossfireTelemetryValue<4>(3, value, rxBuffer))
				processCrossfireTelemetryValue(GPS_LATITUDE_INDEX, value / 10);
			if (getCrossfireTelemetryValue<4>(7, value, rxBuffer))
				processCrossfireTelemetryValue(GPS_LONGITUDE_INDEX, value / 10);
			if (getCrossfireTelemetryValue<2>(11, value, rxBuffer))
				processCrossfireTelemetryValue(GPS_GROUND_SPEED_INDEX, value);
			if (getCrossfireTelemetryValue<2>(13, value, rxBuffer))
				processCrossfireTelemetryValue(GPS_HEADING_INDEX, value);
			if (getCrossfireTelemetryValue<2>(15, value, rxBuffer))
				processCrossfireTelemetryValue(GPS_ALTITUDE_INDEX, value - 1000);
			if (getCrossfireTelemetryValue<1>(17, value, rxBuffer))
				processCrossfireTelemetryValue(GPS_SATELLITES_INDEX, value);

			break;
		case LINK_RX_ID:
			std::cout << "LINK_RX_ID" << std::endl;

			if (getCrossfireTelemetryValue<1>(4, value, rxBuffer))
				processCrossfireTelemetryValue(RX_RSSI_PERC_INDEX, value);
			if (getCrossfireTelemetryValue<1>(7, value, rxBuffer))
				processCrossfireTelemetryValue(TX_RF_POWER_INDEX, value);
			break;

		case LINK_TX_ID:
			std::cout << "LINK_TX_ID" << std::endl;

			if (getCrossfireTelemetryValue<1>(4, value, rxBuffer))
				processCrossfireTelemetryValue(TX_RSSI_PERC_INDEX, value);
			if (getCrossfireTelemetryValue<1>(7, value, rxBuffer))
				processCrossfireTelemetryValue(RX_RF_POWER_INDEX, value);
			if (getCrossfireTelemetryValue<1>(8, value, rxBuffer))
				processCrossfireTelemetryValue(TX_FPS_INDEX, value * 10);
			break;

		case BATTERY_ID:
			std::cout << "BATTERY_ID" << std::endl;

			if (getCrossfireTelemetryValue<2>(3, value, rxBuffer))
				processCrossfireTelemetryValue(BATT_VOLTAGE_INDEX, value);
			if (getCrossfireTelemetryValue<2>(5, value, rxBuffer))
				processCrossfireTelemetryValue(BATT_CURRENT_INDEX, value);
			if (getCrossfireTelemetryValue<3>(7, value, rxBuffer))
				processCrossfireTelemetryValue(BATT_CAPACITY_INDEX, value);
			if (getCrossfireTelemetryValue<1>(10, value, rxBuffer))
				processCrossfireTelemetryValue(BATT_REMAINING_INDEX, value);
			break;

		case ATTITUDE_ID:
			std::cout << "ATTITUDE_ID" << std::endl;

			if (getCrossfireTelemetryValue<2>(3, value, rxBuffer))
				processCrossfireTelemetryValue(ATTITUDE_PITCH_INDEX, value / 10);
			if (getCrossfireTelemetryValue<2>(5, value, rxBuffer))
				processCrossfireTelemetryValue(ATTITUDE_ROLL_INDEX, value / 10);
			if (getCrossfireTelemetryValue<2>(7, value, rxBuffer))
				processCrossfireTelemetryValue(ATTITUDE_YAW_INDEX, value / 10);
			break;

		case FLIGHT_MODE_ID:
		{
			const CrossfireSensor& sensor = crossfireSensors[FLIGHT_MODE_INDEX];
			auto textLength = std::min<int>(16, rxBuffer[1]);
			rxBuffer[textLength] = '\0';

			std::cout << "FLIGHT_MODE_ID" << std::endl;
			std::cout << '\t' << (const char*)rxBuffer + 3 << std::endl;

			break;
		}
		}

		idx += len + 2; // +1 for crc, +1 for address
	}

	return 0;
}
