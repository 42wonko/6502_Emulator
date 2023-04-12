#include <iostream>
#include "cpu_6502_logic_test.h"

//-----------------------------------------------------------------------------
//	ASL
//-----------------------------------------------------------------------------
TEST_F(CPU6502LogicTest, AslAbs)
{
	mem[0x1234]	= 0xaa;
	mem[0x4242]	= CPU6502::INS_ASL_ABS;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	std::cerr << "C-Flag" << std::endl;
	SetRegisters(cpu, 0, 0, 0);		// preset A=0, X=0, Y=0
	int clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_C);
	EXPECT_EQ(mem[0x1234], 0x54);


	std::cerr << "C-Flag, Z-Flag" << std::endl;
	mem[0x1234]	= 0x80;
	cpu.Reset();
	SetRegisters(cpu, 0, 0, 0);		// preset A=0, X=0, Y=0
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_C | CPU6502::MSK_SR_Z);
	EXPECT_EQ(mem[0x1234], 0x00);

	std::cerr << "N-Flag" << std::endl;
	mem[0x1234]	= 0x40;
	cpu.Reset();
	SetRegisters(cpu, 0, 0, 0);		// preset A=0, X=0, Y=0
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_N);
	EXPECT_EQ(mem[0x1234], 0x80);

	std::cerr << "Standard" << std::endl;
	mem[0x1234]	= 0x03;
	cpu.Reset();
	SetRegisters(cpu, 0, 0, 0);		// preset A=0, X=0, Y=0
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_NONE);
	EXPECT_EQ(mem[0x1234], 0x06);
}

TEST_F(CPU6502LogicTest, AslZp)
{
	mem[0x0040]	= 0xaa;
	mem[0x4242]	= CPU6502::INS_ASL_ZP;
	mem[0x4243]	= 0x40;

	std::cerr << "C-Flag" << std::endl;
	SetRegisters(cpu, 0, 0, 0);		// preset A=0, X=0, Y=0
	int clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_C);
	EXPECT_EQ(mem[0x0040], 0x54);


	std::cerr << "C-Flag, Z-Flag" << std::endl;
	mem[0x0040]	= 0x80;
	cpu.Reset();
	SetRegisters(cpu, 0, 0, 0);		// preset A=0, X=0, Y=0
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_C | CPU6502::MSK_SR_Z);
	EXPECT_EQ(mem[0x0040], 0x00);

	std::cerr << "N-Flag" << std::endl;
	mem[0x0040]	= 0x40;
	cpu.Reset();
	SetRegisters(cpu, 0, 0, 0);		// preset A=0, X=0, Y=0
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_N);
	EXPECT_EQ(mem[0x0040], 0x80);

	std::cerr << "Standard" << std::endl;
	mem[0x0040]	= 0x03;
	cpu.Reset();
	SetRegisters(cpu, 0, 0, 0);		// preset A=0, X=0, Y=0
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_NONE);
	EXPECT_EQ(mem[0x0040], 0x06);
}

TEST_F(CPU6502LogicTest, AslAcc)
{
	mem[0x4242]	= CPU6502::INS_ASL_ACC;

	std::cerr << "C-Flag" << std::endl;
	SetRegisters(cpu, 0xaa, 0x00, 0x00);		// preset A=0, X=0, Y=0
	int clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x54, 0x00, 0x00, 0x4243, CPU6502::MSK_SR_C);


	std::cerr << "C-Flag, Z-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x80, 0x00, 0x00);		// preset A=0, X=0, Y=0
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0x00, 0x00, 0x4243, CPU6502::MSK_SR_C | CPU6502::MSK_SR_Z);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x40, 0x00, 0x00);		// preset A=0, X=0, Y=0
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x80, 0x00, 0x00, 0x4243, CPU6502::MSK_SR_N);

	std::cerr << "Standard" << std::endl;
	mem[0x0040]	= 0x03;
	cpu.Reset();
	SetRegisters(cpu, 0x03, 0x00, 0x00);		// preset A=0, X=0, Y=0
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x06, 0x00, 0x00, 0x4243, CPU6502::MSK_SR_NONE);
}

TEST_F(CPU6502LogicTest, AslZpX)
{
	mem[0x0042]	= 0xaa;
	mem[0x4242]	= CPU6502::INS_ASL_ZPX;
	mem[0x4243]	= 0x40;

	std::cerr << "C-Flag" << std::endl;
	SetRegisters(cpu, 0, 2, 0);		// preset A=0, X=0, Y=0
	int clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_C);
	EXPECT_EQ(mem[0x0042], 0x54);


	std::cerr << "C-Flag, Z-Flag" << std::endl;
	mem[0x0042]	= 0x80;
	cpu.Reset();
	SetRegisters(cpu, 0, 2, 0);		// preset A=0, X=0, Y=0
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_C | CPU6502::MSK_SR_Z);
	EXPECT_EQ(mem[0x0042], 0x00);

	std::cerr << "N-Flag" << std::endl;
	mem[0x0042]	= 0x40;
	cpu.Reset();
	SetRegisters(cpu, 0, 2, 0);		// preset A=0, X=0, Y=0
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_N);
	EXPECT_EQ(mem[0x0042], 0x80);

	std::cerr << "Standard" << std::endl;
	mem[0x0042]	= 0x03;
	cpu.Reset();
	SetRegisters(cpu, 0, 2, 0);		// preset A=0, X=0, Y=0
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_NONE);
	EXPECT_EQ(mem[0x0042], 0x06);
}

TEST_F(CPU6502LogicTest, AslAbsX)
{
	mem[0x1236]	= 0xaa;
	mem[0x4242]	= CPU6502::INS_ASL_ABS_X;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	std::cerr << "C-Flag" << std::endl;
	SetRegisters(cpu, 0, 2, 0);		// preset A=0, X=0, Y=0
	int clocks = cpu.Run(7);
	VerifyRegisters(cpu, 7, 0x00, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_C);
	EXPECT_EQ(mem[0x1236], 0x54);

	std::cerr << "C-Flag, Z-Flag" << std::endl;
	mem[0x1236]	= 0x80;
	cpu.Reset();
	SetRegisters(cpu, 0, 2, 0);		// preset A=0, X=0, Y=0
	clocks = cpu.Run(7);
	VerifyRegisters(cpu, 7, 0x00, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_C | CPU6502::MSK_SR_Z);
	EXPECT_EQ(mem[0x1236], 0x00);

	std::cerr << "N-Flag" << std::endl;
	mem[0x1236]	= 0x40;
	cpu.Reset();
	SetRegisters(cpu, 0, 2, 0);		// preset A=0, X=0, Y=0
	clocks = cpu.Run(7);
	VerifyRegisters(cpu, 7, 0x00, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_N);
	EXPECT_EQ(mem[0x1236], 0x80);

	std::cerr << "Standard" << std::endl;
	mem[0x1236]	= 0x03;
	cpu.Reset();
	SetRegisters(cpu, 0, 2, 0);		// preset A=0, X=0, Y=0
	clocks = cpu.Run(7);
	VerifyRegisters(cpu, 7, 0x00, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_NONE);
	EXPECT_EQ(mem[0x1236], 0x06);
}

//-----------------------------------------------------------------------------
//	BIT
//-----------------------------------------------------------------------------
TEST_F(CPU6502LogicTest, BitAbs)
{
	mem[0x1234]	= 0xff;
	mem[0x4242] = CPU6502::INS_BIT_ABS;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	std::cerr << "BIT Mem:0xff test bit 0" << std::endl;
	SetRegisters(cpu, 0x01, 0x00, 0x00);		// preset A=1, X=0, Y=0
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x01, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_N | CPU6502::MSK_SR_V);

	std::cerr << "BIT Mem:0xff test bit 1" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x02, 0x00, 0x00);		// preset A=2, X=0, Y=0
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x02, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_N | CPU6502::MSK_SR_V);

	std::cerr << "BIT Mem:0xff test bit 2" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x04, 0x00, 0x00);		// preset A=4, X=0, Y=0
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x04, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_N | CPU6502::MSK_SR_V);

	std::cerr << "BIT Mem:0xff test bit 3" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x08, 0x00, 0x00);		// preset A=8, X=0, Y=0
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x08, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_N | CPU6502::MSK_SR_V);

	std::cerr << "BIT Mem:0xff test bit 4" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x10, 0x00, 0x00);		// preset A=16, X=0, Y=0
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x10, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_N | CPU6502::MSK_SR_V);

	std::cerr << "BIT Mem:0xff test bit 5" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x20, 0x00, 0x00);		// preset A=32, X=0, Y=0
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x20, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_N | CPU6502::MSK_SR_V);

	std::cerr << "BIT Mem:0xff test bit 6" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x40, 0x00, 0x00);		// preset A=64, X=0, Y=0
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x40, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_N | CPU6502::MSK_SR_V);

	std::cerr << "BIT Mem:0xff test bit 7" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x80, 0x00, 0x00);		// preset A=128, X=0, Y=0
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x80, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_N | CPU6502::MSK_SR_V);

	std::cerr << "BIT Mem:0x00 test bit 0" << std::endl;
	mem[0x1234]	= 0x00;
	cpu.Reset();
	SetRegisters(cpu, 0x01, 0x00, 0x00);		// preset A=1, X=0, Y=0
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x01, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_Z);

	std::cerr << "BIT Mem:0x40 test bit 1" << std::endl;
	mem[0x1234]	= 0x40;
	cpu.Reset();
	SetRegisters(cpu, 0x02, 0x00, 0x00);		// preset A=2, X=0, Y=0
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x02, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_Z | CPU6502::MSK_SR_V);

	std::cerr << "BIT Mem:0x80 test bit 2" << std::endl;
	mem[0x1234]	= 0x80;
	cpu.Reset();
	SetRegisters(cpu, 0x04, 0x00, 0x00);		// preset A=4, X=0, Y=0
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x04, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_Z | CPU6502::MSK_SR_N);

	std::cerr << "BIT Mem:0xc0 test bit 3" << std::endl;
	mem[0x1234]	= 0xc0;
	cpu.Reset();
	SetRegisters(cpu, 0x08, 0x00, 0x00);		// preset A=8, X=0, Y=0
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x08, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_Z | CPU6502::MSK_SR_N | CPU6502::MSK_SR_V);

	std::cerr << "BIT Mem:0x00 test bit 4" << std::endl;
	mem[0x1234]	= 0x00;
	cpu.Reset();
	SetRegisters(cpu, 0x10, 0x00, 0x00);		// preset A=16, X=0, Y=0
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x10, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_Z);

	std::cerr << "BIT Mem:0x00 test bit 5" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x20, 0x00, 0x00);		// preset A=32, X=0, Y=0
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x20, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_Z);

	std::cerr << "BIT Mem:0x00 test bit 6" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x40, 0x00, 0x00);		// preset A=64, X=0, Y=0
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x40, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_Z);

	std::cerr << "BIT Mem:0x00 test bit 7" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x80, 0x00, 0x00);		// preset A=128, X=0, Y=0
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x80, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_Z);

}

TEST_F(CPU6502LogicTest, BitZp)
{
	mem[0x0040]	= 0xff;
	mem[0x4242] = CPU6502::INS_BIT_ZP;
	mem[0x4243]	= 0x40;

	std::cerr << "BIT_ZP Mem:0xff test bit 0" << std::endl;
	SetRegisters(cpu, 0x01, 0x00, 0x00);		// preset A=1, X=0, Y=0
	int clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x01, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_N | CPU6502::MSK_SR_V);

	std::cerr << "BIT_ZP Mem:0xff test bit 1" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x02, 0x00, 0x00);		// preset A=2, X=0, Y=0
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x02, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_N | CPU6502::MSK_SR_V);

	std::cerr << "BIT_ZP Mem:0xff test bit 2" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x04, 0x00, 0x00);		// preset A=4, X=0, Y=0
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x04, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_N | CPU6502::MSK_SR_V);

	std::cerr << "BIT_ZP Mem:0xff test bit 3" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x08, 0x00, 0x00);		// preset A=8, X=0, Y=0
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x08, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_N | CPU6502::MSK_SR_V);

	std::cerr << "BIT_ZP Mem:0xff test bit 4" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x10, 0x00, 0x00);		// preset A=16, X=0, Y=0
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x10, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_N | CPU6502::MSK_SR_V);

	std::cerr << "BIT_ZP Mem:0xff test bit 5" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x20, 0x00, 0x00);		// preset A=32, X=0, Y=0
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x20, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_N | CPU6502::MSK_SR_V);

	std::cerr << "BIT_ZP Mem:0xff test bit 6" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x40, 0x00, 0x00);		// preset A=64, X=0, Y=0
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x40, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_N | CPU6502::MSK_SR_V);

	std::cerr << "BIT_ZP Mem:0xff test bit 7" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x80, 0x00, 0x00);		// preset A=128, X=0, Y=0
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x80, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_N | CPU6502::MSK_SR_V);

	std::cerr << "BIT_ZP Mem:0x00 test bit 0" << std::endl;
	mem[0x0040]	= 0x00;
	cpu.Reset();
	SetRegisters(cpu, 0x01, 0x00, 0x00);		// preset A=1, X=0, Y=0
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x01, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_Z);

	std::cerr << "BIT_ZP Mem:0x40 test bit 1" << std::endl;
	mem[0x0040]	= 0x40;
	cpu.Reset();
	SetRegisters(cpu, 0x02, 0x00, 0x00);		// preset A=2, X=0, Y=0
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x02, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_Z | CPU6502::MSK_SR_V);

	std::cerr << "BIT_ZP Mem:0x80 test bit 2" << std::endl;
	mem[0x0040]	= 0x80;
	cpu.Reset();
	SetRegisters(cpu, 0x04, 0x00, 0x00);		// preset A=4, X=0, Y=0
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x04, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_Z | CPU6502::MSK_SR_N);

	std::cerr << "BIT_ZP Mem:0xc0 test bit 3" << std::endl;
	mem[0x0040]	= 0xc0;
	cpu.Reset();
	SetRegisters(cpu, 0x08, 0x00, 0x00);		// preset A=8, X=0, Y=0
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x08, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_Z | CPU6502::MSK_SR_N | CPU6502::MSK_SR_V);

	std::cerr << "BIT_ZP Mem:0x00 test bit 4" << std::endl;
	mem[0x0040]	= 0x00;
	cpu.Reset();
	SetRegisters(cpu, 0x10, 0x00, 0x00);		// preset A=16, X=0, Y=0
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x10, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_Z);

	std::cerr << "BIT_ZP Mem:0x00 test bit 5" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x20, 0x00, 0x00);		// preset A=32, X=0, Y=0
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x20, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_Z);

	std::cerr << "BIT_ZP Mem:0x00 test bit 6" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x40, 0x00, 0x00);		// preset A=64, X=0, Y=0
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x40, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_Z);

	std::cerr << "BIT_ZP Mem:0x00 test bit 7" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x80, 0x00, 0x00);		// preset A=128, X=0, Y=0
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x80, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_Z);
}

//-----------------------------------------------------------------------------
//	EOR
//-----------------------------------------------------------------------------
TEST_F(CPU6502LogicTest, EorImm)
{
	mem[0x4242]	= CPU6502::INS_EOR_IM;
	mem[0x4243]	= 0x5f;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x0c, 0x00, 0x00);		// preset A=0b00001100, X=0, Y=0
	int clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x53, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_NONE);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	mem[0x4243]	= 0xaa;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0, X=0, Y=0
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0xaa, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_N);

	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0xaa, 0x00, 0x00);		// preset A=0, X=0, Y=0
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_Z);
}

TEST_F(CPU6502LogicTest, EorAbs)
{
	mem[0x1234]	= 0x5f;
	mem[0x4242]	= CPU6502::INS_EOR_ABS;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x0c, 0x00, 0x00);		// preset A=0b00001100, X=0, Y=0
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x53, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_NONE);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	mem[0x1234]	= 0xaa;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0, X=0, Y=0
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0xaa, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_N);

	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0xaa, 0x00, 0x00);		// preset A=0, X=0, Y=0
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_Z);
}

TEST_F(CPU6502LogicTest, EorZp)
{
	mem[0x0040]	= 0x5f;
	mem[0x4242]	= CPU6502::INS_EOR_ZP;
	mem[0x4243]	= 0x40;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x0c, 0x00, 0x00);		// preset A=0b00001100, X=0, Y=0
	int clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x53, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_NONE);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	mem[0x0040]	= 0xaa;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0, X=0, Y=0
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0xaa, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_N);

	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0xaa, 0x00, 0x00);		// preset A=0, X=0, Y=0
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x00, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_Z);
}

TEST_F(CPU6502LogicTest, EorIndX)
{
	mem[0x0042]	= 0x34;
	mem[0x0043]	= 0x12;
	mem[0x1234]	= 0x5f;
	mem[0x4242]	= CPU6502::INS_EOR_IND_X;
	mem[0x4243]	= 0x40;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x0c, 0x02, 0x00);		// preset A=0b00001100, X=2, Y=0
	int clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x53, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_NONE);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	mem[0x1234]	= 0xaa;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0, X=2, Y=0
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0xaa, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_N);

	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0xaa, 0x02, 0x00);		// preset A=0, X=2, Y=0
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_Z);
}

TEST_F(CPU6502LogicTest, EorIndY)
{
	mem[0x0040]	= 0x34;
	mem[0x0041]	= 0x12;
	mem[0x1236]	= 0x5f;
	mem[0x4242]	= CPU6502::INS_EOR_IND_Y;
	mem[0x4243]	= 0x40;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x0c, 0x00, 0x02);		// preset A=0b00001100, X=0, Y=2
	int clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x53, 0x00, 0x02, 0x4244, CPU6502::MSK_SR_NONE);

	std::cerr << "Standard + page break" << std::endl;
	mem[0x0040]	= 0xff;
	mem[0x0041]	= 0x10;
	mem[0x1101]	= 0x5f;
	cpu.Reset();
	SetRegisters(cpu, 0x0c, 0x00, 0x02);		// preset A=0b00001100, X=0, Y=2
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x53, 0x00, 0x02, 0x4244, CPU6502::MSK_SR_NONE);

	std::cerr << "N-Flag" << std::endl;
	mem[0x0040]	= 0x34;
	mem[0x0041]	= 0x12;
	cpu.Reset();
	mem[0x1236]	= 0xaa;
	SetRegisters(cpu, 0x00, 0x00, 0x02);		// preset A=0, X=0, Y=2
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0xaa, 0x00, 0x02, 0x4244, CPU6502::MSK_SR_N);

	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0xaa, 0x00, 0x02);		// preset A=0, X=0, Y=2
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0x00, 0x02, 0x4244, CPU6502::MSK_SR_Z);
}

TEST_F(CPU6502LogicTest, EorZpX)
{
	mem[0x0042]	= 0x5f;
	mem[0x4242]	= CPU6502::INS_EOR_ZPX;
	mem[0x4243]	= 0x40;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x0c, 0x02, 0x00);		// preset A=0b00001100, X=2, Y=0
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x53, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_NONE);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	mem[0x0042]	= 0xaa;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0, X=2, Y=0
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0xaa, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_N);

	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0xaa, 0x02, 0x00);		// preset A=0, X=2, Y=0
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_Z);
}

TEST_F(CPU6502LogicTest, EorAbsX)
{
	mem[0x1236]	= 0x5f;
	mem[0x4242]	= CPU6502::INS_EOR_ABS_X;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x0c, 0x02, 0x00);		// preset A=0b00001100, X=2, Y=0
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x53, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_NONE);

	std::cerr << "Standard" << std::endl;
	cpu.Reset();
	mem[0x4243]	= 0xff;
	mem[0x4244]	= 0x10;
	mem[0x1101]	= 0x5f;
	SetRegisters(cpu, 0x0c, 0x02, 0x00);		// preset A=0b00001100, X=2, Y=0
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x53, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_NONE);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;
	mem[0x1236]	= 0xaa;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0, X=2, Y=0
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0xaa, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_N);

	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0xaa, 0x02, 0x00);		// preset A=0, X=2, Y=0
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_Z);
}

TEST_F(CPU6502LogicTest, EorAbsY)
{
	mem[0x1236]	= 0x5f;
	mem[0x4242]	= CPU6502::INS_EOR_ABS_Y;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x0c, 0x00, 0x02);		// preset A=0b00001100, X=0, Y=2
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x53, 0x00, 0x02, 0x4245, CPU6502::MSK_SR_NONE);

	std::cerr << "Standard" << std::endl;
	cpu.Reset();
	mem[0x4243]	= 0xff;
	mem[0x4244]	= 0x10;
	mem[0x1101]	= 0x5f;
	SetRegisters(cpu, 0x0c, 0x00, 0x02);		// preset A=0b00001100, X=0, Y=2
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x53, 0x00, 0x02, 0x4245, CPU6502::MSK_SR_NONE);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;
	mem[0x1236]	= 0xaa;
	SetRegisters(cpu, 0x00, 0x00, 0x02);		// preset A=0, X=0, Y=2
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0xaa, 0x00, 0x02, 0x4245, CPU6502::MSK_SR_N);

	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0xaa, 0x00, 0x02);		// preset A=0, X=0, Y=2
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x00, 0x02, 0x4245, CPU6502::MSK_SR_Z);
}

//-----------------------------------------------------------------------------
//	LSR 
//-----------------------------------------------------------------------------
TEST_F(CPU6502LogicTest, LsrAbs)
{
	mem[0x1234]	= 0xa5;							// 0x5f = 0b10100101 -> 0b 01010010 (c=1)
	mem[0x4242]	= CPU6502::INS_LSR_ABS;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	std::cerr << "standard" << std::endl;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0, X=0, Y=0
	int clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_C);
	EXPECT_EQ(mem[0x1234], 0x52);

	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	mem[0x1234]	= 0x00;							// 0x5f = 0b00000000 -> 0b 00000000 (c=1)
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0, X=0, Y=0
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_Z);
	EXPECT_EQ(mem[0x1234], 0x00);

	std::cerr << "Z-Flag, C-Flag" << std::endl;
	cpu.Reset();
	mem[0x1234]	= 0x01;							// 0x5f = 0b00000001 -> 0b 00000000 (c=1)
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0, X=0, Y=0
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_Z | CPU6502::MSK_SR_C);
	EXPECT_EQ(mem[0x1234], 0x00);
}

TEST_F(CPU6502LogicTest, LsrZp)
{
	mem[0x0040]	= 0xa5;							// 0x5f = 0b10100101 -> 0b 01010010 (c=1)
	mem[0x4242]	= CPU6502::INS_LSR_ZP;
	mem[0x4243]	= 0x40;

	std::cerr << "standard" << std::endl;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0, X=0, Y=0
	int clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_C);
	EXPECT_EQ(mem[0x0040], 0x52);

	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	mem[0x0040]	= 0x00;							// 0x5f = 0b00000000 -> 0b 00000000 (c=1)
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0, X=0, Y=0
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_Z);
	EXPECT_EQ(mem[0x0040], 0x00);

	std::cerr << "Z-Flag, C-Flag" << std::endl;
	cpu.Reset();
	mem[0x0040]	= 0x01;							// 0x5f = 0b00000001 -> 0b 00000000 (c=1)
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0, X=0, Y=0
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_Z | CPU6502::MSK_SR_C);
	EXPECT_EQ(mem[0x0040], 0x00);
}

TEST_F(CPU6502LogicTest, LsrAcc)
{
	mem[0x4242]	= CPU6502::INS_LSR_ACC;

	std::cerr << "standard" << std::endl;
	SetRegisters(cpu, 0xa5, 0x00, 0x00);		// preset A=0, X=0, Y=0
	int clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x52, 0x00, 0x00, 0x4243, CPU6502::MSK_SR_C);

	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0, X=0, Y=0
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0x00, 0x00, 0x4243, CPU6502::MSK_SR_Z);

	std::cerr << "Z-Flag, C-Flag" << std::endl;
	cpu.Reset();
	mem[0x0040]	= 0x01;							// 0x5f = 0b00000001 -> 0b 00000000 (c=1)
	SetRegisters(cpu, 0x01, 0x00, 0x00);		// preset A=0, X=0, Y=0
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0x00, 0x00, 0x4243, CPU6502::MSK_SR_Z | CPU6502::MSK_SR_C);
}

TEST_F(CPU6502LogicTest, LsrZpX)
{
	mem[0x0042]	= 0xa5;							// 0x5f = 0b10100101 -> 0b 01010010 (c=1)
	mem[0x4242]	= CPU6502::INS_LSR_ZPX;
	mem[0x4243]	= 0x40;

	std::cerr << "standard" << std::endl;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0, X=2, Y=0
	int clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_C);
	EXPECT_EQ(mem[0x0042], 0x52);

	std::cerr << "standard with wrap around" << std::endl;
	cpu.Reset();
	mem[0x002f]	= 0xa5;							// 0x5f = 0b10100101 -> 0b 01010010 (c=1)
	SetRegisters(cpu, 0x00, 0xef, 0x00);		// preset A=0, X=0xef, Y=0 (0x40+0xef = 0x01 2f)
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0xef, 0x00, 0x4244, CPU6502::MSK_SR_C);
	EXPECT_EQ(mem[0x002f], 0x52);

	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	mem[0x0042]	= 0x00;							// 0x5f = 0b00000000 -> 0b 00000000 (c=1)
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0, X=0, Y=0
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_Z);
	EXPECT_EQ(mem[0x0042], 0x00);

	std::cerr << "Z-Flag, C-Flag" << std::endl;
	cpu.Reset();
	mem[0x0042]	= 0x01;							// 0x5f = 0b00000001 -> 0b 00000000 (c=1)
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0, X=0, Y=0
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_Z | CPU6502::MSK_SR_C);
	EXPECT_EQ(mem[0x0042], 0x00);
}

TEST_F(CPU6502LogicTest, LsrAbsX)
{
	mem[0x1236]	= 0xa5;							// 0x5f = 0b10100101 -> 0b 01010010 (c=1)
	mem[0x4242]	= CPU6502::INS_LSR_ABS_X;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	std::cerr << "standard" << std::endl;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0, X=0, Y=0
	int clocks = cpu.Run(7);
	VerifyRegisters(cpu, 7, 0x00, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_C);
	EXPECT_EQ(mem[0x1236], 0x52);

	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	mem[0x1236]	= 0x00;							// 0x5f = 0b00000000 -> 0b 00000000 (c=1)
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0, X=0, Y=0
	clocks = cpu.Run(7);
	VerifyRegisters(cpu, 7, 0x00, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_Z);
	EXPECT_EQ(mem[0x1236], 0x00);

	std::cerr << "Z-Flag, C-Flag" << std::endl;
	cpu.Reset();
	mem[0x1236]	= 0x01;							// 0x5f = 0b00000001 -> 0b 00000000 (c=1)
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0, X=0, Y=0
	clocks = cpu.Run(7);
	VerifyRegisters(cpu, 7, 0x00, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_Z | CPU6502::MSK_SR_C);
	EXPECT_EQ(mem[0x1236], 0x00);
}

//-----------------------------------------------------------------------------
// ORA
//-----------------------------------------------------------------------------
TEST_F(CPU6502LogicTest, OraImm)
{
	mem[0x4242]	= CPU6502::INS_ORA_IM;
	mem[0x4243]	= 0x01;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	int clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x01, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_NONE);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	mem[0x4243]	= 0x2a;
	SetRegisters(cpu, 0x80, 0x00, 0x00);		// preset A=0, X=0, Y=0
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0xaa, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_N);

	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	mem[0x4243]	= 0x00;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0, X=0, Y=0
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_Z);
}

TEST_F(CPU6502LogicTest, OraAbs)
{
	mem[0x1234]	= 0x01;
	mem[0x4242]	= CPU6502::INS_ORA_ABS;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x01, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_NONE);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	mem[0x1234]	= 0x2a;
	SetRegisters(cpu, 0x80, 0x00, 0x00);		// preset A=0x80, X=0x00, Y=0x00
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0xaa, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_N);

	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	mem[0x1234]	= 0x00;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_Z);
}

TEST_F(CPU6502LogicTest, OraZp)
{
	mem[0x0040]	= 0x01;
	mem[0x4242]	= CPU6502::INS_ORA_ZP;
	mem[0x4243]	= 0x40;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	int clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x01, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_NONE);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	mem[0x0040]	= 0x2a;
	SetRegisters(cpu, 0x80, 0x00, 0x00);		// preset A=0x80, X=0x00, Y=0x00
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0xaa, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_N);

	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	mem[0x0040]	= 0x00;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x00, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_Z);
}

TEST_F(CPU6502LogicTest, OraIndX)
{
	mem[0x0042]	= 0x34;
	mem[0x0043]	= 0x12;
	mem[0x1234]	= 0x01;
	mem[0x4242]	= CPU6502::INS_ORA_IND_X;
	mem[0x4243]	= 0x40;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0x00, X=0x02, Y=0x00
	int clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x01, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_NONE);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	mem[0x1234]	= 0x2a;
	SetRegisters(cpu, 0x80, 0x02, 0x00);		// preset A=0x80, X=0x02, Y=0x00
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0xaa, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_N);

	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	mem[0x1234]	= 0x00;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0x00, X=0x02, Y=0x00
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_Z);
}

TEST_F(CPU6502LogicTest, OraIndY)
{
	mem[0x0040]	= 0x34;
	mem[0x0041]	= 0x12;
	mem[0x1236]	= 0x01;
	mem[0x4242]	= CPU6502::INS_ORA_IND_Y;
	mem[0x4243]	= 0x40;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x00, 0x00, 0x02);		// preset A=0x00, X=0x00, Y=0x02
	int clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x01, 0x00, 0x02, 0x4244, CPU6502::MSK_SR_NONE);

	std::cerr << "Standard + page break" << std::endl;
	mem[0x0040]	= 0xff;
	mem[0x0041]	= 0x10;
	mem[0x1101]	= 0x01;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x00, 0x02);		// preset A=0x00, X=0x00, Y=0x02
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x01, 0x00, 0x02, 0x4244, CPU6502::MSK_SR_NONE);

	std::cerr << "N-Flag" << std::endl;
	mem[0x0040]	= 0x34;
	mem[0x0041]	= 0x12;
	cpu.Reset();
	mem[0x1236]	= 0x2a;
	SetRegisters(cpu, 0x80, 0x00, 0x02);		// preset A=0x80, X=0x00, Y=0x02
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0xaa, 0x00, 0x02, 0x4244, CPU6502::MSK_SR_N);

	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	mem[0x1236]	= 0x00;
	SetRegisters(cpu, 0x00, 0x00, 0x02);		// preset A=0x00, X=0x00, Y=0x02
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0x00, 0x02, 0x4244, CPU6502::MSK_SR_Z);
}

TEST_F(CPU6502LogicTest, OraZpX)
{
	mem[0x0042]	= 0x01;
	mem[0x4242]	= CPU6502::INS_ORA_ZPX;
	mem[0x4243]	= 0x40;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0x00, X=0x02, Y=0x00
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x01, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_NONE);

	std::cerr << "standard with wrap around" << std::endl;
	cpu.Reset();
	mem[0x002f]	= 0x01;							// 
	SetRegisters(cpu, 0x00, 0xef, 0x00);		// preset A=0, X=0xef, Y=0 (0x40+0xef = 0x01 2f)
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x01, 0xef, 0x00, 0x4244, CPU6502::MSK_SR_NONE);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	mem[0x0042]	= 0x2a;
	SetRegisters(cpu, 0x80, 0x02, 0x00);		// preset A=0x80, X=0x02, Y=0x00
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0xaa, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_N);

	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	mem[0x0042]	= 0x00;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0x00, X=0x02, Y=0x00
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_Z);
}

TEST_F(CPU6502LogicTest, OraAbsX)
{
	mem[0x1236]	= 0x01;
	mem[0x4242]	= CPU6502::INS_ORA_ABS_X;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0x00, X=0x02, Y=0x00
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x01, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_NONE);

	std::cerr << "Standard + page break" << std::endl;
	cpu.Reset();
	mem[0x4243]	= 0xff;
	mem[0x4244]	= 0x10;
	mem[0x1101]	= 0x01;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0x00, X=0x02, Y=0x00
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x01, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_NONE);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;
	mem[0x1236]	= 0x2a;
	SetRegisters(cpu, 0x80, 0x02, 0x00);		// preset A=0x80, X=0x02, Y=0x00
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0xaa, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_N);

	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	mem[0x1236]	= 0x00;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0x00, X=0x02, Y=0x00
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_Z);
}

TEST_F(CPU6502LogicTest, OraAbsY)
{
	mem[0x1236]	= 0x01;
	mem[0x4242]	= CPU6502::INS_ORA_ABS_Y;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x00, 0x00, 0x02);		// preset A=0x00, X=0x00, Y=0x02
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x01, 0x00, 0x02, 0x4245, CPU6502::MSK_SR_NONE);

	std::cerr << "Standard + page break" << std::endl;
	cpu.Reset();
	mem[0x4243]	= 0xff;
	mem[0x4244]	= 0x10;
	mem[0x1101]	= 0x01;
	SetRegisters(cpu, 0x00, 0x00, 0x02);		// preset A=0x00, X=0x00, Y=0x02
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x01, 0x00, 0x02, 0x4245, CPU6502::MSK_SR_NONE);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;
	mem[0x1236]	= 0x2a;
	SetRegisters(cpu, 0x80, 0x00, 0x02);		// preset A=0x00, X=0x00, Y=0x02
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0xaa, 0x00, 0x02, 0x4245, CPU6502::MSK_SR_N);

	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	mem[0x1236]	= 0x00;
	SetRegisters(cpu, 0x00, 0x00, 0x02);		// preset A=0x00, X=0x00, Y=0x02
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x00, 0x02, 0x4245, CPU6502::MSK_SR_Z);
}

//-----------------------------------------------------------------------------
// ROL
//-----------------------------------------------------------------------------
TEST_F(CPU6502LogicTest, RolAbs)
{
	int clocks;

	mem[0x1234]	= 0b00000000;
	mem[0x4242]	= CPU6502::INS_ROL_ABS;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	std::cerr << "M=0x00, C=0" << std::endl;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_Z);
	EXPECT_EQ(mem[0x1234], 0x00);

	std::cerr << "M=0x00, C=1" << std::endl;
	cpu.Reset();
	mem[0x1234]	= 0b00000000;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_NONE);
	EXPECT_EQ(mem[0x1234], 0x01);

	std::cerr << "M=0x80, C=0" << std::endl;
	cpu.Reset();
	mem[0x1234]	= 0b10000000;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_C |  CPU6502::MSK_SR_Z);
	EXPECT_EQ(mem[0x1234], 0x00);

	std::cerr << "M=0x80, C=1" << std::endl;
	cpu.Reset();
	mem[0x1234]	= 0b10000000;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_C);
	EXPECT_EQ(mem[0x1234], 0x01);

	std::cerr << "M=0x40, C=0" << std::endl;
	cpu.Reset();
	mem[0x1234]	= 0b01000000;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_N);
	EXPECT_EQ(mem[0x1234], 0x80);

	std::cerr << "M=0x40, C=1" << std::endl;
	cpu.Reset();
	mem[0x1234]	= 0b01000000;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_N);
	EXPECT_EQ(mem[0x1234], 0x81);

	std::cerr << "M=0xc0, C=0" << std::endl;
	cpu.Reset();
	mem[0x1234]	= 0b11000000;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_N | CPU6502::MSK_SR_C);
	EXPECT_EQ(mem[0x1234], 0x80);

	std::cerr << "M=0xc0, C=1" << std::endl;
	cpu.Reset();
	mem[0x1234]	= 0b11000000;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_N | CPU6502::MSK_SR_C);
	EXPECT_EQ(mem[0x1234], 0x81);
}

TEST_F(CPU6502LogicTest, RolAbsX)
{
	int clocks;

	mem[0x1236]	= 0b00000000;
	mem[0x4242]	= CPU6502::INS_ROL_ABS_X;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	std::cerr << "M=0x00, C=0" << std::endl;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0x00, X=0x02, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(7);
	VerifyRegisters(cpu, 7, 0x00, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_Z);
	EXPECT_EQ(mem[0x1236], 0x00);

	std::cerr << "M=0x00, C=1" << std::endl;
	cpu.Reset();
	mem[0x1236]	= 0b00000000;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0x00, X=0x02, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(7);
	VerifyRegisters(cpu, 7, 0x00, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_NONE);
	EXPECT_EQ(mem[0x1236], 0x01);

	std::cerr << "M=0x80, C=0" << std::endl;
	cpu.Reset();
	mem[0x1236]	= 0b10000000;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(7);
	VerifyRegisters(cpu, 7, 0x00, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_C |  CPU6502::MSK_SR_Z);
	EXPECT_EQ(mem[0x1236], 0x00);

	std::cerr << "M=0x80, C=1" << std::endl;
	cpu.Reset();
	mem[0x1236]	= 0b10000000;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(7);
	VerifyRegisters(cpu, 7, 0x00, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_C);
	EXPECT_EQ(mem[0x1236], 0x01);

	std::cerr << "M=0x40, C=0" << std::endl;
	cpu.Reset();
	mem[0x1236]	= 0b01000000;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(7);
	VerifyRegisters(cpu, 7, 0x00, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_N);
	EXPECT_EQ(mem[0x1236], 0x80);

	std::cerr << "M=0x40, C=1" << std::endl;
	cpu.Reset();
	mem[0x1236]	= 0b01000000;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(7);
	VerifyRegisters(cpu, 7, 0x00, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_N);
	EXPECT_EQ(mem[0x1236], 0x81);

	std::cerr << "M=0xc0, C=0" << std::endl;
	cpu.Reset();
	mem[0x1236]	= 0b11000000;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(7);
	VerifyRegisters(cpu, 7, 0x00, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_N | CPU6502::MSK_SR_C);
	EXPECT_EQ(mem[0x1236], 0x80);

	std::cerr << "M=0xc0, C=1" << std::endl;
	cpu.Reset();
	mem[0x1236]	= 0b11000000;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(7);
	VerifyRegisters(cpu, 7, 0x00, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_N | CPU6502::MSK_SR_C);
	EXPECT_EQ(mem[0x1236], 0x81);
}

TEST_F(CPU6502LogicTest, RolAcc)
{
	int clocks;

	mem[0x4242]	= CPU6502::INS_ROL_ACC;

	std::cerr << "M=0x00, C=0" << std::endl;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0x00, 0x00, 0x4243, CPU6502::MSK_SR_Z);

	std::cerr << "M=0x00, C=1" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x01, 0x00, 0x00, 0x4243, CPU6502::MSK_SR_NONE);

	std::cerr << "M=0x80, C=0" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x80, 0x00, 0x00);		// preset A=0x80, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0x00, 0x00, 0x4243, CPU6502::MSK_SR_C |  CPU6502::MSK_SR_Z);

	std::cerr << "M=0x80, C=1" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x80, 0x00, 0x00);		// preset A=0x80, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x01, 0x00, 0x00, 0x4243, CPU6502::MSK_SR_C);

	std::cerr << "M=0x40, C=0" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x40, 0x00, 0x00);		// preset A=0x40, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x80, 0x00, 0x00, 0x4243, CPU6502::MSK_SR_N);

	std::cerr << "M=0x40, C=1" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x40, 0x00, 0x00);		// preset A=0x40, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x81, 0x00, 0x00, 0x4243, CPU6502::MSK_SR_N);

	std::cerr << "M=0xc0, C=0" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0xc0, 0x00, 0x00);		// preset A=0xc0, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x80, 0x00, 0x00, 0x4243, CPU6502::MSK_SR_N | CPU6502::MSK_SR_C);

	std::cerr << "M=0xc0, C=1" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0xc0, 0x00, 0x00);		// preset A=0xc0, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x81, 0x00, 0x00, 0x4243, CPU6502::MSK_SR_N | CPU6502::MSK_SR_C);
}

TEST_F(CPU6502LogicTest, RolZp)
{
	int clocks;

	mem[0x0040]	= 0x00;
	mem[0x4242]	= CPU6502::INS_ROL_ZP;
	mem[0x4243]	= 0x40;

	std::cerr << "M=0x00, C=0" << std::endl;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_Z);
	EXPECT_EQ(mem[0x0040], 0x00);

	std::cerr << "M=0x00, C=1" << std::endl;
	cpu.Reset();
	mem[0x0040]	= 0b00000000;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_NONE);
	EXPECT_EQ(mem[0x0040], 0x01);

	std::cerr << "M=0x80, C=0" << std::endl;
	cpu.Reset();
	mem[0x0040]	= 0b10000000;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_C |  CPU6502::MSK_SR_Z);
	EXPECT_EQ(mem[0x0040], 0x00);

	std::cerr << "M=0x80, C=1" << std::endl;
	cpu.Reset();
	mem[0x0040]	= 0b10000000;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_C);
	EXPECT_EQ(mem[0x0040], 0x01);

	std::cerr << "M=0x40, C=0" << std::endl;
	cpu.Reset();
	mem[0x0040]	= 0b01000000;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_N);
	EXPECT_EQ(mem[0x0040], 0x80);

	std::cerr << "M=0x40, C=1" << std::endl;
	cpu.Reset();
	mem[0x0040]	= 0b01000000;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_N);
	EXPECT_EQ(mem[0x0040], 0x81);

	std::cerr << "M=0xc0, C=0" << std::endl;
	cpu.Reset();
	mem[0x0040]	= 0b11000000;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_N | CPU6502::MSK_SR_C);
	EXPECT_EQ(mem[0x0040], 0x80);

	std::cerr << "M=0xc0, C=1" << std::endl;
	cpu.Reset();
	mem[0x0040]	= 0b11000000;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_N | CPU6502::MSK_SR_C);
	EXPECT_EQ(mem[0x0040], 0x81);
}

TEST_F(CPU6502LogicTest, RolZpX)
{
	int clocks;

	mem[0x0042]	= 0x00;
	mem[0x4242]	= CPU6502::INS_ROL_ZPX;
	mem[0x4243]	= 0x40;

	std::cerr << "M=0x00, C=0" << std::endl;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0x00, X=0x02, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_Z);
	EXPECT_EQ(mem[0x0042], 0x00);

	std::cerr << "M=0x00, C=1" << std::endl;
	cpu.Reset();
	mem[0x0042]	= 0b00000000;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0x00, X=0x02, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_NONE);
	EXPECT_EQ(mem[0x0042], 0x01);

	std::cerr << "M=0x80, C=0" << std::endl;
	cpu.Reset();
	mem[0x0042]	= 0b10000000;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_C |  CPU6502::MSK_SR_Z);
	EXPECT_EQ(mem[0x0042], 0x00);

	std::cerr << "M=0x80, C=1" << std::endl;
	cpu.Reset();
	mem[0x0042]	= 0b10000000;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_C);
	EXPECT_EQ(mem[0x0042], 0x01);

	std::cerr << "M=0x40, C=0" << std::endl;
	cpu.Reset();
	mem[0x0042]	= 0b01000000;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_N);
	EXPECT_EQ(mem[0x0042], 0x80);

	std::cerr << "M=0x40, C=1" << std::endl;
	cpu.Reset();
	mem[0x0042]	= 0b01000000;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_N);
	EXPECT_EQ(mem[0x0042], 0x81);

	std::cerr << "M=0xc0, C=0" << std::endl;
	cpu.Reset();
	mem[0x0042]	= 0b11000000;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_N | CPU6502::MSK_SR_C);
	EXPECT_EQ(mem[0x0042], 0x80);

	std::cerr << "M=0xc0, C=1" << std::endl;
	cpu.Reset();
	mem[0x0042]	= 0b11000000;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_N | CPU6502::MSK_SR_C);
	EXPECT_EQ(mem[0x0042], 0x81);
}

//-----------------------------------------------------------------------------
// ROR
//-----------------------------------------------------------------------------
TEST_F(CPU6502LogicTest, RorAbs)
{
	int clocks;

	mem[0x1234]	= 0b00000000;
	mem[0x4242]	= CPU6502::INS_ROR_ABS;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	std::cerr << "M=0x00, C=0" << std::endl;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_Z);
	EXPECT_EQ(mem[0x1234], 0x00);

	std::cerr << "M=0x00, C=1" << std::endl;
	cpu.Reset();
	mem[0x1234]	= 0b00000000;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_N);
	EXPECT_EQ(mem[0x1234], 0x80);

	std::cerr << "M=0x01, C=0" << std::endl;
	cpu.Reset();
	mem[0x1234]	= 0b00000001;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_C |  CPU6502::MSK_SR_Z);
	EXPECT_EQ(mem[0x1234], 0x00);

	std::cerr << "M=0x01, C=1" << std::endl;
	cpu.Reset();
	mem[0x1234]	= 0b00000001;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_N | CPU6502::MSK_SR_C);
	EXPECT_EQ(mem[0x1234], 0x80);

	std::cerr << "M=0x02, C=0" << std::endl;
	cpu.Reset();
	mem[0x1234]	= 0b00000010;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_NONE);
	EXPECT_EQ(mem[0x1234], 0x01);

	std::cerr << "M=0x02, C=1" << std::endl;
	cpu.Reset();
	mem[0x1234]	= 0b00000010;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_N);
	EXPECT_EQ(mem[0x1234], 0x81);

	std::cerr << "M=0x03, C=0" << std::endl;
	cpu.Reset();
	mem[0x1234]	= 0b00000011;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_C);
	EXPECT_EQ(mem[0x1234], 0x01);

	std::cerr << "M=0x03, C=1" << std::endl;
	cpu.Reset();
	mem[0x1234]	= 0b00000011;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_N | CPU6502::MSK_SR_C);
	EXPECT_EQ(mem[0x1234], 0x81);
}

TEST_F(CPU6502LogicTest, RorAbsX)
{
	int clocks;

	mem[0x1236]	= 0b00000000;
	mem[0x4242]	= CPU6502::INS_ROR_ABS_X;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	std::cerr << "M=0x00, C=0" << std::endl;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0x00, X=0x02, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(7);
	VerifyRegisters(cpu, 7, 0x00, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_Z);
	EXPECT_EQ(mem[0x1236], 0x00);

	std::cerr << "M=0x00, C=1" << std::endl;
	cpu.Reset();
	mem[0x1236]	= 0b00000000;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0x00, X=0x02, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(7);
	VerifyRegisters(cpu, 7, 0x00, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_N);
	EXPECT_EQ(mem[0x1236], 0x80);

	std::cerr << "M=0x01, C=0" << std::endl;
	cpu.Reset();
	mem[0x1236]	= 0b00000001;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(7);
	VerifyRegisters(cpu, 7, 0x00, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_C | CPU6502::MSK_SR_Z);
	EXPECT_EQ(mem[0x1236], 0x00);

	std::cerr << "M=0x01, C=1" << std::endl;
	cpu.Reset();
	mem[0x1236]	= 0b00000001;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(7);
	VerifyRegisters(cpu, 7, 0x00, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_N | CPU6502::MSK_SR_C);
	EXPECT_EQ(mem[0x1236], 0x80);

	std::cerr << "M=0x02, C=0" << std::endl;
	cpu.Reset();
	mem[0x1236]	= 0b00000010;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(7);
	VerifyRegisters(cpu, 7, 0x00, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_NONE);
	EXPECT_EQ(mem[0x1236], 0x01);

	std::cerr << "M=0x02, C=1" << std::endl;
	cpu.Reset();
	mem[0x1236]	= 0b00000010;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(7);
	VerifyRegisters(cpu, 7, 0x00, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_N);
	EXPECT_EQ(mem[0x1236], 0x81);

	std::cerr << "M=0x03, C=0" << std::endl;
	cpu.Reset();
	mem[0x1236]	= 0b00000011;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(7);
	VerifyRegisters(cpu, 7, 0x00, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_C);
	EXPECT_EQ(mem[0x1236], 0x01);

	std::cerr << "M=0x03, C=1" << std::endl;
	cpu.Reset();
	mem[0x1236]	= 0b00000011;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(7);
	VerifyRegisters(cpu, 7, 0x00, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_N | CPU6502::MSK_SR_C);
	EXPECT_EQ(mem[0x1236], 0x81);
}

TEST_F(CPU6502LogicTest, RorAcc)
{
	int clocks;

	mem[0x4242]	= CPU6502::INS_ROR_ACC;

	std::cerr << "M=0x00, C=0" << std::endl;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0x00, 0x00, 0x4243, CPU6502::MSK_SR_Z);

	std::cerr << "M=0x00, C=1" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x80, 0x00, 0x00, 0x4243, CPU6502::MSK_SR_N);

	std::cerr << "M=0x01, C=0" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x01, 0x00, 0x00);		// preset A=0x01, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0x00, 0x00, 0x4243, CPU6502::MSK_SR_C | CPU6502::MSK_SR_Z);

	std::cerr << "M=0x01, C=1" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x01, 0x00, 0x00);		// preset A=0x01, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x80, 0x00, 0x00, 0x4243, CPU6502::MSK_SR_N | CPU6502::MSK_SR_C);

	std::cerr << "M=0x02, C=0" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x02, 0x00, 0x00);		// preset A=0x02, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x01, 0x00, 0x00, 0x4243, CPU6502::MSK_SR_NONE);

	std::cerr << "M=0x02, C=1" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x02, 0x00, 0x00);		// preset A=0x02, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x81, 0x00, 0x00, 0x4243, CPU6502::MSK_SR_N);

	std::cerr << "M=0x03, C=0" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x03, 0x00, 0x00);		// preset A=0x03, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x01, 0x00, 0x00, 0x4243, CPU6502::MSK_SR_C);

	std::cerr << "M=0x03, C=1" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x03, 0x00, 0x00);		// preset A=0x03, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x81, 0x00, 0x00, 0x4243, CPU6502::MSK_SR_N | CPU6502::MSK_SR_C);
}

TEST_F(CPU6502LogicTest, RorZp)
{
	int clocks;

	mem[0x0040]	= 0x00;
	mem[0x4242]	= CPU6502::INS_ROR_ZP;
	mem[0x4243]	= 0x40;

	std::cerr << "M=0x00, C=0" << std::endl;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_Z);
	EXPECT_EQ(mem[0x0040], 0x00);

	std::cerr << "M=0x00, C=1" << std::endl;
	cpu.Reset();
	mem[0x0040]	= 0b00000000;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_N);
	EXPECT_EQ(mem[0x0040], 0x80);

	std::cerr << "M=0x01, C=0" << std::endl;
	cpu.Reset();
	mem[0x0040]	= 0b00000001;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_C | CPU6502::MSK_SR_Z);
	EXPECT_EQ(mem[0x0040], 0x00);

	std::cerr << "M=0x01, C=1" << std::endl;
	cpu.Reset();
	mem[0x0040]	= 0b00000001;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_N | CPU6502::MSK_SR_C);
	EXPECT_EQ(mem[0x0040], 0x80);

	std::cerr << "M=0x02, C=0" << std::endl;
	cpu.Reset();
	mem[0x0040]	= 0b00000010;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_NONE);
	EXPECT_EQ(mem[0x0040], 0x01);

	std::cerr << "M=0x02, C=1" << std::endl;
	cpu.Reset();
	mem[0x0040]	= 0b00000010;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_N);
	EXPECT_EQ(mem[0x0040], 0x81);

	std::cerr << "M=0x03, C=0" << std::endl;
	cpu.Reset();
	mem[0x0040]	= 0b00000011;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_C);
	EXPECT_EQ(mem[0x0040], 0x01);

	std::cerr << "M=0x03, C=1" << std::endl;
	cpu.Reset();
	mem[0x0040]	= 0b00000011;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_N | CPU6502::MSK_SR_C);
	EXPECT_EQ(mem[0x0040], 0x81);
}

TEST_F(CPU6502LogicTest, RorZpX)
{
	int clocks;

	mem[0x0042]	= 0x00;
	mem[0x4242]	= CPU6502::INS_ROR_ZPX;
	mem[0x4243]	= 0x40;

	std::cerr << "M=0x00, C=0" << std::endl;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0x00, X=0x02, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_Z);
	EXPECT_EQ(mem[0x0042], 0x00);

	std::cerr << "M=0x00, C=1" << std::endl;
	cpu.Reset();
	mem[0x0042]	= 0b00000000;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0x00, X=0x02, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_N);
	EXPECT_EQ(mem[0x0042], 0x80);

	std::cerr << "M=0x01, C=0" << std::endl;
	cpu.Reset();
	mem[0x0042]	= 0b00000001;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_C | CPU6502::MSK_SR_Z);
	EXPECT_EQ(mem[0x0042], 0x00);

	std::cerr << "M=0x01, C=1" << std::endl;
	cpu.Reset();
	mem[0x0042]	= 0b00000001;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_N | CPU6502::MSK_SR_C);
	EXPECT_EQ(mem[0x0042], 0x80);

	std::cerr << "M=0x02, C=0" << std::endl;
	cpu.Reset();
	mem[0x0042]	= 0b00000010;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_NONE);
	EXPECT_EQ(mem[0x0042], 0x01);

	std::cerr << "M=0x02, C=1" << std::endl;
	cpu.Reset();
	mem[0x0042]	= 0b00000010;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_N);
	EXPECT_EQ(mem[0x0042], 0x81);

	std::cerr << "M=0x03, C=0" << std::endl;
	cpu.Reset();
	mem[0x0042]	= 0b00000011;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_C);
	EXPECT_EQ(mem[0x0042], 0x01);

	std::cerr << "M=0x03, C=1" << std::endl;
	cpu.Reset();
	mem[0x0042]	= 0b00000011;
	SetRegisters(cpu, 0x00, 0x02, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_N | CPU6502::MSK_SR_C);
	EXPECT_EQ(mem[0x0042], 0x81);
}

