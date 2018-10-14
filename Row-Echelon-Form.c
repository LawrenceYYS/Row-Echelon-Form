#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//��������ð��������
int** firstColomnSort(int** a, int r, int c, int sr, int sc, int er) {
	for (int k = 1; k <= er - sr; k++)
	{
		int equal = 0;
		for (int i = sr; i < er; i++)
		{
			if (a[i - 1][sc] != a[i][sc]) {
				equal = 1;
			}
		}
		if (equal == 0) {
			continue;
		}
		for (int i = er; i > sr + k - 1; i--)
		{
			if (a[i - 1][sc - 1] < a[i - 2][sc - 1]) {
				for (int j = sc; j <= c; j++)
				{
					int t = a[i - 1][j - 1];
					a[i - 1][j - 1] = a[i - 2][j - 1];
					a[i - 2][j - 1] = t;
				}
			}
		}
	}
	return a;
}
int gys(int m, int n)
{
	int t, b;
	if (m < n)
	{
		t = m;
		m = n;
		n = t;
	}
	do
	{
		b = m % n;
		m = n;
		n = b;
	} while (n != 0);
	return m;
}

int gbs(int m, int n)
{
	int c, d;
	c = gys(m, n);
	d = m * n / c;
	return d;
}

void printArray(int** a,int r,int c) {
	for (int i = 1; i <= r; i++)
	{
		for (int j = 1; j <= c; j++)
		{
			printf("%5d", a[i - 1][j - 1]);
		}
		printf("\n");
	}
}

//�������飬�ر�أ��������Դ�������Ҫ��������Ҫ��0Խ������ƶ���Խ�·�
int** sortArray(int** a, int r, int c) {
	//ͳ�Ƹ��п�ͷ0�ĸ���
	int* zeros; int containZeroLines = 0;
	zeros = (int*)malloc(sizeof(int*)*r);
	for (int i = 1; i <= r; i++)
	{
		if (a[i - 1][0] != 0) {
			zeros[i - 1] = 0;
			continue;
		}
		else {
			zeros[i - 1] = 1; containZeroLines++;
		}
		for (int j = 1; j < c; j++)
		{
			if (a[i - 1][j] == a[i - 1][0]) {
				zeros[i - 1]++;
			}
		}
	}
	//ͳ����ϣ�ð��������ʹ��0Խ�������Խ�·�
	for (int i = 1; i <= r; i++)
	{
		for (int j = r; j > i; j--)
		{
			if (zeros[j - 1] < zeros[j - 2]) {
				int t = zeros[j - 1];
				zeros[j - 1] = zeros[j - 2];
				zeros[j - 2] = t;
				for (int k = 1; k <= c; k++)
				{
					t = a[j - 1][k - 1];
					a[j - 1][k - 1] = a[j - 2][k - 1];
					a[j - 2][k - 1] = t;
				}
			}
		}
	}
	int startRow = 1, startColomn = 1, endRow = r - containZeroLines, scanStart = 1, scanEnd = 1;
	a = firstColomnSort(a, r, c, 1, 1, endRow);
	for (int j = startColomn; j <= r; j++)
	{
		scanStart = startRow; scanEnd = scanStart;
		for (int i = startRow; i < endRow; i++)
		{
			if (a[startRow - 1][j - 1] == a[i][j - 1]) {
				scanEnd = i + 1;
			}
			else {
				break;
			}
		}
		if ((scanStart == startRow) && (scanEnd == endRow)) {
			startRow = 1; scanStart = 1; endRow = r - containZeroLines; scanEnd = 1;
			a = firstColomnSort(a, r, c, startRow, startColomn + 1, endRow);
			continue;
		}
		if (scanStart != scanEnd) {
			a = firstColomnSort(a, r, c, scanStart, startColomn + 1, scanEnd);
			j--;
			startRow = scanEnd + 1;
			if (startRow > r) {
				startRow = 1; startColomn += 1;
			}
		}
		else {
			startColomn += 1;
		}
	}
	return a;
}

//��������Ƿ�����н�����ʽ��0�����ϣ�1����
int checkForm(int** a, int r, int c) {
	//ͳ�Ƹ��п�ͷ0�ĸ���
	int* zeros;
	zeros = (int*)malloc(sizeof(int*)*r);
	for (int i = 1; i <= r; i++)
	{
		if (a[i - 1][0] != 0) {
			zeros[i - 1] = 0;
			continue;
		}
		else {
			zeros[i - 1] = 1;
		}
		for (int j = 1; j < c; j++)
		{
			if (a[i - 1][j] == a[i - 1][0]) {
				zeros[i - 1]++;
			}
			else {
				break;
			}
		}
	}
	int formed = 1;
	for (int i = 1; i < r; i++)
	{
		if (zeros[i - 1] >= zeros[i]) {
			formed = 0;
		}
	}
	return formed;
}

//������׸���0Ԫ���Ƿ�Ϊ����0Ϊ�Ǹ���1Ϊ��
int row_beginWithNavigate(int** a, int r, int c, int sr) {
	int navigate = 0;
	for (int i = 1; i <= c; i++)
	{
		if (a[sr - 1][i - 1] == 0) {
			continue;
		}
		else {
			if (a[sr - 1][i - 1] > 0) {
				navigate = 0;
				break;
			}
			else {
				navigate = 1;
				break;
			}
		}
	}
	return navigate;
}

//���������Լ����0��������㣬���Ϊ0��1��main()�в���Ҫ������
int row_gys(int** a, int r, int c, int sr) {
	int max_gys = 0;
	for (int i = 1; i <= c; i++)
	{
		if ((max_gys == 0)&&(a[sr - 1][i - 1] !=0)) {
			max_gys = a[sr - 1][i - 1];
		}
		if ((max_gys != 0)&&(a[sr - 1][i] != 0)&&(i < c)) {
			max_gys = gys(max_gys, a[sr - 1][i]);
		}
	}
	return abs(max_gys);
}

//�ж�������ͬ��ģ�Ķ�ά�����Ƿ���ȣ�0����ȣ�1���
int arraysAreSame(int** a, int** b, int r, int c) {
	int same = 1;
	for (int i = 1; i <= r; i++)
	{
		for (int j = 1; j <= c; j++)
		{
			if (a[i - 1][j - 1] != b[i - 1][j - 1]) {
				same = 0;
				break;
			}
		}
		if (same == 0) {
			break;
		}
	}
	return same;
}

int main()
{
	printf("���԰汾 ���棺�ó���ֻ�ܸ���������н�����ʽ�����Һܿ��ܲ��������ڼ����������ʽ��\n");
	int r, c;//��ȡ����������
	printf("����������С[row] [column]:");
	scanf("%d %d", &r, &c);
	//�����������������ö�̬��ά�����Ա�ʾһ������
	int** matrix;
	matrix = (int**)malloc(sizeof(int*)*r);
	for (int i = 0; i < r; i++)
		matrix[i] = (int*)malloc(sizeof(int)*c);
	printf("���������Ԫ��[element_1] [element_2] ... [element_n]:\n");
	for (int i = 1; i <= r; i++)
	{
		for (int j = 1; j <= c; j++)
		{
			scanf("%d", &matrix[i - 1][j - 1]);
		}
	}
	printf("\n����Ԫ�ػ�ȡ��ϣ�����Ӧ������ʾ��\n");
	printArray(matrix, r, c);
	printf("\n���ڿ�ʼ�������ʹ���Ϊ�н����;���\n");
	int step = 0;
	//��ʼ��������Ƿ�Ϊ��
	for (int i = 1; i <= r; i++)
	{
		if (row_beginWithNavigate(matrix, r, c, i) == 1) {
			for (int j = 1; j <= c; j++)
			{
				matrix[i - 1][j - 1] = -matrix[i - 1][j - 1];
			}
			printf("\nStep %d >> Row.%d * (-1)\n", ++step, i);
			printArray(matrix, r, c);
		}
	}
	//��ʼ�������Ƿ���ڲ�Ϊ1�����Լ��
	for (int i = 1; i <= r; i++)
	{
		int max_gys = row_gys(matrix, r, c, i);
		if ((max_gys != 1)&&(max_gys != 0)) {
			for (int k = 1; k <= c; k++)
			{
				matrix[i - 1][k - 1] = matrix[i - 1][k - 1] / max_gys;
			}
			printf("\nStep %d >> Row.%d / %d\n", ++step, i, max_gys);
			printArray(matrix, r, c);
		}
	}
	//��ʼ�Զ�ά�����������colomn.1�� colomn.2-n�ֱ�Ϊ���ؼ��֡��ιؼ��֣�ð������
	//�ر�أ��������Դ�������Ҫ��������Ҫ��0Խ������ƶ���Խ�·�
	if (checkForm(matrix, r, c) == 1) {
		printf("\n�����Ѿ������н��ݸ�ʽ��");
		system("pause");
		return 0;
	}
	matrix = sortArray(matrix, r, c);
	printf("\nStep %d >> ���ɣ���0�����н���\n", ++step);
	printArray(matrix, r, c);
	//��ʱ�����Ѿ���ȫ������ϣ���ʼ������ȥ
	int basicRow = 1, basicColomn = 1, operate = 0;
	while ((basicColomn < c)||(basicRow < r))
	{
		int operate = 0;
		for (int i = basicRow + 1; i <= r; i++)
		{
			if ((matrix[basicRow - 1][basicColomn - 1] == 0) || (matrix[i - 1][basicColomn - 1] == 0)) {
				continue;
			}
			if (matrix[basicRow - 1][basicColomn - 1] == matrix[i - 1][basicColomn - 1]) {//���
				for (int j = 1; j <= c; j++)
				{
					matrix[i - 1][j - 1] -= matrix[basicRow - 1][j - 1];
				}
				operate = 1;
				printf("\nStep %d >> Row.%d - Row.%d\n", ++step, i, basicRow);
				printArray(matrix, r, c);
				continue;
			}
			int min_gbs = gbs(matrix[basicRow - 1][basicColomn - 1],matrix [i - 1][basicColomn - 1]);
			if (min_gbs == matrix[i - 1][basicColomn - 1]) {
				int muiltiple = min_gbs / matrix[basicRow - 1][basicColomn - 1];//����
				for (int j = 1; j <= c; j++)
				{
					matrix[i - 1][j - 1] -= muiltiple * matrix[basicRow - 1][j - 1];
				}
				operate = 1;
				printf("\nStep %d >> Row.%d - %d * Row.%d\n", ++step, i, muiltiple, basicRow);
				printArray(matrix, r, c);
			}
			else {
				int muiltiple = min_gbs / matrix[i - 1][basicColomn - 1];//����
				for (int j = 1; j <= c; j++)
				{
					matrix[i - 1][j - 1] *= muiltiple;
				}
				printf("\nStep %d >> Row.%d * %d\n", ++step, i, muiltiple);
				printArray(matrix, r, c);
				muiltiple = matrix[i - 1][basicColomn - 1] / matrix[basicRow - 1][basicColomn - 1];
				for (int j = basicColomn; j <= c; j++)
				{
					matrix[i - 1][j - 1] -= (muiltiple * matrix[basicRow - 1][basicColomn - 1]);
				}
				operate = 1;
				printf("\nStep %d >> Row.%d - %d * Row.%d\n", ++step, i, muiltiple, basicRow);
				printArray(matrix, r, c);
			}
		}
		if (operate == 1) {
			basicColomn++; basicRow++; operate = 0;
			//��ʼ��������Ƿ�Ϊ��
			for (int i = 1; i <= r; i++)
			{
				if (row_beginWithNavigate(matrix, r, c, i) == 1) {
					for (int j = 1; j <= c; j++)
					{
						matrix[i - 1][j - 1] = -matrix[i - 1][j - 1];
					}
					printf("\nStep %d >> Row.%d * (-1)\n", ++step, i);
					printArray(matrix, r, c);
				}
			}
			//��ʼ�������Ƿ���ڲ�Ϊ1�����Լ��
			for (int i = 1; i <= r; i++)
			{
				int max_gys = row_gys(matrix, r, c, i);
				if ((max_gys != 1) && (max_gys != 0)) {
					for (int k = 1; k <= c; k++)
					{
						matrix[i - 1][k - 1] = matrix[i - 1][k - 1] / max_gys;
					}
					printf("\nStep %d >> Row.%d / %d\n", ++step, i, max_gys);
					printArray(matrix, r, c);
				}
			}
			//����
			matrix = sortArray(matrix, r, c);
			printf("\nStep %d >> ���ɣ���0�����н���\n", ++step);
			printArray(matrix, r, c);
			//��ʽ���
			if (checkForm(matrix, r, c) == 1) {
				printf("\n�����Ѿ������н��ݸ�ʽ��");
				system("pause");
				return 0;
			}
		}
		else {
			basicColomn++; basicRow++; operate = 0;
		}

	}
	system("pause");
	return 0;
}