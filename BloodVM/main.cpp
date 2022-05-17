#include <iostream>
#include "BloodVM.h"

int __declspec(naked) __stdcall Sumar()
{
    __asm
    {
        call BloodVM_Init;
        //MOV_R_N => mov eax, 4;
        _emit 0x02; //OPCODE::MOV_R_N
        _emit 0x05; //EAX offset
        _emit 0x04; //number 4 bytes
        _emit 0x00;
        _emit 0x00;
        _emit 0x00;
        //ADD_R_N => add eax, 5;
        _emit 0x04; //OPCODE::ADD_R_N
        _emit 0x05; //EAX offset
        _emit 0x05; //number 4 bytes
        _emit 0x00;
        _emit 0x00;
        _emit 0x00;
        //ADD_R_R => add eax, eax;
        _emit 0x03; //OPCODE::ADD_R_R
        _emit 0x05; //EAX offset
        _emit 0x05; //EAX offset
        //QUIT => Exit VM
        _emit 0x00;
        ret;
    }
}

int __declspec(naked) __stdcall Multiplicar()
{
    __asm
    {
        call BloodVM_Init;
        //MOV_R_N => mov eax, 0;
        _emit 0x02; //OPCODE::MOV_R_N
        _emit 0x05; //EAX offset
        _emit 0x00; //number 4 bytes
        _emit 0x00;
        _emit 0x00;
        _emit 0x00;
        //MOV_R_N => mov edx, 4;
        _emit 0x02; //OPCODE::MOV_R_N
        _emit 0x03; //EDX offset
        _emit 0x04; //number 4 bytes
        _emit 0x00;
        _emit 0x00;
        _emit 0x00;
        //MOV_R_N => mov ecx, 0;
        _emit 0x02; //OPCODE::MOV_R_N
        _emit 0x04; //ECX offset
        _emit 0x00; //number 4 bytes
        _emit 0x00;
        _emit 0x00;
        _emit 0x00;

        // Begin loop
        //ADD_R_N => add eax, 2;
        _emit 0x04; //OPCODE::ADD_R_N
        _emit 0x05; //EAX offset
        _emit 0x02; //number 4 bytes
        _emit 0x00;
        _emit 0x00;
        _emit 0x00;
        //ADD_R_N => add ecx, 1;
        _emit 0x04; //OPCODE::ADD_R_N
        _emit 0x04; //ECX offset
        _emit 0x01; //number 4 bytes
        _emit 0x00;
        _emit 0x00;
        _emit 0x00;
        //CMP_R_R => cmp edx, ecx;
        _emit 0x06; //OPCODE::CMP_R_R
        _emit 0x03; //EDX offset
        _emit 0x04; //ECX offset
        //JNZ_N => jmp to Begin loop
        _emit 0x05; //OPCODE::JNZ_N
        _emit 0xEC; //number 4 bytes (-20)
        _emit 0xFF;
        _emit 0xFF;
        _emit 0xFF;
        //QUIT => Exit VM
        _emit 0x00;
        ret;
    }
}

int main()
{
    std::cout << "Suma virtualizada (4 + 5) + (4 + 5) = " << Sumar() << std::endl;
    std::cout << "Multiplicar virtualizado 2 x 4 = " << Multiplicar() << std::endl;
    std::cin.ignore();
}
