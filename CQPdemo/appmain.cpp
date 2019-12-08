/*
* CoolQ Demo for VC++ 
* Api Version 9
* Written by Coxxs & Thanks for the help of orzFly
*/

#include "stdafx.h"
#include "string"
#include "cqp.h"
#include "appmain.h" //Ӧ��AppID����Ϣ������ȷ��д�������Q�����޷�����
#include "ifly.h"

#include <ctime>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <time.h>
#include <random>
#include <Windows.h>
#include <locale.h>
#include <process.h>
#include <regex>

using namespace std;

int ac = -1; //AuthCode ���ÿ�Q�ķ���ʱ��Ҫ�õ�
int totalreceivemsg = 0;//ÿ�ս�����Ϣ��
int totalsendmsg = 0;//ÿ�շ�����Ϣ��
bool enabled = false;
bool pythonenabled = true;
bool repeatenabled = true;
bool cenabled = true;
bool pixivenabled = true;
bool baiduseepicenabled = true;
bool saytimeenabled = true;
bool ipsearchenabled = true;
bool onlinecompileenabled = true;
bool setuenabled = true;
bool asynpythonenabled = false;
bool ijsenabled = false;

string asynpythonfile = "asyn.py";

struct repeprob
{
	int64_t fromQQ;
	int prob;
};

struct msgrecord
{
	int64_t fromQQ;
	string message;
};

struct addrequest
{
	int64_t QQorGroup;
	string responseflag;
};

struct groupmsg
{
	int64_t fromQQ;
	int64_t fromGroup;
	int32_t msgId;
	string msg;
};

//�����cmd����
vector<string> allowedcmdword = { "ping","python","ver","hath.py" };
//����������
vector<string> specialallowedcmdword = { };
//�����pythonģ��
vector<string> allowedpython = { "import math","import numpy","import numba","import scipy","import random","import requests",
								"import hashlib","import jieba","import unidecode","import time","import sys","import sympy",
								"import bs4","import re" };
//�����c��
vector<string> allowedc = { "#include <stdio.h>","#include <time.h>","#include <string.h>","#include <math.h>","#include <cmath.h>" };
//����Ĺ���Ա����
vector<string> allowedadminword = { "pip", "tasklist", "taskkill"};
//����Ա
vector<int64_t> admins = { 1325275429, 915326989, 3148859519, 1242158343, 632787458, 1063260948, 819774119, 1053017630, 1518350122 };
//��������
vector<repeprob> repeatprobability = {};
//����ظ�����
vector<string> randomreplycontent = {  };
//����˵���Ⱥ����
vector<addrequest> GroupReview = {};
//����˵ĺ�������
vector<addrequest> FriendReview = {};



void SaveMsgAmount();

string to_utf8(const wchar_t* buffer, int len)
{
	int nChars = ::WideCharToMultiByte(
		CP_UTF8,
		0,
		buffer,
		len,
		NULL,
		0,
		NULL,
		NULL);
	if (nChars == 0) return "";

	string newbuffer;
	newbuffer.resize(nChars);
	::WideCharToMultiByte(
		CP_UTF8,
		0,
		buffer,
		len,
		const_cast< char* >(newbuffer.c_str()),
		nChars,
		NULL,
		NULL);

	return newbuffer;
}

string to_utf8(const std::wstring& str)
{
	return to_utf8(str.c_str(), (int)str.size());
}

void AnsiToUnicode(char* szAnsi)
{
	/*
	// ansi to unicode
	char* szAnsi = "abcd1234������";
	//Ԥת�����õ�����ռ�Ĵ�С
	int wcsLen = MultiByteToWideChar(CP_ACP, NULL, szAnsi, strlen(szAnsi), NULL, 0);
	//����ռ�Ҫ��'\0'�����ռ䣬MultiByteToWideChar�����'\0'�ռ�
	wchar_t* wszString = new wchar_t[wcsLen + 1];
	//ת��
	MultiByteToWideChar(CP_ACP, NULL, szAnsi, strlen(szAnsi), wszString, wcsLen);
	//������'\0'
	wszString[wcsLen] = '\0';
	//unicode���MessageBox API
	//MessageBoxW(GetSafeHwnd(), wszString, wszString, MB_OK);

	//������д���ı�
	//д�ı��ļ���ͷ2���ֽ�0xfeff����λ0xffд��ǰ
	CFile cFile;
	cFile.Open(_T("1.txt"), CFile::modeWrite | CFile::modeCreate);
	//�ļ���ͷ
	cFile.SeekToBegin();
	cFile.Write("\xff\xfe", 2);
	//д������
	cFile.Write(wszString, wcsLen * sizeof(wchar_t));
	cFile.Flush();
	cFile.Close();
	delete[] wszString;
	wszString = NULL;
	*/

	//����2
	//���õ�ǰ������Ϣ�������õĻ���ʹ�����ַ��������Ĳ�����ȷ��ʾ
	//��Ҫ#include<locale.h>
	setlocale(LC_CTYPE, "chs");
	wchar_t wcsStr[100];
	//ע�������Ǵ�дS����unicode�У����������ansi�ַ���
	//swprintf��sprintf��unicode�汾
	//��ʽ��ǰ��Ҫ�Ӵ�дL��������unicode
	swprintf(wcsStr, L"%S", szAnsi);
	//::MessageBoxW(GetSafeHwnd(), wcsStr, wcsStr, MB_OK);
}


void ReadRepeatProb()
{
	ifstream infile;
	infile.open("repeatprob.txt");

	repeprob r;
	while (!infile.eof())
	{
		infile >> r.fromQQ >> r.prob;
		int iter;
		for (iter = 0; ; iter++)
		{
			if (iter >= repeatprobability.size())
			{
				repeatprobability.push_back(r);
				break;
			}
			if (repeatprobability[iter].fromQQ == r.fromQQ)
				break;
		}
	}

	infile.close();
}

void SaveRepeatProb()
{
	ofstream outfile;
	outfile.open("repeatprob.txt");

	for (int i = 0; i < repeatprobability.size(); i++)
	{
		outfile << repeatprobability[i].fromQQ << ' ' << repeatprobability[i].prob << "\n";
	}

	outfile.close();
}

void ReadRandomReplyContent()
{
	ifstream infile;
	infile.open("randomreplycontent.txt");

	string s;
	while (!infile.eof())
	{
		infile >> s;
		auto p = find(randomreplycontent.begin(), randomreplycontent.end(), s);
		if (p == randomreplycontent.end())
			randomreplycontent.push_back(s);
		else
			;
	}

	infile.close();
}

void SaveRandomReplyContent()
{
	ofstream outfile;
	outfile.open("randomreplycontent.txt");

	for (int i = 0; i < randomreplycontent.size(); i++)
	{
		outfile << randomreplycontent[i] << "\n";
	}

	outfile.close();
}

vector<string> exec(vector<string> cmd, int64_t fromGroup) {
	FILE* pipe;
	char buffer[128];
	vector<string> result;

	for (int i = 0; i < cmd.size(); i++)
	{
		pipe = _popen(cmd[i].c_str(), "r");
		//if (!pipe) return { "ERROR", };
		result.push_back("");
		clock_t t0 = clock();
		while (!feof(pipe)) 
		{
			/*if ((clock() - t0) / 1000 > 1000)
			{
				CQ_sendGroupMsg(ac, fromGroup, "����ʱ");
				system("taskkill /F /IM python.exe");
				//system("taskkill /F /IM cmd.exe");
				Sleep(1000);
				_pclose(pipe);
				return result;
			}*/
			if (fgets(buffer, 128, pipe) != NULL)
				result[i] += buffer;
		}
	}
	_pclose(pipe);
	return result;
}//����cmd

string exec(string cmd, int64_t fromGroup) {
	FILE* pipe;
	char buffer[128];
	string result;

	pipe = _popen(cmd.c_str(), "r");
	//if (!pipe) return { "ERROR", };
	clock_t t0 = clock();
	while (!feof(pipe))
	{
		if (fgets(buffer, 128, pipe) != NULL)
			result += buffer;
	}
	_pclose(pipe);
	return result;
}//����cmd

string Word(string str, int i)
{
	string word;
	for (int k = 0; k < str.size(); k++)
	{
		if (str[k] == ' ' && i == 1)
			break;
		else if (str[k] == ' ' && i > 1)
		{
			word.clear();
			i--;
		}
		else if (i == 1)
			word.push_back(str[k]);//�ո�ǰ���ַ�
	}
	return word;//��i���ʴ�1��ʼ
}

string Replace(string raw, vector<string> target, vector<string> aim)
{
	for (int i = 0; i < target.size(); i++)
	{
		regex reg(target[i]);
		raw = regex_replace(raw, reg, aim[i]);
	}
	return raw;
}

string Replace(string raw, string target, string aim)
{
	regex reg(target);
	raw = regex_replace(raw, reg, aim);
	return raw;
}

bool isadmin(int64_t fromQQ)
{
	auto iter3 = find(admins.begin(), admins.end(), fromQQ);
	if (iter3!= admins.end())
	{
		return true;
	}
	else
		return false;
}

bool isallowed(string str, int64_t fromQQ)
{
	string firstword = Word(str, 1);
	auto iter1 = find(allowedcmdword.begin(), allowedcmdword.end(), firstword);//���б�������
	auto iter2 = find(specialallowedcmdword.begin(), specialallowedcmdword.end(), str);
	auto iter3 = find(allowedadminword.begin(), allowedadminword.end(), firstword);
	if (iter1 != allowedcmdword.end() || iter2 != specialallowedcmdword.end() || iter3 != allowedadminword.end() && isadmin(fromQQ))
	{
		return true;
	}
	else
		return false;
}

bool isallowedpython(string str)
{
	auto iter2 = find(allowedpython.begin(), allowedpython.end(), str);
	if (iter2 != allowedpython.end())
	{
		return true;
	}
	else
		return false;
}

bool isallowedc(string str)
{
	auto iter2 = find(allowedc.begin(), allowedc.end(), str);
	if (iter2 != allowedc.end())
	{
		return true;
	}
	else
		return false;
}

void ViewSettings( int64_t fromGroup)
{
	string answer;
	answer.append("�����cmd����:");
	for (int i = 0; i < allowedcmdword.size(); i++)
	{
		answer.append(allowedcmdword[i]);
		answer.append(",");
	}
	answer.append("\n");
	/*
	answer.append("�����pythonģ��:");
	for (int i = 0; i < allowedpython.size(); i++)
	{
		answer.append(allowedpython[i]);
		answer.append(",");
	}
	answer.append("\n");
	answer.append("�����c��:");
	for (int i = 0; i < allowedc.size(); i++)
	{
		answer.append(allowedc[i]);
		answer.append(",");
	}*/

	CQ_sendGroupMsg(ac, fromGroup, answer.c_str());
	totalsendmsg++;
}

void SavePython(vector<string> msgstring, int64_t fromGroup, int64_t fromQQ)
{
	string PythonContent = "# -*- coding: ANSI -*-\n";
	string filename = to_string(fromQQ) + ".py";
	if (Word(msgstring[0], 2) != "" && isadmin(fromQQ))
	{
		filename = Word(msgstring[0], 2);
		CQ_sendGroupMsg(ac, fromGroup, ("д��" + filename).c_str());
		totalsendmsg++;
	}
	int i;
	for (i = 1; i < msgstring.size() && msgstring[i] != "endpython"; i++)
	{
		/*
		string firstword = Word(msgstring[i], 1);
		if (firstword == imp || firstword == fro)
		{
			if (isallowedpython(msgstring[i]))
			{
				//CQ_sendGroupMsg(ac, fromGroup, "�Ϸ���ģ��");
				PythonContent.append(msgstring[i]);
				PythonContent.push_back('\n');
			}
			else
			{
				CQ_sendGroupMsg(ac, fromGroup, "�Ƿ���ģ��");
				totalsendmsg++;
			}
				
		}
		else
		{
			PythonContent.append(msgstring[i]);
			PythonContent.push_back('\n');
		}*/
		msgstring[i] = Replace(msgstring[i], "&#91;", "[");
		msgstring[i] = Replace(msgstring[i], "&#93;", "]");
		PythonContent.append(msgstring[i]);
		PythonContent.push_back('\n');
	}
	ofstream outpyfile;
	outpyfile.open(("pythoncode\\" + filename).c_str());
	outpyfile.imbue(locale("", locale::all ^ locale::numeric));
	outpyfile << PythonContent;
	outpyfile.close();

}

void SaveC(vector<string> msgstring, int64_t fromGroup, int64_t fromQQ)
{
	string CContent;
	int i;
	for (i = 1; i < msgstring.size() && msgstring[i] != "endc"; i++)
	{
		/*
		bool doubt = false, danger = false;
		if (msgstring[i].size() > 7)
			for (int j = 0; j < msgstring[i].size()-8; j++)
				if (msgstring[i].substr(j, 8) == inc)
					doubt = true;
		if (msgstring[i].size() > 6)
			for (int j = 0; j < msgstring[i].size() - 7; j++)
				if (msgstring[i].substr(j, 7) == sys)
					danger = true;
		if (danger)
		{
			CQ_sendGroupMsg(ac, fromGroup, "ȥ�����system");
			totalsendmsg++;
			return;
		}
		if (doubt)
		{
			if (isallowedc(msgstring[i]))
			{
				//CQ_sendGroupMsg(ac, fromGroup, "�Ϸ���ģ��");
				CContent.append(msgstring[i]);
				CContent.push_back('\n');
			}
			else
			{
				CQ_sendGroupMsg(ac, fromGroup, "�Ƿ��Ŀ�");
				totalsendmsg++;
				return;
			}
		}
		else
		{
			CContent.append(msgstring[i]);
			CContent.push_back('\n');
		}*/
		msgstring[i] = Replace(msgstring[i], "&#91;", "[");
		msgstring[i] = Replace(msgstring[i], "&#93;", "]");
		CContent.append(msgstring[i]);
		CContent.push_back('\n');
	}
	ofstream outcfile;
	outcfile.open(("ccode\\" + to_string(fromQQ) + ".c").c_str());
	//outpyfile.imbue(locale("", locale::all ^ locale::numeric));
	outcfile << CContent;
	outcfile.close();

}

void RunPython(string msgstring0, int64_t fromGroup, int64_t fromQQ)
{
	string cmd = "pythonw pythoncode\\run.py " + to_string(fromQQ) + ".py" + msgstring0.substr(9);//20181208�޸�pythonw
	CQ_sendGroupMsg(ac, fromGroup, exec(cmd, fromGroup).c_str());
	totalsendmsg++;
}

void RunC(string msgstring0, int64_t fromGroup, int64_t fromQQ)
{
	string cmd = "pythonw ccode\\run.py " + to_string(fromQQ) + ".c" + msgstring0.substr(4);//20181208�޸�pythonw
	CQ_sendGroupMsg(ac, fromGroup, exec(cmd, fromGroup).c_str());
	totalsendmsg++;
}

void BrotherSound(int64_t fromGroup)
{
	int a = (rand()+66)* 97 % 163;
	string answer = "[CQ:record,file=";
	string suffix = "brothersound.mp3]";
	answer = answer + to_string(a) + suffix;
	CQ_sendGroupMsg(ac, fromGroup, answer.c_str());
	totalsendmsg++;
}

void Ifly(vector<string> msgstring, int64_t fromGroup)
{
	ifly a;
	if (msgstring.size() > 1 && msgstring[1] == "/?")
	{
		CQ_sendGroupMsg(ac, fromGroup, "�����ʽ��\nifly\nxiaoqi 65 50 47\n%�ı�����%\n�ĸ������ֱ�Ϊ�����ˡ��ٶȡ�����������");
		totalsendmsg++;
		return;
	}
	a.voice_name = Word(msgstring[1], 1);
	a.speed = Word(msgstring[1], 2);
	a.volume = Word(msgstring[1], 3);
	a.pitch = Word(msgstring[1], 4);
	for (int i = 2; i < msgstring.size(); i++)
	{
		a.text.append(msgstring[i]);
		a.text.push_back('\n');
	}
	if (a.TextSaveasWav())
	{
		CQ_sendGroupMsg(ac, fromGroup, "ת��ʧ��");
		totalsendmsg++;
	}
	else
	{
		_sleep(20);
		CQ_sendGroupMsg(ac, fromGroup, "[CQ:record,file=iflytexttosound.wav]");
		totalsendmsg++;
	}
}

void Pixiv(vector<string> msgstring, int64_t fromGroup)
{
	if (msgstring.size() > 1 && msgstring[1] == "/?")
	{
		CQ_sendGroupMsg(ac, fromGroup, "�����ʽ��\npixiv\nrefresh 6 1 0\n���������ֱ�Ϊģʽ��r18��·��\nģʽ��1��7\n1����\n2����\n3����\n4ԭ��\n5����\n6������\n7Ů����\nr18����Ϊ��\n·����0Ϊ�ƶ�");
		totalsendmsg++;
	}
	else if (msgstring.size() > 1 && Word(msgstring[1], 1) == "send")
	{
		string a = Word(msgstring[1], 2);
		if (a.empty())
			return;
		string head = "[CQ:image,file=pixivimage";
		string end = ".jpg]";
		head = head + a + end;
		CQ_sendGroupMsg(ac, fromGroup, head.c_str());
		totalsendmsg++;
	}
	else if (msgstring.size() > 1 && Word(msgstring[1], 1) == "sendr18")
	{
		string a = Word(msgstring[1], 2);
		if (a.empty())
			return;
		string head = "[CQ:image,file=pixivimage";
		string end = "r18.jpg]";
		head = head + a + end;
		int64_t msgid = CQ_sendGroupMsg(ac, fromGroup, head.c_str());
		totalsendmsg++;
		_sleep(40000);
		CQ_deleteMsg(ac, msgid);
	}
	else if (msgstring.size() > 1 && Word( msgstring[1], 1) == "refresh")
	{
		string mode = Word(msgstring[1], 2);
		if (mode.empty())
			return;
		string r18 = Word(msgstring[1], 3);
		if (r18.empty())
			return;
		string path = Word(msgstring[1], 4);
		if (path.empty())
			return;
		string cmd = "pythonw crawlFromPivix.py " + mode + " 5 " + r18;//20181208�޸�pythonw
		if (path == "0")
			cmd = cmd + " E:\\CQPro\\data\\image\\";
		else
			cmd = cmd + " C:\\CQPro\\data\\image\\";
		CQ_sendGroupMsg(ac, fromGroup, "������ȡ");
		totalsendmsg++;
		system(cmd.c_str());
		CQ_sendGroupMsg(ac, fromGroup, "��ȡ����");
		totalsendmsg++;
	}
	else if (msgstring.size() > 1 && Word(msgstring[1], 1) == "r18")
	{
		string head = "[CQ:image,file=pixivimage";
		random_device rd;   // non-deterministic generator  
		mt19937 gen(rd());  // to seed mersenne twister.  
		uniform_int_distribution<> dist(1, 50); // distribute results between 1 and 6 inclusive.  
		head = head + to_string(dist(gen)) + "r18.jpg]";
		int64_t msgid = CQ_sendGroupMsg(ac, fromGroup, head.c_str());
		totalsendmsg++;
		_sleep(40000);
		CQ_deleteMsg(ac, msgid);
	}
	else
	{
		string head = "[CQ:image,file=pixivimage";
		string end = ".jpg]";
		random_device rd;   // non-deterministic generator  
		mt19937 gen(rd());  // to seed mersenne twister.  
		uniform_int_distribution<> dist(1, 50); // distribute results between 1 and 6 inclusive.  
		head = head + to_string(dist(gen)) + end;
		CQ_sendGroupMsg(ac, fromGroup, head.c_str());
		totalsendmsg++;
	}
}

void BaiduSeePic(vector<string> msgstring, int64_t fromGroup)
{
	string cmd = "pythonw baiduSeePic.py " + msgstring[1];//20181208�޸�pythonw
	string ans = exec(cmd, fromGroup);
	CQ_sendGroupMsg(ac, fromGroup, ans.c_str());
	totalsendmsg++;
}

void Tex2Image(vector<string> msgstring, int64_t fromGroup)
{
	string texstring;
	for (int i = 1; i < msgstring.size(); i++)
		texstring.append(msgstring[i]);
	system(("pythonw Tex2Image.py \"" + texstring + "\"").c_str());//20181208�޸�pythonw

	CQ_sendGroupMsg(ac, fromGroup, "[CQ:image,file=tex.png]");
	totalsendmsg++;
}

void IpSearch(vector<string> msgstring, int64_t fromGroup)
{
	string answer;
	if (msgstring.size()>1)
		answer = exec("pythonw IpSearch.py " + msgstring[1], fromGroup);//20181208�޸�pythonw
	
	CQ_sendGroupMsg(ac, fromGroup, answer.c_str());
	totalsendmsg++;
}

void SaveCode(vector<string> msgstring, int64_t fromGroup, int64_t fromQQ, string type)
{
	string Content;
	for (int i = 1; i < msgstring.size(); i++)
	{
		if (msgstring[i] == "end" + type)
			break;
		msgstring[i] = Replace(msgstring[i], "&#91;", "[");
		msgstring[i] = Replace(msgstring[i], "&#93;", "]");
		Content = Content + msgstring[i];
		Content.push_back('\n');
	}
	ofstream outfile;
	outfile.open(("othercode\\" + to_string(fromQQ) + "." + type).c_str());
	//outpyfile.imbue(locale("", locale::all ^ locale::numeric));
	outfile << Content;
	outfile.close();
}

void RunCode(int64_t fromGroup, int64_t fromQQ, string type)
{
	string answer;
	answer = exec("pythonw compile2.py " + type + " " + to_string(fromQQ) + "." + type, fromGroup);//20181208�޸�pythonw
	CQ_sendGroupMsg(ac, fromGroup, answer.c_str());
	totalsendmsg++;
}

void EatWhat(int64_t fromGroup, int64_t fromQQ)
{
	CQ_sendGroupMsg(ac, fromGroup, exec("pythonw eatwhat.py", fromGroup).c_str());//20181208�޸�pythonw
	totalsendmsg++;
}

void KdSearch(vector<string> msgstring, int64_t fromGroup, int64_t fromQQ)
{
	CQ_sendGroupMsg(ac, fromGroup, exec("pythonw kuaidiSearch.py " + msgstring[1], fromGroup).c_str());//20181208�޸�pythonw
	totalsendmsg++;
}

void AgreeApply(vector<string>msgstring, int64_t fromQQ, int a)//0group,1friend
{
	if (!(isadmin(fromQQ) || fromQQ == 1325275429))
		return;
	if (!a)//group
	{
		for (int i = 1; i < msgstring.size(); i++)
		{
			for (int j = 0; j < GroupReview.size() ; j++)
			{
				if (GroupReview[j].QQorGroup == stoi(msgstring[i]))
				{
					CQ_setGroupAddRequestV2(ac, GroupReview[j].responseflag.c_str(), REQUEST_GROUPINVITE, REQUEST_ALLOW, "");
					CQ_sendGroupMsg(ac, 799733244, "��ͬ��");
					totalsendmsg++;
					break;
				}
			}
		}
	}
	else//friend
	{
		for (int i = 1; i < msgstring.size(); i++)
		{
			for (int j = 0; j < FriendReview.size(); j++)
			{
				if (FriendReview[j].QQorGroup == stoi(msgstring[i]))
				{
					CQ_setFriendAddRequest(ac, FriendReview[j].responseflag.c_str(), REQUEST_ALLOW, "");
					CQ_sendGroupMsg(ac, 799733244, "��ͬ��");
					totalsendmsg++;
					break;
				}
			}
		}
	}
	
}

void CheckSetu(string msgstring0, int64_t fromGroup)
{
	for (int i = 0 ; i < msgstring0.size(); i++)
	{
		if (msgstring0[i] == ']')
		{
			msgstring0 = msgstring0.substr(0, i + 1);
			break;
		}	
	}
	//[CQ:image,file=****.jpg]
	string filetype = msgstring0.substr(msgstring0.size() - 5, 4);//".jpg"/".png"
	string filepath = "data/image/" + msgstring0.substr(15, msgstring0.size() - 16) + ".cqimg";
	string s;
	ifstream infile;
	infile.open(filepath.c_str());
	if (!infile.is_open())
		return;
	infile >> s; infile >> s;
	string md5 = s.substr(4);
	infile >> s;
	int width = stoi(s.substr(6));
	infile >> s;
	int height = stoi(s.substr(7));
	infile >> s;
	int size = stoi(s.substr(5));
	infile >> s;
	string url = s.substr(4);
	infile.close();

	//CQ_sendGroupMsg(ac, 799733244, (md5+"\n"+to_string(size)+"\n"+url).c_str());

	if ((filetype!=".jpg" && filetype!=".png") || size < 10000 || size > 5000000)
		return;

	CQ_addLog(ac, CQLOG_DEBUG, "ɫͼ���", (md5 + "\n" + to_string(size) + "\n" + url).c_str());
	string ans = exec("pythonw BaiduImgCensor.py \"" + url + "\" " + md5 + filetype, fromGroup);
	if (ans.size() > 0)
	{
		CQ_sendGroupMsg(ac, fromGroup, ans.c_str());
		totalsendmsg++;
	}
}

void SendSetu(int64_t fromGroup)
{
	int64_t msgid = CQ_sendGroupMsg(ac, fromGroup, exec("pythonw SelectSetu.py", fromGroup).c_str());
	totalsendmsg++;
	_sleep(20000);
	CQ_deleteMsg(ac, msgid);
}

void RunIjs(vector<string> msgstring, int64_t fromGroup, int64_t fromQQ)
{
	string expr = "";
	if (Word(msgstring[0], 1) == "ijs")
	{
		if (Word(msgstring[0], 2) != "")
		{
			if (Word(msgstring[0], 2) == "new")
			{
				CQ_sendGroupMsg(ac, fromGroup, exec("pythonw jsclient.py new " + to_string(fromQQ), fromGroup).c_str());
			}
			else if (Word(msgstring[0], 2) == "del")
			{
				CQ_sendGroupMsg(ac, fromGroup, exec("pythonw jsclient.py del " + to_string(fromQQ), fromGroup).c_str());
			}
			else
			{
				CQ_sendGroupMsg(ac, fromGroup, "syntax error");
			}
		}
		else
		{
			if (msgstring.size() > 1)
				for (int i = 1; i < msgstring.size(); i++)
				{
					expr += msgstring[i] + '\n';
				}
			expr = Replace(expr, vector<string>({ "\"", "\n"}), vector<string>({ "\\\"", " "}));
			CQ_sendGroupMsg(ac, fromGroup, exec("pythonw jsclient.py eval " + to_string(fromQQ) + " " + expr, fromGroup).c_str());
		}
	}
	else if (Word(msgstring[0], 1) == "ijsg")
	{
		if (Word(msgstring[0], 2) != "")
		{
			if (Word(msgstring[0], 2) == "new")
			{
				CQ_sendGroupMsg(ac, fromGroup, exec("pythonw jsclient.py new g" + to_string(fromGroup), fromGroup).c_str());
			}
			else if (Word(msgstring[0], 2) == "del")
			{
				CQ_sendGroupMsg(ac, fromGroup, exec("pythonw jsclient.py del g" + to_string(fromGroup), fromGroup).c_str());
			}
			else
			{
				CQ_sendGroupMsg(ac, fromGroup, "syntax error");
			}
		}
		else
		{
			if (msgstring.size() > 1)
				for (int i = 1; i < msgstring.size(); i++)
				{
					expr += msgstring[i] + '\n';
				}
			expr = Replace(expr, vector<string>({ "\"", "\n" }), vector<string>({ "\\\"", " " }));
			CQ_sendGroupMsg(ac, fromGroup, exec("pythonw jsclient.py eval g" + to_string(fromGroup) + " " + expr, fromGroup).c_str());
		}
	}
	totalsendmsg++;
}

void AdminSetting(vector<string> msgstring, int64_t fromGroup, int64_t fromQQ)
{
	bool issuadmin = fromQQ == 1325275429;
	for (int i = 1; i < msgstring.size(); i++)
	{
		if (msgstring[i] == "python on")
			pythonenabled = true;
		else if (msgstring[i] == "python off")
			pythonenabled = false;
		else if (msgstring[i] == "repeat on")
			repeatenabled = true;
		else if (msgstring[i] == "repeat off")
			repeatenabled = false;
		else if (msgstring[i] == "c on")
			cenabled = true;
		else if (msgstring[i] == "c off")
			cenabled = false;
		else if (msgstring[i] == "pixiv on")
			pixivenabled = true;
		else if (msgstring[i] == "pixiv off")
			pixivenabled = false;
		else if (msgstring[i] == "baiduseepic on")
			baiduseepicenabled = true;
		else if (msgstring[i] == "baiduseepic off")
			baiduseepicenabled = false;
		else if (msgstring[i] == "saytime on")
			saytimeenabled = true;
		else if (msgstring[i] == "saytime off")
			saytimeenabled = false;
		else if (msgstring[i] == "ipsearch on")
			ipsearchenabled = true;
		else if (msgstring[i] == "ipsearch off")
			ipsearchenabled = false;
		else if (msgstring[i] == "compile on")
			onlinecompileenabled = true;
		else if (msgstring[i] == "compile off")
			onlinecompileenabled = false;
		else if (msgstring[i] == "setu on")
			setuenabled = true;
		else if (msgstring[i] == "setu off")
			setuenabled = false;
		else if (msgstring[i] == "asynpython on")
			asynpythonenabled = true;
		else if (msgstring[i] == "asynpython off")
			asynpythonenabled = false;
		else if (msgstring[i] == "ijs on")
			ijsenabled = true;
		else if (msgstring[i] == "ijs off")
			ijsenabled = false;
		else if (Word(msgstring[i], 1) == "repeatprob")
		{
			repeprob a = { stoi(Word(msgstring[i], 2)), stoi(Word(msgstring[i], 3)) };
			int iter = 0;
			for (iter = 0; iter < repeatprobability.size(); iter++)
			{
				if (iter == repeatprobability.size())
					break;
				if (repeatprobability[iter].fromQQ == a.fromQQ)
					break;
			}
			if (iter < repeatprobability.size())
				repeatprobability[iter] = a;
			else
				repeatprobability.push_back(a);
			SaveRepeatProb();
		}
		else if (Word(msgstring[i], 1) == "addreplycontent")
		{
			if (Word(msgstring[i], 2) != "")
				randomreplycontent.push_back(Word(msgstring[i], 2));
			SaveRandomReplyContent();
		}
		else if (Word(msgstring[i], 1) == "delreplycontent")
		{
			string s = Word(msgstring[i], 2);
			if (s != "")
			{
				auto p = find(randomreplycontent.begin(), randomreplycontent.end(), s);
				if (p == randomreplycontent.end())
				{
					CQ_sendGroupMsg(ac, fromGroup, "û������");
					totalsendmsg++;
				}
				else
				{
					randomreplycontent.erase(p);
					CQ_sendGroupMsg(ac, fromGroup, "��ɾ��");
					totalsendmsg++;
				}
				SaveRandomReplyContent();
			}
			
		}
		else if (Word(msgstring[i], 1) == "addadmin" && issuadmin)
		{
			if (Word(msgstring[i], 2) != "")
				admins.push_back(stoi(Word(msgstring[i], 2)));
		}
		else if (Word(msgstring[i], 1) == "deladmin" && issuadmin)
		{
			if (Word(msgstring[i], 2) != "")
				admins.erase(find(admins.begin(), admins.end(), fromQQ));
		}
		else if (Word(msgstring[i], 1) == "setasynpythonfile" && issuadmin)
		{
			if (Word(msgstring[i], 2) != "")
				asynpythonfile = Word(msgstring[i], 2);
		}
	}
	CQ_sendGroupMsg(ac, fromGroup, "û�б��������");
	totalsendmsg++;
}

int SearchRepeatProbability(int64_t fromQQ)
{
	for (int i = 0; i < repeatprobability.size(); i++)
		if (repeatprobability[i].fromQQ == fromQQ)
			return repeatprobability[i].prob;
	return 5;
}

void PrintInfo(int64_t fromGroup)
{
	CQ_sendGroupMsg(ac, fromGroup, "�ɱ�̸������ϻ�����\nv3.0\n��л��ү���������ޡ����������");
	totalsendmsg++;
}

DWORD WINAPI SayTime(LPVOID pM)
{
	time_t rawtime;
	tm *info;
	bool o = true;
	while (saytimeenabled)
	{
		time(&rawtime);
		info = localtime(&rawtime);
		if (info->tm_min == 0 && o)
		{
			o = false;
			string dang;
			CQ_sendGroupMsg(ac, 570216513, ("������" + to_string(info->tm_hour) + "�㣬�����˿�ѧϰ").c_str());
			totalsendmsg++;
			for (int i = 0; i < info->tm_hour; i++)
			{
				dang = dang + "��";
			}
			CQ_sendGroupMsg(ac, 570216513, dang.c_str());
			totalsendmsg++;
			if (info->tm_hour == 0)
			{
				CQ_sendGroupMsg(ac, 570216513, ("�����յ�" + to_string(totalreceivemsg) + "����Ϣ\n����" + to_string(totalsendmsg) + "��").c_str());
				totalsendmsg = 1;
				totalreceivemsg = 0;
				CQ_sendGroupMsg(ac, 570216513, "�������ϱ�����");
				totalsendmsg++;

				system("del msgrecord.txt");
			}

			SaveMsgAmount();
			GroupReview.clear();
			FriendReview.clear();
		}
		else if (info->tm_min != 0)
			o = true;
		_sleep(1000);
	}
	return 0;
}

DWORD WINAPI AsynPythonCall(PVOID pM)
{
	groupmsg* gmg = (groupmsg*)pM;
	int64_t fromQQ = gmg->fromQQ;
	int64_t fromGroup = gmg->fromGroup;
	string msg = gmg->msg;
	int32_t msgId = gmg->msgId;
	//CQ_sendGroupMsg(ac, 799733244, (to_string(fromQQ)).c_str());

	string cmd = "pythonw pythoncode\\asynrun.py " + asynpythonfile + " " + to_string(fromGroup) + " " + to_string(fromQQ) + " " + to_string(msgId) + " " + msg ;
	string ans = exec(cmd, fromGroup);
	if (ans != "")
	{
		CQ_sendGroupMsg(ac, fromGroup, ans.c_str());
		totalsendmsg++;
	}
	delete gmg;

	return 0;
}

string RandomReply()
{
	if (randomreplycontent.size() < 1)
		return "��������˵ʲô";

	random_device rd;   // non-deterministic generator  
	mt19937 gen(rd());  // to seed mersenne twister.  
	uniform_int_distribution<> dist(0, randomreplycontent.size()-1); // distribute results between 1 and 6 inclusive.  
	int a = dist(gen);

	return randomreplycontent[a];
}

void ReadMsgAmount()
{
	ifstream infile;
	infile.open("msgamount.txt");
	infile >> totalreceivemsg;
	infile >> totalsendmsg;
	infile.close();
}

void SaveMsgAmount()
{
	ofstream outfile;
	outfile.open("msgamount.txt");
	outfile << totalreceivemsg << '\n';
	outfile << totalsendmsg << '\n';
	outfile.close();
}

void SaveMsgRecord(string newmsg)
{
	ofstream outfile;
	outfile.open("msgrecord.txt", ios::app);
	outfile << newmsg << '\n';
	outfile.close();
}




/* 
* ����Ӧ�õ�ApiVer��Appid������󽫲������
*/
CQEVENT(const char*, AppInfo, 0)() {
	return CQAPPINFO;
}


/* 
* ����Ӧ��AuthCode����Q��ȡӦ����Ϣ��������ܸ�Ӧ�ã���������������������AuthCode��
* ��Ҫ�ڱ��������������κδ��룬���ⷢ���쳣���������ִ�г�ʼ����������Startup�¼���ִ�У�Type=1001����
*/
CQEVENT(int32_t, Initialize, 4)(int32_t AuthCode) {
	ac = AuthCode;
	return 0;
}


/*
* Type=1001 ��Q����
* ���۱�Ӧ���Ƿ����ã������������ڿ�Q������ִ��һ�Σ���������ִ��Ӧ�ó�ʼ�����롣
* ��Ǳ�Ҫ����������������ش��ڡ���������Ӳ˵������û��ֶ��򿪴��ڣ�
*/
CQEVENT(int32_t, __eventStartup, 0)() {

	return 0;
}


/*
* Type=1002 ��Q�˳�
* ���۱�Ӧ���Ƿ����ã������������ڿ�Q�˳�ǰִ��һ�Σ���������ִ�в���رմ��롣
* ������������Ϻ󣬿�Q���ܿ�رգ��벻Ҫ��ͨ���̵߳ȷ�ʽִ���������롣
*/
CQEVENT(int32_t, __eventExit, 0)() {

	return 0;
}

/*
* Type=1003 Ӧ���ѱ�����
* ��Ӧ�ñ����ú󣬽��յ����¼���
* �����Q����ʱӦ���ѱ����ã�����_eventStartup(Type=1001,��Q����)�����ú󣬱�����Ҳ��������һ�Ρ�
* ��Ǳ�Ҫ����������������ش��ڡ���������Ӳ˵������û��ֶ��򿪴��ڣ�
*/
CQEVENT(int32_t, __eventEnable, 0)() {

	HANDLE hThread1 = CreateThread(NULL, 0, SayTime, NULL, 0, NULL);
	CloseHandle(hThread1);

	ReadRepeatProb();
	ReadRandomReplyContent();
	ReadMsgAmount();

	enabled = true;
	return 0;
}


/*
* Type=1004 Ӧ�ý���ͣ��
* ��Ӧ�ñ�ͣ��ǰ�����յ����¼���
* �����Q����ʱӦ���ѱ�ͣ�ã��򱾺���*����*�����á�
* ���۱�Ӧ���Ƿ����ã���Q�ر�ǰ��������*����*�����á�
*/
CQEVENT(int32_t, __eventDisable, 0)() {
	enabled = false;

	SaveMsgAmount();

	return 0;
}


/*
* Type=21 ˽����Ϣ
* subType �����ͣ�11/���Ժ��� 1/��������״̬ 2/����Ⱥ 3/����������
*/
CQEVENT(int32_t, __eventPrivateMsg, 24)(int32_t subType, int32_t msgId, int64_t fromQQ, const char *msg, int32_t font) {

	//���Ҫ�ظ���Ϣ������ÿ�Q�������ͣ��������� return EVENT_BLOCK - �ضϱ�����Ϣ�����ټ�������  ע�⣺Ӧ�����ȼ�����Ϊ"���"(10000)ʱ������ʹ�ñ�����ֵ
	//������ظ���Ϣ������֮���Ӧ��/�������������� return EVENT_IGNORE - ���Ա�����Ϣ
	totalreceivemsg++;

	return EVENT_IGNORE;
}


/*
* Type=2 Ⱥ��Ϣ
*/
CQEVENT(int32_t, __eventGroupMsg, 36)(int32_t subType, int32_t msgId, int64_t fromGroup, int64_t fromQQ, const char *fromAnonymous, const char *msg, int32_t font) {

	//CQ_setGroupLeave(ac, fromGroup, false);//20190112add

	totalreceivemsg++;
	SaveMsgRecord(string(msg));

	if (asynpythonenabled)
	{
		groupmsg* gmg = new groupmsg;
		gmg->fromQQ = fromQQ;
		gmg->fromGroup = fromGroup;
		gmg->msg = string(msg);
		gmg->msgId = msgId;
		HANDLE pythonthread = CreateThread(NULL, 0, AsynPythonCall, (LPVOID)(gmg), 0, NULL);
		CloseHandle(pythonthread);
	}

	//cmd
	vector<string> msgstring = {""};
	vector<string> answer;
	vector<string> cmd;
	string py = "python";
	int j = 0;
	for (int i = 0; i < strlen(msg); i++)
	{
		if (msg[i] == '\n')
		{
			msgstring.push_back("");
			j++;
		}
		else if (msg[i] == '\r')
			;
		else
		{
			msgstring[j].push_back(msg[i]);
		}
	}//���س��ֿ�


	if (Word(msgstring[0], 1) == "python" && pythonenabled)
	{
		SavePython(msgstring, fromGroup, fromQQ);
		return EVENT_BLOCK;//����QQ��.py
	}
	else if (Word(msgstring[0], 1) == "runpython" && pythonenabled)
	{
		RunPython(msgstring[0], fromGroup, fromQQ);
		return EVENT_BLOCK;
	}
	else if (msgstring[0] == "c" && cenabled)
	{
		SaveC(msgstring, fromGroup, fromQQ);
		return EVENT_BLOCK;//����QQ��.c
	}
	else if (msgstring[0] == "runc" && cenabled)
	{
		RunC(msgstring[0], fromGroup, fromQQ);
		return EVENT_BLOCK;
	}
	else if (msgstring[0] == "pixiv" && pixivenabled)
	{
		Pixiv(msgstring, fromGroup);
		return EVENT_BLOCK;
	}
	else if (msgstring[0] == "baiduseepic" && baiduseepicenabled)
	{
		BaiduSeePic(msgstring, fromGroup);
		return EVENT_BLOCK;
	}
	else if (msgstring[0] == "ifly")
	{
		Ifly(msgstring, fromGroup);
	}
	/*else if (msgstring[0] == "������")
	{
		BrotherSound(fromGroup);
		return EVENT_BLOCK;
	}*/
	else if (msgstring[0] == "info")
	{
		PrintInfo(fromGroup);
		return EVENT_BLOCK;
	}
	else if (msgstring[0] == "settings")
	{
		ViewSettings(fromGroup);//�鿴����
		return EVENT_BLOCK;
	}
	else if (msgstring[0] == "tex")
	{
		Tex2Image(msgstring, fromGroup);
		return EVENT_BLOCK;
	}
	else if (msgstring[0] == "ipsearch" && ipsearchenabled)
	{
		IpSearch(msgstring, fromGroup);
		return EVENT_BLOCK;
	}
	else if (msgstring[0] == "php" && onlinecompileenabled)
	{
		SaveCode(msgstring, fromGroup, fromQQ, "php");
		return EVENT_BLOCK;//����QQ��.php
	}
	else if (msgstring[0] == "runphp" && onlinecompileenabled)
	{
		RunCode(fromGroup, fromQQ, "php");
		return EVENT_BLOCK;//����QQ��.php
	}
	else if (msgstring[0] == "python2" && onlinecompileenabled)
	{
		SaveCode(msgstring, fromGroup, fromQQ, "python2");
		return EVENT_BLOCK;//����QQ��.python2
	}
	else if (msgstring[0] == "runpython2" && onlinecompileenabled)
	{
		RunCode(fromGroup, fromQQ, "python2");
		return EVENT_BLOCK;//����QQ��.python2
	}
	else if (msgstring[0] == "java" && onlinecompileenabled)
	{
		SaveCode(msgstring, fromGroup, fromQQ, "java");
		return EVENT_BLOCK;//����QQ��.java
	}
	else if (msgstring[0] == "runjava" && onlinecompileenabled)
	{
		RunCode(fromGroup, fromQQ, "java");
		return EVENT_BLOCK;//����QQ��.java
	}
	else if (msgstring[0] == "cpp" && onlinecompileenabled)
	{
		SaveCode(msgstring, fromGroup, fromQQ, "cpp");
		return EVENT_BLOCK;//����QQ��.cpp
	}
	else if (msgstring[0] == "runcpp" && onlinecompileenabled)
	{
		RunCode(fromGroup, fromQQ, "cpp");
		return EVENT_BLOCK;//����QQ��.cpp
	}
	else if (msgstring[0] == "ruby" && onlinecompileenabled)
	{
		SaveCode(msgstring, fromGroup, fromQQ, "ruby");
		return EVENT_BLOCK;//����QQ��.ruby
	}
	else if (msgstring[0] == "runruby" && onlinecompileenabled)
	{
		RunCode(fromGroup, fromQQ, "ruby");
		return EVENT_BLOCK;//����QQ��.ruby
	}
	else if (msgstring[0] == "csharp" && onlinecompileenabled)
	{
		SaveCode(msgstring, fromGroup, fromQQ, "csharp");
		return EVENT_BLOCK;//����QQ��.csharp
	}
	else if (msgstring[0] == "runcsharp" && onlinecompileenabled)
	{
		RunCode(fromGroup, fromQQ, "csharp");
		return EVENT_BLOCK;//����QQ��.csharp
	}
	else if (msgstring[0] == "scala" && onlinecompileenabled)
	{
		SaveCode(msgstring, fromGroup, fromQQ, "scala");
		return EVENT_BLOCK;//����QQ��.scala
	}
	else if (msgstring[0] == "runscala" && onlinecompileenabled)
	{
		RunCode(fromGroup, fromQQ, "scala");
		return EVENT_BLOCK;//����QQ��.scala
	}
	else if (msgstring[0] == "objectivec" && onlinecompileenabled)
	{
		SaveCode(msgstring, fromGroup, fromQQ, "objectivec");
		return EVENT_BLOCK;//����QQ��.objectivec
	}
	else if (msgstring[0] == "runobjectivec" && onlinecompileenabled)
	{
		RunCode(fromGroup, fromQQ, "objectivec");
		return EVENT_BLOCK;//����QQ��.objectivec
	}
	else if (msgstring[0] == "perl" && onlinecompileenabled)
	{
		SaveCode(msgstring, fromGroup, fromQQ, "perl");
		return EVENT_BLOCK;//����QQ��.perl
	}
	else if (msgstring[0] == "runperl" && onlinecompileenabled)
	{
		RunCode(fromGroup, fromQQ, "perl");
		return EVENT_BLOCK;//����QQ��.perl
	}
	else if (msgstring[0] == "perl6" && onlinecompileenabled)
	{
		SaveCode(msgstring, fromGroup, fromQQ, "perl6");
		return EVENT_BLOCK;//����QQ��.perl6
	}
	else if (msgstring[0] == "runperl6" && onlinecompileenabled)
	{
		RunCode(fromGroup, fromQQ, "perl6");
		return EVENT_BLOCK;//����QQ��.perl6
	}
	else if (msgstring[0] == "bash" && onlinecompileenabled)
	{
		SaveCode(msgstring, fromGroup, fromQQ, "bash");
		return EVENT_BLOCK;//����QQ��.bash
	}
	else if (msgstring[0] == "runbash" && onlinecompileenabled)
	{
		RunCode(fromGroup, fromQQ, "bash");
		return EVENT_BLOCK;//����QQ��.bash
	}
	else if (msgstring[0] == "assembly" && onlinecompileenabled)
	{
		SaveCode(msgstring, fromGroup, fromQQ, "assembly");
		return EVENT_BLOCK;//����QQ��.assembly
	}
	else if (msgstring[0] == "runassembly" && onlinecompileenabled)
	{
		RunCode(fromGroup, fromQQ, "assembly");
		return EVENT_BLOCK;//����QQ��.assembly
	}
	else if (msgstring[0] == "swift" && onlinecompileenabled)
	{
		SaveCode(msgstring, fromGroup, fromQQ, "swift");
		return EVENT_BLOCK;//����QQ��.swift
	}
	else if (msgstring[0] == "runswift" && onlinecompileenabled)
	{
		RunCode(fromGroup, fromQQ, "swift");
		return EVENT_BLOCK;//����QQ��.swift
	}
	else if (msgstring[0] == "go" && onlinecompileenabled)
	{
		SaveCode(msgstring, fromGroup, fromQQ, "go");
		return EVENT_BLOCK;//����QQ��.go
	}
	else if (msgstring[0] == "rungo" && onlinecompileenabled)
	{
		RunCode(fromGroup, fromQQ, "go");
		return EVENT_BLOCK;//����QQ��.go
	}
	else if (msgstring[0] == "typescript" && onlinecompileenabled)
	{
		SaveCode(msgstring, fromGroup, fromQQ, "typescript");
		return EVENT_BLOCK;//����QQ��.typescript
	}
	else if (msgstring[0] == "runtypescript" && onlinecompileenabled)
	{
		RunCode(fromGroup, fromQQ, "typescript");
		return EVENT_BLOCK;//����QQ��.typescript
	}
	else if (msgstring[0] == "lua" && onlinecompileenabled)
	{
		SaveCode(msgstring, fromGroup, fromQQ, "lua");
		return EVENT_BLOCK;//����QQ��.lua
	}
	else if (msgstring[0] == "runlua" && onlinecompileenabled)
	{
		RunCode(fromGroup, fromQQ, "lua");
		return EVENT_BLOCK;//����QQ��.lua
	}
	else if (msgstring[0] == "rust" && onlinecompileenabled)
	{
		SaveCode(msgstring, fromGroup, fromQQ, "rust");
		return EVENT_BLOCK;//����QQ��.rust
	}
	else if (msgstring[0] == "runrust" && onlinecompileenabled)
	{
		RunCode(fromGroup, fromQQ, "rust");
		return EVENT_BLOCK;//����QQ��.rust
	}
	else if (msgstring[0] == "kotlin" && onlinecompileenabled)
	{
		SaveCode(msgstring, fromGroup, fromQQ, "kotlin");
		return EVENT_BLOCK;//����QQ��.kotlin
	}
	else if (msgstring[0] == "runkotlin" && onlinecompileenabled)
	{
		RunCode(fromGroup, fromQQ, "kotlin");
		return EVENT_BLOCK;//����QQ��.kotlin
	}
	else if (msgstring[0] == "ats" && onlinecompileenabled)
	{
		SaveCode(msgstring, fromGroup, fromQQ, "ats");
		return EVENT_BLOCK;//����QQ��.ats
	}
	else if (msgstring[0] == "runats" && onlinecompileenabled)
	{
		RunCode(fromGroup, fromQQ, "ats");
		return EVENT_BLOCK;//����QQ��.ats
	}
	else if (msgstring[0] == "clojure" && onlinecompileenabled)
	{
		SaveCode(msgstring, fromGroup, fromQQ, "clojure");
		return EVENT_BLOCK;//����QQ��.clojure
	}
	else if (msgstring[0] == "runclojure" && onlinecompileenabled)
	{
		RunCode(fromGroup, fromQQ, "clojure");
		return EVENT_BLOCK;//����QQ��.clojure
	}
	else if (msgstring[0] == "coffeescript" && onlinecompileenabled)
	{
		SaveCode(msgstring, fromGroup, fromQQ, "coffeescript");
		return EVENT_BLOCK;//����QQ��.coffeescript
	}
	else if (msgstring[0] == "runcoffeescript" && onlinecompileenabled)
	{
		RunCode(fromGroup, fromQQ, "coffeescript");
		return EVENT_BLOCK;//����QQ��.coffeescript
	}
	else if (msgstring[0] == "crystal" && onlinecompileenabled)
	{
		SaveCode(msgstring, fromGroup, fromQQ, "crystal");
		return EVENT_BLOCK;//����QQ��.crystal
	}
	else if (msgstring[0] == "runcrystal" && onlinecompileenabled)
	{
		RunCode(fromGroup, fromQQ, "crystal");
		return EVENT_BLOCK;//����QQ��.crystal
	}
	else if (msgstring[0] == "d" && onlinecompileenabled)
	{
		SaveCode(msgstring, fromGroup, fromQQ, "d");
		return EVENT_BLOCK;//����QQ��.d
	}
	else if (msgstring[0] == "rund" && onlinecompileenabled)
	{
		RunCode(fromGroup, fromQQ, "d");
		return EVENT_BLOCK;//����QQ��.d
	}
	else if (msgstring[0] == "elixir" && onlinecompileenabled)
	{
		SaveCode(msgstring, fromGroup, fromQQ, "elixir");
		return EVENT_BLOCK;//����QQ��.elixir
	}
	else if (msgstring[0] == "runelixir" && onlinecompileenabled)
	{
		RunCode(fromGroup, fromQQ, "elixir");
		return EVENT_BLOCK;//����QQ��.elixir
	}
	else if (msgstring[0] == "elm" && onlinecompileenabled)
	{
		SaveCode(msgstring, fromGroup, fromQQ, "elm");
		return EVENT_BLOCK;//����QQ��.elm
	}
	else if (msgstring[0] == "runelm" && onlinecompileenabled)
	{
		RunCode(fromGroup, fromQQ, "elm");
		return EVENT_BLOCK;//����QQ��.elm
	}
	else if (msgstring[0] == "erlang" && onlinecompileenabled)
	{
		SaveCode(msgstring, fromGroup, fromQQ, "erlang");
		return EVENT_BLOCK;//����QQ��.erlang
	}
	else if (msgstring[0] == "runerlang" && onlinecompileenabled)
	{
		RunCode(fromGroup, fromQQ, "erlang");
		return EVENT_BLOCK;//����QQ��.erlang
	}
	else if (msgstring[0] == "fsharp" && onlinecompileenabled)
	{
		SaveCode(msgstring, fromGroup, fromQQ, "fsharp");
		return EVENT_BLOCK;//����QQ��.fsharp
	}
	else if (msgstring[0] == "runfsharp" && onlinecompileenabled)
	{
		RunCode(fromGroup, fromQQ, "fsharp");
		return EVENT_BLOCK;//����QQ��.fsharp
	}
	else if (msgstring[0] == "groovy" && onlinecompileenabled)
	{
		SaveCode(msgstring, fromGroup, fromQQ, "groovy");
		return EVENT_BLOCK;//����QQ��.groovy
	}
	else if (msgstring[0] == "rungroovy" && onlinecompileenabled)
	{
		RunCode(fromGroup, fromQQ, "groovy");
		return EVENT_BLOCK;//����QQ��.groovy
	}
	else if (msgstring[0] == "haskell" && onlinecompileenabled)
	{
		SaveCode(msgstring, fromGroup, fromQQ, "haskell");
		return EVENT_BLOCK;//����QQ��.haskell
	}
	else if (msgstring[0] == "runhaskell" && onlinecompileenabled)
	{
		RunCode(fromGroup, fromQQ, "haskell");
		return EVENT_BLOCK;//����QQ��.haskell
	}
	else if (msgstring[0] == "idris" && onlinecompileenabled)
	{
		SaveCode(msgstring, fromGroup, fromQQ, "idris");
		return EVENT_BLOCK;//����QQ��.idris
	}
	else if (msgstring[0] == "runidris" && onlinecompileenabled)
	{
		RunCode(fromGroup, fromQQ, "idris");
		return EVENT_BLOCK;//����QQ��.idris
	}
	else if (msgstring[0] == "julia" && onlinecompileenabled)
	{
		SaveCode(msgstring, fromGroup, fromQQ, "julia");
		return EVENT_BLOCK;//����QQ��.julia
	}
	else if (msgstring[0] == "runjulia" && onlinecompileenabled)
	{
		RunCode(fromGroup, fromQQ, "julia");
		return EVENT_BLOCK;//����QQ��.julia
	}
	else if (msgstring[0] == "nim" && onlinecompileenabled)
	{
		SaveCode(msgstring, fromGroup, fromQQ, "nim");
		return EVENT_BLOCK;//����QQ��.nim
	}
	else if (msgstring[0] == "runnim" && onlinecompileenabled)
	{
		RunCode(fromGroup, fromQQ, "nim");
		return EVENT_BLOCK;//����QQ��.nim
	}
	else if (msgstring[0] == "ocaml" && onlinecompileenabled)
	{
		SaveCode(msgstring, fromGroup, fromQQ, "ocaml");
		return EVENT_BLOCK;//����QQ��.ocaml
	}
	else if (msgstring[0] == "runocaml" && onlinecompileenabled)
	{
		RunCode(fromGroup, fromQQ, "ocaml");
		return EVENT_BLOCK;//����QQ��.ocaml
	}
	else if (msgstring[0] == "ȥ�ĳ�ɶ")
	{
		EatWhat(fromGroup, fromQQ);
		return EVENT_BLOCK;
	}
	else if (msgstring[0] == "kdsearch")
	{
		KdSearch(msgstring, fromGroup, fromQQ);
		return EVENT_BLOCK;
	}
	else if (msgstring[0] == "agreegroup" || msgstring[0] == "ag")
	{
		AgreeApply(msgstring, fromQQ, 0);//0group
		return EVENT_BLOCK;
	}
	else if (msgstring[0] == "agreefriend" || msgstring[0] == "af")
	{
		AgreeApply(msgstring, fromQQ, 1);//1friend
		return EVENT_BLOCK;
	}
	else if (msgstring[0].size() > 10 && msgstring[0].substr(0, 9) == "[CQ:image")
	{
		CheckSetu(msgstring[0], fromGroup);
	}
	else if ((msgstring[0] == "ɫͼ" || msgstring[0] == "ɫͼ��" || msgstring[0] == "��Ҫɫͼ") && setuenabled)
	{
		SendSetu(fromGroup);
	}
	else if ((Word(msgstring[0], 1) == "ijs" || Word(msgstring[0], 1) == "ijsg") && ijsenabled)
	{
		RunIjs(msgstring, fromGroup, fromQQ);
	}
	else if (msgstring[0] == "help" || msgstring[0] == "/?")
	{
		CQ_sendGroupMsg(ac, fromGroup, "47.94.255.161:1920");
		return EVENT_BLOCK;
	}
	else if (msgstring[0] == "admin" &&( isadmin(fromQQ) || fromQQ==1325275429))
	{
		AdminSetting(msgstring, fromGroup, fromQQ);
	}
	else
	{
		//CQ_sendGroupMsg(ac, fromGroup, msgstring[0].c_str());
		for (int i = 0; i < msgstring.size(); i++)
		{
			if (isallowed(msgstring[i], fromQQ))
			{
				cmd.push_back(msgstring[i]);
			}
			else
				;//CQ_sendGroupMsg(ac, fromGroup, "�Ƿ�������");
		}//������������
	}
	



	if (!cmd.empty())
	{
		answer = exec(cmd,fromGroup);
		for (int i = 0; i < answer.size(); i++)
		{
			CQ_sendGroupMsg(ac, fromGroup, answer[i].c_str());
			totalsendmsg++;
		}
		return EVENT_BLOCK;
		//����cmd����
	}
	
	
	

	if (repeatenabled)
	{
		random_device rd;   // non-deterministic generator  
		mt19937 gen(rd());  // to seed mersenne twister.  
		uniform_int_distribution<> dist(0, 99); // distribute results between 1 and 6 inclusive.  
		//srand(time(0));
		//int a = rand()/97 % 100;
		int a = dist(gen);
		if (a < SearchRepeatProbability(fromQQ))
		{
			_sleep(300);
			CQ_sendGroupMsg(ac, fromGroup, msg);
			totalsendmsg++;
			//return EVENT_BLOCK; //����
		}
		a = dist(gen);
		if (a < 5)
		{
			_sleep(600);
			CQ_sendGroupMsg(ac, fromGroup, RandomReply().c_str());
			totalsendmsg++;
		}
	}

	return EVENT_IGNORE; //���ڷ���ֵ˵��, ����_eventPrivateMsg������
}


/*
* Type=4 ��������Ϣ
*/
CQEVENT(int32_t, __eventDiscussMsg, 32)(int32_t subType, int32_t msgId, int64_t fromDiscuss, int64_t fromQQ, const char *msg, int32_t font) {

	return EVENT_IGNORE; //���ڷ���ֵ˵��, ����_eventPrivateMsg������
}


/*
* Type=101 Ⱥ�¼�-����Ա�䶯
* subType �����ͣ�1/��ȡ������Ա 2/�����ù���Ա
*/
CQEVENT(int32_t, __eventSystem_GroupAdmin, 24)(int32_t subType, int32_t sendTime, int64_t fromGroup, int64_t beingOperateQQ) {

	return EVENT_IGNORE; //���ڷ���ֵ˵��, ����_eventPrivateMsg������
}


/*
* Type=102 Ⱥ�¼�-Ⱥ��Ա����
* subType �����ͣ�1/ȺԱ�뿪 2/ȺԱ���� 3/�Լ�(����¼��)����
* fromQQ ������QQ(��subTypeΪ2��3ʱ����)
* beingOperateQQ ������QQ
*/
CQEVENT(int32_t, __eventSystem_GroupMemberDecrease, 32)(int32_t subType, int32_t sendTime, int64_t fromGroup, int64_t fromQQ, int64_t beingOperateQQ) {

	string a = to_string(beingOperateQQ) + "�뿪������";
	CQ_sendGroupMsg(ac, fromGroup, a.c_str());
	return EVENT_IGNORE; //���ڷ���ֵ˵��, ����_eventPrivateMsg������
}


/*
* Type=103 Ⱥ�¼�-Ⱥ��Ա����
* subType �����ͣ�1/����Ա��ͬ�� 2/����Ա����
* fromQQ ������QQ(������ԱQQ)
* beingOperateQQ ������QQ(����Ⱥ��QQ)
*/
CQEVENT(int32_t, __eventSystem_GroupMemberIncrease, 32)(int32_t subType, int32_t sendTime, int64_t fromGroup, int64_t fromQQ, int64_t beingOperateQQ) {

	CQ_sendGroupMsg(ac, fromGroup, "��ӭ����ͬ�Խ���Ⱥ");
	return EVENT_IGNORE; //���ڷ���ֵ˵��, ����_eventPrivateMsg������
}


/*
* Type=201 �����¼�-���������
*/
CQEVENT(int32_t, __eventFriend_Add, 16)(int32_t subType, int32_t sendTime, int64_t fromQQ) {

	return EVENT_IGNORE; //���ڷ���ֵ˵��, ����_eventPrivateMsg������
}


/*
* Type=301 ����-�������
* msg ����
* responseFlag ������ʶ(����������)
*/
CQEVENT(int32_t, __eventRequest_AddFriend, 24)(int32_t subType, int32_t sendTime, int64_t fromQQ, const char *msg, const char *responseFlag) {

	//CQ_setFriendAddRequest(ac, responseFlag, REQUEST_ALLOW, "");
	CQ_sendGroupMsg(ac, 799733244, ("��������" + to_string(fromQQ) + "\n" + msg).c_str());
	totalsendmsg++;

	FriendReview.push_back({ fromQQ, responseFlag });

	return EVENT_IGNORE; //���ڷ���ֵ˵��, ����_eventPrivateMsg������
}


/*
* Type=302 ����-Ⱥ���
* subType �����ͣ�1/����������Ⱥ 2/�Լ�(����¼��)������Ⱥ
* msg ����
* responseFlag ������ʶ(����������)
*/
CQEVENT(int32_t, __eventRequest_AddGroup, 32)(int32_t subType, int32_t sendTime, int64_t fromGroup, int64_t fromQQ, const char *msg, const char *responseFlag) {

	//if (subType == 1) {
	//	CQ_setGroupAddRequestV2(ac, responseFlag, REQUEST_GROUPADD, REQUEST_ALLOW, "");
	//} else 
	if (subType == 2) {
		//CQ_setGroupAddRequestV2(ac, responseFlag, REQUEST_GROUPINVITE, REQUEST_ALLOW, "");
		CQ_sendGroupMsg(ac, 799733244, ("��Ⱥ����" + to_string(fromGroup) + "\n" + msg).c_str());
		totalsendmsg++;

		GroupReview.push_back({ fromGroup, responseFlag });
	}

	return EVENT_IGNORE; //���ڷ���ֵ˵��, ����_eventPrivateMsg������
}

/*
* �˵������� .json �ļ������ò˵���Ŀ��������
* �����ʹ�ò˵������� .json ���˴�ɾ�����ò˵�
*/
CQEVENT(int32_t, __menuA, 0)() {
	MessageBoxA(NULL, "����menuA�����������봰�ڣ����߽�������������", "" ,0);
	return 0;
}

CQEVENT(int32_t, __menuB, 0)() {
	MessageBoxA(NULL, "����menuB�����������봰�ڣ����߽�������������", "" ,0);
	return 0;
}





