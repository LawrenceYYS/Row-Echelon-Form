#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<math.h>

int gys(int m, int n){
	int t, b;
	if (m < n){
		t = m; m = n; n = t;
	}
	do{
		b = m % n; m = n; n = b;
	} while (n != 0);
	return m;
}

int gbs(int m, int n){
	int c, d;
	c = gys(m, n);
	d = m * n / c;
	return d;
}

//计算行最大公约数函数
int row_maxgys(int** m, int pr, int c) {
	int i, maxgys = m[pr][0];
	for (i = 1; i < c; i++) {
		if (!maxgys && m[pr][i] != 0) {
			maxgys = m[pr][i];
		}
		else if (maxgys && m[pr][i]) {
			maxgys = gys(maxgys, m[pr][i]);
		}
	}
	return abs(maxgys);
}

//检查某行首个非零元素是否为负，为负返回1，不为负返回0
int row_beginWithNegative(int** m, int pr, int c) {
	int i;
	for (i = 0; i < c; i++) {
		if (m[pr][i] > 0) {
			return 0;
		}
		else if (m[pr][i] < 0) {
			return 1;
		}
	}
	return 0;
}

//打印矩阵函数
void printMatrix(int** m, int r, int c) {
	for (int i = 0; i < r; i++){
		for (int j = 0; j < c; j++){
			printf("%5d", m[i][j]);
		}
		printf("\n");
	}
}

//判断矩阵是否满足行阶梯形式，满足返回1，不满足返回0
int isFormed(int** m, int r, int c) {
	if (r == 1) {
		return 1;
	}
	int *zeros = (int *)malloc(sizeof(int)*r), i, j, count;
	for (i = 0; i < r; i++) {
		for (count = 0, j = 0; j < c; j++) {
			if (m[i][j] == 0) {
				count++;
			}
			else {
				break;
			}
		}
		zeros[i] = count;
	}
	for (i = 0; i < r - 1; i++) {
		if (zeros[i] >= zeros[i + 1] && zeros[i + 1] != c) {
			free(zeros);
			return 0;
		}
	}
	free(zeros);
	return 1;
}

//矩阵排序函数，有移动返回1，无移动返回0
int sortMatrix(int** m, int r, int c) {
	int *zeros = (int *)malloc(sizeof(int)*r), i, j, k, count, moved = 0, t;
	for (i = 0; i < r; i++) {
		for (count = 0, j = 0; j < c; j++) {
			if (m[i][j] == 0) {
				count++;
			}
			else {
				break;
			}
		}
		zeros[i] = count;
	}
	for (i = 0; i < r - 1; i++) {
		for (j = i + 1; j < r; j++) {
			if (zeros[j] < zeros[i]) {
				moved = 1;
				t = zeros[i]; zeros[i] = zeros[j]; zeros[j] = t;
				for (k = 0; k < c; k++) {
					t = m[i][k]; m[i][k] = m[j][k]; m[j][k] = t;
				}
			}
		}
	}
	free(zeros);
	return moved;
}

int main() {
	printf("注意：此版本为测试版本，计算结果可能不正确，仅作参考！\n");
	int row, column, **matrix, i, j, processRowPoint = 0, processColumnPoint = 0, step = 0, *stepPoint = &step, operated = 0, max_gys, min_gbs, muiltiple;
	printf("请输入矩阵大小[row] [column]:");
	scanf("%d %d", &row, &column);//获取矩阵大小
	matrix = (int**)malloc(sizeof(int*)*row);
	for (i = 0; i < row; i++) {
		matrix[i] = (int*)malloc(sizeof(int)*column);
	}//根据用户输入分配二维数组空间
	printf("请输入矩阵元素[element_1] [element_2] ... [element_n]:\n");
	for (i = 0; i < row; i++){
		for (j = 0; j < column; j++){
			scanf("%d", &matrix[i][j]);
		}
	}//获取矩阵元素
	printf("\n矩阵元素获取完毕，矩阵应如下所示：\n");
	printMatrix(matrix, row, column);
	printf("\n现在开始处理矩阵，使其成为行阶梯型矩阵。\n");
	if (isFormed(matrix, row, column)) {
		printf("\n矩阵已经符合行阶梯形式，处理完毕。");
		system("pause");
		exit(0);
	}
	while (!isFormed(matrix, row, column)) {
		operated = 0;
		if (sortMatrix(matrix, row, column)) {
			printf("\nStep %d >> 若干次行交换\n", ++step);
			printMatrix(matrix, row, column); operated++;
		}
		//确认列处理参考
		for (i = 0; i < column; i++) {
			if (matrix[processRowPoint][i] != 0) {
				processColumnPoint = i;
				break;
			}
		}
		//检查各行首项是否为负
		for (i = 0; i < row; i++) {
			if (row_beginWithNegative(matrix, i, column)) {
				for (j = 0; j < column; j++) {
					matrix[i][j] *= -1;
				}
				printf("\nStep %d >> Row.%d * (-1)\n", ++step, i + 1);
				printMatrix(matrix, row, column); operated++;
			}
		}
		//检查各行是否拥有大于1的最大公约数
		for (i = 0; i < row; i++) {
			max_gys = row_maxgys(matrix, i, column);
			if (max_gys >= 2) {
				for (j = 0; j < column; j++) {
					matrix[i][j] /= max_gys;
				}
				printf("\nStep %d >> Row.%d / %d\n", ++step, i + 1, max_gys);
				printMatrix(matrix, row, column); operated++;
			}
		}
		//开始处理
		for (i = processRowPoint + 1; i < row; i++) {
			if (matrix[i][processColumnPoint] && matrix[processRowPoint][processColumnPoint]) {//检查是否有0
				if (matrix[i][processColumnPoint] == matrix[processRowPoint][processColumnPoint]) {//相等则相减
					for (j = 0; j < column; j++) {
						matrix[i][j] -= matrix[processRowPoint][j];
					}
					printf("\nStep %d >> Row.%d - Row.%d\n", ++step, i + 1, processRowPoint + 1);
					printMatrix(matrix, row, column); operated++;
				}
				else {//不等则先乘后减
					min_gbs = gbs(matrix[i][processColumnPoint], matrix[processRowPoint][processColumnPoint]);
					muiltiple = min_gbs / matrix[i][processColumnPoint];
					if (muiltiple > 1) {
						for (j = 0; j < column; j++) {
							matrix[i][j] *= muiltiple;
						}
						printf("\nStep %d >> Row.%d * %d\n", ++step, i + 1, muiltiple);
						printMatrix(matrix, row, column); operated++;
					}
					muiltiple = min_gbs / matrix[processRowPoint][processColumnPoint];
					for (j = 0; j < column; j++) {
						matrix[i][j] -= muiltiple * matrix[processRowPoint][j];
					}
					if (muiltiple > 1) {
						printf("\nStep %d >> Row.%d - %d * Row.%d\n", ++step, i + 1, muiltiple, processRowPoint + 1);
					}
					else {
						printf("\nStep %d >> Row.%d - Row.%d\n", ++step, i + 1, processRowPoint + 1);
					}
					printMatrix(matrix, row, column); operated++;
				}
			}
		}
		//检查各行首项是否为负
		for (i = 0; i < row; i++) {
			if (row_beginWithNegative(matrix, i, column)) {
				for (j = 0; j < column; j++) {
					matrix[i][j] *= -1;
				}
				printf("\nStep %d >> Row.%d * (-1)\n", ++step, i + 1);
				printMatrix(matrix, row, column); operated++;
			}
		}
		//检查各行是否拥有大于1的最大公约数
		for (i = 0; i < row; i++) {
			max_gys = row_maxgys(matrix, i, column);
			if (max_gys >= 2) {
				for (j = 0; j < column; j++) {
					matrix[i][j] /= max_gys;
				}
				printf("\nStep %d >> Row.%d / %d\n", ++step, i + 1, max_gys);
				printMatrix(matrix, row, column); operated++;
			}
		}
		if (!operated) {
			processRowPoint++;
		}
	}
	printf("\n矩阵已经符合行阶梯形式，处理完毕。");
	system("pause");
	return 0;
}
