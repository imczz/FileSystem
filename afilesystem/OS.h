#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "FileSystem.h"

using namespace std;

const enum UN { user0, user1, user2, user3, user4, user5, user6, user7, user8, unknown };

struct SystemOpenFileListItem
{
	string name;
	short id;

	SystemOpenFileListItem();

	SystemOpenFileListItem(string name, short id);

	SystemOpenFileListItem(const SystemOpenFileListItem & sofli);
};

class OS
{
public:

	vector< FileSystem * > fsList;

	vector< SystemOpenFileListItem > openList;

	//���캯��
	OS();


	//��������
	~OS();

	/* -1���޵�½

	0������Ա

	1��2��3��4��5��6��7��8���û�1-8

	*/

	int user = -1;





	//����

	int login(UN id, string key);



	//�ǳ�

	void logout();



	//���ļ�

	void open(string fileName);



	//�ر��ļ�

	void close(string fileName);



	//�����ļ�

	void create(string fileName);



	//���ļ�

	void read(string fileName);



	//д�ļ�

	void write(string fileName);


	//����Ŀ¼

	void mkdir();



	//�ı䵱ǰĿ¼

	void chdir();


	//�г��ļ�Ŀ¼

	void dir();


	//��ʽ��

	void format();


	//terminal
	void start();

	//���˵�
	int menu0();

	void outCurrentInode();

	void ls();

	//����
	void help();

};

