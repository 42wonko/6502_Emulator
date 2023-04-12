#ifndef CPU_6502_H
#define CPU_6502_H

#include "memory.h"

class CPU6502 {
	public:
		//--------------------------
		// definition of constants
		//--------------------------
		enum SR_BIT_NUM {
			NUM_BIT_SR_C	= 0,	// Carry flag
			NUM_BIT_SR_Z	= 1,	// Zero flag
			NUM_BIT_SR_I	= 2,	// Interrupt disable
			NUM_BIT_SR_D	= 3,	// Decimal mode flag
			NUM_BIT_SR_B	= 4,	// break command
			NUM_BIT_SR_U	= 5,	// bit 5 is unused
			NUM_BIT_SR_V	= 6,	// Overflow flag
			NUM_BIT_SR_N	= 7,	// Negative flag
		};
	
		static constexpr Byte	MSK_SR_NONE	= 0x00;
		static constexpr Byte	MSK_SR_C	= 0x01 << NUM_BIT_SR_C;
		static constexpr Byte	MSK_SR_Z	= 0x01 << NUM_BIT_SR_Z;
		static constexpr Byte	MSK_SR_I	= 0x01 << NUM_BIT_SR_I;
		static constexpr Byte	MSK_SR_D	= 0x01 << NUM_BIT_SR_D;
		static constexpr Byte	MSK_SR_B	= 0x01 << NUM_BIT_SR_B;
		static constexpr Byte	MSK_SR_U	= 0x01 << NUM_BIT_SR_U;
		static constexpr Byte	MSK_SR_V	= 0x01 << NUM_BIT_SR_V;
		static constexpr Byte	MSK_SR_N	= 0x01 << NUM_BIT_SR_N;

		enum ACCESS_TYPE {
			TYPE_READ	= 0,
			TYPE_WRITE	= 1
		};

		static constexpr Byte INS_ADC_IM	= 0x69;
		static constexpr Byte INS_ADC_ABS	= 0x6d;
		static constexpr Byte INS_ADC_ZP	= 0x65;
		static constexpr Byte INS_ADC_IND_X	= 0x61;
		static constexpr Byte INS_ADC_IND_Y	= 0x71;
		static constexpr Byte INS_ADC_ZPX	= 0x75;
		static constexpr Byte INS_ADC_ABS_X	= 0x7d;
		static constexpr Byte INS_ADC_ABS_Y	= 0x79;

		static constexpr Byte INS_AND_IM	= 0x29;
		static constexpr Byte INS_AND_ABS	= 0x2d;
		static constexpr Byte INS_AND_ZP	= 0x25;
		static constexpr Byte INS_AND_IND_X	= 0x21;
		static constexpr Byte INS_AND_IND_Y	= 0x31;
		static constexpr Byte INS_AND_ZPX	= 0x35;
		static constexpr Byte INS_AND_ABS_X	= 0x3d;
		static constexpr Byte INS_AND_ABS_Y	= 0x39;

		static constexpr Byte INS_ASL_ABS	= 0x0e;
		static constexpr Byte INS_ASL_ZP	= 0x06;
		static constexpr Byte INS_ASL_ACC	= 0x0a;
		static constexpr Byte INS_ASL_ZPX	= 0x16;
		static constexpr Byte INS_ASL_ABS_X	= 0x1e;

		static constexpr Byte INS_BCC_REL	= 0x90;

		static constexpr Byte INS_BCS_REL	= 0xb0;

		static constexpr Byte INS_BEQ_REL	= 0xf0;

		static constexpr Byte INS_BIT_ABS	= 0x2c;
		static constexpr Byte INS_BIT_ZP	= 0x24;

		static constexpr Byte INS_BMI_REL	= 0x30;

		static constexpr Byte INS_BNE_REL	= 0xd0;

		static constexpr Byte INS_BPL_REL	= 0x10;

		static constexpr Byte INS_BRK_IMP	= 0x00;

		static constexpr Byte INS_BVC_REL	= 0x50;

		static constexpr Byte INS_BVS_REL	= 0x70;

		static constexpr Byte INS_CLC_IMP	= 0x18;

		static constexpr Byte INS_CLD_IMP	= 0xd8;

		static constexpr Byte INS_CLI_IMP	= 0x58;

		static constexpr Byte INS_CLV_IMP	= 0xb8;
		
		static constexpr Byte INS_CMP_IM	= 0xc9;
		static constexpr Byte INS_CMP_ABS	= 0xcd;
		static constexpr Byte INS_CMP_ZP	= 0xc5;
		static constexpr Byte INS_CMP_IND_X	= 0xc1;
		static constexpr Byte INS_CMP_IND_Y	= 0xd1;
		static constexpr Byte INS_CMP_ZPX	= 0xd5;
		static constexpr Byte INS_CMP_ABS_X	= 0xdd;
		static constexpr Byte INS_CMP_ABS_Y	= 0xd9;

		static constexpr Byte INS_CPX_IM	= 0xe0;
		static constexpr Byte INS_CPX_ABS	= 0xec;
		static constexpr Byte INS_CPX_ZP	= 0xe4;

		static constexpr Byte INS_CPY_IM	= 0xc0;
		static constexpr Byte INS_CPY_ABS	= 0xcc;
		static constexpr Byte INS_CPY_ZP	= 0xc4;

		static constexpr Byte INS_DEC_ABS	= 0xce;
		static constexpr Byte INS_DEC_ZP	= 0xc6;
		static constexpr Byte INS_DEC_ZPX	= 0xd6;
		static constexpr Byte INS_DEC_ABS_X	= 0xde;

		static constexpr Byte INS_DEX_IMP	= 0xca;

		static constexpr Byte INS_DEY_IMP	= 0x88;

		static constexpr Byte INS_EOR_IM	= 0x49;
		static constexpr Byte INS_EOR_ABS	= 0x4d;
		static constexpr Byte INS_EOR_ZP	= 0x45;
		static constexpr Byte INS_EOR_IND_X	= 0x41;
		static constexpr Byte INS_EOR_IND_Y	= 0x51;
		static constexpr Byte INS_EOR_ZPX	= 0x55;
		static constexpr Byte INS_EOR_ABS_X	= 0x5d;
		static constexpr Byte INS_EOR_ABS_Y	= 0x59;

		static constexpr Byte INS_INC_ABS	= 0xee;
		static constexpr Byte INS_INC_ZP	= 0xe6;
		static constexpr Byte INS_INC_ZPX	= 0xf6;
		static constexpr Byte INS_INC_ABS_X	= 0xfe;

		static constexpr Byte INS_INX_IMP	= 0xe8;

		static constexpr Byte INS_INY_IMP	= 0xc8;

		static constexpr Byte INS_JMP_ABS	= 0x4c;
		static constexpr Byte INS_JMP_IND	= 0x6c;

		static constexpr Byte INS_JSR_ABS	= 0x20;

		static constexpr Byte INS_LDA_IM	= 0xa9;
		static constexpr Byte INS_LDA_ABS	= 0xad;
		static constexpr Byte INS_LDA_ABS_X	= 0xbd;
		static constexpr Byte INS_LDA_ABS_Y	= 0xb9;
		static constexpr Byte INS_LDA_IND_X	= 0xa1;
		static constexpr Byte INS_LDA_IND_Y	= 0xb1;
		static constexpr Byte INS_LDA_ZP	= 0xa5;
		static constexpr Byte INS_LDA_ZPX	= 0xb5;

		static constexpr Byte INS_LDX_IM	= 0xa2;
		static constexpr Byte INS_LDX_ABS	= 0xae;
		static constexpr Byte INS_LDX_ZP	= 0xa6;
		static constexpr Byte INS_LDX_ZPY	= 0xb6;
		static constexpr Byte INS_LDX_ABS_Y	= 0xbe;

		static constexpr Byte INS_LDY_IM	= 0xa0;
		static constexpr Byte INS_LDY_ABS	= 0xac;
		static constexpr Byte INS_LDY_ZP	= 0xa4;
		static constexpr Byte INS_LDY_ZPX	= 0xb4;
		static constexpr Byte INS_LDY_ABS_X	= 0xbc;
		
		static constexpr Byte INS_LSR_ABS	= 0x4e;
		static constexpr Byte INS_LSR_ZP	= 0x46;
		static constexpr Byte INS_LSR_ACC	= 0x4a;
		static constexpr Byte INS_LSR_ZPX	= 0x56;
		static constexpr Byte INS_LSR_ABS_X	= 0x5e;

		static constexpr Byte INS_NOP_IMP	= 0xea;

		static constexpr Byte INS_ORA_IM	= 0x09;
		static constexpr Byte INS_ORA_ABS	= 0x0d;
		static constexpr Byte INS_ORA_ZP	= 0x05;
		static constexpr Byte INS_ORA_ZPX	= 0x15;
		static constexpr Byte INS_ORA_IND_X	= 0x01;
		static constexpr Byte INS_ORA_IND_Y	= 0x11;
		static constexpr Byte INS_ORA_ABS_X	= 0x1d;
		static constexpr Byte INS_ORA_ABS_Y	= 0x19;

		static constexpr Byte INS_PHA_IMP	= 0x48;

		static constexpr Byte INS_PHP_IMP	= 0x08;

		static constexpr Byte INS_PLA_IMP	= 0x68;

		static constexpr Byte INS_PLP_IMP	= 0x28;

		static constexpr Byte INS_ROL_ABS	= 0x2e;
		static constexpr Byte INS_ROL_ZP	= 0x26;
		static constexpr Byte INS_ROL_ZPX	= 0x36;
		static constexpr Byte INS_ROL_ABS_X	= 0x3E;
		static constexpr Byte INS_ROL_ACC	= 0x2a;

		static constexpr Byte INS_ROR_ABS	= 0x6e;
		static constexpr Byte INS_ROR_ZP	= 0x66;
		static constexpr Byte INS_ROR_ZPX	= 0x76;
		static constexpr Byte INS_ROR_ABS_X	= 0x7e;
		static constexpr Byte INS_ROR_ACC	= 0x6a;

		static constexpr Byte INS_RTI_IMP	= 0x40;

		static constexpr Byte INS_RTS_IMP	= 0x60;

		static constexpr Byte INS_SBC_IM	= 0xe9;
		static constexpr Byte INS_SBC_ABS	= 0xed;
		static constexpr Byte INS_SBC_ZP	= 0xe5;
		static constexpr Byte INS_SBC_IND_X	= 0xe1;
		static constexpr Byte INS_SBC_IND_Y	= 0xf1;
		static constexpr Byte INS_SBC_ZPX	= 0xf5;
		static constexpr Byte INS_SBC_ABS_X	= 0xfd;
		static constexpr Byte INS_SBC_ABS_Y	= 0xf9;

		static constexpr Byte INS_SEC_IMP	= 0x38;

		static constexpr Byte INS_SED_IMP	= 0xf8;

		static constexpr Byte INS_SEI_IMP	= 0x78;

		static constexpr Byte INS_STA_ABS	= 0x8d;
		static constexpr Byte INS_STA_ZP	= 0x85;
		static constexpr Byte INS_STA_IND_X	= 0x81;
		static constexpr Byte INS_STA_IND_Y	= 0x91;
		static constexpr Byte INS_STA_ZPX	= 0x95;
		static constexpr Byte INS_STA_ABS_X	= 0x9d;
		static constexpr Byte INS_STA_ABS_Y	= 0x99;

		static constexpr Byte INS_STX_ABS	= 0x8e;
		static constexpr Byte INS_STX_ZP	= 0x86;
		static constexpr Byte INS_STX_ZPY	= 0x96;

		static constexpr Byte INS_STY_ABS	= 0x8c;
		static constexpr Byte INS_STY_ZP	= 0x84;
		static constexpr Byte INS_STY_ZPX	= 0x94;

		static constexpr Byte INS_TAX_IMP	= 0xaa;

		static constexpr Byte INS_TAY_IMP	= 0xa8;

		static constexpr Byte INS_TSX_IMP	= 0xba;

		static constexpr Byte INS_TXA_IMP	= 0x8a;

		static constexpr Byte INS_TXS_IMP	= 0x9a;

		static constexpr Byte INS_TYA_IMP	= 0x98;

		CPU6502(Memory& mem);
		~CPU6502(void);

		void			SetDebug(bool aDebug){ mDebug = aDebug;};
		void			Reset(void);
		unsigned int	Run(unsigned int const aClocks);
		unsigned int	GetClocks(void);
		Word			GetPC(void){return PC;};
		Byte			GetA(void){return A;};
		Byte			GetX(void){return X;};
		Byte			GetY(void){return Y;};
		Byte			GetSP(void){return SP;};
		Byte			GetSR(void){return SR;};
		void			SetA(Byte aVal){A = aVal;};
		void			SetX(Byte aVal){X = aVal;};
		void			SetY(Byte aVal){Y = aVal;};
		void			SetSP(Byte const aVal){SP = aVal;};
		void			SetSR(Byte const aVal){SR = aVal;};
		void			SetPC(Word const aVal){PC = aVal;};

	protected:

	private:
		static constexpr Word	StackBase	= 0x0100;	// stack resides at 0x0100 - 0x01ff

		//--------------------------
		// definition of methods
		//--------------------------
		Byte GetByte(void);									// Read one byte from memory and increment PC
		Byte ReadByte(Word aAddress);						// Read one byte from memory without incrementing PC
		void WriteByte(Word aAddress, Byte aValue);			// Write one byte to memory without incrementing PC
//		Word GetWord(void);									// Read two bytes frm memory and incement PC
		Word ReadWord(Word aAddress);						// Read one word from memory without incrementing PC
		Word AddrModeAbs(void);								// Read address from memory in absolute adressing mode.
		Word AddrModeAbsX(ACCESS_TYPE aType = TYPE_READ);	// Read address from memory in absolute X adressing mode.
		Word AddrModeAbsY(ACCESS_TYPE aType = TYPE_READ);	// Read address from memory in absolute Y adressing mode.
		Word AddrModeInd(void);								// Read address from memory in indirect adressing mode.
		Word AddrModeIndX(void);							// Read address from memory in indirect X adressing mode.
		Word AddrModeIndY(ACCESS_TYPE aType = TYPE_READ);	// Read address from memory in indirect Y adressing mode.
		Word AddrModeZpX(void);								// Read address from memory in zero page X adressing mode.
		Word AddrModeZpY(void);								// Read address from memory in zero page Y adressing mode.
		Word AddrModeZp(void);								// Read address from memory in zero page adressing mode.
		Word AddrModeRel(void);								// Read address from program counter for relative adressing mode.
		
		void SetBit(Byte& aByte, Byte const aNum);			//
		void ClearBit(Byte& aByte, Byte const aNum);		//
		void SetStatus_N_Z(Byte const aRegister);							// 
		void AdcSetBinStatus(Word const aTmpA, Word const aImValue);		//	
		void AdcSetBcdStatus(Word const aVal);								//
		void AdcDoAdd(Word const aVal);										//
		void AdcDoBinAdd(Word const tmpA, Word imValue);					//
		void AdcDoBcdAdd(Word const tmpA, Word const imValue);				// 
		void SbcSetBinStatus(Word const aTmpA, Word const aImValue);		//	
		void SbcSetBcdStatus(Word const aVal);								//
		void DoSbc(Word const aVal);										//
		void DoBinSbc(Word const tmpA, Word imValue);						//
		void DoBcdSbc(Word const tmpA, Word const imValue);					// 
		void DoAsl(Word const aAddress, Byte aValue);						//
		void BranchOnFlagClear(Byte const aFlag);							// Perform a relative jump if the flag is clear (BCC,BNE,BPL,BVC)
		void BranchOnFlagSet(Byte const aFlag);								// Perform a relative jump if the flag is set (BCS,BEQ,BMI,BVS)
		void DoBitTest(Byte const aValue);									// Handle the BIT instruction.
		void DoCompare(unsigned char const aReg, unsigned char const aValue);	// compare register to memory contents
		void DoDec(Word const aAddress);									// 	
		void DoInc(Word const aAddress);									// 	
		void DoEor(Byte const aValue);										// 	
		void DoLsr(Word const aAddress);									// 	
		void DoRol(Word const aAddress);									// 	
		void DoRor(Word const aAddress);									// 	
		void PrintDebugStatus(void);

		//--------------------------
		// definition of member vars
		//--------------------------
		Word			PC;		// Program counter
		Byte			SP;		// Stack pointer
		Byte			SR;		// Status register
		Byte			A;		// Accumulator
		Byte			X;		// Index register X
		Byte			Y;		// Index register Y

		Memory&			mMem;	// Our connection to the computer memory
		unsigned int	mClocks;
		bool			mDebug;
};

#endif
