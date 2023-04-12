#include "cpu_6502.h"
#include "memory.h"
#include <fstream>
#include <iostream>

int main(void)
{
	Memory	mem;
	CPU6502	cpu(mem);
	
	std::fstream	prog;

	prog.open("../../../6502_65C02_functional_tests/6502_functional_test.bin", std::fstream::in);	
	if(prog.is_open()){
		std::cerr << "loading program ..." << std::endl;
		prog.read((char*)mem.Buffer()+10,1024*64);
		prog.close();
		std::cerr << "resetting ..." << std::endl;
		cpu.Reset();
		cpu.SetPC(0x0400);
		std::cerr << "running ..." << std::endl;
		int clocks = cpu.Run(-1);
		std::cerr << "Done ... clock=" << clocks << std::endl;
	}

	return 0;
}
