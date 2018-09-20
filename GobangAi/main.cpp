//五子棋程序
#include<iostream>

const int BOARD_LENGTH = 15;
const int BOARD_HIGH = 15;
int human = 1, cmp = 2;

void display(short** board) {
	using namespace std;
	char character = 'A';
	//打印字母
	cout << endl;
	cout << " ";
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
			switch ((int)board[i][j]) {
			case 1:
				cout << "X";
			case 2:
				cout << "O";
			default:
				cout << " ";
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
	for (int i = x; i >= 0&&board[i][y]==my; i--) {	//左
		len++;
	}
	for (int i = x; i <=BOARD_LENGTH && board[i][y] == my; i++) {	//左
		len++;
	}
	if (len > 5) {
		return true;
	}
	//竖
	len = 0;
	for (int i = y; i >= 0 && board[x][i] == my; i--) {	//左
		len++;
	}
	for (int i = x; i <= BOARD_LENGTH && board[x][i] == my; i++) {	//左
		len++;
	}
	if (len > 5) {
		return true;
	}
	//撇
	len = 0;
	for (int i = x, j = y; i >= 0 && j <=BOARD_HIGH  && board[i][j] == my; i--,j++) {	//左
		len++;
	}
	for (int i = x, j = y; i <= BOARD_LENGTH, j >= 0 && board[i][j] == my; i++, j--) {	//左
		len++;
	}
	if (len > 5) {
		return true;
	}
	//捺
	len = 0;
	for (int i = x, j = y; i >= 0 && j >= 0 && board[i][j] == my; i--, j++) {	//左
		len++;
	}
	for (int i = x, j = y; i <= BOARD_LENGTH, j <= BOARD_HIGH && board[i][j] == my; i++, j++) {	//左
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
		std::cout << std::endl << "请输入坐标（格式：字母 数字）：";
		while (1) {	//UNDONE:输入问题

		}
		x = (short)(row - 'A');
		y = column;
		if (x >= 0 && x <= BOARD_LENGTH && y >= 0 && y <= BOARD_HIGH) {
			cout << "超过边界！请重新输入" << endl;
			display(board);
			continue;
		}
		if (!board[x][y]) {
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

int assess(short** board, short x, short y, int steps) {
	if (iswin(board, x, y)) {
		return 100000;
	}
	auto my = board[x][y];
	bool iscontinuity = true;
	


	return 1;

}

int alphabeta() {
	return 1;
}

void cmphand(short** board, short& x, short& y, int& steps,int thinkdeep) {
	

	board[x][y] = 2;
	steps++;
	display(board);
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
	int thinkdeep = 8;

	//确定先手
	std::cout << "是否先手？(默认为是)(Y/N)" << std::endl;
	char c;
	while (c=std::cin.get()!='\n') {	//HACK: 输入方式有问题
		if (c == 'Y') {
			break;
		}
		else if (c == 'N') {
			board[7][7] = 2;
			steps++;
			break;
		}
		else {
			std::cout << "input error" << std::endl;
			while (std::cin.get() != '\n');
			std::cin.clear();
		}
	}
	//显示棋盘
	display(board);
	while (1) {
		if (steps == BOARD_HIGH * BOARD_LENGTH) {
			std::cout << "平局" << std::endl;
			break;
		}
		humanhand(board, x, y, steps);
		if (iswin(board,x,y)) {
			std::cout << "你赢了" << std::endl;
		}
		if (steps == BOARD_HIGH * BOARD_LENGTH) {
			std::cout << "平局" << std::endl;
			break;
		}
		cmphand(board, x, y, steps,thinkdeep);
		if (iswin(board, x, y)) {
			std::cout << "你输了" << std::endl;
		}
	}

	system("pause");
	return 0;
}