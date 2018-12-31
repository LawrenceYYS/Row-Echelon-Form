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

//���������Լ������
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

//���ĳ���׸�����Ԫ���Ƿ�Ϊ����Ϊ������1����Ϊ������0
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

//��ӡ������
void printMatrix(int** m, int r, int c) {
	for (int i = 0; i < r; i++){
		for (int j = 0; j < c; j++){
			printf("%5d", m[i][j]);
		}
		printf("\n");
	}
}

//�жϾ����Ƿ������н�����ʽ�����㷵��1�������㷵��0
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

//���������������ƶ�����1�����ƶ�����0
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
	printf("ע�⣺�˰汾Ϊ���԰汾�����������ܲ���ȷ�������ο���\n");
	int row, column, **matrix, i, j, processRowPoint = 0, processColumnPoint = 0, step = 0, *stepPoint = &step, operated = 0, max_gys, min_gbs, muiltiple;
	printf("����������С[row] [column]:");
	scanf("%d %d", &row, &column);//��ȡ�����С
	matrix = (int**)malloc(sizeof(int*)*row);
	for (i = 0; i < row; i++) {
		matrix[i] = (int*)malloc(sizeof(int)*column);
	}//�����û���������ά����ռ�
	printf("���������Ԫ��[element_1] [element_2] ... [element_n]:\n");
	for (i = 0; i < row; i++){
		for (j = 0; j < column; j++){
			scanf("%d", &matrix[i][j]);
		}
	}//��ȡ����Ԫ��
	printf("\n����Ԫ�ػ�ȡ��ϣ�����Ӧ������ʾ��\n");
	printMatrix(matrix, row, column);
	printf("\n���ڿ�ʼ�������ʹ���Ϊ�н����;���\n");
	if (isFormed(matrix, row, column)) {
		printf("\n�����Ѿ������н�����ʽ��������ϡ�");
		exit(0);
	}
	while (!isFormed(matrix, row, column)) {
		operated = 0;
		if (sortMatrix(matrix, row, column)) {
			printf("\nStep %d >> ���ɴ��н���\n", ++step);
			printMatrix(matrix, row, column); operated++;
		}
		//ȷ���д���ο�
		for (i = 0; i < column; i++) {
			if (matrix[processRowPoint][i] != 0) {
				processColumnPoint = i;
				break;
			}
		}
		//�����������Ƿ�Ϊ��
		for (i = 0; i < row; i++) {
			if (row_beginWithNegative(matrix, i, column)) {
				for (j = 0; j < column; j++) {
					matrix[i][j] *= -1;
				}
				printf("\nStep %d >> Row.%d * (-1)\n", ++step, i + 1);
				printMatrix(matrix, row, column); operated++;
			}
		}
		//�������Ƿ�ӵ�д���1�����Լ��
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
		//��ʼ����
		for (i = processRowPoint + 1; i < row; i++) {
			if (matrix[i][processColumnPoint] && matrix[processRowPoint][processColumnPoint]) {//����Ƿ���0
				if (matrix[i][processColumnPoint] == matrix[processRowPoint][processColumnPoint]) {//��������
					for (j = 0; j < column; j++) {
						matrix[i][j] -= matrix[processRowPoint][j];
					}
					printf("\nStep %d >> Row.%d - Row.%d\n", ++step, i + 1, processRowPoint + 1);
					printMatrix(matrix, row, column); operated++;
				}
				else {//�������ȳ˺��
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
		//�����������Ƿ�Ϊ��
		for (i = 0; i < row; i++) {
			if (row_beginWithNegative(matrix, i, column)) {
				for (j = 0; j < column; j++) {
					matrix[i][j] *= -1;
				}
				printf("\nStep %d >> Row.%d * (-1)\n", ++step, i + 1);
				printMatrix(matrix, row, column); operated++;
			}
		}
		//�������Ƿ�ӵ�д���1�����Լ��
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
	printf("\n�����Ѿ������н�����ʽ��������ϡ�");
	system("pause");
	return 0;
}