#pragma once
/**
* 命名空间: None
*
* 功 能： 定义miniC语言的单词编码
* 类 名： None
*
* Ver 2016-06-10 张赛 定义miniC语言的单词编码及相关宏定义
* ───────────────────────────────────
* V0.02 2016-06-10 张赛 2版
*
* Copyright (c) 2015 Lir Corporation. All rights reserved.
*┌──────────────────────────────────┐
*│　此技术信息为本公司机密信息，未经本公司书面同意禁止向第三方披露．　│
*│　版权所有：*****有限公司 　　　              　　　　　　　　　　　│
*└──────────────────────────────────┘
*/
//未识别
#define Error 0xFFF //错误的单词
#define Unknown 0x00	//未识别
//关键字或者标识符
#define Identifier 0x01//标识符
#define Character 0x02	//字符
#define String 0x03 //字符串
#define Number_Exponent 0x04 //指数 
#define Number_Decimals 0x05 //小数
#define Number_Decimalism 0x06 //整数 [十进制]
#define Number_Octonary 0x07 //整数 [八进制]
#define Number_Hexadecimal 0x08 //整数 [十六进制]

#define Grammar_Nonterminator 0x0A	//定义非终结符

//界符 ( ) ; [ ] { } . , ~ 共10个字符
// $ 在文法分析时会用到
#define Delimiter_Left_Small_Bracket 0x11	// ( 左小括号
#define Delimiter_Right_Small_Bracket 0x12	// ) 右小括号
#define Delimiter_Semicolon 0x13			// ; 分号
#define Delimiter_Left_Middle_Bracket 0x14	// [ 左中括号
#define Delimiter_Right_Middle_Bracket 0x15	// ] 右中括号
#define Delimiter_Left_Large_Bracket 0x16	// { 左大括号
#define Delimiter_Right_Large_Bracket 0x17	// } 右大括号
#define Delimiter_Period 0x18				// . 句号
#define Delimiter_Comma 0x19				// , 逗号
#define Delimiter_Tilde 0x1A				// ~ 波浪字符
#define Delimiter_Pound_Sign 0x1B			// # 井号
#define Delimiter_Dollar 0x1C				// $ 美元符号 源代码中的异常字符，文法中的空符号

//运算符
#define Operator_Not 0x20				// ! 非
#define Operator_Not_Equal_To 0x21		// != 不等于
#define Operator_Mod 0x22				// % 取余
#define Operator_Mod_Equal 0x23			// %= 取余等于
#define Operator_Equal 0x24				// = 等于
#define Operator_Is_Equal 0x25			// == 是否等于
#define Operator_Xor 0x26				// ^ 异或
#define Operator_Xor_Equal 0x27			// ^= 异或等于
#define Operator_Bit_And 0x28			// & 位与
#define Operator_Bit_And_Equal 0x29		// &= 位与等于
#define Operator_And 0x2A				// && 逻辑与
#define Operator_Plus 0x2B				// + 加
#define Operator_Plus_Equal 0x2C		// += 加等于
#define Operator_Plus_Plus 0x2D			// ++ 自增
#define Operator_Minus 0x2E				// - 减
#define Operator_Minus_Equal 0x2F		// -= 减等于
#define Operator_Minus_Minus 0x30		// -- 自减
#define Operator_Bit_Or 0x31			// | 位或
#define Operator_Bit_Or_Equal 0x32		// |= 位或等于
#define Operator_Or 0x33				// || 逻辑或
#define Operator_Less_Than 0x34			// < 小于
#define Operator_Less_Than_Equal 0x35	// <= 小于等于
#define Operator_Left_Shift 0x36		// << 左移
#define Operator_More_Than 0x37			// > 大于
#define Operator_More_Than_Equal 0x38	// >= 大于等于
#define Operator_Right_Shift 0x39		// >> 右移
#define Operator_Multiply 0x3A			// * 乘 星
#define Operator_Multiply_Equal 0x3B	// *= 乘等于
#define Operator_Divide 0x3C			// / 除
#define Operator_Divide_Equal 0x3D		// /= 除等于
#define Operator_Colon 0x3E				// : 冒号[待使用]
#define Operator_Member 0x3F			// :: 成员运算符
#define Operator_Arrows 0x40			// -> 箭头

//关键词 Keyword
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
//添加BOOL型关键词
#define Keyword_true 0x125	//true
#define Keyword_false 0x126	//false
#define Keyword_print 0x127 //print
#define Keyword_scan 0x128	//scan
