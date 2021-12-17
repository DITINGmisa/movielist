#ifndef LIB_H //就是头文件名（全大写后加个_H
#define LIB_H
#include "kll.h"
#include <iomanip>
static const char* smdf = "MovieBase";
static const char* smif = "Noidx";
static const char* slf1 = "Nameidx";
static const char* slf2 = "Directoridx";
static const char* slf3 = "Tableidx";
static const char* saf = "Audience";
static const char* smrf = "Record";
static const char* srcf = "Recommend";
using namespace std;
class Lib
{
public:
	//取MovieDbaseFile结构的len
	int getNrbooks()const {
		return mdf.len;
	}
	//追加一条主数据库记录
	void AppDbaseRec(const MovieRecType& newbook)
	{
		mdf.append(newbook);
	}
	//兴趣评级
	void recomrank()
	{

	}
	//按浏览量排序
	void sort1()
	{
		int i, j;
		RecommendRecType* temp=(RecommendRecType*)malloc(sizeof(RecommendRecType));
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4 - i; j++)
			{
				if (mdf.MovieDbase[rcf.RecommendDbase[j].num].watchnum < mdf.MovieDbase[rcf.RecommendDbase[j + 1].num].watchnum)
				{
					temp->num = rcf.RecommendDbase[j].num;
					rcf.RecommendDbase[j].num = rcf.RecommendDbase[j + 1].num;
					rcf.RecommendDbase[j + 1].num = temp->num;
					temp->recorank = rcf.RecommendDbase[j].recorank;
					rcf.RecommendDbase[j].recorank = rcf.RecommendDbase[j + 1].recorank;
					rcf.RecommendDbase[j + 1].recorank = temp->recorank;
				}
			}
		
		}
	}
	//按评分排序
	void sort2()
	{
		int i, j;
		RecommendRecType* temp = (RecommendRecType*)malloc(sizeof(RecommendRecType));
		for (i = 5; i < 10; i++)
		{
			for (j = 5; j < 10; j++)
				if (mdf.MovieDbase[rcf.RecommendDbase[j].num].star < mdf.MovieDbase[rcf.RecommendDbase[j+1].num].star)
				{
					temp->num = rcf.RecommendDbase[j].num;
					rcf.RecommendDbase[j].num = rcf.RecommendDbase[j + 1].num;
					rcf.RecommendDbase[j + 1].num = temp->num;
					temp->recorank = rcf.RecommendDbase[j].recorank;
					rcf.RecommendDbase[j].recorank = rcf.RecommendDbase[j + 1].recorank;
					rcf.RecommendDbase[j + 1].recorank = temp->recorank;
				}
		}
	}
	//个性化排序
	void sort3()
	{

	}
	//按浏览量推荐
	void recommend1()
	{
		for (int i = 0; i < mdf.len; i++)
		{
			if (mdf.MovieDbase[i].watchnum > mdf.MovieDbase[rcf.RecommendDbase[4].num].watchnum)
			{
				rcf.RecommendDbase[4].num = i;
				sort1();
			}
		}
		cout <<"最多播放：\n" <<"=============================================\n"
			<< "编号  影片名    导演    标签   星级    价格   浏览量\n";
		for (int i = 0; i < 5; i++)
		{
			MovieRecType tmp = mdf.MovieDbase[rcf.RecommendDbase[i].num];
			cout << tmp.mNo << "\t" << tmp.mName << "\t"
				<< tmp.director << "\t" << tmp.table << "\t"
				<< tmp.star << "\t" << tmp.cost << "\t" << tmp.watchnum<<"\n";
		}
		cout<< endl << "=============================================\n\n";
	}
	//按评分推荐
	void recommend2()
	{
		for (int i = 0; i < mdf.len; i++)
		{
			if (mdf.MovieDbase[i].star > mdf.MovieDbase[rcf.RecommendDbase[9].num].star)
			{
				rcf.RecommendDbase[9].num = i;
				sort2();
			}
		}
		cout << "最受好评：\n" << "=============================================\n"
			<< "编号  影片名    导演    标签   星级    价格   浏览量\n";
		for (int i = 5; i < 10; i++)
		{
			MovieRecType tmp = mdf.MovieDbase[rcf.RecommendDbase[i].num];
			cout << tmp.mNo << "\t" << tmp.mName << "\t"
				<< tmp.director << "\t" << tmp.table << "\t"
				<< tmp.star << "\t" << tmp.cost << "\t" << tmp.watchnum << "\n";
		}
		cout << endl << "=============================================\n\n";
	}
	//个性化推荐
	void recommend3()
	{


	}
	//初始化
	void Int()
	{
		/*for (int i = 1; i <= mdf.len; i++)
		{
			for (int j = 0; j <= mdf.len; j++)
			{
				if (mdf.MovieDbase[j].mNo == i && j != i - 1)
				{
					MovieRecType temp;
					temp = mdf.MovieDbase[i-1];
					mdf.MovieDbase[i-1] = mdf.MovieDbase[j];
					mdf.MovieDbase[j] = temp;
				}
			}
		}
		for (int i = 1; i <= 22; i++)
		{
			ShowRec(i);
		}*/
		for (int i = 0; i < 15; i++)
		{
			rcf.RecommendDbase[i].num = i;
			rcf.RecommendDbase[i].recorank = 0;
		}
		sort1();
		sort2();
		sort3();
	}
	//修改编号索引表
	void ChangeNoF(int indexofrec)
	{
		int i = indexofrec;
		int j = mif.len - 1;//目前长度
		int k = 0;
		while (j >= 0)
		{
			//找插入位置
			if (mdf.MovieDbase[i].mNo > mif.BnoIdx[j].mNo)
			{
				k = j + 1;
				break;
			}
			j--;
		}
		//在有序索引表中插入一个索引记录
		MIDRecType tmp;
		tmp.mNo = mdf.MovieDbase[i].mNo;
		tmp.RecNo = i;
		mif.append(tmp);
		if (mif.len > 1)								//有序表的插入 
			for (j = mif.len - 2; j >= k; j--)
			{
				mif.BnoIdx[j + 1] = mif.BnoIdx[j];	//记录后移
			}
		mif.BnoIdx[k].mNo = mdf.MovieDbase[i].mNo;
		mif.BnoIdx[k].RecNo = i;
	}
	//修改电影名索引和链头索引
	void ChangeLinkHeadF1(int indexofrec)
	{
		//修改电影当前记录
		int i, j, k;
		char mn[100];
		i = indexofrec;
		strcpy(mn, mdf.MovieDbase[i].mName);			//取记录中的电影名送至变量mn中
		j = 0; k = -1;
		while (j < lf1.len)
		{
			//在链头中查找与次关键字相等的记录
			if (strcmp(mn, lf1.LHFrec1[j].mName) == 0)
			{
				k = j;
				break;
			}
			j++;
		}
		//采用头插法建立索引
		if (k != -1)
		{
			mdf.MovieDbase[i].namenext = lf1.LHFrec1[k].lhead;
			lf1.LHFrec1[k].lhead = i;			//i为主文件的当前记录号
			lf1.LHFrec1[k].RecNum++;
		}
		else
		{
			mdf.MovieDbase[i].namenext = -1;		//用头插法建立链表，指针置-1
			MNRecType tmp;
			tmp.lhead = i;						//i为主文件的当前记录号
			tmp.RecNum = 1;						//计数器置1
			strcpy(tmp.mName, mn);
			lf1.append(tmp);
		}
	}
	//修改导演索引和链头索引
	void ChangeLinkHeadF2(int indexofrec)
	{
		//修改影片当前记录
		int i, j, k;
		char dir[100];
		i = indexofrec;
		strcpy(dir, mdf.MovieDbase[i].director);			//取记录中的导演送至变量dir中
		j = 0; k = -1;
		while (j < lf2.len)
		{
			//在链头中查找与次关键字相等的记录
			if (strcmp(dir, lf2.LHFrec2[j].director) == 0)
			{
				k = j;
				break;
			}
			j++;
		}
		if (k != -1)
		{
			mdf.MovieDbase[i].dirnext = lf2.LHFrec2[k].lhead;
			lf2.LHFrec2[k].lhead = i;			//i为主文件的当前记录号
			lf2.LHFrec2[k].RecNum++;
		}
		else
		{
			MDRecType tmp;
			tmp.lhead = i;						//i为主文件的当前记录号
			tmp.RecNum = 1;						//计数器置1
			strcpy(tmp.director, dir);
			lf2.append(tmp);
			mdf.MovieDbase[i].dirnext = -1;
		}
	}
	//修改关键词1索引和链头索引
	void ChangeLinkHeadF3(int indexofrec)
	{
		//修改电影当前记录
		int i, j, k;
		char table[11];
		i = indexofrec;
		strcpy(table, mdf.MovieDbase[i].table);			//取记录中的关键词送至变量table中
		j = 0; k = -1;
		while (j < lf3.len)
		{
			//在链头中查找与次关键字相等的记录
			if (strcmp(table, lf3.LHFrec3[j].table) == 0)
			{
				k = j;
				break;
			}
			j++;
		}
		if (k != -1)
		{
			mdf.MovieDbase[i].tblnext = lf3.LHFrec3[k].lhead;
			lf3.LHFrec3[k].lhead = i;			//i为主文件的当前记录号
			lf3.LHFrec3[k].RecNum++;
		}
		else
		{
			MTRecType tmp;
			tmp.lhead = i;						//i为主文件的当前记录号
			tmp.RecNum = 1;						//计数器置1
			strcpy(tmp.table, table);
			lf3.append(tmp);
			mdf.MovieDbase[i].tblnext = -1;
		}
	}
	//按编号二分查找
	int MNoFind(int key)
	{
		int low = 0;
		int high = mif.len - 1;
		while (low <= high)
		{
			int mid = (low + high) / 2;
			if (key == mif.BnoIdx[mid].mNo)
				return mif.BnoIdx[mid].RecNo;
			else if (key < mif.BnoIdx[mid].mNo)
				high = mid - 1;
			else
				low = mid + 1;
		}
		return -1;//没找到
	}
	//按片名查找
	int MNameFind(char* key)
	{
		int k = -1;
		for (int i = 0; i < lf1.len; i++)
		{
			if (strcmp(key, lf1.LHFrec1[i].mName) == 0)
			{
				k = lf1.LHFrec1[i].lhead;
				break;
			}
		}
		return k;
	}
	//按导演查找
	int MDirFind(char* key)
	{
		int k = -1;
		for (int i = 0; i < lf2.len; i++)
		{
			if (strcmp(key, lf2.LHFrec2[i].director) == 0)
			{
				k = lf2.LHFrec2[i].lhead;
				break;
			}
		}
		return k;
	}
	//按标签查找
	int MTabFind(char* key)
	{
		int k = -1;
		for (int i = 0; i < lf3.len; i++)
		{
			if (strcmp(key, lf3.LHFrec3[i].table) == 0)
			{
				k = lf3.LHFrec3[i].lhead;
				break;
			}
		}
		return k;
	}
	//输出一条主数据库记录
	void ShowRec(int indexofrec)
	{
		int i = indexofrec;
		const MovieRecType& tmp = mdf.MovieDbase[i];
		cout << "编号  影片名    导演    标签   星级    价格   浏览量\n"
			<< tmp.mNo << "\t" << tmp.mName << "\t"
			<< tmp.director << "\t" << tmp.table << "\t"
			<< tmp.star << "\t" << tmp.cost << "\t" << tmp.watchnum
			<< endl << "=============================================\n";
	}
	//电影查询控制
	void SearchMovie()
	{
		char mn[100], dir[100], table[11];
		int k, sel;
		int mno;
		while (true)
		{
			cout << "\n\n\n按关键字查询\n"
				<< "--------------\n"
				<< "1.编号  2.片名\n"
				<< "3.导演  4.类型标签\n"
				<< "5.退出查询\n"
				<< "--------------\n"
				<< "请选择操作：";
			cin >> sel;
			switch (sel)
			{
			case 1:
				cout << "输入编号：";
				cin >> mno;
				k = MNoFind(mno);
				if (k == -1)
				{
					cout << "没有找到编号为 " << mno << " 的影片，请检查是否输入出错\n";
				}
				else ShowRec(k);
				break;
			case 2:
				cout << "输入片名：";
				cin >> mn;
				k = MNameFind(mn);
				if (k == -1)
				{
					cout << "没有找到片名为 " << mn << " 的影片，请检查是否输入出错\n";
				}
				else
				{
					for (int i = k; i != -1; i = mdf.MovieDbase[i].namenext)
						ShowRec(i);
				}
				break;
			case 3:
				cout << "输入导演名：";
				cin >> dir;
				k = MDirFind(dir);
				if (k == -1)
				{
					cout << "没有找到导演名为 " << dir << " 的影片，请检查是否输入出错\n";
				}
				else
				{
					for (int i = k; i != -1; i = mdf.MovieDbase[i].dirnext)
						ShowRec(i);
				}
				break;
			case 4:
				cout << "\n\n\n影片类型有：\n"
					 << "奇幻\n科幻\n恐怖\n爱情\n古装\n动作\n动画\n"
					 << "输入类型标签：";
				cin >> table;
				k = MTabFind(table);
				if (k == -1)
				{
					cout << "没有找到类型标签为 " << table << " 的影片，请检查是否输入出错\n";
				}
				else
				{
					for (int i = k; i != -1; i = mdf.MovieDbase[i].tblnext)
						ShowRec(i);
				}
				break;
			case 5:
				return;
			}
		}
	}
	//订阅管理
	void BuyMovie()
	{
		int mno, auid;
		int j, k = -1;
		char yn;
		cout << "输入会员号   影片编号\n";
		cin >> auid >> mno;
		for (int i = 0; i < af.len; i++)
		{
			if (auid == af.AudiRec[i].aNo)
			{
				k = i;
				break;
			}
		}
		j = MNoFind(mno);
		if (j == -1)
		{
			cout << "查无此片，请检查编号\n";
			return;
		}
		else
		{
			ShowRec(j);
			cout << "\n";
		}
		if (k == -1)
		{
			cout << "您未注册会员！\n";
			return;
		}
		if (af.AudiRec[k].money < mdf.MovieDbase[j].cost)
		{
			cout << "您的余额不足\n"<< "当前余额：" << af.AudiRec[k].money;
			return;
		}
		MRecordRecType tmp;
		mdf.MovieDbase[j].watchnum++;
		tmp.aNo = auid;
		tmp.mNo = mno;
		af.AudiRec[k].money= af.AudiRec[k].money - mdf.MovieDbase[j].cost;
		cout<< "购买成功！\n影片网址为："
			<< mdf.MovieDbase[j].location
			<< "\n密码：" << mdf.MovieDbase[j].password;
		cout << "\n您的余额为：" << af.AudiRec[k].money;
		cout << "\n\n您是否想对影片评分？(可以帮助您更好地个性化推荐影片)\n"
			<< "y/n:";
		cin >> yn;
		if (yn == 'y' || yn == 'Y')
		{
			cout << "请输入评分(0-10)：";
			cin >> tmp.valuate;
			mdf.MovieDbase[j].star=(float)(mdf.MovieDbase[j].star * (float)mdf.MovieDbase[j].watchnum + (float)tmp.valuate) / (float)mdf.MovieDbase[j].watchnum ;
			cout << "评分成功！\n" << "当前评分：";
			cout.unsetf(ios::fixed);
			cout << setprecision(3) << (float)mdf.MovieDbase[j].star<<"\n";
		}
		mrf.append(tmp);
	}
	//评价管理
	void Evaluate()
	{
		char hsrq[9];
		int mno, auid;
		int j, k = -1, m = -1;
		cout << "输入会员号   影片编号\n";
		cin >> auid >> mno;
		for (int i = 0; i < af.len; i++)
		{
			if (auid == af.AudiRec[i].aNo)
			{
				k = i;
				break;
			}
		}
		j = MNoFind(mno);
		if (j == -1)
		{
			cout << "查无此片，请检查编号\n";
			return;
		}
		if (k == -1)
		{
			cout << "您未注册会员！\n";
			return;
		}
		for (int i = 0; i < mrf.len; i++)
		{
			if (mno == mrf.Record[i].mNo && auid==mrf.Record[i].aNo)
			{
				m = i;
				break;
			}
		}
		if (m == -1)
		{
			cout << "您未看过此片，不能评分\n";
			return;
		}
		if (mrf.Record[m].valuate != -1)
		{
			cout << "您之前的评分为：" << mrf.Record[m].valuate << "\n";
		}
		cout << "请输入评分(0-10)：";
		cin>>mrf.Record[m].valuate;
		mdf.MovieDbase[j].star = (float)(mdf.MovieDbase[j].star * (float)mdf.MovieDbase[j].watchnum + (float)mrf.Record[m].valuate) / (float)(mdf.MovieDbase[j].watchnum+1);
		cout << "评分成功！\n" << "当前评分：";
		cout.unsetf(ios::fixed);
		cout << setprecision(3) << (float)mdf.MovieDbase[j].star << "\n";
	}
	//会员管理
	void ReaderManage()
	{
		cout << "1.新增会员   2.会员充值   3.查询余额"
			<< "\n请输入：";
		int j, k = -1;
		cin >> j;
		if (j == 1)
		{
			char yn = 'y';
			while (yn == 'y' || yn == 'Y')
			{
				MARecType reader;
				cout << "输入会员号  会员名  金额：" << "\n";
				cin >> reader.aNo >> reader.name >> reader.money;
				af.append(reader);
				cout << "已有" << af.len << "个会员\n";
				cout << "是否继续输入？(y/n):";
				cin >> yn;
			}
			return;
		}
		if (j == 2)
		{
			int auid , money;
			cout << "输入会员号:";
			cin >> auid;
			for (int i = 0; i < af.len; i++)
			{
				if (auid == af.AudiRec[i].aNo)
				{
					k = i;
					break;
				}
			}
			if (k == -1)
			{
				cout << "查无此人\n";
				return;
			}
			else
			{
				cout << "输入充值金额:";
				cin >> money;
				af.AudiRec[k].money += money;
				cout << "当前余额：" << af.AudiRec[k].money << "\n";;
			}
			return;
		}
		else
		{
			int auid, money;
			cout << "输入会员号:";
			cin >> auid;
			for (int i = 0; i < af.len; i++)
			{
				if (auid == af.AudiRec[i].aNo)
				{
					k = i;
					break;
				}
			}
			if (k == -1)
			{
				cout << "查无此人\n";
				return;
			}
			else
			{
				cout << "当前余额：" << af.AudiRec[k].money << "\n";;
			}
			return;
		}
	}
	void MovieRcommend()
	{
		recommend1();
		recommend2();
		recommend3();
	}
	//写各类文件
	void writeFile()
	{
		//写影片主文件
		ofstream out;
		out.open(smdf);
		mdf.serilize(out);
		out.close();
		//写编号索引文件
		out.open(smif);
		mif.serilize(out);
		out.close();
		//写片名索引文件
		out.open(slf1);
		lf1.serilize(out);
		out.close();
		//写导演索引文件
		out.open(slf2);
		lf2.serilize(out);
		out.close();
		//写标签索引文件
		out.open(slf3);
		lf3.serilize(out);
		out.close();
		//写会员索引文件
		out.open(saf);
		af.serilize(out);
		out.close();
		//写记录索引文件
		out.open(smrf);
		mrf.serilize(out);
		out.close();
		//写推荐影片文件
		out.open(srcf);
		rcf.serilize(out);
		out.close();
	}
	//读各类文件
	void readFile()
	{
		//读影片主文件
		ifstream out;
		out.open(smdf);
		mdf.deserilize(out);
		out.close();
		//读编号索引文件
		out.open(smif);
		mif.deserilize(out);
		out.close();
		//读片名索引文件
		out.open(slf1);
		lf1.deserilize(out);
		out.close();
		//读导演索引文件
		out.open(slf2);
		lf2.deserilize(out);
		out.close();
		//读标签索引文件
		out.open(slf3);
		lf3.deserilize(out);
		out.close();
		//读会员索引文件
		out.open(saf);
		af.deserilize(out);
		out.close();
		//读记录索引文件
		out.open(smrf);
		mrf.deserilize(out);
		out.close();
		//读推荐影片文件
		out.open(srcf);
		rcf.deserilize(out);
		out.close();
	}

private:
	MovieDbaseFile	mdf;
	MNoFile		mif;
	LHFile1	lf1;
	LHFile2	lf2;
	LHFile3	lf3;
	AudiFile	af;
	MRecordFile	mrf;
	RecommendFile rcf;
};
#endif