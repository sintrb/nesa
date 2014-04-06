#include "function.h"

/*
�ú������ں�ָ����жϺͷַ���Ϊ��һ���괦��������
2011-01-30
11:53
*/
TYPE_STRING args = "";
TYPE_STATUS macro::macrojudge(TYPE_STRING& mac)
{
	int sp = mac.find(' ');
	string strmac = strprocess::getstringarg(mac, 0);
	strprocess::supper(strmac);
	if(sp >= 0){
		args = mac.substr(sp + 1, string::npos);
	}
	else{
		args = "";
	}
	if(strmac == ".POINT" || strmac == ".POI"){
		m_point();
	}
	else if(strmac == ".SEGMENT" || strmac == ".SEG"){
		m_segment();
	}
	else if(strmac == ".STRING" || strmac == ".STR"){
		m_string();
	}
	else if(strmac == ".ORG"){
		m_org();
	}
	else if(strmac == ".SEGMENTDEFINE" || strmac == ".SEGDEF"){
		m_segmentdefine();
	}
	else if(strmac == ".BYTE" ||strmac == ".BYT"){
		m_byte();
	}
	else if(strmac == ".WORD" || strmac == ".WOR"){
		m_word();
	}
	else if(strmac == ".DATA" || strmac == ".DAT"){
		m_data();
	}
	else if(strmac == ".INCLUDEBIN" || strmac == ".INCBIN"){
		m_includebin();
	}
	else if(strmac == ".ERROR" || strmac == ".ERR"){
		m_error();
	}
	else if(strmac == ".WARNING" || strmac == ".WAR"){
		m_warning();
	}
	else if(strmac == ".LABEL" || strmac == ".LAB"){
		m_label();
	}
	else if(strmac == ".FILE" || strmac == ".FIL"){
		m_file();
	}
	else if(strmac == ".LINE" || strmac == ".LIN"){
		m_line();
	}
	else{
		errorprocess::showwarning(UNKNOWN_MAC_TYPE, strmac);
	}

	return 1;
}


/*
�ú������ں�ָ�������ļ�λ��
2011-01-30
13:20
*/
TYPE_STATUS macro::m_point()
{
	TYPE_FILENAME str;
	TYPE_FILENAME fn;
	TYPE_LINE ln;
	str = strprocess::getstring(args);
	if(str.length()>0){
		fn = str;
		str = strprocess::getstring(args);
		if(str.length()){
			ln = valueswitch::numvalue(str);
			g_filepoint.set(fn, ln);
		}
		else{
			errorprocess::showwarning(WARNING_NO_USING, ".POINT (error line number)");
		}
	}
	else{
		errorprocess::showwarning(WARNING_NO_USING, ".POINT (error filename)");
	}
	return 1;
}

/*
�ú����������õ�ǰ�Ĵ����
2011-02-07
13:00
*/
TYPE_STATUS macro::m_segment()
{
	return segmentmanager::setcurrentsegment(strprocess::getstring(args));
}

/*
�ú�����������ַ���
2011-02-07
13:12
*/
TYPE_STATUS macro::m_string()
{
	return segmentmanager::put(strprocess::getstringarg(args));
}



/*
�ú����������õ�ǰ����λ��
2011-02-07
18:44
*/
TYPE_STATUS macro::m_org()
{
	if(strprocess::getstringarg(args,0)=="START"){
		return segmentmanager::setstart();
	}
	else{
		string str = strprocess::getstringarg(args,0);
		if(str.length() == 0){
			errorprocess::showerr(ERR_EMPTY_NUM, " after .ORG");
			return 0;
		}
		return segmentmanager::setorgaddress(valueswitch::numvalue(str));
	}
}

/*
�ú���������Ӵ�����ļ�����
2011-02-08
15:58
*/
TYPE_STATUS macro::m_segmentdefine()
{
	TYPE_STRING_ARRAY segs = strprocess::getstringarray(args);
	TYPE_NAME name = "unknown";	//���������
	TYPE_SIZE org = 0;	//�������ʼλ��
	TYPE_SIZE size = 0;	//����εĴ�С
	TYPE_BYTE fill = 0;	//��������
	for(unsigned int i = 0; i < segs.size(); ++i){
		strprocess::supper(segs[i]);
		TYPE_KEYVALUE kv = strprocess::getkeyvalue(segs[i]);
		//cout<<"K:"<<kv.key<<" V:"<<kv.value<<endl;
		if(kv.key == "NAME")name = kv.value;
			else if(kv.key == "START")org = valueswitch::numvalue(kv.value);
				else if(kv.key == "SIZE")size = valueswitch::numvalue(kv.value);
					else if(kv.key == "FILL")fill = valueswitch::numvalue(kv.value);
						else errorprocess::showwarning(WARNING_NO_USING, kv.key);
	}
	return segmentmanager::addsegment(TYPE_SEGMENT(name, org, size, 0, fill));
}
	
/*
�ú����������������
2011-02-08
21:11
*/
TYPE_STATUS macro::m_byte()
{
	TYPE_BYTE v;
	TYPE_NUM num;
	TYPE_STRING_ARRAY& sa = strprocess::getdatastringarray(args);
	for(unsigned int i=0; i < sa.size(); ++i){
		TYPE_VALUERESULT vr;
		valueswitch::valueresult(sa[i], vr);
		if(gloabfunction::datatypesize(vr.type)==2){
			errorprocess::showwarning(WARNING_TYPE_WARN, sa[i]);
		}
		
		if(vr.flag){
			num = vr.data;
			v = (TYPE_BYTE)(num & 0xff);
			segmentmanager::put(v);
		}
		else{	//δ����,��������
			task::addtask(vr.datastr, vr.type);
			TYPE_BYTE bt = 0xff;	//ռλ
			if(gloabfunction::datatypesize(vr.type)==1){
				segmentmanager::put(bt);
			}
			else if(gloabfunction::datatypesize(vr.type)==2){
				segmentmanager::put(bt);
				segmentmanager::put(bt);
			}
		}
	}
	return 1;
}

/*
�ú����������������
2011-02-08
21:15
*/
TYPE_STATUS macro::m_word()
{
	TYPE_WORD v;
	TYPE_NUM num;
	TYPE_STRING_ARRAY& sa = strprocess::getdatastringarray(args);
	for(unsigned int i=0; i < sa.size(); ++i){
		TYPE_VALUERESULT vr;
		valueswitch::valueresult(sa[i], vr);
		if(vr.flag){
			num = vr.data;
			if(num <= 0xffff){
				v = (TYPE_WORD)num;
				segmentmanager::put(v);
			}
			else{
				errorprocess::showerr(ERR_OUT_RANGE, sa[i]);
			}
		}
		else{
			task::addtask(vr.datastr, vr.type);
			TYPE_BYTE bt = 0xff;	//ռλ
			if(gloabfunction::datatypesize(vr.type)==1){
				segmentmanager::put(bt);
			}
			else if(gloabfunction::datatypesize(vr.type)==2){
				segmentmanager::put(bt);
				segmentmanager::put(bt);
			}
		}
	}
	return 1;
}


/*
�ú�������������ݣ���˫�ֽڻ���
2011-02-08
21:58
*/
TYPE_STATUS macro::m_data()
{
	TYPE_WORD wd;
	TYPE_BYTE bt;
	TYPE_NUM num;
	TYPE_STRING_ARRAY& sa = strprocess::getdatastringarray(args);
	for(unsigned int i=0; i < sa.size(); ++i){
		TYPE_VALUERESULT vr;
		valueswitch::valueresult(sa[i], vr);
		if(vr.flag){
			num = vr.data;
			if(gloabfunction::datatypesize(vr.type)==1){
				bt = (TYPE_BYTE)num;
				segmentmanager::put(bt);
			}
			else if(gloabfunction::datatypesize(vr.type)==2){
				wd = (TYPE_WORD)num;
				if(!segmentmanager::put(wd))return 0;
			}
			else{
				errorprocess::showerr(ERR_OUT_RANGE, sa[i]);
			}
		}
		else{
			task::addtask(vr.datastr, vr.type);
			TYPE_BYTE bt = 0xff;	//ռλ
			if(gloabfunction::datatypesize(vr.type)==1){
				segmentmanager::put(bt);
			}
			else if(gloabfunction::datatypesize(vr.type)==2){
				segmentmanager::put(bt);
				segmentmanager::put(bt);
			}
		}
	}
	return 1;
}

/*
�ú������ڰ���һ���������ļ�
2011-02-09
19:20
*/
TYPE_STATUS macro::m_includebin()
{
	string fn = strprocess::getstringarg(args,0);
	TYPE_BYTE_STRING bs;
	fileio::loadall(fn, bs);
	return segmentmanager::put(bs);
}

/*
�ú����������þ��漶��
2011-02-09
22:40
*/
TYPE_STATUS macro::m_warning()
{
	string str = strprocess::getstringarg(args,0);
	TYPE_NUM num = valueswitch::numvalue(str);
	if(str.length() == 0 || num == 1){
		g_warninglevel = 1;
	}else if(num == 0){
		g_warninglevel = 0;
	}else if(num == 2){
		g_warninglevel = 2;
	}else{
		errorprocess::showwarning(WARNING_NO_USING, str + " level is 0-2");
		return 0;
	}
	return 1;
}

/*
�ú����������ô��󼶱�
2011-02-09
22:47
*/
TYPE_STATUS macro::m_error()
{
	string str = strprocess::getstringarg(args,0);
	TYPE_NUM num = valueswitch::numvalue(str);
	if(str.length() == 0 || num == 0){
		g_errorlevel = 0;
	}else if(num == 1){
		g_errorlevel = 1;
	}else if(num == 2){
		g_errorlevel = 2;
	}else{
		errorprocess::showwarning(WARNING_NO_USING, str + " level is 0-2");
		return 0;
	}
	return 1;
}

/*
�ú������ڴ����ǩ�Ķ���
2011-02-10
12:59
*/
TYPE_STATUS macro::m_label()
{
	TYPE_STRING_ARRAY strs = strprocess::getstringarray(args);
	if(args.find_first_of('=') != string::npos){
		TYPE_KEYVALUE kv = strprocess::getkeyvalue(args);
		TYPE_VALUERESULT vr;
		valueswitch::valueresult(kv.value, vr);
		if(vr.flag){	//�Ѿ����
			return label::addlabel(TYPE_LABEL(kv.key, vr.type, vr.data));
		}
		else{
			errorprocess::showerr(ERR_NOT_CONST, kv.value);
			return 0;
		}
	}
	else if(args.length()==1 && args[0]=='{'){	//ǰջ��ǩ
		g_labelname.push(label::getnextlabel(0));
		return label::addcurrentadd(label::next());
	}
	else if(args.length()==1 && args[0]=='}'){	//��ջ��ǩ
		if(g_taskname.size()>0){
			label::addcurrentadd(g_taskname.top());
			g_taskname.pop();
			return 1;
		}
		else{
			errorprocess::showerr(ERR_HAVANO_LAB, "{");
			return 0;
		}
	}
	else if(args.length()>0){
		return label::addcurrentadd(strprocess::getstringarg(args));
	}
	else{
		return label::addnonamelabel();
	}
}

/*
�ú������������ļ�
2011-02-13
17:06
*/
TYPE_STATUS macro::m_file()
{
	g_filepoint.set(args);
	return 1;
}

/*
�ú�������������
2011-02-13
17:07
*/
TYPE_STATUS macro::m_line()
{
	g_filepoint.set(valueswitch::numvalue(args));
	return 1;
}


