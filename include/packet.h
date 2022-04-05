#ifndef PACKET_H
#define PACKET_H
void add_u8(uint8_t* data, uint8_t byte, unsigned int pos) {
    *(data + pos) = byte;
}
uint8_t read_u8(uint8_t* data, unsigned int pos) {
    return *(data + pos);
}
void add_u16(uint8_t* data, uint16_t u16, unsigned int pos) {
    *(data + pos) = u16 & 0xFF;
    *(data + pos + 1) = (u16 >> 8) & 0xFF;
}
uint16_t read_u16(uint8_t* data, unsigned int pos) {
    return *(data + pos) | *(data + pos + 1) << 0xFF;
}
#endif