#ifndef __Register__
#define __Register__

inline void Register_SetBit(volatile unsigned char* Register, unsigned char Bit){
  *Register = *Register | (1 << Bit);
}

inline void Register_ResetBit(volatile unsigned char* Register, unsigned char Bit){
  *Register = *Register & ~(1 << Bit);
}

inline void Register_ToggleBit(volatile unsigned char* Register, unsigned char Bit){
  *Register = *Register ^ (1 << Bit);
}

inline unsigned char Register_GetBit(volatile unsigned char* Register, unsigned char Bit){
  return (*Register >> Bit) & (unsigned char)0x01;
}

#endif