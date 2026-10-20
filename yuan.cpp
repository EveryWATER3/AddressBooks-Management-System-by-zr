#include<iostream>
#include<string>
#include <limits>
using namespace std;
#define MAX 1000

struct Person//个人信息结构体
{
	string m_Name;
	int m_Sex;
	int m_Age;
	string m_Phone;
	string m_Addr;
};

struct Addressbooks//通讯录结构体数组+人数
{
	Person personArray[MAX];

	int m_Size;//通讯录人数
};
void ShowMenu()
{
	cout << "*******************" << endl;
	cout << "***1、添加联系人***" << endl;
	cout << "***2、显示联系人***" << endl;
	cout << "***3、删除联系人***" << endl;
	cout << "***4、查找联系人***" << endl;
	cout << "***5、修改联系人***" << endl;
	cout << "***6、清空联系人***" << endl;
	cout << "***0、退出通讯录***" << endl;
	cout << "*******************" << endl;
}

void addPerson(Addressbooks* abs)//添加联系人
{//需要具备判满，判错功能
	if (abs->m_Size == MAX)
	{
		cout << "当前通讯录已满。" << endl;
		return;
	} else
	{
		//名字
		string name;
		cout << "请输入姓名：" << endl;
		cin >> name;
		abs->personArray[abs->m_Size].m_Name = name;

		//性别
		cout << "请输入性别；" 
			<< "1--男，2--女" << endl;
		
		int sex = 0;
		while (true)
		{
			cin >> sex;
			if (sex == 1 || sex == 2)
			{
				abs->personArray[abs->m_Size].m_Sex = sex;
				break;
			}
			else
			{
				cout << "输入有误，请重新输入！" << endl;
			}
		}

		//年龄
		cout << "请输入年龄；" << endl;

		int age = 0;
		
		while (true)
		{
			cin >> age;
			if (cin.fail())
			{
				cin.clear();            // 清除错误状态
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 丢弃非法输入
				cout << "输入无效，请输入数字！" << endl;
				continue;
			}
			if (age >= 0 && age <= 100)
			{
				abs->personArray[abs->m_Size].m_Age = age;
				break;
			}else if(age > 100)
			{
				cout << "请确认新增联系人的年龄？" 
					<<"1--我确认ta超过100岁"
					<<"2--重新输入"<<endl;
				int temp =0;
				cin >> temp;
				if (temp == 1)
				{
					abs->personArray[abs->m_Size].m_Age = age;
					break;
				}
				else
				{
					cout << "请重新输入!" << endl;
				}
			}
			else
			{
				cout << "年龄不能为负数，请重新输入！" << endl;
			}
		}

		//电话
		cout << "请输入电话：";
		string phone;
		cin >> phone;
		abs->personArray[abs->m_Size].m_Phone = phone;

		//住址
		cout << "请输入住址：" << endl;
		string address;
		cin >> address;
		abs->personArray[abs->m_Size].m_Addr = address;

		//重要：更新通讯录人数
		abs->m_Size++;

		cout << "添加成功..." << endl;

		system("pause");
		system("cls");
	}
}

void showPerson(Addressbooks* abs)//显示联系人
{
	if (abs->m_Size == 0)
	{
		cout << "当前记录为空" << endl;
	}
	else
	{
		for (int i = 0; i < abs->m_Size; i++)
		{
			cout << "姓名：" << abs->personArray[i].m_Name << "\t";
			cout << "性别：" << ( abs->personArray[i].m_Sex == 1 ? "男":"女" ) << "\t";
			cout << "年龄：" << abs->personArray[i].m_Age << "\t";
			cout << "电话：" << abs->personArray[i].m_Phone << "\t";
			cout << "住址：" << abs->personArray[i].m_Addr << endl;
		}
	}

	system("pause");
	system("cls");
}

int isExist(Addressbooks* abs,string name)//按名查找：检测是否存在联系人
{
	for(int i =0;i<abs->m_Size;i++)
	{
		if (abs->personArray[i].m_Name == name)
		{
			return i;
		}
	}
	return -1;
}

void deletePerson(Addressbooks* abs)//删除联系人
{
	cout << "请输入要删除的联系人姓名：" << endl;
	string name;
	cin >> name;

	int ret = isExist(abs, name);

	if (ret != -1)
	{
		for (int i = ret; i < abs->m_Size - 1; i++)
		{
			abs->personArray[i] = abs->personArray[i + 1];
		}
		abs->m_Size--;
	}
	else
	{
		cout << "查无此人" << endl;
	}
	system("pause");
	system("cls");
}

void findPerson(Addressbooks* abs)//查找联系人
{
	cout << "请输入要查找的联系人姓名：" << endl;
	string name;
	cin >> name;

	int ret = isExist(abs, name);

	if (ret != -1)
	{
		cout << "姓名：" << abs->personArray[ret].m_Name << "\t";
		cout << "性别：" << (abs->personArray[ret].m_Sex == 1 ? "男" : "女") << "\t";
		cout << "年龄：" << abs->personArray[ret].m_Age << "\t";
		cout << "电话：" << abs->personArray[ret].m_Phone << "\t";
		cout << "住址：" << abs->personArray[ret].m_Addr << endl;
	}
	else
	{
		cout << "查无此人" << endl; 
	}
	system("pause");
	system("cls");
}

void modifyPerson(Addressbooks* abs)//修改联系人
{
	cout << "请输入要修改的联系人姓名：" << endl;
	string name;
	cin >> name;

	int ret = isExist(abs, name);

	if (ret != -1)
	{

		//要实现多选功能，先用副本
		Person tempPerson = abs->personArray[ret];
		bool isFinished = false;//思路学习：是否结束修改并确认

		while (!isFinished)
		{
			//用bool数组记录用户要修改哪些项 (索引1-5对应姓名到住址)
			bool modifyFlags[6] = { false };
			bool selecting = true;

			//多选
			cout << "\n请选择要修改的选项（可多选，输入0结束选择）：" << endl;
			cout << "1--姓名 2--性别 3--年龄 4--电话 5--住址" << endl;

			while (selecting)
			{
				int choice = 0;
				cin >> choice;
				if (choice == 0)
				{
					selecting = false;
				}
				else if (choice >= 1 && choice <= 5)
				{
					modifyFlags[choice] = true;//标记该选项需要修改
					cout << "已选择修改项" << choice << "，可继续选择或输入0结束" << endl;
				}
				else
				{
					cout << "输入有误，请重新输入(1-5或0)：" << endl;
				}
			}

			if (modifyFlags[1]) {
				cout << "请重新输入姓名：" << endl;
				cin >> tempPerson.m_Name;
			}

			if (modifyFlags[2]) {
				int sex = 0;
				while (true) {
					cout << "请输入性别(1--男 2--女)：" << endl;
					cin >> sex;
					if (sex == 1 || sex == 2) { tempPerson.m_Sex = sex; break; }
					cout << "输入有误，请重新输入！" << endl;
				}
			}
			if (modifyFlags[3]) {
				cout << "请重新输入年龄：" << endl;
				int age = 0;
				while (true)
				{
					cin >> age;
					if (cin.fail())
					{
						cin.clear();            // 清除错误状态
						cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 丢弃非法输入
						cout << "输入无效，请输入数字！" << endl;
						continue;
					}//ai给的健壮性建议，9级
					if (age >= 0 && age <= 100)
					{
						tempPerson.m_Age = age;

						break;
					}
					else if (age > 100)
					{
						cout << "请确认联系人年龄是否大于100岁" 
							<<"1--确定 2--重新输入"<< endl;
						int temp;
						cin >> temp;
						if (temp == 1) 
						{
							tempPerson.m_Age = age;
							break;
						}
						else
						{
							continue;
						}
					}
					else if (age < 0)
					{
						cout << "年龄不能为负数！请重新输入！" << endl;
						continue;
					}
				}
			}

			if (modifyFlags[4]) {
				
				while (true)
				{	
					string temp;
					cout << "请重新输入电话：" << endl;
					cin >> tempPerson.m_Phone;
					cout << "请再次输入以保证准确无误：" << endl;
					cin >> temp;
					if (temp == tempPerson.m_Phone)
					{
						tempPerson.m_Phone = temp;
						break;
					}
					else
					{
						cout << "输入有误，请重新输入" << endl;
						continue;
					}
				}
			}

			if (modifyFlags[5]) {
				cout << "请重新输入住址：" << endl;
				cin >> tempPerson.m_Addr;
			}

			cout << "\n========修改后的信息========" << endl;
			cout << "姓名：" << tempPerson.m_Name << "\t";
			cout << "性别：" << (tempPerson.m_Sex == 1 ? "男" : "女") << "\t";
			cout << "年龄：" << tempPerson.m_Age << "\t";
			cout << "电话：" << tempPerson.m_Phone << "\t";
			cout << "住址：" << tempPerson.m_Addr << endl;
			cout << "============================" << endl;
			cout << "确认保存修改吗？ 1--确认  2--重新修改" << endl;

			int confirm = 0;
			cin >> confirm;
			if (confirm == 1)
			{
				abs->personArray[ret] = tempPerson;
				cout << "修改成功！" << endl;
				isFinished = true;
			}
			else
			{
				tempPerson = abs->personArray[ret];
				cout << "已取消，请重新选择。" << endl;
			}
		}
	}
	else
	{
		cout << "查无此人" << endl;
	}

	system("pause");
	system("cls");
}

void cleanPerson(Addressbooks* abs)//清空联系人
{
	abs->m_Size = 0;
	cout << "通讯录已清空" << endl;
	system("pause");
	system("cls");
}
int main()
{
	int select = 0;//使用者的选择

	Addressbooks abs;

	abs.m_Size = 0;

	while (true)
	{
		ShowMenu();
		cin >> select;

		switch (select)
		{
		case 1://1、添加联系人
			addPerson(&abs);
			break;
		case 2://2、显示联系人
			showPerson(&abs);
			break;
		case 3://3、删除联系人
			deletePerson(&abs);
			break;
		case 4://4、查找联系人
			findPerson(&abs);
			break;
		case 5://5、修改联系人
			modifyPerson(&abs);
			break;
		case 6://6、清空联系人
			cleanPerson(&abs);
			break;
		case 0://0、退出通讯录
			cout << "欢迎下次使用" << endl;
			system("pause");
			return 0;
		default:
			break;
		}
	}

	system("pause");
	return 0;
}