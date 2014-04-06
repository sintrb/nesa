#include "function.h"

#define ISSPACE(_c)	((_c)==' ' || (_c)=='\t' || (_c)=='\r' || (_c)=='\n')

/*
该函数用于从str中获取下一个参数
2011-01-30
10:00
*/
TYPE_STRING strprocess::getstring(TYPE_STRING &str)
{
	int l =str.length();
	int st = 0, ed;
	string rstr;
	while(st < l && str[st] == ' '){
		++st;
	}
	if(str[st] == '\"'){
		++st;
		ed = st;
		while(ed < l && str[ed] != '\"'){
			++ed;
		}
		rstr = str.substr(st, ed - st);
		++ed;
	}
	else{
		ed = st;
		while(ed < l && str[ed] != ' ' && str[ed] != '\n'){
			++ed;
		}
		rstr = str.substr(st, ed - st);
	}
	if(ed < l){
		if(str[ed]==' ')++ed;
		str = str.substr(ed, string::npos);
	}
	else{
		str = "";
	}
	return rstr;
}

/*
该函数用于从str中获取第pos个字符串参数
2011-02-07
13:27
*/
TYPE_STRING strprocess::getstringarg(const TYPE_STRING str, TYPE_POS pos)
{
	char *s = new char[str.length()+1];
	TYPE_STRING rstr;
	TYPE_SIZE i=0, j=0;
	TYPE_SIZE l = str.length();
	while(pos){
		while(i < l && str[i] == ' '){
			++i;
		}
		if(i < l && str[i] == '\"'){
			++i;
			while(i < l && str[i] != '\"'){
				++i;
			}
			++i;
			if(i>=l){
				delete s;
				return rstr;
			}
		}
		else{
			while(i < l && str[i] != ' '){
				++i;
			}
			++i;
			if(i>=l){
				return rstr;
			}
		}
		--pos;
	}
	
	while(i < l && str[i] == ' '){
		++i;
	}
	//cout<<"AT:"<<i<<" L:"<<l<<endl;
	if(i < l && str[i] == '\"'){
		++i;
		while(i < l && str[i] != '\"'){
			s[j] = str[i];
			++j;
			++i;
		}
	}
	else{
		while(i < l && str[i] != ' '){
			s[j] = str[i];
			++j;
			++i;
		}
	}
	s[j] = '\0';
	rstr = s;
	delete s;
	return rstr;
		
}

/*
该函数用于从str第pos个字符开始获取参数,用空格隔开
2011-02-08
10:47
*/
TYPE_STRING_ARRAY& strprocess::getstringarray(const TYPE_STRING str, TYPE_POS pos)
{
	TYPE_STRING_ARRAY &sa = *(new TYPE_STRING_ARRAY);
	char *s = NULL;
	sa.reserve(10);
	TYPE_POS l = str.length();
	TYPE_POS i;
	TYPE_POS j;

	s = new char[l+1];
	i = pos;
	while(i<l){
		j = 0;
		while(i<l && str[i] != ','){
			if(str[i] == '\"'){
				s[j++] = str[i++];
				while(i < l && str[i] != '\"'){
					s[j++] = str[i++];
				}
				s[j++] = str[i++];
			}
			else{
				s[j++] = str[i++];
			}
		}
		//cout<<s<<endl;
		s[j] = '\0';
		sa.push_back(s);
		++i;
	}
	delete s;
	return sa;
}
	
/*
该函数用于从str获取键值对
2011-02-08
15:20
*/
TYPE_KEYVALUE  strprocess::getkeyvalue(const TYPE_STRING str)
{
	TYPE_KEYVALUE kv;
	int l = str.length();
	int i = 0;
	int j = 0;
	char *s = new char[l+1];
	while(i < l && str[i] == ' '){
		++i;
	}
	while(i < l){
		if(str[i] == '\"'){
			++i;
			while(i < l && str[i] != '\"'){
				s[j++] =  str[i++];
			}
			++i;
		}else{
			if(str[i] == '='){
				break;
			}
			else{
				s[j++] =  str[i++];
			}
		}
	}
	if(i>=l || str[i] != '='){//不是键值对
		errorprocess::showerr(ERR_UK_SYM, str);
		return kv;
	}
	if(i>1 && str[i-1] != '\"' && j>1 && s[j-1] == ' '){
		--j;
		while(j>0 && s[j] == ' '){
			--j;
		}
		++j;
	}
	s[j] = '\0';
	kv.key = s;
	j = 0;
	++i;
	while(i < l && str[i] == ' '){
		++i;
	}
	while(i < l){
		if(str[i] == '\"'){
			++i;
			while(i < l && str[i] != '\"'){
				s[j++] = str[i++];
			}
			++i;
		}else{
			s[j++] = str[i++];
		}
	}
	if(i>1 && str[i-1] != '\"' && j>1 && s[j-1] == ' '){
		--j;
		while(j>0 && s[j] == ' '){
			--j;
		}
		++j;
	}
	s[j] = '\0';
	kv.value = s;
	delete s;
	return kv;
}

/*
该函数用于从str中获取第pos个字符之后的字符串组(空格和逗号分割)
2011-02-08
20:39
*/
TYPE_STRING_ARRAY& strprocess::getdatastringarray(const TYPE_STRING str, TYPE_POS pos)
{
	TYPE_STRING_ARRAY &sa = *(new TYPE_STRING_ARRAY);
	char *s = NULL;
	sa.reserve(10);
	TYPE_POS l = str.length();
	TYPE_POS i;
	TYPE_POS j;

	s = new char[l+1];
	i = pos;
	j = 0;
	while(i < l){
		if(str[i] == ' ' || str[i] == ','){
			if(j > 0){
				s[j] = '\0';
				sa.push_back(s);
				j = 0;
			}
		}
		else{
			s[j] = str[i];
			++j;
		}
		++i;
	}
	if(j > 0){
		s[j] = '\0';
		sa.push_back(s);
		j = 0;
	}
	delete s;
	return sa;
}

/*
该函数用于去前后导空格
2011-02-10
20:40
*/
TYPE_STATUS strprocess::killfbspace(TYPE_STRING& str)
{
	if(str.length()>0){
		TYPE_POS f = 0;
		TYPE_POS b = str.length()-1;
		while(f < b && ISSPACE(str[f])){
			++f;
		}
		while(f < b && ISSPACE(str[b])){
			--b;
		}
		if(b>=0 && str[f]!=' '){
			str = str.substr(f, b-f+1);
		}
		else{
			str = "";
		}
	}
	return 1;
}

/*
该函数用于获取一行中的单指令
2011-02-13
12:48
*/
TYPE_STATUS strprocess::getinsarray(TYPE_STRING& line, TYPE_STRING_ARRAY& insa, bool& isNote)
{
	killspace(line);
	TYPE_POS l = line.length();
	char *s = new char[l+1];
	TYPE_POS i;
	TYPE_POS j;
	i = 0;
	j = 0;
	while(i<l){
		if(isNote){
			while(i<l){	//等待注释
				if(i<(l-1) && line[i]=='*' && line[i+1]=='/'){	//注释完
					isNote = false;
					++i;
					++i;
					break;
				}
				++i;
			}
		}
		else{
			if(line[i]==';' || line[i]=='\n' || line[i]=='\r'){	//单句
				s[j] = '\0';
				insa.push_back(s);
				j = 0;
				++i;
			}
			else if(i<(l-1) && line[i]=='/' && line[i+1]=='*'){	//左注释
				isNote = true;
				++i;
				++i;
			}
			else if(i<(l-1) && line[i]=='/' && line[i+1]=='/' && !isNote){	//注释
				i = l+1;
				break;
			}
			else{
				if((j==0 && line[i]!=' ') || j != 0){
					s[j++] = line[i++];
				}
				else{
					++i;
				}
			}
		}
	}
	if(j>0 && s[j-1]==' ')--j;
	if(j>0){
		s[j] = '\0';
		insa.push_back(s);
		j = 0;
	}
	delete s;
	return 0;
}

/*
该函数用于获取一行中的单指令
2011-02-13
12:56
*/
TYPE_STATUS strprocess::killspace(TYPE_STRING& str)
{
	TYPE_POS l = str.length();
	TYPE_POS i = 0;
	TYPE_POS j = 0;
	char *s = new char[l+1];
	bool isSpace = true;
	while(i<l){
		if(str[i]=='\"'){
			s[j++] = str[i++];
			while(i<l && str[i]!='\"'){
				s[j++] = str[i++];
			}
			if(i<l){
				s[j++] = str[i++];
			}
			isSpace = false;
		}
		else{
			if(str[i] == ' ' || str[i] == '\t'){
				if(!isSpace){
					s[j++] = ' ';
					isSpace = true;
				}
				++i;
			}
			else{
//				s[j++] = cupper(str[i++]);
				s[j++] = str[i++];
				isSpace = false;
			}
		}
	}
	if(j>0 && s[j-1]==' ')--j;
	s[j] = '\0';
	str = s;
	delete s;
	return 0;
}

/*
该函数用于获取大写
2011-02-13
13:56
*/
inline char strprocess::cupper(char c)
{
	if(c>='a' && c<='z')return c+'A'-'a';
	else return c;
}


/*
该函数用于获取大写
2011-02-13
14:34
*/
TYPE_STRING& strprocess::supper(TYPE_STRING& str)
{
	TYPE_POS l = str.length();
	TYPE_POS i = 0;
	while(i<l){
		str[i] = cupper(str[i]);
		++i;
	}
	return str;
}

/*
该函数用于获取大写
2013-12-09
15:37
 */
inline void strprocess::tosupper(char *s){
	while(*s){
		*s = cupper(*s);
		++s;
	}
}


















