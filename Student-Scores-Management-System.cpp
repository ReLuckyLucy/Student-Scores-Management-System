#include <iostream>//C++输入输出流标准库
#include <fstream>//C++文件流标准库
#include <iomanip>//C++输入输出操纵标准库
#include <string>//C++String类标准库

//以下三个头文件用于创建弹出式文件选择窗体
#include <windows.h>//Windows图形设备接口函数
#include <Commdlg.h>
#include <cstdio>//C++标准输入输出库

using namespace std;

///C++标准：C++11
///Windows SDK 版本：10.0.17763.0
///平台工具集：Visual Studio 2019 (v142)

#pragma region 全局变量区域
///
///全局变量区域
///

int stu_num = 0;//学生实际人数
int course_num = 0;//课程实际门数
int course_scores_sum[6] = { 0 };//课程总分
float course_scores_average[6] = { 0 };//课程平均分
int t = 0;//全局条件执行参数，用于t=1时退出while循环

//定义结构体类型“学生成绩”
struct student_scores {
	int stu_id = 0;//学生学号
	string stu_name = "";//学生姓名
	int stu_score[6] = { 0 };//各门课程的成绩（课程最大不超过6门）
	int stu_sum = 0;//学生的总分
	float stu_average = 0;//学生的平均分
	int stu_rank = 0;//学生成绩的总排名
};

#pragma endregion


#pragma region 全局函数区域
///
///全局函数区域
///

//学生成绩录入后加载事件
void load_student_scores_sum_and_average(student_scores stu[], int n);
void load_score_list(student_scores stu[], int n);
void score_loading(student_scores stu[])//学生成绩一旦录入完毕，立刻执行总分、平均分、排名的计算
{
	load_student_scores_sum_and_average(stu, stu_num);
	load_score_list(stu, stu_num);
}

//学生成绩标题栏打印
void score_title()
{
	cout << "ID" << "\t\t" << "Name" << "\t";
	for (int i = 0; i < course_num; i++)
		cout << "Course" << i + 1 << "\t";
	cout << "Sum" << "\t" << "Average" << "\t" << "Rank" << endl;
}

//学生成绩输出（以成绩条的方式输出）
void score_bar(student_scores stu[], int a)//a为学生序号
{
	cout << stu[a].stu_id << "\t" << stu[a].stu_name << "\t";
	for (int i = 0; i < course_num; i++)
		cout << stu[a].stu_score[i] << "\t";
	cout << stu[a].stu_sum << "\t" << setiosflags(ios::fixed) << setprecision(2) << stu[a].stu_average << "\t";
	cout << stu[a].stu_rank << endl;
}

#pragma endregion


#pragma region 基础功能
///
///基础功能
///

//菜单1 - 录入每个学生的学号、姓名和各科考试成绩
void student_scores_input(student_scores stu[], int n)//n为学生实际人数
{
	cout << "Input course number(m<=6):" << endl;
	t = 0;
	while (t == 0)
	{
		if (cin >> course_num)
			t = 1;
		else
		{
			cout << "Input error!" << endl;
			cin.clear(); //将cin重新标记为正确，以达到重新输入的目的
			while (cin.get() != '\n')	 //清空之前cin缓冲区的数据
				continue;
		}
	}

	cout << "Input student's ID, name and score:" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> stu[i].stu_id >> stu[i].stu_name;
		for (int j = 0; j < course_num; j++)
		{
			cin >> stu[i].stu_score[j];
		}
	}
}

//菜单2 - 计算每门课程的总分和平均分
void course_scores_sum_and_average(student_scores stu[], int n)//n为学生实际人数
{
	//计算部分
	for (int i = 0; i < course_num; i++)//逐个计算每门课程的平均分和总分
	{
		for (int k = 0; k < n; k++)//累加每个学生对应课程的分数
		{
			course_scores_sum[i] = course_scores_sum[i] + stu[k].stu_score[i];
		}
		course_scores_average[i] = float(course_scores_sum[i]) / n;
	}
	//输出部分
	for (int i = 0; i < course_num; i++)
	{
		cout << "course" << i + 1 << ": sum=" << course_scores_sum[i] << setiosflags(ios::fixed) << setprecision(2) << ", aver=" << course_scores_average[i] << endl;
	}
}

//菜单3 - 计算每个学生的总分和平均分（成绩录入后立刻完成计算部分）
void load_student_scores_sum_and_average(student_scores stu[], int n)//n为学生实际人数
{
	//计算部分
	for (int i = 0; i < n; i++)//逐个计算每个学生的总分和平均分
	{
		for (int j = 0; j < course_num; j++)//累加对应学生每门课程的分数
		{
			stu[i].stu_sum = stu[i].stu_sum + stu[i].stu_score[j];
		}
		stu[i].stu_average = float(stu[i].stu_sum) / course_num;
	}
}

//菜单3 - 计算每个学生的总分和平均分
void student_scores_sum_and_average(student_scores stu[], int n)//n为学生实际人数
{
	//输出部分
	for (int i = 0; i < n; i++)
	{
		cout << stu[i].stu_name << ": sum=" << stu[i].stu_sum << setiosflags(ios::fixed) << setprecision(2) << ", aver=" << stu[i].stu_average << endl;
	}
}

//菜单11 - 输出每个学生的学号、姓名、各科考试成绩，以及每门课程的总分和平均分
void score_output(student_scores stu[], int n)//n为学生实际人数
{
	score_title();
	for (int i = 0; i < n; i++)//逐个输出学生的成绩条
	{
		score_bar(stu, i);
	}
}

#pragma endregion


#pragma region 排序功能
///
///排序功能
///

//计算学生总分总排名（成绩录入后立刻完成排名计算）
void load_score_list(student_scores stu[], int n)
{
	int a;
	int* temp = new int[n];
	for (int i = 0; i < n; i++)
		temp[i] = stu[i].stu_sum;
	for (int i = 0; i < n; i++)
	{
		a = 0;
		for (int j = 0; j < n; j++)
			a = temp[j] > temp[a] ? j : a;
		temp[a] = 0;
		stu[a].stu_rank = i + 1;
	}
}

//菜单 4/5 - 按每个学生的总分 由高到低/由低到高 排出名次表
void score_list(student_scores stu[], int n, int high_low)
{
	cout << "Sort in ascending order by score :" << endl;
	score_title();
	if (high_low == 1)
	{
		for (int i = 1; i <= n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (stu[j].stu_rank == i)
					score_bar(stu, j);
			}
		}
	}
	else
	{
		for (int i = n; i >= 1; i--)
		{
			for (int j = 0; j < n; j++)
			{
				if (stu[j].stu_rank == i)
					score_bar(stu, j);
			}
		}
	}
}

//菜单6 - 按学号由小到大排出成绩表
void id_list(student_scores stu[], int n)
{
	cout << "Sort in ascending order by number :" << endl;
	int a;
	int* temp = new int[n];
	for (int i = 0; i < n; i++)
		temp[i] = stu[i].stu_id;
	score_title();
	for (int i = 0; i < n; i++)
	{
		a = 0;
		for (int j = 0; j < n; j++)
			a = temp[j] < temp[a] ? j : a;
		temp[a] = 99999999;
		score_bar(stu, a);
	}
	cout << endl;
}


//菜单7 - 按姓名的字典顺序排出成绩表
void name_list(student_scores stu[], int n)
{
	cout << "Sort in dictionary order by name:" << endl;
	int a;
	string *temp = new string[n];
	for (int i = 0; i < n; i++)
		temp[i] = stu[i].stu_name;
	score_title();
	for (int i = 0; i < n; i++)
	{
		a = 0;
		for (int j = 0; j < n; j++)
			a = temp[j] < temp[a] ? j : a;
		temp[a] = "~";
		score_bar(stu, a);
	}
	cout << endl;
}
#pragma endregion


#pragma region 查询功能
///
///查询功能
///

//菜单8 - 按学号查询学生排名及其考试成绩
void checking_out_for_id(student_scores stu[], int n)//n为学生实际人数
{
	cout << "Input the number you want to search:" << endl;
	int checking_stu_id = 0;//被查询的学生学号
	cin >> checking_stu_id;
	int i = 0;
	for (i = 0; i < n; i++)
	{
		if (stu[i].stu_id == checking_stu_id)
		{
			score_title();
			score_bar(stu, i);
			break;
		}
	}
	if (stu[i].stu_id != checking_stu_id)
		cout << "Not found!" << endl;
}

//菜单9 - 按姓名查询学生排名及其考试成绩
void checking_out_for_name(student_scores stu[], int n)//n为学生实际人数
{
	cout << "Input the name you want to search:" << endl;
	string checking_stu_name;//被查询学生的姓名
	cin >> checking_stu_name;
	int i = 0;
	for (i = 0; i < n; i++)
	{
		if (stu[i].stu_name == checking_stu_name)
		{
			score_title();
			score_bar(stu, i);
			break;
		}
	}
	if (stu[i].stu_name != checking_stu_name)
		cout << "Not found!" << endl;
}

#pragma endregion


#pragma region 统计功能
///
///统计功能
///

//菜单10 - 对每门课程分别统计每个类别的人数以及所占的百分比
void count(student_scores stu[])
{
	int peo[6] = {0};
	int n = 1;
	for (int i = 0; i < stu_num; i++)
		peo[i] = 0;
	while (n <= course_num)
	{
		printf("For course %d\n", n);
		for (int i = 0; i < stu_num; i++)
		{
			if (stu[i].stu_score[n - 1] < 60) peo[0]++;
			else if (stu[i].stu_score[n - 1] < 70 && stu[i].stu_score[n - 1] >= 60) peo[1]++;
			else if (stu[i].stu_score[n - 1] < 80 && stu[i].stu_score[n - 1] >= 70) peo[2]++;
			else if (stu[i].stu_score[n - 1] < 90 && stu[i].stu_score[n - 1] >= 80) peo[3]++;
			else if (stu[i].stu_score[n - 1] < 100 && stu[i].stu_score[n - 1] >= 90) peo[4]++;
			else peo[5]++;
		}
		printf("<60\t%d\t%.2f%%\n", peo[0], 100 * (double)peo[0] / (double)stu_num);
		printf("60-69\t%d\t%.2f%%\n", peo[1], 100 * (double)peo[1] / (double)stu_num);
		printf("70-79\t%d\t%.2f%%\n", peo[2], 100 * (double)peo[2] / (double)stu_num);
		printf("80-89\t%d\t%.2f%%\n", peo[3], 100 * (double)peo[3] / (double)stu_num);
		printf("90-99\t%d\t%.2f%%\n", peo[4], 100 * (double)peo[4] / (double)stu_num);
		printf("100\t%d\t%.2f%%\n", peo[5], 100 * (double)peo[5] / (double)stu_num);
		for (int i = 0; i < stu_num; i++)
			peo[i] = 0;
		n++;
	}
}


#pragma endregion


#pragma region 恢复与备份功能
///
///恢复与备份功能
///

//菜单12 - 恢复学生成绩数据
void recovery(student_scores stu[], int n)
{
	
	//<-弹出窗口选择数据文件
	OPENFILENAME ofn;
	char szFile[300];

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = (LPWSTR)szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = L"Scores Record\0*.score\0Text\0*.txt\0All\0*.*\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	//弹出窗口选择数据文件->

	if (GetOpenFileName(&ofn))
	{
		cout << "Successfully choose the path." << endl;
		wprintf(L"%s\n", ofn.lpstrFile);
		
		//数据文件导入
		ifstream fin(ofn.lpstrFile);
		fin >> course_num;
		for (int i = 0; i < n; i++)
		{
			fin >> stu[i].stu_id >> stu[i].stu_name;
			for (int j = 0; j < course_num; j++)
				fin >> stu[i].stu_score[j];
		}
		fin.close();
		cout << "Recovery successfully." << endl;
	}
	else
	{
		cout << "User cancel the Recovery." << endl;
	}
}

//菜单13 - 备份学生成绩数据
void backup(student_scores stu[], int n)
{
	ofstream fout("scores record.score");
	fout << course_num << endl;
	for (int i = 0; i < n; i++)
	{
		fout << stu[i].stu_id << "\t" << stu[i].stu_name << "\t";
		for (int j = 0; j < course_num; j++)
			fout << stu[i].stu_score[j] << "\t";
		fout << endl;
	}
	fout.close();
	cout << "Backup successfully." << endl;
}

#pragma endregion


#pragma region 主程序
///
///主程序
///

int main()
{
	//输入学生人数
	cout << "Input student number(n<30):" << endl;
	t = 0;
	while (t == 0)
	{
		if (cin >> stu_num)
			t = 1;
		else
		{
			cout << "Input error!" << endl;
			cin.clear(); //将cin重新标记为正确，以达到重新输入的目的
			while (cin.get() != '\n')	 //清空之前cin缓冲区的数据
				continue;
		}
	}
	student_scores stu[30];//学生人数不超过30人

	#if 0
	//if 0 时该代码片段处于注释状态，if 1 时该代码片段会执行
	//用于程序初始化时自动注入样例数据，不必执行“菜单选项1”，从而可以直接调试其他菜单选项的模块
	//调试其他模块时，请把对应模块函数引用的stu（外部!）改为stu2
	stu_num = 6;
	course_num = 3;
	student_scores stu2[6] =
	{
		{11003001,"lisi",87,82,89},
		{11003005,"heli",98,92,90},
		{11003003,"ludi",75,78,80},
		{11003002,"dumo",48,50,67},
		{11003004,"zuma",65,69,72},
		{11003006,"suyu",100,95,94}
	};
	#endif

	//程序主面板显示
	while (1)
	{
		int menu = 0; //菜单选项
		cout << "Management for Students' scores" << endl //学生成绩管理 - 主菜单
			<< "1.Input record" << endl //（1）录入每个学生的学号、姓名和各科考试成绩
			<< "2.Caculate total and average score of every course" << endl //（2）计算每门课程的总分和平均分
			<< "3.Caculate total and average score of every student" << endl //（3）计算每个学生的总分和平均分
			<< "4.Sort in descending order by score" << endl //（4）按每个学生的总分由高到低排出名次表
			<< "5.Sort in ascending order by score" << endl //（5）按每个学生的总分由低到高排出名次表
			<< "6.Sort in ascending order by number" << endl //（6）按学号由小到大排出成绩表
			<< "7.Sort in dictionary order by name" << endl //（7）按姓名的字典顺序排出成绩表
			<< "8.Search by number" << endl //（8）按学号查询学生排名及其考试成绩
			<< "9.Search by name" << endl //（9）按姓名查询学生排名及其考试成绩
			<< "10.Statistic analysis" << endl //（10）对每门课程分别统计每个类别的人数以及所占的百分比
			<< "11.List record" << endl //（11）输出每个学生的学号、姓名、各科考试成绩，以及每门课程的总分和平均分
			<< "12.Recovery record" << endl //（12）恢复学生成绩数据
			<< "13.Backup record" << endl //（13）备份学生成绩数据
			<< "0.Exit" << endl //退出程序
			<< "Please Input your choice:" << endl;
		
		t = 0;
		while (t == 0)
		{
			if (cin >> menu)
				t = 1;
			else
			{
				cout << "Input error!" << endl;
				cin.clear(); //将cin重新标记为正确，以达到重新输入的目的
				while (cin.get() != '\n')	 //清空之前cin缓冲区的数据
					continue;
			}
		}

		switch (menu)
		{
		case 1:
			student_scores_input(stu, stu_num);
			score_loading(stu);
			break;
		case 2:
			course_scores_sum_and_average(stu, stu_num);
			break;
		case 3:
			student_scores_sum_and_average(stu, stu_num);
			break;
		case 4:
			score_list(stu, stu_num, 1);
			break;
		case 5:
			score_list(stu, stu_num, 0);
			break;
		case 6:
			id_list(stu, stu_num);
			break;
		case 7:
			name_list(stu, stu_num);
			break;
		case 8:
			checking_out_for_id(stu, stu_num);
			break;
		case 9:
			checking_out_for_name(stu, stu_num);
			break;
		case 10:
			count(stu);
			break;
		case 11:
			score_output(stu, stu_num);
			break;
		case 12:
			recovery(stu, stu_num);
			score_loading(stu);
			break;
		case 13:
			backup(stu, stu_num);
			break;
		case 0:
			cout << "End of program!" << endl;
			return 0;
		default:
			cout << "Input error!" << endl;
		}
	}
	
	return 0;
}

#pragma endregion