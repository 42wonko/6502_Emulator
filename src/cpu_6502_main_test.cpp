#include <iostream>
#include "cpu_6502_main_test.h"

CPU6502Test::CPU6502Test()
: cpu(mem)
{
	mem[0xfffc]	= 0x42;
	mem[0xfffd]	= 0x42;
	cpu.Reset();
}

CPU6502Test::~CPU6502Test()
{
}

void CPU6502Test::VerifyRegisters(CPU6502& aCpu, unsigned int const aClocks, Byte const aRegA, Byte const aRegX, Byte const aRegY, Word const aRegPC, Byte const aRegSR)
{
	EXPECT_EQ(aCpu.GetClocks(),	aClocks);
	EXPECT_EQ(aCpu.GetA(),		aRegA);
	EXPECT_EQ(aCpu.GetX(),		aRegX);
	EXPECT_EQ(aCpu.GetY(),		aRegY);
	EXPECT_EQ(aCpu.GetPC(), 	aRegPC);
	EXPECT_EQ(aCpu.GetSR(),		aRegSR);

}

void CPU6502Test::SetRegisters(CPU6502& aCpu, Byte aRegA, Byte aRegX, Byte aRegY)
{
	aCpu.SetA(aRegA);
	aCpu.SetX(aRegX);
	aCpu.SetY(aRegY);
}

TEST_F(CPU6502Test, Nop)
{
	mem[0x4242]	= CPU6502::INS_NOP_IMP;

	cpu.SetSR(0x00);
	Byte SPc = cpu.GetSP();
	SetRegisters(cpu, 0x01, 0x02, 0x03);		// preset A=1, X=2, Y=3
	int clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x01, 0x02, 0x03, 0x4243, 0x00);
	EXPECT_EQ(SPc, cpu.GetSP());

	cpu.Reset();
	cpu.SetSR(0xff);
	SPc = cpu.GetSP();
	SetRegisters(cpu, 0x01, 0x02, 0x03);		// preset A=1, X=2, Y=3
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x01, 0x02, 0x03, 0x4243, 0xff);
	EXPECT_EQ(SPc, cpu.GetSP());
}

