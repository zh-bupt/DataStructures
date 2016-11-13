/*
��ѧ������С����,֧�ֺ�������(sin,cos,ln,log),֧��������
*/
#include<iostream>
#include<cmath>
using namespace std;

const int MAXLEN = 100;
const double PI = 3.141592653589793;
const double E = 2.718281828459;
int precision = 10;//����
char dor = 'd';//�Ƕ��ƻ��߻�����

/*�������ݵĽ��*/
typedef struct data_node {
	double data;
	struct data_node* next;
}data_node, *pdata_node;

/*����������Ľ��*/
typedef struct  symbol_node {
	char symbol;
	struct symbol_node* next;
}symbol_node, *psymbol_node;

/*�����������ջ*/
typedef struct {
	pdata_node bottom;
	pdata_node top;
	int stacksize;
} sqdata_stack;

/*�����������ջ*/
typedef struct {
	psymbol_node bottom;
	psymbol_node top;
	int stacksize;
} sqsymbol_stack;


sqdata_stack dst;
sqsymbol_stack sst;


void Initiate(sqdata_stack& st);//��ʼ��ջ
void Initiate(sqsymbol_stack& st);//��ʼ��ջ
double Pop(sqdata_stack& st, double& data);//����ջ��Ԫ��
char Pop(sqsymbol_stack& st, char& symbol);//����ջ��Ԫ��
int Push(sqdata_stack& st, double data);//��һ��Ԫ��ѹ��ջ
int Push(sqsymbol_stack& st, char symbol);//��һ��Ԫ��ѹ��ջ
int Empty(sqdata_stack st);//�ж�ջ�Ƿ�Ϊ��
int Empty(sqsymbol_stack st);//�ж�ջ�Ƿ�Ϊ��

void Calcute();//����ı��ʽ��ֵ�ĺ���
int Compare(char c1, char c2);//�Ƚ���������������ȼ���c1����c2����1�����򷵻�0
double Convert(char* buff);//��һ���ַ���ת��Ϊdouble���͵�����
double Operate(double data1, double data2, char s);//����������������Ϊ��������data1Ϊ��������data2��ֵΪ�㼴��

int main() {
	cout << "*************************************************************" << endl;
	cout << "*                ��ӭʹ�ÿ�ѧ������                         *" << endl;
	cout << "*************************************************************" << endl;
	cout << "���þ���(1-20λ��Ч����):";
	cin >> precision;//���뾫��
	cin.ignore(100, '\n');//���������
	if (precision>20 || precision<1)  precision = 10;
	cout << "��ѡ��Ƕ���(D)���ǻ�����(R):";
	cin >> dor;//ѡ��Ƕ��ƻ��ǻ�����
	cin.ignore(100, '\n');//���������
	dor = toupper(dor);
	cout << "��������ʽ:";
	Calcute();
	system("pause");
	return 0;
}

void Initiate(sqdata_stack& st) {
	pdata_node p = new data_node;
	p->next = NULL;
	st.top = p;
	st.bottom = p;
	st.stacksize = 0;
}
void Initiate(sqsymbol_stack& st) {
	psymbol_node p = new symbol_node;
	p->next = NULL;
	st.top = p;
	st.bottom = p;
	st.stacksize = 0;
}
double Pop(sqdata_stack& st) {
	if (Empty(st))  return 0;
	double data = st.top->data;
	pdata_node p = st.top;
	st.top = st.top->next;
	delete p;
	return data;
}
char Pop(sqsymbol_stack& st) {
	if (Empty(st))  return 0;
	char symbol = st.top->symbol;
	psymbol_node p = st.top;
	st.top = st.top->next;
	delete p;
	return symbol;
}
int Push(sqdata_stack& st, double data) {
	pdata_node p = new data_node;
	if (!p)  return 0;
	p->data = data;
	p->next = st.top;
	st.top = p;
	return 1;
}
int Push(sqsymbol_stack& st, char symbol) {
	psymbol_node p = new symbol_node;
	if (!p)  return 0;
	p->symbol = symbol;
	p->next = st.top;
	st.top = p;
	return 1;
}
int Empty(sqdata_stack st) {
	if (st.top != st.bottom)  return 0;
	return 1;
}
int Empty(sqsymbol_stack st) {
	if (st.top != st.bottom)  return 0;
	return 1;
}

void Calcute() {
	Initiate(dst);
	Initiate(sst);
	char ch, pre_ch = '+', wch, buff[100] = { '\0' };
	int buff_p = 0, i = 0;
	cin.get(ch);
	while (ch != '\n') {
		ch = (char)toupper(ch);
		switch (ch) {
		case ' ':
			break;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case '.':
			buff[buff_p++] = ch;
			break;
		case '(':
			if (buff[0] != '\0') {
				Push(dst, Convert(buff));
				buff_p = 0;
			}
			Push(sst, '(');
			break;
		case ')':
			if (buff[0] != '\0') {
				Push(dst, Convert(buff));
				buff_p = 0;
			}
			while (!Empty(sst) && (sst.top->symbol) != '(') {
				char s = Pop(sst);
				if (s == 'S' || s == 'C' || s == 'N' || s == 'G' || s == 'M' || s == 'P')
					Push(dst, Operate(Pop(dst), 0, s));
				else
					Push(dst, Operate(Pop(dst), Pop(dst), s));
			}
			Pop(sst);
			break;
		case 'C':
		case 'S':
			if (buff[0] != '\0') {
				Push(dst, Convert(buff));
				buff_p = 0;
			}
			cin.get(wch);
			cin.get(wch);
			if (pre_ch == 'S' || pre_ch == 'C' || pre_ch == 'N' || pre_ch == 'G')  Push(sst, ch);
			else {
				while (!Empty(sst) && !Compare(ch, sst.top->symbol)) {
					char s = Pop(sst);
					if (s == 'S' || s == 'C' || s == 'N' || s == 'G' || s == 'M' || s == 'P')
						Push(dst, Operate(Pop(dst), 0, s));
					else
						Push(dst, Operate(Pop(dst), Pop(dst), s));
				}
				Push(sst, ch);
			}
			break;
		case 'L':
			if (buff[0] != '\0') {
				Push(dst, Convert(buff));
				buff_p = 0;
			}
			cin.get(wch);
			wch = (char)toupper(wch);
			if (ch == 'N') {
				ch = 'N';
				if (pre_ch == 'S' || pre_ch == 'C' || pre_ch == 'N' || pre_ch == 'G')  Push(sst, ch);
				else {
					while (!Empty(sst) && !Compare(ch, sst.top->symbol)) {
						char s = Pop(sst);
						if (s == 'S' || s == 'C' || s == 'N' || s == 'G' || s == 'M' || s == 'P')
							Push(dst, Operate(Pop(dst), 0, s));
						else
							Push(dst, Operate(Pop(dst), Pop(dst), s));
					}
					Push(sst, ch);
				}
			}
			else {
				cin.get(wch);
				ch = 'G';
				if (pre_ch == 'S' || pre_ch == 'C' || pre_ch == 'N' || pre_ch == 'G')  Push(sst, ch);
				else {
					while (!Empty(sst) && !Compare(ch, sst.top->symbol)) {
						char s = Pop(sst);
						if (s == 'S' || s == 'C' || s == 'N' || s == 'G' || s == 'M' || s == 'P')
							Push(dst, Operate(Pop(dst), 0, s));
						else
							Push(dst, Operate(Pop(dst), Pop(dst), s));
					}
					Push(sst, ch);
				}
			}
			break;
		case '^':
		case '/':
		case '*':
			if (buff[0] != '\0') {
				Push(dst, Convert(buff));
				buff_p = 0;
			}
			while (!Empty(sst) && !Compare(ch, sst.top->symbol)) {
				char s = Pop(sst);
				if (s == 'S' || s == 'C' || s == 'N' || s == 'G' || s == 'M' || s == 'P')
					Push(dst, Operate(Pop(dst), 0, s));
				else
					Push(dst, Operate(Pop(dst), Pop(dst), s));
			}
			Push(sst, ch);
			break;
		case '-':
		case '+':
			if (buff[0] != '\0') {
				Push(dst, Convert(buff));
				buff_p = 0;
			}
			if (pre_ch<'0' || pre_ch>'9') {
				if (ch == '-')  ch = 'M';
				else  ch = 'P';
			}
			while (!Empty(sst) && !Compare(ch, sst.top->symbol)) {
				char s = Pop(sst);
				if (s == 'S' || s == 'C' || s == 'N' || s == 'G' || s == 'M' || s == 'P')
					Push(dst, Operate(Pop(dst), 0, s));
				else
					Push(dst, Operate(Pop(dst), Pop(dst), s));
			}
			Push(sst, ch);
			break;
		case '=':
			if (buff[0] != '\0') {
				Push(dst, Convert(buff));
				buff_p = 0;
			}
			while (!Empty(sst)) {
				char s = Pop(sst);
				if (s == 'S' || s == 'C' || s == 'N' || s == 'G' || s == 'M' || s == 'P')
					Push(dst, Operate(Pop(dst), 0, s));
				else
					Push(dst, Operate(Pop(dst), Pop(dst), s));
			}
			cout.precision(precision);
			cout << "���Ϊ:" << Pop(dst) << endl;
			break;
		}
		pre_ch = ch;
		cin.get(ch);
	}
}

//��һ���ַ���ת��Ϊdouble���͵�����
double Convert(char* buff) {
	double ret = 0;
	char *p = buff;
	while (*p && (*p != '.')) {//������������
		ret *= 10;
		ret += (*p) - '0';//���ַ�תΪ���ֲ��ۼ�
		(*p) = '\0';
		p++;//�ƶ�ָ��
	}
	if (*p == '.') {//����С�������
		double step = 0.1;
		(*p) = '\0';
		p++; //�Թ�С����
		while (*p) {//����С�����֣�ֱ���ַ�������
			ret += step*((*p) - '0');
			(*p) = '\0';
			step /= 10;
			p++;
		}
	}
	return ret;
}

//�Ƚ���������������ȼ���c1����c2����1�����򷵻�0
int Compare(char c1, char c2) {
	switch (c1) {
	case '+':
	case '-':
		switch (c2) {
		case 'G':
		case 'N':
		case 'C':
		case 'S':
		case '*':
		case '/':
		case '^':
		case '+':
		case '-':
			return 0;
		default:
			return 1;
		}
		break;
	case '*':
	case '/':
		switch (c2) {
		case 'M':
		case 'G':
		case 'N':
		case 'C':
		case 'S':
		case '^':
		case '*':
		case '/':
			return 0;
		default:
			return 1;
		}
		break;
	case '^':
		switch (c2) {
		case 'M':
		case 'G':
		case 'N':
		case 'C':
		case 'S':
		case '^':
			return 0;
		default:
			return 1;
		}
	case 'G':
	case 'N':
	case 'C':
	case 'S':
		switch (c2) {
		case 'P':
		case 'M':
		case 'G':
		case 'N':
		case 'C':
		case 'S':
			return 0;
		default:
			return 1;
		}
	case 'M':
	case 'P':
		return 1;
	}
}

/*����������������Ϊ��������data1Ϊ��������data2��ֵΪ�㼴��*/
double Operate(double data1, double data2, char s) {
	switch (s) {
	case '^':
		return pow(data1, data2);
	case '/':
		return data1 / data2;
	case '*':
		return data1*data2;
	case '-':
		return data1 - data2;
	case '+':
		return data1 + data2;
	case 'S':
		if (dor == 'D')  return sin(data1*PI / 180);
		else  return sin(data1);
	case 'C':
		if (dor == 'D')  return cos(data1*PI / 180);
		else  return cos(data1);
	case 'G':
		return log10(data1);
	case 'N':
		return log(data1);
	case 'M':
		return 0 - data1;
	case 'P':
		return data1;
	}
}
