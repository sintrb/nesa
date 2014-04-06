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



typedef enum TYPE_DATATYPE{	//��������
	DATATYPE_NONE,		//��ֵ
	DATATYPE_ADDRESS,	//��ַ
	DATATYPE_ZPADDRESS,	//��ַ
	DATATYPE_WORD,			//��
	DATATYPE_BYTE,			//�ֽ�
	DATATYPE_HBYT,			//���ֽ�
	DATATYPE_LBYT,			//���ֽ�
	DATATYPE_RELATIVE,		//���ƫ��
	DATATYPE_LABEL,		//��ǩ
	DATATYPE_TASK,
	DATATYPE_BIG,	//����
}TYPE_DATATYPE;

typedef enum TYPE_NUMTYPE{	//��ֵ����
	NUMTYPE_UNKNOWN,	//δ֪����
	NUMTYPE_BIN,	//������
	NUMTYPE_OCT,
	NUMTYPE_DEC,	//ʮ����
	NUMTYPE_HEX	//ʮ������
}TYPE_NUMTYPE;

typedef struct TYPE_FORMATRESULT{	//������ʽ��ָ��
	TYPE_NAME ins;	//ָ���ַ���
	TYPE_DATATYPE type;	//ֵ����
	TYPE_BYTE flag;	//��ɱ�־��0:����ʽ 1:ֵ��ʽ
	TYPE_NAME datastr;	//����
	TYPE_WORD data;	//ֵ��
	
	void inf();
}TYPE_FORMATRESULT;

typedef struct TYPE_VALUERESULT{
	TYPE_DATATYPE type;
	TYPE_NAME datastr;	//����
	TYPE_NUM data;	//ֵ��
	TYPE_WORD flag;	//������
	void inf() const;
}TYPE_VALUERESULT;


class TYPE_BYTE_STRING{
public:
	TYPE_BYTE* buf;	//����
	TYPE_SIZE size;	//��С
	TYPE_SIZE capacity;	//����
	
	TYPE_BYTE_STRING();
	~TYPE_BYTE_STRING();
};

class TYPE_SEGMENT{//�ļ�����
public:
	TYPE_NAME name;	//���������
	TYPE_SIZE org;	//�������ʼλ��
	TYPE_SIZE size;	//����εĴ�С
	TYPE_SIZE offset;	//���ļ��е���ʼλ��
	TYPE_SIZE pos;	//����ε�ǰλ��

	TYPE_BYTE *buf;	//���ݻ���
	TYPE_BYTE fill;	//��������
	//org + pos Ϊ6502�е��ڴ��ַ
	//ÿ�����֮�����
	//��ǰ��С=pos-org


public:
	TYPE_ADDRESS nowpos() const;
	TYPE_SEGMENT();
	TYPE_SEGMENT(TYPE_NAME nm, TYPE_ADDRESS o, TYPE_SIZE s, TYPE_SIZE p = 0, TYPE_BYTE f = 0);
	void inf() const;	//��ʾ��Ϣ
};

class TYPE_RAMSEGMENT{//RAM�Ĵ����
protected:
	TYPE_NAME name;	//���������
	TYPE_ADDRESS org;	//�������ʼλ��
	TYPE_SIZE size;	//����εĴ�С
	TYPE_SIZE pos;	//����ε�ǰλ��
	
public:
	TYPE_RAMSEGMENT();
	TYPE_RAMSEGMENT(TYPE_NAME nm, TYPE_ADDRESS o, TYPE_SIZE s, TYPE_SIZE p = 0);
	
};

typedef struct TYPE_INSTRUCTION{
	TYPE_NAME ins;		//ָ����ʽ
	TYPE_BYTE code;	//������
	TYPE_SSIZE size;	//ռλ
	TYPE_DATATYPE type;	//������ʽ(��ַ,��, ���ƫ��)

	TYPE_INSTRUCTION();	//��ʼ������
	TYPE_INSTRUCTION(TYPE_NAME i, TYPE_BYTE c, TYPE_SSIZE s, TYPE_DATATYPE t = DATATYPE_NONE);	//��ʼ������
	void inf() const;	//��Ϣ
}TYPE_INSTRUCTION;

class TYPE_LABEL{	//��ǩ
public:
	TYPE_NAME label;	//��ǩ��
	TYPE_DATATYPE flag;	//��������(��ַ,��, �ֽ�)
	TYPE_WORD dat;	//ֵ
	
public:
	TYPE_LABEL();
	TYPE_LABEL(TYPE_NAME lb, TYPE_DATATYPE fg = DATATYPE_ADDRESS, TYPE_WORD d = 0);
	void inf() const;
};

class TYPE_POINT{//λ�ü�¼�����ڴ�����Ϣ���ռ������
protected:
	TYPE_FILENAME filename;	//�ļ���
	TYPE_LINE line;		//����
	
public:
	void up();	//��һ�����
	TYPE_LINE getline();	//��
	TYPE_FILENAME getfilename();	//�ļ���
	TYPE_POINT();
	TYPE_POINT(TYPE_FILENAME f, TYPE_LINE l);
	void set(TYPE_FILENAME f, TYPE_LINE l);	//����λ��
	void set(TYPE_LINE l);
	void set(TYPE_FILENAME f);
	void next();	//��һ��λ��
	
};

class TYPE_TASK{	//����
public:
	TYPE_NAME label;	//��ǩ
	TYPE_DATATYPE flag;	//��������(��ַ���֣��ֽڣ���λ����λ)
	TYPE_NAME segment;	//�����
	TYPE_ADDRESS address;	//��ַ
	TYPE_POINT point;	//�ļ�λ��
	
public:
	TYPE_TASK();
	TYPE_TASK(TYPE_NAME lb, TYPE_DATATYPE fg, TYPE_NAME seg, TYPE_ADDRESS add, TYPE_POINT pt);
	void inf();
};

class TYPE_FUNCTION{
protected:
	TYPE_NAME name;	//������
	TYPE_STRING body;	//������
	TYPE_SIZE ramsize;//�ڴ�����
	TYPE_SIZE romsize;//Rom����
	
public:
	TYPE_FUNCTION();
	TYPE_FUNCTION(TYPE_NAME nm, TYPE_STRING bd);
};

class TYPE_OUTFILE{
public:
	map<TYPE_NAME, TYPE_SEGMENT> segments;	//���������
	TYPE_FILENAME filename;	//�ļ���
	TYPE_SEGMENT* currentsegment;	//��ǰ�����
	TYPE_SIZE filesize;		//�ļ���С
	TYPE_SIZE currentsize;	//��ǰ��С
	TYPE_SIZE segmentcount;	//����θ���
public:
	TYPE_OUTFILE();
	TYPE_OUTFILE(TYPE_FILENAME fn);
	~TYPE_OUTFILE();
	TYPE_SIZE emptysize();	//����ʣ��ռ�
	void inf();	//��ʾ��Ϣ
};






typedef enum TYPE_ERROR{
	ERR_MISS_FH,	//ȱ�ֺ�:;
	ERR_MISS_YH,	//ȱ����:"
	ERR_MISS_LH,	//ȱ������:{
	ERR_MISS_RH,	//ȱ������:}
	ERR_MISS_ZS,	//ȱ��ע��:*/
	ERR_MISS_LK,	//ȱ������:(
	ERR_MISS_RK,	//ȱ������:)
	ERR_MISS_LF,	//ȱ������:[
	ERR_MISS_RF,	//ȱ�ҷ�����:]
	
	ERR_UK_LABEL,	//��ǩδ֪
	ERR_UK_SYM,		//δ֪����
	
	
	ERR_OUT_CODE,	//�������
	ERR_OUT_ORG,	//Org�������
	ERR_OUT_RANGE,	//��С���
	ERR_OUT_ADD,	//��ַ���
	ERR_OUT_REV,	//���Ѱַ���
	
	
	ERR_HAVA_SEG,	//������ظ�
	ERR_HAVA_LAB,	//��ǩ�ظ�
	ERR_HAVA_INS,	//ָ���ظ�
	
	
	ERR_HAVANO_SEG,		//����β�����
	ERR_HAVANO_FILE,	//�ļ�������
	ERR_HAVANO_LAB,		//��ǩ������
	
	
	ERR_UNDEFINE_SEG,	//����ζ���Ϊ��
	ERR_UNDEFINE_LAB,	//δ�����ǩ
	ERR_ERR_FILENAME, 	//�ļ�������
	ERR_EMPTY_FILENAME,	//�ļ�����
	ERR_OPEN_FILE,		//���ļ���ʧ��
	ERR_EMPTY_NUM,		//����Ϊ��
	
	ERR_ILL_SYN,	//�﷨����
	
	ERR_SIZE_SEG,	//����γߴ����
	
	ERR_CNT_LAB,	//���ܽ����ǩ����
	
	ERR_NOT_NUM,	//��������
	ERR_NOT_CONST,	//����ȷ������
	
}TYPE_ERROR;

typedef enum TYPE_WARNING{
	WARNING_NO_USING,	//������
	UNKNOWN_NUM_TYPE,	//λ����������
	UNKNOWN_MAC_TYPE,	//δ֪αָ��
	WARNING_EMPTY_NUM,	//������
	WARNING_ARE_INCFILE,	//�Ѱ����ļ�
	WARNING_FLOW_OVER,	//����
	WARNING_FLOW_UNDER,	//����
	WARNING_TYPE_WARN,	//���Ͳ�ƥ��
}TYPE_WARNING;


typedef map<TYPE_NAME, TYPE_LABEL> TYPE_LABELS;	//��ǩ��
typedef map<TYPE_NAME, TYPE_INSTRUCTION> TYPE_INSTRUCTIONS;	//ָ�
typedef vector<TYPE_TASK> TYPE_TASKS;	//����


namespace gloab{
	extern TYPE_CODE g_code_line;	//���ڱ��浱ǰ����Ĵ�����

	extern TYPE_POS g_code_len;	//���볤��
	extern TYPE_CODE g_ins;		//��ָ���С�ı���Ƭ��
	
	extern bool isShowErrline;		//�Ƿ����������
	
	extern TYPE_POINT g_filepoint;	//��¼��ǰ�ı���λ��
	
	extern TYPE_OUTFILE g_outfile;	//����ļ�
	
	extern TYPE_BYTE g_warninglevel; //���漶�� 0����߼���ʾ���ж� 1:�м�����ʾ 2:����ʾ
	extern TYPE_BYTE g_errorlevel;	//���󼶱� 0����߼���ʾ���ж� 1:�м�����ʾ 2:����ʾ
	
	extern TYPE_FILENAME g_outfilename;//����ļ���
	extern TYPE_FILENAME g_infilename;	//�����ļ�
	extern TYPE_STRING g_version;	//�汾��Ϣ
	
	extern TYPE_LABELS g_labels;	//ȫ�ֱ�ǩ��
	
	extern TYPE_INSTRUCTIONS g_inss;	//ָ�
	
	extern TYPE_TASKS g_tasks;	//����
	
	extern TYPE_FILE_ARRAY g_includedfiles;	//�԰������ļ�
	extern TYPE_INS_ARRAY g_insarray;	//������ĵ�ָ���
	
	extern const TYPE_NAME const_ins_ins[152]; //Ĭ��ָ�
	extern const TYPE_BYTE const_ins_code[152];
	extern const TYPE_SIZE const_ins_size[152];
	extern const TYPE_DATATYPE const_ins_type[152];
	
	extern bool g_insinf;	//ָ���־
	extern bool g_tasinf;	//�����־
	extern bool g_labinf;	//��ǩ��־
	extern bool g_seginf;	//����α�־
	
	extern unsigned long g_lbct; //������ǩ������
	
	extern TYPE_STRING_STACK g_labelname;	//{ջ
	extern TYPE_STRING_STACK g_taskname;	//}ջ
};


//map<TYPE_NAME, TYPE_SEGMENT> TYPE_SEGMENTS;	//����μ���

namespace gloabfunction{
	TYPE_STRING datatypetostring(TYPE_DATATYPE dt);	//��������
	TYPE_WORD datatypesize(TYPE_DATATYPE dt);	//���ݳ���
};


using namespace gloab;
#endif
