/*
 * 74ls595.h
 *
 *  Created on: 2017. 12. 13.
 *      Author: JS
 */

#ifndef shift_register_H_
#define shift_register_H_

/***************************************
 Configure Connections
 ****************************************/

/***************************************
 Configure Connections ***ENDS***
 ****************************************/

//Initialize HC595 System
void HC595Init();

//Sends a clock pulse on SH_CP line
void HC595Pulse();

//Sends a clock pulse on ST_CP line
void HC595Latch();

/*
 Main High level function to write a single byte to
 Output shift register 74HC595.
 Arguments:
 single byte to write to the 74HC595 IC
 Returns:
 NONE
 Description:
 The byte is serially transfered to 74HC595
 and then latched. The byte is then available on
 output line Q0 to Q7 of the HC595 IC.
 */
void HC595Write(uint8_t data);




#endif /* 74LS595_H_ */
