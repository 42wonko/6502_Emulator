#include "cpu_6502_memory_test.h"

//-----------------------------------------------------------------------------
//	LDA
//-----------------------------------------------------------------------------
TEST_F(CPU6502MemoryTest, LdaImmidiate)
{
	mem[0x4242]	= CPU6502::INS_LDA_IM;
	mem[0x4243]	= 0x55;

	SetRegisters(cpu, 0, 0, 0);		// preset A=0, X=0, Y=0
	int clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x55, 0, 0, 0x4244, CPU6502::MSK_SR_NONE);
}

TEST_F(CPU6502MemoryTest, LdaImmidiateNeg)
{
	mem[0x4242]	= CPU6502::INS_LDA_IM;
	mem[0x4243]	= 0x84;

	SetRegisters(cpu, 0, 0, 0);		// preset A=0, X=0, Y=0
	int clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x84, 0, 0, 0x4244, CPU6502::MSK_SR_N);
}

TEST_F(CPU6502MemoryTest, LdaImmidiateZero)
{
	mem[0x4242]	= CPU6502::INS_LDA_IM;
	mem[0x4243]	= 0x00;

	SetRegisters(cpu, 0, 0, 0);		// preset A=0, X=0, Y=0
	int clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0, 0, 0x4244, CPU6502::MSK_SR_Z);
}

TEST_F(CPU6502MemoryTest, LdaAbs)
{
	mem[0x1234]	= 0x55;
	mem[0x4242]	= CPU6502::INS_LDA_ABS;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	SetRegisters(cpu, 0, 0, 0);		// preset A=0, X=0, Y=0
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x55, 0, 0, 0x4245, CPU6502::MSK_SR_NONE);
}

TEST_F(CPU6502MemoryTest, LdaAbsNeg)
{
	mem[0x1234]	= 0x84;
	mem[0x4242]	= CPU6502::INS_LDA_ABS;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	SetRegisters(cpu, 0, 0, 0);		// preset A=0, X=0, Y=0
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x84, 0, 0, 0x4245, CPU6502::MSK_SR_N);
}

TEST_F(CPU6502MemoryTest, LdaAbsZero)
{
	mem[0x1234]	= 0x00;
	mem[0x4242]	= CPU6502::INS_LDA_ABS;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	SetRegisters(cpu, 0, 0, 0);		// preset A=0, X=0, Y=0
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0, 0, 0x4245, CPU6502::MSK_SR_Z);
}

TEST_F(CPU6502MemoryTest, LdaAbsX)
{
	mem[0x1235]	= 0x55;
	mem[0x4242]	= CPU6502::INS_LDA_ABS_X;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	SetRegisters(cpu, 0, 1, 0);		// preset A=0, X=1, Y=0
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x55, 0x01, 0, 0x4245, CPU6502::MSK_SR_NONE);
}

TEST_F(CPU6502MemoryTest, LdaAbsXPB)
{
	mem[0x1100]	= 0x55;
	mem[0x4242]	= CPU6502::INS_LDA_ABS_X;
	mem[0x4243]	= 0xff;
	mem[0x4244]	= 0x10;

	SetRegisters(cpu, 0, 1, 0);		// preset A=0, X=1, Y=0
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 5, 0x55, 0x01, 0, 0x4245, CPU6502::MSK_SR_NONE);
}

TEST_F(CPU6502MemoryTest, LdaAbsXNeg)
{
	mem[0x1235]	= 0x84;
	mem[0x4242]	= CPU6502::INS_LDA_ABS_X;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	SetRegisters(cpu, 0, 1, 0);		// preset A=0, X=1, Y=0
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x84, 0x01, 0, 0x4245, CPU6502::MSK_SR_N);
}

TEST_F(CPU6502MemoryTest, LdaAbsXZero)
{
	mem[0x1235]	= 0x00;
	mem[0x4242]	= CPU6502::INS_LDA_ABS_X;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	SetRegisters(cpu, 0, 1, 0);		// preset A=0, X=1, Y=0
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x01, 0, 0x4245, CPU6502::MSK_SR_Z);
}

TEST_F(CPU6502MemoryTest, LdaAbsY)
{
	mem[0x1235]	= 0x55;
	mem[0x4242]	= CPU6502::INS_LDA_ABS_Y;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	SetRegisters(cpu, 0, 0, 1);		// preset A=0, X=0, Y=1
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x55, 0x00, 0x01, 0x4245, CPU6502::MSK_SR_NONE);
}

TEST_F(CPU6502MemoryTest, LdaAbsYPB)
{
	mem[0x1100]	= 0x55;
	mem[0x4242]	= CPU6502::INS_LDA_ABS_Y;
	mem[0x4243]	= 0xff;
	mem[0x4244]	= 0x10;

	SetRegisters(cpu, 0, 0, 1);		// preset A=0, X=0, Y=1
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 5, 0x55, 0x00, 0x01, 0x4245, CPU6502::MSK_SR_NONE);
}

TEST_F(CPU6502MemoryTest, LdaAbsYNeg)
{
	mem[0x1235]	= 0x84;
	mem[0x4242]	= CPU6502::INS_LDA_ABS_Y;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	SetRegisters(cpu, 0, 0, 1);		// preset A=0, X=0, Y=1
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x84, 0x00, 0x01, 0x4245, CPU6502::MSK_SR_N);
}

TEST_F(CPU6502MemoryTest, LdaAbsYZero)
{
	mem[0x1235]	= 0x00;
	mem[0x4242]	= CPU6502::INS_LDA_ABS_Y;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	SetRegisters(cpu, 0, 0, 1);		// preset A=0, X=0, Y=1
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x00, 0x01, 0x4245, CPU6502::MSK_SR_Z);
}

TEST_F(CPU6502MemoryTest, LdaIndX)
{
	mem[0x0042]	= 0x34;
	mem[0x0043]	= 0x12;
	mem[0x1234]	= 0x55;
	mem[0x4242]	= CPU6502::INS_LDA_IND_X;
	mem[0x4243]	= 0x40;

	SetRegisters(cpu, 0, 2, 0);		// preset A=0, X=2, Y=0
	cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x55, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_NONE);
}

TEST_F(CPU6502MemoryTest, LdaIndXNeg)
{
	mem[0x0042]	= 0x34;
	mem[0x0043]	= 0x12;
	mem[0x1234]	= 0x84;
	mem[0x4242]	= CPU6502::INS_LDA_IND_X;
	mem[0x4243]	= 0x40;

	SetRegisters(cpu, 0, 2, 0);		// preset A=0, X=2, Y=0
	cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x84, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_N);
}

TEST_F(CPU6502MemoryTest, LdaIndXZero)
{
	mem[0x0042]	= 0x34;
	mem[0x0043]	= 0x12;
	mem[0x1234]	= 0x00;
	mem[0x4242]	= CPU6502::INS_LDA_IND_X;
	mem[0x4243]	= 0x40;

	cpu.SetX(2);
	cpu.Run(6);
	Byte flags = CPU6502::MSK_SR_Z;

	EXPECT_EQ(cpu.GetClocks(), 6);
	EXPECT_EQ(cpu.GetA(), 0x00);
	EXPECT_EQ(cpu.GetX(), 0x02);
	EXPECT_EQ(cpu.GetPC(), 0x4244);
	EXPECT_EQ(cpu.GetSR(), flags);
}

TEST_F(CPU6502MemoryTest, LdaIndY)
{
	mem[0x0040] = 0x34;
	mem[0x0041] = 0x12;
	mem[0x1236]	= 0x55;
	mem[0x4242]	= CPU6502::INS_LDA_IND_Y;
	mem[0x4243]	= 0x40;

	cpu.SetY(2);
	cpu.Run(5);

	EXPECT_EQ(cpu.GetClocks(), 5);
	EXPECT_EQ(cpu.GetA(), 0x55);
	EXPECT_EQ(cpu.GetY(), 0x02);
	EXPECT_EQ(cpu.GetPC(), 0x4244);
	EXPECT_EQ(cpu.GetSR(), 0x00);
}

TEST_F(CPU6502MemoryTest, LdaIndYPB)
{
	mem[0x0040] = 0xff;
	mem[0x0041] = 0x10;
	mem[0x1101]	= 0x55;
	mem[0x4242]	= CPU6502::INS_LDA_IND_Y;
	mem[0x4243]	= 0x40;

	cpu.SetY(2);
	cpu.Run(5);

	EXPECT_EQ(cpu.GetClocks(), 6);
	EXPECT_EQ(cpu.GetA(), 0x55);
	EXPECT_EQ(cpu.GetY(), 0x02);
	EXPECT_EQ(cpu.GetPC(), 0x4244);
	EXPECT_EQ(cpu.GetSR(), 0x00);
}

TEST_F(CPU6502MemoryTest, LdaIndYNeg)
{
	mem[0x0040] = 0x34;
	mem[0x0041] = 0x12;
	mem[0x1236]	= 0x84;
	mem[0x4242]	= CPU6502::INS_LDA_IND_Y;
	mem[0x4243]	= 0x40;

	cpu.SetY(2);
	cpu.Run(5);
	Byte flags = CPU6502::MSK_SR_N;

	EXPECT_EQ(cpu.GetClocks(), 5);
	EXPECT_EQ(cpu.GetA(), 0x84);
	EXPECT_EQ(cpu.GetY(), 0x02);
	EXPECT_EQ(cpu.GetPC(), 0x4244);
	EXPECT_EQ(cpu.GetSR(), flags);
}

TEST_F(CPU6502MemoryTest, LdaIndYZero)
{
	mem[0x0040] = 0x34;
	mem[0x0041] = 0x12;
	mem[0x1236]	= 0x00;
	mem[0x4242]	= CPU6502::INS_LDA_IND_Y;
	mem[0x4243]	= 0x40;

	cpu.SetY(2);
	cpu.Run(5);
	Byte flags = CPU6502::MSK_SR_Z;

	EXPECT_EQ(cpu.GetClocks(), 5);
	EXPECT_EQ(cpu.GetA(), 0x00);
	EXPECT_EQ(cpu.GetY(), 0x02);
	EXPECT_EQ(cpu.GetPC(), 0x4244);
	EXPECT_EQ(cpu.GetSR(), flags);
}

TEST_F(CPU6502MemoryTest, LdaZp)
{
	mem[0x0040] = 0x55;
	mem[0x4242]	= CPU6502::INS_LDA_ZP;
	mem[0x4243]	= 0x40;

	cpu.Run(3);

	EXPECT_EQ(cpu.GetClocks(), 3);
	EXPECT_EQ(cpu.GetA(), 0x55);
	EXPECT_EQ(cpu.GetPC(), 0x4244);
	EXPECT_EQ(cpu.GetSR(), 0x00);
}

TEST_F(CPU6502MemoryTest, LdaZpNeg)
{
	mem[0x0040] = 0x84;
	mem[0x4242]	= CPU6502::INS_LDA_ZP;
	mem[0x4243]	= 0x40;

	cpu.Run(3);
	Byte flags = CPU6502::MSK_SR_N;

	EXPECT_EQ(cpu.GetClocks(), 3);
	EXPECT_EQ(cpu.GetA(), 0x84);
	EXPECT_EQ(cpu.GetPC(), 0x4244);
	EXPECT_EQ(cpu.GetSR(), flags);
}

TEST_F(CPU6502MemoryTest, LdaZpZero)
{
	mem[0x0040] = 0x00;
	mem[0x4242]	= CPU6502::INS_LDA_ZP;
	mem[0x4243]	= 0x40;

	cpu.Run(3);
	Byte flags = CPU6502::MSK_SR_Z;

	EXPECT_EQ(cpu.GetClocks(), 3);
	EXPECT_EQ(cpu.GetA(), 0x00);
	EXPECT_EQ(cpu.GetPC(), 0x4244);
	EXPECT_EQ(cpu.GetSR(), flags);
}

TEST_F(CPU6502MemoryTest, LdaZpX)
{
	mem[0x0042] = 0x55;
	mem[0x4242]	= CPU6502::INS_LDA_ZPX;
	mem[0x4243]	= 0x40;

	cpu.SetX(2);
	cpu.Run(4);

	EXPECT_EQ(cpu.GetClocks(), 4);
	EXPECT_EQ(cpu.GetA(), 0x55);
	EXPECT_EQ(cpu.GetX(), 0x02);
	EXPECT_EQ(cpu.GetPC(), 0x4244);
	EXPECT_EQ(cpu.GetSR(), 0x00);
}

TEST_F(CPU6502MemoryTest, LdaZpXNeg)
{
	mem[0x0042] = 0x84;
	mem[0x4242]	= CPU6502::INS_LDA_ZPX;
	mem[0x4243]	= 0x40;

	cpu.SetX(2);
	cpu.Run(4);
	Byte flags = CPU6502::MSK_SR_N;

	EXPECT_EQ(cpu.GetClocks(), 4);
	EXPECT_EQ(cpu.GetA(), 0x84);
	EXPECT_EQ(cpu.GetX(), 0x02);
	EXPECT_EQ(cpu.GetPC(), 0x4244);
	EXPECT_EQ(cpu.GetSR(), flags);
}

TEST_F(CPU6502MemoryTest, LdaZpXZero)
{
	mem[0x0042] = 0x00;
	mem[0x4242]	= CPU6502::INS_LDA_ZPX;
	mem[0x4243]	= 0x40;

	cpu.SetX(2);
	cpu.Run(4);
	Byte flags = CPU6502::MSK_SR_Z;

	EXPECT_EQ(cpu.GetClocks(), 4);
	EXPECT_EQ(cpu.GetA(), 0x00);
	EXPECT_EQ(cpu.GetX(), 0x02);
	EXPECT_EQ(cpu.GetPC(), 0x4244);
	EXPECT_EQ(cpu.GetSR(), flags);
}

//-----------------------------------------------------------------------------
//	LDX
//-----------------------------------------------------------------------------
TEST_F(CPU6502MemoryTest, LdxIm)
{
	mem[0x4242] = CPU6502::INS_LDX_IM;
	mem[0x4243]	= 0x55;

	cpu.Run(2);
	EXPECT_EQ(cpu.GetClocks(), 2);
	EXPECT_EQ(cpu.GetX(), 0x55);
	EXPECT_EQ(cpu.GetPC(), 0x4244);
	EXPECT_EQ(cpu.GetSR(), 0x00);
}

TEST_F(CPU6502MemoryTest, LdxImNeg)
{
	mem[0x4242] = CPU6502::INS_LDX_IM;
	mem[0x4243]	= 0x84;
	cpu.Run(2);
	Byte flags = CPU6502::MSK_SR_N;
	EXPECT_EQ(cpu.GetClocks(), 2);
	EXPECT_EQ(cpu.GetX(), 0x84);
	EXPECT_EQ(cpu.GetPC(), 0x4244);
	EXPECT_EQ(cpu.GetSR(), flags);
}

TEST_F(CPU6502MemoryTest, LdxImZero)
{
	mem[0x4242] = CPU6502::INS_LDX_IM;
	mem[0x4243]	= 0x00;
	cpu.Run(2);
	Byte flags = CPU6502::MSK_SR_Z;
	EXPECT_EQ(cpu.GetClocks(), 2);
	EXPECT_EQ(cpu.GetX(), 0x00);
	EXPECT_EQ(cpu.GetPC(), 0x4244);
	EXPECT_EQ(cpu.GetSR(), flags);
}

TEST_F(CPU6502MemoryTest, LdxAbs)
{
	mem[0x1234]	= 0x55;
	mem[0x4242] = CPU6502::INS_LDX_ABS;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	cpu.Run(4);
	EXPECT_EQ(cpu.GetClocks(), 4);
	EXPECT_EQ(cpu.GetX(), 0x55);
	EXPECT_EQ(cpu.GetPC(), 0x4245);
	EXPECT_EQ(cpu.GetSR(), 0x00);
}

TEST_F(CPU6502MemoryTest, LdxAbsNeg)
{
	mem[0x1234]	= 0x84;
	mem[0x4242] = CPU6502::INS_LDX_ABS;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	cpu.Run(4);
	Byte flags = CPU6502::MSK_SR_N;
	EXPECT_EQ(cpu.GetClocks(), 4);
	EXPECT_EQ(cpu.GetX(), 0x84);
	EXPECT_EQ(cpu.GetPC(), 0x4245);
	EXPECT_EQ(cpu.GetSR(), flags);
}

TEST_F(CPU6502MemoryTest, LdxAbsZero)
{
	mem[0x1234]	= 0x00;
	mem[0x4242] = CPU6502::INS_LDX_ABS;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	cpu.Run(4);
	Byte flags = CPU6502::MSK_SR_Z;
	EXPECT_EQ(cpu.GetClocks(), 4);
	EXPECT_EQ(cpu.GetX(), 0x00);
	EXPECT_EQ(cpu.GetPC(), 0x4245);
	EXPECT_EQ(cpu.GetSR(), flags);
}

TEST_F(CPU6502MemoryTest, LdxZp)
{
	mem[0x0040] = 0x55;
	mem[0x4242]	= CPU6502::INS_LDX_ZP;
	mem[0x4243]	= 0x40;

	cpu.Run(3);

	EXPECT_EQ(cpu.GetClocks(), 3);
	EXPECT_EQ(cpu.GetX(), 0x55);
	EXPECT_EQ(cpu.GetPC(), 0x4244);
	EXPECT_EQ(cpu.GetSR(), 0x00);
}

TEST_F(CPU6502MemoryTest, LdxZpNeg)
{
	mem[0x0040] = 0x84;
	mem[0x4242]	= CPU6502::INS_LDX_ZP;
	mem[0x4243]	= 0x40;

	cpu.Run(3);
	Byte flags = CPU6502::MSK_SR_N;

	EXPECT_EQ(cpu.GetClocks(), 3);
	EXPECT_EQ(cpu.GetX(), 0x84);
	EXPECT_EQ(cpu.GetPC(), 0x4244);
	EXPECT_EQ(cpu.GetSR(), flags);
}

TEST_F(CPU6502MemoryTest, LdxZpZero)
{
	mem[0x0040] = 0x00;
	mem[0x4242]	= CPU6502::INS_LDX_ZP;
	mem[0x4243]	= 0x40;

	cpu.Run(3);
	Byte flags = CPU6502::MSK_SR_Z;

	EXPECT_EQ(cpu.GetClocks(), 3);
	EXPECT_EQ(cpu.GetX(), 0x00);
	EXPECT_EQ(cpu.GetPC(), 0x4244);
	EXPECT_EQ(cpu.GetSR(), flags);
}

TEST_F(CPU6502MemoryTest, LdxZpY)
{
	mem[0x0041] = 0x55;
	mem[0x4242]	= CPU6502::INS_LDX_ZPY;
	mem[0x4243]	= 0x40;

	cpu.SetY(1);
	cpu.Run(4);

	EXPECT_EQ(cpu.GetClocks(), 4);
	EXPECT_EQ(cpu.GetX(), 0x55);
	EXPECT_EQ(cpu.GetY(), 0x01);
	EXPECT_EQ(cpu.GetPC(), 0x4244);
	EXPECT_EQ(cpu.GetSR(), 0x00);
}

TEST_F(CPU6502MemoryTest, LdxZpYNeg)
{
	mem[0x0041] = 0x84;
	mem[0x4242]	= CPU6502::INS_LDX_ZPY;
	mem[0x4243]	= 0x40;

	cpu.SetY(1);
	cpu.Run(4);
	Byte flags = CPU6502::MSK_SR_N;

	EXPECT_EQ(cpu.GetClocks(), 4);
	EXPECT_EQ(cpu.GetX(), 0x84);
	EXPECT_EQ(cpu.GetY(), 0x01);
	EXPECT_EQ(cpu.GetPC(), 0x4244);
	EXPECT_EQ(cpu.GetSR(), flags);
}

TEST_F(CPU6502MemoryTest, LdxZpYZero)
{
	mem[0x0041] = 0x00;
	mem[0x4242]	= CPU6502::INS_LDX_ZPY;
	mem[0x4243]	= 0x40;

	cpu.SetY(1);
	cpu.Run(4);
	Byte flags = CPU6502::MSK_SR_Z;

	EXPECT_EQ(cpu.GetClocks(), 4);
	EXPECT_EQ(cpu.GetX(), 0x00);
	EXPECT_EQ(cpu.GetY(), 0x01);
	EXPECT_EQ(cpu.GetPC(), 0x4244);
	EXPECT_EQ(cpu.GetSR(), flags);
}

TEST_F(CPU6502MemoryTest, LdxAbsY)
{
	mem[0x1235]	= 0x55;
	mem[0x4242] = CPU6502::INS_LDX_ABS_Y;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	cpu.SetY(1);
	cpu.Run(4);
	EXPECT_EQ(cpu.GetClocks(), 4);
	EXPECT_EQ(cpu.GetX(), 0x55);
	EXPECT_EQ(cpu.GetPC(), 0x4245);
	EXPECT_EQ(cpu.GetSR(), 0x00);
}

TEST_F(CPU6502MemoryTest, LdxAbsYPB)
{
	mem[0x1100]	= 0x55;
	mem[0x4242] = CPU6502::INS_LDX_ABS_Y;
	mem[0x4243]	= 0xff;
	mem[0x4244]	= 0x10;

	cpu.SetY(1);
	cpu.Run(4);
	EXPECT_EQ(cpu.GetClocks(), 5);
	EXPECT_EQ(cpu.GetX(), 0x55);
	EXPECT_EQ(cpu.GetPC(), 0x4245);
	EXPECT_EQ(cpu.GetSR(), 0x00);
}

TEST_F(CPU6502MemoryTest, LdxAbsYNeg)
{
	mem[0x1235]	= 0x84;
	mem[0x4242] = CPU6502::INS_LDX_ABS_Y;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	cpu.SetY(1);
	cpu.Run(4);
	Byte flags = CPU6502::MSK_SR_N;
	EXPECT_EQ(cpu.GetClocks(), 4);
	EXPECT_EQ(cpu.GetX(), 0x84);
	EXPECT_EQ(cpu.GetPC(), 0x4245);
	EXPECT_EQ(cpu.GetSR(), flags);
}

TEST_F(CPU6502MemoryTest, LdxAbsYZero)
{
	mem[0x1235]	= 0x00;
	mem[0x4242] = CPU6502::INS_LDX_ABS_Y;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	cpu.SetY(1);
	cpu.Run(4);
	Byte flags = CPU6502::MSK_SR_Z;
	EXPECT_EQ(cpu.GetClocks(), 4);
	EXPECT_EQ(cpu.GetX(), 0x00);
	EXPECT_EQ(cpu.GetPC(), 0x4245);
	EXPECT_EQ(cpu.GetSR(), flags);
}

//-----------------------------------------------------------------------------
//	LDY
//-----------------------------------------------------------------------------
TEST_F(CPU6502MemoryTest, LdyIm)
{
	mem[0x4242] = CPU6502::INS_LDY_IM;
	mem[0x4243]	= 0x55;

	cpu.Run(2);
	EXPECT_EQ(cpu.GetClocks(), 2);
	EXPECT_EQ(cpu.GetY(), 0x55);
	EXPECT_EQ(cpu.GetPC(), 0x4244);
	EXPECT_EQ(cpu.GetSR(), 0x00);
}

TEST_F(CPU6502MemoryTest, LdyImNeg)
{
	mem[0x4242] = CPU6502::INS_LDY_IM;
	mem[0x4243]	= 0x84;
	cpu.Run(2);
	Byte flags = CPU6502::MSK_SR_N;
	EXPECT_EQ(cpu.GetClocks(), 2);
	EXPECT_EQ(cpu.GetY(), 0x84);
	EXPECT_EQ(cpu.GetPC(), 0x4244);
	EXPECT_EQ(cpu.GetSR(), flags);
}

TEST_F(CPU6502MemoryTest, LdyImZero)
{
	mem[0x4242] = CPU6502::INS_LDY_IM;
	mem[0x4243]	= 0x00;
	cpu.Run(2);
	Byte flags = CPU6502::MSK_SR_Z;
	EXPECT_EQ(cpu.GetClocks(), 2);
	EXPECT_EQ(cpu.GetY(), 0x00);
	EXPECT_EQ(cpu.GetPC(), 0x4244);
	EXPECT_EQ(cpu.GetSR(), flags);
}

TEST_F(CPU6502MemoryTest, LdyAbs)
{
	mem[0x1234]	= 0x55;
	mem[0x4242] = CPU6502::INS_LDY_ABS;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	cpu.Run(4);
	EXPECT_EQ(cpu.GetClocks(), 4);
	EXPECT_EQ(cpu.GetY(), 0x55);
	EXPECT_EQ(cpu.GetPC(), 0x4245);
	EXPECT_EQ(cpu.GetSR(), 0x00);
}

TEST_F(CPU6502MemoryTest, LdyAbsNeg)
{
	mem[0x1234]	= 0x84;
	mem[0x4242] = CPU6502::INS_LDY_ABS;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	cpu.Run(4);
	Byte flags = CPU6502::MSK_SR_N;
	EXPECT_EQ(cpu.GetClocks(), 4);
	EXPECT_EQ(cpu.GetY(), 0x84);
	EXPECT_EQ(cpu.GetPC(), 0x4245);
	EXPECT_EQ(cpu.GetSR(), flags);
}

TEST_F(CPU6502MemoryTest, LdyAbsZero)
{
	mem[0x1234]	= 0x00;
	mem[0x4242] = CPU6502::INS_LDY_ABS;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	cpu.Run(4);
	Byte flags = CPU6502::MSK_SR_Z;
	EXPECT_EQ(cpu.GetClocks(), 4);
	EXPECT_EQ(cpu.GetY(), 0x00);
	EXPECT_EQ(cpu.GetPC(), 0x4245);
	EXPECT_EQ(cpu.GetSR(), flags);
}

TEST_F(CPU6502MemoryTest, LdyZp)
{
	mem[0x0040] = 0x55;
	mem[0x4242]	= CPU6502::INS_LDY_ZP;
	mem[0x4243]	= 0x40;

	cpu.Run(3);

	EXPECT_EQ(cpu.GetClocks(), 3);
	EXPECT_EQ(cpu.GetY(), 0x55);
	EXPECT_EQ(cpu.GetPC(), 0x4244);
	EXPECT_EQ(cpu.GetSR(), 0x00);
}

TEST_F(CPU6502MemoryTest, LdyZpNeg)
{
	mem[0x0040] = 0x84;
	mem[0x4242]	= CPU6502::INS_LDY_ZP;
	mem[0x4243]	= 0x40;

	cpu.Run(3);
	Byte flags = CPU6502::MSK_SR_N;

	EXPECT_EQ(cpu.GetClocks(), 3);
	EXPECT_EQ(cpu.GetY(), 0x84);
	EXPECT_EQ(cpu.GetPC(), 0x4244);
	EXPECT_EQ(cpu.GetSR(), flags);
}

TEST_F(CPU6502MemoryTest, LdyZpZero)
{
	mem[0x0040] = 0x00;
	mem[0x4242]	= CPU6502::INS_LDY_ZP;
	mem[0x4243]	= 0x40;

	cpu.Run(3);
	Byte flags = CPU6502::MSK_SR_Z;

	EXPECT_EQ(cpu.GetClocks(), 3);
	EXPECT_EQ(cpu.GetY(), 0x00);
	EXPECT_EQ(cpu.GetPC(), 0x4244);
	EXPECT_EQ(cpu.GetSR(), flags);
}

TEST_F(CPU6502MemoryTest, LdyZpX)
{
	mem[0x0041] = 0x55;
	mem[0x4242]	= CPU6502::INS_LDY_ZPX;
	mem[0x4243]	= 0x40;

	cpu.SetX(1);
	cpu.Run(4);

	EXPECT_EQ(cpu.GetClocks(), 4);
	EXPECT_EQ(cpu.GetY(), 0x55);
	EXPECT_EQ(cpu.GetX(), 0x01);
	EXPECT_EQ(cpu.GetPC(), 0x4244);
	EXPECT_EQ(cpu.GetSR(), 0x00);
}

TEST_F(CPU6502MemoryTest, LdyZpXNeg)
{
	mem[0x0041] = 0x84;
	mem[0x4242]	= CPU6502::INS_LDY_ZPX;
	mem[0x4243]	= 0x40;

	cpu.SetX(1);
	cpu.Run(4);
	Byte flags = CPU6502::MSK_SR_N;

	EXPECT_EQ(cpu.GetClocks(), 4);
	EXPECT_EQ(cpu.GetY(), 0x84);
	EXPECT_EQ(cpu.GetX(), 0x01);
	EXPECT_EQ(cpu.GetPC(), 0x4244);
	EXPECT_EQ(cpu.GetSR(), flags);
}

TEST_F(CPU6502MemoryTest, LdyZpXZero)
{
	mem[0x0041] = 0x00;
	mem[0x4242]	= CPU6502::INS_LDY_ZPX;
	mem[0x4243]	= 0x40;

	cpu.SetX(1);
	cpu.Run(4);
	Byte flags = CPU6502::MSK_SR_Z;

	EXPECT_EQ(cpu.GetClocks(), 4);
	EXPECT_EQ(cpu.GetY(), 0x00);
	EXPECT_EQ(cpu.GetX(), 0x01);
	EXPECT_EQ(cpu.GetPC(), 0x4244);
	EXPECT_EQ(cpu.GetSR(), flags);
}

TEST_F(CPU6502MemoryTest, LdyAbsX)
{
	mem[0x1235]	= 0x55;
	mem[0x4242] = CPU6502::INS_LDY_ABS_X;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	cpu.SetX(1);
	cpu.Run(4);
	EXPECT_EQ(cpu.GetClocks(), 4);
	EXPECT_EQ(cpu.GetY(), 0x55);
	EXPECT_EQ(cpu.GetPC(), 0x4245);
	EXPECT_EQ(cpu.GetSR(), 0x00);
}

TEST_F(CPU6502MemoryTest, LdyAbsXPB)
{
	mem[0x1100]	= 0x55;
	mem[0x4242] = CPU6502::INS_LDY_ABS_X;
	mem[0x4243]	= 0xff;
	mem[0x4244]	= 0x10;

	cpu.SetX(1);
	cpu.Run(4);
	EXPECT_EQ(cpu.GetClocks(), 5);
	EXPECT_EQ(cpu.GetY(), 0x55);
	EXPECT_EQ(cpu.GetPC(), 0x4245);
	EXPECT_EQ(cpu.GetSR(), 0x00);
}

TEST_F(CPU6502MemoryTest, LdyAbsXNeg)
{
	mem[0x1235]	= 0x84;
	mem[0x4242] = CPU6502::INS_LDY_ABS_X;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	cpu.SetX(1);
	cpu.Run(4);
	Byte flags = CPU6502::MSK_SR_N;
	EXPECT_EQ(cpu.GetClocks(), 4);
	EXPECT_EQ(cpu.GetY(), 0x84);
	EXPECT_EQ(cpu.GetPC(), 0x4245);
	EXPECT_EQ(cpu.GetSR(), flags);
}

TEST_F(CPU6502MemoryTest, LdyAbsYZero)
{
	mem[0x1235]	= 0x00;
	mem[0x4242] = CPU6502::INS_LDY_ABS_X;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	cpu.SetX(1);
	cpu.Run(4);
	Byte flags = CPU6502::MSK_SR_Z;
	EXPECT_EQ(cpu.GetClocks(), 4);
	EXPECT_EQ(cpu.GetY(), 0x00);
	EXPECT_EQ(cpu.GetPC(), 0x4245);
	EXPECT_EQ(cpu.GetSR(), flags);
}

//-----------------------------------------------------------------------------
//	DEC
//-----------------------------------------------------------------------------
TEST_F(CPU6502MemoryTest, DecAbs)
{
	mem[0x1234]	= 0x02;
	mem[0x4242] = CPU6502::INS_DEC_ABS;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x00, 0x00, 0x00);
	cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_NONE);
	EXPECT_EQ(mem[0x1234], 0x01);

	mem[0x1234]	= 0x1;
	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x00, 0x00);
	cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_Z);
	EXPECT_EQ(mem[0x1234], 0x00);

	mem[0x1234]	= 0x0;
	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x00, 0x00);
	cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_N);
	EXPECT_EQ(mem[0x1234], 0xff);
}

TEST_F(CPU6502MemoryTest, DecZp)
{
	mem[0x0040]	= 0x02;
	mem[0x4242] = CPU6502::INS_DEC_ZP;
	mem[0x4243]	= 0x40;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x00, 0x00, 0x00);
	cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_NONE);
	EXPECT_EQ(mem[0x0040], 0x01);

	mem[0x0040]	= 0x1;
	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x00, 0x00);
	cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_Z);
	EXPECT_EQ(mem[0x0040], 0x00);

	mem[0x0040]	= 0x0;
	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x00, 0x00);
	cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_N);
	EXPECT_EQ(mem[0x0040], 0xff);
}

TEST_F(CPU6502MemoryTest,DecZpX)
{
	mem[0x0042]	= 0x02;
	mem[0x4242] = CPU6502::INS_DEC_ZPX;
	mem[0x4243]	= 0x40;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x00, 0x02, 0x00);
	cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_NONE);
	EXPECT_EQ(mem[0x0042], 0x01);

	mem[0x0042]	= 0x1;
	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x02, 0x00);
	cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_Z);
	EXPECT_EQ(mem[0x0042], 0x00);

	mem[0x0042]	= 0x0;
	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x02, 0x00);
	cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_N);
	EXPECT_EQ(mem[0x0042], 0xff);
}

TEST_F(CPU6502MemoryTest, DecAbsX)
{
	mem[0x1236]	= 0x02;
	mem[0x4242] = CPU6502::INS_DEC_ABS_X;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x00, 0x02, 0x00);
	cpu.Run(7);
	VerifyRegisters(cpu, 7, 0x00, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_NONE);
	EXPECT_EQ(mem[0x1236], 0x01);

	mem[0x1236]	= 0x1;
	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x02, 0x00);
	cpu.Run(7);
	VerifyRegisters(cpu, 7, 0x00, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_Z);
	EXPECT_EQ(mem[0x1236], 0x00);

	mem[0x1236]	= 0x0;
	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x02, 0x00);
	cpu.Run(7);
	VerifyRegisters(cpu, 7, 0x00, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_N);
	EXPECT_EQ(mem[0x1236], 0xff);
}

//-----------------------------------------------------------------------------
//	DEX
//-----------------------------------------------------------------------------
TEST_F(CPU6502MemoryTest, DexImp)
{
	std::cerr << "Standard" << std::endl;
	mem[0x4242] = CPU6502::INS_DEX_IMP;
	SetRegisters(cpu, 0x00, 0x02, 0x00);
	cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0x01, 0x00, 0x4243, CPU6502::MSK_SR_NONE);

	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x01, 0x00);
	cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0x00, 0x00, 0x4243, CPU6502::MSK_SR_Z);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x00, 0x00);
	cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0xff, 0x00, 0x4243, CPU6502::MSK_SR_N);
}

//-----------------------------------------------------------------------------
//	DEY
//-----------------------------------------------------------------------------
TEST_F(CPU6502MemoryTest,DeyImp)
{
	std::cerr << "Standard" << std::endl;
	mem[0x4242] = CPU6502::INS_DEY_IMP;
	SetRegisters(cpu, 0x00, 0x00, 0x02);
	cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0x00, 0x01, 0x4243, CPU6502::MSK_SR_NONE);

	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x00, 0x01);
	cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0x00, 0x00, 0x4243, CPU6502::MSK_SR_Z);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x00, 0x00);
	cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0x00, 0xff, 0x4243, CPU6502::MSK_SR_N);
}

//-----------------------------------------------------------------------------
//	INC
//-----------------------------------------------------------------------------
TEST_F(CPU6502MemoryTest, IncAbs)
{
	mem[0x1234]	= 0x02;
	mem[0x4242] = CPU6502::INS_INC_ABS;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x00, 0x00, 0x00);
	cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_NONE);
	EXPECT_EQ(mem[0x1234], 0x03);

	mem[0x1234]	= 0xff;
	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x00, 0x00);
	cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_Z);
	EXPECT_EQ(mem[0x1234], 0x00);

	mem[0x1234]	= 0x7f;
	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x00, 0x00);
	cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_N);
	EXPECT_EQ(mem[0x1234], 0x80);
}

TEST_F(CPU6502MemoryTest, IncZp)
{
	mem[0x0040]	= 0x02;
	mem[0x4242] = CPU6502::INS_INC_ZP;
	mem[0x4243]	= 0x40;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x00, 0x00, 0x00);
	cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_NONE);
	EXPECT_EQ(mem[0x0040], 0x03);

	mem[0x0040]	= 0xff;
	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x00, 0x00);
	cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_Z);
	EXPECT_EQ(mem[0x0040], 0x00);

	mem[0x0040]	= 0x7f;
	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x00, 0x00);
	cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_N);
	EXPECT_EQ(mem[0x0040], 0x80);
}

TEST_F(CPU6502MemoryTest, IncZpX)
{
	mem[0x0042]	= 0x02;
	mem[0x4242] = CPU6502::INS_INC_ZPX;
	mem[0x4243]	= 0x40;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x00, 0x02, 0x00);
	cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_NONE);
	EXPECT_EQ(mem[0x0042], 0x03);

	mem[0x0042]	= 0xff;
	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x02, 0x00);
	cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_Z);
	EXPECT_EQ(mem[0x0042], 0x00);

	mem[0x0042]	= 0x7f;
	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x02, 0x00);
	cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_N);
	EXPECT_EQ(mem[0x0042], 0x80);
}

TEST_F(CPU6502MemoryTest, IncAbsX)
{
	mem[0x1236]	= 0x02;
	mem[0x4242] = CPU6502::INS_INC_ABS_X;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x00, 0x02, 0x00);
	cpu.Run(7);
	VerifyRegisters(cpu, 7, 0x00, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_NONE);
	EXPECT_EQ(mem[0x1236], 0x03);

	mem[0x1236]	= 0xff;
	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x02, 0x00);
	cpu.Run(7);
	VerifyRegisters(cpu, 7, 0x00, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_Z);
	EXPECT_EQ(mem[0x1236], 0x00);

	mem[0x1236]	= 0x7f;
	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x02, 0x00);
	cpu.Run(7);
	VerifyRegisters(cpu, 7, 0x00, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_N);
	EXPECT_EQ(mem[0x1236], 0x80);
}

//-----------------------------------------------------------------------------
//	INX
//-----------------------------------------------------------------------------
TEST_F(CPU6502MemoryTest, InxImp)
{
	std::cerr << "Standard" << std::endl;
	mem[0x4242] = CPU6502::INS_INX_IMP;
	SetRegisters(cpu, 0x00, 0x02, 0x00);
	cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0x03, 0x00, 0x4243, CPU6502::MSK_SR_NONE);

	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0xff, 0x00);
	cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0x00, 0x00, 0x4243, CPU6502::MSK_SR_Z);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x7f, 0x00);
	cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0x80, 0x00, 0x4243, CPU6502::MSK_SR_N);
}

//-----------------------------------------------------------------------------
//	INY
//-----------------------------------------------------------------------------
TEST_F(CPU6502MemoryTest, InyImp)
{
	std::cerr << "Standard" << std::endl;
	mem[0x4242] = CPU6502::INS_INY_IMP;
	SetRegisters(cpu, 0x00, 0x00, 0x02);
	cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0x00, 0x03, 0x4243, CPU6502::MSK_SR_NONE);

	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x00, 0xff);
	cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0x00, 0x00, 0x4243, CPU6502::MSK_SR_Z);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x00, 0x7f);
	cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0x00, 0x80, 0x4243, CPU6502::MSK_SR_N);
}

//-----------------------------------------------------------------------------
//	PHA
//-----------------------------------------------------------------------------
TEST_F(CPU6502MemoryTest, PHA_IMP)
{
	mem[0x4242]	= CPU6502::INS_PHA_IMP;

	cpu.SetSR(CPU6502::MSK_SR_NONE);
	Byte SPc = cpu.GetSP();
	SetRegisters(cpu, 0x55, 0x02, 0x03);		// preset A=0x55, X=0x02, Y=0x03
	int clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x55, 0x02, 0x03, 0x4243, CPU6502::MSK_SR_NONE);
	EXPECT_EQ(SPc, cpu.GetSP()+1);
	EXPECT_EQ(mem[0x100 + SPc], 0x55);

	cpu.Reset();
	cpu.SetSR(0xaa);							// set bits in status register
	SPc = cpu.GetSP();
	SetRegisters(cpu, 0xaa, 0x02, 0x03);		// preset A=0xaa, X=0x02, Y=0x03
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0xaa, 0x02, 0x03, 0x4243, 0xaa);
	EXPECT_EQ(SPc, cpu.GetSP()+1);
	EXPECT_EQ(mem[0x0100 + SPc], 0xaa);
}
//-----------------------------------------------------------------------------
//	PHP
//-----------------------------------------------------------------------------

TEST_F(CPU6502MemoryTest, PHP_IMP)
{
	mem[0x4242]	= CPU6502::INS_PHP_IMP;

	cpu.SetSR(0x45);
	Byte SPc = cpu.GetSP();
	SetRegisters(cpu, 0x55, 0x02, 0x03);		// preset A=0x55, X=0x02, Y=0x03
	int clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x55, 0x02, 0x03, 0x4243, 0x45);
	EXPECT_EQ(SPc, cpu.GetSP()+1);
	EXPECT_EQ(mem[0x0100 + SPc], 0x75);

	cpu.Reset();
	cpu.SetSR(0x8a);
	SPc = cpu.GetSP();
	SetRegisters(cpu, 0xaa, 0x02, 0x03);		// preset A=0xaa, X=0x02, Y=0x03
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0xaa, 0x02, 0x03, 0x4243, 0x8a);
	EXPECT_EQ(SPc, cpu.GetSP()+1);
	EXPECT_EQ(mem[0x0100 + SPc], 0xba);

	cpu.Reset();
	cpu.SetSR(0b11001111);
	SPc = cpu.GetSP();
	SetRegisters(cpu, 0xaa, 0x02, 0x03);		// preset A=0xaa, X=0x02, Y=0x03
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0xaa, 0x02, 0x03, 0x4243, 0b11001111);
	EXPECT_EQ(SPc, cpu.GetSP()+1);
	EXPECT_EQ(mem[0x0100 + SPc], 0b11111111);
}

//-----------------------------------------------------------------------------
//	PLA
//-----------------------------------------------------------------------------
TEST_F(CPU6502MemoryTest, PLA_IMP)
{
	mem[0x4242]	= CPU6502::INS_PLA_IMP;

	std::cerr << "Standard" << std::endl;
	cpu.SetSR(0x00);
	cpu.SetSP(0xef);
	mem[0x0100 + cpu.GetSP() + 1]	= 0x55;
	Byte SPc = cpu.GetSP();
	SetRegisters(cpu, 0x00, 0x02, 0x03);		// preset A=0x00, X=0x02, Y=0x03
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x55, 0x02, 0x03, 0x4243, 0x00);
	EXPECT_EQ(SPc, cpu.GetSP()-1);

	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(0x00);							// set bits in status register
	cpu.SetSP(0xef);
	mem[0x0100 + cpu.GetSP() + 1]	= 0x00;
	SPc = cpu.GetSP();
	SetRegisters(cpu, 0xaa, 0x02, 0x03);		// preset A=0xaa, X=0x02, Y=0x03
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x02, 0x03, 0x4243, CPU6502::MSK_SR_Z);
	EXPECT_EQ(SPc, cpu.GetSP()-1);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(0x00);							// set bits in status register
	cpu.SetSP(0xef);
	mem[0x0100 + cpu.GetSP() + 1]	= 0x80;
	SPc = cpu.GetSP();
	SetRegisters(cpu, 0x00, 0x02, 0x03);		// preset A=0x00, X=0x02, Y=0x03
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x80, 0x02, 0x03, 0x4243, CPU6502::MSK_SR_N);
	EXPECT_EQ(SPc, cpu.GetSP()-1);
}

//-----------------------------------------------------------------------------
//	PLP
//-----------------------------------------------------------------------------
TEST_F(CPU6502MemoryTest, PLP_IMP)
{
	mem[0x4242]	= CPU6502::INS_PLP_IMP;

	cpu.SetSR(0x00);
	cpu.SetSP(0xef);
	mem[0x0100 + cpu.GetSP() + 1]	= 0x55;
	Byte SPc = cpu.GetSP();
	SetRegisters(cpu, 0x00, 0x02, 0x03);		// preset A=0x00, X=0x02, Y=0x03
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x02, 0x03, 0x4243, 0x45);
	EXPECT_EQ(SPc, cpu.GetSP()-1);

	cpu.Reset();
	cpu.SetSR(0x45);							// set bits in status register
	cpu.SetSP(0xef);
	mem[0x0100 + cpu.GetSP() + 1]	= 0x00;
	SPc = cpu.GetSP();
	SetRegisters(cpu, 0xaa, 0x02, 0x03);		// preset A=0xaa, X=0x02, Y=0x03
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0xaa, 0x02, 0x03, 0x4243, 0x00);
	EXPECT_EQ(SPc, cpu.GetSP()-1);

	cpu.Reset();
	cpu.SetSR(0x8a);							// set bits in status register
	cpu.SetSP(0xef);
	mem[0x0100 + cpu.GetSP() + 1]	= 0x80;
	SPc = cpu.GetSP();
	SetRegisters(cpu, 0x00, 0x02, 0x03);		// preset A=0x00, X=0x02, Y=0x03
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x02, 0x03, 0x4243, 0x80);
	EXPECT_EQ(SPc, cpu.GetSP()-1);
}

//-----------------------------------------------------------------------------
//	STA
//-----------------------------------------------------------------------------
TEST_F(CPU6502MemoryTest, StaAbs)
{
	int clocks;

	mem[0x4242] = CPU6502::INS_STA_ABS;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	cpu.SetSR(CPU6502::MSK_SR_NONE);
	SetRegisters(cpu, 0x55, 0x02, 0x03);		// preset A=0x55, X=0x02, Y=0x03
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x55, 0x02, 0x03, 0x4245, CPU6502::MSK_SR_NONE);
	EXPECT_EQ(mem[0x1234], 0x55);	
}

TEST_F(CPU6502MemoryTest, StaZp)
{
	int clocks;

	mem[0x4242] = CPU6502::INS_STA_ZP;
	mem[0x4243]	= 0x40;

	cpu.SetSR(CPU6502::MSK_SR_NONE);
	SetRegisters(cpu, 0x55, 0x02, 0x03);		// preset A=0x55, X=0x02, Y=0x03
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x55, 0x02, 0x03, 0x4244, CPU6502::MSK_SR_NONE);
	EXPECT_EQ(mem[0x0040], 0x55);	
}

TEST_F(CPU6502MemoryTest, StaIndX)
{
	int clocks;

	mem[0x0042]	= 0x34;
	mem[0x0043]	= 0x12;
	mem[0x4242] = CPU6502::INS_STA_IND_X;
	mem[0x4243]	= 0x40;

	cpu.SetSR(CPU6502::MSK_SR_NONE);
	SetRegisters(cpu, 0x55, 0x02, 0x03);		// preset A=0x55, X=0x02, Y=0x03
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x55, 0x02, 0x03, 0x4244, CPU6502::MSK_SR_NONE);
	EXPECT_EQ(mem[0x1234], 0x55);	
}

TEST_F(CPU6502MemoryTest, StaIndY)
{
	int clocks;

	mem[0x0040]	= 0x34;
	mem[0x0041]	= 0x12;
	mem[0x4242] = CPU6502::INS_STA_IND_Y;
	mem[0x4243]	= 0x40;

	cpu.SetSR(CPU6502::MSK_SR_NONE);
	SetRegisters(cpu, 0x55, 0x02, 0x03);		// preset A=0x55, X=0x02, Y=0x03
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x55, 0x02, 0x03, 0x4244, CPU6502::MSK_SR_NONE);
	EXPECT_EQ(mem[0x1237], 0x55);	
}

TEST_F(CPU6502MemoryTest, StaZpX)
{
	int clocks;

	mem[0x4242] = CPU6502::INS_STA_ZPX;
	mem[0x4243]	= 0x40;

	cpu.SetSR(CPU6502::MSK_SR_NONE);
	SetRegisters(cpu, 0x55, 0x02, 0x03);		// preset A=0x55, X=0x02, Y=0x03
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x55, 0x02, 0x03, 0x4244, CPU6502::MSK_SR_NONE);
	EXPECT_EQ(mem[0x0042], 0x55);	
}

TEST_F(CPU6502MemoryTest, StaAbsX)
{
	int clocks;

	mem[0x4242] = CPU6502::INS_STA_ABS_X;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	cpu.SetSR(CPU6502::MSK_SR_NONE);
	SetRegisters(cpu, 0x55, 0x02, 0x03);		// preset A=0x55, X=0x02, Y=0x03
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x55, 0x02, 0x03, 0x4245, CPU6502::MSK_SR_NONE);
	EXPECT_EQ(mem[0x1236], 0x55);	
}

TEST_F(CPU6502MemoryTest, StaAbsY)
{
	int clocks;

	mem[0x4242] = CPU6502::INS_STA_ABS_X;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	cpu.SetSR(CPU6502::MSK_SR_NONE);
	SetRegisters(cpu, 0x55, 0x02, 0x03);		// preset A=0x55, X=0x02, Y=0x03
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x55, 0x02, 0x03, 0x4245, CPU6502::MSK_SR_NONE);
	EXPECT_EQ(mem[0x1237], 0x55);	
}

//-----------------------------------------------------------------------------
//	STX
//-----------------------------------------------------------------------------
TEST_F(CPU6502MemoryTest, StxAbs)
{
	int clocks;

	mem[0x4242] = CPU6502::INS_STX_ABS;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	cpu.SetSR(CPU6502::MSK_SR_NONE);
	SetRegisters(cpu, 0x01, 0x55, 0x03);		// preset A=0x01, X=0x55, Y=0x03
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x01, 0x55, 0x03, 0x4245, CPU6502::MSK_SR_NONE);
	EXPECT_EQ(mem[0x1234], 0x55);	
}

TEST_F(CPU6502MemoryTest, StxZp)
{
	int clocks;

	mem[0x4242] = CPU6502::INS_STX_ZP;
	mem[0x4243]	= 0x40;

	cpu.SetSR(CPU6502::MSK_SR_NONE);
	SetRegisters(cpu, 0x01, 0x55, 0x03);		// preset A=0x01, X=0x55, Y=0x03
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x01, 0x55, 0x03, 0x4244, CPU6502::MSK_SR_NONE);
	EXPECT_EQ(mem[0x0040], 0x55);	
}

TEST_F(CPU6502MemoryTest, StxZpY)
{
	int clocks;

	mem[0x4242] = CPU6502::INS_STX_ZPY;
	mem[0x4243]	= 0x40;

	cpu.SetSR(CPU6502::MSK_SR_NONE);
	SetRegisters(cpu, 0x01, 0x55, 0x03);		// preset A=0x01, X=0x55, Y=0x03
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x01, 0x55, 0x03, 0x4244, CPU6502::MSK_SR_NONE);
	EXPECT_EQ(mem[0x0043], 0x55);	
}

//-----------------------------------------------------------------------------
//	STY
//-----------------------------------------------------------------------------
TEST_F(CPU6502MemoryTest, StyAbs)
{
	int clocks;

	mem[0x4242] = CPU6502::INS_STY_ABS;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	cpu.SetSR(CPU6502::MSK_SR_NONE);
	SetRegisters(cpu, 0x01, 0x02, 0x55);		// preset A=0x01, X=0x02, Y=0x55
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x01, 0x02, 0x55, 0x4245, CPU6502::MSK_SR_NONE);
	EXPECT_EQ(mem[0x1234], 0x55);	
}

TEST_F(CPU6502MemoryTest, StyZp)
{
	int clocks;

	mem[0x4242] = CPU6502::INS_STY_ZP;
	mem[0x4243]	= 0x40;

	cpu.SetSR(CPU6502::MSK_SR_NONE);
	SetRegisters(cpu, 0x01, 0x02, 0x55);		// preset A=0x01, X=0x02, Y=0x55
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x01, 0x02, 0x55, 0x4244, CPU6502::MSK_SR_NONE);
	EXPECT_EQ(mem[0x0040], 0x55);	
}

TEST_F(CPU6502MemoryTest, StyZpX)
{
	int clocks;

	mem[0x4242] = CPU6502::INS_STY_ZPX;
	mem[0x4243]	= 0x40;

	cpu.SetSR(CPU6502::MSK_SR_NONE);
	SetRegisters(cpu, 0x01, 0x02, 0x55);		// preset A=0x01, X=0x02, Y=0x55
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x01, 0x02, 0x55, 0x4244, CPU6502::MSK_SR_NONE);
	EXPECT_EQ(mem[0x0042], 0x55);	
}

//-----------------------------------------------------------------------------
//	TAX
//-----------------------------------------------------------------------------
TEST_F(CPU6502MemoryTest, TaxImp)
{
	mem[0x4242]	= CPU6502::INS_TAX_IMP;

	std::cerr << "Standard" << std::endl;
	cpu.SetSR(0x00);
	SetRegisters(cpu, 0x03, 0x00, 0x00);		// preset A=0x03, X=0x00, Y=0x00
	int clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x03, 0x03, 0x00, 0x4243, CPU6502::MSK_SR_NONE);

	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(0x00);
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0x00, 0x00, 0x4243, CPU6502::MSK_SR_Z);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(0x00);
	SetRegisters(cpu, 0x80, 0x00, 0x00);		// preset A=0x80, X=0x00, Y=0x00
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x80, 0x80, 0x00, 0x4243, CPU6502::MSK_SR_N);
}

//-----------------------------------------------------------------------------
//	TAY
//-----------------------------------------------------------------------------
TEST_F(CPU6502MemoryTest, TayImp)
{
	mem[0x4242]	= CPU6502::INS_TAY_IMP;

	std::cerr << "Standard" << std::endl;
	cpu.SetSR(0x00);
	SetRegisters(cpu, 0x03, 0x00, 0x00);		// preset A=0x03, X=0x00, Y=0x00
	int clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x03, 0x00, 0x03, 0x4243, CPU6502::MSK_SR_NONE);

	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(0x00);
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0x00, 0x00, 0x4243, CPU6502::MSK_SR_Z);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(0x00);
	SetRegisters(cpu, 0x80, 0x00, 0x00);		// preset A=0x80, X=0x00, Y=0x00
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x80, 0x00, 0x80, 0x4243, CPU6502::MSK_SR_N);
}

//-----------------------------------------------------------------------------
//	TSX
//-----------------------------------------------------------------------------
TEST_F(CPU6502MemoryTest, TsxImp)
{
	mem[0x4242]	= CPU6502::INS_TSX_IMP;

	std::cerr << "Standard" << std::endl;
	cpu.SetSR(0x00);
	cpu.SetSP(0x55);
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	int clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0x55, 0x00, 0x4243, CPU6502::MSK_SR_NONE);

	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(0x00);
	cpu.SetSP(0x00);
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0x00, 0x00, 0x4243, CPU6502::MSK_SR_Z);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(0x00);
	cpu.SetSP(0x80);
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0x80, 0x00, 0x4243, CPU6502::MSK_SR_N);
}

//-----------------------------------------------------------------------------
//	TXA
//-----------------------------------------------------------------------------
TEST_F(CPU6502MemoryTest, TxaImp)
{
	mem[0x4242]	= CPU6502::INS_TXA_IMP;

	std::cerr << "Standard" << std::endl;
	cpu.SetSR(0x00);
	SetRegisters(cpu, 0x00, 0x03, 0x00);		// preset A=0x00, X=0x03, Y=0x00
	int clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x03, 0x03, 0x00, 0x4243, CPU6502::MSK_SR_NONE);

	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(0x00);
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0x00, 0x00, 0x4243, CPU6502::MSK_SR_Z);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(0x00);
	SetRegisters(cpu, 0x00, 0x80, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x80, 0x80, 0x00, 0x4243, CPU6502::MSK_SR_N);
}

//-----------------------------------------------------------------------------
//	TXS
//-----------------------------------------------------------------------------
TEST_F(CPU6502MemoryTest, TxsImp)
{
	mem[0x4242]	= CPU6502::INS_TXS_IMP;

	cpu.SetSR(0x00);
	SetRegisters(cpu, 0x00, 0xef, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	int clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0xef, 0x00, 0x4243, CPU6502::MSK_SR_NONE);
	EXPECT_EQ(cpu.GetSP(), 0xef);
}

//-----------------------------------------------------------------------------
//	TYA
//-----------------------------------------------------------------------------
TEST_F(CPU6502MemoryTest, TyaImp)
{
	mem[0x4242]	= CPU6502::INS_TYA_IMP;

	std::cerr << "Standard" << std::endl;
	cpu.SetSR(0x00);
	SetRegisters(cpu, 0x00, 0x00, 0x03);		// preset A=0x00, X=0x00, Y=0x00
	int clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x03, 0x00, 0x03, 0x4243, CPU6502::MSK_SR_NONE);

	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(0x00);
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0x00, 0x00, 0x4243, CPU6502::MSK_SR_Z);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(0x00);
	SetRegisters(cpu, 0x00, 0x00, 0x80);		// preset A=0x00, X=0x00, Y=0x00
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x80, 0x00, 0x80, 0x4243, CPU6502::MSK_SR_N);
}
