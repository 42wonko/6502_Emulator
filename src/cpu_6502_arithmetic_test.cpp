#include "cpu_6502_arithmetic_test.h"

TEST_F(CPU6502ArithmeticTest, AdcIm)
{
	mem[0x4242]	= CPU6502::INS_ADC_IM;
	mem[0x4243]	= 0x55;

	std::cerr << "Standard" << std::endl;
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	SetRegisters(cpu, 5, 0, 0);
	int clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x5a, 0, 0, 0x4244, CPU6502::MSK_SR_NONE);

	mem[0x4243]	= 0x00;
	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	SetRegisters(cpu, 0, 0, 0);
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0, 0, 0x4244, CPU6502::MSK_SR_Z);

	mem[0x4243]	= 0x01;
	std::cerr << "N-Flag 1" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	SetRegisters(cpu, 0x7f, 0, 0);
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x80, 0, 0, 0x4244, CPU6502::MSK_SR_N|CPU6502::MSK_SR_V);

	mem[0x4243]	= 0xff;
	std::cerr << "N-Flag 2" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	SetRegisters(cpu, 0x80, 0, 0);
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x7f, 0, 0, 0x4244, CPU6502::MSK_SR_C|CPU6502::MSK_SR_V);

	mem[0x4243]	= 0xff;
	std::cerr << "N-Flag 3" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_NONE);
	SetRegisters(cpu, 0x01, 0, 0);
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0, 0, 0x4244, CPU6502::MSK_SR_C|CPU6502::MSK_SR_Z);
}

TEST_F(CPU6502ArithmeticTest, AdcAbs)
{
	mem[0x1234] = 0x55;
	mem[0x4242]	= CPU6502::INS_ADC_ABS;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x05, 0, 0);
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x5a, 0, 0, 0x4245, CPU6502::MSK_SR_NONE);

	mem[0x1234]	= 0x00;
	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0, 0);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0, 0, 0x4245, CPU6502::MSK_SR_Z);

	mem[0x1234]	= 0x01;
	std::cerr << "N-Flag 1" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x7f, 0, 0);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x80, 0, 0, 0x4245, CPU6502::MSK_SR_N | CPU6502::MSK_SR_V);

	mem[0x1234]	= 0xff;
	std::cerr << "N-Flag 2" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x80, 0, 0);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x7f, 0, 0, 0x4245, CPU6502::MSK_SR_C | CPU6502::MSK_SR_V);

	mem[0x1234]	= 0xff;
	std::cerr << "N-Flag 3" << std::endl;
	cpu.Reset();
	cpu.SetA(0x01);
	SetRegisters(cpu, 0x01, 0, 0);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0, 0, 0x4245, CPU6502::MSK_SR_C | CPU6502::MSK_SR_Z);
}

TEST_F(CPU6502ArithmeticTest, AdcZp)
{
	mem[0x0042] = 0x55;
	mem[0x4242]	= CPU6502::INS_ADC_ZP;
	mem[0x4243]	= 0x42;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x05, 0, 0);
	int clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x5a, 0, 0, 0x4244, CPU6502::MSK_SR_NONE);

	mem[0x0042]	= 0x00;
	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0, 0);
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x00, 0, 0, 0x4244, CPU6502::MSK_SR_Z);

	mem[0x0042]	= 0x01;
	std::cerr << "N-Flag 1" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x7f, 0, 0);
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x80, 0, 0, 0x4244, CPU6502::MSK_SR_N | CPU6502::MSK_SR_V);

	mem[0x0042]	= 0xff;
	std::cerr << "N-Flag 2" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x80, 0, 0);
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x7f, 0, 0, 0x4244, CPU6502::MSK_SR_C | CPU6502::MSK_SR_V);

	mem[0x0042]	= 0xff;
	std::cerr << "N-Flag 3" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x01, 0, 0);
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x00, 0, 0, 0x4244, CPU6502::MSK_SR_C | CPU6502::MSK_SR_Z);
}

TEST_F(CPU6502ArithmeticTest, AdcZpX)
{
	mem[0x0042] = 0x55;
	mem[0x4242]	= CPU6502::INS_ADC_ZPX;
	mem[0x4243]	= 0x40;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x05, 0x02, 0x00);
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x5a, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_NONE);

	mem[0x0042]	= 0x00;
	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x02, 0x00);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_Z);

	mem[0x0042]	= 0x01;
	std::cerr << "N-Flag, V-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x7f, 0x02, 0x00);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x80, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_N | CPU6502::MSK_SR_V);

	mem[0x0042]	= 0xff;
	std::cerr << "C-Flag, V-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x80, 0x02, 0x00);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x7f, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_C | CPU6502::MSK_SR_V);

	mem[0x0042]	= 0xff;
	std::cerr << "C-Flag, Z-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x01, 0x02, 0x00);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_C | CPU6502::MSK_SR_Z);
}

TEST_F(CPU6502ArithmeticTest, AdcIndX)
{
	mem[0x0042]	= 0x34;
	mem[0x0043]	= 0x12;
	mem[0x1234]	= 0x55;
	mem[0x4242]	= CPU6502::INS_ADC_IND_X;
	mem[0x4243]	= 0x40;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 5, 2, 0);		// preset A=5, X=2
	cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x5a, 2, 0, 0x4244, CPU6502::MSK_SR_NONE);

	std::cerr << "C-Flag" << std::endl;
	cpu.Reset();
	mem[0x1234]	= 0xff;
	SetRegisters(cpu, 1, 2, 0);		// preset A=1, X=2
	cpu.SetSR(CPU6502::MSK_SR_I|CPU6502::MSK_SR_B|CPU6502::MSK_SR_V|CPU6502::MSK_SR_N);
	cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 2, 0, 0x4244, CPU6502::MSK_SR_I|CPU6502::MSK_SR_B|CPU6502::MSK_SR_Z|CPU6502::MSK_SR_C);

	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	mem[0x1234]	= 0x00;
	SetRegisters(cpu, 0, 2, 0);		// preset A=0, X=2
	cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 2, 0, 0x4244, CPU6502::MSK_SR_Z);

	std::cerr << "V-Flag" << std::endl;
	cpu.Reset();
	mem[0x1234]	= 0xff;
	SetRegisters(cpu, 0x80, 2, 0);		// preset A=0x80, X=2
	cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x7f, 2, 0, 0x4244, CPU6502::MSK_SR_C|CPU6502::MSK_SR_V);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	mem[0x1234]	= 0x01;
	SetRegisters(cpu, 0x7f, 2, 0);		// preset A=0x7f, X=2
	cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x80, 2, 0, 0x4244, CPU6502::MSK_SR_N|CPU6502::MSK_SR_V);
}

TEST_F(CPU6502ArithmeticTest, AdcIndY)
{
	mem[0x0040]	= 0x32;
	mem[0x0041]	= 0x12;
	mem[0x1234]	= 0x55;
	mem[0x4242]	= CPU6502::INS_ADC_IND_Y;
	mem[0x4243]	= 0x40;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 5, 0, 2);		// preset A=5, Y=2
	cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x5a, 0, 2, 0x4244, CPU6502::MSK_SR_NONE);

	std::cerr << "Standard + page break" << std::endl;
	cpu.Reset();
	mem[0x0040]	= 0xff;
	mem[0x0041]	= 0x10;
	mem[0x1100]	= 0x55;
	SetRegisters(cpu, 5, 0, 1);		// preset A=5, Y=1
	cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x5a, 0, 1, 0x4244, CPU6502::MSK_SR_NONE);

	std::cerr << "C-Flag" << std::endl;
	cpu.Reset();
	mem[0x0040]	= 0x32;
	mem[0x0041]	= 0x12;
	mem[0x1234]	= 0xff;
	SetRegisters(cpu, 1, 0, 2);		// preset A=1, Y=2
	cpu.SetSR(CPU6502::MSK_SR_I|CPU6502::MSK_SR_B|CPU6502::MSK_SR_V|CPU6502::MSK_SR_N);
	cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0, 2, 0x4244, CPU6502::MSK_SR_I|CPU6502::MSK_SR_B|CPU6502::MSK_SR_Z|CPU6502::MSK_SR_C);

	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	mem[0x1234]	= 0x00;
	SetRegisters(cpu, 0, 0, 2);		// preset A=0, Y=2
	cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0, 2, 0x4244, CPU6502::MSK_SR_Z);

	std::cerr << "V-Flag" << std::endl;
	cpu.Reset();
	mem[0x1234]	= 0xff;
	SetRegisters(cpu, 0x80, 0, 2);		// preset A=0x80, Y=2
	cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x7f, 0, 2, 0x4244, CPU6502::MSK_SR_C|CPU6502::MSK_SR_V);

	std::cerr << "N-Flag" << std::endl;
	cpu.Reset();
	mem[0x1234]	= 0x01;
	SetRegisters(cpu, 0x7f, 0, 2);		// preset A=0x7f, Y=2
	cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x80, 0, 2, 0x4244, CPU6502::MSK_SR_N|CPU6502::MSK_SR_V);
}

TEST_F(CPU6502ArithmeticTest, AdcAbsX)
{
	mem[0x1236] = 0x55;
	mem[0x4242]	= CPU6502::INS_ADC_ABS_X;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x05, 0x02, 0x00);
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x5a, 0x02, 0, 0x4245, CPU6502::MSK_SR_NONE);

	std::cerr << "Standard page break" << std::endl;
	mem[0x1101] = 0x55;
	mem[0x4243]	= 0xff;
	mem[0x4244]	= 0x10;
	cpu.Reset();
	SetRegisters(cpu, 0x05, 0x02, 0x00);
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x5a, 0x02, 0, 0x4245, CPU6502::MSK_SR_NONE);

	mem[0x1236]	= 0x00;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;
	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x02, 0x00);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_Z);

	mem[0x1236]	= 0x01;
	std::cerr << "N-Flag, V-Flag " << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x7f, 0x02, 0x00);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x80, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_N | CPU6502::MSK_SR_V);

	mem[0x1236]	= 0xff;
	std::cerr << "C-Flag, V-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x80, 0x02, 0x00);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x7f, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_C | CPU6502::MSK_SR_V);

	mem[0x1236]	= 0xff;
	std::cerr << "C-Flag, Z-Flag" << std::endl;
	cpu.Reset();
	cpu.SetA(0x01);
	SetRegisters(cpu, 0x01, 0x02, 0x00);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_C | CPU6502::MSK_SR_Z);
}

TEST_F(CPU6502ArithmeticTest, AdcAbsY)
{
	mem[0x1236] = 0x55;
	mem[0x4242]	= CPU6502::INS_ADC_ABS_Y;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x05, 0x00, 0x02);
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x5a, 0x00, 0x02, 0x4245, CPU6502::MSK_SR_NONE);

	std::cerr << "Standard page break" << std::endl;
	mem[0x1101] = 0x55;
	mem[0x4243]	= 0xff;
	mem[0x4244]	= 0x10;
	cpu.Reset();
	SetRegisters(cpu, 0x05, 0x00, 0x02);
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x5a, 0x00, 0x02, 0x4245, CPU6502::MSK_SR_NONE);

	mem[0x1236]	= 0x00;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;
	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0x00, 0x02);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x00, 0x02, 0x4245, CPU6502::MSK_SR_Z);

	mem[0x1236]	= 0x01;
	std::cerr << "N-Flag, V-Flag " << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x7f, 0x00, 0x02);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x80, 0x00, 0x02, 0x4245, CPU6502::MSK_SR_N | CPU6502::MSK_SR_V);

	mem[0x1236]	= 0xff;
	std::cerr << "C-Flag, V-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x80, 0x00, 0x02);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x7f, 0x00, 0x02, 0x4245, CPU6502::MSK_SR_C | CPU6502::MSK_SR_V);

	mem[0x1236]	= 0xff;
	std::cerr << "C-Flag, Z-Flag" << std::endl;
	cpu.Reset();
	cpu.SetA(0x01);
	SetRegisters(cpu, 0x01, 0x00, 0x02);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x00, 0x02, 0x4245, CPU6502::MSK_SR_C | CPU6502::MSK_SR_Z);
}

TEST_F(CPU6502ArithmeticTest, AdcImBcd)
{
	mem[0x4242]	= CPU6502::INS_ADC_IM;
	mem[0x4243]	= 0x50;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 5, 0, 0);		// preset A=5
	cpu.SetSR(CPU6502::MSK_SR_D);
	cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x55, 0, 0, 0x4244, CPU6502::MSK_SR_D);

	std::cerr << "C-Flag" << std::endl;
	cpu.Reset();
	mem[0x4243]	= 0x99;
	SetRegisters(cpu, 0x02, 0, 0);		// preset A=2
	cpu.SetSR(CPU6502::MSK_SR_D);
	cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x01, 0, 0, 0x4244, CPU6502::MSK_SR_D | CPU6502::MSK_SR_C);

	std::cerr << "Z-Flag, C-Flag" << std::endl;
	cpu.Reset();
	mem[0x4243]	= 0x99;
	SetRegisters(cpu, 1, 0, 0);		// preset A=1
	cpu.SetSR(CPU6502::MSK_SR_D);
	cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0, 0, 0x4244, CPU6502::MSK_SR_D | CPU6502::MSK_SR_C | CPU6502::MSK_SR_Z);
}

TEST_F(CPU6502ArithmeticTest, AdcAbsBcd)
{
	mem[0x1234] = 0x50;
	mem[0x4242]	= CPU6502::INS_ADC_ABS;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x05, 0, 0);
	cpu.SetSR(CPU6502::MSK_SR_D);
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x55, 0, 0, 0x4245, CPU6502::MSK_SR_D);

	mem[0x1234]	= 0x00;
	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0, 0);
	cpu.SetSR(CPU6502::MSK_SR_D);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0, 0, 0x4245, CPU6502::MSK_SR_D | CPU6502::MSK_SR_Z);

	mem[0x1234]	= 0x01;
	std::cerr << "C-Flag, Z-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x99, 0, 0);
	cpu.SetSR(CPU6502::MSK_SR_D);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0, 0, 0x4245, CPU6502::MSK_SR_D | CPU6502::MSK_SR_C | CPU6502::MSK_SR_Z);

	mem[0x1234]	= 0x99;
	std::cerr << "C-Flag, Z-Flag 2" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x02, 0, 0);
	cpu.SetSR(CPU6502::MSK_SR_D);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x01, 0, 0, 0x4245, CPU6502::MSK_SR_D | CPU6502::MSK_SR_C);
}

TEST_F(CPU6502ArithmeticTest, AdcZpBcd)
{
	mem[0x0042] = 0x55;
	mem[0x4242]	= CPU6502::INS_ADC_ZP;
	mem[0x4243]	= 0x42;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x06, 0, 0);
	cpu.SetSR(CPU6502::MSK_SR_D);
	int clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x61, 0, 0, 0x4244, CPU6502::MSK_SR_D | CPU6502::MSK_SR_NONE);

	mem[0x0042]	= 0x00;
	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x00, 0, 0);
	cpu.SetSR(CPU6502::MSK_SR_D);
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x00, 0, 0, 0x4244, CPU6502::MSK_SR_D | CPU6502::MSK_SR_Z);

	mem[0x0042]	= 0x99;
	std::cerr << "C-Flag, Z-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x01, 0, 0);
	cpu.SetSR(CPU6502::MSK_SR_D);
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x00, 0, 0, 0x4244, CPU6502::MSK_SR_D | CPU6502::MSK_SR_C | CPU6502::MSK_SR_Z);

	mem[0x0042]	= 0x99;
	std::cerr << "C-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0x02, 0, 0);
	cpu.SetSR(CPU6502::MSK_SR_D);
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x01, 0, 0, 0x4244, CPU6502::MSK_SR_D | CPU6502::MSK_SR_C);

}

TEST_F(CPU6502ArithmeticTest, AdcZpXBcd)
{
	mem[0x0042] = 0x50;
	mem[0x4242]	= CPU6502::INS_ADC_ZPX;
	mem[0x4243]	= 0x40;

	std::cerr << "Standard" << std::endl;
	cpu.SetSR(CPU6502::MSK_SR_D);
	SetRegisters(cpu, 0x05, 0x02, 0x00);
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x55, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_D);

	mem[0x0042]	= 0x00;
	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_D);
	SetRegisters(cpu, 0x00, 0x02, 0x00);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_D | CPU6502::MSK_SR_Z);

	mem[0x0042]	= 0x99;
	std::cerr << "C-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_D);
	SetRegisters(cpu, 0x02, 0x02, 0x00);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x01, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_D | CPU6502::MSK_SR_C);

	mem[0x0042]	= 0x99;
	std::cerr << "C-Flag, Z-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_D);
	SetRegisters(cpu, 0x01, 0x02, 0x00);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_D | CPU6502::MSK_SR_C | CPU6502::MSK_SR_Z);

}

TEST_F(CPU6502ArithmeticTest, AdcIndXBcd)
{
	mem[0x0042]	= 0x34;
	mem[0x0043]	= 0x12;
	mem[0x1234]	= 0x50;
	mem[0x4242]	= CPU6502::INS_ADC_IND_X;
	mem[0x4243]	= 0x40;

	std::cerr << "Standard" << std::endl;
	cpu.SetSR(CPU6502::MSK_SR_D);
	SetRegisters(cpu, 5, 2, 0);		// preset A=5, X=2
	cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x55, 2, 0, 0x4244, CPU6502::MSK_SR_D | CPU6502::MSK_SR_NONE);

	std::cerr << "C-Flag" << std::endl;
	cpu.Reset();
	mem[0x1234]	= 0x99;
	SetRegisters(cpu, 1, 2, 0);		// preset A=1, X=2
	cpu.SetSR(CPU6502::MSK_SR_D | CPU6502::MSK_SR_I|CPU6502::MSK_SR_B|CPU6502::MSK_SR_V|CPU6502::MSK_SR_N);
	cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 2, 0, 0x4244, CPU6502::MSK_SR_D | CPU6502::MSK_SR_I|CPU6502::MSK_SR_B|CPU6502::MSK_SR_Z|CPU6502::MSK_SR_C);

	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_D);
	mem[0x1234]	= 0x00;
	SetRegisters(cpu, 0, 2, 0);		// preset A=0, X=2
	cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 2, 0, 0x4244, CPU6502::MSK_SR_D | CPU6502::MSK_SR_Z);

	std::cerr << "C-Flag, Z-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_D);
	mem[0x1234]	= 0x01;
	SetRegisters(cpu, 0x99, 2, 0);		// preset A=0x7f, X=2
	cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 2, 0, 0x4244, CPU6502::MSK_SR_D | CPU6502::MSK_SR_C | CPU6502::MSK_SR_Z);
}

TEST_F(CPU6502ArithmeticTest, AdcIndYBcd)
{
	mem[0x0040]	= 0x34;
	mem[0x0041]	= 0x12;
	mem[0x1236]	= 0x50;
	mem[0x4242]	= CPU6502::INS_ADC_IND_Y;
	mem[0x4243]	= 0x40;

	std::cerr << "Standard" << std::endl;
	cpu.SetSR(CPU6502::MSK_SR_D);
	SetRegisters(cpu, 5, 0, 2);		// preset A=5, X=2
	cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x55, 0, 2, 0x4244, CPU6502::MSK_SR_D | CPU6502::MSK_SR_NONE);

	mem[0x0040]	= 0xff;
	mem[0x0041]	= 0x10;
	mem[0x1101]	= 0x50;
	std::cerr << "Standard + page break" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_D);
	SetRegisters(cpu, 5, 0, 2);		// preset A=5, X=2
	cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x55, 0, 2, 0x4244, CPU6502::MSK_SR_D | CPU6502::MSK_SR_NONE);

	std::cerr << "C-Flag" << std::endl;
	cpu.Reset();
	mem[0x1236]	= 0x99;
	mem[0x0040]	= 0x34;
	mem[0x0041]	= 0x12;
	SetRegisters(cpu, 1, 0, 2);		// preset A=1, X=2
	cpu.SetSR(CPU6502::MSK_SR_D | CPU6502::MSK_SR_I|CPU6502::MSK_SR_B|CPU6502::MSK_SR_V|CPU6502::MSK_SR_N);
	cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0, 2, 0x4244, CPU6502::MSK_SR_D | CPU6502::MSK_SR_I|CPU6502::MSK_SR_B|CPU6502::MSK_SR_Z|CPU6502::MSK_SR_C);

	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_D);
	mem[0x1236]	= 0x00;
	SetRegisters(cpu, 0, 0, 2);		// preset A=0, X=2
	cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0, 2, 0x4244, CPU6502::MSK_SR_D | CPU6502::MSK_SR_Z);

	std::cerr << "C-Flag, Z-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_D);
	mem[0x1236]	= 0x01;
	SetRegisters(cpu, 0x99, 0, 2);		// preset A=0x7f, X=2
	cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0, 2, 0x4244, CPU6502::MSK_SR_D | CPU6502::MSK_SR_C | CPU6502::MSK_SR_Z);
}

TEST_F(CPU6502ArithmeticTest, AdcAbsXBcd)
{
	mem[0x1236] = 0x50;
	mem[0x4242]	= CPU6502::INS_ADC_ABS_X;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x05, 0x02, 0x00);
	cpu.SetSR(CPU6502::MSK_SR_D);
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x55, 0x02, 0, 0x4245, CPU6502::MSK_SR_D);

	std::cerr << "Standard + page break" << std::endl;
	mem[0x1101] = 0x50;
	mem[0x4243]	= 0xff;
	mem[0x4244]	= 0x10;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_D);
	SetRegisters(cpu, 0x05, 0x02, 0x00);
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x55, 0x02, 0, 0x4245, CPU6502::MSK_SR_D);

	mem[0x1236]	= 0x00;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;
	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_D);
	SetRegisters(cpu, 0x00, 0x02, 0x00);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_D | CPU6502::MSK_SR_Z);

	mem[0x1236]	= 0x99;
	std::cerr << "C-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_D);
	SetRegisters(cpu, 0x02, 0x02, 0x00);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x01, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_D | CPU6502::MSK_SR_C);

	mem[0x1236]	= 0x99;
	std::cerr << "C-Flag, Z-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_D);
	SetRegisters(cpu, 0x01, 0x02, 0x00);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_D | CPU6502::MSK_SR_C | CPU6502::MSK_SR_Z);
}

TEST_F(CPU6502ArithmeticTest, AdcAbsYBcd)
{
	mem[0x1236] = 0x50;
	mem[0x4242]	= CPU6502::INS_ADC_ABS_Y;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x05, 0x00, 0x02);
	cpu.SetSR(CPU6502::MSK_SR_D);
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x55, 0x00, 0x02, 0x4245, CPU6502::MSK_SR_D);

	std::cerr << "Standard + page break" << std::endl;
	mem[0x1101] = 0x50;
	mem[0x4243]	= 0xff;
	mem[0x4244]	= 0x10;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_D);
	SetRegisters(cpu, 0x05, 0x00, 0x02);
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x55, 0x00, 2, 0x4245, CPU6502::MSK_SR_D);

	mem[0x1236]	= 0x00;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;
	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_D);
	SetRegisters(cpu, 0x00, 0x00, 0x02);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x00, 0x02, 0x4245, CPU6502::MSK_SR_D | CPU6502::MSK_SR_Z);

	mem[0x1236]	= 0x99;
	std::cerr << "C-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_D);
	SetRegisters(cpu, 0x02, 0x00, 0x02);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x01, 0x00, 0x02, 0x4245, CPU6502::MSK_SR_D | CPU6502::MSK_SR_C);

	mem[0x1236]	= 0x99;
	std::cerr << "C-Flag, Z-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_D);
	SetRegisters(cpu, 0x01, 0x00, 0x02);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x00, 0x02, 0x4245, CPU6502::MSK_SR_D | CPU6502::MSK_SR_C | CPU6502::MSK_SR_Z);
}

TEST_F(CPU6502ArithmeticTest, AndIm)
{
	mem[0x4242]	= CPU6502::INS_AND_IM;
	mem[0x4243]	= 0x55;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x55, 0x00, 0x00);
	int clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x55, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_NONE);

	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0xaa, 0x00, 0x00);
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_Z);

	std::cerr << "N-Flag" << std::endl;
	mem[0x4243]	= 0x80;
	cpu.Reset();
	SetRegisters(cpu, 0xaa, 0x00, 0x00);
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x80, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_N);
}

TEST_F(CPU6502ArithmeticTest, AndAbs)
{
	mem[0x1234] = 0x55;
	mem[0x4242]	= CPU6502::INS_AND_ABS;
	mem[0x4243]	= 0x34;
	mem[0x4244] = 0x12;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x55, 0x00, 0x00);
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x55, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_NONE);

	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0xaa, 0x00, 0x00);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_Z);

	std::cerr << "N-Flag" << std::endl;
	mem[0x1234]	= 0x80;
	cpu.Reset();
	SetRegisters(cpu, 0xaa, 0x00, 0x00);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x80, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_N);
}

TEST_F(CPU6502ArithmeticTest, AndZp)
{
	mem[0x0040]	= 0x55;
	mem[0x4242]	= CPU6502::INS_AND_ZP;
	mem[0x4243]	= 0x40;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x55, 0x00, 0x00);
	int clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x55, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_NONE);

	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0xaa, 0x00, 0x00);
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x00, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_Z);

	std::cerr << "N-Flag" << std::endl;
	mem[0x40]	= 0x80;
	cpu.Reset();
	SetRegisters(cpu, 0xaa, 0x00, 0x00);
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x80, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_N);
}

TEST_F(CPU6502ArithmeticTest, AndZpX)
{
	mem[0x0042]	= 0x55;
	mem[0x4242]	= CPU6502::INS_AND_ZPX;
	mem[0x4243]	= 0x40;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x55, 0x02, 0x00);
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x55, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_NONE);

	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0xaa, 0x02, 0x00);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_Z);

	std::cerr << "N-Flag" << std::endl;
	mem[0x42]	= 0x80;
	cpu.Reset();
	SetRegisters(cpu, 0xaa, 0x02, 0x00);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x80, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_N);
}

TEST_F(CPU6502ArithmeticTest, AndAbsX)
{
	mem[0x1236]	= 0x55;
	mem[0x4242]	= CPU6502::INS_AND_ABS_X;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x55, 0x02, 0x00);
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x55, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_NONE);

	std::cerr << "Standard" << std::endl;
	mem[0x1101]	= 0x55;
	mem[0x4243]	= 0xff;
	mem[0x4244]	= 0x10;
	cpu.Reset();
	SetRegisters(cpu, 0x55, 0x02, 0x00);
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x55, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_NONE);

	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;
	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0xaa, 0x02, 0x00);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_Z);

	std::cerr << "N-Flag" << std::endl;
	mem[0x1236]	= 0x80;
	cpu.Reset();
	SetRegisters(cpu, 0xaa, 0x02, 0x00);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x80, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_N);
}

TEST_F(CPU6502ArithmeticTest, AndAbsY)
{
	mem[0x1236]	= 0x55;
	mem[0x4242]	= CPU6502::INS_AND_ABS_Y;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x55, 0x00, 0x02);
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x55, 0x00, 0x02, 0x4245, CPU6502::MSK_SR_NONE);

	std::cerr << "Standard" << std::endl;
	mem[0x1101]	= 0x55;
	mem[0x4243]	= 0xff;
	mem[0x4244]	= 0x10;
	cpu.Reset();
	SetRegisters(cpu, 0x55, 0x00, 0x02);
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x55, 0x00, 0x02, 0x4245, CPU6502::MSK_SR_NONE);

	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;
	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0xaa, 0x00, 0x02);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x00, 0x02, 0x4245, CPU6502::MSK_SR_Z);

	std::cerr << "N-Flag" << std::endl;
	mem[0x1236]	= 0x80;
	cpu.Reset();
	SetRegisters(cpu, 0xaa, 0x00, 0x02);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x80, 0x00, 0x02, 0x4245, CPU6502::MSK_SR_N);
}

TEST_F(CPU6502ArithmeticTest, AndIndX)
{
	mem[0x0042]	= 0x34;
	mem[0x0043]	= 0x12;
	mem[0x1234]	= 0x55;
	mem[0x4242]	= CPU6502::INS_AND_IND_X;
	mem[0x4243]	= 0x40;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x55, 0x02, 0x00);
	int clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x55, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_NONE);

	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	SetRegisters(cpu, 0xaa, 0x02, 0x00);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_Z);

	std::cerr << "N-Flag" << std::endl;
	mem[0x1234]	= 0x80;
	cpu.Reset();
	SetRegisters(cpu, 0xaa, 0x02, 0x00);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x80, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_N);
}

TEST_F(CPU6502ArithmeticTest, AndIndY)
{
	mem[0x0040]	= 0x34;
	mem[0x0041]	= 0x12;
	mem[0x1236]	= 0x55;
	mem[0x4242]	= CPU6502::INS_AND_IND_Y;
	mem[0x4243]	= 0x40;

	std::cerr << "Standard" << std::endl;
	SetRegisters(cpu, 0x55, 0x00, 0x02);
	int clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x55, 0x00, 0x02, 0x4244, CPU6502::MSK_SR_NONE);

	std::cerr << "Standard + page break" << std::endl;
	mem[0x0040]	= 0xff;
	mem[0x0041]	= 0x10;
	mem[0x1101]	= 0x55;
	cpu.Reset();
	SetRegisters(cpu, 0x55, 0x00, 0x02);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x55, 0x00, 0x02, 0x4244, CPU6502::MSK_SR_NONE);

	std::cerr << "Z-Flag" << std::endl;
	mem[0x0040]	= 0x34;
	mem[0x0041]	= 0x12;
	cpu.Reset();
	SetRegisters(cpu, 0xaa, 0x00, 0x02);
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0x00, 0x02, 0x4244, CPU6502::MSK_SR_Z);

	std::cerr << "N-Flag" << std::endl;
	mem[0x1236]	= 0x80;
	cpu.Reset();
	SetRegisters(cpu, 0xaa, 0x00, 0x02);
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x80, 0x00, 0x02, 0x4244, CPU6502::MSK_SR_N);
}

/*
  CLC      ; 1 + 1 = 2, returns C = 0
  LDA #$01
  ADC #$01

  CLC      ; 1 + 1 = 2, returns V = 0
  LDA #$01
  ADC #$01

  SEC      ; 0 - 1 = -1, returns V = 0
  LDA #$00
  SBC #$01

  SEC      ; -128 - 1 = -129, returns V = 1
  LDA #$80
  SBC #$01

  SEC      ; 127 - -1 = 128, returns V = 1
  LDA #$7F
  SBC #$FF
*/
TEST_F(CPU6502ArithmeticTest, SbcImm){
	mem[0x4242]	= CPU6502::INS_SBC_IM;
	mem[0x4243]	= 0x55;

	std::cerr << "Standard" << std::endl;
	cpu.SetSR(CPU6502::MSK_SR_C);
	SetRegisters(cpu, 0x5a, 0, 0);
	int clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x05, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_C);

	mem[0x4243]	= 0x00;
	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_C);
	SetRegisters(cpu, 0, 0, 0);
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0, 0, 0x4244, CPU6502::MSK_SR_C | CPU6502::MSK_SR_Z);

	mem[0x4243]	= 0xff;
	std::cerr << "N,V-Flag: 127 - (-1) = 128-> Z,V" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_C);
	SetRegisters(cpu, 0x7f, 0, 0);
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x80, 0, 0, 0x4244, CPU6502::MSK_SR_N|CPU6502::MSK_SR_V);

	mem[0x4243]	= 0x01;
	std::cerr << "C,V-Flag: -128 - 1  -> C,V" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_C | CPU6502::MSK_SR_N);
	SetRegisters(cpu, 0x80, 0, 0);
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x7f, 0, 0, 0x4244, CPU6502::MSK_SR_C | CPU6502::MSK_SR_V);

	mem[0x4243]	= 0x01;
	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_C);
	SetRegisters(cpu, 0x01, 0, 0);
	clocks = cpu.Run(2);
	VerifyRegisters(cpu, 2, 0x00, 0, 0, 0x4244, CPU6502::MSK_SR_C|CPU6502::MSK_SR_Z);
}

TEST_F(CPU6502ArithmeticTest, SbcAbs){
	mem[0x1234]	= 0x55;
	mem[0x4242]	= CPU6502::INS_SBC_ABS;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	std::cerr << "Standard" << std::endl;
	cpu.SetSR(CPU6502::MSK_SR_C);
	SetRegisters(cpu, 0x5a, 0, 0);
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x05, 0x00, 0x00, 0x4245, CPU6502::MSK_SR_C);

	mem[0x1234]	= 0x00;
	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_C);
	SetRegisters(cpu, 0, 0, 0);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0, 0, 0x4245, CPU6502::MSK_SR_C | CPU6502::MSK_SR_Z);

	mem[0x1234]	= 0xff;
	std::cerr << "N,V-Flag: 127 - (-1) = 128-> Z,V" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_C);
	SetRegisters(cpu, 0x7f, 0, 0);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x80, 0, 0, 0x4245, CPU6502::MSK_SR_N|CPU6502::MSK_SR_V);

	mem[0x1234]	= 0x01;
	std::cerr << "C,V-Flag: -128 - 1  -> C,V" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_C | CPU6502::MSK_SR_N);
	SetRegisters(cpu, 0x80, 0, 0);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x7f, 0, 0, 0x4245, CPU6502::MSK_SR_C | CPU6502::MSK_SR_V);

	mem[0x1234]	= 0x01;
	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_C);
	SetRegisters(cpu, 0x01, 0, 0);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0, 0, 0x4245, CPU6502::MSK_SR_C|CPU6502::MSK_SR_Z);
}

TEST_F(CPU6502ArithmeticTest, SbcZp){
	mem[0x0034]	= 0x55;
	mem[0x4242]	= CPU6502::INS_SBC_ZP;
	mem[0x4243]	= 0x34;

	std::cerr << "Standard" << std::endl;
	cpu.SetSR(CPU6502::MSK_SR_C);
	SetRegisters(cpu, 0x5a, 0, 0);
	int clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x05, 0x00, 0x00, 0x4244, CPU6502::MSK_SR_C);

	mem[0x0034]	= 0x00;
	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_C);
	SetRegisters(cpu, 0, 0, 0);
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x00, 0, 0, 0x4244, CPU6502::MSK_SR_C | CPU6502::MSK_SR_Z);

	mem[0x0034]	= 0xff;
	std::cerr << "N,V-Flag: 127 - (-1) = 128-> Z,V" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_C);
	SetRegisters(cpu, 0x7f, 0, 0);
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x80, 0, 0, 0x4244, CPU6502::MSK_SR_N|CPU6502::MSK_SR_V);

	mem[0x0034]	= 0x01;
	std::cerr << "C,V-Flag: -128 - 1  -> C,V" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_C | CPU6502::MSK_SR_N);
	SetRegisters(cpu, 0x80, 0, 0);
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x7f, 0, 0, 0x4244, CPU6502::MSK_SR_C | CPU6502::MSK_SR_V);

	mem[0x0034]	= 0x01;
	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_C);
	SetRegisters(cpu, 0x01, 0, 0);
	clocks = cpu.Run(3);
	VerifyRegisters(cpu, 3, 0x00, 0, 0, 0x4244, CPU6502::MSK_SR_C|CPU6502::MSK_SR_Z);
}

TEST_F(CPU6502ArithmeticTest, SbcIndX){
	mem[0x0036]	= 0x34;
	mem[0x0037]	= 0x12;
	mem[0x1234]	= 0x55;
	mem[0x4242]	= CPU6502::INS_SBC_IND_X;
	mem[0x4243]	= 0x34;

	std::cerr << "Standard" << std::endl;
	cpu.SetSR(CPU6502::MSK_SR_C);
	SetRegisters(cpu, 0x5a, 0x02, 0x00);
	int clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x05, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_C);

	mem[0x1234]	= 0x00;
	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_C);
	SetRegisters(cpu, 0x00, 0x02, 0x00);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_C | CPU6502::MSK_SR_Z);

	mem[0x1234]	= 0xff;
	std::cerr << "N,V-Flag: 127 - (-1) = 128-> Z,V" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_C);
	SetRegisters(cpu, 0x7f, 0x02, 0x00);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x80, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_N|CPU6502::MSK_SR_V);

	mem[0x1234]	= 0x01;
	std::cerr << "C,V-Flag: -128 - 1  -> C,V" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_C | CPU6502::MSK_SR_N);
	SetRegisters(cpu, 0x80, 0x02, 0x00);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x7f, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_C | CPU6502::MSK_SR_V);

	mem[0x1234]	= 0x01;
	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_C);
	SetRegisters(cpu, 0x01, 0x02, 0x00);
	clocks = cpu.Run(6);
	VerifyRegisters(cpu, 6, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_C|CPU6502::MSK_SR_Z);
}

TEST_F(CPU6502ArithmeticTest, SbcIndY){
	mem[0x0034]	= 0x34;
	mem[0x0035]	= 0x12;
	mem[0x1236]	= 0x55;
	mem[0x4242]	= CPU6502::INS_SBC_IND_Y;
	mem[0x4243]	= 0x34;

	std::cerr << "Standard" << std::endl;
	cpu.SetSR(CPU6502::MSK_SR_C);
	SetRegisters(cpu, 0x5a, 0x00, 0x02);
	int clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x05, 0x00, 0x02, 0x4244, CPU6502::MSK_SR_C);

	mem[0x1236]	= 0x00;
	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_C);
	SetRegisters(cpu, 0x00, 0x00, 0x02);
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0x00, 0x02, 0x4244, CPU6502::MSK_SR_C | CPU6502::MSK_SR_Z);

	mem[0x1236]	= 0xff;
	std::cerr << "N,V-Flag: 127 - (-1) = 128-> Z,V" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_C);
	SetRegisters(cpu, 0x7f, 0x00, 0x02);
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x80, 0x00, 0x02, 0x4244, CPU6502::MSK_SR_N|CPU6502::MSK_SR_V);

	mem[0x1236]	= 0x01;
	std::cerr << "C,V-Flag: -128 - 1  -> C,V" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_C | CPU6502::MSK_SR_N);
	SetRegisters(cpu, 0x80, 0x00, 0x02);
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x7f, 0x00, 0x02, 0x4244, CPU6502::MSK_SR_C | CPU6502::MSK_SR_V);

	mem[0x1236]	= 0x01;
	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_C);
	SetRegisters(cpu, 0x01, 0x00, 0x02);
	clocks = cpu.Run(5);
	VerifyRegisters(cpu, 5, 0x00, 0x00, 0x02, 0x4244, CPU6502::MSK_SR_C|CPU6502::MSK_SR_Z);
}

TEST_F(CPU6502ArithmeticTest, SbcZpX){
	mem[0x0036]	= 0x55;
	mem[0x4242]	= CPU6502::INS_SBC_ZPX;
	mem[0x4243]	= 0x34;

	std::cerr << "Standard" << std::endl;
	cpu.SetSR(CPU6502::MSK_SR_C);
	SetRegisters(cpu, 0x5a, 0x02, 0x00);
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x05, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_C);

	mem[0x0036]	= 0x00;
	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_C);
	SetRegisters(cpu, 0, 0x02, 0x00);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_C | CPU6502::MSK_SR_Z);

	mem[0x0036]	= 0xff;
	std::cerr << "N,V-Flag: 127 - (-1) = 128-> Z,V" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_C);
	SetRegisters(cpu, 0x7f, 0x02, 0x00);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x80, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_N|CPU6502::MSK_SR_V);

	mem[0x0036]	= 0x01;
	std::cerr << "C,V-Flag: -128 - 1  -> C,V" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_C | CPU6502::MSK_SR_N);
	SetRegisters(cpu, 0x80, 0x02, 0x00);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x7f, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_C | CPU6502::MSK_SR_V);

	mem[0x0036]	= 0x01;
	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_C);
	SetRegisters(cpu, 0x01, 0x02, 0x00);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x02, 0x00, 0x4244, CPU6502::MSK_SR_C|CPU6502::MSK_SR_Z);
}

TEST_F(CPU6502ArithmeticTest, SbcAbsX){
	mem[0x1236]	= 0x55;
	mem[0x4242]	= CPU6502::INS_SBC_ABS_X;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	std::cerr << "Standard" << std::endl;
	cpu.SetSR(CPU6502::MSK_SR_C);
	SetRegisters(cpu, 0x5a, 0x02, 0x00);
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x05, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_C);

	mem[0x1236]	= 0x00;
	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_C);
	SetRegisters(cpu, 0x00, 0x02, 0x00);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_C | CPU6502::MSK_SR_Z);

	mem[0x1236]	= 0xff;
	std::cerr << "N,V-Flag: 127 - (-1) = 128-> Z,V" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_C);
	SetRegisters(cpu, 0x7f, 0x02, 0x00);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x80, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_N|CPU6502::MSK_SR_V);

	mem[0x1236]	= 0x01;
	std::cerr << "C,V-Flag: -128 - 1  -> C,V" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_C | CPU6502::MSK_SR_N);
	SetRegisters(cpu, 0x80, 0x02, 0x00);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x7f, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_C | CPU6502::MSK_SR_V);

	mem[0x1236]	= 0x01;
	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_C);
	SetRegisters(cpu, 0x01, 0x02, 0x00);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x02, 0x00, 0x4245, CPU6502::MSK_SR_C|CPU6502::MSK_SR_Z);
}

TEST_F(CPU6502ArithmeticTest, SbcAbsY){
	mem[0x1236]	= 0x55;
	mem[0x4242]	= CPU6502::INS_SBC_ABS_Y;
	mem[0x4243]	= 0x34;
	mem[0x4244]	= 0x12;

	std::cerr << "Standard" << std::endl;
	cpu.SetSR(CPU6502::MSK_SR_C);
	SetRegisters(cpu, 0x5a, 0x00, 0x02);
	int clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x05, 0x00, 0x02, 0x4245, CPU6502::MSK_SR_C);

	mem[0x1236]	= 0x00;
	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_C);
	SetRegisters(cpu, 0x00, 0x00, 0x02);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x00, 0x02, 0x4245, CPU6502::MSK_SR_C | CPU6502::MSK_SR_Z);

	mem[0x1236]	= 0xff;
	std::cerr << "N,V-Flag: 127 - (-1) = 128-> Z,V" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_C);
	SetRegisters(cpu, 0x7f, 0x00, 0x02);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x80, 0x00, 0x02, 0x4245, CPU6502::MSK_SR_N|CPU6502::MSK_SR_V);

	mem[0x1236]	= 0x01;
	std::cerr << "C,V-Flag: -128 - 1  -> C,V" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_C | CPU6502::MSK_SR_N);
	SetRegisters(cpu, 0x80, 0x00, 0x02);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x7f, 0x00, 0x02, 0x4245, CPU6502::MSK_SR_C | CPU6502::MSK_SR_V);

	mem[0x1236]	= 0x01;
	std::cerr << "Z-Flag" << std::endl;
	cpu.Reset();
	cpu.SetSR(CPU6502::MSK_SR_C);
	SetRegisters(cpu, 0x01, 0x00, 0x02);
	clocks = cpu.Run(4);
	VerifyRegisters(cpu, 4, 0x00, 0x00, 0x02, 0x4245, CPU6502::MSK_SR_C|CPU6502::MSK_SR_Z);
}
