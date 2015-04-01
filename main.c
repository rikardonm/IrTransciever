#include <msp430.h>
#include <ti/mcu/msp430/Grace.h>

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>



#define CPU_REAL_CLOCK				16000000


#define IR_CLOCK					2000000
#define	IR_SEND_ONE_PERIOD			0.0005625
static const uint16_t IRSendOnePeriodCount = (CPU_REAL_CLOCK*IR_SEND_ONE_PERIOD);
uint16_t IRSendAddress=0, IRSendData=0, IRSendRepeat=0,\
		IRLastAddress=0, IRLastData=0, IRSendState=0,\
		IRSendStateCounter=0, IRSendScan=0;
static const uint16_t IRSendStartCount = IRSendOnePeriodCount*24,\
		IRSendStartSpace = IRSendOnePeriodCount*16;
uint16_t IRSendPulseTrain[36], IRSendSpaceTrain[36], IRSendPulseTrainLength;
#define IR_END_COUNTER				TACCR0
#define IR_BURST_COUNTER			TACCR1
#define IR_PROTOCOL_OLD_VERSION		0x00
#define IR_PROTOCOL_NEW_VERSION		0x01
#define IR_SEND_EN					0x01




void IRSendTimerInit(void)
{
	/*
	 * main configuration done in grace
	 *
	 * generate pwm to set/reset 555 timer
	 * Ton should be 562.5 us
	 * Toff should be 562.5 us for 0, 3x562.5 us for 1
	 * timer timeout interrupt should scan address and data variables,
	 * and configure next timer cycle.
	 */
}



uint16_t IRCompileToSend(uint16_t address, uint16_t data, uint16_t config)
{
	uint16_t temp, temp2;
	if(address == IRLastAddress)
	{
		if(data == IRLastData)
		{
			IRSendRepeat = 1;
		}
	}
	if(IRSendRepeat == 1)
		goto IRAddressCompileRepeatJump;
	if(config&IR_PROTOCOL_NEW_VERSION == 0)
	{
		//old version, invert second byte
		temp = ~address;
		temp <<= 8;
		address |= temp;
		temp = ~data;
		temp <<= 8;
		data |= temp;
	}
	//else do nothing
	IRSendAddress = address;
	IRSendData = data;
	//compile send codes
	//9ms start
	//4.5 ms space
	//add bits
	//data bits
	//last pulse
	IRSendPulseTrain[0] = IRSendOnePeriodCount * 16;
	IRSendSpaceTrain[0] = IRSendOnePeriodCount * 8;
	temp = 1;
	while(temp < 17)
	{
		temp2 = address & 0x1;
		if(temp2 == 0)
			temp2 = IRSendOnePeriodCount*2;
		else
			temp2 = IRSendOnePeriodCount*4;
		IRSendPulseTrain[temp] = IRSendOnePeriodCount;
		IRSendSpaceTrain[temp] = temp2 + IRSendOnePeriodCount;
		address >>= 1;
		temp ++;
	}
	temp = 16
	while(temp < 32)
	{
		temp2 = data & 0x1;
		if(temp2 == 0)
			temp2 = IRSendOnePeriodCount*2;
		else
			temp2 = IRSendOnePeriodCount*4;
		IRSendPulseTrain[temp] = IRSendOnePeriodCount;
		IRSendSpaceTrain[temp] = temp2 + IRSendOnePeriodCount;
		data >>= 1;
		temp ++;
	}
	return(1);

IRAddressCompileRepeatJump:
	//compile repeat code
	//change length terminator
	return(0);
}



void IRInterruptFunction(void)
{
	uint16_t test;
	if(IRSendState == 0)
	{
		//configure for 9ms start
		IR_END_COUNTER = IRSendStartCount;
		IR_BURST_COUNTER = IRSendStartSpace;
		IRSendState ++;
		IRSendScan = 0;
	}
	if(IRSendScan == 16)
		IRSendState ++;
	if(IRSendState == 1)
	{
		IR_BURST_COUNTER = IRSendOnePeriodCount;
		test = IRSendAddress & 0x01;
		if(test == 0)
			IR_END_COUNTER = IRSendOnePeriodCount*2;
		else
			IR_END_COUNTER = IRSendOnePeriodCount*4;
		IRSendAddress >>= 1;
		IRSendScan ++;
	}
	if(IRSendState == 2)
	{
		IR_BURST_COUNTER = IRSendOnePeriodCount;
	}
	IRSendOnePeriodCount
}



/*
 *  ======== main ========
 */
int main(void)
{
    Grace_init();                   // Activate Grace-generated configuration
    
    // >>>>> Fill-in user code here <<<<<
    
    return (0);
}
