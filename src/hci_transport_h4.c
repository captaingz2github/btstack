/*
 *  hci_h4_transport.c
 *
 *  Created by Matthias Ringwald on 4/29/09.
 *
 */
#include <termios.h>  /* POSIX terminal control definitions */
#include <fcntl.h>    /* File control definitions */
#include <unistd.h>   /* UNIX standard function definitions */
#include <stdio.h>

#include "hci.h"
#include "hci_transport_h4.h"

typedef enum {
    H4_W4_PACKET_TYPE,
    H4_W4_EVENT_HEADER,
    H4_W4_EVENT_PAYLOAD,
    H4_W4_ACL_HEADER,
    H4_W4_ACL_PAYLOAD
} H4_STATE;

static void dummy_handler(uint8_t *packet, int size); 
static    hci_uart_config_t *hci_uart_config;

static  int fd;
static  void (*event_packet_handler)(uint8_t *packet, int size) = dummy_handler;
static  void (*acl_packet_handler)  (uint8_t *packet, int size) = dummy_handler;

// packet reader state machine
static  H4_STATE h4_state;
static int bytes_to_read;
static int read_pos;
// static uint8_t hci_event_buffer[255+2]; // maximal payload + 2 bytes header
static uint8_t hci_packet[400]; // bigger than largest packet



// prototypes
static int    h4_open(void *transport_config){
    hci_uart_config = (hci_uart_config_t*) transport_config;
    struct termios toptions;
    fd = open(hci_uart_config->device_name, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1)  {
        perror("init_serialport: Unable to open port ");
        perror(hci_uart_config->device_name);
        return -1;
    }
    
    if (tcgetattr(fd, &toptions) < 0) {
        perror("init_serialport: Couldn't get term attributes");
        return -1;
    }
    speed_t brate = hci_uart_config->baudrate; // let you override switch below if needed
    switch(hci_uart_config->baudrate) {
        case 57600:  brate=B57600;  break;
        case 115200: brate=B115200; break;
    }
    cfsetispeed(&toptions, brate);
    cfsetospeed(&toptions, brate);
    
    // 8N1
    toptions.c_cflag &= ~PARENB;
    toptions.c_cflag &= ~CSTOPB;
    toptions.c_cflag &= ~CSIZE;
    toptions.c_cflag |= CS8;

    if (hci_uart_config->flowcontrol) {
        // with flow control
        toptions.c_cflag |= CRTSCTS;
    } else {
        // no flow control
        toptions.c_cflag &= ~CRTSCTS;
    }
    
    toptions.c_cflag |= CREAD | CLOCAL;  // turn on READ & ignore ctrl lines
    toptions.c_iflag &= ~(IXON | IXOFF | IXANY); // turn off s/w flow ctrl
    
    toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // make raw
    toptions.c_oflag &= ~OPOST; // make raw
    
    // see: http://unixwiz.net/techtips/termios-vmin-vtime.html
    toptions.c_cc[VMIN]  = 1;
    toptions.c_cc[VTIME] = 0;
    
    if( tcsetattr(fd, TCSANOW, &toptions) < 0) {
        perror("init_serialport: Couldn't set term attributes");
        return -1;
    }
    
    // init state machine
    bytes_to_read = 1;
    h4_state = H4_W4_PACKET_TYPE;
    read_pos = 0;
    
    return 0;
}

static int    h4_close(){
    return 0;
}

static int    h4_send_cmd_packet(uint8_t *packet, int size){
    printf("CMD: ");
    hexdump(packet, size);
    
    char *data = (char*) packet;
    char packet_type = HCI_COMMAND_DATA_PACKET;
    write(fd, &packet_type, 1);
    while (size > 0) {
        int bytes_written = write(fd, data, size);
        if (bytes_written < 0) {
            return bytes_written;
        }
        data += bytes_written;
        size -= bytes_written;
    }
    return 0;
}

static int    h4_send_acl_packet(uint8_t *packet, int size){
    printf("ACL> ");
    hexdump(packet, size);
    
    char *data = (char*) packet;
    char packet_type = HCI_ACL_DATA_PACKET;
    write(fd, &packet_type, 1);
    while (size > 0) {
        int bytes_written = write(fd, data, size);
        if (bytes_written < 0) {
            return bytes_written;
        }
        data += bytes_written;
        size -= bytes_written;
    }
    return 0;
}

static void   h4_register_event_packet_handler(void (*handler)(uint8_t *packet, int size)){
    event_packet_handler = handler;
}

static void   h4_register_acl_packet_handler  (void (*handler)(uint8_t *packet, int size)){
    acl_packet_handler = handler;
}

static int    h4_get_fd() {
    return fd;
}

static int    h4_handle_data() {
    // read up to bytes_to_read data in
    int bytes_read = read(fd, &hci_packet[read_pos], bytes_to_read);
    if (bytes_read < 0) {
        return bytes_read;
    }
    // printf("Bytes read: %u\n", bytes_read);
    bytes_to_read -= bytes_read;
    read_pos      += bytes_read;
    if (bytes_to_read > 0) {
        return 0;
    }
    
    // act
    switch (h4_state) {
        case H4_W4_PACKET_TYPE:
            if (hci_packet[0] == HCI_EVENT_PACKET){
                read_pos = 0;
                bytes_to_read = HCI_EVENT_PKT_HDR;
                h4_state = H4_W4_EVENT_HEADER;
            } else if (hci_packet[0] == HCI_ACL_DATA_PACKET){
                read_pos = 0;
                bytes_to_read = HCI_ACL_DATA_PKT_HDR;
                h4_state = H4_W4_ACL_HEADER;
            } else {
            }
            break;
        case H4_W4_EVENT_HEADER:
            bytes_to_read = hci_packet[1];
            h4_state = H4_W4_EVENT_PAYLOAD;
            break;
        case H4_W4_EVENT_PAYLOAD:
            printf("EVT: ");
            hexdump(hci_packet, read_pos);
            event_packet_handler(hci_packet, read_pos);
            h4_state = H4_W4_PACKET_TYPE;
            read_pos = 0;
            bytes_to_read = 1;
            break;
        case H4_W4_ACL_HEADER:
            bytes_to_read = READ_BT_16( hci_packet, 2);
            h4_state = H4_W4_ACL_PAYLOAD;
            break;
        case H4_W4_ACL_PAYLOAD:
            printf("<ACL ");
            hexdump(hci_packet, read_pos);
            acl_packet_handler(hci_packet, read_pos);
            h4_state = H4_W4_PACKET_TYPE;
            read_pos = 0;
            bytes_to_read = 1;
            break;
    }
    return 0;
}

static const char * h4_get_transport_name(){
    return "H4";
}

static void dummy_handler(uint8_t *packet, int size){
}

// single instance
hci_transport_t hci_h4_transport = {
    h4_open, 
    h4_close,
    h4_send_cmd_packet,
    h4_send_acl_packet,
    h4_register_event_packet_handler,
    h4_register_acl_packet_handler,
    h4_get_fd,
    h4_handle_data,
    h4_get_transport_name
};
