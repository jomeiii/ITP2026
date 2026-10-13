#include <stdio.h>

int main(){
    union {
        unsigned int raw;
        struct {
            unsigned char version: 4;
            unsigned char ihl: 4;
            unsigned char dscp: 6;
            unsigned char ecn: 2;
            unsigned short total_length;
        } parsed;
    } packet;

    packet.parsed.version = 0b1000;
    packet.parsed.ihl = 0b1011;
    packet.parsed.dscp = 0b111011;
    packet.parsed.ecn = 0b00;
    packet.parsed.total_length = 12345;

    printf("%u\n", packet.parsed.version);
    printf("%u\n", packet.parsed.ihl);
    printf("%u\n", packet.parsed.dscp);
    printf("%u\n", packet.parsed.ecn);
    printf("%u\n", packet.parsed.total_length);
    return 0;
}