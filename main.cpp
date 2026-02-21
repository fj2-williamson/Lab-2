#include "mbed.h"
#include "arm_book_lib.h"
#define BLINKING_RATE 500ms
int main()
{
    DigitalIn enterButton(BUTTON1);
    DigitalIn Abutton(D2);
    DigitalIn Bbutton(D3);
    DigitalIn Cbutton(D4);
    DigitalIn Dbutton(D5);
    DigitalIn Ebutton(D6);
    DigitalIn Fbutton(D7);

    DigitalOut correctcodeled(LED1);
    DigitalOut incorrectCodeLed(LED3);
    DigitalOut systemBlockedLed(LED2);

    enterButton.mode(PullDown);
    Abutton.mode(PullDown);
    Bbutton.mode(PullDown);
    Cbutton.mode(PullDown);
    Dbutton.mode(PullDown);
    Ebutton.mode(PullDown);
    Fbutton.mode(PullDown);

    correctcodeled = OFF;
    incorrectCodeLed = OFF;
    systemBlockedLed = OFF;

    bool correctcode = OFF;
    int numberOfIncorrectCodes = 0;
    int x = 1;

    while (true) {
        //while there have been less than 3 incorrect guesses
        if (numberOfIncorrectCodes < 3 && !correctcode){
            //when the code is entered
            if (enterButton){
//this is the combination lock
        if ( Abutton && Bbutton && Dbutton && Fbutton && !Cbutton && !Ebutton) {
            //turns on LED1
            correctcode = ON;}
            //if the code isn't entered...
            else{
                //flash LED3
                incorrectCodeLed = ON;
                ThisThread::sleep_for(BLINKING_RATE);
                incorrectCodeLed = OFF;
                //Add 1 to the incorrect code counter
                numberOfIncorrectCodes++;
            }

            }
        }
        //for 3 incorrect guesses
        if (numberOfIncorrectCodes == 3){
            //turn all lights off
            correctcode = OFF;
            incorrectCodeLed = OFF;
            //for 30s, flash LED3
            for (int i=0; i < 60; i++){
                incorrectCodeLed = !incorrectCodeLed;
                ThisThread::sleep_for(BLINKING_RATE);
            }
            //turn off LED3 after 30s
            incorrectCodeLed = OFF;
            numberOfIncorrectCodes++;
        }
        //for the final attempt
        if (numberOfIncorrectCodes == 4 && !correctcode){
            //when code is entered
                      if (enterButton){
//this is the combination lock
        if ( Abutton && Bbutton && Dbutton && Fbutton && !Cbutton && !Ebutton) {
            //turns on LED1
            correctcode = ON;}
            //if the code isn't entered...
            else{
                numberOfIncorrectCodes++;
            }
        }
        }
        //for 4 incorrect guesses
        if (numberOfIncorrectCodes == 5){
            //turn on LED2
            systemBlockedLed = ON;
            //flash LED3 for 60s
            for(int i=0; i<120; i++){
                incorrectCodeLed = !incorrectCodeLed;
                ThisThread::sleep_for(BLINKING_RATE);
                //if the override code is entered
                if(Abutton && Bbutton && Cbutton &&Dbutton && enterButton){
                    //turn all LEDs OFF
                    correctcode = OFF;
                    incorrectCodeLed = OFF;
                    systemBlockedLed = OFF;
                    //break the for loop
                    i=60;
                    //reset the number of attempts
                    numberOfIncorrectCodes++;
                    break;
                }
            }
        }
        //this is the log counter
        if (numberOfIncorrectCodes > 5){
            //blinks for however many times you have guessed wrong 
            for(int i=0;i<x; i++){
            //turn LED1 on, blink for as many times as this has occured
            ThisThread::sleep_for(BLINKING_RATE);
                correctcodeled = ON;
                ThisThread::sleep_for(BLINKING_RATE);
                correctcodeled = OFF;
                ThisThread::sleep_for(BLINKING_RATE);
            }
            //add 1 to the coutner and reset the number of incorrect codes
            x++;
            numberOfIncorrectCodes = 0;
        }
        correctcodeled = correctcode;
    }
}



      

    