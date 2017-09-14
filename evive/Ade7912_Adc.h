/*
 * evive_oscilloscope.h
 *
 *  Created on: May 26, 2016
 *      Author: dhrups
 *  NOTE: Screen Implementation for mini oscilloscope feature is done in
 *  SCREEN_IMPLEMENTATION_H
 */

#ifndef ADC_ADE7912_H_
#define ADC_ADE7912_H_

#include "evive.h"

#ifndef ADE7911X_REG_IWV
#define ADE791X_REG_IWV            0x00    /* Instantaneous value of Current I. */
#define ADE791X_REG_V1WV           0x01    /* Instantaneous value of Voltage V1 */
#define ADE791X_REG_V2WV           0x02    /* Instantaneous value of Voltage V2 */
//For V1WV 5,320,000 reading = 34.5V  (Multiplier = 0.006485) mV
#define ADE791X_MUL_V1WV           0.006485
//For V2WV 5,320,000Num reading = 6.3315V (Multiplier = 0.0011901) mV
#define ADE791X_MUL_VIMWV          0.0011901
//For IWV 5,320,000 reading = 3.15A (Multiplier = 0.0005921) mA
#define ADE791X_MUL_IWV            0.0005921
#define ADE791X_OFFSET_V1WV          363378      //387161;   //Adjust
#define ADE791X_OFFSET_VIMWV         369226                  //Adjust  
#define ADE791X_OFFSET_IWV           355000			//369226;   //Adjust
#endif

void ade791x_init(void);
long ade791x_read_v1(void);
long ade791x_read_vim(void);
long ade791x_read_im(void);

#endif /* ADC_ADE7912_H_ */
