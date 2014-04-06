#include "function.h"


/*
�ú������ڳ�ʼ��ָ��
2011-02-10
15:59
*/
TYPE_STATUS instruction::init()
{
	//cout<<"In..."<<endl;
	for(int i = 0; i<152; ++i){
		instruction::addins(TYPE_INSTRUCTION(const_ins_ins[i], const_ins_code[i], const_ins_size[i], const_ins_type[i]));
	}
	//cout<<"In OK!"<<endl;
	return 0;
}


/*
�ú������ڳ�ʼ��ָ��
2011-02-10
15:59
*/
void instruction::inf()
{
	TYPE_INSTRUCTIONS::const_iterator it;
	cout<<"Instruction Information:\n";
	cout<<'\t';
	cout.width(13);
	cout<<left<<"  Format";
	cout.width(6);
	cout<<hex<<"Code";
	cout.width(6);
	cout<<left<<"Size";
	cout<<"  Type"<<endl;
	for(it = g_inss.begin(); it != g_inss.end(); ++it){
		it->second.inf();
	}
	cout<<endl;
}


/*
�ú����������һ��ָ��
2011-02-10
14:17
*/
TYPE_STATUS instruction::addins(TYPE_INSTRUCTION ins)
{
	if(g_inss.find(ins.ins)==g_inss.end()){
		g_inss[ins.ins] = ins;
		return 1;
	}
	errorprocess::showerr(ERR_HAVA_INS, ins.ins);
	return 0;
}

/*
�ú������ڲ���ָ��
2011-02-10
16:16
*/
TYPE_INSTRUCTION* instruction::find(TYPE_NAME nm)
{
	if(g_inss.find(nm)==g_inss.end()){
		return NULL;
	}
	return &g_inss[nm];
}


/*
�ú����������һ��ָ��
2011-02-10
20:37
*/
TYPE_STATUS instruction::compileins(TYPE_STRING& g_ins)
{
	TYPE_FORMATRESULT rs;
	//strprocess::killfbspace(s);
//	strprocess::supper(g_ins);
	if(insformat::formatinstruction(g_ins, rs)){
		TYPE_INSTRUCTION* ins;
		//rs.inf();
		ins = instruction::find(rs.ins);
		if(ins){
			//ins->inf();
			segmentmanager::put(ins->code);	//д������
			if(rs.flag){	//���贴������
				TYPE_WORD wd;
				TYPE_BYTE bt;
				wd = (TYPE_WORD)(rs.data & 0xffff);
				bt = (TYPE_BYTE)(rs.data & 0xff);
				if(ins->type == DATATYPE_NONE){	//��ָ��
					
				}
				else if(ins->type == DATATYPE_BYTE){	//�ֽ�����
					segmentmanager::put(bt);
				}
				else if(ins->type == DATATYPE_ZPADDRESS){	//��ҳ
					segmentmanager::put(bt);
				}
				else if(ins->type == DATATYPE_ADDRESS){	//ȫַ
					segmentmanager::put(wd);
				}
				else if(ins->type == DATATYPE_RELATIVE){	//���ƫ��
					segmentmanager::putreaddress(wd);
				}
				return 1;
			}
			else{	//��������
				int sz;
				if(ins->type == DATATYPE_RELATIVE && ins->type != DATATYPE_NONE){
					task::addtask(rs.datastr, ins->type);
					sz = ins->size;
				}
				else{
					task::addtask(rs.datastr, rs.type);
					sz = gloabfunction::datatypesize(rs.type)+1;
				}
				TYPE_BYTE bt = 0xff;	//ռλ
				if(sz == 2){
					segmentmanager::put(bt);
				}
				else if(sz == 3){
					segmentmanager::put(bt);
					segmentmanager::put(bt);
				}
				return 1;
			}
		}
		else{
			errorprocess::showerr(ERR_ILL_SYN, rs.ins);
		}
	}
	return 0;
}




