#pragma once
#include <cstdint>
#include <vector>

enum OPCODE
{
	QUIT,
	MOV_R_R,
	MOV_R_N,
	ADD_R_R,
	ADD_R_N,
	JNZ_N,
	CMP_R_R,
};

class BloodVM
{
	public:
		BloodVM()
		{
			vInstructions =
			{
				/*
				All opcodes sizes are always 1 byte
				All registers (R) sizes are also 1 byte
				All numbers (N) sizes are always 4 bytes
				*/
				{OPCODE::QUIT, 1, &BloodVM::QUIT},
				{OPCODE::MOV_R_R, 3, &BloodVM::MOV},
				{OPCODE::MOV_R_N, 6, &BloodVM::MOV},
				{OPCODE::ADD_R_R, 3, &BloodVM::ADD},
				{OPCODE::ADD_R_N, 6, &BloodVM::ADD},
				{OPCODE::JNZ_N, 5, &BloodVM::JNZ},
				{OPCODE::CMP_R_R, 3, &BloodVM::CMP},
			};
		}

		struct EFLAGS
		{
			uint8_t Zero = 0;
		};

        uint32_t EDI, ESI, EBX, EDX, ECX, EAX, EBP, EIP, ESP;
		EFLAGS Flags;

		uint8_t currentOpcode;
		void RunVirtualMachine();

		void JNZ();
		void CMP();
		void MOV();
		void ADD();
		void QUIT();

		struct INSTRUCTION
		{
			uint8_t opcode;
			uint8_t sizeOfInstruction;
			void (BloodVM::* operate)() = nullptr;
		};

		std::vector<INSTRUCTION> vInstructions;
};

void __stdcall BloodVM_Init();
void __stdcall BloodVM_End();