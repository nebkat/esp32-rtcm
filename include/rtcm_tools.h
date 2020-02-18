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

#ifndef RTCM_TOOLS_H
#define RTCM_TOOLS_H

#include <stdbool.h>

#include "rtcm_protocol.h"

int rtcm_decode_mt1005(rtcm_message_station_arp *destination, const uint8_t *source);
int rtcm_decode_mt1006(rtcm_message_station_arp *destination, const uint8_t *source);
int rtcm_decode_mt1007(rtcm_message_antenna_descriptor *destination, const uint8_t *source);
int rtcm_decode_mt1008(rtcm_message_antenna_descriptor *destination, const uint8_t *source);
int rtcm_decode_mt1033(rtcm_message_receiver_antenna_descriptor *destination, const uint8_t *source);

int rtcm_encode_mt1005(uint8_t *destination, const rtcm_message_station_arp *source);
int rtcm_encode_mt1006(uint8_t *destination, const rtcm_message_station_arp *source);
int rtcm_encode_mt1007(uint8_t *destination, const rtcm_message_antenna_descriptor *source);
int rtcm_encode_mt1008(uint8_t *destination, const rtcm_message_antenna_descriptor *source);
int rtcm_encode_mt1033(uint8_t *destination, const rtcm_message_receiver_antenna_descriptor *source);

#endif //RTCM_TOOLS_H
