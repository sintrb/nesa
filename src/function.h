#ifndef ASM2NES_FUNCTION
#define ASM2NES_FUNCTION
#include "stddef.h"

using namespace gloab;
namespace strprocess{	//指令操作

	TYPE_STRING getstring(TYPE_STRING &str);	//从一个字串里面获取字串
	
	TYPE_STRING getstringarg(const TYPE_STRING str, TYPE_POS pos = 0);	//从字串中获取第pos个字串参数
	
	TYPE_STRING_ARRAY& getstringarray(const TYPE_STRING str, TYPE_POS pos = 0);	//从str中获取字符组(逗号分割)
	TYPE_KEYVALUE getkeyvalue(const TYPE_STRING str);	//从str里面获取键值对
	TYPE_STRING_ARRAY& getdatastringarray(const TYPE_STRING str, TYPE_POS pos = 0);	//从字符串中获取字符组(逗号空格分割)
	TYPE_STATUS killfbspace(TYPE_STRING& str);	//前后导
	TYPE_STATUS killspace(TYPE_STRING& str);	//除空格
	TYPE_STATUS getinsarray(TYPE_STRING& line, TYPE_STRING_ARRAY& insa, bool& isNote);//获取指令组
	inline char cupper(char c);	//大写
	TYPE_STRING& supper(TYPE_STRING& str); // 大写
	inline void tosupper(char *s);	// 大写
};

namespace insformat{	//单指令格式化
	TYPE_STATUS upperinstruction();	//单指令大写化
	TYPE_STATUS formatinstruction(TYPE_STRING ins, TYPE_FORMATRESULT& rst);	//知识化指令语句
}

namespace valueswitch{	//数据转换
	TYPE_WORD wordtodec(TYPE_HEX hex);	//十六进制到十进制
	TYPE_HEX dectobyte(TYPE_WORD dec);	//十进制到字节
	TYPE_HEX dectoword(TYPE_WORD dec);	//十六进制到字
	TYPE_WORD bintodec(TYPE_BIN bin);	//二进制到十进制
	TYPE_BIN dectobin(TYPE_WORD dec);	//十进制到二进制

	TYPE_NUM bintonum(TYPE_BIN bin);	//二进制到十进制
	TYPE_NUM hextonum(TYPE_HEX hex);	//十六进制到十进制
	TYPE_NUM strtonum(TYPE_STRING str);	//将一个字符串转换为数字
	TYPE_NUM octtonum(TYPE_OCT oct);	//八进制到十进制
	
	TYPE_HEX numtohex(TYPE_NUM dec, TYPE_SIZE w = 4);	//转十六进制
	TYPE_STRING numtostr(TYPE_NUM num);	//转串
	
	TYPE_NUMTYPE numtype(TYPE_STRING& str);	//返回一个字符串的数据类型
	TYPE_NUM numvalue(TYPE_STRING str);	//将一个未知类型的数据转换成十进制数据
	TYPE_STATUS valueresult(TYPE_STRING str, TYPE_VALUERESULT& vr);	//获取处理结果
}

namespace compile{	//编译
	TYPE_STATUS compileall();
	TYPE_STATUS compileone(TYPE_STRING& ins);
};

namespace macro{		//伪指令处理
	TYPE_STATUS macrojudge(TYPE_STRING& mac);	//宏判断和指令分发
	TYPE_STATUS m_point();		//文件定位指令
	TYPE_STATUS m_segment();	//设置当前代码段
	TYPE_STATUS m_string();	//添加串
	TYPE_STATUS m_org();	//设置代码段
	TYPE_STATUS m_segmentdefine();	//添加代码段
	TYPE_STATUS m_byte();	//添加字节组
	TYPE_STATUS m_word();	//添加字组
	TYPE_STATUS m_data();	//添加数据
	TYPE_STATUS m_includebin();//包含二进制文件
	TYPE_STATUS m_warning();	//设置警告级别
	TYPE_STATUS m_error();		//设置错误级别
	TYPE_STATUS m_label();		//标签定义
	TYPE_STATUS m_file();	//文件
	TYPE_STATUS m_line();	//行
};

namespace errorprocess{	//错误处理
	void front();	//显示错误头
	void back();	//显示尾
	
	void showerr(TYPE_ERROR err);	//显示错误
	void showerr(TYPE_ERROR err, TYPE_STRING serr);


	void showwarning(TYPE_WARNING wn);	//显示警告
	void showwarning(TYPE_WARNING wn, TYPE_STRING swn);
};

namespace segmentmanager{	//代码段管理
	TYPE_STATUS put(TYPE_BYTE dat);	//向当前位置输入一字节
	TYPE_STATUS put(TYPE_WORD dat);	//输出字
	TYPE_STATUS put(TYPE_STRING s);	//输出串
	TYPE_STATUS put(char* s);		//输出串
	TYPE_STATUS put(const TYPE_BYTE_STRING& bs);//输出TYPE_BYTE_STRING结构的数据
	TYPE_STATUS putreaddress(TYPE_ADDRESS add);	//写入相对地址,出入目的地址
	
	TYPE_STATUS addsegment(TYPE_SEGMENT sg);		//增加代码段描述
	TYPE_STATUS setcurrentsegment(TYPE_NAME nm);	//设置当前代码段
	TYPE_SEGMENT* getcurrentsegment();	//获取当前的代码段
	TYPE_STATUS setfilename(TYPE_FILENAME fn);	//设置文件名
	TYPE_STATUS saveoutfile(TYPE_FILENAME fn);	//保存文件
	TYPE_STATUS saveoutfile();	//保存文件
	TYPE_STATUS setorgaddress(TYPE_SIZE add);	//设置代码位置
	TYPE_STATUS checkcurrnetsegment(); //检查当前代码是否可用
	TYPE_STATUS setstart();		//设置当前代码段位置到起始位置
	void segmentinf();	//显示代码段信息
};

namespace fileio{	//IO
	TYPE_STATUS loadall(TYPE_FILENAME fn, TYPE_BYTE* dat);	//读取文件fn的全部内容到dat
	TYPE_STATUS loadall(TYPE_FILENAME fn, TYPE_BYTE_STRING& bs);
	TYPE_STATUS loadtxt(TYPE_FILENAME fn, TYPE_BYTE_STRING& bs);	//读取文本文件
	TYPE_STATUS saveall(TYPE_FILENAME fn, TYPE_BYTE* dat, TYPE_SIZE sz);//保存
	TYPE_STATUS saveall(TYPE_FILENAME fn, TYPE_BYTE_STRING& sa);//保存
	TYPE_STATUS loadtxtarray(TYPE_FILENAME fn, TYPE_STRING_ARRAY& sa);	//读文件到字串组


	FILE * safeopen(const char *fname, const char *status);
};

namespace label{	//标签
	void labelinf(TYPE_LABELS& lbs = g_labels);	//输出标签信息
	TYPE_STATUS addlabel(TYPE_LABEL lb, TYPE_LABELS& lbs = g_labels);	//添加标签
	TYPE_STATUS getlabel(TYPE_NAME name, TYPE_LABEL& lb, TYPE_LABELS& lbs = g_labels);	//获取标签
	TYPE_STATUS addcurrentadd(TYPE_NAME nm, TYPE_LABELS& lbs = g_labels);	//添加当前地址到标签
	
	TYPE_NAME getnextlabel(TYPE_POS offset=1);//获取下一个标签
	TYPE_NAME getprelabel(TYPE_POS offset=1);//获取下一个标签
	TYPE_STATUS addnonamelabel();	//添加匿名标签
	TYPE_NAME next();	//自动移到下一条
};

namespace instruction{	//指令
	TYPE_STATUS init();	//初始化
	TYPE_STATUS addins(TYPE_INSTRUCTION ins);	//添加指令
	TYPE_INSTRUCTION* find(TYPE_NAME nm);	//查找指令
	TYPE_STATUS compileins(TYPE_STRING& ins);	//编译单指令
	void inf();	//信息
};

namespace task{	//任务操作
	TYPE_STATUS addtask(TYPE_NAME lb, TYPE_DATATYPE fg); //添加标签
	void taskinf();	//信息
	TYPE_STATUS dotask();	//做任务
};

namespace preprocess{	//预处理
	TYPE_STATUS includefile(TYPE_FILENAME fn);	//包含文件
	void inf();	//信息
};

namespace arguments{
	TYPE_STATUS initarg(int args, char *arg[]);	//初始化参数
	void version();	//版本
	void help();	//帮助
};


//using namespace strprocess;
//using namespace insformat;
//using namespace valueswitch;
//using namespace errorprocess;
//using namespace segmentmanager;
#endif

