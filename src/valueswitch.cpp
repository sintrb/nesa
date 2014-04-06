#include "function.h"

#define HexCharValue(c) ((c)>='0' && (c)<='9')?(c-'0'):(((c)>='A' && (c)<='F')?(c-'A' + 10):0)
#define CharDecValue(v) (v)<10?('0' + (char)(v)):((v)<16?('A' + (char)((v)-10)):'0')

/*
该函数用于将一个十六进制转换为十进制
2011-01-29
22:50
*/
TYPE_WORD valueswitch::wordtodec(TYPE_HEX hex)
{
	TYPE_WORD dec = 0;
	int i = 0;
	int l = hex.length();
	while(i < l){
		dec <<= 4;
		dec |= (HexCharValue(hex[i]));
		++i;
	}
	return dec;
}

/*
该函数用于将一个十进制转换为十六进制，字节表示
2011-01-29
23:00
*/
TYPE_HEX valueswitch::dectobyte(TYPE_WORD dec)
{
	char chex[3];
	dec %= 0x100;
	chex[0] = CharDecValue(dec/0x10);
	chex[1] = CharDecValue(dec%0x10);
	chex[2] = '\0';
	return chex;
}	


/*
该函数用于将一个十进制转换为十六进制，字表示
2011-01-29
23:06
*/
TYPE_HEX valueswitch::dectoword(TYPE_WORD dec)
{
	char chex[5];
	dec %= 0x10000;
	chex[0] = CharDecValue(dec/0x1000);
	dec %= 0x1000;
	chex[1] = CharDecValue(dec/0x100);
	dec %= 0x100;
	chex[2] = CharDecValue(dec/0x10);
	chex[3] = CharDecValue(dec%0x10);
	chex[4] = '\0';
	return chex;
}

/*
该函数用于将一个二进制转换为十进制，字表示
2011-01-30
11:06
*/
TYPE_WORD valueswitch::bintodec(TYPE_BIN bin)
{
	int l = bin.length();
	int i = 0;
	TYPE_WORD dec = 0;
	while(i < l){
		switch(bin[i])
		{
			case '0':{
				dec <<= 1;
				break;
			}
			case '1':{
				dec <<= 1;
				dec |= 0x0001;
				break;
			}
			default:{
				return dec;
			}
		}
		++i;
	}
	return dec;
}

/*
该函数用于将一个十进制进制转换为二进制
2011-01-30
11:22
*/
TYPE_BIN valueswitch::dectobin(TYPE_WORD dec)
{
	char s[17];
	int i = 16;
	dec &= 0xffff;
	s[i--] = '\0';
	if(dec == 0){
		s[i--] = '0';
	}
	while(dec){
		if(dec & 0x0001){
			s[i--] = '1';
		}
		else{
			s[i--] = '0';
		}
		dec >>= 1;
	}
	TYPE_BIN str = &s[++i];
	return str;
}


/*
该函数用于将一个二进制转换为十进制
2011-01-30
14:38
*/
TYPE_NUM valueswitch::bintonum(TYPE_BIN bin)
{
	int l = bin.length();
	int i = 0;
	TYPE_NUM dec = 0;
	while(i < l){
		switch(bin[i])
		{
			case '0':{
				dec <<= 1;
				break;
			}
			case '1':{
				dec <<= 1;
				dec |= 0x0001;
				break;
			}
			default:{
				errorprocess::showerr(ERR_NOT_NUM, bin);
				i = l;
			}
		}
		++i;
	}
	return dec;
}


/*
该函数用于将一个十六进制转换为十进制
2011-01-30
14:50
*/
TYPE_NUM valueswitch::hextonum(TYPE_HEX hex)
{
	TYPE_NUM dec = 0;
	int i = 0;
	int l = hex.length();
	while(i < l){
		if(hex[i] >= '0' && hex[i] <= '9'){
			dec <<= 4;
			dec |= (unsigned char)(hex[i] - '0');
		}
		else if(hex[i] >= 'A' && hex[i] <= 'F'){
			dec <<= 4;
			dec |= (unsigned char)(hex[i] - 'A' + 10);
		}
		else if(hex[i] >= 'a' && hex[i] <= 'f'){
			dec <<= 4;
			dec |= (unsigned char)(hex[i] - 'a' + 10);
		}
		else{
			errorprocess::showerr(ERR_NOT_NUM, hex);
			break;
		}
		++i;
	}
	return dec;
}


/*
该函数用于将一个八进制转换为十进制
2011-02-12
18:42
*/
TYPE_NUM valueswitch::octtonum(TYPE_OCT oct)
{
	TYPE_NUM dec = 0;
	int i = 0;
	int l = oct.length();
	while(i < l){
		if(oct[i] >= '0' && oct[i] <= '7'){
			dec <<= 3;
			dec |= (unsigned char)(oct[i] - '0');
		}
		else{
			errorprocess::showerr(ERR_NOT_NUM, oct);
			break;
		}
		++i;
	}
	return dec;
}


/*
该函数用于将一个字符串转换为数字
2011-01-30
14:52
*/
TYPE_NUM valueswitch::strtonum(TYPE_STRING str)
{
	TYPE_NUM dec = 0;
	int i = 0;
	int l = str.length();
	while(i < l){
		if(str[i] >= '0' && str[i] <= '9'){
			dec *= 10;
			dec += (unsigned char)(str[i] - '0');
		}
		else{
			errorprocess::showerr(ERR_NOT_NUM, str);
			break;
		}
		++i;
	}
	return dec;
}

/*
该函数用于将一个字符串转换为数字
2011-02-07
23:27
*/
TYPE_HEX valueswitch::numtohex(TYPE_NUM dec, TYPE_SIZE w)
{
	char *s = new char[101];
	int i = 100;
	int v;
	s[i] = '\0';
	--i;
	while(dec){
		v = (dec%16);
		s[i] = CharDecValue(v);
		dec /= 16;
		--i;
	}
	++i;
	TYPE_HEX str = (s+i);
	delete s;
	TYPE_HEX hex;
	if(str.length()>=w){
		hex = str;
	}
	else{
		hex = string(w - str.length(), '0') + str;
	}
	return hex;
}

/*
该函数用于将一个字符串转换为数字
2011-02-13
14:00
*/
TYPE_STRING valueswitch::numtostr(TYPE_NUM num)
{
	char s[100];
	s[99] = '\0';
	int i = 99;
	TYPE_STRING str;
	if(num==0)s[--i]='0';
	else{
		while(num){
			s[--i] = (char)(num%10 + '0');
			num /= 10;
		}
	}
	str = &s[i];
	return str;
}


/*
该函数用于将一个字符串数据对应的数字类型（BIN DEC HEX..）
2011-01-31
11:40
*/
TYPE_NUMTYPE valueswitch::numtype(TYPE_STRING& str)
{
	TYPE_NUMTYPE tp;
	int l = str.length();
	int i = 0;
	unsigned char ty = 0xff;
	while(i < l){
		if(!(str[i] >= '0' && str[i] <= '1')){	//not bin
			ty &= 0xfe;
		}
		if(!(str[i] >= '0' && str[i] <= '9')){	//not bin、not dec
			ty &= 0xfc;
		}
		if(!((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'A' && str[i] <= 'F'))){	//not bin、not dec、not hex
			ty &= 0xf8;
		}
		++i;
	}
	if(str[0]=='%'){
		tp = NUMTYPE_BIN;
		str = str.substr(1, string::npos);
	}
	else if(str[0]>='1' && str[0]<='9'){
		tp = NUMTYPE_DEC;
	}
	else if(str[0]=='0'){
		str = str.substr(1, string::npos);
		tp = NUMTYPE_OCT;
	}
	else if(str[0]=='$'){
		str = str.substr(1, string::npos);
		tp = NUMTYPE_HEX;
	}
	else{
		tp = NUMTYPE_UNKNOWN;
	}
	return tp;
}

/*
该函数用于将一个字符串转换为数字
2011-01-30
14:58
*/
TYPE_NUM valueswitch::numvalue(TYPE_STRING str)
{
	TYPE_NUM num = 0;
	if(str.length() == 0){
		errorprocess::showerr(ERR_EMPTY_NUM);
	}
	else{
		TYPE_VALUERESULT vr;
		valueswitch::valueresult(str, vr);
		if(vr.flag){
			num = vr.data;
		}
		else{
			errorprocess::showerr(ERR_UK_LABEL, str);
		}
	}
	return num;
}

/*
该函数返回数字处理结果
2011-01-30
14:58
*/
TYPE_STATUS valueswitch::valueresult(TYPE_STRING str, TYPE_VALUERESULT& vr)
{
	TYPE_SIZE l = str.length();
	TYPE_STRING val;
	TYPE_DATATYPE tp;
	if(l > 0){
		TYPE_NUM num;
		val = str.substr(1, string::npos);
		switch(str[0])
		{
			case '#':{	//Data
				valueresult(val, vr);
				vr.type = DATATYPE_BYTE;
				break;
				//cout<<"Data"<<endl;
			}
			case '@':{
				valueresult(val, vr);
				vr.type = DATATYPE_ADDRESS;
				break;
			}
			case '&':{
				valueresult(val, vr);
				vr.type = DATATYPE_ZPADDRESS;
				break;
			}
			case '$':{//Hex
				num = hextonum(val);
				if(num > 0xffff){
					tp = DATATYPE_BIG;
					//errorprocess::showerr(ERR_OUT_RANGE, val);
				}
				if(num > 0xff || val.length()>2){
					tp = DATATYPE_ADDRESS;
				}
				else{
					tp = DATATYPE_ZPADDRESS;
				}
				vr.type = tp;
				vr.data = num;
				vr.flag = 1;
				//cout<<"Hex"<<endl;
				break;
			}
			case '%':{//Bin
				num = bintonum(val);
				if(num > 0xffff){
					tp = DATATYPE_BIG;
					//errorprocess::showerr(ERR_OUT_RANGE, val);
				}
				if(num > 0xff || val.length()>8){
					tp = DATATYPE_ADDRESS;
				}
				else{
					tp = DATATYPE_ZPADDRESS;
				}
				vr.type = tp;
				vr.data = num;
				vr.flag = 1;
				//cout<<"Bin"<<endl;
				break;
			}
			case '0':{//Oct
				num = octtonum(val);
				if(num > 0xffff){
					tp = DATATYPE_BIG;
					//errorprocess::showerr(ERR_OUT_RANGE, val);
				}
				if(num > 0xff || val.length()>3){
					tp = DATATYPE_ADDRESS;
				}
				else{
					tp = DATATYPE_ZPADDRESS;
				}
				vr.type = tp;
				vr.data = num;
				vr.flag = 1;
				//cout<<"Oct"<<endl;
				break;
			}
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':{	//Dec
				num = strtonum(str);
				if(num > 0xffff){
					tp = DATATYPE_BIG;
					//errorprocess::showerr(ERR_OUT_RANGE, val);
				}
				if(num > 0xff || val.length()>3){
					tp = DATATYPE_ADDRESS;
				}
				else{
					tp = DATATYPE_ZPADDRESS;
				}
				vr.type = tp;
				vr.data = num;
				vr.flag = 1;
				//cout<<"Dec"<<endl;
				break;
			}
			case '>':{	//HByte
				valueresult(val, vr);
				if(vr.flag == 0){
					vr.type = DATATYPE_ZPADDRESS;
					vr.datastr = str;
				}
				else{
					vr.type = DATATYPE_ZPADDRESS;
					vr.data = (vr.data>>8)&0x00ff;
				}				
				//cout<<"HByte"<<endl;
				break;
			}
			case '<':{	//LByte
				valueresult(val, vr);
				if(vr.flag == 0){
					vr.type = DATATYPE_ZPADDRESS;
					vr.datastr = str;
				}
				else{
					vr.type = DATATYPE_ZPADDRESS;
					vr.data = (vr.data & 0x00ff);
				}
				
				//cout<<"LByte"<<endl;
				break;
			}
			case '+':{	//Next
				valueresult(val, vr);
				if(vr.flag == 0){
					vr.type = DATATYPE_ZPADDRESS;
					vr.datastr = str;
				}
				else{
					if(vr.data == 0xffff || ((vr.type==DATATYPE_ZPADDRESS || vr.type==DATATYPE_BYTE) && vr.data ==0xff)){
						//上溢
						errorprocess::showwarning(WARNING_FLOW_OVER, val);
					}
					vr.data = vr.data + 1;
				}
				break;
			}
			case '-':{	//Pre
				valueresult(val, vr);
				if(vr.flag == 0){
					vr.datastr = str;
				}
				else{
					if(vr.data==0){
						//下溢
						errorprocess::showwarning(WARNING_FLOW_UNDER, val);
					}
					vr.data = vr.data - 1;
				}
				break;
			}
			case '[':{	//下标运算
				if(val.find_first_of(']')!=string::npos){
					TYPE_VALUERESULT tpvr;
					TYPE_STRING tpval = val.substr(0, val.find_first_of(']'));
					valueresult(tpval, tpvr);
					if(tpvr.flag == 0){
						errorprocess::showerr(ERR_NOT_CONST, tpval);
					}
					val = val.substr(val.find_first_of(']')+1, string::npos);
					valueresult(val, vr);
					if(vr.flag == 0){
						vr.datastr = str;
					}
					else{
						if((vr.data + tpvr.data) == 0xffff || ((vr.type==DATATYPE_ZPADDRESS || vr.type==DATATYPE_BYTE) && (vr.data+tpvr.data) > 0xff)){
							//上溢
							errorprocess::showwarning(WARNING_FLOW_OVER, val);
						}
						vr.data = vr.data + tpvr.data;
					}
				}
				else{
					errorprocess::showerr(ERR_MISS_RF, str);
					return 0;
				}
				break;
			}
			case '/':{	//前置标签
				TYPE_POS oft = 1;
				if(val.length()>0){
					TYPE_VALUERESULT vof;
					valueresult(val, vof);
					if(vof.flag == 0){
						errorprocess::showerr(ERR_NOT_CONST, val);
					}
					else{
						oft = vof.data;
					}
				}
				valueresult(label::getprelabel(oft), vr);
				break;
			}
			case '\\':{	//后置标签
				TYPE_POS oft = 0;
				if(val.length()>0){
					TYPE_VALUERESULT vof;
					valueresult(val, vof);
					if(vof.flag == 0){
						errorprocess::showerr(ERR_NOT_CONST, val);
					}
					else{
						oft = vof.data-1;
					}
				}
				valueresult(label::getnextlabel(oft), vr);
				break;
			}
			case '{':{	//后栈标签
				vr.type = DATATYPE_ADDRESS;
				vr.datastr = label::next();
				vr.flag = 0;	//未
				g_taskname.push(vr.datastr);
				break;
			}
			case '}':{	//前栈标签
				if(g_labelname.size()>0){
					//cout<<g_labelname.top()<<endl;
					valueresult(g_labelname.top(), vr);
					g_labelname.pop();
				}
				else{
					errorprocess::showerr(ERR_HAVANO_LAB, "{");
				}
				break;
			}
			default:{	//Label
				//cout<<"Lab"<<endl;
				TYPE_LABEL lb;
				if(label::getlabel(str, lb)){
					vr.type = lb.flag;
					vr.datastr = str;
					vr.data = lb.dat;
					vr.flag = 1;	//已计算
				}
				else{
					vr.type = DATATYPE_ADDRESS;
					vr.datastr = str;
					vr.flag = 0;	//未
				}
			}
		}
	}
	else{	//Empty
		errorprocess::showerr(ERR_EMPTY_NUM);
		return 0;
	}
	//vr.inf();
	return 1;
}






