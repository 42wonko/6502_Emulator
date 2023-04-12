#include "cpu_6502.h"
#include <iostream>
#include <iomanip>

/**

*/
CPU6502::CPU6502(Memory& aMem)
: mMem(aMem), mDebug(false)
{
}
//-----------------------------------------------------------------------------

/**

*/
CPU6502::~CPU6502(void)
{
}
//-----------------------------------------------------------------------------

/**

*/
unsigned int CPU6502::GetClocks(void)
{
	return mClocks;
}
//-----------------------------------------------------------------------------

/**

*/
void CPU6502::Reset(void)
{
	mClocks	= 0;
	PC 		= ReadWord(0xfffc);		// get reset vector
	SP		= 0xff;					// set stack pointer to end of pge one
	A		= 0;					// clear all registers
	X		= 0;
	Y		= 0;
	ClearBit(SR, NUM_BIT_SR_C);		// clear status register
	ClearBit(SR, NUM_BIT_SR_Z);
	ClearBit(SR, NUM_BIT_SR_I);
	ClearBit(SR, NUM_BIT_SR_D);
	ClearBit(SR, NUM_BIT_SR_B);
	ClearBit(SR, NUM_BIT_SR_V);
	ClearBit(SR, NUM_BIT_SR_N);
}
//-----------------------------------------------------------------------------

/**
	Set the status flags for the LDA, LDX and LDY instructions.
	Only Z- and N-flags are effected.
	\param	[in]	aRegister	The register to be tested.
*/
void CPU6502::SetStatus_N_Z(Byte const aRegister)
{
	if(aRegister == 0){
		SetBit(SR, NUM_BIT_SR_Z);
	} else {
		ClearBit(SR, NUM_BIT_SR_Z);
	}

	if((aRegister & 0x80) > 0){
		SetBit(SR, NUM_BIT_SR_N);
	} else {
		ClearBit(SR, NUM_BIT_SR_N);
	}
}
//-----------------------------------------------------------------------------

/**

*/
void CPU6502::AdcSetBcdStatus(Word const aVal)
{									
	if(aVal >= 100){
		SetBit(SR, NUM_BIT_SR_C);
	} else {
		ClearBit(SR, NUM_BIT_SR_C);
	}
	if(A == 0){													// handle zero-flag
		SetBit(SR, NUM_BIT_SR_Z);
	} else {
		ClearBit(SR, NUM_BIT_SR_Z);
	}
	ClearBit(SR, NUM_BIT_SR_V);
	ClearBit(SR, NUM_BIT_SR_N);
}
//-----------------------------------------------------------------------------

/**

*/
void CPU6502::AdcSetBinStatus(Word const aTmpA, Word const aImValue)
{									
	bool pcf = ( ((aTmpA & 0x7f)+(aImValue & 0x7f)) > 0x007f );	// calculate penultimate carry
	bool cf	= ((aTmpA+aImValue+((SR & MSK_SR_C) == 1)) > 0x00ff);						// calculate carry

	if(true == cf){
		SetBit(SR, NUM_BIT_SR_C);
	} else {
		ClearBit(SR, NUM_BIT_SR_C);
	}
/*	
	if(cf ^ pcf){												// Overflow flag is the ExOR of CF and pCF
		SetBit(SR, NUM_BIT_SR_V);
	} else {
		ClearBit(SR, NUM_BIT_SR_V);
	}
*/
	if((((aTmpA & 0x80) == 0 ) && ((aImValue & 0x80) == 0) && ((A & 0x80) > 0))
		|| (((aTmpA & 0x80) > 0 ) && ((aImValue & 0x80) > 0) && ((A & 0x80) == 0))){
		SetBit(SR, NUM_BIT_SR_V);
	} else {
		ClearBit(SR, NUM_BIT_SR_V);
	}
	if(A == 0){													// handle zero-flag
		SetBit(SR, NUM_BIT_SR_Z);
	} else {
		ClearBit(SR, NUM_BIT_SR_Z);
	}
	if(A & 0x80){												// handle negative-flag
		SetBit(SR, NUM_BIT_SR_N);
	} else {
		ClearBit(SR, NUM_BIT_SR_N);
	}
}
//-----------------------------------------------------------------------------

/**

*/
void CPU6502::SbcSetBcdStatus(Word const aVal)
{									
}
//-----------------------------------------------------------------------------

/**

*/
void CPU6502::SbcSetBinStatus(Word const aTmpA, Word const aImValue)
{									
	bool pcf = ( ((aTmpA & 0x7f)+(aImValue & 0x7f)) > 0x007f );	// calculate penultimate carry
//	bool cf	= ((aTmpA+aImValue) > 0x00ff);						// calculate carry
/*
	if(true == cf){
		SetBit(SR, NUM_BIT_SR_C);
	} else {
		ClearBit(SR, NUM_BIT_SR_C);
	}
	
	if(cf ^ pcf){												// Overflow flag is the ExOR of CF and pCF
		SetBit(SR, NUM_BIT_SR_V);
	} else {
		ClearBit(SR, NUM_BIT_SR_V);
	}
	*/
	if(A == 0){													// handle zero-flag
		SetBit(SR, NUM_BIT_SR_Z);
	} else {
		ClearBit(SR, NUM_BIT_SR_Z);
	}
	if(A & 0x80){												// handle negative-flag
		SetBit(SR, NUM_BIT_SR_N);
	} else {
		ClearBit(SR, NUM_BIT_SR_N);
	}
}
//-----------------------------------------------------------------------------

/**

*/
unsigned int CPU6502::Run(unsigned int const aClocks)
{
	while(aClocks > mClocks){
		Byte value			= 0;
		Word address		= 0;
		Byte instruction	= GetByte();

		switch(instruction){
			case INS_ADC_IM:	value	= GetByte();				// fetch immideate value from memory
								AdcDoAdd(value);
								break;
			case INS_ADC_ABS:	value	= ReadByte(AddrModeAbs());	// fetch value from absolute memory
								AdcDoAdd(value);
								break;
			case INS_ADC_ZP:	value	= ReadByte( AddrModeZp());	// fetch value from zero page 
								AdcDoAdd(value);
								break;
			case INS_ADC_IND_X:	value = ReadByte(AddrModeIndX());
								AdcDoAdd(value);
								break;
			case INS_ADC_IND_Y:	value = ReadByte(AddrModeIndY());
								AdcDoAdd(value);
								break;
			case INS_ADC_ZPX:	value	= ReadByte(AddrModeZpX());
								AdcDoAdd(value);
								break;
			case INS_ADC_ABS_X:	value	= ReadByte(AddrModeAbsX());
								AdcDoAdd(value);
								break;
			case INS_ADC_ABS_Y:	value	= ReadByte(AddrModeAbsY());
								AdcDoAdd(value);
								break;
			case INS_AND_IM:	A &= GetByte();
								SetStatus_N_Z(A);
								break;
			case INS_AND_ABS:	A &= ReadByte(AddrModeAbs());
								SetStatus_N_Z(A);
								break;
			case INS_AND_ZP:	A &= ReadByte(AddrModeZp());
								SetStatus_N_Z(A);
								break;
			case INS_AND_IND_X:	A &= ReadByte(AddrModeIndX());									// 
								SetStatus_N_Z(A);
								break;
			case INS_AND_IND_Y:	A &= ReadByte(AddrModeIndY());									// 
								SetStatus_N_Z(A);
								break;
			case INS_AND_ZPX:	A &= ReadByte(AddrModeZpX());
								SetStatus_N_Z(A);
								break;
			case INS_AND_ABS_X: A &= ReadByte(AddrModeAbsX());
								SetStatus_N_Z(A);
								break;
			case INS_AND_ABS_Y: A &= ReadByte(AddrModeAbsY());
								SetStatus_N_Z(A);
								break;
			case INS_ASL_ABS:	address = AddrModeAbs();
								value = ReadByte(address);
								DoAsl(address, value);
								break;
			case INS_ASL_ACC:	if(A & 0x80){
									SetBit(SR, NUM_BIT_SR_C);
								} else {
									ClearBit(SR, NUM_BIT_SR_C);
								}
								A = A << 1;
								++mClocks;
								SetStatus_N_Z(A);
								break;
			case INS_ASL_ZPX:	address = AddrModeZpX();
								value = ReadByte(address);
								DoAsl(address, value);
								break;
			case INS_ASL_ABS_X:	address = AddrModeAbsX();
								value = ReadByte(address);
								DoAsl(address, value);
								++mClocks;												// no idea why
								break;
			case INS_ASL_ZP:	address = AddrModeZp();
								value = ReadByte(address);
								DoAsl(address, value);
								break;
			case INS_BCC_REL:	BranchOnFlagClear(MSK_SR_C);
								break;
			case INS_BPL_REL:	BranchOnFlagClear(MSK_SR_N);
								break;
			case INS_BVC_REL:	BranchOnFlagClear(MSK_SR_V);
								break;
			case INS_BNE_REL:	BranchOnFlagClear(MSK_SR_Z);
								break;
			case INS_BCS_REL:	BranchOnFlagSet(MSK_SR_C);
								break;
			case INS_BMI_REL:	BranchOnFlagSet(MSK_SR_N);
								break;
			case INS_BVS_REL:	BranchOnFlagSet(MSK_SR_V);
								break;
			case INS_BEQ_REL:	BranchOnFlagSet(MSK_SR_Z);
								break;
			case INS_BRK_IMP:	{
									address = ReadWord(0xfffe);
									WriteByte(StackBase+SP, (PC+1)>>8);
									WriteByte(StackBase+SP-1, (PC+1));
									SP -= sizeof(Word);										// adjust stack pointer
									PC = address, mClocks +=2;
									Byte srTmp = SR;
									SetBit(srTmp, NUM_BIT_SR_B);
									SetBit(srTmp, NUM_BIT_SR_U);
									WriteByte(StackBase+SP, srTmp), mClocks +=1;
									SP -= sizeof(Byte);										// adjust stack pointer
									SetBit(SR, NUM_BIT_SR_I);
								}
								break;
			case INS_BIT_ABS:	value = ReadByte(AddrModeAbs());
								DoBitTest(value);
								break;
			case INS_BIT_ZP:	value = ReadByte(AddrModeZp());
								DoBitTest(value);
								break;
			case INS_CLC_IMP:	ClearBit(SR, NUM_BIT_SR_C), ++mClocks;
								break;
			case INS_CLD_IMP:	ClearBit(SR, NUM_BIT_SR_D), ++mClocks;
								break;
			case INS_CLI_IMP:	ClearBit(SR, NUM_BIT_SR_I), ++mClocks;
								break;
			case INS_CLV_IMP:	ClearBit(SR, NUM_BIT_SR_V), ++mClocks;
								break;
			case INS_CMP_IM:	value = GetByte();
								DoCompare(A, value);
								break;
			case INS_CMP_ABS:	value = ReadByte(AddrModeAbs());
								DoCompare(A, value);
								break;
			case INS_CMP_ZP:	value = ReadByte(AddrModeZp());
								DoCompare(A, value);
								break;
			case INS_CMP_IND_X:	value = ReadByte(AddrModeIndX());
								DoCompare(A, value);
								break;
			case INS_CMP_IND_Y:	value = ReadByte(AddrModeIndY());
								DoCompare(A, value);
								break;
			case INS_CMP_ZPX:	value = ReadByte(AddrModeZpX());
								DoCompare(A, value);
								break;
			case INS_CMP_ABS_X:	value = ReadByte(AddrModeAbsX());
								DoCompare(A, value);
								break;
			case INS_CMP_ABS_Y:	value = ReadByte(AddrModeAbsY());
								DoCompare(A, value);
								break;
			case INS_CPX_IM:	value = GetByte();
								DoCompare(X, value);
								break;
			case INS_CPX_ABS:	value = ReadByte(AddrModeAbs());
								DoCompare(X, value);
								break;
			case INS_CPX_ZP:	value = ReadByte(AddrModeZp());
								DoCompare(X, value);
								break;
			case INS_CPY_IM:	value = GetByte();
								DoCompare(Y, value);
								break;
			case INS_CPY_ABS:	value = ReadByte(AddrModeAbs());
								DoCompare(Y, value);
								break;
			case INS_CPY_ZP:	value = ReadByte(AddrModeZp());
								DoCompare(Y, value);
								break;
			case INS_DEC_ABS:	address	= AddrModeAbs();
								DoDec(address);
								break;
			case INS_DEC_ZP:	address = AddrModeZp();
								DoDec(address);
								break;
			case INS_DEC_ZPX:	address = AddrModeZpX();
								DoDec(address);
								break;
			case INS_DEC_ABS_X:	address = AddrModeAbsX();
								DoDec(address);
								++mClocks;
								break;
			case INS_DEX_IMP:	--X; ++mClocks;
								SetStatus_N_Z(X);
								break;
			case INS_DEY_IMP:	--Y; ++mClocks;
								SetStatus_N_Z(Y);
								break;
			case INS_EOR_IM:	value = GetByte();
								DoEor(value);
								break;
			case INS_EOR_ABS:	value = ReadByte(AddrModeAbs());
								DoEor(value);
								break;
			case INS_EOR_ZP:	value = ReadByte(AddrModeZp());
								DoEor(value);
								break;
			case INS_EOR_IND_X:	value = ReadByte(AddrModeIndX());
								DoEor(value);
								break;
			case INS_EOR_IND_Y:	value = ReadByte(AddrModeIndY());
								DoEor(value);
								break;
			case INS_EOR_ZPX:	value = ReadByte(AddrModeZpX());
								DoEor(value);
								break;
			case INS_EOR_ABS_X:	value = ReadByte(AddrModeAbsX());
								DoEor(value);
								break;
			case INS_EOR_ABS_Y:	value = ReadByte(AddrModeAbsY());
								DoEor(value);
								break;
			case INS_INC_ABS:	address	= AddrModeAbs();
								DoInc(address);
								break;
			case INS_INC_ZP:	address = AddrModeZp();
								DoInc(address);
								break;
			case INS_INC_ZPX:	address = AddrModeZpX();
								DoInc(address);
								break;
			case INS_INC_ABS_X:	address = AddrModeAbsX();
								DoInc(address);
								++mClocks;
								break;
			case INS_INX_IMP:	++X; ++mClocks;
								SetStatus_N_Z(X);
								break;
			case INS_INY_IMP:	++Y; ++mClocks;
								SetStatus_N_Z(Y);
								break;
			case INS_JMP_ABS:	PC = AddrModeAbs();
								break;
/*
NB: An original 6502 has does not correctly fetch the target address if the indirect vector falls on a page 
    boundary (e.g. $xxFF where xx is any value from $00 to $FF). In this case fetches the LSB from $xxFF as 
	expected but takes the MSB from $xx00. This is fixed in some later chips like the 65SC02 so for 
	compatibility always ensure the indirect vector is not at the end of the page.
*/
			case INS_JMP_IND:	PC = AddrModeInd();
								break;
			case INS_JSR_ABS:	address = AddrModeAbs();								// read target address
								WriteByte(StackBase+SP, (PC-1)>>8);						// push high byte of return address to stack
								WriteByte(StackBase+SP-1, (PC-1));						// push low byte of return address to stack
								SP -= sizeof(Word);										// adjust stack pointer
								PC = address;											// set program counter to target address (i.e. do th jump)
								++mClocks;
								break;
			case INS_LDA_IM:	A = GetByte();											// load accu immidiate
								SetStatus_N_Z(A);
								break;
			case INS_LDA_ABS:	A = ReadByte(AddrModeAbs());							// load accu absolute
								SetStatus_N_Z(A);
								break;
			case INS_LDA_ABS_X: A = ReadByte(AddrModeAbsX());
								SetStatus_N_Z(A);
								break;
			case INS_LDA_ABS_Y:	A = ReadByte(AddrModeAbsY());
								SetStatus_N_Z(A);
								break;
			case INS_LDA_IND_X: A = ReadByte(AddrModeIndX());									// 
								SetStatus_N_Z(A);
								break;
			case INS_LDA_IND_Y:	A = ReadByte(AddrModeIndY());									// 
								SetStatus_N_Z(A);
								break;
			case INS_LDA_ZP:	A = ReadByte(AddrModeZp());								// load accu zero page
								SetStatus_N_Z(A);
								break;
			case INS_LDA_ZPX:	A 	= ReadByte(AddrModeZpX());
								SetStatus_N_Z(A);
								break;
			case INS_LDX_IM:	X = GetByte();
								SetStatus_N_Z(X);
								break;
			case INS_LDX_ABS:	X = ReadByte(AddrModeAbs());
								SetStatus_N_Z(X);
								break;
			case INS_LDX_ZP:	X =  ReadByte(AddrModeZp());
								SetStatus_N_Z(X);
								break;
			case INS_LDX_ZPY:	X 	= ReadByte(AddrModeZpY());
								SetStatus_N_Z(X);
								break;
			case INS_LDX_ABS_Y:	X = ReadByte(AddrModeAbsY());
								SetStatus_N_Z(X);
								break;
			case INS_LDY_IM:	Y = GetByte();
								SetStatus_N_Z(Y);
								break;
			case INS_LDY_ABS:	Y = ReadByte(AddrModeAbs());
								SetStatus_N_Z(Y);
								break;
			case INS_LDY_ZP:	Y =  ReadByte(AddrModeZp());
								SetStatus_N_Z(Y);
								break;
			case INS_LDY_ZPX:	Y 	= ReadByte(AddrModeZpX());
								SetStatus_N_Z(Y);
								break;
			case INS_LDY_ABS_X:	Y = ReadByte(AddrModeAbsX());
								SetStatus_N_Z(Y);
								break;
			case INS_LSR_ABS:	address	= AddrModeAbs();
								DoLsr(address);
								break;
			case INS_LSR_ZP:	address	= AddrModeZp();
								DoLsr(address);
								break;
			case INS_LSR_ACC:	if(A & 0x01){				// bit 0 will end up in C-flag so check it
									SetBit(SR, NUM_BIT_SR_C);
								} else {
									ClearBit(SR, NUM_BIT_SR_C);
								}
								A = (A >> 1); ++mClocks;
								if(0 == A){
									SetBit(SR, NUM_BIT_SR_Z);
								} else {
									ClearBit(SR, NUM_BIT_SR_Z);
								}
								ClearBit(SR, NUM_BIT_SR_N);
								break;
			case INS_LSR_ZPX:	address	= AddrModeZpX();
								DoLsr(address);
								break;
			case INS_LSR_ABS_X:	address	= AddrModeAbsX();
								DoLsr(address); ++mClocks;
								break;
			case INS_NOP_IMP:	++mClocks;
								break;
			case INS_ORA_IM:	A |= GetByte();											// OR accu immidiate
								SetStatus_N_Z(A);
								break;
			case INS_ORA_ABS:	A |= ReadByte(AddrModeAbs());							// load accu absolute
								SetStatus_N_Z(A);
								break;
			case INS_ORA_ABS_X: A |= ReadByte(AddrModeAbsX());
								SetStatus_N_Z(A);
								break;
			case INS_ORA_ABS_Y:	A |= ReadByte(AddrModeAbsY());
								SetStatus_N_Z(A);
								break;
			case INS_ORA_IND_X: A |= ReadByte(AddrModeIndX());							// 
								SetStatus_N_Z(A);
								break;
			case INS_ORA_IND_Y:	A |= ReadByte(AddrModeIndY());							// 
								SetStatus_N_Z(A);
								break;
			case INS_ORA_ZP:	A |= ReadByte(AddrModeZp());							// load accu zero page
								SetStatus_N_Z(A);
								break;
			case INS_ORA_ZPX:	A |= ReadByte(AddrModeZpX());
								SetStatus_N_Z(A);
								break;
			case INS_PHA_IMP:	mMem[StackBase+SP] = A; ++mClocks;						// push A to stack
								SP -= sizeof(Byte);	++mClocks;
								break;
			case INS_PHP_IMP:	{
									Byte srTmp = SR;
									SetBit(srTmp, NUM_BIT_SR_B);						// PHP always sets B-Flag to 1
									SetBit(srTmp, NUM_BIT_SR_U);						// PHP always sets U-Flag to 1
									mMem[StackBase+SP] = srTmp; ++mClocks;				// push A to stack
									SP -= sizeof(Byte);	++mClocks;
								}
								break;
			case INS_PLA_IMP:	SP += sizeof(Byte); ++mClocks;
								A = mMem[StackBase+SP]; ++mClocks;
								SetStatus_N_Z(A); ++mClocks;					
								break;
			case INS_PLP_IMP:	SP += sizeof(Byte); ++mClocks;
								SR = mMem[StackBase+SP]; mClocks += 2;
								ClearBit(SR, NUM_BIT_SR_B);								// Bits 4 and 5 (B-Flag, unused) are ignored ...
								ClearBit(SR, NUM_BIT_SR_U);								// ... because it doesn't actually exists in SR
								break;
			case INS_ROL_ABS:	address	= AddrModeAbs();
								DoRol(address);
								break;
			case INS_ROL_ABS_X:	address	= AddrModeAbsX();
								DoRol(address); ++mClocks;
								break;
			case INS_ROL_ACC:	{
									bool tmpC	= ((A & 0x80) > 0);				// bit 7 will end up in C-flag so check it

									A = A << 1; ++mClocks;

									if(SR & MSK_SR_C){
										SetBit(A, 0);
									} else {
										ClearBit(A, 0);
									}

									if(tmpC){
										SetBit(SR, NUM_BIT_SR_C);
									} else {
										ClearBit(SR, NUM_BIT_SR_C);
									}
									SetStatus_N_Z(A);
								}
								break;
			case INS_ROL_ZP:	address	= AddrModeZp();
								DoRol(address);
								break;
			case INS_ROL_ZPX:	address	= AddrModeZpX();
								DoRol(address);
								break;
			case INS_ROR_ABS:	address	= AddrModeAbs();
								DoRor(address);
								break;
			case INS_ROR_ABS_X:	address	= AddrModeAbsX();
								DoRor(address); ++mClocks;
								break;
			case INS_ROR_ACC:	{
									bool tmpC	= ((A & 0x01) > 0);				// bit 1 will end up in C-flag so check it

									A = A >> 1; ++mClocks;

									if(SR & MSK_SR_C){
										SetBit(A, 7);
									} else {
										ClearBit(A, 7);
									}

									if(tmpC){
										SetBit(SR, NUM_BIT_SR_C);
									} else {
										ClearBit(SR, NUM_BIT_SR_C);
									}
									SetStatus_N_Z(A);
								}
								break;
			case INS_ROR_ZP:	address	= AddrModeZp();
								DoRor(address);
								break;
			case INS_ROR_ZPX:	address	= AddrModeZpX();
								DoRor(address);
								break;
			case INS_RTI_IMP:	++SP; ++mClocks;
								SR = ReadByte(StackBase + SP);
								ClearBit(SR, NUM_BIT_SR_B);								// Bits 4 and 5 (B-Flag, unused) are ignored ...
								ClearBit(SR, NUM_BIT_SR_U);								// ... because it doesn't actually exists in SR
								++SP; address = ReadByte(StackBase + SP);
								++SP; address += (ReadByte(StackBase + SP) << 8);
								PC = address; ++mClocks;
								break;
			case INS_RTS_IMP:	++SP; address = ReadByte(StackBase + SP);
								++SP; address += (ReadByte(StackBase + SP) << 8);
								PC = address; ++mClocks;
								++PC; mClocks += 2;
								break;
			case INS_SBC_IM:	value	= GetByte();				// fetch immideate value from memory
								DoSbc(value);
								break;
			case INS_SBC_ABS:	value	= ReadByte(AddrModeAbs());	// fetch value from absolute memory
								DoSbc(value);
								break;
			case INS_SBC_ZP:	value	= ReadByte(AddrModeZp());
								DoSbc(value);
								break;
			case INS_SBC_IND_X:	value	= ReadByte(AddrModeIndX());
								DoSbc(value);
								break;
			case INS_SBC_IND_Y:	value	= ReadByte(AddrModeIndY());
								DoSbc(value);
								break;
			case INS_SBC_ZPX:	value	= ReadByte(AddrModeZpX());
								DoSbc(value);
								break;
			case INS_SBC_ABS_X:	value	= ReadByte(AddrModeAbsX());
								DoSbc(value);
								break;
			case INS_SBC_ABS_Y:	value	= ReadByte(AddrModeAbsY());
								DoSbc(value);
								break;
			case INS_SEC_IMP:	SetBit(SR, NUM_BIT_SR_C); ++mClocks;
								break;
			case INS_SED_IMP:	SetBit(SR, NUM_BIT_SR_D); ++mClocks;
								break;
			case INS_SEI_IMP:	SetBit(SR, NUM_BIT_SR_I); ++mClocks;
								break;
			case INS_STA_ABS:	WriteByte(AddrModeAbs(), A);
								break;
			case INS_STA_ZP:	WriteByte(AddrModeZp(), A);
								break;
			case INS_STA_IND_X:	WriteByte(AddrModeIndX(), A);
								break;
			case INS_STA_IND_Y:	WriteByte(AddrModeIndY(TYPE_WRITE), A);
								break;
			case INS_STA_ZPX:	WriteByte(AddrModeZpX(), A);
								break;
			case INS_STA_ABS_X:	WriteByte(AddrModeAbsX(TYPE_WRITE), A);
								break;
			case INS_STA_ABS_Y:	WriteByte(AddrModeAbsY(TYPE_WRITE), A);
								break;
			case INS_STX_ABS:	WriteByte(AddrModeAbs(), X);
								break;
			case INS_STX_ZP:	WriteByte(AddrModeZp(), X);
								break;
			case INS_STX_ZPY:	WriteByte(AddrModeZpY(), X);
								break;
			case INS_STY_ABS:	WriteByte(AddrModeAbs(), Y);
								break;
			case INS_STY_ZP:	WriteByte(AddrModeZp(), Y);
								break;
			case INS_STY_ZPX:	WriteByte(AddrModeZpX(), Y);
								break;
			case INS_TAX_IMP:	X = A; ++mClocks;
								SetStatus_N_Z(X);
								break;
			case INS_TAY_IMP:	Y = A; ++mClocks;
								SetStatus_N_Z(Y);
								break;
			case INS_TSX_IMP:	X = SP; ++mClocks;
								SetStatus_N_Z(X);
								break;
			case INS_TXA_IMP:	A = X; ++mClocks;
								SetStatus_N_Z(A);
								break;
			case INS_TXS_IMP:	SP = X; ++mClocks;
								break;
			case INS_TYA_IMP:	A = Y; ++mClocks;
								SetStatus_N_Z(A);
								break;
			default:			std::cerr << "Instruction <" << std::setw(2) << std::hex << instruction << "> not handled" << std::endl;

		}
		PrintDebugStatus();
}

	return mClocks;
}
//-----------------------------------------------------------------------------

/**

*/

Byte CPU6502::GetByte(void)
{
	Byte data = mMem[PC];
	++PC;
	++mClocks;
	return data;
}
//-----------------------------------------------------------------------------

/**

*/
Byte CPU6502::ReadByte(Word aAddress)
{
	++mClocks;
	return mMem[aAddress];
}
//-----------------------------------------------------------------------------

/**

*/
void CPU6502::WriteByte(Word aAddress, Byte aValue)
{
	++mClocks;
	mMem.WriteByte(aAddress, aValue);
}
//-----------------------------------------------------------------------------

/**

*/
Word CPU6502::AddrModeAbs(void)
{
	// 6502 is little endian
	Word data = mMem[PC];
	++PC;

	data |= (mMem[PC] << 8);
	++PC;
	mClocks += 2;

	return data;
}
//-----------------------------------------------------------------------------

/**

*/
Word CPU6502::AddrModeAbsX(ACCESS_TYPE aType)
{
	Word address = AddrModeAbs();
	if(TYPE_READ == aType){
		if((X > 0) && ((address & 0x00ff)+X >= 0x100 )){
			++mClocks;
		}
	} else {
		++mClocks;
	}
	address += X;

	return address;
}
//-----------------------------------------------------------------------------

/**

*/
Word CPU6502::AddrModeAbsY(ACCESS_TYPE aType)
{
	Word address = AddrModeAbs();
	if(TYPE_READ == aType){
		if((Y > 0) && ((address & 0x00ff) + Y >= 0x100 )){
			++mClocks;
		}
	} else {
		++mClocks;
	}
	address += Y;

	return address;
}
//-----------------------------------------------------------------------------

/**

NB: An original 6502 has does not correctly fetch the target address if the indirect vector falls on a page 
    boundary (e.g. $xxFF where xx is any value from $00 to $FF). In this case fetches the LSB from $xxFF as 
	expected but takes the MSB from $xx00. This is fixed in some later chips like the 65SC02 so for 
	compatibility always ensure the indirect vector is not at the end of the page.
*/
Word CPU6502::AddrModeInd(void)
{
	Word address = ReadWord(PC); mClocks += 2;			// read indirect address
	if((address & 0x00ff) == 0xff){						// check if we have to emulate the bug in early 6502s
		Byte lowByte 	= ReadByte(address);
		Byte hiByte		= ReadByte(address & 0xff00);	// <- Bug! hi byte is wrong
		address = (hiByte << 8 ) + lowByte;
	} else {
		address = ReadWord(address); mClocks += 2;		// read target address
	}

	return address;
}
//-----------------------------------------------------------------------------

/**

*/
Word CPU6502::AddrModeIndX(void)
{
	Word address = static_cast<Word>((GetByte() + X) % 256); ++mClocks;		// read zero page address and add Index X (with ZP wrap around)
	address = ReadWord(address); mClocks +=2;								// read target address from zero page table

	return address;
}
//-----------------------------------------------------------------------------

/**

*/
Word CPU6502::AddrModeIndY(ACCESS_TYPE aType)
{
	Word address = ReadWord(GetByte()); mClocks +=2;						// read target address from zero page and add Y-register
	if(TYPE_READ == aType){
		if((Y > 0) && ((address & 0xff)+Y >= 0x100)){						// if a page break occurrs use one extra clock
			++mClocks;
		}
	} else {
		++mClocks;
	}
	address += Y;

	return address;
}
//-----------------------------------------------------------------------------

/**

*/
Word CPU6502::AddrModeZp(void)
{
	Word address = GetByte();

	return address;
}
//-----------------------------------------------------------------------------

/**

*/
Word CPU6502::AddrModeZpX(void)
{
	Word address = (GetByte() + X) % 256;
	++mClocks;
	return address;
}
//-----------------------------------------------------------------------------

/**

*/
Word CPU6502::AddrModeZpY(void)
{
	Word address = (GetByte() + Y) % 256;
	++mClocks;
	return address;
}
//-----------------------------------------------------------------------------

/**

*/
Word CPU6502::AddrModeRel(void)
{
	Word address = PC;
	return address;
}
//-----------------------------------------------------------------------------

/**

*/
Word CPU6502::ReadWord(Word aAddress)
{
	// 6502 is little endian
	Word data = mMem[aAddress];
	++aAddress;
	data |= (mMem[aAddress] << 8);

	return data;
}
//-----------------------------------------------------------------------------

/**

*/
void CPU6502::SetBit(Byte& aByte, Byte const aNum)
{
	aByte |= (0x01 << aNum);
}
//-----------------------------------------------------------------------------

/**
	This method clears one bit in a byte

	\param [inout]	aByte	Byte that is to b modified.
	\param [in]		aNum	number of bit to be cleard [0:7]
*/
void CPU6502::ClearBit(Byte& aByte, Byte const aNum)
{
	aByte &= ~(0x01 << aNum);
}
//-----------------------------------------------------------------------------

/**

*/
void CPU6502::AdcDoAdd(Word const aVal)
{
	Word tmpA 		= A;
	if((SR & MSK_SR_D) == 0){						// are we in binary mode?
		AdcDoBinAdd(tmpA, aVal);
	} else {										// we are in decimal mode
		AdcDoBcdAdd(tmpA, aVal);
	}
}
//-----------------------------------------------------------------------------

/**

*/
void CPU6502::AdcDoBinAdd(Word const aTmpA, Word aImValue)
{
	/*
	if((SR & MSK_SR_C) != 0){
		++aImValue;								// add one if Carry Flag is set
	}
	*/
	A	= (Byte)((A+aImValue) & 0x00ff);
	if((SR & MSK_SR_C) != 0){
		++A;									// add one if Carry Flag is set
	}
	AdcSetBinStatus(aTmpA, aImValue);
}
//-----------------------------------------------------------------------------

/**

*/
void CPU6502::AdcDoBcdAdd(Word const aTmpA, Word const aImValue)
{
	Word binA		= ((A & 0xf0) >> 4) * 10 +(A & 0x0f);
	Word binImVal	= ((aImValue & 0x00f0) >> 4) * 10 +(aImValue & 0x000f);

	if((SR & MSK_SR_C) != 0){
		++binImVal;								// add one if Carry Flag is set
	}
	Byte res = binA+binImVal;
	A	= (((res/10)%10)<<4) + (res%10);
	AdcSetBcdStatus(res);
}
//-----------------------------------------------------------------------------

/**

*/
void CPU6502::DoSbc(Word const aVal)
{
	Word tmpA 		= A;
	Byte iVal		= ~aVal;

//	if(SR & MSK_SR_C){
//		++iVal;
//	}
//	ClearBit(SR, NUM_BIT_SR_C);
	if((SR & MSK_SR_D) == 0){						// are we in binary mode?
		AdcDoBinAdd(tmpA, iVal);
	} else {										// we are in decimal mode
		AdcDoBcdAdd(tmpA, iVal);
	}
/*
	if((SR & MSK_SR_D) == 0){						// are we in binary mode?
		DoBinSbc(tmpA, aVal);
	} else {										// we are in decimal mode
		DoBcdSbc(tmpA, aVal);
	}
*/
}
//-----------------------------------------------------------------------------

/**

*/
void CPU6502::DoBinSbc(Word const aTmpA, Word aImValue)
{
	if((SR & MSK_SR_C) == 0){
		++aImValue;								// subtract one more if Carry Flag is clear
	}
	A	= (Byte)((A-aImValue) & 0x00ff);
	SbcSetBinStatus(aTmpA, aImValue);
}
//-----------------------------------------------------------------------------

/**

*/
void CPU6502::DoBcdSbc(Word const aTmpA, Word const aImValue)
{
	//SbcSetBcdStatus(aTmpA, aImValue);
}
//-----------------------------------------------------------------------------

/**

*/
void CPU6502::DoAsl(Word const aAddress, Byte aValue)
{
	if(aValue & 0x80){
		SetBit(SR, NUM_BIT_SR_C);
	} else {
		ClearBit(SR, NUM_BIT_SR_C);
	}
	aValue = aValue << 1;
	++mClocks;
	WriteByte(aAddress, aValue);
	SetStatus_N_Z(aValue);
}
//-----------------------------------------------------------------------------

/**

*/
void CPU6502::BranchOnFlagClear(Byte const aFlag)
{
	signed char value	= GetByte();									// GetByte increments PC. PC nowpoints one byte behind this command
	Word 		address = AddrModeRel();

	if((GetSR() & aFlag)^aFlag){
		address = (unsigned short)((signed short)PC + value);
		++mClocks;
	}
	PC = address;
}
//-----------------------------------------------------------------------------

/**

*/
void CPU6502::BranchOnFlagSet(Byte const aFlag)
{
	signed char value	= GetByte();									// GetByte increments PC. PC nowpoints one byte behind this command
	Word 		address = AddrModeRel();

	if(GetSR() & aFlag){
		address = (unsigned short)((signed short)PC + value);
		++mClocks;
	}
	PC = address;
}
//-----------------------------------------------------------------------------

/**

*/
void CPU6502::DoBitTest(Byte const aValue)
{
	bool result = aValue & A;

	if(result){
		ClearBit(SR, NUM_BIT_SR_Z);
	} else {
		SetBit(SR, NUM_BIT_SR_Z);
	}

	if(aValue & MSK_SR_N){
		SetBit(SR, NUM_BIT_SR_N);
	} else {
		ClearBit(SR, NUM_BIT_SR_N);
	}

	if(aValue & MSK_SR_V){
		SetBit(SR, NUM_BIT_SR_V);
	} else {
		ClearBit(SR, NUM_BIT_SR_V);
	}
}
//-----------------------------------------------------------------------------

/**

*/
void CPU6502::DoCompare(unsigned char const aReg, unsigned char const aValue)
{
	if(aReg == aValue){
		SetBit(SR, NUM_BIT_SR_C);
		SetBit(SR, NUM_BIT_SR_Z);
		ClearBit(SR, NUM_BIT_SR_N);
	} else if(aReg >= aValue){
		SetBit(SR, NUM_BIT_SR_C);
		ClearBit(SR, NUM_BIT_SR_Z);
		ClearBit(SR, NUM_BIT_SR_N);
	} else {
		SetBit(SR, NUM_BIT_SR_N);
		ClearBit(SR, NUM_BIT_SR_C);
		ClearBit(SR, NUM_BIT_SR_Z);
	}
}
//-----------------------------------------------------------------------------

/**

*/
void CPU6502::DoDec(Word const aAddress)
{
	Byte value = ReadByte(aAddress);
	--value, ++mClocks;
	WriteByte(aAddress, value);
	SetStatus_N_Z(value);
}
//-----------------------------------------------------------------------------

/**

*/
void CPU6502::DoInc(Word const aAddress)
{
	Byte value = ReadByte(aAddress);
	++value, ++mClocks;
	WriteByte(aAddress, value);
	SetStatus_N_Z(value);
}
//-----------------------------------------------------------------------------
	
/**

*/
void CPU6502::DoEor(Byte const aValue)
{
	A ^= aValue;
	SetStatus_N_Z(A);
}
//-----------------------------------------------------------------------------

/**

*/
void CPU6502::DoLsr(Word const aAddress)
{
	Byte value 	= ReadByte(aAddress);
	
	if(value & 0x01){				// bit 0 will end up in C-flag so check it
		SetBit(SR, NUM_BIT_SR_C);
	} else {
		ClearBit(SR, NUM_BIT_SR_C);
	}
	value = (value >> 1); ++mClocks;
	if(0 == value){
		SetBit(SR, NUM_BIT_SR_Z);
	} else {
		ClearBit(SR, NUM_BIT_SR_Z);
	}
	ClearBit(SR, NUM_BIT_SR_N);
	WriteByte(aAddress, value);
}
//-----------------------------------------------------------------------------

/**

*/
void CPU6502::DoRol(Word const aAddress)
{
	Byte value 	= ReadByte(aAddress);
	bool tmpC	= ((value & 0x80) > 0);				// bit 7 will end up in C-flag so check it

	value = value << 1;
	++mClocks;

	if(SR & MSK_SR_C){
		SetBit(value, 0);
	} else {
		ClearBit(value, 0);
	}

	if(tmpC){
		SetBit(SR, NUM_BIT_SR_C);
	} else {
		ClearBit(SR, NUM_BIT_SR_C);
	}
	SetStatus_N_Z(value);
	WriteByte(aAddress, value);
}
//-----------------------------------------------------------------------------


/**

*/
void CPU6502::DoRor(Word const aAddress)
{
	Byte value 	= ReadByte(aAddress);
	bool tmpC	= ((value & 0x01) > 0);				// bit 7 will end up in C-flag so check it

	value = value >> 1;
	++mClocks;

	if(SR & MSK_SR_C){
		SetBit(value, 7);
	} else {
		ClearBit(value, 7);
	}

	if(tmpC){
		SetBit(SR, NUM_BIT_SR_C);
	} else {
		ClearBit(SR, NUM_BIT_SR_C);
	}
	SetStatus_N_Z(value);
	WriteByte(aAddress, value);
}
//-----------------------------------------------------------------------------

/**

*/
void CPU6502::PrintDebugStatus(void)
{
	fprintf(stderr, "PC:%04X: SP:0x%02X A=%02X, X=%02X, Y=%02X, (N=%d,V=%d,D=%d,I=%d,Z=%d,C=%d) CLK:%d\n",
	PC, SP, A, X, Y, (SR&MSK_SR_N)>0, (SR&MSK_SR_V)>0, (SR&MSK_SR_D)>0, (SR&MSK_SR_I)>0, (SR&MSK_SR_Z)>0, (SR&MSK_SR_C)>0, mClocks);
}
//-----------------------------------------------------------------------------
