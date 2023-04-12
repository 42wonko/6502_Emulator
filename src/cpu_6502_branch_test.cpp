#include "cpu_6502_branch_test.h"

TEST_F(CPU6502BranchTest, BccRel)
{
	mem[0x4242]	= CPU6502::INS_BCC_REL;
	mem[0x4243]	= 0x7f;
	
	std::cerr << "BCC not taken" << std::endl;
	SetRegisters(cpu, 0, 0, 0);		// preset A=0, X=0, Y=0
	cpu.SetSR(CPU6502::MSK_SR_C);
	int clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0, 0, 0, 0x4244, CPU6502::MSK_SR_C);
	
	std::cerr << "BCC forward" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0, 0, 0, 0x42c3, CPU6502::MSK_SR_NONE);
	
	std::cerr << "BCC backwards" << std::endl;
	mem[0x4243]	= 0x80;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0, 0, 0, 0x41c4, CPU6502::MSK_SR_NONE);
}

TEST_F(CPU6502BranchTest, BcsRel)
{
	mem[0x4242]	= CPU6502::INS_BCS_REL;
	mem[0x4243]	= 0x7f;
	
	std::cerr << "BCS not taken" << std::endl;
	SetRegisters(cpu, 0, 0, 0);		// preset A=0, X=0, Y=0
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	int clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0, 0, 0, 0x4244, CPU6502::MSK_SR_NONE);
	
	std::cerr << "BCS forward" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0, 0, 0, 0x42c3, CPU6502::MSK_SR_C);
	
	std::cerr << "BCS backwards" << std::endl;
	mem[0x4243]	= 0x80;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_C);
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0, 0, 0, 0x41c4, CPU6502::MSK_SR_C);
}

TEST_F(CPU6502BranchTest, BeqRel)
{
	mem[0x4242]	= CPU6502::INS_BEQ_REL;
	mem[0x4243]	= 0x7f;
	
	std::cerr << "BEQ not taken" << std::endl;
	SetRegisters(cpu, 0, 0, 0);		// preset A=0, X=0, Y=0
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	int clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0, 0, 0, 0x4244, CPU6502::MSK_SR_NONE);
	
	std::cerr << "BEQ forward" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_Z);
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0, 0, 0, 0x42c3, CPU6502::MSK_SR_Z);
	
	std::cerr << "BEQ backwards" << std::endl;
	mem[0x4243]	= 0x80;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_Z);
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0, 0, 0, 0x41c4, CPU6502::MSK_SR_Z);
}

TEST_F(CPU6502BranchTest, BneRel)
{
	mem[0x4242]	= CPU6502::INS_BNE_REL;
	mem[0x4243]	= 0x7f;
	
	std::cerr << "BNE not taken" << std::endl;
	SetRegisters(cpu, 0, 0, 0);		// preset A=0, X=0, Y=0
	cpu.SetSR(CPU6502::MSK_SR_Z);
	int clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0, 0, 0, 0x4244, CPU6502::MSK_SR_Z);
	
	std::cerr << "BNE forward" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0, 0, 0, 0x42c3, CPU6502::MSK_SR_NONE);
	
	std::cerr << "BNE backwards" << std::endl;
	mem[0x4243]	= 0x80;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0, 0, 0, 0x41c4, CPU6502::MSK_SR_NONE);
}

TEST_F(CPU6502BranchTest, BmiRel)
{
	mem[0x4242]	= CPU6502::INS_BMI_REL;
	mem[0x4243]	= 0x7f;
	
	std::cerr << "BMI not taken" << std::endl;
	SetRegisters(cpu, 0, 0, 0);		// preset A=0, X=0, Y=0
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	int clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0, 0, 0, 0x4244, CPU6502::MSK_SR_NONE);
	
	std::cerr << "BMI forward" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_N);
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0, 0, 0, 0x42c3, CPU6502::MSK_SR_N);
	
	std::cerr << "BMI backwards" << std::endl;
	mem[0x4243]	= 0x80;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_N);
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0, 0, 0, 0x41c4, CPU6502::MSK_SR_N);
}

TEST_F(CPU6502BranchTest, BplRel)
{
	mem[0x4242]	= CPU6502::INS_BPL_REL;
	mem[0x4243]	= 0x7f;
	
	std::cerr << "BPL not taken" << std::endl;
	SetRegisters(cpu, 0, 0, 0);		// preset A=0, X=0, Y=0
	cpu.SetSR(CPU6502::MSK_SR_N);
	int clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0, 0, 0, 0x4244, CPU6502::MSK_SR_N);
	
	std::cerr << "BPL forward" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0, 0, 0, 0x42c3, CPU6502::MSK_SR_NONE);
	
	std::cerr << "BPL backwards" << std::endl;
	mem[0x4243]	= 0x80;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0, 0, 0, 0x41c4, CPU6502::MSK_SR_NONE);
}

TEST_F(CPU6502BranchTest, BvcRel)
{
	mem[0x4242]	= CPU6502::INS_BVC_REL;
	mem[0x4243]	= 0x7f;
	
	std::cerr << "BVC not taken" << std::endl;
	SetRegisters(cpu, 0, 0, 0);		// preset A=0, X=0, Y=0
	cpu.SetSR(CPU6502::MSK_SR_V);
	int clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0, 0, 0, 0x4244, CPU6502::MSK_SR_V);
	
	std::cerr << "BVC forward" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0, 0, 0, 0x42c3, CPU6502::MSK_SR_NONE);
	
	std::cerr << "BVC backwards" << std::endl;
	mem[0x4243]	= 0x80;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0, 0, 0, 0x41c4, CPU6502::MSK_SR_NONE);
}

TEST_F(CPU6502BranchTest, BvsRel)
{
	mem[0x4242]	= CPU6502::INS_BVS_REL;
	mem[0x4243]	= 0x7f;
	
	std::cerr << "BVS not taken" << std::endl;
	SetRegisters(cpu, 0, 0, 0);		// preset A=0, X=0, Y=0
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	int clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0, 0, 0, 0x4244, CPU6502::MSK_SR_NONE);
	
	std::cerr << "BVS forward" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_V);
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0, 0, 0, 0x42c3, CPU6502::MSK_SR_V);
	
	std::cerr << "BVS backwards" << std::endl;
	mem[0x4243]	= 0x80;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_V);
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0, 0, 0, 0x41c4, CPU6502::MSK_SR_V);
}

TEST_F(CPU6502BranchTest, JsrAbs)
{
	mem[0x4242]	= CPU6502::INS_JSR_ABS;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	Byte sp = cpu.GetSP();
	SetRegisters(cpu, 0, 0, 0);		// preset A=0, X=0, Y=0
	int clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0, 0, 0, 0x1234, CPU6502::MSK_SR_NONE);
	EXPECT_EQ(cpu.GetSP(), sp-2);
	EXPECT_EQ(mem[0x01fe], 0x44);
	EXPECT_EQ(mem[0x01ff], 0x42);
}

TEST_F(CPU6502BranchTest, BrkImp)
{
	mem[0x4242]	= CPU6502::INS_BRK_IMP;
	mem[0xfffe]	= 0x34;
	mem[0xffff]	= 0x12;

	Byte sp = cpu.GetSP();
	SetRegisters(cpu, 0, 0, 0);		// preset A=0, X=0, Y=0
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	int clocks = cpu.Run(7);
	VerifyRegisters(cpu, 7, 0, 0, 0, 0x1234, CPU6502::MSK_SR_I);
	EXPECT_EQ(cpu.GetSP(), sp-3);	// on word address + one byte status register
	EXPECT_EQ(mem[0x01fe], 0x44);	// although BRK is just one byte the PC in incremented by ...
	EXPECT_EQ(mem[0x01ff], 0x42);	// ... two before being pushed on the stack
	EXPECT_TRUE((mem[0x01fd] & CPU6502::MSK_SR_B));
	EXPECT_TRUE((mem[0x01fd] & CPU6502::MSK_SR_U));
	EXPECT_TRUE(cpu.GetSR() & CPU6502::MSK_SR_I);
}

TEST_F(CPU6502BranchTest, ClcImp)
{
	mem[0x4242] = CPU6502::INS_CLC_IMP;
	SetRegisters(cpu, 0, 0, 0);		// preset A=0, X=0, Y=0
	cpu.SetSR(CPU6502::MSK_SR_C);
	int clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0, 0, 0, 0x4243, CPU6502::MSK_SR_NONE);
}

TEST_F(CPU6502BranchTest, CldImp)
{
	mem[0x4242] = CPU6502::INS_CLD_IMP;
	SetRegisters(cpu, 0, 0, 0);		// preset A=0, X=0, Y=0
	cpu.SetSR(CPU6502::MSK_SR_D);
	int clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0, 0, 0, 0x4243, CPU6502::MSK_SR_NONE);
}

TEST_F(CPU6502BranchTest, CliImp)
{
	mem[0x4242] = CPU6502::INS_CLI_IMP;
	SetRegisters(cpu, 0, 0, 0);		// preset A=0, X=0, Y=0
	cpu.SetSR(CPU6502::MSK_SR_I);
	int clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0, 0, 0, 0x4243, CPU6502::MSK_SR_NONE);
}

TEST_F(CPU6502BranchTest, ClvImp)
{
	mem[0x4242] = CPU6502::INS_CLV_IMP;
	SetRegisters(cpu, 0, 0, 0);		// preset A=0, X=0, Y=0
	cpu.SetSR(CPU6502::MSK_SR_V);
	int clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0, 0, 0, 0x4243, CPU6502::MSK_SR_NONE);
}

TEST_F(CPU6502BranchTest, CmpImm)
{
	mem[0x4242]	= CPU6502::INS_CMP_IM;
	mem[0x4243]	= 0x7e;

	std::cerr << "Z-Flag C-Flag" << std::endl;
	SetRegisters(cpu, 0x7e, 0, 0);		// preset A=0x7f, X=0, Y=0
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	int clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x7e, 0, 0, 0x4244, CPU6502::MSK_SR_Z | CPU6502::MSK_SR_C);

	std::cerr << "C-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x7f, 0, 0);		// preset A=0, X=0, Y=0
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x7f, 0, 0, 0x4244, CPU6502::MSK_SR_C);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x7d, 0, 0);		// preset A=0, X=0, Y=0
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x7d, 0, 0, 0x4244, CPU6502::MSK_SR_N);
}

TEST_F(CPU6502BranchTest, CmpAbs)
{
	mem[0x1234]	= 0x7e;
	mem[0x4242]	= CPU6502::INS_CMP_ABS;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	std::cerr << "Z-Flag C-Flag" << std::endl;
	SetRegisters(cpu, 0x7e, 0, 0);		// preset A=0x7f, X=0, Y=0
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x7e, 0, 0, 0x4245, CPU6502::MSK_SR_Z | CPU6502::MSK_SR_C);

	std::cerr << "C-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x7f, 0, 0);		// preset A=0, X=0, Y=0
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x7f, 0, 0, 0x4245, CPU6502::MSK_SR_C);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x7d, 0, 0);		// preset A=0, X=0, Y=0
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x7d, 0, 0, 0x4245, CPU6502::MSK_SR_N);
}

TEST_F(CPU6502BranchTest, CmpZp)
{
	mem[0x0040]	= 0x7e;
	mem[0x4242]	= CPU6502::INS_CMP_ZP;
	mem[0x4243]	= 0x40;

	std::cerr << "Z-Flag C-Flag" << std::endl;
	SetRegisters(cpu, 0x7e, 0, 0);		// preset A=0x7f, X=0, Y=0
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	int clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x7e, 0, 0, 0x4244, CPU6502::MSK_SR_Z | CPU6502::MSK_SR_C);

	std::cerr << "C-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x7f, 0, 0);		// preset A=0, X=0, Y=0
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x7f, 0, 0, 0x4244, CPU6502::MSK_SR_C);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x7d, 0, 0);		// preset A=0, X=0, Y=0
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x7d, 0, 0, 0x4244, CPU6502::MSK_SR_N);
}

TEST_F(CPU6502BranchTest, CmpIndX)
{
	mem[0x0042]	= 0x34;
	mem[0x0043]	= 0x12;
	mem[0x1234]	= 0x7e;
	mem[0x4242]	= CPU6502::INS_CMP_IND_X;
	mem[0x4243]	= 0x40;

	std::cerr << "Z-Flag C-Flag" << std::endl;
	SetRegisters(cpu, 0x7e, 0x02, 0x00);		// preset A=0x7f, X=2, Y=0
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	int clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x7e, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_Z | CPU6502::MSK_SR_C);

	std::cerr << "C-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x7f, 0x02, 0x00);		// preset A=0, X=2, Y=0
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x7f, 0x02, 0, 0x4244, CPU6502::MSK_SR_C);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x7d, 0x02, 0x00);		// preset A=0, X=2, Y=0
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x7d, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_N);
}

TEST_F(CPU6502BranchTest, CmpIndY)
{
	mem[0x0040]	= 0x34;
	mem[0x0041]	= 0x12;
	mem[0x1236]	= 0x7e;
	mem[0x4242]	= CPU6502::INS_CMP_IND_Y;
	mem[0x4243]	= 0x40;

	std::cerr << "Z-Flag C-Flag" << std::endl;
	SetRegisters(cpu, 0x7e, 0x00, 0x02);		// preset A=0x7f, X=0, Y=2
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	int clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x7e, 0x00, 0x02, 0x4244, CPU6502::MSK_SR_Z | CPU6502::MSK_SR_C);

	mem[0x0040]	= 0xff;
	mem[0x0041]	= 0x10;
	mem[0x1101]	= 0x7e;
	std::cerr << "Z-Flag C-Flag and page break" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x7e, 0x00, 0x02);		// preset A=0x7f, X=0, Y=2
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x7e, 0x00, 0x02, 0x4244, CPU6502::MSK_SR_Z | CPU6502::MSK_SR_C);

	mem[0x0040]	= 0x34;
	mem[0x0041]	= 0x12;
	mem[0x1236]	= 0x7e;
	std::cerr << "C-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x7f, 0x00, 0x02);		// preset A=0, X=0, Y=2
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x7f, 0x00, 0x02, 0x4244, CPU6502::MSK_SR_C);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x7d, 0x00, 0x02);		// preset A=0, X=0, Y=2
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x7d, 0x00, 0x02, 0x4244, CPU6502::MSK_SR_N);
}

TEST_F(CPU6502BranchTest, CmpZpX)
{
	mem[0x0042]	= 0x7e;
	mem[0x4242]	= CPU6502::INS_CMP_ZPX;
	mem[0x4243]	= 0x40;

	std::cerr << "Z-Flag C-Flag" << std::endl;
	SetRegisters(cpu, 0x7e, 2, 0);		// preset A=0x7f, X=0, Y=0
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x7e, 2, 0, 0x4244, CPU6502::MSK_SR_Z | CPU6502::MSK_SR_C);

	std::cerr << "C-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x7f, 2, 0);		// preset A=0, X=0, Y=0
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x7f, 2, 0, 0x4244, CPU6502::MSK_SR_C);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x7d, 2, 0);		// preset A=0, X=0, Y=0
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x7d, 2, 0, 0x4244, CPU6502::MSK_SR_N);
}

TEST_F(CPU6502BranchTest, CmpAbsX)
{
	mem[0x1236]	= 0x7e;
	mem[0x4242]	= CPU6502::INS_CMP_ABS_X;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	std::cerr << "Z-Flag C-Flag" << std::endl;
	SetRegisters(cpu, 0x7e, 0x02, 0x00);		// preset A=0x7f, X=2, Y=0
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x7e, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_Z | CPU6502::MSK_SR_C);

	mem[0x1101]	= 0x7e;
	mem[0x4243]	= 0xff;
	mem[0x4244]	= 0x10;
	std::cerr << "Z-Flag C-Flag and page break" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x7e, 0x02, 0x00);		// preset A=0x7f, X=2, Y=0
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x7e, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_Z | CPU6502::MSK_SR_C);

	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;
	std::cerr << "C-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x7f, 0x02, 0x00);		// preset A=0, X=2, Y=0
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x7f, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_C);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x7d, 0x02, 0x00);		// preset A=0, X=2, Y=0
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x7d, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_N);
}

TEST_F(CPU6502BranchTest, CmpAbsY)
{
	mem[0x1236]	= 0x7e;
	mem[0x4242]	= CPU6502::INS_CMP_ABS_Y;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	std::cerr << "Z-Flag C-Flag" << std::endl;
	SetRegisters(cpu, 0x7e, 0x00, 0x02);		// preset A=0x7f, X=0, Y=2
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x7e, 0x00, 0x02, 0x4245, CPU6502::MSK_SR_Z | CPU6502::MSK_SR_C);

	mem[0x1101]	= 0x7e;
	mem[0x4243]	= 0xff;
	mem[0x4244]	= 0x10;
	std::cerr << "Z-Flag C-Flag and page break" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x7e, 0x00, 0x02);		// preset A=0x7f, X=0, Y=2
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x7e, 0x00, 0x02, 0x4245, CPU6502::MSK_SR_Z | CPU6502::MSK_SR_C);

	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;
	std::cerr << "C-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x7f, 0x00, 0x02);		// preset A=0x7f, X=0, Y=2
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x7f, 0x00, 0x02, 0x4245, CPU6502::MSK_SR_C);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x7d, 0x00, 0x02);		// preset A=0x7f, X=0, Y=2
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x7d, 0x00, 0x02, 0x4245, CPU6502::MSK_SR_N);
}

TEST_F(CPU6502BranchTest, CpxImm)
{
	mem[0x4242]	= CPU6502::INS_CPX_IM;
	mem[0x4243]	= 0x7e;

	std::cerr << "Z-Flag C-Flag" << std::endl;
	SetRegisters(cpu, 0x00, 0x7e, 0x00);		// preset A=0x00, X=0x7e, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	int clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0x7e, 0x00, 0x4244, CPU6502::MSK_SR_Z | CPU6502::MSK_SR_C);

	std::cerr << "C-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x7f, 0x00);		// preset A=0x00, X=0x7f, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0x7f, 0x00, 0x4244, CPU6502::MSK_SR_C);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x7d, 0x00);		// preset A=0x00, X=0x7d, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0x7d, 0x00, 0x4244, CPU6502::MSK_SR_N);
}

TEST_F(CPU6502BranchTest, CpxAbs)
{
	mem[0x1234]	= 0x7e;
	mem[0x4242]	= CPU6502::INS_CPX_ABS;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	std::cerr << "Z-Flag C-Flag" << std::endl;
	SetRegisters(cpu, 0x00, 0x7e, 0);		// preset A=0x00, X=0x7e, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x7e, 0, 0x4245, CPU6502::MSK_SR_Z | CPU6502::MSK_SR_C);

	std::cerr << "C-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x7f, 0);		// preset A=0x00, X=0x7f, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x7f, 0, 0x4245, CPU6502::MSK_SR_C);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x7d, 0);		// preset A=0x00, X=0x7d, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x7d, 0, 0x4245, CPU6502::MSK_SR_N);
}

TEST_F(CPU6502BranchTest, CpxZp)
{
	mem[0x0040]	= 0x7e;
	mem[0x4242]	= CPU6502::INS_CPX_ZP;
	mem[0x4243]	= 0x40;

	std::cerr << "Z-Flag C-Flag" << std::endl;
	SetRegisters(cpu, 0x00, 0x7e, 0x00);		// preset A=0x00, X=0x7e, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	int clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x00, 0x7e, 0x00, 0x4244, CPU6502::MSK_SR_Z | CPU6502::MSK_SR_C);

	std::cerr << "C-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x7f, 0x00);		// preset A=0x00, X=0x7f, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x00, 0x7f, 0x00, 0x4244, CPU6502::MSK_SR_C);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x7d, 0x00);		// preset A=0x00, X=0x7d, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x00, 0x7d, 0, 0x4244, CPU6502::MSK_SR_N);
}

TEST_F(CPU6502BranchTest, CpyImm)
{
	mem[0x4242]	= CPU6502::INS_CPY_IM;
	mem[0x4243]	= 0x7e;

	std::cerr << "Z-Flag C-Flag" << std::endl;
	SetRegisters(cpu, 0x00, 0x00, 0x7e);		// preset A=0x00, X=0x00, Y=0x7e
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	int clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0x00, 0x7e, 0x4244, CPU6502::MSK_SR_Z | CPU6502::MSK_SR_C);

	std::cerr << "C-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x00, 0x7f);		// preset A=0x00, X=0x00, Y=0x7f
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0x00, 0x7f, 0x4244, CPU6502::MSK_SR_C);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x00, 0x7d);		// preset A=0x00, X=0x00, Y=0x7d
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0x00, 0x7d, 0x4244, CPU6502::MSK_SR_N);
}

TEST_F(CPU6502BranchTest, CpyAbs)
{
	mem[0x1234]	= 0x7e;
	mem[0x4242]	= CPU6502::INS_CPY_ABS;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	std::cerr << "Z-Flag C-Flag" << std::endl;
	SetRegisters(cpu, 0x00, 0x00, 0x7e);		// preset A=0x00, X=0x00, Y=0x7e
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x00, 0x7e, 0x4245, CPU6502::MSK_SR_Z | CPU6502::MSK_SR_C);

	std::cerr << "C-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x00, 0x7f);		// preset A=0x00, X=0x00, Y=0x7f
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x00, 0x7f, 0x4245, CPU6502::MSK_SR_C);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x00, 0x7d);		// preset A=0x00, X=0x00, Y=0x7d
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x00, 0x7d, 0x4245, CPU6502::MSK_SR_N);
}

TEST_F(CPU6502BranchTest, CpyZp)
{
	mem[0x0040]	= 0x7e;
	mem[0x4242]	= CPU6502::INS_CPY_ZP;
	mem[0x4243]	= 0x40;

	std::cerr << "Z-Flag C-Flag" << std::endl;
	SetRegisters(cpu, 0x00, 0x00, 0x7e);		// preset A=0x00, X=0x00, Y=0x7e
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	int clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x00, 0x00, 0x7e, 0x4244, CPU6502::MSK_SR_Z | CPU6502::MSK_SR_C);

	std::cerr << "C-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x00, 0x7f);		// preset A=0x00, X=0x00, Y=0x7f
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x00, 0x00, 0x7f, 0x4244, CPU6502::MSK_SR_C);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x00, 0x7d);		// preset A=0x00, X=0x00, Y=0x7d
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x00, 0x00, 0x7d, 0x4244, CPU6502::MSK_SR_N);
}

TEST_F(CPU6502BranchTest, JmpAbs)
{
	mem[0x4242]	= CPU6502::INS_JMP_ABS;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	int clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x00, 0x00, 0x00, 0x1234, CPU6502::MSK_SR_NONE);
}

TEST_F(CPU6502BranchTest, JmpInd)
{
	std::cerr << "normal - no page break" << std::endl;
	mem[0x1234]	= 0x21;
	mem[0x1235]	= 0x43;
	mem[0x4242]	= CPU6502::INS_JMP_IND;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	int clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0x00, 0x00, 0x4321, CPU6502::MSK_SR_NONE);

	std::cerr << "bug - page break" << std::endl;
	mem[0x12ff]	= 0x21;
	mem[0x1200]	= 0x43;
	mem[0x4243]	= 0xff;
	mem[0x4244]	= 0x12;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0x00, 0x00, 0x4321, CPU6502::MSK_SR_NONE);
}

TEST_F(CPU6502BranchTest, RtiImp)
{
	int clocks;

	mem[0x4242]	= CPU6502::INS_RTI_IMP;
	cpu.SetSP(0xef);
	Byte cSP = cpu.GetSP();
	mem[0x0100 + cSP + 1]	= 0xff;
	mem[0x0100 + cSP + 2]	= 0x34;
	mem[0x0100 + cSP + 3]	= 0x12;

	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x00, 0x00, 0x1234, 0b11001111);
	EXPECT_EQ(cSP, cpu.GetSP() - 3);
}

TEST_F(CPU6502BranchTest, RtsImp)
{
	int clocks;

	mem[0x4242]	= CPU6502::INS_RTS_IMP;
	cpu.SetSP(0xef);
	Byte cSP = cpu.GetSP();
	mem[0x0100 + cSP + 1]	= 0x34;
	mem[0x0100 + cSP + 2]	= 0x12;

	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x00, 0x00, 0x1235, CPU6502::MSK_SR_NONE);	// we expect PC+1 as new PC
	EXPECT_EQ(cSP, cpu.GetSP() - 2);
}

TEST_F(CPU6502BranchTest, SecImp)
{
	int clocks;

	mem[0x4242]	= CPU6502::INS_SEC_IMP;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0x00, 0x00, 0x4243, CPU6502::MSK_SR_C);	//
}

TEST_F(CPU6502BranchTest, SedImp)
{
	int clocks;

	mem[0x4242]	= CPU6502::INS_SED_IMP;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0x00, 0x00, 0x4243, CPU6502::MSK_SR_D);	//
}

TEST_F(CPU6502BranchTest, SeiImp)
{
	int clocks;

	mem[0x4242]	= CPU6502::INS_SEI_IMP;
	SetRegisters(cpu, 0x00, 0x00, 0x00);		// preset A=0x00, X=0x00, Y=0x00
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0x00, 0x00, 0x4243, CPU6502::MSK_SR_I);	//
}
