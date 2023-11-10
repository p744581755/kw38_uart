#include "stdint.h"
#include "Flash_Adapter.h"


void Change_bytes_to_hex(uint8_t *input, uint16_t inputlen, uint8_t* output)
{
	uint16_t i;
	uint8_t tmp1,tmp2;
	for (i = 0; i < inputlen; i++)
	{
		tmp1 = input[i] >> 4;
		tmp2 = input[i] & 0x0F;
		if (tmp1 < 10)
		{
			output[(inputlen - i - 1) * 2] = tmp1 + '0';
		}
		else
		{
			output[(inputlen - i - 1) * 2] = tmp1 + 'A' - 10;
		}
		if (tmp2 < 10)
		{
			output[(inputlen - i - 1) * 2 + 1] = tmp2 + '0';
		}
		else
		{
			output[(inputlen - i - 1) * 2 + 1] = tmp2 + 'A' - 10;
		}
	}
}


void init_BLE_name(uint8_t *name)
{
	name[0] = 'S';
	name[1] = 'N';
	name[2] = 'B';
	name[3] = 'R';
    Change_bytes_to_hex(gHardwareParameters.bluetooth_address, 6, name + 4);
    name[16] = 0;
}
