#include "common.h"
#include <stdio.h>                                                                                             
#include <stdlib.h> 
#include <time.h>

unsigned int timeGetTime()  
{  
	unsigned int uptime = 0;  
        struct timespec on;  
        if(clock_gettime(CLOCK_MONOTONIC, &on) == 0)  
	        uptime = on.tv_sec*1000 + on.tv_nsec/1000000;  
	return uptime;  
}  


unsigned long GetTickCount()
{
    	struct timespec ts;
    	clock_gettime(CLOCK_MONOTONIC, &ts);
    	return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

/*
unsigned char* ASCIItoUNICODE (unsigned char ch)                                                               
{                                                                                                              
	unsigned char Val[2];                                                                                          
	if ((ch < 192)&&(ch != 168)&&(ch != 184))  {Val[0] = 0; Val[1] = ch;    return Val;}                           
	if (ch == 168) {Val[0] = 208;   Val[1] = 129;   return Val;}                                                   
	if (ch == 184) {Val[0] = 209;   Val[1] = 145;   return Val;}                                                   
	if (ch < 240)  {Val[0] = 208;   Val[1] = ch-48; return Val;}                                                   
	if (ch < 249)  {Val[0] = 209;   Val[1] = ch-112;        return Val;}                                           
}                                                                                                              
unsigned int* ConvertString (unsigned char *string)                                                            
{                                                                                                              
    unsigned int size=0, *NewString;                                                                           
        unsigned char* Uni;                                                                                    
    while (string[size++]!=0);                                                                                 
        NewString = (unsigned int*)malloc(sizeof(unsigned int)*2*size-1);                                      
        NewString[0]=2*size-1;                                                                                 
        size=0;                                                                                                
        while (string[size]!=0)                                                                                
        {                                                                                                      
            Uni = ASCIItoUNICODE(string[size]);                                                                
            NewString[2*size+1]=Uni[0];                                                                        
            NewString[2*size+2]=Uni[1];                                                                        
            size++;                                                                                            
        }                                                                                                      
        return NewString;                                                                                      
} */ 

std::string ASCIIToUTF8(const std::string& str)
{
	//return code_convert("ascii","utf-8",str,strlen(str),outbuf,255);
	return ".";	
}

std::string UTF8ToASCII(const std::string& str)
{
	//return code_convert("utf-8","ascii",str,strlen(str),outbuf,255);
	return ".";
}

//crc
//High-Order Byte Table
/* Table of CRC values for high��Corder byte */
const unsigned auchCRCHi[256] = {
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
	0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
	0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
	0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
	0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
	0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
	0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
	0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
	0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
	0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
	0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
	0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
	0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
	0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
	0x40
} ;


//Low-Order Byte Table
/* Table of CRC values for low��Corder byte */
const unsigned auchCRCLo[256] = {
	0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,
	0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
	0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD,
	0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
	0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
	0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
	0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE,
	0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
	0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2,
	0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
	0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB,
	0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
	0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91,
	0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
	0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88,
	0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
	0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,
	0x40
};

std::string getRandomCode()
{
#define n 10
	char list[n+1];
	srand((uint32_t)time(NULL));
    for(int i=0;i<n;i++)
       list[i]=rand()%26+97;
	list[n] = '\0';
	return std::string(list);
}

int ByteToInt32(uint8_t *buf)
{
	return (buf[0] & 0xFF) | (buf[1] << 8) | (buf[2] << 16) | (buf[3] << 24);
}

uint16_t ByteToInt16(uint8_t *buf)
{
	return (buf[0] & 0xFF) | (buf[1] << 8);
}

float ByteToFloat(uint8_t *buf)
{
	float val = 0;
	uint8_t *data = (uint8_t *)&val;
	data[0] = buf[0];
	data[1] = buf[1];
	data[2] = buf[2];
	data[3] = buf[3];
	return val;
}

double ByteToDouble(uint8_t *buf)
{
	double val = 0;
	uint8_t *data = (uint8_t *)&val;
	data[0] = buf[0];
	data[1] = buf[1];
	data[2] = buf[2];
	data[3] = buf[3];
	data[4] = buf[4];
	data[5] = buf[5];
	data[6] = buf[6];
	data[7] = buf[7];
	return val;
}

std::string ByteToString(uint8_t *buf,uint32_t len)
{
	std::string str;
	char *strValue = new char[len+1];
    memcpy(strValue,buf,len);
	strValue[len] = '\0';
    str.append(strValue);
	return str;
}

uint8_t *Int16ToByte(uint8_t *buf,uint16_t val)
{
	buf[0] = val & 0xFF;
	buf[1] = val >> 8;
	return buf+2;
}
uint8_t *Int32ToByte(uint8_t *buf,uint32_t val)
{
	buf[0] = val & 0xFF;
	buf[1] = val >> 8;
	buf[2] = val >> 16;
	buf[3] = val >> 24;
	return buf+4;
}


uint8_t *LongToByte(uint8_t *buf,uint64_t val)
{
	uint8_t *data = (uint8_t *)&val;
    buf[0] = data[0];
	buf[1] = data[1];
	buf[2] = data[2];
	buf[3] = data[3];
	buf[4] = data[4];
	buf[5] = data[5];
	buf[6] = data[6];
	buf[7] = data[7];
	return buf+8;
}


uint8_t *DoubleToByte(uint8_t *buf,double val)
{
    uint8_t *data = (uint8_t *)&val;
    buf[0] = data[0];
	buf[1] = data[1];
	buf[2] = data[2];
	buf[3] = data[3];
	buf[4] = data[4];
	buf[5] = data[5];
	buf[6] = data[6];
	buf[7] = data[7];
	return buf+8;
}

uint8_t *FloatToByte(uint8_t *buf,float val)
{
	uint8_t *data = (uint8_t *)&val;
	buf[0] = data[0];
	buf[1] = data[1];
	buf[2] = data[2];
	buf[3] = data[3];
	return buf+4;
}

// �ȸߺ��
uint16_t Big_ByteToInt16(uint8_t *buf)
{
	return ((uint16_t)buf[0] << 8) | (uint16_t)(buf[1] & 0xFF);
}

uint8_t *Big_Int16ToByte(uint8_t *buf,uint16_t val)
{
	buf[0] = val >> 8;
	buf[1] = val & 0xFF;
	return buf+2;
}

//CRC-ITU
uint16_t crc16_verify( uint8_t *buf, uint16_t len )
{
	unsigned char uchCRCHi = 0xFF;

	unsigned char uchCRCLo = 0xFF;

	uint16_t uIndex;

	while (len--)
	{
		uIndex = uchCRCLo ^ *buf++ ;
		uchCRCLo = uchCRCHi ^ auchCRCHi[uIndex];
		uchCRCHi = auchCRCLo[uIndex] ; 
	} 

	return ( (uchCRCHi << 8)| uchCRCLo );
}
