#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include"json.hpp"
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using json = nlohmann::json;  //简写一下

class PlayManager {
private:

	struct Task {                          /*用于用户自己添加事项*/
		string name;
		int ValueToAdd;
		string category;
		int ncategory;
	};

	vector<Task> intelligence;
	vector<Task> stamina;
	vector<Task> strength;

	struct PlayData {
		int strength = 10;
		int stamina = 10;
		int intelligence = 10;
	};

	PlayData IniData;

public:

	PlayData Dataload() {  //Playdata 用于传递回值
		PlayData data;
		std::ifstream file("D:\\LIFE RPG\\BETA I\\playdata.txt");  //本地开发，先存储在本地文件方便调试
		if (file.is_open()) {                      //在读取方面，需要判断文件是否存在
			file >> data.intelligence;
			file >> data.stamina;
			file >> data.strength;
		}
		IniData = data;
		return data;
	}


	void AddVal(int cat,int times,int choice) {   /*用于对数值进行操作*/
		int i = 0;
		if (choice < 0 || choice>stamina.size())
			return;

		if (cat == 1) {
			if (choice <= 0 || choice>intelligence.size())
				return;

			IniData.intelligence += intelligence[choice - 1].ValueToAdd * times;
		}

		if (cat == 2) {
			if (choice <= 0 || choice > stamina.size())
				return;
			IniData.stamina += stamina[choice - 1].ValueToAdd * times;
		}

		if (cat == 3) {
			if (choice <= 0 || choice > strength.size())
				return;
			IniData.strength += strength[choice - 1].ValueToAdd * times;
		}

		return ;
	}


	void CreateNewTask(string nameof,int val,int ncat,string cat) {    //创建新的任务

		Task newtask;
		newtask.name = nameof;
		newtask.category = cat;
		newtask.ValueToAdd = val;
		newtask.ncategory = ncat;

		switch (newtask.ncategory) {    //按照任务的类型分类
		case 1:
			intelligence.push_back(newtask);
			break;
		case 2:
			stamina.push_back(newtask);
			break;
		case 3:
			strength.push_back(newtask);
			break;
		default:
			cout << "错误的结果" << endl;
		}
	}


	void DataSave() { 
		std::ofstream file;
		file.open("D:\\LIFE RPG\\BETA I\\playdata.txt");
		PlayData Data;

		Data = IniData;

		file << Data.intelligence << "\n";
		file << Data.stamina << "\n";
		file << Data.strength << "\n";


		file.close();
	}


	void TaskSave() {
		json j = json::array();
		for (const auto& t : intelligence) {
			j.push_back({
				{"name",t.name},
				{"ValueToAdd",t.ValueToAdd},
				{"category",t.category},
				{"ncategory",t.ncategory}
				});
		}
		for (const auto& t : stamina) {
			j.push_back({
				{"name",t.name},
				{"ValueToAdd",t.ValueToAdd},
				{"category",t.category},
				{"ncategory",t.ncategory}
				});
		}
		for (const auto& t : strength) {
			j.push_back({
				{"name",t.name},
				{"ValueToAdd",t.ValueToAdd},
				{"category",t.category},
				{"ncategory",t.ncategory}
				});
		}
		std::ofstream file("D:\\LIFE RPG\\BETA I\\tasks.json");
		file << j.dump(4);        //以字符串输出到文件
	}


	void DownloadTask() {
		std::ifstream file("D:\\LIFE RPG\\BETA I\\tasks.json");
		if (!file.is_open()) {
			std::cerr << "警告：未找到tasks.json文件，将创建新的任务列表" << std::endl;
			return;
		}
		json j;
		file >> j;
		for (const auto& jsonTask : j) {
			Task comtemporary;
			comtemporary.category = jsonTask["category"];
			comtemporary.ncategory = jsonTask["ncategory"];
			comtemporary.name = jsonTask["name"];
			comtemporary.ValueToAdd = jsonTask["ValueToAdd"];
			switch (comtemporary.ncategory) {    //按照任务的类型分类
			case 1:
				intelligence.push_back(comtemporary);
				break;
			case 2:
				stamina.push_back(comtemporary);
				break;
			case 3:
				strength.push_back(comtemporary);
				break;
			default:
				cout << "错误的结果" << endl;
			}
		}

	}


	int IntelligenceGet() {
		return IniData.intelligence;
	}


	int StaminaGet() {
		return IniData.stamina;
	}


	int StrengthGet() {
		return IniData.strength;
	}


	void IntelligenceTaskGet() {
		int i = 1;

		if (intelligence.empty())
			cout << "没有任务可用" << endl;

		for (auto x : intelligence) {
			cout << i << "  " << x.name << "  " << x.ValueToAdd << endl;
			i++;
		}
		return;
	}


	void StaminaTaskGet() {
		if (stamina.empty())
			cout << "没有任务可用" << endl;

		int i = 1;

		for (auto x : stamina) {
			cout << i <<" " << x.name << " " << x.ValueToAdd << endl;
			i++;
		}
		return;
	}


	void StrengthTaskGet() {
		if (strength.empty())
			cout << "没有任务可用" << endl;

		int i = 1;

		for (auto x : strength) {
			cout <<i<<" " << x.name << " " << x.ValueToAdd << endl;
			i++;
		}
		return;
	}

};



int main() {
	int a,timejudge=0;
	PlayManager mymanager;
	mymanager.DownloadTask();   //加载任务数据

	mymanager.Dataload();

	cout << "您当前数值为" << endl;
	cout << mymanager.IntelligenceGet() <<"  " << mymanager.StaminaGet() <<"  " << mymanager.StrengthGet() << endl;
	cout << endl;

	while (1) {
		timejudge++;
		cout << "请输入你的操作" << endl;
		cout << "0:结束" << endl;
		cout << "1:进行智力训练" << endl;
		cout << "2:进行体力训练" << endl;
		cout << "3:进行力量训练" << endl;
		cout << "4:加入新任务" << endl;
		cout << "5:查看当前数值" << endl;
		cin >> a;
		cout << endl;
		if (a == 0)
			if (timejudge == 1)
				return 0;
			else break;
		int choice, times;
		switch (a) {       /*switch语句1-3都是增加数值的*/


		case 1:
			cout << "请选择你要进行的任务" << endl;
			mymanager.IntelligenceTaskGet();

			cin >> choice ;
			cout << "  ";
			cin >> times;
			cout << endl;

			mymanager.AddVal(1, times, choice);
			break;


		case 2:
			cout << "请选择你要进行的任务" << endl;
			mymanager.StaminaTaskGet();

			cin >> choice;
			cout << "  ";
			cin >> times;
			cout << endl;

			mymanager.AddVal(2, times, choice);

			break;
			


		case 3:
			cout << "请选择你要进行的任务" << endl;
			mymanager.StrengthTaskGet();

			
			cin >> choice;
			cout << "  ";
			cin >> times;
			cout << endl;

			mymanager.AddVal(3, times, choice);

			break;


		case 4: {

			string name, cat;
			int val, ncat;
			cout << "请分别输入任务名字，能力增长，类别，类别代号" << endl;
			cin >> name >> val >> cat >> ncat;

			mymanager.CreateNewTask(name, val, ncat, cat);

			break;
		}
		case 5:
			cout << "您当前数值为" << endl;
			cout << mymanager.IntelligenceGet() << "  " << mymanager.StaminaGet() << "  " << mymanager.StrengthGet() << endl;
			cout << endl;
			break;

		default:
			cout << "错误操作" << endl;
			break;
		}

	}
	mymanager.DataSave();
	mymanager.TaskSave();
	return 0;
}
