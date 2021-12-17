#include "Lib.h"
int main()
{
	int j, k = 1;
	Lib lib;
	cout << "读原始文件中，请稍后。。。\n";
	lib.readFile();
	lib.Int();
	while (true)
	{
		cout << "影片购买与后台管理系统\n"
			<< "============\n"
			<< "1.会员管理\n"
			<< "2.影片管理\n"
			<< "3.影片流通\n"
			<< "4.退出系统\n"
			<< "===========\n"
			<< "请选择1-4：";
		cin >> k;
		switch (k)
		{
		case 1:
			lib.ReaderManage();
			break;
		case 2:
			cout << "影片管理子系统\n"
				<< "--------------\n"
				<< "1.影片信息输入\n"
				<< "2.影片信息查询\n"
				<< "--------------\n"
				<< "请选择1-2：";
			cin >> j;
			if (j == 1)
			{
				char yn = 'y';
				while (yn == 'y' || yn == 'Y')
				{
					MovieRecType tmp;
					/*cout << "编号  影 片 名   导演  标签\n";
					cin >> tmp.mNo >> tmp.mName >> tmp.director
						>> tmp.table ;
					cout << " 价格  网址  密码\n";
					cin >> tmp.cost >> tmp.location >> tmp.password;*/
					cout << "编号  影 片 名   导演  标签  价格  网址  密码\n";
					cin >> tmp.mNo >> tmp.mName >> tmp.director
						>> tmp.table>>tmp.cost >> tmp.location >> tmp.password;
					tmp.watchnum = 0;
					tmp.star = 0.0;
					lib.AppDbaseRec(tmp);
					int index = lib.getNrbooks() - 1;
					lib.ChangeNoF(index);
					lib.ChangeLinkHeadF1(index);
					lib.ChangeLinkHeadF2(index);
					lib.ChangeLinkHeadF3(index);
					cout << "是否继续输入？(y/n):";
					cin >> yn;
				}
				break;
			}
			else if (j == 2)
			{
				lib.SearchMovie();
				break;
			}
			else
				cout << "命令错误\n";
		case 3:
			cout << "影片流通子系统\n"
				<< "--------------\n"
				<< "1.购买影片\n"
				<< "2.评价影片\n"
				<< "3.推荐影片\n"
				<< "--------------\n"
				<< "请选择1-3：";
			cin >> j;
			if (j == 1)
				lib.BuyMovie();
			else if (j == 2)
				lib.Evaluate();
			else
				lib.MovieRcommend();
			break;
		case 4:
			cout << "写入文件中，请稍后。。。\n";
			lib.writeFile();
			cout << "再见！\n";
			return 0;
		}

	}
	return 0;
}