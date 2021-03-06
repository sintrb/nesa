//指令",机器码",长度
#include "stddef.h"
namespace gloab{
	const TYPE_NAME const_ins_ins[152] = {//指令
		"LDA ($xx,X)",
		"LDA $xx",
		"LDA #$xx",
		"LDA $xxxx",
		"LDA ($xx),Y",
		"LDA $xx,X",
		"LDA $xxxx,Y",
		"LDA $xxxx,X",
		"LDX #$xx",
		"LDX $xx",
		"LDX $xxxx",
		"LDX $xx,Y",
		"LDX $xxxx,Y",
		"LDY #$xx",
		"LDY $xx",
		"LDY $xxxx",
		"LDY $xx,X",
		"LDY $xxxx,X",
		"STA ($xx,X)",
		"STA $xx",
		"STA $xxxx",
		"STA ($xx),Y",
		"STA $xx,X",
		"STA $xxxx,Y",
		"STA $xxxx,X",
		"STX $xx",
		"STX $xxxx",
		"STX $xx,Y",
		"STY $xx",
		"STY $xxxx",
		"STY $xx,X",
		"TAX",
		"TXA",
		"TAY",
		"TYA",
		"TSX",
		"TXS",
		"ADC ($xx,X)",
		"ADC $xx",
		"ADC #$xx",
		"ADC $xxxx",
		"ADC ($xx),Y",
		"ADC $xx,X",
		"ADC $xxxx,Y",
		"ADC $xxxx,X",
		"SBC ($xx,X)",
		"SBC $xx",
		"SBC #$xx",
		"SBC $xxxx",
		"SBC ($xx),Y",
		"SBC $xx,X",
		"SBC $xxxx,Y",
		"SBC $xxxx,X",
		"INC $xx",
		"INC $xxxx",
		"INC $xx,X",
		"INC $xxxx,X",
		"DEC $xx",
		"DEC $xxxx",
		"DEC $xx,X",
		"DEC $xxxx,X",
		"INX",
		"DEX",
		"INY",
		"DEY",
		"AND ($xx,X)",
		"AND $xx",
		"AND #$xx",
		"AND $xxxx",
		"AND ($xx),Y",
		"AND $xx,X",
		"AND $xxxx,Y",
		"AND $xxxx,X",
		"ORA ($xx,X)",
		"ORA $xx",
		"ORA #$xx",
		"ORA $xxxx",
		"ORA ($xx),Y",
		"ORA $xx,X",
		"ORA $xxxx,Y",
		"ORA $xxxx,X",
		"EOR ($xx,X)",
		"EOR $xx",
		"EOR #$xx",
		"EOR $xxxx",
		"EOR ($xx),Y",
		"EOR $xx,X",
		"EOR $xxxx,Y",
		"EOR $xxxx,X",
		"CLC",
		"SEC",
		"CLD",
		"SED",
		"CLV",
		"CLI",
		"SEI",
		"CMP ($xx,X)",
		"CMP $xx",
		"CMP #$xx",
		"CMP $xxxx",
		"CMP ($xx),Y",
		"CMP $xx,X",
		"CMP $xxxx,Y",
		"CMP $xxxx,X",
		"CPX #$xx",
		"CPX $xx",
		"CPX $xxxx",
		"CPY #$xx",
		"CPY $xx",
		"CPY $xxxx",
		"BIT $xx",
		"BIT $xxxx",
		"ASL",
		"ASL $xx",
		"ASL $xxxx",
		"ASL $xx,X",
		"ASL $xxxx,X",
		"LSR",
		"LSR $xx",
		"LSR $xxxx",
		"LSR $xx,X",
		"LSR $xxxx,X",
		"ROL",
		"ROL $xx",
		"ROL $xxxx",
		"ROL $xx,X",
		"ROL $xxxx,X",
		"ROR",
		"ROR $xx",
		"ROR $xxxx",
		"ROR $xx,X",
		"ROR $xxxx,X",
		"PHA",
		"PLA",
		"PHP",
		"PLP",
		"JMP $xxxx",
		"JMP ($xxxx)",
		"BEQ $xxxx",
		"BNE $xxxx",
		"BCS $xxxx",
		"BCC $xxxx",
		"BMI $xxxx",
		"BPL $xxxx",
		"BVS $xxxx",
		"BVC $xxxx",
		"JSR $xxxx",
		"RTS",
		"INT $xxxx",
		"NOP",
		"RTI",
		"BRK"};
		
	const TYPE_BYTE const_ins_code[152] = {//机器码
		0xa1,
		0xa5,
		0xa9,
		0xad,
		0xb1,
		0xb5,
		0xb9,
		0xbd,
		0xa2,
		0xa6,
		0xae,
		0xb6,
		0xbe,
		0xa0,
		0xa4,
		0xac,
		0xb4,
		0xbc,
		0x81,
		0x85,
		0x8d,
		0x91,
		0x95,
		0x99,
		0x9d,
		0x86,
		0x8e,
		0x96,
		0x84,
		0x8c,
		0x94,
		0xaa,
		0x8a,
		0xa8,
		0x98,
		0xba,
		0x9a,
		0x61,
		0x65,
		0x69,
		0x6d,
		0x71,
		0x75,
		0x79,
		0x7d,
		0xe1,
		0xe5,
		0xe9,
		0xed,
		0xf1,
		0xf5,
		0xf9,
		0xfd,
		0xe6,
		0xee,
		0xf6,
		0xfe,
		0xc6,
		0xce,
		0xd6,
		0xde,
		0xe8,
		0xca,
		0xc8,
		0x88,
		0x21,
		0x25,
		0x29,
		0x2d,
		0x31,
		0x35,
		0x39,
		0x3d,
		0x1,
		0x5,
		0x9,
		0xd,
		0x11,
		0x15,
		0x19,
		0x1d,
		0x41,
		0x45,
		0x49,
		0x4d,
		0x51,
		0x55,
		0x59,
		0x5d,
		0x18,
		0x38,
		0xd8,
		0xf8,
		0xb8,
		0x58,
		0x78,
		0xc1,
		0xc5,
		0xc9,
		0xcd,
		0xd1,
		0xd5,
		0xd9,
		0xdd,
		0xe0,
		0xe4,
		0xec,
		0xc0,
		0xc4,
		0xcc,
		0x24,
		0x2c,
		0xa,
		0x6,
		0xe,
		0x16,
		0x1e,
		0x4a,
		0x46,
		0x4e,
		0x56,
		0x5e,
		0x2a,
		0x26,
		0x2e,
		0x36,
		0x3e,
		0x6a,
		0x66,
		0x6e,
		0x76,
		0x7e,
		0x48,
		0x68,
		0x8,
		0x28,
		0x4c,
		0x6c,
		0xf0,
		0xd0,
		0xb0,
		0x90,
		0x30,
		0x10,
		0x70,
		0x50,
		0x20,
		0x60,
		0x0,
		0xea,
		0x40,
		0x0};
		
	const TYPE_SIZE const_ins_size[152] = {//长度
		2,
		2,
		2,
		3,
		2,
		2,
		3,
		3,
		2,
		2,
		3,
		2,
		3,
		2,
		2,
		3,
		2,
		3,
		2,
		2,
		3,
		2,
		2,
		3,
		3,
		2,
		3,
		2,
		2,
		3,
		2,
		1,
		1,
		1,
		1,
		1,
		1,
		2,
		2,
		2,
		3,
		2,
		2,
		3,
		3,
		2,
		2,
		2,
		3,
		2,
		2,
		3,
		3,
		2,
		3,
		2,
		3,
		2,
		3,
		2,
		3,
		1,
		1,
		1,
		1,
		2,
		2,
		2,
		3,
		2,
		2,
		3,
		3,
		2,
		2,
		2,
		3,
		2,
		2,
		3,
		3,
		2,
		2,
		2,
		3,
		2,
		2,
		3,
		3,
		1,
		1,
		1,
		1,
		1,
		1,
		1,
		2,
		2,
		2,
		3,
		2,
		2,
		3,
		3,
		2,
		2,
		3,
		2,
		2,
		3,
		2,
		3,
		1,
		2,
		3,
		2,
		3,
		1,
		2,
		3,
		2,
		3,
		1,
		2,
		3,
		2,
		3,
		1,
		2,
		3,
		2,
		3,
		1,
		1,
		1,
		1,
		3,
		3,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		2,
		3,
		1,
		3,
		1,
		1,
		1};
	
	const TYPE_DATATYPE const_ins_type[152] = {//类型
		DATATYPE_ZPADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_BYTE,
		DATATYPE_ADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_ADDRESS,
		DATATYPE_ADDRESS,
		DATATYPE_BYTE,
		DATATYPE_ZPADDRESS,
		DATATYPE_ADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_ADDRESS,
		DATATYPE_BYTE,
		DATATYPE_ZPADDRESS,
		DATATYPE_ADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_ADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_ADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_ADDRESS,
		DATATYPE_ADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_ADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_ADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_NONE,
		DATATYPE_NONE,
		DATATYPE_NONE,
		DATATYPE_NONE,
		DATATYPE_NONE,
		DATATYPE_NONE,
		DATATYPE_ZPADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_BYTE,
		DATATYPE_ADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_ADDRESS,
		DATATYPE_ADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_BYTE,
		DATATYPE_ADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_ADDRESS,
		DATATYPE_ADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_ADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_ADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_ADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_ADDRESS,
		DATATYPE_NONE,
		DATATYPE_NONE,
		DATATYPE_NONE,
		DATATYPE_NONE,
		DATATYPE_ZPADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_BYTE,
		DATATYPE_ADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_ADDRESS,
		DATATYPE_ADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_BYTE,
		DATATYPE_ADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_ADDRESS,
		DATATYPE_ADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_BYTE,
		DATATYPE_ADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_ADDRESS,
		DATATYPE_ADDRESS,
		DATATYPE_NONE,
		DATATYPE_NONE,
		DATATYPE_NONE,
		DATATYPE_NONE,
		DATATYPE_NONE,
		DATATYPE_NONE,
		DATATYPE_NONE,
		DATATYPE_ZPADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_BYTE,
		DATATYPE_ADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_ADDRESS,
		DATATYPE_ADDRESS,
		DATATYPE_BYTE,
		DATATYPE_ZPADDRESS,
		DATATYPE_ADDRESS,
		DATATYPE_BYTE,
		DATATYPE_ZPADDRESS,
		DATATYPE_ADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_ADDRESS,
		DATATYPE_NONE,
		DATATYPE_ZPADDRESS,
		DATATYPE_ADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_ADDRESS,
		DATATYPE_NONE,
		DATATYPE_ZPADDRESS,
		DATATYPE_ADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_ADDRESS,
		DATATYPE_NONE,
		DATATYPE_ZPADDRESS,
		DATATYPE_ADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_ADDRESS,
		DATATYPE_NONE,
		DATATYPE_ZPADDRESS,
		DATATYPE_ADDRESS,
		DATATYPE_ZPADDRESS,
		DATATYPE_ADDRESS,
		DATATYPE_NONE,
		DATATYPE_NONE,
		DATATYPE_NONE,
		DATATYPE_NONE,
		DATATYPE_ADDRESS,
		DATATYPE_ADDRESS,
		DATATYPE_RELATIVE,
		DATATYPE_RELATIVE,
		DATATYPE_RELATIVE,
		DATATYPE_RELATIVE,
		DATATYPE_RELATIVE,
		DATATYPE_RELATIVE,
		DATATYPE_RELATIVE,
		DATATYPE_RELATIVE,
		DATATYPE_ADDRESS,
		DATATYPE_NONE,
		DATATYPE_ADDRESS,
		DATATYPE_NONE,
		DATATYPE_NONE,
		DATATYPE_NONE};

};

