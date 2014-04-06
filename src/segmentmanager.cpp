#include "function.h"

/*
该函数用于将一个字节写入到当前位置
2011-02-07
11:42
*/
TYPE_STATUS segmentmanager::put(TYPE_BYTE dat)	//向当前位置输入一字节
{
	if(checkcurrnetsegment()>0){
		if(g_outfile.currentsegment->pos < g_outfile.currentsegment->size){
			g_outfile.currentsegment->buf[g_outfile.currentsegment->pos] = dat;
			++g_outfile.currentsegment->pos;
			return 1;
		}
		else{
			errorprocess::showerr(ERR_OUT_CODE, g_outfile.currentsegment->name);
		}
	}
	return 0;
}

/*
该函数用于将一个字写入到当前位置
2011-02-07
11:50
*/
TYPE_STATUS segmentmanager::put(TYPE_WORD dat)	//输出字
{
	if(checkcurrnetsegment()){
		if(g_outfile.emptysize()>=2){
			TYPE_BYTE hb, lb;
			lb = (TYPE_BYTE)(dat & 0xff);	//低字节
			hb = (TYPE_BYTE)((dat >> 8) & 0xff);	//高字节
		//	cout<<"Pos:"<<hex<<g_outfile.currentsegment->nowpos()<<"  Data:"<<dat<<endl;
			g_outfile.currentsegment->buf[g_outfile.currentsegment->pos] = lb;	//低字节
			++g_outfile.currentsegment->pos;
			g_outfile.currentsegment->buf[g_outfile.currentsegment->pos] = hb;	//高字节
			++g_outfile.currentsegment->pos;
			return 1;
		}
		else{
			errorprocess::showerr(ERR_OUT_CODE, g_outfile.currentsegment->name);
		}
	}
	return 0;
}

/*
该函数用于将一个串写入到当前位置
2011-02-07
11:57
*/
TYPE_STATUS segmentmanager::put(char* s)		//输出串
{
	if(checkcurrnetsegment()){
		if(g_outfile.emptysize() > strlen(s)){
			strcpy((char *)(g_outfile.currentsegment->buf + g_outfile.currentsegment->pos), s);
			g_outfile.currentsegment->pos += (strlen(s) + 1);
			return 1;
		}
		else{
			errorprocess::showerr(ERR_OUT_CODE, g_outfile.currentsegment->name);
		}
	}
	return 0;
}

/*
该函数用于将一个串写入到当前位置(string 形式)
2011-02-07
12:00
*/
TYPE_STATUS segmentmanager::put(TYPE_STRING s)	//输出串
{
	if(checkcurrnetsegment()){
		if(g_outfile.emptysize() > s.length()){
			strcpy((char *)(g_outfile.currentsegment->buf + g_outfile.currentsegment->pos), s.c_str());
			g_outfile.currentsegment->pos += (s.length() + 1);
			return 1;
		}
		else{
			errorprocess::showerr(ERR_OUT_CODE, g_outfile.currentsegment->name);
		}
	}
	return 0;
}

/*
该函数用于写入TYPE_BYTE_STRING结构的数据
2011-02-09
19:23
*/
TYPE_STATUS segmentmanager::put(const TYPE_BYTE_STRING& bs)
{
	if(checkcurrnetsegment()){
		if(g_outfile.emptysize() >= bs.size){
			TYPE_BYTE *tobuf = g_outfile.currentsegment->buf + g_outfile.currentsegment->pos;
			TYPE_BYTE *srcbuf = bs.buf;
			for(TYPE_SIZE i = 0; i < bs.size; ++i){
				tobuf[i] = srcbuf[i];
			}
			g_outfile.currentsegment->pos += bs.size;
			return 1;
		}
		else{
			string str = g_outfile.currentsegment->name + "\n\tEmptySize:" + 
						valueswitch::numtohex(g_outfile.emptysize()) + 
						" CodeLength:" + 
						valueswitch::numtohex(bs.size);
			errorprocess::showerr(ERR_OUT_CODE, str);
		}
	}
	return 0;
}


/*
该函数用于增加代码段描述,出入代码段
2011-02-07
12:05
*/
TYPE_STATUS segmentmanager::addsegment(TYPE_SEGMENT sg)		//增加代码段描述
{
	//sg.inf();
	if(g_outfile.segments.find(sg.name)==g_outfile.segments.end()){
		sg.offset = g_outfile.currentsize;
		if(!(sg.buf = new TYPE_BYTE[sg.size])){
			errorprocess::showerr(ERR_SIZE_SEG, g_outfile.currentsegment->name);
			return 0;
		}
		for(TYPE_SIZE i = 0; i < sg.size; ++i){
			sg.buf[i] = sg.fill;
		}
		g_outfile.currentsize += sg.size;
		g_outfile.filesize = g_outfile.currentsize;
		g_outfile.segments[sg.name] = sg;
		if(++g_outfile.segmentcount == 1){	//第一次，设置为当前代码段
			g_outfile.currentsegment = &(g_outfile.segments[sg.name]);
		}
		return 1;
	}
	errorprocess::showerr(ERR_HAVA_SEG, g_outfile.currentsegment->name);
	return 0;
}

/*
该函数用于设置当前代码段,传入代码段名
2011-02-07
12:10
*/
TYPE_STATUS segmentmanager::setcurrentsegment(TYPE_NAME nm)	//设置当前代码段
{
	map<TYPE_NAME, TYPE_SEGMENT>::iterator seg = g_outfile.segments.find(nm);
	if(seg != g_outfile.segments.end()){	//存在这个
		g_outfile.currentsegment = &(seg->second);
		return 1;
	}
	errorprocess::showerr(ERR_HAVANO_SEG, nm);
	return 0;
}

/*
该函数用于获取当前代码段
2011-02-07
12:18
*/
TYPE_SEGMENT* segmentmanager::getcurrentsegment()	//获取当前的代码段
{
	if(g_outfile.currentsegment){
		return g_outfile.currentsegment;
	}
	errorprocess::showerr(ERR_UNDEFINE_SEG, g_outfile.currentsegment->name);
	return NULL;
}

/*
该函数用于设置输出文件名并保存
2011-02-07
12:22
*/
TYPE_STATUS segmentmanager::saveoutfile(TYPE_FILENAME fn)	//保存文件
{
	g_outfile.filename = fn;
	return saveoutfile();
}

/*
该函数用于设置输出文件名
2011-02-07
12:23
*/
TYPE_STATUS segmentmanager::setfilename(TYPE_FILENAME fn)	//设置文件名
{
	g_outfile.filename = fn;
	return 1;
}


TYPE_STATUS segmentmanager::saveoutfile()	//保存文件
{
	if(g_outfile.filename.length() > 0){
		TYPE_BYTE_STRING codebuf;
		codebuf.capacity = g_outfile.filesize + 1;
		codebuf.buf = new TYPE_BYTE[codebuf.capacity];
		codebuf.size = g_outfile.filesize;
		TYPE_POS l;
		for(map<TYPE_NAME, TYPE_SEGMENT>::iterator seg = g_outfile.segments.begin(); seg != g_outfile.segments.end(); ++seg){
			for(l = 0; l < seg->second.size; ++l){
				codebuf.buf[l+seg->second.offset] = seg->second.buf[l];
			}
		}
		return fileio::saveall(g_outfile.filename, codebuf);
	}
	else{
		errorprocess::showerr(ERR_EMPTY_FILENAME);
	}
	return 0;
}

/*
该函数用于显示代码段信息
2011-02-07
12:42
*/
void segmentmanager::segmentinf()
{
	cout<<"Segment Information:"<<endl;
	g_outfile.inf();
	cout<<endl;
}

/*
该函数用于显示代码段信息
2011-02-07
18:46
*/
TYPE_STATUS segmentmanager::setorgaddress(TYPE_SIZE add)
{
	//cout<<"ADD:"<<add<<endl;
	if(checkcurrnetsegment()){
		TYPE_SEGMENT* sg = getcurrentsegment();
		if((sg->org + sg->size) >= add && add >= sg->org){
			sg->pos = add - sg->org;
			return 1;
		}
		string s = string("(rang:") + valueswitch::numtohex(sg->org) + string(" to ") + valueswitch::numtohex(sg->org + sg->size) + string("):") + valueswitch::numtohex(add);
		errorprocess::showerr(ERR_OUT_ORG, s);
	}
	return 0;
}

/*
该函数用检查当前代码段是否可用
2011-02-07
19:23
*/
TYPE_STATUS segmentmanager::checkcurrnetsegment()
{
	if(g_outfile.currentsegment){
		return 1;
	}
	errorprocess::showerr(ERR_UNDEFINE_SEG);
	return 0;
}

/*
该函数用于设置当前代码段位置为起始位置
2011-02-09
23:08
*/
TYPE_STATUS segmentmanager::setstart()
{
	if(checkcurrnetsegment()){
		TYPE_SEGMENT* sg = getcurrentsegment();
		sg->pos = 0;
		return 1;
	}
	return 0;
}


/*
该函数用于写入先对地址(传入地址，自动计算)
2011-02-11
21:52
*/
TYPE_STATUS segmentmanager::putreaddress(TYPE_ADDRESS add)
{
	if(checkcurrnetsegment()){
		TYPE_BYTE bt;
		TYPE_ADDRESS nowadd = getcurrentsegment()->nowpos();
		if(add > nowadd){
		//	cout<<dec<<add - nowadd<<endl;
			if((add - nowadd) <= 256){
				bt = add - nowadd - 1;
			}
			else{
				errorprocess::showerr(ERR_OUT_REV, valueswitch::numtohex(add));
				return 0;
			}
		}
		else{
			if((nowadd - add) <= 255){
				bt = 0xff - (TYPE_BYTE)(nowadd - add);
			}
			else{
				errorprocess::showerr(ERR_OUT_REV, valueswitch::numtohex(add));
				return 0;
			}
		}
		return put(bt);;
	}
	return 0;
}




