#include <gtest/gtest.h>
#include "cpu_6502.h"
#include "memory.h"

#ifndef CPU_6502_MAIN_TEST_H
#define CPU_6502_MAIN_TEST_H

class CPU6502Test : public testing::Test
{
	public:
		Memory	mem;
		CPU6502	cpu;

		CPU6502Test();
		~CPU6502Test();

		void VerifyRegisters(CPU6502& aCpu, unsigned int const aClocks, Byte const aRegA, Byte const aRegX, Byte const aRegY, Word const aRegPC, Byte const aRegSR);
		void SetRegisters(CPU6502& aCpu, Byte aRegA, Byte aRegX, Byte aRegY);
};

#endif

