#include "function.h"

/*
�ú������ڽ�һ���ֽ�д�뵽��ǰλ��
2011-02-07
11:42
*/
TYPE_STATUS segmentmanager::put(TYPE_BYTE dat)	//��ǰλ������һ�ֽ�
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
�ú������ڽ�һ����д�뵽��ǰλ��
2011-02-07
11:50
*/
TYPE_STATUS segmentmanager::put(TYPE_WORD dat)	//�����
{
	if(checkcurrnetsegment()){
		if(g_outfile.emptysize()>=2){
			TYPE_BYTE hb, lb;
			lb = (TYPE_BYTE)(dat & 0xff);	//���ֽ�
			hb = (TYPE_BYTE)((dat >> 8) & 0xff);	//���ֽ�
		//	cout<<"Pos:"<<hex<<g_outfile.currentsegment->nowpos()<<"  Data:"<<dat<<endl;
			g_outfile.currentsegment->buf[g_outfile.currentsegment->pos] = lb;	//���ֽ�
			++g_outfile.currentsegment->pos;
			g_outfile.currentsegment->buf[g_outfile.currentsegment->pos] = hb;	//���ֽ�
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
�ú������ڽ�һ����д�뵽��ǰλ��
2011-02-07
11:57
*/
TYPE_STATUS segmentmanager::put(char* s)		//�����
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
�ú������ڽ�һ����д�뵽��ǰλ��(string ��ʽ)
2011-02-07
12:00
*/
TYPE_STATUS segmentmanager::put(TYPE_STRING s)	//�����
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
�ú�������д��TYPE_BYTE_STRING�ṹ������
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
�ú����������Ӵ��������,��������
2011-02-07
12:05
*/
TYPE_STATUS segmentmanager::addsegment(TYPE_SEGMENT sg)		//���Ӵ��������
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
		if(++g_outfile.segmentcount == 1){	//��һ�Σ�����Ϊ��ǰ�����
			g_outfile.currentsegment = &(g_outfile.segments[sg.name]);
		}
		return 1;
	}
	errorprocess::showerr(ERR_HAVA_SEG, g_outfile.currentsegment->name);
	return 0;
}

/*
�ú����������õ�ǰ�����,����������
2011-02-07
12:10
*/
TYPE_STATUS segmentmanager::setcurrentsegment(TYPE_NAME nm)	//���õ�ǰ�����
{
	map<TYPE_NAME, TYPE_SEGMENT>::iterator seg = g_outfile.segments.find(nm);
	if(seg != g_outfile.segments.end()){	//�������
		g_outfile.currentsegment = &(seg->second);
		return 1;
	}
	errorprocess::showerr(ERR_HAVANO_SEG, nm);
	return 0;
}

/*
�ú������ڻ�ȡ��ǰ�����
2011-02-07
12:18
*/
TYPE_SEGMENT* segmentmanager::getcurrentsegment()	//��ȡ��ǰ�Ĵ����
{
	if(g_outfile.currentsegment){
		return g_outfile.currentsegment;
	}
	errorprocess::showerr(ERR_UNDEFINE_SEG, g_outfile.currentsegment->name);
	return NULL;
}

/*
�ú���������������ļ���������
2011-02-07
12:22
*/
TYPE_STATUS segmentmanager::saveoutfile(TYPE_FILENAME fn)	//�����ļ�
{
	g_outfile.filename = fn;
	return saveoutfile();
}

/*
�ú���������������ļ���
2011-02-07
12:23
*/
TYPE_STATUS segmentmanager::setfilename(TYPE_FILENAME fn)	//�����ļ���
{
	g_outfile.filename = fn;
	return 1;
}


TYPE_STATUS segmentmanager::saveoutfile()	//�����ļ�
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
�ú���������ʾ�������Ϣ
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
�ú���������ʾ�������Ϣ
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
�ú����ü�鵱ǰ������Ƿ����
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
�ú����������õ�ǰ�����λ��Ϊ��ʼλ��
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
�ú�������д���ȶԵ�ַ(�����ַ���Զ�����)
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




