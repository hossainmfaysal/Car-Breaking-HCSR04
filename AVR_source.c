#include <mega32.h>
#include <delay.h>

int i=0;
int tim=0;
interrupt [EXT_INT0] void ext_int0_isr (void)

{
    if(i==0)
        {  
            TCCR1B=(0<<CS12)|(1<<CS11)|(0<<CS10); 
            i=1;
        }
    if(i==1)
        {
            tim=TCNT1;
            TCNT1=0;
            i=0;
        } 
}
void main(void)
{
int dist=0;
int diga, digb=0;
char cathode[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
DDRD=0b11011011;
DDRA=0xFF;
DDRB=0xFF;
delay_ms(50);

GICR=(1<<INT0);
MCUCR=(1<<ISC00);
#asm("sei")
     while(1)
     {
        PORTD.0=1;
        delay_us(10);
        PORTD.0=~(PORTD.0);
        dist=tim/58;
        diga=dist%10;
        digb=dist/10;
        PORTA=cathode[digb];
        PORTB=cathode[diga];
        if(dist<=15)
        {
            PORTD.6=1;
            PORTD.7=0;
        } 
        else if(dist>15 && dist<=30)
        {
            PORTD.6=0;
            PORTD.7=1;
        }
        else
        {
            PORTD.6=0;
            PORTD.7=0;
        }
        if(PIND.5==0)
        {
        break;
        }   
     }  
PORTD.6=0;
PORTD.7=0;
}