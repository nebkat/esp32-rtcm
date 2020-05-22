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

#include <stddef.h>
#include <string.h>

#include "rtcm_protocol.h"
#include "rtcm_tools.h"

#define B(field) message->field = read_bit(buffer, i); i++;
#define U(bits, field) message->field = read_unsigned(buffer, i, bits); i += bits;
#define I(bits, field) message->field = read_signed(buffer, i, bits); i += bits;
#define I_SM(bits, field) message->field = (read_bit(buffer, i) ? 1 : -1) * read_unsigned(buffer, i, bits - 1); i += bits;
#define S(lengthBits, field) if (true) { \
        message->field##_length = read_unsigned(buffer, i, lengthBits); \
        read_string(&message->field, buffer, i + lengthBits, message->field##_length); \
        i += lengthBits + message->field##_length * 8; \
    }

#define S_UTF8(lengthBits, charBits, field) if (true) { \
        uint8_t length = read_unsigned(buffer, i, lengthBits); \
        read_string(buffer, i + lengthBits + charBits); \
        i += lengthBits + charBits + length * 8; \
    }

uint64_t read_unsigned(const uint8_t *buffer, size_t offset, size_t bits) {
    return 0;
}
void read_string(char **target, const uint8_t *buffer, size_t offset, size_t bytes) {

}

size_t rtcm_decode_1007(rtcm_message_receiver_antenna_descriptor *message, const uint8_t *buffer, size_t i) {
    U(12, reference_station_id)
    S(8, antenna_descriptor)

    return i;
}

/**
 * Copy block of memory to arbitrary bit offset
 *
 * Used to realign portions of RTCM messages that are no longer bit aligned.
 *
 * @param destination Pointer to the destination array where the content is to be copied
 * @param source Pointer to the source of data to be copied
 * @param bit_shift Amount of bits to left shift by
 * @param bit_length Amount of bits to copy
 * @return destination
 */
uint8_t *rtcm_memcpy_bitwise(uint8_t *destination, const uint8_t *source, uint8_t bit_shift, size_t bit_length) {
    uint8_t bit_remainder = bit_length % 8;
    size_t byte_length = bit_length / 8 + (bit_remainder > 0 ? 1 : 0);
    if (bit_shift == 0) {
        memcpy(destination, source, byte_length);
    } else {
        for (size_t i = 0; i < byte_length; i++) {
            destination[i] = (source[i] << bit_shift) | (source[i + 1] >> (8 - bit_shift));
        }
    }
    if (bit_remainder > 0) destination[byte_length - 1] &= 0xff << (8 - bit_remainder);
    return destination;
}

static inline bool rtcm_verify_message_type(const rtcm_message_type_t *source, rtcm_message_type_t message_type) {
    // Point to source to read message type from header
    return ((rtcm_message_header_t *) source)->message_id == message_type;
}

int rtcm_decode_mt1005(rtcm_message_station_arp *destination, const uint8_t *source) {
    if (!rtcm_verify_message_type((rtcm_message_type_t *) source, RTCM_MT_STATION_ARP)) return -1;
    return rtcm_decode_mt1006(destination, source);
}

int rtcm_decode_mt1006(rtcm_message_station_arp *destination, const uint8_t *source) {
    if (!rtcm_verify_message_type((rtcm_message_type_t *) source, RTCM_MT_STATION_ARP) &&
        !rtcm_verify_message_type((rtcm_message_type_t *) source, RTCM_MT_STATION_ARP_HEIGHT)) return -1;

    memcpy(destination, source, sizeof(rtcm_message_station_arp));

    return sizeof(rtcm_message_station_arp);
}

int rtcm_decode_mt1007(rtcm_message_antenna_descriptor *destination, const uint8_t *source) {
    if (!rtcm_verify_message_type((rtcm_message_type_t *) source, RTCM_MT_ANTENNA_DESCRIPTOR)) return -1;
    return rtcm_decode_mt1033((rtcm_message_receiver_antenna_descriptor *) destination, source);
}

int rtcm_decode_mt1008(rtcm_message_antenna_descriptor *destination, const uint8_t *source) {
    if (!rtcm_verify_message_type((rtcm_message_type_t *) source, RTCM_MT_ANTENNA_DESCRIPTOR_SERIAL)) return -1;
    return rtcm_decode_mt1033((rtcm_message_receiver_antenna_descriptor *) destination, source);
}

int rtcm_decode_mt1033(rtcm_message_receiver_antenna_descriptor *destination, const uint8_t *source) {
    // Verify message ID
    if (!rtcm_verify_message_type((rtcm_message_type_t *) source, RTCM_MT_ANTENNA_DESCRIPTOR) &&
            !rtcm_verify_message_type((rtcm_message_type_t *) source, RTCM_MT_ANTENNA_DESCRIPTOR_SERIAL) &&
            !rtcm_verify_message_type((rtcm_message_type_t *) source, RTCM_MT_RECEIVER_ANTENNA_DESCRIPTOR)) return -1;

    // Header
    int i = 0;
    memcpy(destination, source, 3);
    i += 3;

    // Antenna descriptor
    destination->antenna_descriptor_length = source[i++];
    memcpy(&destination->antenna_descriptor, &source[i], destination->antenna_descriptor_length);
    i += destination->antenna_descriptor_length;

    if (rtcm_verify_message_type((rtcm_message_type_t *) source, RTCM_MT_ANTENNA_DESCRIPTOR)) return i;

    // Antenna setup ID
    destination->antenna_setup_id = source[i++];

    if (rtcm_verify_message_type((rtcm_message_type_t *) source, RTCM_MT_ANTENNA_DESCRIPTOR_SERIAL)) return i;

    // Antenna serial number
    destination->antenna_serial_number_length = source[i++];
    memcpy(&destination->antenna_serial_number, &source[i], destination->antenna_serial_number_length);
    i += destination->antenna_serial_number_length;

    // Receiver type descriptor
    destination->receiver_type_descriptor_length = source[i++];
    memcpy(&destination->receiver_type_descriptor, &source[i], destination->receiver_type_descriptor_length);
    i += destination->receiver_type_descriptor_length;

    // Receiver firmware version
    destination->receiver_firmware_version_length = source[i++];
    memcpy(&destination->receiver_firmware_version, &source[i], destination->receiver_firmware_version_length);
    i += destination->receiver_firmware_version_length;

    // Receiver serial number
    destination->receiver_serial_number_length = source[i++];
    memcpy(&destination->receiver_serial_number, &source[i], destination->receiver_serial_number_length);
    i += destination->receiver_serial_number_length;

    return i;
}

int rtcm_encode_mt1005(uint8_t *destination, const rtcm_message_station_arp *source) {
    if (!rtcm_verify_message_type((rtcm_message_type_t *) source, RTCM_MT_STATION_ARP)) return -1;
    return rtcm_encode_mt1006(destination, source);
}

int rtcm_encode_mt1006(uint8_t *destination, const rtcm_message_station_arp *source) {
    if (!rtcm_verify_message_type((rtcm_message_type_t *) source, RTCM_MT_STATION_ARP) &&
            !rtcm_verify_message_type((rtcm_message_type_t *) source, RTCM_MT_STATION_ARP_HEIGHT)) return -1;

    memcpy(destination, source, sizeof(rtcm_message_station_arp));

    return sizeof(rtcm_message_station_arp);
}

int rtcm_encode_mt1007(uint8_t *destination, const rtcm_message_antenna_descriptor *source) {
    if (!rtcm_verify_message_type((rtcm_message_type_t *) source, RTCM_MT_ANTENNA_DESCRIPTOR)) return -1;
    return rtcm_encode_mt1033(destination, (rtcm_message_receiver_antenna_descriptor *) source);
}

int rtcm_encode_mt1008(uint8_t *destination, const rtcm_message_antenna_descriptor *source) {
    if (!rtcm_verify_message_type((rtcm_message_type_t *) source, RTCM_MT_ANTENNA_DESCRIPTOR_SERIAL)) return -1;
    return rtcm_encode_mt1033(destination, (rtcm_message_receiver_antenna_descriptor *) source);
}

int rtcm_encode_mt1033(uint8_t *destination, const rtcm_message_receiver_antenna_descriptor *source) {
    // Verify message ID
    if (!rtcm_verify_message_type((rtcm_message_type_t *) destination, RTCM_MT_ANTENNA_DESCRIPTOR) &&
            !rtcm_verify_message_type((rtcm_message_type_t *) destination, RTCM_MT_ANTENNA_DESCRIPTOR_SERIAL) &&
            !rtcm_verify_message_type((rtcm_message_type_t *) destination, RTCM_MT_RECEIVER_ANTENNA_DESCRIPTOR)) return -1;

    // Header
    int i = 0;
    memcpy((void *) destination, source, 3);
    i += 3;

    // Antenna descriptor
    destination[i++] = source->antenna_descriptor_length;
    memcpy(&destination[i], &source->antenna_descriptor, source->antenna_descriptor_length);
    i += source->antenna_descriptor_length;

    if (rtcm_verify_message_type((rtcm_message_type_t *) source, RTCM_MT_ANTENNA_DESCRIPTOR)) return i;

    // Antenna setup ID
    destination[i++] = source->antenna_setup_id;

    if (rtcm_verify_message_type((rtcm_message_type_t *) source, RTCM_MT_ANTENNA_DESCRIPTOR_SERIAL)) return i;

    // Antenna serial number
    destination[i++] = source->antenna_serial_number_length;
    memcpy(&destination[i], &source->antenna_serial_number, source->antenna_serial_number_length);
    i += source->antenna_serial_number_length;

    // Receiver type descriptor
    destination[i++] = source->receiver_type_descriptor_length;
    memcpy(&destination[i], &source->receiver_type_descriptor, source->receiver_type_descriptor_length);
    i += source->receiver_type_descriptor_length;

    // Receiver firmware version
    destination[i++] = source->receiver_firmware_version_length;
    memcpy(&destination[i], &source->receiver_firmware_version, source->receiver_firmware_version_length);
    i += source->receiver_firmware_version_length;

    // Receiver serial number
    destination[i++] = source->receiver_serial_number_length;
    memcpy(&destination[i], &source->receiver_serial_number, source->receiver_serial_number_length);
    i += source->receiver_serial_number_length;

    return i;
}