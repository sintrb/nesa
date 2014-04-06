#ifndef STDDEF
#define STDDEF
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <stack>
using namespace std;

//typedef for often types
typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned short address;
typedef unsigned int TYPE_ADDRESS;
typedef unsigned short TYPE_WORD;
typedef unsigned char TYPE_BYTE;
typedef string TYPE_HEX;
typedef string TYPE_OCT;
typedef string TYPE_BIN;
typedef string TYPE_NAME;
typedef string TYPE_ASMNAME;
typedef unsigned char TYPE_SSIZE;
typedef unsigned char TYPE_SPOS;
typedef unsigned long TYPE_SIZE;
typedef unsigned long TYPE_POS;
typedef long TYPE_OFFSET;
typedef unsigned int TYPE_NUM;
typedef int TYPE_STATUS;
typedef string TYPE_FILENAME;
typedef string TYPE_STRING;
typedef unsigned int TYPE_LINE;
typedef string TYPE_CODE;


typedef struct TYPE_KEYVALUE{
	TYPE_STRING key;
	TYPE_STRING value;
}TYPE_KEYVALUE;

typedef vector<TYPE_STRING> TYPE_STRING_ARRAY;
typedef set<TYPE_FILENAME> TYPE_FILE_ARRAY;
typedef vector<TYPE_KEYVALUE> TYPE_KEYVALUE_ARRAY;
typedef vector<TYPE_STRING> TYPE_INS_ARRAY;
typedef stack<TYPE_STRING> TYPE_STRING_STACK;



typedef enum TYPE_DATATYPE{	//数据类型
	DATATYPE_NONE,		//空值
	DATATYPE_ADDRESS,	//地址
	DATATYPE_ZPADDRESS,	//地址
	DATATYPE_WORD,			//字
	DATATYPE_BYTE,			//字节
	DATATYPE_HBYT,			//高字节
	DATATYPE_LBYT,			//低字节
	DATATYPE_RELATIVE,		//相对偏移
	DATATYPE_LABEL,		//标签
	DATATYPE_TASK,
	DATATYPE_BIG,	//大数
}TYPE_DATATYPE;

typedef enum TYPE_NUMTYPE{	//数值类型
	NUMTYPE_UNKNOWN,	//未知类型
	NUMTYPE_BIN,	//二进制
	NUMTYPE_OCT,
	NUMTYPE_DEC,	//十进制
	NUMTYPE_HEX	//十六进制
}TYPE_NUMTYPE;

typedef struct TYPE_FORMATRESULT{	//处理后格式化指令
	TYPE_NAME ins;	//指令字符串
	TYPE_DATATYPE type;	//值类型
	TYPE_BYTE flag;	//完成标志，0:串形式 1:值形式
	TYPE_NAME datastr;	//串域
	TYPE_WORD data;	//值域
	
	void inf();
}TYPE_FORMATRESULT;

typedef struct TYPE_VALUERESULT{
	TYPE_DATATYPE type;
	TYPE_NAME datastr;	//串域
	TYPE_NUM data;	//值域
	TYPE_WORD flag;	//计算域
	void inf() const;
}TYPE_VALUERESULT;


class TYPE_BYTE_STRING{
public:
	TYPE_BYTE* buf;	//缓存
	TYPE_SIZE size;	//大小
	TYPE_SIZE capacity;	//容量
	
	TYPE_BYTE_STRING();
	~TYPE_BYTE_STRING();
};

class TYPE_SEGMENT{//文件布局
public:
	TYPE_NAME name;	//代码段名称
	TYPE_SIZE org;	//代码段起始位置
	TYPE_SIZE size;	//代码段的大小
	TYPE_SIZE offset;	//在文件中的起始位置
	TYPE_SIZE pos;	//代码段当前位置

	TYPE_BYTE *buf;	//数据缓冲
	TYPE_BYTE fill;	//填充的数据
	//org + pos 为6502中的内存地址
	//每次填充之后后移
	//当前大小=pos-org


public:
	TYPE_ADDRESS nowpos() const;
	TYPE_SEGMENT();
	TYPE_SEGMENT(TYPE_NAME nm, TYPE_ADDRESS o, TYPE_SIZE s, TYPE_SIZE p = 0, TYPE_BYTE f = 0);
	void inf() const;	//显示信息
};

class TYPE_RAMSEGMENT{//RAM的代码段
protected:
	TYPE_NAME name;	//代码段名称
	TYPE_ADDRESS org;	//代码段起始位置
	TYPE_SIZE size;	//代码段的大小
	TYPE_SIZE pos;	//代码段当前位置
	
public:
	TYPE_RAMSEGMENT();
	TYPE_RAMSEGMENT(TYPE_NAME nm, TYPE_ADDRESS o, TYPE_SIZE s, TYPE_SIZE p = 0);
	
};

typedef struct TYPE_INSTRUCTION{
	TYPE_NAME ins;		//指令形式
	TYPE_BYTE code;	//机器码
	TYPE_SSIZE size;	//占位
	TYPE_DATATYPE type;	//数据形式(地址,字, 相对偏移)

	TYPE_INSTRUCTION();	//初始化函数
	TYPE_INSTRUCTION(TYPE_NAME i, TYPE_BYTE c, TYPE_SSIZE s, TYPE_DATATYPE t = DATATYPE_NONE);	//初始化函数
	void inf() const;	//信息
}TYPE_INSTRUCTION;

class TYPE_LABEL{	//标签
public:
	TYPE_NAME label;	//标签名
	TYPE_DATATYPE flag;	//数据类型(地址,字, 字节)
	TYPE_WORD dat;	//值
	
public:
	TYPE_LABEL();
	TYPE_LABEL(TYPE_NAME lb, TYPE_DATATYPE fg = DATATYPE_ADDRESS, TYPE_WORD d = 0);
	void inf() const;
};

class TYPE_POINT{//位置记录，用于错误信息的收集和输出
protected:
	TYPE_FILENAME filename;	//文件名
	TYPE_LINE line;		//行数
	
public:
	void up();	//上一个标记
	TYPE_LINE getline();	//行
	TYPE_FILENAME getfilename();	//文件名
	TYPE_POINT();
	TYPE_POINT(TYPE_FILENAME f, TYPE_LINE l);
	void set(TYPE_FILENAME f, TYPE_LINE l);	//设置位置
	void set(TYPE_LINE l);
	void set(TYPE_FILENAME f);
	void next();	//下一个位置
	
};

class TYPE_TASK{	//任务
public:
	TYPE_NAME label;	//标签
	TYPE_DATATYPE flag;	//任务类型(地址，字，字节，高位，低位)
	TYPE_NAME segment;	//代码段
	TYPE_ADDRESS address;	//地址
	TYPE_POINT point;	//文件位置
	
public:
	TYPE_TASK();
	TYPE_TASK(TYPE_NAME lb, TYPE_DATATYPE fg, TYPE_NAME seg, TYPE_ADDRESS add, TYPE_POINT pt);
	void inf();
};

class TYPE_FUNCTION{
protected:
	TYPE_NAME name;	//函数名
	TYPE_STRING body;	//函数体
	TYPE_SIZE ramsize;//内存消耗
	TYPE_SIZE romsize;//Rom消耗
	
public:
	TYPE_FUNCTION();
	TYPE_FUNCTION(TYPE_NAME nm, TYPE_STRING bd);
};

class TYPE_OUTFILE{
public:
	map<TYPE_NAME, TYPE_SEGMENT> segments;	//代码段描述
	TYPE_FILENAME filename;	//文件名
	TYPE_SEGMENT* currentsegment;	//当前代码段
	TYPE_SIZE filesize;		//文件大小
	TYPE_SIZE currentsize;	//当前大小
	TYPE_SIZE segmentcount;	//代码段个数
public:
	TYPE_OUTFILE();
	TYPE_OUTFILE(TYPE_FILENAME fn);
	~TYPE_OUTFILE();
	TYPE_SIZE emptysize();	//返回剩余空间
	void inf();	//显示信息
};






typedef enum TYPE_ERROR{
	ERR_MISS_FH,	//缺分号:;
	ERR_MISS_YH,	//缺引号:"
	ERR_MISS_LH,	//缺左花括号:{
	ERR_MISS_RH,	//缺左花括号:}
	ERR_MISS_ZS,	//缺右注释:*/
	ERR_MISS_LK,	//缺左括号:(
	ERR_MISS_RK,	//缺右括号:)
	ERR_MISS_LF,	//缺左方括号:[
	ERR_MISS_RF,	//缺右方括号:]
	
	ERR_UK_LABEL,	//标签未知
	ERR_UK_SYM,		//未知符号
	
	
	ERR_OUT_CODE,	//代码溢出
	ERR_OUT_ORG,	//Org设置溢出
	ERR_OUT_RANGE,	//大小溢出
	ERR_OUT_ADD,	//地址溢出
	ERR_OUT_REV,	//相对寻址溢出
	
	
	ERR_HAVA_SEG,	//代码段重复
	ERR_HAVA_LAB,	//标签重复
	ERR_HAVA_INS,	//指令重复
	
	
	ERR_HAVANO_SEG,		//代码段不存在
	ERR_HAVANO_FILE,	//文件不存在
	ERR_HAVANO_LAB,		//标签不存在
	
	
	ERR_UNDEFINE_SEG,	//代码段定义为空
	ERR_UNDEFINE_LAB,	//未定义标签
	ERR_ERR_FILENAME, 	//文件名问题
	ERR_EMPTY_FILENAME,	//文件名空
	ERR_OPEN_FILE,		//打开文件夹失败
	ERR_EMPTY_NUM,		//数字为空
	
	ERR_ILL_SYN,	//语法错误
	
	ERR_SIZE_SEG,	//代码段尺寸错误
	
	ERR_CNT_LAB,	//不能解决标签问题
	
	ERR_NOT_NUM,	//不是数字
	ERR_NOT_CONST,	//不是确定的数
	
}TYPE_ERROR;

typedef enum TYPE_WARNING{
	WARNING_NO_USING,	//无意义
	UNKNOWN_NUM_TYPE,	//位置数制类型
	UNKNOWN_MAC_TYPE,	//未知伪指令
	WARNING_EMPTY_NUM,	//空数据
	WARNING_ARE_INCFILE,	//已包含文件
	WARNING_FLOW_OVER,	//上溢
	WARNING_FLOW_UNDER,	//下溢
	WARNING_TYPE_WARN,	//类型不匹配
}TYPE_WARNING;


typedef map<TYPE_NAME, TYPE_LABEL> TYPE_LABELS;	//标签集
typedef map<TYPE_NAME, TYPE_INSTRUCTION> TYPE_INSTRUCTIONS;	//指令集
typedef vector<TYPE_TASK> TYPE_TASKS;	//任务集


namespace gloab{
	extern TYPE_CODE g_code_line;	//用于保存当前编译的代码行

	extern TYPE_POS g_code_len;	//代码长度
	extern TYPE_CODE g_ins;		//单指令，最小的编译片段
	
	extern bool isShowErrline;		//是否输出错误行
	
	extern TYPE_POINT g_filepoint;	//记录当前的编译位置
	
	extern TYPE_OUTFILE g_outfile;	//输出文件
	
	extern TYPE_BYTE g_warninglevel; //警告级别 0：最高级显示并中断 1:中级仅显示 2:不显示
	extern TYPE_BYTE g_errorlevel;	//错误级别 0：最高级显示并中断 1:中级仅显示 2:不显示
	
	extern TYPE_FILENAME g_outfilename;//输出文件名
	extern TYPE_FILENAME g_infilename;	//输入文件
	extern TYPE_STRING g_version;	//版本信息
	
	extern TYPE_LABELS g_labels;	//全局标签集
	
	extern TYPE_INSTRUCTIONS g_inss;	//指令集
	
	extern TYPE_TASKS g_tasks;	//任务集
	
	extern TYPE_FILE_ARRAY g_includedfiles;	//以包含的文件
	extern TYPE_INS_ARRAY g_insarray;	//解析后的单指令集合
	
	extern const TYPE_NAME const_ins_ins[152]; //默认指令集
	extern const TYPE_BYTE const_ins_code[152];
	extern const TYPE_SIZE const_ins_size[152];
	extern const TYPE_DATATYPE const_ins_type[152];
	
	extern bool g_insinf;	//指令标志
	extern bool g_tasinf;	//任务标志
	extern bool g_labinf;	//标签标志
	extern bool g_seginf;	//代码段标志
	
	extern unsigned long g_lbct; //匿名标签计数器
	
	extern TYPE_STRING_STACK g_labelname;	//{栈
	extern TYPE_STRING_STACK g_taskname;	//}栈
};


//map<TYPE_NAME, TYPE_SEGMENT> TYPE_SEGMENTS;	//代码段集合

namespace gloabfunction{
	TYPE_STRING datatypetostring(TYPE_DATATYPE dt);	//数据描述
	TYPE_WORD datatypesize(TYPE_DATATYPE dt);	//数据长度
};


using namespace gloab;
#endif
