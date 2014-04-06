#include "function.h"

/*
该函数用于输出标签集信息
2011-02-10
12:27
*/
void label::labelinf(TYPE_LABELS& lbs)
{
	cout<<"Label Information:\n\t";
	cout.width(28);
	cout<<left<<"LabelName";
	cout.width(14);
	cout<<left<<"Type";
	cout.width(14);
	cout<<left<<"Value"<<endl;
	for(map<TYPE_NAME, TYPE_LABEL>::const_iterator lb = lbs.begin(); lb != lbs.end(); ++lb){
		lb->second.inf();
	}
	cout<<endl;
}


/*
该函数用于向标签组添加标签
2011-02-10
12:15
*/
TYPE_STATUS label::addlabel(TYPE_LABEL lb, TYPE_LABELS& lbs)
{
	if(lbs.find(lb.label) == lbs.end()){	//未定义标签
		lbs[lb.label] = lb;
		return 1;
	}
	errorprocess::showerr(ERR_HAVA_LAB, lb.label);
	return 0;
}


/*
该函数用于向标签组添加当前地址标签
2011-02-10
12:59
*/
TYPE_STATUS label::addcurrentadd(TYPE_NAME nm, TYPE_LABELS& lbs)
{
	TYPE_SEGMENT* seg;
	if((seg = segmentmanager::getcurrentsegment()) && nm.length()){
		addlabel(TYPE_LABEL(nm, DATATYPE_ADDRESS, seg->nowpos()), lbs);
		return 1;
	}
	return 0;
}


/*
该函数用于从标签组获取标签
2011-02-10
12:35
*/
TYPE_STATUS label::getlabel(TYPE_NAME name, TYPE_LABEL& lb, TYPE_LABELS& lbs)
{
	if(lbs.find(name) != lbs.end()){	//存在标签
		lb = lbs[name];
		return 1;
	}
	//errorprocess::showerr(ERR_HAVANO_LAB, name);
	return 0;
}


/*
该函数用于获取前面的标签
2011-03-10
12:22
*/
TYPE_NAME label::getnextlabel(TYPE_POS offset)
{
	return "__LB" + valueswitch::numtohex(g_lbct+offset);
}

/*
该函数用于获取后面的标签
2011-03-10
12:24
*/
TYPE_NAME label::getprelabel(TYPE_POS offset)
{
	if(g_lbct<offset){
		errorprocess::showerr(ERR_HAVANO_LAB, "__LB" + valueswitch::numtohex(g_lbct-offset));
	}
	return "__LB" + valueswitch::numtohex(g_lbct-offset);
}

/*
该函数用于添加匿名标签
2011-03-10
12:27
*/
TYPE_STATUS label::addnonamelabel()
{
	if(addcurrentadd(getnextlabel(0))){
		g_lbct++;
		return 1;
	}
	return 0;
}

/*
该函数用于自动转向下一条
2011-03-10
19:42
*/
TYPE_NAME label::next()
{
	TYPE_NAME lb = getnextlabel(0);
	g_lbct++;
	return lb;
}