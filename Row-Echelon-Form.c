#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//首列整行冒泡排序函数
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

//排列数组，特别地，根据线性代数解题要求，我们需要将0越多的项移动到越下方
int** sortArray(int** a, int r, int c) {
	//统计各行开头0的个数
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
	//统计完毕，冒泡排序行使得0越多的行在越下方
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

//检查数组是否符合行阶梯形式，0不符合，1符合
int checkForm(int** a, int r, int c) {
	//统计各行开头0的个数
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

//检查行首个非0元素是否为负，0为非负，1为负
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

//计算行最大公约数，0不参与计算，结果为0或1，main()中不需要作处理
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

//判断两个相同规模的二维数组是否相等，0不相等，1相等
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
	printf("测试版本 警告：该程序只能给出矩阵的行阶梯形式，并且很可能不适宜用于计算行最简形式！\n");
	int r, c;//获取行数、列数
	printf("请输入矩阵大小[row] [column]:");
	scanf("%d %d", &r, &c);
	//根据行数、列数设置动态二维数组以表示一个矩阵
	int** matrix;
	matrix = (int**)malloc(sizeof(int*)*r);
	for (int i = 0; i < r; i++)
		matrix[i] = (int*)malloc(sizeof(int)*c);
	printf("请输入矩阵元素[element_1] [element_2] ... [element_n]:\n");
	for (int i = 1; i <= r; i++)
	{
		for (int j = 1; j <= c; j++)
		{
			scanf("%d", &matrix[i - 1][j - 1]);
		}
	}
	printf("\n矩阵元素获取完毕，矩阵应如下所示：\n");
	printArray(matrix, r, c);
	printf("\n现在开始处理矩阵，使其成为行阶梯型矩阵。\n");
	int step = 0;
	//开始检查首项是否为负
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
	//开始检查各行是否存在不为1的最大公约数
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
	//开始对二维数组进行排序，colomn.1， colomn.2-n分别为主关键字、次关键字，冒泡排序
	//特别地，根据线性代数解题要求，我们需要将0越多的行移动到越下方
	if (checkForm(matrix, r, c) == 1) {
		printf("\n矩阵已经符合行阶梯格式！");
		system("pause");
		return 0;
	}
	matrix = sortArray(matrix, r, c);
	printf("\nStep %d >> 若干（或0）次行交换\n", ++step);
	printArray(matrix, r, c);
	//此时矩阵已经完全排序完毕，开始逐行消去
	int basicRow = 1, basicColomn = 1, operate = 0;
	while ((basicColomn < c)||(basicRow < r))
	{
		int operate = 0;
		for (int i = basicRow + 1; i <= r; i++)
		{
			if ((matrix[basicRow - 1][basicColomn - 1] == 0) || (matrix[i - 1][basicColomn - 1] == 0)) {
				continue;
			}
			if (matrix[basicRow - 1][basicColomn - 1] == matrix[i - 1][basicColomn - 1]) {//相等
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
				int muiltiple = min_gbs / matrix[basicRow - 1][basicColomn - 1];//倍数
				for (int j = 1; j <= c; j++)
				{
					matrix[i - 1][j - 1] -= muiltiple * matrix[basicRow - 1][j - 1];
				}
				operate = 1;
				printf("\nStep %d >> Row.%d - %d * Row.%d\n", ++step, i, muiltiple, basicRow);
				printArray(matrix, r, c);
			}
			else {
				int muiltiple = min_gbs / matrix[i - 1][basicColomn - 1];//倍数
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
			//开始检查首项是否为负
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
			//开始检查各行是否存在不为1的最大公约数
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
			//排序
			matrix = sortArray(matrix, r, c);
			printf("\nStep %d >> 若干（或0）次行交换\n", ++step);
			printArray(matrix, r, c);
			//形式检查
			if (checkForm(matrix, r, c) == 1) {
				printf("\n矩阵已经符合行阶梯格式！");
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