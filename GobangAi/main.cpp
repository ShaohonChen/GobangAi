//���������
#include<iostream>

const int BOARD_LENGTH = 15;
const int BOARD_HIGH = 15;
int human = 1, cmp = 2;

void display(short** board) {
	using namespace std;
	char character = 'A';
	//��ӡ��ĸ
	cout << endl;
	cout << " ";
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
			switch ((int)board[i][j]) {
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
	for (int i = x; i >= 0&&board[i][y]==my; i--) {	//��
		len++;
	}
	for (int i = x; i <=BOARD_LENGTH && board[i][y] == my; i++) {	//��
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
	for (int i = x; i <= BOARD_LENGTH && board[x][i] == my; i++) {	//��
		len++;
	}
	if (len > 5) {
		return true;
	}
	//Ʋ
	len = 0;
	for (int i = x, j = y; i >= 0 && j <=BOARD_HIGH  && board[i][j] == my; i--,j++) {	//��
		len++;
	}
	for (int i = x, j = y; i <= BOARD_LENGTH, j >= 0 && board[i][j] == my; i++, j--) {	//��
		len++;
	}
	if (len > 5) {
		return true;
	}
	//��
	len = 0;
	for (int i = x, j = y; i >= 0 && j >= 0 && board[i][j] == my; i--, j++) {	//��
		len++;
	}
	for (int i = x, j = y; i <= BOARD_LENGTH, j <= BOARD_HIGH && board[i][j] == my; i++, j++) {	//��
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
		std::cout << std::endl << "���������꣨��ʽ����ĸ ���֣���";
		while (1) {	//UNDONE:��������

		}
		x = (short)(row - 'A');
		y = column;
		if (x >= 0 && x <= BOARD_LENGTH && y >= 0 && y <= BOARD_HIGH) {
			cout << "�����߽磡����������" << endl;
			display(board);
			continue;
		}
		if (!board[x][y]) {
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

int assess(short** board, short x, short y, int steps) {
	if (iswin(board, x, y)) {
		return 100000;
	}
	auto my = board[x][y];
	auto other = 3 - my;
	short tempx, tempy;
	bool iscontinuity1 = true, iscontinuity2 = true;
	bool barrier1, barrier2;
	int olen1,olen2,len;
	int clen1,clen2,clen;
	int score = 0;
	//��
	tempx = x;
	tempy = y;
	len = 0;
	clen = 0;
	olen1 = 0, olen2 = 0, clen1 = 0, clen2 = 0;
	barrier1 = false, barrier2 = false;
	iscontinuity1 = true, iscontinuity2 = true;
	while (1) {	//��
		if (tempx < 0 && tempx >= BOARD_LENGTH)
			break;
		if (tempy < 0 && tempy >= BOARD_HIGH)
			break;
		if (board[tempx][tempy] != my) {
			if (board[tempx][tempy] == other) {
				barrier1=true;
				break;
			}
			else {
				if (!iscontinuity1) {
					break;
				}
				else {
					iscontinuity1 = false;
					continue;
				}
			}
		}
		if (iscontinuity1)
			clen1++;
		else
			olen1++;
		tempx++;
	}
	while (1) {	//��
		if (tempx < 0 && tempx >= BOARD_LENGTH)
			break;
		if (tempy < 0 && tempy >= BOARD_HIGH)
			break;
		if (board[tempx][tempy] != my) {
			if (board[tempx][tempy] == other) {
				barrier2 = true;
				break;
			}
			else {
				if (!iscontinuity2) {
					break;
				}
				else {
					iscontinuity2 = false;
					continue;
				}
			}
		}
		if (iscontinuity2)
			clen1++;
		else
			olen1++;
		tempx--;
	}
	//����
	clen = clen1 + clen2 - 1;	//UNDONE:�����Ƿ�ϸ������
	

	//��

	return 1;

}

int alphabeta(short** board,short& x,short& y,short human_pose,int steps,int thinkdeep) {
	int win = 100000, draw = 0;
	int thistp = 0;

	if (human_pose==-1)
		if (iswin(board, human_pose/BOARD_LENGTH, human_pose%BOARD_LENGTH)) {
			return -win;
		}
		else
			thistp = 1 << (thinkdeep);
	if (steps == BOARD_LENGTH * BOARD_HIGH)
		return 0;
	for (short i = 0; i < BOARD_HIGH*BOARD_LENGTH; i++) {
		if (board[i / BOARD_LENGTH][i%BOARD_LENGTH])
			continue;
		board[i / 3][i % 3] = my;
	}
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
	int thinkdeep = 8;

	//ȷ������
	std::cout << "�Ƿ����֣�(Ĭ��Ϊ��)(Y/N)" << std::endl;
	char c;
	while (c=std::cin.get()!='\n') {	//HACK: ���뷽ʽ������
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
	//��ʾ����
	display(board);
	while (1) {
		if (steps == BOARD_HIGH * BOARD_LENGTH) {
			std::cout << "ƽ��" << std::endl;
			break;
		}
		humanhand(board, x, y, steps);
		if (iswin(board,x,y)) {
			std::cout << "��Ӯ��" << std::endl;
		}
		if (steps == BOARD_HIGH * BOARD_LENGTH) {
			std::cout << "ƽ��" << std::endl;
			break;
		}
		cmphand(board, x, y, steps,thinkdeep);
		if (iswin(board, x, y)) {
			std::cout << "������" << std::endl;
		}
	}

	system("pause");
	return 0;
}