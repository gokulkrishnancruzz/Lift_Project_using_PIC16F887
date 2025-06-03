#include <xc.h>

void delay(unsigned int a)
{
    while(a--);
}
void enable()
{
    RE1=1;
    delay(50);
    RE1=0;
    delay(50);
}
void data(char a, char b)
{
    RE0=a;
    PORTD=b;
    enable();
}
void string(char *ptr)
{
    while(*ptr)
    {
        data(1,*ptr++);
    }
}
void main()
{
    PORTB=PORTD=PORTE=PORTC=0x00;
    PORTA=TRISA=0x00;
    TRISB=0xFF;
    TRISC=TRISD=TRISE=0x00;
    ANSEL=ANSELH=0x00;
    int floor,sensor;
    data(0,0x38);

    data(0,0x0E);
    data(0,0x80);
    string("FLR");
    while(1)
    {
        data(0,0x84);
        data(1,floor+48);
        string("FLR AT");
        data(1,sensor+48);
        //floors
        if(RB4==1)
            floor=3;
        if(RB5==1)
            floor=2;
        if(RB6==1)
            floor=1;
        if(RB7==1)
            floor=0;

        //sensors
        if(RB0==1)
            sensor=3;
        if(RB1==1)
            sensor=2;
        if(RB2==1)
            sensor=1;
        if(RB3==1)
            sensor=0;


        if(floor==sensor)
        {
            RC0=RC1=0;
            data(0,0xc0);
            string("Motor Stop");
        }
        if(floor<sensor)
        {
            RC0=RC1=1;
            data(0,0xc0);
            string("Motor Rev");
        }
         if(floor>sensor)
        {
            RC1=RC0=1
                    ;
            data(0,0xc0);
            string("Motor For");
        }
    }
}
