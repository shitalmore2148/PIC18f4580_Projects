#include<p18f4580.h>
#define r1 PORTBbits.RB3
#define r2 PORTBbits.RB4
#define r3 PORTBbits.RB5
#define r4 PORTBbits.RB6
#define c1 PORTBbits.RB0
#define c2 PORTBbits.RB1
#define c3 PORTBbits.RB2
#define rs PORTDbits.RD2
#define en PORTDbits.RD3
#define delay for(i=0;i<1500;i++);
#define delay1 for(j=0;j<500;j++);

int i,j,k;
void eeprom_msg(void);
void display_eeprom(void);
void write(unsigned char address,unsigned char data);
unsigned char read(unsigned char address);
void uart_init(void);
void tx_char(unsigned char a);
unsigned char rx_char(void);
void key_pressed(void);
void lcd_init(void);
void tx_str(unsigned char *s);
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void display(unsigned char *); 
void DutyCycle(int);
void delay_30s(void);

unsigned char msg1[33]="DC Motor speed control using PWM";
unsigned char msg2[18]="select DutyCycle:";
unsigned char msg3[17]="1)10%2)50%3)100%";
unsigned char msg4[17]=" speed:1000  rpm";
unsigned char msg5[17]=" speed:5000  rpm";
unsigned char msg6[17]=" speed:10000 rpm";
unsigned char add1=0;
unsigned char add2=17;
unsigned char add3=34;

unsigned char key,address=0,read_char;
unsigned char write_char1='1';
unsigned char write_char2='2';
unsigned char write_char3='3';
unsigned char read_char1,read_char2,read_char3;
void main()
{
TRISDbits.TRISD0=0;
TRISDbits.TRISD1=0;
TRISCbits.TRISC2=0;
PORTB=0x00;
ADCON1=0x0f;
TRISB=0;
TRISD=0;
uart_init();
lcd_init();
for(k=0;k<=20;k++)
{
lcd_cmd(0x80);
display(msg1);
lcd_cmd(0x18);
}
lcd_cmd(0x01);
lcd_cmd(0x80);
display(msg2);
lcd_cmd(0xc0);
display(msg3);
while(1)
{
//eeprom_msg();

key_pressed();
if(key=='1')
{
lcd_cmd(0x01);
display(msg4);
CCP1CON=0b00001100;
T2CON=0b00000010;
PR2=61;
CCPR1L=6;
PORTDbits.RD0=1;
PORTDbits.RD1=0;
PIR1bits.TMR2IF=0;
TMR2=0;
T2CONbits.TMR2ON=1;
while(PIR1bits.TMR2IF==0);
//delay_30s();
//eeprom_msg();
display_eeprom();
key_pressed();

}
if(key=='2')
{
lcd_cmd(0x01);
display(msg5);
CCP1CON=0b00001100;
T2CON=0b00000010;
PR2=61;
CCPR1L=31;
PORTDbits.RD0=1;
PORTDbits.RD1=0;
PIR1bits.TMR2IF=0;
TMR2=0;
T2CONbits.TMR2ON=1;
while(PIR1bits.TMR2IF==0);
//delay_30s();
//eeprom_msg();
display_eeprom();
key_pressed();
}
if(key=='3')
{
lcd_cmd(0x01);
display(msg6);
CCP1CON=0b00001100;
T2CON=0b00000010;
PR2=61;
CCPR1L=61;
PORTDbits.RD0=1;
PORTDbits.RD1=0;
PIR1bits.TMR2IF=0;
TMR2=0;
T2CONbits.TMR2ON=1;
while(PIR1bits.TMR2IF==0);
//delay_30s();
//eeprom_msg();
display_eeprom();
key_pressed();
}
}
}

void lcd_init()
{
lcd_cmd(0x02);
delay1
lcd_cmd(0x28);
delay1
lcd_cmd(0x0e);
delay1
lcd_cmd(0x06);
delay1
lcd_cmd(0x80);
delay1
}
void lcd_cmd(unsigned char a)
{
rs=0;
PORTD&=0x0f;
PORTD|=a&0xf0;
en=1;
delay
en=0;
delay
PORTD&=0x0f;
PORTD|=(a<<4)&0xf0;
en=1;
delay
en=0;
delay
}
void lcd_data(unsigned char b)
{
rs=1;
PORTD&=0x0f;
PORTD|=b&0xf0;
en=1;
delay
en=0;
delay
PORTD&=0x0f;
PORTD|=(b<<4)&0xf0;
en=1;
delay
en=0;
delay
}
void display(unsigned char *s)
{
while(*s)
{
lcd_data(*s++);
}
}
void key_pressed()
{
r1=1;
r2=1;
r3=1;
r4=1;
c1=1;
c2=1;
c3=1;

r1=0;
if(c1==0)
{
delay
while(c1==0);
lcd_data('1');
key='1';
//return '1';
}
if(c2==0)
{
delay
while(c2==0);
lcd_data('2');
key='2';
//return '2';
}
if(c3==0)
{
delay
while(c3==0);
lcd_data('3');
key='3';
//return '3';
}

r1=1;
r2=0;
if(c1==0)
{
delay
while(c1==0);
lcd_data('4');
key='4';
//return '4';
}
if(c2==0)
{
delay
while(c2==0);
lcd_data('5');
key='5';
//return '5';
}
if(c3==0)
{
delay
while(c3==0);
lcd_data('6');
key='6';
//return '6';
}

r2=1;
r3=0;
if(c1==0)
{
delay
while(c1==0);
lcd_data('7');
key='7';
//return '7';
}
if(c2==0)
{
delay
while(c2==0);
lcd_data('8');
key='8';
//return '8';
}
if(c3==0)
{
delay
while(c3==0);
lcd_data('9');
key='9';
//return '9';
}

r3=1;
r4=0;
if(c1==0)
{
delay
while(c1==0);
lcd_data('*');
key='*';
//return '*';
}
if(c2==0)
{
delay
while(c2==0);
lcd_data('0');
key='0';
//return '0';
}
if(c3==0)
{
delay
while(c3==0);
lcd_data('#');
key='#';
//return '#';
}
}
void write(unsigned char address,unsigned char data)
{
unsigned char gie_status;
while(EECON1bits.WR);
EEADR=address;
EEDATA=data;
EECON1bits.WREN=1;
gie_status=INTCONbits.GIE;
INTCONbits.GIE=0;
EECON2=0x55;
EECON2=0xAA;
EECON1bits.WR=1;
INTCONbits.GIE=gie_status;
EECON1bits.WREN=0;
}
unsigned char read(unsigned char address)
{
while(EECON1bits.RD||EECON1bits.WR);
EEADR=address;
EECON1bits.RD=1;
return(EEDATA);
}
void uart_init()
{
TRISCbits.RC6=0;
TRISCbits.RC7=1;
SPBRG=31;
TXSTAbits.SYNC=0;
RCSTAbits.SPEN=1;
RCSTAbits.CREN=1;
PIE1bits.TXIE=1;
PIE1bits.RCIE=1;
TXSTAbits.TX9=0;
RCSTAbits.RX9=0;
TXSTAbits.TXEN=1;
}
void tx_char(unsigned char a)
{
while(PIR1bits.TXIF==0);
TXREG=a;
}
unsigned char rx_char()
{
while(PIR1bits.RCIF==0);
if(RCSTAbits.OERR)
{
RCSTAbits.CREN=0;
delay;
RCSTAbits.CREN=1;
}
return(RCREG);
}

void tx_str(unsigned char *s)
{
while(*s)
{
tx_char(*s++);
}
}
void delay_30s(void)
{
int i;
for(i=0;i<30;i++)
{
T0CON=0x86;
TMR0H=0x67;
TMR0L=0x68;
while(!INTCONbits.TMR0IF);
INTCONbits.TMR0IF=0;
T0CON=0x00;
}
}
//void eeprom_msg()
//{
//while(1)
//{
//key_pressed();
//switch(key)
//{
//case '1':
//lcd_cmd(0x01);
//display(msg4);
//for(i=0;i<17;i++)
//{
//write(add1+i,msg4[i]);
//read_char1=read(add1+i);
//tx_char(read_char1);	
//}
////while(1);
//break;
//case '2':
//lcd_cmd(0x01);
//display(msg5);
//for(i=0;i<17;i++)
//{
//write(add2+i,msg5[i]);
//read_char2=read(add2+i);
//tx_char(read_char2);	
//}
////while(1);
////delay_30s();
//break;
//case '3':
//lcd_cmd(0x01);
//display(msg6);
//for(i=0;i<17;i++)
//{
//write(add3+i,msg6[i]);
//read_char3=read(add3+i);
//tx_char(read_char3);	
//}
////while(1);
//break;	
//}
//}
//}
void display_eeprom()
{
switch(key)
{
case '1':
lcd_cmd(0x01);
display(msg4);
for(i=0;i<17;i++)
{
write(add1+i,msg4[i]);
read_char1=read(add1+i);
tx_char(read_char1);	
}
//while(1);
break;
case '2':
lcd_cmd(0x01);
display(msg5);
for(i=0;i<17;i++)
{
write(add2+i,msg5[i]);
read_char2=read(add2+i);
tx_char(read_char2);	
}
//while(1);
//delay_30s();
break;
case '3':
lcd_cmd(0x01);
display(msg6);
for(i=0;i<17;i++)
{
write(add3+i,msg6[i]);
read_char3=read(add3+i);
tx_char(read_char3);	
}
//while(1);
break;	
}
}
