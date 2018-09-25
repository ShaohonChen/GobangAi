//五子棋程序
#include<iostream>
#include<math.h>

const int BOARD_LENGTH = 15;
const int BOARD_HIGH = 15;
int human = 1, cmp = 2;

void display(short** board) {
	using namespace std;
	char character = 'A';
	//打印字母
	cout << endl;
	cout << "  ";
	for (int i = 0; i < BOARD_LENGTH; i++) {
		cout << " " << (char)(character + i) << " ";
	}
	cout << endl;
	//打印数字加棋盘
	for (int i = 0; i < BOARD_HIGH; i++) {
		cout << i + 1;
		if (i + 1 < 10)
			cout << " ";
		for (int j = 0; j < BOARD_LENGTH; j++) {
			cout << "[";
			switch ((int)board[j][i]) {
			case 1:
				cout << "X";
				break;
			case 2:
				cout << "O";
				break;
			default:
				cout << " ";
				break;
			}
			cout << "]";
		}
		cout << endl;
	}
}

bool iswin(short** board,short x,short y) {
	short my = board[x][y];
	short len;
	//横
	len = 0;
	for (int i = x; i >= 0 && board[i][y]==my; i--) {	//左
		len++;
	}
	for (int i = x; i < BOARD_LENGTH && board[i][y] == my; i++) {	//右
		len++;
	}
	if (len > 5) {
		return true;
	}
	//竖
	len = 0;
	for (int i = y; i >= 0 && board[x][i] == my; i--) {	//上
		len++;
	}
	for (int i = y; i < BOARD_LENGTH && board[x][i] == my; i++) {	//下
		len++;
	}
	if (len > 5) {
		return true;
	}
	//撇
	len = 0;
	for (int i = x, j = y; i >= 0 && j < BOARD_HIGH  && board[i][j] == my; i--,j++) {	//左
		len++;
	}
	for (int i = x, j = y; i < BOARD_LENGTH && j >= 0 && board[i][j] == my; i++, j--) {	//右
		len++;
	}
	if (len > 5) {
		return true;
	}
	//捺
	len = 0;
	for (int i = x, j = y; i >= 0 && j >= 0 && board[i][j] == my; i--, j--) {	//左
		len++;
	}
	for (int i = x, j = y; i < BOARD_LENGTH && j < BOARD_HIGH && board[i][j] == my; i++, j++) {	//右
		len++;
	}
	if (len > 5) {
		return true;
	}
	return false;
}

void humanhand(short**board, short&x, short&y, int& steps) {
	using namespace std;
	char row;
	short column;
	while (1) {
		bool input = false;
		while (!input) {
			std::cout << std::endl << "请输入坐标（格式：字母 数字）：";
			input = true;
			cin >> row;
			if (row > 'Z' || row < 'A') {
				cout << "横坐标读入错误" << endl;
				while (cin.get() != '\n');
				cin.clear();
				input = false;
			}
			if (!(cin >> column)) {
				cout << "纵坐标格式错误" << endl;
				cin.clear();
				input = false;
			}
		}
		x = (short)(row - 'A');
		y = column - 1;
		if (x < 0 || x >= BOARD_LENGTH || y < 0 && y >= BOARD_HIGH) {
			cout << "超过边界！请重新输入" << endl;
			display(board);
			continue;
		}
		if (board[x][y]) {
			cout << "此位置已有棋子！请重新输入" << endl;
			display(board);
			continue;
		}
		board[x][y] = 1;
		steps++;
		break;
	}
	return;
}

//int assess(short** board, short x, short y, int steps) {
//	if (iswin(board, x, y)) {
//		return 100000;
//	}
//	auto my = board[x][y];
//	auto other = 3 - my;
//	short tempx, tempy;
//	bool iscontinuity1 = true, iscontinuity2 = true;
//	bool barrier1, barrier2;
//	int olen1,olen2,len;
//	int clen1,clen2,clen;
//	int score = 0;
//	//横
//	tempx = x;
//	tempy = y;
//	len = 0;
//	clen = 0;
//	olen1 = 0, olen2 = 0, clen1 = 0, clen2 = 0;
//	barrier1 = false, barrier2 = false;
//	iscontinuity1 = true, iscontinuity2 = true;
//	while (1) {	//加
//		if (tempx < 0 || tempx >= BOARD_LENGTH)
//			break;
//		if (tempy < 0 || tempy >= BOARD_HIGH)
//			break;
//		if (board[tempx][tempy] != my) {
//			if (board[tempx][tempy] == other) {
//				barrier1=true;
//				break;
//			}
//			else {
//				if (!iscontinuity1) {
//					break;
//				}
//				else {
//					iscontinuity1 = false;
//					continue;
//				}
//			}
//		}
//		if (iscontinuity1)
//			clen1++;
//		else
//			olen1++;
//		tempx++;
//	}
//	while (1) {	//减
//		if (tempx < 0 || tempx >= BOARD_LENGTH)
//			break;
//		if (tempy < 0 || tempy >= BOARD_HIGH)
//			break;
//		if (board[tempx][tempy] != my) {
//			if (board[tempx][tempy] == other) {
//				barrier2 = true;
//				break;
//			}
//			else {
//				if (!iscontinuity2) {
//					break;
//				}
//				else {
//					iscontinuity2 = false;
//					continue;
//				}
//			}
//		}
//		if (iscontinuity2)
//			clen1++;
//		else
//			olen1++;
//		tempx--;
//	}
//	//评分
//	clen = clen1 + clen2 - 1;	//UNDONE:考虑是否细化评分
//	
//	//竖
//	return 1;
//}

int assessone(short** board, short x, short y, int steps) {
	if (iswin(board, x, y)) {
		return 100000;
	}
	auto my = board[x][y];
	auto other = 3 - my;
	short tempx, tempy;
	int barrier;
	int len;
	int score = 0;
	//横
	tempx = x;
	tempy = y;
	len = 0;
	barrier = 0;
	while (1) {	//加
		if (tempx < 0 || tempx >= BOARD_LENGTH)
			break;
		if (tempy < 0 || tempy >= BOARD_HIGH)
			break;
		if (board[tempx][tempy] != my) {
			if (board[tempx][tempy] == other) {
				barrier++;
			}
			break;
		}
		len;
		tempx++;
	}
	tempx = x;
	tempy = y;
	while (1) {	//减
		if (tempx < 0 || tempx >= BOARD_LENGTH)
			break;
		if (tempy < 0 || tempy >= BOARD_HIGH)
			break;
		if (board[tempx][tempy] != my) {
			if (board[tempx][tempy] == other) {
				barrier++;
			}
			break;
		}
		len++;
		tempx--;
	}
	//评分
	len--;
	if (barrier < 2) {
		score += (double)std::pow(10, len - barrier);
	}
	//竖
	tempx = x;
	tempy = y;
	len = 0;
	barrier = 0;
	while (1) {	//加
		if (tempx < 0 || tempx >= BOARD_LENGTH)
			break;
		if (tempy < 0 || tempy >= BOARD_HIGH)
			break;
		if (board[tempx][tempy] != my) {
			if (board[tempx][tempy] == other) {
				barrier++;
			}
			break;
		}
		len;
		tempy++;
	}
	tempx = x;
	tempy = y;
	while (1) {	//减
		if (tempx < 0 || tempx >= BOARD_LENGTH)
			break;
		if (tempy < 0 || tempy >= BOARD_HIGH)
			break;
		if (board[tempx][tempy] != my) {
			if (board[tempx][tempy] == other) {
				barrier++;
			}
			break;
		}
		len++;
		tempy--;
	}
	//评分
	len--;
	if (barrier < 2) {
		score += (double)std::pow(10, len - barrier);
	}
	//撇
	tempx = x;
	tempy = y;
	len = 0;
	barrier = 0;
	while (1) {	//加
		if (tempx < 0 || tempx >= BOARD_LENGTH)
			break;
		if (tempy < 0 || tempy >= BOARD_HIGH)
			break;
		if (board[tempx][tempy] != my) {
			if (board[tempx][tempy] == other) {
				barrier++;
			}
			break;
		}
		len;
		tempx++;
		tempx++;
	}
	tempx = x;
	tempy = y;
	while (1) {	//减
		if (tempx < 0 || tempx >= BOARD_LENGTH)
			break;
		if (tempy < 0 || tempy >= BOARD_HIGH)
			break;
		if (board[tempx][tempy] != my) {
			if (board[tempx][tempy] == other) {
				barrier++;
			}
			break;
		}
		len++;
		tempx--;
		tempy--;
	}
	//评分
	len--;
	if (barrier < 2) {
		score += (double)std::pow(10, len - barrier);
	}
	//捺
	tempx = x;
	tempy = y;
	len = 0;
	barrier = 0;
	while (1) {	//加
		if (tempx < 0 || tempx >= BOARD_LENGTH)
			break;
		if (tempy < 0 || tempy >= BOARD_HIGH)
			break;
		if (board[tempx][tempy] != my) {
			if (board[tempx][tempy] == other) {
				barrier++;
			}
			break;
		}
		len;
		tempx++;
		tempy--;
	}
	tempx = x;
	tempy = y;
	while (1) {	//减
		if (tempx < 0 || tempx >= BOARD_LENGTH)
			break;
		if (tempy < 0 || tempy >= BOARD_HIGH)
			break;
		if (board[tempx][tempy] != my) {
			if (board[tempx][tempy] == other) {
				barrier++;
			}
			break;
		}
		len++;
		tempx--;
		tempy++;
	}
	//评分
	len--;
	if (barrier < 2) {
		score += (double)std::pow(10, len - barrier);
	}
	return score;
}

int assessall(short** board, int steps,int my) {
	int finial = 0, one = 0;
	for (short i = 0; i < BOARD_LENGTH*BOARD_HIGH; i++) {
		if (!board[i / BOARD_LENGTH][i % BOARD_LENGTH])
			continue;
		one = assessone(board, i / BOARD_LENGTH, i % BOARD_LENGTH, steps);
		if (!(board[i / BOARD_LENGTH][i % BOARD_LENGTH] == my)) {
			one = -one*5;
		}
		finial += one;
	}
	return finial;
}

int alphabeta(short my, short** board, int alpha,int beta, short& x, short& y, short human_pose, int steps, int thinkdeep) {	//HACK 内容有问题
	int win = 100000, draw = 0;
	int result;
	short tmpx,tmpy;
	if (human_pose != -1) 
		if (iswin(board, human_pose / BOARD_LENGTH, human_pose % BOARD_LENGTH)) {
			return -win;
		}
	if (steps == BOARD_LENGTH * BOARD_HIGH)
		return 0;
	for (short i = 0; i < BOARD_LENGTH*BOARD_HIGH; i++) {
		if (board[i / BOARD_LENGTH][i % BOARD_LENGTH])
			continue;
		if (alpha >= beta)
			break;
		board[i / BOARD_LENGTH][i % BOARD_LENGTH] = my;
		steps++;
		if (!(thinkdeep>0)) {
			result = -assessall(board, steps, 3-my);
		}
		else
			result = -alphabeta(3 - my, board, -beta, -alpha, tmpx, tmpy, i, steps, thinkdeep - 1);
		if (result > alpha) {
			alpha = result;
			x = i / BOARD_LENGTH;
			y = i % BOARD_LENGTH;
		}
		board[i / BOARD_LENGTH][i % BOARD_LENGTH] = 0;
		steps--;
	}
	return alpha;
}

void cmphand(short** board, short& x, short& y, int& steps,int thinkdeep) {
	alphabeta(2, board, -100000000000, +100000000000, x, y, -1, steps, thinkdeep);
	board[x][y] = 2;
	steps++;
	display(board);
	using namespace std;
	cout << "电脑下：" << (char)('A' + x) << " " << y + 1 << endl;
	return;
}

int main()
{
	std::cout << "五子棋游戏" << std::endl;
	std::cout << "作者：陈少宏" << std::endl\
		<< "规则：输入坐标进行下棋，坐标格式：“横坐标字母 纵坐标数字”" << std::endl;

	//初始化棋盘
	short **board = new short*[BOARD_LENGTH];
	for (int i = 0; i < 15; i++) {
		board[i] = new short[BOARD_HIGH]{ 0 };
	}
	short x, y;
	int steps = 0;
	int thinkdeep = 2;
	//确定先手
	std::cout << "是否先手？(默认为是)(Y/N)" << std::endl;
	char c;
	while (c = std::cin.get()) {
		if (c == 'Y') {
			break;
		}
		else if (c == 'N') {
			board[BOARD_HIGH / 2][BOARD_LENGTH / 2] = 2;
			steps++;
			break;
		}
		else {
			std::cout << "输入错误" << std::endl;
			while (std::cin.get() != '\n');
			std::cin.clear();
			std::cout << "是否先手？(默认为是)(Y/N)" << std::endl;
		}
	}
	c = std::cin.get();
	//显示棋盘
	display(board);
	while (1) {
		if (steps == BOARD_HIGH * BOARD_LENGTH) {
			std::cout << "平局" << std::endl;
			break;
		}
		humanhand(board, x, y, steps);
		if (iswin(board,x,y)) {
			display(board);
			std::cout << "你赢了" << std::endl;
			break;
		}
		if (steps == BOARD_HIGH * BOARD_LENGTH) {
			display(board);
			std::cout << "平局" << std::endl;
			break;
		}
		cmphand(board, x, y, steps,thinkdeep);
		if (iswin(board, x, y)) {
			display(board);
			std::cout << "你输了" << std::endl;
			break;
		}
	}
	system("pause");
	return 0;
}