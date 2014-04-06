#include "function.h"

/*
该函数用于将指令大写化
2011-01-29
22:27
*/
TYPE_STATUS insformat::upperinstruction()
{
	TYPE_POS i = 0;
	TYPE_POS l = g_ins.length();
	bool isString = false;
	while(i < l){
		if(g_ins[i] =='\"'){
			isString = !isString;
		}
		else if(g_ins[i] >= 'a' && g_ins[i] <= 'z' && !isString){
			g_ins[i] += 'A' - 'a';
		}
		++i;
	}
	return 1;
}


/*
该函数用于将语句格式化，返回处理结果结构
2011-02-10
18:40
*/
TYPE_STATUS insformat::formatinstruction(TYPE_STRING ins, TYPE_FORMATRESULT& rst)
{
	TYPE_POS sp = ins.find(' ');
	TYPE_POS st = ins.find_first_not_of(' ', sp);
	TYPE_STRING lins = ins.substr(0, sp);
	TYPE_STRING rins = "";
	strprocess::supper(lins);
	if(st < ins.length())rins = ins.substr(st, string::npos);
	TYPE_POS l = rins.length();
	TYPE_POS i = 0;
	TYPE_POS j = 0;
	char* s = new char[l+1];
	while(i < l){
		if(rins[i] != ' ' && rins[i] != '\t' && rins[i] != '\"' && rins[i] != '\r'){
			s[j++] = rins[i];
		}
		++i;
	}
	s[j] = '\0';
	rins = s;
	delete s;
	l = rins.length();
	if(l > 0){	//包含地址或者数据
		TYPE_STRING ls = "";
		TYPE_STRING add = "";
		TYPE_STRING rs = "";
		i = 0;
		while(i < l && (rins[i] == '(' || rins[i] == ',' || rins[i] == ')')){
			ls += rins[i];
			++i;
		}

		while(i < l && rins[i] != '(' && rins[i] != ',' && rins[i] != ')'){
			add += rins[i];
			++i;
		}

		while(i < l){
			rs += rins[i];
			++i;
		}

		//cout<<"LS:"<<ls<<endl;
		//cout<<"RS:"<<rs<<endl;
		//cout<<"ADD:"<<add<<endl;

		TYPE_VALUERESULT vr;
		valueswitch::valueresult(add, vr);
		rst.flag = vr.flag;
		rst.data = vr.data;
		rst.datastr = vr.datastr;
		rst.type = vr.type;
		if(vr.type == DATATYPE_BYTE){
			add = "#$xx";
		}
		else if(vr.type == DATATYPE_ZPADDRESS){
			add = "$xx";
		}
		else{
			add = "$xxxx";
		}
		rst.ins = lins + " " + ls + add + rs;
	}
	else{	//简单指令
		rst.ins = lins;	//格式指令
		rst.flag = 1;	//值标志:未计算
		rst.type = DATATYPE_NONE;	//无值
	}
	return 1;
}








