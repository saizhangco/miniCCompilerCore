#pragma once
/**
* �����ռ�: None
*
* �� �ܣ� ����miniC���Եĵ��ʱ���
* �� ���� None
*
* Ver 2016-06-10 ���� ����miniC���Եĵ��ʱ��뼰��غ궨��
* ����������������������������������������������������������������������
* V0.02 2016-06-10 ���� 2��
*
* Copyright (c) 2015 Lir Corporation. All rights reserved.
*������������������������������������������������������������������������
*�����˼�����ϢΪ����˾������Ϣ��δ������˾����ͬ���ֹ���������¶������
*������Ȩ���У�*****���޹�˾ ������              ������������������������
*������������������������������������������������������������������������
*/
//δʶ��
#define Error 0xFFF //����ĵ���
#define Unknown 0x00	//δʶ��
//�ؼ��ֻ��߱�ʶ��
#define Identifier 0x01//��ʶ��
#define Character 0x02	//�ַ�
#define String 0x03 //�ַ���
#define Number_Exponent 0x04 //ָ�� 
#define Number_Decimals 0x05 //С��
#define Number_Decimalism 0x06 //���� [ʮ����]
#define Number_Octonary 0x07 //���� [�˽���]
#define Number_Hexadecimal 0x08 //���� [ʮ������]

#define Grammar_Nonterminator 0x0A	//������ս��

//��� ( ) ; [ ] { } . , ~ ��10���ַ�
// $ ���ķ�����ʱ���õ�
#define Delimiter_Left_Small_Bracket 0x11	// ( ��С����
#define Delimiter_Right_Small_Bracket 0x12	// ) ��С����
#define Delimiter_Semicolon 0x13			// ; �ֺ�
#define Delimiter_Left_Middle_Bracket 0x14	// [ ��������
#define Delimiter_Right_Middle_Bracket 0x15	// ] ��������
#define Delimiter_Left_Large_Bracket 0x16	// { �������
#define Delimiter_Right_Large_Bracket 0x17	// } �Ҵ�����
#define Delimiter_Period 0x18				// . ���
#define Delimiter_Comma 0x19				// , ����
#define Delimiter_Tilde 0x1A				// ~ �����ַ�
#define Delimiter_Pound_Sign 0x1B			// # ����
#define Delimiter_Dollar 0x1C				// $ ��Ԫ���� Դ�����е��쳣�ַ����ķ��еĿշ���

//�����
#define Operator_Not 0x20				// ! ��
#define Operator_Not_Equal_To 0x21		// != ������
#define Operator_Mod 0x22				// % ȡ��
#define Operator_Mod_Equal 0x23			// %= ȡ�����
#define Operator_Equal 0x24				// = ����
#define Operator_Is_Equal 0x25			// == �Ƿ����
#define Operator_Xor 0x26				// ^ ���
#define Operator_Xor_Equal 0x27			// ^= ������
#define Operator_Bit_And 0x28			// & λ��
#define Operator_Bit_And_Equal 0x29		// &= λ�����
#define Operator_And 0x2A				// && �߼���
#define Operator_Plus 0x2B				// + ��
#define Operator_Plus_Equal 0x2C		// += �ӵ���
#define Operator_Plus_Plus 0x2D			// ++ ����
#define Operator_Minus 0x2E				// - ��
#define Operator_Minus_Equal 0x2F		// -= ������
#define Operator_Minus_Minus 0x30		// -- �Լ�
#define Operator_Bit_Or 0x31			// | λ��
#define Operator_Bit_Or_Equal 0x32		// |= λ�����
#define Operator_Or 0x33				// || �߼���
#define Operator_Less_Than 0x34			// < С��
#define Operator_Less_Than_Equal 0x35	// <= С�ڵ���
#define Operator_Left_Shift 0x36		// << ����
#define Operator_More_Than 0x37			// > ����
#define Operator_More_Than_Equal 0x38	// >= ���ڵ���
#define Operator_Right_Shift 0x39		// >> ����
#define Operator_Multiply 0x3A			// * �� ��
#define Operator_Multiply_Equal 0x3B	// *= �˵���
#define Operator_Divide 0x3C			// / ��
#define Operator_Divide_Equal 0x3D		// /= ������
#define Operator_Colon 0x3E				// : ð��[��ʹ��]
#define Operator_Member 0x3F			// :: ��Ա�����
#define Operator_Arrows 0x40			// -> ��ͷ

//�ؼ��� Keyword
#define Keyword_auto 0x100 //auto
#define Keyword_break 0x101 //break
#define Keyword_case 0x102 //case
#define Keyword_char 0x103 //char
#define Keyword_const 0x104 //const
#define Keyword_continue 0x105 //continue
#define Keyword_default 0x106 //default
#define Keyword_do 0x107 //do
#define Keyword_double 0x108 //double
#define Keyword_else 0x109 //else
#define Keyword_enum 0x10A //enum
#define Keyword_extern 0x10B //extern
#define Keyword_float 0x10C //float
#define Keyword_for 0x10D //for
#define Keyword_goto 0x10E //goto
#define Keyword_if 0x10F //if
#define Keyword_inline 0x110 //inline
#define Keyword_int 0x111 //int
#define Keyword_long 0x112 //long
#define Keyword_register 0x113 //register
#define Keyword_restrict 0x114 //restrict
#define Keyword_return 0x115 //return
#define Keyword_short 0x116 //short
#define Keyword_signed 0x117 //signed
#define Keyword_sizeof 0x118 //sizeof
#define Keyword_static 0x119 //static
#define Keyword_struct 0x11A //struct
#define Keyword_switch 0x11B //switch
#define Keyword_typedef 0x11C //typedef
#define Keyword_union 0x11D //union
#define Keyword_unsigned 0x11E //unsigned
#define Keyword_void 0x11F //void
#define Keyword_volatile 0x120 //volatile
#define Keyword_while 0x121 //while
#define Keyword__bool 0x122 //_bool
#define Keyword__Complex 0x123 //_Complex
#define Keyword__Imaginary 0x124 //_Imaginary
//���BOOL�͹ؼ���
#define Keyword_true 0x125	//true
#define Keyword_false 0x126	//false
#define Keyword_print 0x127 //print
#define Keyword_scan 0x128	//scan