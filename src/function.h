#ifndef ASM2NES_FUNCTION
#define ASM2NES_FUNCTION
#include "stddef.h"

using namespace gloab;
namespace strprocess{	//ָ�����

	TYPE_STRING getstring(TYPE_STRING &str);	//��һ���ִ������ȡ�ִ�
	
	TYPE_STRING getstringarg(const TYPE_STRING str, TYPE_POS pos = 0);	//���ִ��л�ȡ��pos���ִ�����
	
	TYPE_STRING_ARRAY& getstringarray(const TYPE_STRING str, TYPE_POS pos = 0);	//��str�л�ȡ�ַ���(���ŷָ�)
	TYPE_KEYVALUE getkeyvalue(const TYPE_STRING str);	//��str�����ȡ��ֵ��
	TYPE_STRING_ARRAY& getdatastringarray(const TYPE_STRING str, TYPE_POS pos = 0);	//���ַ����л�ȡ�ַ���(���ſո�ָ�)
	TYPE_STATUS killfbspace(TYPE_STRING& str);	//ǰ��
	TYPE_STATUS killspace(TYPE_STRING& str);	//���ո�
	TYPE_STATUS getinsarray(TYPE_STRING& line, TYPE_STRING_ARRAY& insa, bool& isNote);//��ȡָ����
	inline char cupper(char c);	//��д
	TYPE_STRING& supper(TYPE_STRING& str); // ��д
	inline void tosupper(char *s);	// ��д
};

namespace insformat{	//��ָ���ʽ��
	TYPE_STATUS upperinstruction();	//��ָ���д��
	TYPE_STATUS formatinstruction(TYPE_STRING ins, TYPE_FORMATRESULT& rst);	//֪ʶ��ָ�����
}

namespace valueswitch{	//����ת��
	TYPE_WORD wordtodec(TYPE_HEX hex);	//ʮ�����Ƶ�ʮ����
	TYPE_HEX dectobyte(TYPE_WORD dec);	//ʮ���Ƶ��ֽ�
	TYPE_HEX dectoword(TYPE_WORD dec);	//ʮ�����Ƶ���
	TYPE_WORD bintodec(TYPE_BIN bin);	//�����Ƶ�ʮ����
	TYPE_BIN dectobin(TYPE_WORD dec);	//ʮ���Ƶ�������

	TYPE_NUM bintonum(TYPE_BIN bin);	//�����Ƶ�ʮ����
	TYPE_NUM hextonum(TYPE_HEX hex);	//ʮ�����Ƶ�ʮ����
	TYPE_NUM strtonum(TYPE_STRING str);	//��һ���ַ���ת��Ϊ����
	TYPE_NUM octtonum(TYPE_OCT oct);	//�˽��Ƶ�ʮ����
	
	TYPE_HEX numtohex(TYPE_NUM dec, TYPE_SIZE w = 4);	//תʮ������
	TYPE_STRING numtostr(TYPE_NUM num);	//ת��
	
	TYPE_NUMTYPE numtype(TYPE_STRING& str);	//����һ���ַ�������������
	TYPE_NUM numvalue(TYPE_STRING str);	//��һ��δ֪���͵�����ת����ʮ��������
	TYPE_STATUS valueresult(TYPE_STRING str, TYPE_VALUERESULT& vr);	//��ȡ������
}

namespace compile{	//����
	TYPE_STATUS compileall();
	TYPE_STATUS compileone(TYPE_STRING& ins);
};

namespace macro{		//αָ���
	TYPE_STATUS macrojudge(TYPE_STRING& mac);	//���жϺ�ָ��ַ�
	TYPE_STATUS m_point();		//�ļ���λָ��
	TYPE_STATUS m_segment();	//���õ�ǰ�����
	TYPE_STATUS m_string();	//��Ӵ�
	TYPE_STATUS m_org();	//���ô����
	TYPE_STATUS m_segmentdefine();	//��Ӵ����
	TYPE_STATUS m_byte();	//����ֽ���
	TYPE_STATUS m_word();	//�������
	TYPE_STATUS m_data();	//�������
	TYPE_STATUS m_includebin();//�����������ļ�
	TYPE_STATUS m_warning();	//���þ��漶��
	TYPE_STATUS m_error();		//���ô��󼶱�
	TYPE_STATUS m_label();		//��ǩ����
	TYPE_STATUS m_file();	//�ļ�
	TYPE_STATUS m_line();	//��
};

namespace errorprocess{	//������
	void front();	//��ʾ����ͷ
	void back();	//��ʾβ
	
	void showerr(TYPE_ERROR err);	//��ʾ����
	void showerr(TYPE_ERROR err, TYPE_STRING serr);


	void showwarning(TYPE_WARNING wn);	//��ʾ����
	void showwarning(TYPE_WARNING wn, TYPE_STRING swn);
};

namespace segmentmanager{	//����ι���
	TYPE_STATUS put(TYPE_BYTE dat);	//��ǰλ������һ�ֽ�
	TYPE_STATUS put(TYPE_WORD dat);	//�����
	TYPE_STATUS put(TYPE_STRING s);	//�����
	TYPE_STATUS put(char* s);		//�����
	TYPE_STATUS put(const TYPE_BYTE_STRING& bs);//���TYPE_BYTE_STRING�ṹ������
	TYPE_STATUS putreaddress(TYPE_ADDRESS add);	//д����Ե�ַ,����Ŀ�ĵ�ַ
	
	TYPE_STATUS addsegment(TYPE_SEGMENT sg);		//���Ӵ��������
	TYPE_STATUS setcurrentsegment(TYPE_NAME nm);	//���õ�ǰ�����
	TYPE_SEGMENT* getcurrentsegment();	//��ȡ��ǰ�Ĵ����
	TYPE_STATUS setfilename(TYPE_FILENAME fn);	//�����ļ���
	TYPE_STATUS saveoutfile(TYPE_FILENAME fn);	//�����ļ�
	TYPE_STATUS saveoutfile();	//�����ļ�
	TYPE_STATUS setorgaddress(TYPE_SIZE add);	//���ô���λ��
	TYPE_STATUS checkcurrnetsegment(); //��鵱ǰ�����Ƿ����
	TYPE_STATUS setstart();		//���õ�ǰ�����λ�õ���ʼλ��
	void segmentinf();	//��ʾ�������Ϣ
};

namespace fileio{	//IO
	TYPE_STATUS loadall(TYPE_FILENAME fn, TYPE_BYTE* dat);	//��ȡ�ļ�fn��ȫ�����ݵ�dat
	TYPE_STATUS loadall(TYPE_FILENAME fn, TYPE_BYTE_STRING& bs);
	TYPE_STATUS loadtxt(TYPE_FILENAME fn, TYPE_BYTE_STRING& bs);	//��ȡ�ı��ļ�
	TYPE_STATUS saveall(TYPE_FILENAME fn, TYPE_BYTE* dat, TYPE_SIZE sz);//����
	TYPE_STATUS saveall(TYPE_FILENAME fn, TYPE_BYTE_STRING& sa);//����
	TYPE_STATUS loadtxtarray(TYPE_FILENAME fn, TYPE_STRING_ARRAY& sa);	//���ļ����ִ���


	FILE * safeopen(const char *fname, const char *status);
};

namespace label{	//��ǩ
	void labelinf(TYPE_LABELS& lbs = g_labels);	//�����ǩ��Ϣ
	TYPE_STATUS addlabel(TYPE_LABEL lb, TYPE_LABELS& lbs = g_labels);	//��ӱ�ǩ
	TYPE_STATUS getlabel(TYPE_NAME name, TYPE_LABEL& lb, TYPE_LABELS& lbs = g_labels);	//��ȡ��ǩ
	TYPE_STATUS addcurrentadd(TYPE_NAME nm, TYPE_LABELS& lbs = g_labels);	//��ӵ�ǰ��ַ����ǩ
	
	TYPE_NAME getnextlabel(TYPE_POS offset=1);//��ȡ��һ����ǩ
	TYPE_NAME getprelabel(TYPE_POS offset=1);//��ȡ��һ����ǩ
	TYPE_STATUS addnonamelabel();	//���������ǩ
	TYPE_NAME next();	//�Զ��Ƶ���һ��
};

namespace instruction{	//ָ��
	TYPE_STATUS init();	//��ʼ��
	TYPE_STATUS addins(TYPE_INSTRUCTION ins);	//���ָ��
	TYPE_INSTRUCTION* find(TYPE_NAME nm);	//����ָ��
	TYPE_STATUS compileins(TYPE_STRING& ins);	//���뵥ָ��
	void inf();	//��Ϣ
};

namespace task{	//�������
	TYPE_STATUS addtask(TYPE_NAME lb, TYPE_DATATYPE fg); //��ӱ�ǩ
	void taskinf();	//��Ϣ
	TYPE_STATUS dotask();	//������
};

namespace preprocess{	//Ԥ����
	TYPE_STATUS includefile(TYPE_FILENAME fn);	//�����ļ�
	void inf();	//��Ϣ
};

namespace arguments{
	TYPE_STATUS initarg(int args, char *arg[]);	//��ʼ������
	void version();	//�汾
	void help();	//����
};


//using namespace strprocess;
//using namespace insformat;
//using namespace valueswitch;
//using namespace errorprocess;
//using namespace segmentmanager;
#endif

