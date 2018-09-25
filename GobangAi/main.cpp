//���������
#include<iostream>
#include<math.h>

const int BOARD_LENGTH = 15;
const int BOARD_HIGH = 15;
int human = 1, cmp = 2;

void display(short** board) {
	using namespace std;
	char character = 'A';
	//��ӡ��ĸ
	cout << endl;
	cout << "  ";
	for (int i = 0; i < BOARD_LENGTH; i++) {
		cout << " " << (char)(character + i) << " ";
	}
	cout << endl;
	//��ӡ���ּ�����
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
	//��
	len = 0;
	for (int i = x; i >= 0 && board[i][y]==my; i--) {	//��
		len++;
	}
	for (int i = x; i < BOARD_LENGTH && board[i][y] == my; i++) {	//��
		len++;
	}
	if (len > 5) {
		return true;
	}
	//��
	len = 0;
	for (int i = y; i >= 0 && board[x][i] == my; i--) {	//��
		len++;
	}
	for (int i = y; i < BOARD_LENGTH && board[x][i] == my; i++) {	//��
		len++;
	}
	if (len > 5) {
		return true;
	}
	//Ʋ
	len = 0;
	for (int i = x, j = y; i >= 0 && j < BOARD_HIGH  && board[i][j] == my; i--,j++) {	//��
		len++;
	}
	for (int i = x, j = y; i < BOARD_LENGTH && j >= 0 && board[i][j] == my; i++, j--) {	//��
		len++;
	}
	if (len > 5) {
		return true;
	}
	//��
	len = 0;
	for (int i = x, j = y; i >= 0 && j >= 0 && board[i][j] == my; i--, j--) {	//��
		len++;
	}
	for (int i = x, j = y; i < BOARD_LENGTH && j < BOARD_HIGH && board[i][j] == my; i++, j++) {	//��
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
			std::cout << std::endl << "���������꣨��ʽ����ĸ ���֣���";
			input = true;
			cin >> row;
			if (row > 'Z' || row < 'A') {
				cout << "������������" << endl;
				while (cin.get() != '\n');
				cin.clear();
				input = false;
			}
			if (!(cin >> column)) {
				cout << "�������ʽ����" << endl;
				cin.clear();
				input = false;
			}
		}
		x = (short)(row - 'A');
		y = column - 1;
		if (x < 0 || x >= BOARD_LENGTH || y < 0 && y >= BOARD_HIGH) {
			cout << "�����߽磡����������" << endl;
			display(board);
			continue;
		}
		if (board[x][y]) {
			cout << "��λ���������ӣ�����������" << endl;
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
//	//��
//	tempx = x;
//	tempy = y;
//	len = 0;
//	clen = 0;
//	olen1 = 0, olen2 = 0, clen1 = 0, clen2 = 0;
//	barrier1 = false, barrier2 = false;
//	iscontinuity1 = true, iscontinuity2 = true;
//	while (1) {	//��
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
//	while (1) {	//��
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
//	//����
//	clen = clen1 + clen2 - 1;	//UNDONE:�����Ƿ�ϸ������
//	
//	//��
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
	//��
	tempx = x;
	tempy = y;
	len = 0;
	barrier = 0;
	while (1) {	//��
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
	while (1) {	//��
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
	//����
	len--;
	if (barrier < 2) {
		score += (double)std::pow(10, len - barrier);
	}
	//��
	tempx = x;
	tempy = y;
	len = 0;
	barrier = 0;
	while (1) {	//��
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
	while (1) {	//��
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
	//����
	len--;
	if (barrier < 2) {
		score += (double)std::pow(10, len - barrier);
	}
	//Ʋ
	tempx = x;
	tempy = y;
	len = 0;
	barrier = 0;
	while (1) {	//��
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
	while (1) {	//��
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
	//����
	len--;
	if (barrier < 2) {
		score += (double)std::pow(10, len - barrier);
	}
	//��
	tempx = x;
	tempy = y;
	len = 0;
	barrier = 0;
	while (1) {	//��
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
	while (1) {	//��
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
	//����
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

int alphabeta(short my, short** board, int alpha,int beta, short& x, short& y, short human_pose, int steps, int thinkdeep) {	//HACK ����������
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
	cout << "�����£�" << (char)('A' + x) << " " << y + 1 << endl;
	return;
}

int main()
{
	std::cout << "��������Ϸ" << std::endl;
	std::cout << "���ߣ����ٺ�" << std::endl\
		<< "������������������壬�����ʽ������������ĸ ���������֡�" << std::endl;

	//��ʼ������
	short **board = new short*[BOARD_LENGTH];
	for (int i = 0; i < 15; i++) {
		board[i] = new short[BOARD_HIGH]{ 0 };
	}
	short x, y;
	int steps = 0;
	int thinkdeep = 2;
	//ȷ������
	std::cout << "�Ƿ����֣�(Ĭ��Ϊ��)(Y/N)" << std::endl;
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
			std::cout << "�������" << std::endl;
			while (std::cin.get() != '\n');
			std::cin.clear();
			std::cout << "�Ƿ����֣�(Ĭ��Ϊ��)(Y/N)" << std::endl;
		}
	}
	c = std::cin.get();
	//��ʾ����
	display(board);
	while (1) {
		if (steps == BOARD_HIGH * BOARD_LENGTH) {
			std::cout << "ƽ��" << std::endl;
			break;
		}
		humanhand(board, x, y, steps);
		if (iswin(board,x,y)) {
			display(board);
			std::cout << "��Ӯ��" << std::endl;
			break;
		}
		if (steps == BOARD_HIGH * BOARD_LENGTH) {
			display(board);
			std::cout << "ƽ��" << std::endl;
			break;
		}
		cmphand(board, x, y, steps,thinkdeep);
		if (iswin(board, x, y)) {
			display(board);
			std::cout << "������" << std::endl;
			break;
		}
	}
	system("pause");
	return 0;
}