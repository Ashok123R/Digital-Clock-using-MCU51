/*PROJECT DONE BY: 

Ashok R  


AIM 

 Digital Clock using 8051 microcontroller. 

CODE */

#include<reg51.h> 

  

void lcd_initi(); 

void lcd_cmd(unsigned char cmd); 

void lcd_data(unsigned char data); 

void lcd_string(unsigned char *str); 

void delay(unsigned int msec); 

  

unsigned char hour=0,minute=0,second=0,set=0; 

  

void main() 

{ 

    lcd_init(); // Initialize LCD 

    lcd_string("Digital Clock"); // Display text on LCD 

    lcd_cmd(0xC0); // Move cursor to second row 

    lcd_string("Using 8051 MCU"); // Display text on LCD 

    delay(2000); // Delay of 2000 milliseconds 

    lcd_cmd(0x01); // Clear screen 

    while(1) // Infinite loop 

    { 

        display_time(); // Display current time on LCD 

        second++; // Increment second 

        if(second==60) // If second reaches 60 

        { 

            second=0; // Reset second to 0 

            minute++; // Increment minute 

            if(minute==60) // If minute reaches 60 

            { 

                minute=0; // Reset minute to 0 

                hour++; // Increment hour 

                if(hour==24) // If hour reaches 24 

                { 

                    hour=0; // Reset hour to 0 

                } 

            } 

        } 

        if(set==0) // If time is not being set 

        { 

            delay(1000); // Delay of 1000 milliseconds 

        } 

    } 

} 

  

void display_time() 

{ 

    lcd_cmd(0x80); // Move cursor to first row 

    if(hour<10) // If hour is less than 10 

    { 

        lcd_data('0'); // Display '0' 

    } 

    lcd_data(hour+48); // Display hour 

    lcd_data(':'); // Display ':' 

    if(minute<10) // If minute is less than 10 

    { 

        lcd_data('0'); // Display '0' 

    } 

    lcd_data(minute+48); // Display minute 

    lcd_data(':'); // Display ':' 

    if(second<10) // If second is less than 10 

    { 

        lcd_data('0'); // Display '0' 

    } 

    lcd_data(second+48); // Display second 

} 

  

void set_time() 

{ 

    if(P1_0==0) // If button connected to P1_0 is pressed 

    { 

        while(P1_0==0); // Wait until button is released 

        hour++; // Increment hour 

        if(hour==24) // If hour reaches 24 

        { 

            hour=0; // Reset hour to 0 

        } 

    } 

    if(P1_1==0) // If button connected to P1_1 is pressed 

    { 

        while(P1_1==0); // Wait until button is released 

        minute++; // Increment minute 

        if(minute==60) // If minute reaches 60 

        { 

            minute=0; // Reset minute to 0 

        } 

    } 

    if(P1_2==0) // If button connected to P1_2 is pressed 

    { 

        while(P1_2==0); // Wait until button is released 

        second++; // Increment second 

        if(second==60) // If second reaches 60 

        { 

            second=0; // Reset second to 0 

        } 

    } 

    if(P1_0==0 && P1_1==0 && P1_2==0) // If all buttons are pressed together 

    { 

        while(P1_0==0 && P1==0 && P1_2==0); // Wait until all buttons are released 

             set=0; // Time setting is over 

    } 

} 

  

void lcd_init() 

{ 

    lcd_cmd(0x38); // Initialize LCD 2 lines, 5x7 matrix 

    lcd_cmd(0x0E); // Display on cursor on 

    lcd_cmd(0x01); // Clear LCD screen 

    lcd_cmd(0x06); // Increment cursor 

    lcd_cmd(0x80); // Set cursor position to 1st line, 1st column 

} 

  

void lcd_cmd(unsigned char cmd) 

{ 

    P2=cmd; // Send command to data pins 

    P0=0x04; // RS=0, RW=0, EN=1 

    delay(10); // Delay of 10 milliseconds 

    P0=0x00; // RS=0, RW=0, EN=0 

} 

  

void lcd_data(unsigned char data) 

{ 

    P2=data; // Send data to data pins 

    P0=0x05; // RS=1, RW=0, EN=1 

    delay(10); // Delay of 10 milliseconds 

    P0=0x01; // RS=1, RW=0, EN=0 

} 

  

void lcd_string(unsigned char *str) 

{ 

    int i=0; 

    while(str[i]!='\0') // Loop until end of string 

    { 

        lcd_data(str[i]); // Display character on LCD 

        i++; // Move to next character 

    } 

} 

  

void delay(unsigned int msec) 

{ 

    int i,j; 

    for(i=0;i<msec;i++) 

    { 

        for(j=0;j<1275;j++); 

    } 

} 

 
