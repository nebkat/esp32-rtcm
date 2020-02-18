/* 
 * This file is part of the ESP32-RTCM distribution (https://github.com/nebkat/esp32-rtcm).
 * Copyright (c) 2020 Nebojsa Cvetkovic.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef RTCM_PROTOCOL_H
#define RTCM_PROTOCOL_H

#include <stdint.h>
#include <stdbool.h>

#define RTCM_HEADER_SYNC_CHAR 0xD3

#define RTCM_MESSAGE_MAX_LENGTH 1023

typedef enum {
    // RTCM_MT_EXPERIMENTAL = 1,
    // RTCM_MT_EXPERIMENTAL = ...,
    // RTCM_MT_EXPERIMENTAL = 100,

    RTCM_MT_GPS_L1_OBSERVATIONS = 1001,
    RTCM_MT_GPS_L1_OBSERVATIONS_EXTENDED = 1002,
    RTCM_MT_GPS_L1_L2_OBSERVATIONS = 1003,
    RTCM_MT_GPS_L1_L2_OBSERVATIONS_EXTENDED = 1004,

    RTCM_MT_STATION_ARP = 1005,
    RTCM_MT_STATION_ARP_HEIGHT = 1006,

    RTCM_MT_ANTENNA_DESCRIPTOR = 1007,
    RTCM_MT_ANTENNA_DESCRIPTOR_SERIAL = 1008,

    RTCM_MT_GLONASS_L1_OBSERVATIONS = 1009,
    RTCM_MT_GLONASS_L1_OBSERVATIONS_EXTENDED = 1010,
    RTCM_MT_GLONASS_L1_L2_OBSERVATIONS = 1011,
    RTCM_MT_GLONASS_L1_L2_OBSERVATIONS_EXTENDED = 1012,

    RTCM_MT_AUXILIARY_OPERATION_INFORMATION = 1013,

    RTCM_MT_NETWORK_AUXILIARY_STATION_DATA = 1014,

    RTCM_MT_GPS_IONOSPHERIC_CORRECTION_DIFFERENCE = 1015,
    RTCM_MT_GPS_GEOMETRIC_CORRECTION_DIFFERENCE = 1016,
    RTCM_MT_GPS_COMBINED_CORRECTION_DIFFERENCE = 1017,
    RTCM_MT_GPS_RESERVED_ALTERNATIVE_IONOSPHERIC_CORRECTION_DIFFERENCE = 1018,

    RTCM_MT_GPS_EPHEMERIDES = 1019,
    RTCM_MT_GLONASS_EPHEMERIDES = 1020,

    RTCM_MT_HELMERT_ABRIDGED_MOLODENSKI_TRANSFORMATION_PARAMETERS = 1021,
    RTCM_MT_MOLODENSKI_BADEKAS_TRANSFORMATION_PARAMETERS = 1022,

    RTCM_MT_RESIDUALS_ELLIPSOIDAL_GRID_REPRESENTATION = 1023,
    RTCM_MT_RESIDUALS_PLANE_GRID_REPRESENTATION = 1024,

    RTCM_MT_PROJECTION_PARAMETERS_EXCEPT_LCC2SP_OM = 1025,
    RTCM_MT_PROJECTION_PARAMETERS_LCC2SP = 1026,
    RTCM_MT_PROJECTION_PARAMETERS_OM = 1027,

    RTCM_MT_RESERVED_GLOBAL_PLATE_FIXED_TRANSFORMATION = 1028,

    RTCM_MT_UNICODE_TEXT_STRING = 1029,

    RTCM_MT_GPS_NETWORK_RTK_RESIDUAL = 1030,
    RTCM_MT_GLONASS_NETWORK_RTK_RESIDUIAL = 1031,

    RTCM_MT_PHYSICAL_REFERENCE_STATION_POSITION = 1032,
    RTCM_MT_RECEIVER_ANTENNA_DESCRIPTOR = 1033,

    RTCM_MT_GPS_NETWORK_FKP_GRADIENT = 1034,
    RTCM_MT_GLONASS_NETWORK_FKP_GRADIENT = 1035,

    RTCM_MT_GLONASS_IONOSPHERIC_CORRECTION_DIFFERENCE = 1037,
    RTCM_MT_GLONASS_GEOMETRIC_CORRECTION_DIFFERENCE = 1038,
    RTCM_MT_GLONASS_COMBINED_CORRECTION_DIFFERENCE = 1039,

    RTCM_MT_BEIDOU_SATELLITE_EPHEMERIS = 1042,
    RTCM_MT_QZSS_SATELLITE_EPHEMERIS = 1044,
    RTCM_MT_GALILEO_F_NAV_SATELLITE_EPHEMERIS = 1045,
    RTCM_MT_GALILEO_I_NAV_SATELLITE_EPHEMERIS = 1046,

    RTCM_MT_SSR_GPS_ORBIT_CORRECTION = 1057,
    RTCM_MT_SSR_GPS_CLOCK_CORRECTION = 1058,
    RTCM_MT_SSR_GPS_CODE_BIAS = 1059,
    RTCM_MT_SSR_GPS_COMBINED_CORRECTION = 1060,
    RTCM_MT_SSR_GPS_URA = 1061,
    RTCM_MT_SSR_GPS_HIGH_RATE_CLOCK_CORRECTION = 1062,

    RTCM_MT_SSR_GLONASS_ORBIT_CORRECTION = 1063,
    RTCM_MT_SSR_GLONASS_CLOCK_CORRECTION = 1064,
    RTCM_MT_SSR_GLONASS_CODE_BIAS = 1065,
    RTCM_MT_SSR_GLONASS_COMBINED_CORRECTION = 1066,
    RTCM_MT_SSR_GLONASS_URA = 1067,
    RTCM_MT_SSR_GLONASS_HIGH_RATE_CLOCK_CORRECTION = 1068,

    // RTCM_MT_RESERVED_MSM = 1070,

    RTCM_MT_GPS_MSM1 = 1071,
    RTCM_MT_GPS_MSM2 = 1072,
    RTCM_MT_GPS_MSM3 = 1073,
    RTCM_MT_GPS_MSM4 = 1074,
    RTCM_MT_GPS_MSM5 = 1075,
    RTCM_MT_GPS_MSM6 = 1076,
    RTCM_MT_GPS_MSM7 = 1077,

    // RTCM_MT_RESERVED_MSM = 1078,
    // RTCM_MT_RESERVED_MSM = 1079,
    // RTCM_MT_RESERVED_MSM = 1080,

    RTCM_MT_GLONASS_MSM1 = 1081,
    RTCM_MT_GLONASS_MSM2 = 1082,
    RTCM_MT_GLONASS_MSM3 = 1083,
    RTCM_MT_GLONASS_MSM4 = 1084,
    RTCM_MT_GLONASS_MSM5 = 1085,
    RTCM_MT_GLONASS_MSM6 = 1086,
    RTCM_MT_GLONASS_MSM7 = 1087,

    // RTCM_MT_RESERVED_MSM = 1088,
    // RTCM_MT_RESERVED_MSM = 1089,
    // RTCM_MT_RESERVED_MSM = 1090,

    RTCM_MT_GALILEO_MSM1 = 1091,
    RTCM_MT_GALILEO_MSM2 = 1092,
    RTCM_MT_GALILEO_MSM3 = 1093,
    RTCM_MT_GALILEO_MSM4 = 1094,
    RTCM_MT_GALILEO_MSM5 = 1095,
    RTCM_MT_GALILEO_MSM6 = 1096,
    RTCM_MT_GALILEO_MSM7 = 1097,

    // RTCM_MT_RESERVED_MSM = 1098,
    // RTCM_MT_RESERVED_MSM = 1099,
    // RTCM_MT_RESERVED_MSM = 1100,

    RTCM_MT_SBAS_MSM1 = 1101,
    RTCM_MT_SBAS_MSM2 = 1102,
    RTCM_MT_SBAS_MSM3 = 1103,
    RTCM_MT_SBAS_MSM4 = 1104,
    RTCM_MT_SBAS_MSM5 = 1105,
    RTCM_MT_SBAS_MSM6 = 1106,
    RTCM_MT_SBAS_MSM7 = 1107,

    // RTCM_MT_RESERVED_MSM = 1108,
    // RTCM_MT_RESERVED_MSM = 1109,
    // RTCM_MT_RESERVED_MSM = 1110,

    RTCM_MT_QZSS_MSM1 = 1111,
    RTCM_MT_QZSS_MSM2 = 1112,
    RTCM_MT_QZSS_MSM3 = 1113,
    RTCM_MT_QZSS_MSM4 = 1114,
    RTCM_MT_QZSS_MSM5 = 1115,
    RTCM_MT_QZSS_MSM6 = 1116,
    RTCM_MT_QZSS_MSM7 = 1117,

    // RTCM_MT_RESERVED_MSM = 1118,
    // RTCM_MT_RESERVED_MSM = 1119,
    // RTCM_MT_RESERVED_MSM = 1120,

    RTCM_MT_BEIDOU_MSM1 = 1121,
    RTCM_MT_BEIDOU_MSM2 = 1122,
    RTCM_MT_BEIDOU_MSM3 = 1123,
    RTCM_MT_BEIDOU_MSM4 = 1124,
    RTCM_MT_BEIDOU_MSM5 = 1125,
    RTCM_MT_BEIDOU_MSM6 = 1126,
    RTCM_MT_BEIDOU_MSM7 = 1127,

    // RTCM_MT_RESERVED_MSM = 1128,
    // RTCM_MT_RESERVED_MSM = ...,
    // RTCM_MT_RESERVED_MSM = 1229,

    RTCM_MT_GLONASS_L1_L2_CODE_PHASE_BIASES = 1230,

    RTCM_MT_PROPRIETARY_ASHTECH = 4095,
    RTCM_MT_PROPRIETARY_TRIMBLE = 4094,
    RTCM_MT_PROPRIETARY_NOVATEL = 4093,
    RTCM_MT_PROPRIETARY_LEICA = 4092,
    RTCM_MT_PROPRIETARY_TOPCON = 4091,
    RTCM_MT_PROPRIETARY_GEO = 4090,
    RTCM_MT_PROPRIETARY_SEPTENTRIO = 4089,
    RTCM_MT_PROPRIETARY_IFEN = 4088,
    RTCM_MT_PROPRIETARY_FUGRO = 4087,
    RTCM_MT_PROPRIETARY_INPOSITION = 4086,
    RTCM_MT_PROPRIETARY_GSA = 4085,
    RTCM_MT_PROPRIETARY_GEODETICS = 4084,
    RTCM_MT_PROPRIETARY_DLR = 4083,
    RTCM_MT_PROPRIETARY_CRCSI = 4082,
    RTCM_MT_PROPRIETARY_SNUGL = 4081,
    RTCM_MT_PROPRIETARY_NAVCOM = 4080,
    RTCM_MT_PROPRIETARY_SCSC = 4079,
    RTCM_MT_PROPRIETARY_COMNAV = 4078,
    RTCM_MT_PROPRIETARY_HEMISPHERE = 4077,
    RTCM_MT_PROPRIETARY_IGS = 4076,
    RTCM_MT_PROPRIETARY_ALBERDING = 4075,
    RTCM_MT_PROPRIETARY_UNICORE = 4074,
    RTCM_MT_PROPRIETARY_MITSUBISHI = 4073,
    RTCM_MT_PROPRIETARY_UBLOX = 4072,
    RTCM_MT_PROPRIETARY_WNLBS = 4071,
    RTCM_MT_PROPRIETARY_MENGXIN = 4070,
    RTCM_MT_PROPRIETARY_VERIPOS = 4069,
    RTCM_MT_PROPRIETARY_QIANXUN = 4068,
    RTCM_MT_PROPRIETARY_CTTIC = 4067,

    // RTCM_MT_PROPRIETARY_RESERVED = 4066,
    // RTCM_MT_PROPRIETARY_RESERVED = ...,
    // RTCM_MT_PROPRIETARY_RESERVED = 4001,
} rtcm_message_type_t;

/**
 * RTCM Header
 */
typedef struct {
    uint8_t sync_char :8;
    uint8_t reserved :6;
    uint16_t message_length :10;
} rtcm_header_t;

typedef struct {
    rtcm_message_type_t message_id :12;
} rtcm_message_header_t;

/**
 * Stationary RTK Reference Station ARP - MT1005, MT1006
 */
typedef struct {
    rtcm_message_type_t message_id :12;       // DF002
    uint16_t reference_station_id :12;      // DF003
    uint8_t reserved_itrf_realization_year :6; // DF021
    bool gps_indicator :1;                  // DF022
    bool glonass_indicator :1;              // DF023
    bool galileo_indicator :1;              // DF024
    bool reference_station_indicator :1;    // DF141
    int64_t arp_ecef_x :38;                 // DF025
    bool single_receiver_oscillator_indicator :1; // DF142
    bool reserved :1;                       // DF001
    int64_t arp_ecef_y :38;                 // DF026
    uint8_t quarter_cycle_indicator :2;     // DF364
    int64_t arp_ecef_z :38;                 // DF027
    uint16_t antenna_height :16;            // DF028
} rtcm_message_station_arp;

/**
 * Antenna Descriptor - MT1007, MT1008
 */
typedef struct {
    rtcm_message_type_t message_id :12;       // DF002
    uint16_t reference_station_id :12;      // DF003
    uint8_t antenna_descriptor_length :8;   // DF029
    char antenna_descriptor[32];            // DF030
    uint8_t antenna_setup_id :8;            // DF031
    uint8_t antenna_serial_number_length :8; // DF032
    char antenna_serial_number[32];         // DF033
} rtcm_message_antenna_descriptor;

/**
 * Receiver and Antenna Descriptors - MT1033
 */
typedef struct {
    rtcm_message_type_t message_id :12;       // DF002
    uint16_t reference_station_id :12;      // DF003
    uint8_t antenna_descriptor_length :8;   // DF029
    char antenna_descriptor[32];            // DF030
    uint8_t antenna_setup_id :8;            // DF031
    uint8_t antenna_serial_number_length :8; // DF032
    char antenna_serial_number[32];         // DF033
    uint8_t receiver_type_descriptor_length :8; // DF227
    char receiver_type_descriptor[32];      // DF228
    uint8_t receiver_firmware_version_length :8; // DF229
    char receiver_firmware_version[32];     // DF230
    uint8_t receiver_serial_number_length :8; // DF231
    char receiver_serial_number[32];        // DF232
} rtcm_message_receiver_antenna_descriptor;

/**
 * MSM message header
 *
 * MT1071 - MT1077
 * MT1081 - MT1087
 * MT1091 - MT1097
 * MT1101 - MT1107
 * MT1111 - MT1117
 * MT1121 - MT1127
 * */
typedef struct {
    rtcm_message_type_t message_id :12;       // DF002
    uint16_t reference_station_id :12;      // DF003
    uint32_t gnss_epoch_time :30;           // Specific for each GNSS
    bool multiple_messages :1;              // DF393
    uint8_t issue_of_data_station :3;       // DF409
    uint8_t reserved :7;                    // DF001
    uint8_t clock_steering_indicator :2;    // DF411
    uint8_t external_clock_indicator :2;    // DF412
    bool gnss_divergence_free_smoothing_indicator :1; // DF417
    uint8_t gnss_smoothing_interval :3;     // DF418
    uint64_t gnss_satellite_mask :64;       // DF394
    uint32_t gnss_signal_mask :32;          // DF395
    uint64_t gnss_cell_mask :64;            // DF396
} rtcm_message_msm_header;

/**
 * Unicode Text String - MT1029
 */
typedef struct {
    rtcm_message_type_t message_id :12;       // DF002
    uint16_t reference_station_id :12;      // DF003
    uint16_t modified_julian_day :16;       // DF051
    uint32_t seconds_of_day :17;            // DF052
    uint8_t number_characters :7;           // DF138
    uint8_t number_code_units :8;           // DF139
    uint8_t utf8_code_units[255];           // DF140
} rtcm_message_unicode_text_string;

#endif //RTCM_PROTOCOL_H
