#include "function.h"

/*
该函数用于从把文件fn的数据全部读取到dat中
2011-02-07
15:57
*/
TYPE_STATUS fileio::loadall(TYPE_FILENAME fn, TYPE_BYTE* dat)
{
	FILE *fp;
	fp = safeopen(fn.c_str(), "rb");
	if(fp){
		while(!feof(fp)){
			*dat = (unsigned char)fgetc(fp);
			++dat;
		}
		*dat = '\0';
		fclose(fp);
	}
	return 1;
}

/*
该函数用于从把文件fn的数据全部读取到dat中
2011-02-07
16:02
*/
TYPE_STATUS fileio::saveall(TYPE_FILENAME fn, TYPE_BYTE* dat, TYPE_SIZE sz)
{
	FILE *fp = NULL;
	fp = safeopen(fn.c_str(), "wb");
	if(fp){
		fwrite(dat, sizeof(TYPE_BYTE), sz, fp);
		fclose(fp);
		return 1;
	}
	return 0;
}

/*
该函数用于从把文件fn的数据全部读取到bs中
2011-02-09
19:01
*/
TYPE_STATUS fileio::loadall(TYPE_FILENAME fn, TYPE_BYTE_STRING& bs)
{
	FILE *fp;
	vector<TYPE_BYTE> buf;
	TYPE_BYTE dt;
	fp = safeopen(fn.c_str(), "rb");
	if(fp){
		while(!feof(fp)){
			dt = (unsigned char)fgetc(fp);
			buf.push_back(dt);
		}
		fclose(fp);
		bs.buf = new TYPE_BYTE[buf.size()+1];
		for(TYPE_SIZE i = 0; i < buf.size(); ++i){
			bs.buf[i] = buf[i];
		}
		bs.size = buf.size();
		if(bs.size)--bs.size;
		bs.capacity = bs.size+1;
		return 1;
	}
	return 0;
}

/*
该函数用于读取文本文件
2011-02-09
23:41
*/
TYPE_STATUS fileio::loadtxt(TYPE_FILENAME fn, TYPE_BYTE_STRING& bs)
{
	if(loadall(fn, bs)){
		bs.buf[++bs.size] = '\0';
		return 1;
	}
	return 0;
}

/*
该函数用于读取文本文件到串组数组
2011-02-13
12:38
*/
TYPE_STATUS fileio::loadtxtarray(TYPE_FILENAME fn, TYPE_STRING_ARRAY& sa)
{
	char s[0x10000];
	FILE *fp;
	fp = safeopen(fn.c_str(), "r+");
	if(fp){
		while(fgets(s, 0x10000, fp)){
			sa.push_back(s);
		}
		return 1;
	}
	return 0;
}

/*
该函数用于保存数据
2011-02-14
21:26
*/
TYPE_STATUS fileio::saveall(TYPE_FILENAME fn, TYPE_BYTE_STRING& sa)
{
	return saveall(fn, sa.buf, sa.size);
}


int isabspath(TYPE_FILENAME path){
	if(path[0] == '/')
		return 1;
	else if(path.find(':') < path.find('\\') && path.find(':')>=0)
		return 2;
	return 0;
}

TYPE_FILENAME getparent(TYPE_FILENAME path){
	TYPE_FILENAME ppath = "";
	if(path != ""){
		unsigned int ri = -1;
		ri = path.rfind('/');
		if(ri>=0){
			char lc = path[path.length()-1];
			ppath = path.substr(0, ri+(lc=='/' || lc=='\\' ?'0':1));
		}
	}
//	cout<<path<<" ->"<<ppath<<"\n";
	return ppath;
}


FILE * inopen(const char *fname, const char *status)
{
	FILE *fp;
	cout<<fname;
	fp = fopen(fname, status);
	if(fp){
		cout<<" ok"<<endl;
		return fp;
	}
	cout<<" fail"<<endl;
	return NULL;
}
inline FILE * inopen(TYPE_FILENAME fn, const char *status)
{
	return inopen(fn.c_str(), status);
}




/*
该函数用于安全的打开文件
2013-12-09
16:15
*/
FILE * fileio::safeopen(const char *fname, const char *status)
{
	TYPE_FILENAME cfn = gloab::g_filepoint.getfilename();
	TYPE_FILENAME fn = fname;
	FILE *fp;
	fp = inopen(fname, status);
	if(!fp && !isabspath(fname) && cfn != ""){
		strprocess::killfbspace(cfn);
		TYPE_FILENAME pp = getparent(cfn);
		if(pp != ""){
			fn = pp+fname;
			fp = inopen(fn, status);
		}
	}

	if(fp){
//		gloab::g_filepoint.set(fn);
		return fp;
	}
	errorprocess::showerr(ERR_HAVANO_FILE, fname);
	return NULL;
}






