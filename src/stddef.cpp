#include "stddef.h"

namespace gloab{
	
	TYPE_CODE g_code_line;
	
	TYPE_POS g_code_len = 0;
	
	TYPE_CODE g_ins;
	
	bool isShowErrline = false;
	
	TYPE_POINT g_filepoint;
	
	TYPE_OUTFILE g_outfile;
	
	TYPE_BYTE g_warninglevel = 1;	//仅显示
	TYPE_BYTE g_errorlevel = 0; 	//显示并中断
	
	TYPE_FILENAME g_outfilename;
	TYPE_FILENAME g_infilename;
	
	TYPE_STRING g_version = "V1.2 Dev";
	
	TYPE_FILE_ARRAY g_includedfiles;
	TYPE_INS_ARRAY g_insarray;
	
	TYPE_LABELS g_labels;
	
	TYPE_INSTRUCTIONS g_inss;
	
	TYPE_TASKS g_tasks;
	
	bool g_insinf = false;
	bool g_tasinf = false;
	bool g_labinf = false;
	bool g_seginf = false;
	
	
	TYPE_POS g_lbct = 0;
	
	TYPE_STRING_STACK g_labelname;
	TYPE_STRING_STACK g_taskname;
};

TYPE_LABEL::TYPE_LABEL(TYPE_NAME lb, TYPE_DATATYPE fg, TYPE_WORD d)
{
	this->dat = d;
	this->flag = fg;
	this->label = lb;
}

void TYPE_LABEL::inf() const
{
	string ty = gloabfunction::datatypetostring(this->flag);
	cout<<'\t';
	cout.width(28);
	cout<<left<<this->label;
	cout.width(14);
	cout<<left<<ty;
	cout.width(14);
	cout<<left<<hex<<this->dat<<endl;
}

TYPE_POINT::TYPE_POINT(TYPE_FILENAME f, TYPE_LINE l)
{
	this->filename = f;
	this->line = l;
}

TYPE_RAMSEGMENT::TYPE_RAMSEGMENT(TYPE_NAME nm, TYPE_ADDRESS o, TYPE_SIZE s, TYPE_SIZE p)
{
	this->name = nm;
	this->org = o;
	this->pos = p;
	this->size = s;
}

TYPE_SEGMENT::TYPE_SEGMENT(TYPE_NAME nm, TYPE_ADDRESS o, TYPE_SIZE s, TYPE_SIZE p, TYPE_BYTE f)
{
	this->name = nm;
	this->pos = p;
	this->org = o;
	this->size = s;
	this->buf = NULL;
	this->fill = f;
	this->offset = 0;
}

TYPE_ADDRESS TYPE_SEGMENT::nowpos() const
{
	return this->org + this->pos;
}

void TYPE_SEGMENT::inf() const
{
	cout<<"\t";
	cout.width(28);
	cout<<left<<this->name;
	cout.width(7);
	cout<<hex<<left<<this->size;
	cout.width(7);
	cout<<hex<<left<<this->org;
	cout.width(8);
	cout<<left<<this->nowpos();
	cout<<this->pos<<"bytes("<<dec<<this->pos*100/this->size<<"%)"<<endl;
}

TYPE_TASK::TYPE_TASK(TYPE_NAME lb, TYPE_DATATYPE fg, TYPE_NAME seg, TYPE_ADDRESS add, TYPE_POINT pt)
{
	this->label = lb;
	this->segment = seg;
	this->flag = fg;
	this->point = pt;
	this->address = add;
}

TYPE_FUNCTION::TYPE_FUNCTION(TYPE_NAME nm, TYPE_STRING bd)
{
	this->name = nm;
	this->body = bd;

	this->romsize = 0;
	this->ramsize = 0;
}

TYPE_POINT::TYPE_POINT()
{
	this->filename = "";
	this->line = 0;
}

TYPE_LABEL::TYPE_LABEL()
{
	this->dat = 0;
	this->flag = DATATYPE_NONE;
}

TYPE_RAMSEGMENT::TYPE_RAMSEGMENT()
{
	this->name = "";
	this->org = 0;
	this->pos = 0;
	this->size = 0;
}

TYPE_SEGMENT::TYPE_SEGMENT()
{
	this->buf = NULL;
	this->fill = 0;
	this->name = "";
	this->offset = 0;
	this->org = 0;
	this->pos = 0;
	this->size = 0;
}

TYPE_TASK::TYPE_TASK()
{
	this->address = 0;
	this->flag = DATATYPE_NONE;
}

TYPE_FUNCTION::TYPE_FUNCTION()
{
	this->body = "";
	this->name = "";
	this->ramsize = 0;
	this->romsize = 0;
}



TYPE_FILENAME TYPE_POINT::getfilename()
{
	return this->filename;
}

TYPE_LINE TYPE_POINT::getline()
{
	return this->line;
}


void TYPE_POINT::set(TYPE_FILENAME f, TYPE_LINE l)
{
	this->filename = f;
	this->line = l;
}
void TYPE_POINT::set(TYPE_LINE l)
{
	this->line = l;
}
void TYPE_POINT::set(TYPE_FILENAME f)
{
	this->filename = f;
}
void TYPE_POINT::next()
{
	++this->line;
}

void TYPE_POINT::up()
{
	--this->line;
}


TYPE_OUTFILE::TYPE_OUTFILE()
{
	this->filesize = 0;
	this->currentsize = 0;
	this->currentsegment = NULL;
	this->segmentcount = 0;
}

TYPE_OUTFILE::TYPE_OUTFILE(TYPE_FILENAME fn)
{
	this->filesize = 0;
	this->currentsize = 0;
	this->currentsegment = NULL;
	this->segmentcount = 0;

	this->filename = fn;
}

void TYPE_OUTFILE::inf()
{
	cout<<"\tOutFileName:"<<filename<<endl;
	cout<<"\tFileSize:"<<filesize<<endl;
	cout<<"\tCurrentSize:"<<currentsize<<endl;
	cout<<"\tSegmentCount:"<<segmentcount<<endl;
	if(currentsegment){
		cout<<"\tCurrentSegment:"<<currentsegment->name<<endl<<endl;
		cout<<"\t";
		cout.width(28);
		cout<<left<<"SegmentName";
		cout.width(7);
		cout<<hex<<left<<"Size";
		cout.width(7);
		cout<<hex<<left<<"Start";
		cout.width(8);
		cout<<left<<"Address";
		cout<<"Aready Used"<<endl;
		for(map<TYPE_NAME, TYPE_SEGMENT>::const_iterator seg = this->segments.begin(); this->segments.size() && seg != this->segments.end(); ++seg){
			seg->second.inf();
		}
	}
	else cout<<"\tCurrentSegment:None"<<endl<<endl;
}

TYPE_OUTFILE::~TYPE_OUTFILE()
{
	for(map<TYPE_NAME, TYPE_SEGMENT>::iterator seg = this->segments.begin(); seg != this->segments.end(); ++seg){
		delete seg->second.buf;
	}
}

TYPE_SIZE TYPE_OUTFILE::emptysize()
{
	return this->currentsegment->size - this->currentsegment->pos;
}

TYPE_BYTE_STRING::TYPE_BYTE_STRING()
{
	this->buf = NULL;
	this->size = 0;
	this->capacity = 0;
}

TYPE_BYTE_STRING::~TYPE_BYTE_STRING()
{
	if(this->buf){
		delete this->buf;
	}
	this->buf = NULL;
	this->size = 0;
	this->capacity = 0;
}



TYPE_INSTRUCTION::TYPE_INSTRUCTION()
{
	this->ins = "";
	this->code = 0;
	this->size = 0;
	this->type = DATATYPE_NONE;
}


TYPE_INSTRUCTION::TYPE_INSTRUCTION(TYPE_NAME i, TYPE_BYTE c, TYPE_SSIZE s, TYPE_DATATYPE t)
{
	this->ins = i;
	this->code = c;
	this->size = s;
	this->type = t;
}


void TYPE_INSTRUCTION::inf() const
{
	TYPE_STRING ty = gloabfunction::datatypetostring(this->type);
	cout<<'\t';
	cout.width(14);
	cout<<left<<this->ins;
	cout.width(6);
	cout<<hex<<(int)this->code;
	cout.width(6);
	cout<<left<<(int)this->size;
	cout<<ty<<endl;
}

void TYPE_FORMATRESULT::inf()
{
	TYPE_STRING ty = gloabfunction::datatypetostring(this->type);
	
	cout<<"\tIns:"<<this->ins<<"\n\tType:"<<ty<<"\n\tflag:"<<(int)this->flag<<"\n\tData:"<<hex<<(int)this->data<<"\n\tStr:"<<this->datastr<<endl;
}


void TYPE_TASK::inf()
{
	TYPE_STRING ty = gloabfunction::datatypetostring(this->flag);
	//cout<<"\tLabel:";
	cout<<'\t';
	cout.width(20);
	cout<<left<<this->label;
	cout.width(14);
	cout<<left<<this->segment;
	cout.width(10);
	cout<<left<<ty;
	cout.width(5);
	cout<<left<<hex<<this->address;
	cout<<this->point.getfilename()<<':'<<dec<<this->point.getline()<<endl;
}

void TYPE_VALUERESULT::inf() const
{
	TYPE_STRING ty = gloabfunction::datatypetostring(this->type);
	cout<<"\tData:"<<hex<<(int)this->data<<" Flag:"<<(int)this->flag<<" StrData:"<<this->datastr<<" Type:"<<ty<<endl;
}



