#include <stdbool.h>
#include <stdint.h>

#include "protocol.h"

static protocol_settings_t peer_settings;

bool protocol_init(protocol_peer_t peer, uint8_t id)
{
    bool status = false;
    if (peer == MASTER)
    {
        peer_settings.peer = MASTER;
        peer_settings.id = 255;
    }
    else
    {
        peer_settings.peer = SLAVE;
        /* ID = 0 is BROADCAST*/
        if (id != 0)
        {
            peer_settings.id = id;
            status = true;
        }
    }
    return status;
}

bool protocol_message_parse(char *serial_data, protocol_data_raw_t *data)
{
    bool status = false;

    if ( ((uint8_t)serial_data[0]) == peer_settings.id)
    {
        data->id = (uint8_t)serial_data[0];
        data->action = (uint8_t)serial_data[1];
        data->length = (uint8_t)serial_data[2];

        for (uint8_t index = 0; index < data->length; index++)
        {
            data->data[index] = serial_data[index+3];
        }
        data->data[data->length+1] = '\0';
        status = true;
    }
    return status;
}

bool protocol_create_message(protocol_data_raw_t data, char *serial_data)
{
    bool status = false;
    if (data.id != peer_settings.id)
    {
        serial_data[0] = data.id;
        serial_data[1] = data.action;
        serial_data[2] = data.length;
        for(uint8_t index = 0; index < data.length; index++)
        {
            serial_data[3+index] = data.data[index];
        }
        
        status = true;
    }
    return status;
}

bool protocol_check_id(protocol_data_raw_t data)
{
    bool status = false;
    if (data.id == peer_settings.id)
    {
        status = true;
    }
    return status;
}

uint8_t protocol_get_settings_id(void)
{
    return peer_settings.id;
}

protocol_peer_t protocol_get_settings_peer(void)
{
    return peer_settings.peer;
}
