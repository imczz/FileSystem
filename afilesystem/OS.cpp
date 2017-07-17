#include "OS.h"

#include "BitOperate.h"
#include "windows.h"

//���캯��
OS::OS()
{
	FileSystem * fs = new FileSystem("D:\\disk.txt");
	fsList.push_back(fs);
}

OS::~OS()
{
	for (vector<FileSystem *>::iterator iter = fsList.begin(); iter != fsList.end(); iter++)
	{
		free(*iter);
	}
}

int OS::login(UN id, string key) {

	int result = 0;
	switch (id)

	{

	case user0:

		if (key.compare("000000") == 0) user = 0;

		cout << "����Ա��¼�ɹ�" << endl;
		result = 200;

		break;



	case user1:

		if (key.compare("111111") == 0) user = 1;

		cout << "�û�1��¼�ɹ�" << endl;
		result = 200;

		break;



	case user2:

		if (key.compare("222222") == 0) user = 2;

		cout << "�û�2��¼�ɹ�" << endl;
		result = 200;

		break;



	case user3:

		if (key.compare("333333") == 0) user = 3;

		cout << "�û�3��¼�ɹ�" << endl;
		result = 200;

		break;



	case user4:

		if (key.compare("444444") == 0) user = 4;

		cout << "�û�4��¼�ɹ�" << endl;
		result = 200;

		break;



	case user5:

		if (key.compare("555555") == 0) user = 5;

		cout << "�û�5��¼�ɹ�" << endl;
		result = 200;

		break;



	case user6:

		if (key.compare("666666") == 0) user = 6;

		cout << "�û�6��¼�ɹ�" << endl;
		result = 200;

		break;



	case user7:

		if (key.compare("777777") == 0) user = 7;

		cout << "�û�7��¼�ɹ�" << endl;
		result = 200;

		break;



	case user8:

		if (key.compare("888888") == 0) user = 8;

		cout << "�û�8��¼�ɹ�" << endl;
		result = 200;

		break;

	case unknown:

		cout << "��¼ʧ��" << endl;

		break;
	default:

		cout << "��¼ʧ��" << endl;

		break;

	}
	return result;
}



void OS::logout() {

	user = -1;

	cout << "���˳�" << endl;

}



void OS::open(string fileName) {



}



void OS::close(string fileName) {



}



void OS::create(string fileName) {



}



void OS::read(string fileName) {



}



void OS::write(string fileName) {



}



void OS::mkdir() {



}



void OS::chdir() {



}



void OS::dir() {



}



void OS::format() {



}

void OS::start()
{
	string username;
	string password;
	UN user;
	cout << "�������û���:" << endl;
	cin >> username;
	cout << "����������:" << endl;
	cin >> password;
	if (username == "root")
	{
		user = user0;
	}
	else
	{
		if (username.size() == 5 && username.substr(0, 4) == "user")
		{
			switch (username[4])
			{
			case '0':
				user = user0;
				break;
			case '1':
				user = user1;
				break;
			case '2':
				user = user2;
				break;
			case '3':
				user = user3;
				break;
			case '4':
				user = user4;
				break;
			case '5':
				user = user5;
				break;
			case '6':
				user = user6;
				break;
			case '7':
				user = user7;
				break;
			case '8':
				user = user8;
				break;
			}
		}
		else
		{
			user = unknown;
		}
	}
	if (login(user, password) != 200)
	{
		system("pause");
		exit(0);
	}

	//fsList[0]->Initialize("D:\\disk.txt");
	if (!fsList[0]->IsInitalized)
	{
		cout << "��ʼ���ļ�ϵͳʧ�ܣ���������˳�����" << endl;
		system("pause");
	}
	if (fsList[0]->superBlock.dataBlockNumber != 512)
	{
		cout << "ϵͳ��һ�����У��밴�������ʼ��ʽ�������ļ�ϵͳVFS" << endl;
		system("pause");
		fsList[0]->format();
	}

	SystemOpenFileListItem sofli("", 0);
	openList.push_back(sofli);
	help();
	while (menu0());
	logout();
}

int OS::menu0()
{
	string operate;
	string args;
	int space = 0;
	int result;
	for (int i = 0; i < openList.size(); i++)
	{
		cout << openList[i].name << "/";
	}
	cout << ">";
	cin >> operate;
	if (operate == "exit") return 0;
	else if (operate == "ls") ls();
	else if (operate == "help") help();
	else if (operate == "format")
	{
		cout << "ȷ��Ҫ��ʽ���ļ�ϵͳ��[Y/N]" << endl;
		cin >> args;
		if (args == "Y" || args == "y")
		{
			fsList[0]->format();
			cout << "��ʽ�����" << endl;
			openList.clear();
			openList.push_back(SystemOpenFileListItem("", 0));
		}
	}
	else if (operate == "mkdir")
	{
		cin >> args;
		result = fsList[0]->mkdir(openList[openList.size() - 1].id, user, '0', args);
		if (result == 1)
		{
			cout << "Ŀ¼" + args + "�����ɹ�" << endl;
		}
		else if (result == -10)
		{
			cout << "����ͬ���ļ���Ŀ¼" << endl;
		}
	}
	else if (operate == "create")
	{
		cin >> args;
		result = fsList[0]->CreateAFile(openList[openList.size() - 1].id, user, '0', args);
		if (result == 1)
		{
			cout << "�ļ�" + args + "�����ɹ�" << endl;
		}
		else if (result == -10)
		{
			cout << "�ļ����ظ�" << endl;
		}
	}
	else if (operate == "delete")
	{
		cin >> args;
		result = fsList[0]->DeleteAFile(openList[openList.size() - 1].id, user, '0', args);
		if (result == 1)
		{
			cout << "�ļ�" + args + "�Ѿ��ɹ�ɾ��" << endl;
		}
		else if (result == -10)
		{
			cout << "�ļ����ظ�" << endl;
		}
	}
	else if (operate == "chdir")
	{
		cin >> args;
		if (args == ".." && openList.size() > 1) openList.pop_back();				//�����ϼ��˵�
		else
		{
			result = fsList[0]->namei(openList[openList.size() - 1].id, args);
			
			if (result > 0)
			{
				if (fsList[0]->inodes[result].fileType == 1)
				{
					SystemOpenFileListItem sofli(args, result);
					openList.push_back(sofli);
					return 1;
				}
			}
			cout << "Ŀ¼������" << endl;
		}
	}
	else if (operate == "read")
	{
		cin >> args;
		result = fsList[0]->namei(openList[openList.size() - 1].id, args);
		char fileBuffer[5120];
		if (result > 0)
		{
			if (fsList[0]->inodes[result].fileType == 0)
			{
				int length;
				SystemOpenFileListItem sofli(args, result);
				openList.push_back(sofli);
				cout << args + ":" << endl;
				fsList[0]->read(result, user, '0', length, fileBuffer);
				cout << fileBuffer << endl;
				openList.pop_back();
				return 1;
			}
			cout << "�ļ�������" << endl;
		}
	}
	else if (operate == "write")
	{
		cin >> args;
		result = fsList[0]->namei(openList[openList.size() - 1].id, args);
		char fileBuffer[5120];
		if (result > 0)
		{
			if (fsList[0]->inodes[result].fileType == 0)
			{
				int length;
				SystemOpenFileListItem sofli(args, result);
				openList.push_back(sofli);
				cout << args + ":" << endl;
				cin >> fileBuffer;
				length = strlen(fileBuffer);
				fsList[0]->write(result, user, '0', length, fileBuffer);
				openList.pop_back();
				return 1;
			}
			cout << "�ļ�������" << endl;
		}
	}
	else help();
	return 1;
}

void OS::outCurrentInode()
{
	
}

void OS::ls()
{
	Inode thisInode = fsList[0]->inodes[openList[openList.size() - 1].id];
	int folderNumber = 0, folderItemNumber = 0;
	char blockBuffer[512];
	char foderItem[16];
	FolderItem aFolderItem;

	if (thisInode.fileType == 1)
	{
		if (thisInode.state == 0 || thisInode.fileSize == 0)
		{
			cout << "��Ŀ¼" << endl;
		}
		else
		{
			folderNumber = thisInode.fileSize / 16;
			for (int i = 0; i < thisInode.blockNumber; i++)
			{
				fsList[0]->ReadABlock(34 + thisInode.blocksIndex[i], blockBuffer);
				if (folderNumber >= 32) folderItemNumber = 32;
				else folderItemNumber = folderNumber;
				for ( int j = 0; j < folderItemNumber; j++)
				{
					BitOperate::bitCopy(foderItem, 0, blockBuffer, j * 128, 128);
					aFolderItem.LoadFromBuffer(foderItem);
					cout << aFolderItem.name << "[" << ((fsList[0]->inodes[aFolderItem.inode].fileType == 0) ? "�ļ�" : "�ļ���") << "]" << "\t";
				}
			}
			cout << endl;
		}
	}
}

void OS::help()
{
	cout << "================= ���� help ====================" << endl;
	cout << "help ���� ����" << endl;
	cout << "ls ���� �鿴��ǰĿ¼" << endl;
	cout << "mkdir [folder name] ���� �����ļ���" << endl;
	cout << "create [file name] ���� �����ļ�" << endl;
	cout << "delete [file name] ���� ɾ���ļ�" << endl;
	cout << "chdir [folder name] ���� Ŀ¼��ת" << endl;
	cout << "read [file name] ���� ��ȡ�ļ�" << endl;
	cout << "write [file name] ���� д���ļ�" << endl;
	cout << "format ���� ��ʽ���ļ�ϵͳ" << endl;
	//cout << "close [file name] ���� �ر��ļ�" << endl;
	cout << "exit ���� �˳�ϵͳ" << endl;
	cout << "================================================" << endl << endl;
}

SystemOpenFileListItem::SystemOpenFileListItem()
{
	id = -1;
	name = "";
}

SystemOpenFileListItem::SystemOpenFileListItem(string name, short id)
{
	this->name = name;
	this->id = id;
}

SystemOpenFileListItem::SystemOpenFileListItem(const SystemOpenFileListItem & sofli)
{
	name = sofli.name;
	id = sofli.id;
}
