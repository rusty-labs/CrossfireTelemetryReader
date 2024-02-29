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

#pragma once

 // Device address
#define BROADCAST_ADDRESS              0x00
#define RADIO_ADDRESS                  0xEA
#define MODULE_ADDRESS                 0xEE

// Frame id
#define GPS_ID                         0x02
#define CF_VARIO_ID                    0x07
#define BATTERY_ID                     0x08
#define BARO_ALT_ID                    0x09
#define LINK_ID                        0x14
#define CHANNELS_ID                    0x16
#define LINK_RX_ID                     0x1C
#define LINK_TX_ID                     0x1D
#define ATTITUDE_ID                    0x1E
#define FLIGHT_MODE_ID                 0x21
#define PING_DEVICES_ID                0x28
#define DEVICE_INFO_ID                 0x29
#define REQUEST_SETTINGS_ID            0x2A
#define COMMAND_ID                     0x32
#define RADIO_ID                       0x3A

#define UART_SYNC                      0xC8
#define SUBCOMMAND_CRSF                0x10
#define COMMAND_MODEL_SELECT_ID        0x05

#define MIN_FRAME_LEN 3

enum CrossfireSensorIndexes {
	RX_RSSI1_INDEX,
	RX_RSSI2_INDEX,
	RX_QUALITY_INDEX,
	RX_SNR_INDEX,
	RX_ANTENNA_INDEX,
	RF_MODE_INDEX,
	TX_POWER_INDEX,
	TX_RSSI_INDEX,
	TX_QUALITY_INDEX,
	TX_SNR_INDEX,
	RX_RSSI_PERC_INDEX,
	RX_RF_POWER_INDEX,
	TX_RSSI_PERC_INDEX,
	TX_RF_POWER_INDEX,
	TX_FPS_INDEX,
	BATT_VOLTAGE_INDEX,
	BATT_CURRENT_INDEX,
	BATT_CAPACITY_INDEX,
	BATT_REMAINING_INDEX,
	GPS_LATITUDE_INDEX,
	GPS_LONGITUDE_INDEX,
	GPS_GROUND_SPEED_INDEX,
	GPS_HEADING_INDEX,
	GPS_ALTITUDE_INDEX,
	GPS_SATELLITES_INDEX,
	ATTITUDE_PITCH_INDEX,
	ATTITUDE_ROLL_INDEX,
	ATTITUDE_YAW_INDEX,
	FLIGHT_MODE_INDEX,
	VERTICAL_SPEED_INDEX,
	BARO_ALTITUDE_INDEX,
	UNKNOWN_INDEX,
};

enum TelemetryUnit {
	UNIT_RAW,
	UNIT_VOLTS,
	UNIT_AMPS,
	UNIT_MILLIAMPS,
	UNIT_KTS,
	UNIT_METERS_PER_SECOND,
	UNIT_FEET_PER_SECOND,
	UNIT_KMH,
	UNIT_SPEED = UNIT_KMH,
	UNIT_MPH,
	UNIT_METERS,
	UNIT_DIST = UNIT_METERS,
	UNIT_FEET,
	UNIT_CELSIUS,
	UNIT_TEMPERATURE = UNIT_CELSIUS,
	UNIT_FAHRENHEIT,
	UNIT_PERCENT,
	UNIT_MAH,
	UNIT_WATTS,
	UNIT_MILLIWATTS,
	UNIT_DB,
	UNIT_RPMS,
	UNIT_G,
	UNIT_DEGREE,
	UNIT_RADIANS,
	UNIT_MILLILITERS,
	UNIT_FLOZ,
	UNIT_MILLILITERS_PER_MINUTE,
	UNIT_HERTZ,
	UNIT_MS,
	UNIT_US,
	UNIT_KM,
	UNIT_DBM,
	UNIT_MAX = UNIT_DBM,
	UNIT_SPARE6,
	UNIT_SPARE7,
	UNIT_SPARE8,
	UNIT_SPARE9,
	UNIT_SPARE10,
	UNIT_HOURS,
	UNIT_MINUTES,
	UNIT_SECONDS,
	// FrSky format used for these fields, could be another format in the future
	UNIT_FIRST_VIRTUAL,
	UNIT_CELLS = UNIT_FIRST_VIRTUAL,
	UNIT_DATETIME,
	UNIT_GPS,
	UNIT_BITFIELD,
	UNIT_TEXT,
	// Internal units (not stored in sensor unit)
	UNIT_GPS_LONGITUDE,
	UNIT_GPS_LATITUDE,
	UNIT_DATETIME_YEAR,
	UNIT_DATETIME_DAY_MONTH,
	UNIT_DATETIME_HOUR_MIN,
	UNIT_DATETIME_SEC
};

struct CrossfireSensor {
	const uint8_t id;
	const uint8_t subId;
	const TelemetryUnit unit;
	const uint8_t precision;
	const char* name;
};

// Telemetry sensor name definitions
#define STR_SENSOR_RSSI                      "RSSI"
#define STR_SENSOR_R9PW                      "R9PW"
#define STR_SENSOR_RAS                       "SWR"
#define STR_SENSOR_A1                        "A1"
#define STR_SENSOR_A2                        "A2"
#define STR_SENSOR_A3                        "A3"
#define STR_SENSOR_A4                        "A4"
#define STR_SENSOR_BATT                      "RxBt"
#define STR_SENSOR_ALT                       "Alt"
#define STR_SENSOR_TEMP1                     "Tmp1"
#define STR_SENSOR_TEMP2                     "Tmp2"
#define STR_SENSOR_TEMP3                     "Tmp3"
#define STR_SENSOR_TEMP4                     "Tmp4"
#define STR_SENSOR_RPM2                      "RPM2"
#define STR_SENSOR_PRES                      "Pres"
#define STR_SENSOR_ODO1                      "Odo1"
#define STR_SENSOR_ODO2                      "Odo2"
#define STR_SENSOR_TXV                       "TX_V"
#define STR_SENSOR_CURR_SERVO1               "CSv1"
#define STR_SENSOR_CURR_SERVO2               "CSv2"
#define STR_SENSOR_CURR_SERVO3               "CSv3"
#define STR_SENSOR_CURR_SERVO4               "CSv4"
#define STR_SENSOR_DIST                      "Dist"
#define STR_SENSOR_ARM                       "Arm"
#define STR_SENSOR_C50                       "C50"
#define STR_SENSOR_C200                      "C200"
#define STR_SENSOR_RPM                       "RPM"
#define STR_SENSOR_FUEL                      "Fuel"
#define STR_SENSOR_VSPD                      "VSpd"
#define STR_SENSOR_ACCX                      "AccX"
#define STR_SENSOR_ACCY                      "AccY"
#define STR_SENSOR_ACCZ                      "AccZ"
#define STR_SENSOR_ACC                       "Acc"
#define STR_SENSOR_GYROX                     "GYRX"
#define STR_SENSOR_GYROY                     "GYRY"
#define STR_SENSOR_GYROZ                     "GYRZ"
#define STR_SENSOR_CURR                      "Curr"
#define STR_SENSOR_CAPACITY                  "Capa"
#define STR_SENSOR_VFAS                      "VFAS"
#define STR_SENSOR_ASPD                      "ASpd"
#define STR_SENSOR_GSPD                      "GSpd"
#define STR_SENSOR_HDG                       "Hdg"
#define STR_SENSOR_SATELLITES                "Sats"
#define STR_SENSOR_CELLS                     "Cels"
#define STR_SENSOR_GPSALT                    "GAlt"
#define STR_SENSOR_GPSDATETIME               "Date"
#define STR_SENSOR_GPS                       "GPS"
#define STR_SENSOR_BATT1_VOLTAGE             "RB1V"
#define STR_SENSOR_BATT2_VOLTAGE             "RB2V"
#define STR_SENSOR_BATT1_CURRENT             "RB1A"
#define STR_SENSOR_BATT2_CURRENT             "RB2A"
#define STR_SENSOR_BATT1_CONSUMPTION         "RB1C"
#define STR_SENSOR_BATT2_CONSUMPTION         "RB2C"
#define STR_SENSOR_BATT1_TEMP                "RB1T"
#define STR_SENSOR_BATT2_TEMP                "RB2T"
#define STR_SENSOR_RB_STATE                  "RBS"
#define STR_SENSOR_CHANS_STATE               "RBCS"
#define STR_SENSOR_RX_RSSI1                  "1RSS"
#define STR_SENSOR_RX_RSSI2                  "2RSS"
#define STR_SENSOR_RX_QUALITY                "RQly"
#define STR_SENSOR_RX_SNR                    "RSNR"
#define STR_SENSOR_RX_SIGNAL                 "Sgnl"
#define STR_SENSOR_RX_NOISE                  "RNse"
#define STR_SENSOR_ANTENNA                   "ANT"
#define STR_SENSOR_RF_MODE                   "RFMD"
#define STR_SENSOR_TX_POWER                  "TPWR"
#define STR_SENSOR_TX_RSSI                   "TRSS"
#define STR_SENSOR_TX_QUALITY                "TQly"
#define STR_SENSOR_RX_RSSI_PERC              "RRSP"
#define STR_SENSOR_RX_RF_POWER               "RPWR"
#define STR_SENSOR_TX_RSSI_PERC              "TRSP"
#define STR_SENSOR_TX_FPS                    "TFPS"
#define STR_SENSOR_TX_SNR                    "TSNR"
#define STR_SENSOR_TX_NOISE                  "TNse"
#define STR_SENSOR_PITCH                     "Ptch"
#define STR_SENSOR_ROLL                      "Roll"
#define STR_SENSOR_YAW                       "Yaw"
#define STR_SENSOR_FLIGHT_MODE               "FM"
#define STR_SENSOR_THROTTLE                  "Thr"
#define STR_SENSOR_QOS_A                     "FdeA"
#define STR_SENSOR_QOS_B                     "FdeB"
#define STR_SENSOR_QOS_L                     "FdeL"
#define STR_SENSOR_QOS_R                     "FdeR"
#define STR_SENSOR_QOS_F                     "FLss"
#define STR_SENSOR_QOS_H                     "Hold"
#define STR_SENSOR_BIND                      "BIND"
#define STR_SENSOR_LAP_NUMBER                "Lap "
#define STR_SENSOR_GATE_NUMBER               "Gate"
#define STR_SENSOR_LAP_TIME                  "LapT"
#define STR_SENSOR_GATE_TIME                 "GteT"
#define STR_SENSOR_ESC_VOLTAGE               "EscV"
#define STR_SENSOR_ESC_CURRENT               "EscA"
#define STR_SENSOR_ESC_RPM                   "EscR"   //FrSky name
#define STR_SENSOR_ESC_RPM2                  "Erpm"   //Spektrum name
#define STR_SENSOR_ESC_CONSUMPTION           "EscC"
#define STR_SENSOR_ESC_TEMP                  "EscT"
#define STR_SENSOR_SD1_CHANNEL               "Chan"
#define STR_SENSOR_GASSUIT_TEMP1             "GTp1"
#define STR_SENSOR_GASSUIT_TEMP2             "GTp2"
#define STR_SENSOR_GASSUIT_RPM               "GRPM"
#define STR_SENSOR_GASSUIT_FLOW              "GFlo"
#define STR_SENSOR_GASSUIT_CONS              "GFue"
#define STR_SENSOR_GASSUIT_RES_VOL           "GRVl"
#define STR_SENSOR_GASSUIT_RES_PERC          "GRPc"
#define STR_SENSOR_GASSUIT_MAX_FLOW          "GMFl"
#define STR_SENSOR_GASSUIT_AVG_FLOW          "GAFl"
#define STR_SENSOR_SBEC_VOLTAGE              "BecV"
#define STR_SENSOR_SBEC_CURRENT              "BecA"
#define STR_SENSOR_LOSS                      "Loss" 
#define STR_SENSOR_FLOW                      "Flow"
#define STR_SENSOR_SPEED                     "Spd"
#define STR_SENSOR_FRAME_RATE                "FRat"
#define STR_SENSOR_TOTAL_LATENCY             "TLat"
#define STR_SENSOR_VTX_FREQ                  "VFrq"
#define STR_SENSOR_VTX_PWR                   "VPwr"
#define STR_SENSOR_VTX_CHAN                  "VChn"
#define STR_SENSOR_VTX_BAND                  "VBan"
#define STR_SENSOR_BATT_PERCENT              "Bat%"
#define STR_SENSOR_ESC_VIN                   "EVIN"
#define STR_SENSOR_ESC_TFET                  "TFET"
#define STR_SENSOR_ESC_CUR                   "ECUR"
#define STR_SENSOR_ESC_TBEC                  "TBEC"
#define STR_SENSOR_ESC_BCUR                  "CBEC"
#define STR_SENSOR_ESC_VBEC                  "VBEC"
#define STR_SENSOR_ESC_THR                   "ETHR"
#define STR_SENSOR_ESC_POUT                  "EOUT"
#define STR_SENSOR_SMART_BAT_BTMP            "BTmp"
#define STR_SENSOR_SMART_BAT_BCUR            "BCur"
#define STR_SENSOR_SMART_BAT_BCAP            "BUse"
#define STR_SENSOR_SMART_BAT_MIN_CEL         "CLMi"
#define STR_SENSOR_SMART_BAT_MAX_CEL         "CLMa"
#define STR_SENSOR_SMART_BAT_CYCLES          "Cycl"
#define STR_SENSOR_SMART_BAT_CAPACITY        "BCpT"
#define STR_SENSOR_CL01                      "Cel1"
#define STR_SENSOR_CL02                      "Cel2"
#define STR_SENSOR_CL03                      "Cel3"
#define STR_SENSOR_CL04                      "Cel4"
#define STR_SENSOR_CL05                      "Cel5"
#define STR_SENSOR_CL06                      "Cel6"
#define STR_SENSOR_CL07                      "Cel7"
#define STR_SENSOR_CL08                      "Cel8"
#define STR_SENSOR_CL09                      "Cel9"
#define STR_SENSOR_CL10                      "Cl10"
#define STR_SENSOR_CL11                      "Cl11"
#define STR_SENSOR_CL12                      "Cl12"
#define STR_SENSOR_CL13                      "Cl13"
#define STR_SENSOR_CL14                      "Cl14"
#define STR_SENSOR_CL15                      "Cl15"
#define STR_SENSOR_CL16                      "Cl16"
#define STR_SENSOR_CL17                      "Cl17"
#define STR_SENSOR_CL18                      "Cl18"
#define STR_SENSOR_VFR                       "VFR"
#define STR_SENSOR_RB3040_EXTRA_STATE        "RBES"
#define STR_SENSOR_RB3040_CHANNEL1           "CH1A"
#define STR_SENSOR_RB3040_CHANNEL2           "CH2A"
#define STR_SENSOR_RB3040_CHANNEL3           "CH3A"
#define STR_SENSOR_RB3040_CHANNEL4           "CH4A"
#define STR_SENSOR_RB3040_CHANNEL5           "CH5A"
#define STR_SENSOR_RB3040_CHANNEL6           "CH6A"
#define STR_SENSOR_RB3040_CHANNEL7           "CH7A"
#define STR_SENSOR_RB3040_CHANNEL8           "CH8A"
#define STR_SENSOR_SERVO_CURRENT             "SrvA"
#define STR_SENSOR_SERVO_VOLTAGE             "SrvV"
#define STR_SENSOR_SERVO_TEMPERATURE         "SrvT"
#define STR_SENSOR_SERVO_STATUS              "SrvS"
#define STR_SENSOR_SPECIAL                   "Spcl"

#define CS(id,subId,name,unit,precision) {id,subId,unit,precision,name}

const CrossfireSensor crossfireSensors[] = {
  CS(LINK_ID,        0, STR_SENSOR_RX_RSSI1,      UNIT_DB,                0),
  CS(LINK_ID,        1, STR_SENSOR_RX_RSSI2,      UNIT_DB,                0),
  CS(LINK_ID,        2, STR_SENSOR_RX_QUALITY,    UNIT_PERCENT,           0),
  CS(LINK_ID,        3, STR_SENSOR_RX_SNR,        UNIT_DB,                0),
  CS(LINK_ID,        4, STR_SENSOR_ANTENNA,       UNIT_RAW,               0),
  CS(LINK_ID,        5, STR_SENSOR_RF_MODE,       UNIT_RAW,               0),
  CS(LINK_ID,        6, STR_SENSOR_TX_POWER,      UNIT_MILLIWATTS,        0),
  CS(LINK_ID,        7, STR_SENSOR_TX_RSSI,       UNIT_DB,                0),
  CS(LINK_ID,        8, STR_SENSOR_TX_QUALITY,    UNIT_PERCENT,           0),
  CS(LINK_ID,        9, STR_SENSOR_TX_SNR,        UNIT_DB,                0),
  CS(LINK_RX_ID,     0, STR_SENSOR_RX_RSSI_PERC,  UNIT_PERCENT,           0),
  CS(LINK_RX_ID,     1, STR_SENSOR_RX_RF_POWER,   UNIT_DBM,               0),
  CS(LINK_TX_ID,     0, STR_SENSOR_TX_RSSI_PERC,  UNIT_PERCENT,           0),
  CS(LINK_TX_ID,     1, STR_SENSOR_TX_POWER,      UNIT_DBM,               0),
  CS(LINK_TX_ID,     2, STR_SENSOR_TX_FPS,        UNIT_HERTZ,             0),
  CS(BATTERY_ID,     0, STR_SENSOR_BATT,          UNIT_VOLTS,             1),
  CS(BATTERY_ID,     1, STR_SENSOR_CURR,          UNIT_AMPS,              1),
  CS(BATTERY_ID,     2, STR_SENSOR_CAPACITY,      UNIT_MAH,               0),
  CS(BATTERY_ID,     3, STR_SENSOR_BATT_PERCENT,  UNIT_PERCENT,           0),
  CS(GPS_ID,         0, STR_SENSOR_GPS,           UNIT_GPS_LATITUDE,      0),
  CS(GPS_ID,         0, STR_SENSOR_GPS,           UNIT_GPS_LONGITUDE,     0),
  CS(GPS_ID,         2, STR_SENSOR_GSPD,          UNIT_KMH,               1),
  CS(GPS_ID,         3, STR_SENSOR_HDG,           UNIT_DEGREE,            2),
  CS(GPS_ID,         4, STR_SENSOR_ALT,           UNIT_METERS,            0),
  CS(GPS_ID,         5, STR_SENSOR_SATELLITES,    UNIT_RAW,               0),
  CS(ATTITUDE_ID,    0, STR_SENSOR_PITCH,         UNIT_RADIANS,           3),
  CS(ATTITUDE_ID,    1, STR_SENSOR_ROLL,          UNIT_RADIANS,           3),
  CS(ATTITUDE_ID,    2, STR_SENSOR_YAW,           UNIT_RADIANS,           3),
  CS(FLIGHT_MODE_ID, 0, STR_SENSOR_FLIGHT_MODE,   UNIT_TEXT,              0),
  CS(CF_VARIO_ID,    0, STR_SENSOR_VSPD,          UNIT_METERS_PER_SECOND, 2),
  CS(BARO_ALT_ID,    0, STR_SENSOR_ALT,           UNIT_METERS,            2),
  CS(0,              0, "UNKNOWN",          UNIT_RAW,               0),
};

#if !defined(DIM)
#define DIM(__arr) (sizeof((__arr)) / sizeof((__arr)[0]))
#endif

template <int N>
bool getCrossfireTelemetryValue(uint8_t index, int32_t& value,
	uint8_t* rxBuffer)
{
	bool result = false;
	uint8_t* byte = &rxBuffer[index];
	value = (*byte & 0x80) ? -1 : 0;
	for (uint8_t i = 0; i < N; i++) {
		value <<= 8;
		if (*byte != 0xff) {
			result = true;
		}
		value += *byte++;
	}
	return result;
}
