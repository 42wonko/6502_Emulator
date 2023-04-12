#ifndef CPU_MEMORY_H
#define CPU_MEMORY_H

typedef unsigned char 	Byte;
typedef unsigned short 	Word;
typedef unsigned int 	u32;

class Memory
{
	public:
		static constexpr u32	MAX_MEM = 1024 * 64;

		Byte operator[](u32 aAddress) const;
		Byte& operator[](u32 aAddress);
		void WriteByte(u32 const aAddress, Byte const aValue);
		void WriteWord(Word aData, u32 aAddress);
		Byte* Buffer(void);
		
	protected:

	private:
		Byte					Data[MAX_MEM];


};

#endif	/* CPU_MEMORY_H	*/

