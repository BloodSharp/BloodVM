#include "BloodVM.h"

BloodVM gBloodVM;

uint32_t __declspec(naked) __stdcall GetCaller()//uint32_t dwESP)
{
    //return *(uint32_t*)(dwESP+4);
    __asm
    {
        mov eax, [esp + 4];
        ret;
    }
}

void __declspec(naked) __stdcall BloodVM_Init()
{
    __asm
    {
        pushad;
        pop gBloodVM.EDI;
        pop gBloodVM.ESI;
        pop gBloodVM.EBP;
        pop gBloodVM.ESP;
        pop gBloodVM.EBX;
        pop gBloodVM.EDX;
        pop gBloodVM.ECX;
        pop gBloodVM.EAX;
        
        //push gBloodVM.ESP;
        call GetCaller;
        mov gBloodVM.EIP, eax;
        lea ecx, gBloodVM;
        call BloodVM::RunVirtualMachine;
        mov eax, gBloodVM.EIP;
        mov [esp], eax;

        mov edi, gBloodVM.EDI;
        mov esi, gBloodVM.ESI;
        mov ebx, gBloodVM.EBX;
        mov edx, gBloodVM.EDX;
        mov ecx, gBloodVM.ECX;
        mov eax, gBloodVM.EAX;
        mov ebp, gBloodVM.EBP;
        mov esp, gBloodVM.ESP;

        ret;
    }
}

void BloodVM::RunVirtualMachine()
{
    do
    {
        this->currentOpcode = (uint8_t)(*((uint8_t*)this->EIP));
        uint32_t nextEIP = this->vInstructions[this->currentOpcode].sizeOfInstruction;
        (this->*vInstructions[this->currentOpcode].operate)();
        this->EIP += nextEIP;
    } while (this->currentOpcode != OPCODE::QUIT);
}

void BloodVM::QUIT()
{

}

void BloodVM::MOV()
{
    uint32_t* firstRegister;
    uint32_t* secondRegister;
    uint32_t firstNumber;
    switch (this->currentOpcode)
    {
        case OPCODE::MOV_R_R:
            firstRegister = &this->EDI + *(uint8_t*)(this->EIP + 1);
            secondRegister = &this->EDI + *(uint8_t*)(this->EIP + 2);
            *firstRegister = *secondRegister;
            break;
        case OPCODE::MOV_R_N:
            firstRegister = &this->EDI + *(uint8_t*)(this->EIP + 1);
            firstNumber = *(uint32_t*)(this->EIP + 2);
            *firstRegister = firstNumber;
            break;
    }
}

void BloodVM::ADD()
{
    uint32_t* firstRegister;
    uint32_t* secondRegister;
    uint32_t firstNumber;
    switch (this->currentOpcode)
    {
        case OPCODE::ADD_R_R:
            firstRegister = &this->EDI + *(uint8_t*)(this->EIP + 1);
            secondRegister = &this->EDI + *(uint8_t*)(this->EIP + 2);
            *firstRegister += *secondRegister;
            this->Flags.Zero = (*firstRegister == 0);
            break;
        case OPCODE::ADD_R_N:
            firstRegister = &this->EDI + *(uint8_t*)(this->EIP + 1);
            firstNumber = *(uint32_t*)(this->EIP + 2);
            *firstRegister += firstNumber;
            break;
    }
}

void BloodVM::CMP()
{
    uint32_t* firstRegister;
    uint32_t* secondRegister;
    switch (this->currentOpcode)
    {
        case OPCODE::CMP_R_R:
            firstRegister = &this->EDI + *(uint8_t*)(this->EIP + 1);
            secondRegister = &this->EDI + *(uint8_t*)(this->EIP + 2);
            this->Flags.Zero = (*firstRegister - *secondRegister) == 0;
            break;
    }
}

void BloodVM::JNZ()
{
    uint32_t firstNumber;
    switch (this->currentOpcode)
    {
        case OPCODE::JNZ_N:
            firstNumber = *(uint32_t*)(this->EIP + 1);
            if (!this->Flags.Zero)
                this->EIP += firstNumber;
            break;
    }
}