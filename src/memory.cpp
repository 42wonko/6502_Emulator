#include <iostream>
#include "memory.h"

Byte Memory::operator[](u32 aAddress) const
{
	return Data[aAddress];
}

Byte& Memory::operator[](u32 aAddress)
{
	return Data[aAddress];
}

void Memory::WriteByte(u32 const aAddress, Byte const aValue)
{
	Data[aAddress] = aValue;
}

void Memory::WriteWord(Word aData, u32 aAddress)
{
	Data[aAddress]		= (Byte)(aData & 0xff);
	Data[aAddress + 1]	= (Byte)((aData >> 8));
}

Byte* Memory::Buffer(void)
{
	return Data;
}
