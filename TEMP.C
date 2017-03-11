/********************************************************************
 * Function:        void BlinkUSBStatus(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        BlinkUSBStatus turns on and off LEDs
 *                  corresponding to the USB device state.
 *
 * Note:            mLED macros can be found in HardwareProfile.h
 *                  USBDeviceState is declared and updated in
 *                  usb_device.c.
 *******************************************************************/
void BlinkUSBStatus(void){
   #define mLED_Both_Off()         {mLED_1_Off();mLED_2_Off();}
   #define mLED_Both_On()          {mLED_1_On();mLED_2_On();}
   #define mLED_Only_1_On()        {mLED_1_On();mLED_2_Off();}
   #define mLED_Only_2_On()        {mLED_1_Off();mLED_2_On();}
   if(!TimeOut)return;
   TimeOut=0;
   if(USBSuspendControl == 1){      //If device is in USB suspend, then need to
                                    //make LEDs take minimal average power.
    	if(led_count == 0){
    		led_count = 200;
         if(!LedBusy){
            LATGSET=1<<bLedBusy;             //LATG15=OFF
         }
         else {
            LATGCLR=1<<bLedBusy;             //LATG15=ON
         }
      }
    	led_count--;
   }
   else {
      if(led_count == 0){
    		led_count = 15;         //150mS
    	}
    	led_count--;
    	if(USBDeviceState == DETACHED_STATE){
         mLED_Both_Off();
      }
      else if(USBDeviceState == ATTACHED_STATE){
         mLED_Both_On();
      }
      else if(USBDeviceState == POWERED_STATE){
         mLED_Only_1_On();
      }
      else if(USBDeviceState == DEFAULT_STATE){
         mLED_Only_2_On();
         LATGSET=1<<bLedBusy;             //LATG15=OFF
      }
      else if(USBDeviceState == ADDRESS_STATE){
         if(led_count == 0){
            mLED_1_Toggle();
            mLED_2_Off();
         }//end if
      }
      else if(USBDeviceState == CONFIGURED_STATE){
         mLED_Both_Off();
         if(led_count==0){
            if(!LedBusy){
               LATGSET=1<<bLedBusy;             //LATG15=OFF
            }
            else {
               LATGCLR=1<<bLedBusy;             //LATG15=ON
            }
         }//end if
      }//end if(...)
   }//end if(UCONbits.SUSPND...)
}//end BlinkUSBStatus

// /*
   #define mInitAllLEDs()      LATDCLR = 0x00F0; TRISD &= 0xFF0F;

   #define mLED_1              LATDbits.LATD7   //RY3
   #define mLED_2              LATDbits.LATD6   //RY4
   #define mLED_3              LATDbits.LATD5   //RY5
   #define mLED_4              LATDbits.LATD4   //RY6

   #define mGetLED_1()         mLED_1
   #define mGetLED_2()         mLED_2
   #define mGetLED_3()         mLED_3
   #define mGetLED_4()         mLED_4

   #define mLED_1_On()         mLED_1 = 1;
   #define mLED_2_On()         mLED_2 = 1;
   #define mLED_3_On()         mLED_3 = 1;
   #define mLED_4_On()         mLED_4 = 1;

   #define mLED_1_Off()        mLED_1 = 0;
   #define mLED_2_Off()        mLED_2 = 0;
   #define mLED_3_Off()        mLED_3 = 0;
   #define mLED_4_Off()        mLED_4 = 0;

   #define mLED_1_Toggle()     mLED_1 = !mLED_1;
   #define mLED_2_Toggle()     mLED_2 = !mLED_2;
   #define mLED_3_Toggle()     mLED_3 = !mLED_3;
   #define mLED_4_Toggle()     mLED_4 = !mLED_4;
   #define mInitSwitch1()      TRISCbits.TRISC1=1;
   #define mInitSwitch2()      TRISDbits.TRISD8=1;
   #define mInitAllSwitches()  mInitSwitch1();mInitSwitch2();
   #define sw1                 PORTCbits.RC1    //F1Sw
   #define sw2                 PORTDbits.RD8    //TestSw
// */

