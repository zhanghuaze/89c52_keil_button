#include "Com_Util.h"
#include <INTRINS.H>


/**
 * @brief Delay function for a specified number of milliseconds.
 * 
 * @param xms Number of milliseconds to delay
 */
void Com_Util_Delay(uint16_t xms)	//@11.0592MHz
{
	uint8_t data i, j;

	while (xms--)
	{
		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}
