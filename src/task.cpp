#include "function.h"

/*
该函数用于添加任务
2011-02-11
23:11
*/
TYPE_STATUS task::addtask(TYPE_NAME lb, TYPE_DATATYPE fg)
{
	TYPE_SEGMENT* seg = segmentmanager::getcurrentsegment();
	TYPE_TASK task(lb, fg, seg->name, seg->nowpos(), g_filepoint);
	g_tasks.push_back(task);
	
	return 1;
}


/*
该函数用于输出消息
2011-02-11
23:19
*/
void task::taskinf()
{
	cout<<"Task Information:"<<endl;
	cout<<'\t';
	cout.width(20);
	cout<<"LabelName";
	cout.width(14);
	cout<<"SegmentName";
	cout.width(10);
	cout<<"Type";
	cout.width(5);
	cout<<"Add.";
	cout<<"Point"<<endl;
	for(unsigned int i=0; i<g_tasks.size(); ++i){
		g_tasks[i].inf();
	}
	cout<<endl;
}

/*
该函数用于做任务
2011-02-11
23:46
*/
TYPE_STATUS task::dotask()
{
	isShowErrline = false;
	TYPE_TASKS::iterator it;
	TYPE_NAME segs = segmentmanager::getcurrentsegment()->name;
	TYPE_SIZE adds = segmentmanager::getcurrentsegment()->nowpos();
	TYPE_BYTE hbt, lbt;
	TYPE_WORD wd;
	for(it = g_tasks.begin(); it != g_tasks.end(); ++it){
		TYPE_VALUERESULT vr;
		valueswitch::valueresult(it->label, vr);
		if(vr.flag){	//found
			lbt = (TYPE_BYTE)vr.data;
			hbt = (TYPE_BYTE)vr.data;
			wd = (TYPE_WORD)vr.data;
			segmentmanager::setcurrentsegment(it->segment);
			segmentmanager::setorgaddress(it->address);
			switch(it->flag)
			{
				case DATATYPE_LABEL:
				case DATATYPE_TASK:
				case DATATYPE_NONE:{
					break;
				}
				case DATATYPE_BIG:
				case DATATYPE_ADDRESS:
				case DATATYPE_WORD:{
					segmentmanager::put(wd);
					break;
				}
				
				case DATATYPE_HBYT:{
					segmentmanager::put(hbt);
					break;
				}
				
				case DATATYPE_ZPADDRESS:
				case DATATYPE_BYTE:
				case DATATYPE_LBYT:{
					segmentmanager::put(lbt);
					break;
				}
				
				case DATATYPE_RELATIVE:{
					segmentmanager::putreaddress(wd);
					break;
				}
			}
		}
		else{	//No found 
			//cout<<"No Find:"<<it->label<<endl;
			TYPE_POINT pt = g_filepoint;
			g_filepoint = it->point;
			errorprocess::showerr(ERR_CNT_LAB, it->label);
			g_filepoint = pt;
		}
	}
	
	segmentmanager::setcurrentsegment(segs);
	segmentmanager::setorgaddress(adds);
	isShowErrline = true;
	return 0;
}










