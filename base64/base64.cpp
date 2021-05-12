
//base64.cpp
// BASE64.cpp : 定义控制台应用程序的入口点。
//
//#include "stdafx.h"
//#include "base64.h"
#include "string.h"
#include <stdio.h>
static const char* ALPHA_BASE = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"; //BASE64  64个字符

void enBASE64code(char* charBuf, int charBufLen, char* base64Char, int& base64CharLen);       //BASE64编码
void deBASE64code(char* base64Char, int base64CharLen, char* outStr, int& outStrLen);           //BASE64解码





int main()
{
  


    char str[] = "sdfsdfsdfsd5沈雪冰151546……*（U&*(@&";
    int strLen = strlen(str);
    char str_base64[1024] = { 0 };
    int base64Len;
    enBASE64code(str, strLen, str_base64, base64Len);
    printf("BASE64：%s\n", str_base64);
    printf("len=%d\n", base64Len);

    const  char* test = "c2Rmc2Rmc2Rmc2Q1yfLRqbH5MTUxNTQ2oa2hrSqjqFUmKihAJg==";
    char de_str[1024] = { 0 };
    int de_strLen = 1024;

   // deBASE64code(str_base64, base64Len, de_str, de_strLen);
    deBASE64code((char*)test, strlen(test), de_str, de_strLen);
    printf("解析后：%s\n", de_str);


    printf("len=%d\n", de_strLen);
    getchar();
}




void enBASE64code(char* charBuf, int charBufLen, char* base64Char, int& base64CharLen)
{
    int a = 0;
    int i = 0;
    while (i < charBufLen)
    {
        char b0 = charBuf[i++];
        char b1 = (i < charBufLen) ? charBuf[i++] : 0;
        char b2 = (i < charBufLen) ? charBuf[i++] : 0;

        int int63 = 0x3F;   //  00111111 意图去掉8bit的两高位
        int int255 = 0xFF;  // 11111111
        base64Char[a++] = ALPHA_BASE[(b0 >> 2) & int63];    //b0字符的前6bit   00+6bit 组成一个十进制数 即BASE编码表号
        base64Char[a++] = ALPHA_BASE[((b0 << 4) | ((b1 & int255) >> 4)) & int63];   //b0 要想取最后两位，所以左移四位 得到最后两位 再和b1字符的 前四个字符做  或运算 组成6bit  00+6bit
        base64Char[a++] = ALPHA_BASE[((b1 << 2) | ((b2 & int255) >> 6)) & int63];   //b1 要想得到后四位  需要右移2位 再和 b2的前4 位做或运算 组成6bit   00+bit 租组成BASE64编码
        base64Char[a++] = ALPHA_BASE[b2 & int63];  //b2的后6位   00+6bit 组成BASE编码号
    }
    //最后不够4个字符  补=，最多补两个 ==
    switch (charBufLen % 3)
    {
    case 1:
        base64Char[--a] = '=';
    case 2:
        base64Char[--a] = '=';
    }
    base64CharLen = strlen(base64Char); //输出的base64长度

}

void deBASE64code(char* base64Char, int base64CharLen, char* outStr, int& outStrLen)
{
    int toInt[128] = { -1 };
    for (int i = 0; i < 64; i++) //将ANSI 码找到对应的BASE64码
    {
        int pos = ALPHA_BASE[i];
        toInt[pos] = i;
    }
    int int255 = 0xFF;  //11111111
    int index = 0;
    for (int i = 0; i < base64CharLen; i += 4)
    {
        int c0 = toInt[base64Char[i]]; // 获取一组中第一个BASE64编码号
        int c1 = toInt[base64Char[i + 1]];// 获取一组中第二个BASE64编码号
        outStr[index++] = (((c0 << 2) | (c1 >> 4)) & int255);  //c0后6位  和c1去完前2位的  的前2位  组成8bit 再转换成字符  
        if (index >= base64CharLen)  //如果长度小于输入进来的长度 意图去掉=
        {
            return;
        }
        int c2 = toInt[base64Char[i + 2]];// 获取一组中第三个BASE64编码号
        outStr[index++] = (((c1 << 4) | (c2 >> 2)) & int255);  //c1的后6位和c2去完前2位的  的前2位 组成8bit  转换成字符
        if (index >= outStrLen)  //如果长度小于输入进来的长度  意图去掉=
        {
            return;
        }
        int c3 = toInt[base64Char[i + 3]];// 获取一组中第四个BASE64编码号
        outStr[index++] = (((c2 << 6) | c3) & int255); //c2的后2位和c3的后6位  组成8bit 转换成字符
    }
    outStrLen = strlen(outStr);

}
