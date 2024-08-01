# 1 "CustomLibs/src/compress.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 379 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "CustomLibs/src/compress.c" 2
# 1 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdint.h" 1 3
# 56 "C:\\Keil_v5\\ARM\\ARMCLANG\\Bin\\..\\include\\stdint.h" 3
typedef signed char int8_t;
typedef signed short int int16_t;
typedef signed int int32_t;
typedef signed long long int int64_t;


typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long int uint64_t;





typedef signed char int_least8_t;
typedef signed short int int_least16_t;
typedef signed int int_least32_t;
typedef signed long long int int_least64_t;


typedef unsigned char uint_least8_t;
typedef unsigned short int uint_least16_t;
typedef unsigned int uint_least32_t;
typedef unsigned long long int uint_least64_t;




typedef signed int int_fast8_t;
typedef signed int int_fast16_t;
typedef signed int int_fast32_t;
typedef signed long long int int_fast64_t;


typedef unsigned int uint_fast8_t;
typedef unsigned int uint_fast16_t;
typedef unsigned int uint_fast32_t;
typedef unsigned long long int uint_fast64_t;






typedef signed int intptr_t;
typedef unsigned int uintptr_t;



typedef signed long long intmax_t;
typedef unsigned long long uintmax_t;
# 2 "CustomLibs/src/compress.c" 2






void convert_to_8_bit(uint8_t *arr, int size)
{

 for(int i = 0; i < (size*2); i++)
 {
  uint8_t high_byte = 0;
  high_byte |= ((arr[i*2] & 0xF0) >> 4);
  high_byte |= ((arr[((i*2)+1)] & 0x0F) << 4);
  arr[i] = high_byte;
 }
}






void convert_to_12_bit(uint8_t *arr, int size)
{
    int i = 3, j = 4;
    while (j < size*2)
    {
        if (((j+1)%4) == 0)
        {
            j++;
            continue;
        }

  if ((i%2) == 0)
  {

   arr[i/2] &= 0xF0;
   if((j%2) == 0)
   {

       arr[i/2] |= (arr[j/2] & 0x0F);
   }
   else
   {

       arr[i/2] |= ((arr[j/2] >> 4) & 0x0F);
   }
  }
  else
  {

   arr[i/2] &= 0x0F;
   if((j%2) == 0)
   {

       arr[i/2] |= ((arr[j/2] << 4) & 0xF0);
   }
   else
   {

       arr[i/2] |= (arr[j/2] & 0xF0);
   }
  }
  j++;
  i++;
    }
}
