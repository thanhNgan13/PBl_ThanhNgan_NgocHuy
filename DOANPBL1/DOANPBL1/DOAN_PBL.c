#include <stdio.h>
#include <math.h> 
#include <stdlib.h>
#include <Windows.h>
#include <wchar.h>
#include <fcntl.h> 
#include <io.h>    
#pragma warning(disable : 4996)
typedef long double lb;
typedef struct {
	lb Elements[100];
	int last;
}List;
lb X[2];
int check = 1;
wchar_t m[6][100] = { L"1/ Đọc n, các phần tử của vector x, vector y từ file." ,L"2/ Đọc n, các phần tử của vector x, vector y từ bàn phím." ,L"3/ In kết quả hệ số a, b ra màn hình." ,L"4/ Lưu kết quả hệ số a, b vào file." ,L"5/ Xem chi tiết các bước giải." ,L"6/ Quay lại." };
void makeNull_List(List* L);
int endList(List L);
void insertList(lb x, int position, List* L);
void readListFromFile(List* listX, List* listY);
void readListFromKeyboard(List* listX, List* listY);
void writeTheAnswerInTheScreen1(List listX, List listY);
void writeTheAnswerInTheScreen2(List listX, List listY);
void writeTheAnswerToTheFile1(List listX, List listY);
void writeTheAnswerToTheFile2(List listX, List listY);
void solutionStepSetails1(List listX, List listY);
void solutionStepSetails2(List listX, List listY);
void result1(List listX, List listY);
void result2(List listX, List listY);
void call1(List Lx, List Ly);
void call2(List Lx, List Ly);
lb summation(lb* A, int n);
lb multiplication(lb* A, lb* B, int n);
lb sumOfSquares(lb* A, int n);
void logarithm(lb* A, int n);
void logarithmE(lb* A, int n);
void cramer(lb a, lb b, lb x, lb c, lb d, lb y);
int checkList(List listX, List listY);
void display(List listX, List listY);
void SetColor(WORD color);
void removeTheLastCharacter(wchar_t* x);
int main() {
	List Lx, Ly;
	makeNull_List(&Lx); makeNull_List(&Ly);
	_setmode(_fileno(stdout), _O_U8TEXT);
	_setmode(_fileno(stdin), _O_U8TEXT);
	SetColor(10);  wprintf(L"______________________________ PBL1: Dự án lập trình tính toán ______________________________\nTên đề tài: 910\nNgười thực hiện:\n\tPhan Thành Ngân\n\tNguyễn Ngọc Huy\n_____________________________________________________________________________________________\n");
	system("pause");
	wchar_t m[3][50] = { L"1) Bài toán 1: biểu thức f(x)=ax^b." ,L"2) Bài toán 2: biểu thức f(x)=ae^bx." ,L"3) Thoát" };
	int vitri = 0;
	do {
		system("cls");
		SetColor(8); wprintf(L"Xây dựng các biểu thức dạng phi tuyến tính bằng phương pháp bình phương tối thiểu. \n");
		for (int i = 0; i < 3; i++) {
			if (i == vitri) {
				SetColor(5); wprintf(L">> %s <<\n", m[i]);
			}
			else {
				SetColor(6); wprintf(L"%s\n", m[i]);
			}
		}
		int flag = 0;
		while (1) {
			char key = getch();
			switch (key)
			{
			case 13:
				switch (vitri)
				{
				case 0:
					call1(Lx, Ly); system("pause"); break;
				case 1:
					call2(Lx, Ly); system("pause"); break;
				case 2:
					exit(1); break;
				}
				flag = 1; break;
			case 49:
				vitri = 0; flag = 1; break;
			case 50:
				vitri = 1; flag = 1; break;
			case 51:
				vitri = 2; flag = 1; break;
			case 72:
				vitri--; flag = 1; break;
			case 80:
				vitri++; flag = 1;
			}
			if (vitri < 0) {
				vitri += 3;
			}
			vitri = vitri % 3;
			if (flag) {
				break;
			}
		}
	} while (1);
	return 0;
}
void makeNull_List(List* L) {
	L->last = 0;
}
int endList(List L) {
	return L.last + 1;
}
void insertList(lb x, int position, List* L) {
	for (int i = L->last; i >= position; i--)
		L->Elements[i] = L->Elements[i - 1];
	L->Elements[position - 1] = x;
	L->last++;
}
void readListFromFile(List* listX, List* listY) {
	int len;
	int dem = 1;
	makeNull_List(listX); makeNull_List(listY);
	FILE* myFile = NULL;
	do
	{
		dem++;
		wchar_t name[50];
		wprintf(L"Nhập đường dẫn hoặc tên file. Nhập 0 để thoát chức năng này\n");
		fflush(stdin);
		fgetws(name, sizeof(name), stdin);
		removeTheLastCharacter(name);
		myFile = _wfopen(name, L"r");
		if (wcsncmp(name, L"0", 2) == 0) {
			check = 0; return;
		}
		if (dem == 10) {
			wprintf(L"Bạn đã bị cưỡng chế thoát vì nhập sai quá nhiều!!!\n"); check = 0; return;
		}
	} while (myFile == NULL);
	check = 1;
	fwscanf(myFile, L"%d", &len);
	lb** A = malloc(2 * sizeof(lb*));
	for (int i = 0; i < 2; i++) {
		A[i] = malloc(len * sizeof(lb));
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < len; j++) {
			fwscanf(myFile, L"%Lf", &A[i][j]);
		}
	}
	for (int i = 0; i < len; i++) {
		insertList(A[0][i], endList(*listX), listX);
		insertList(A[1][i], endList(*listY), listY);
	}
	for (int i = 0; i < 2; i++) {
		free(A[i]);
	}
	free(A);
	fclose(myFile);
}
void readListFromKeyboard(List* listX, List* listY) {
	int n;
	lb x, y;
	makeNull_List(listX); makeNull_List(listY);
	wprintf(L"Nhập n số lượng các phần tử của x và y: ");
	wscanf_s(L"%d", &n);
	if (n < 2) {
		return;
	}
	else {
		for (int i = 0; i < n; i++) {
			wprintf(L"Nhập phần tử thứ %d của x:\t", i + 1);
			wscanf_s(L"%Lf", &x);
			if (x <= 0) {
				return;
			}
			else
				insertList(x, endList(*listX), listX);
		}
		for (int i = 0; i < n; i++) {
			wprintf(L"Nhập phần tử thứ %d của y:\t", i + 1);
			wscanf_s(L"%Lf", &y);
			if (y <= 0) {
				return;
			}
			else
				insertList(y, endList(*listY), listY);
		}
	}
}
void writeTheAnswerInTheScreen1(List listX, List listY) {
	result1(listX, listY); wprintf(L"a = %0.3Lf\tb = %0.3Lf\t\n\n", pow(10, X[0]), X[1]);
}
void writeTheAnswerInTheScreen2(List listX, List listY) {
	result2(listX, listY); wprintf(L"a = %0.3Lf\tb = %0.3Lf\t\n\n", exp(X[0]), X[1]);
}
void writeTheAnswerToTheFile1(List listX, List listY) {
	result1(listX, listY);
	FILE* myFile;
	int dem = 1;
	do
	{
		wchar_t name[50];
		wprintf(L"Nhập đường dẫn hoặc tên file cần lưu kết quả. Nhập 0 để thoát chức năng này\n");
		fflush(stdin);
		fgetws(name, sizeof(name), stdin);
		removeTheLastCharacter(name);
		myFile = _wfopen(name, L"w+");
		dem++;
		if (wcsncmp(name, L"0", 2) == 0) { 
			check = 0; return;
		}
		if (dem == 10) {
			wprintf(L"Bạn đã bị cưỡng chế thoát vì nhập sai quá nhiều!!!\n"); check = 0;
			return;
		}
	} while (myFile == NULL);
	fwprintf(myFile, L"%c = %0.3Lf\t%c = %0.3Lf", 'a', pow(10, X[0]), 'b', X[1]);
	fclose(myFile);
	wprintf(L"\nĐã ghi file thành công\n");
}
void writeTheAnswerToTheFile2(List listX, List listY) {
	result2(listX, listY);
	FILE* myFile;
	int dem = 1;
	do
	{
		dem++;
		wchar_t name[50];
		wprintf(L"Nhập đường dẫn hoặc tên file cần lưu kết quả. Nhập 0 để thoát chức năng này\n");
		fflush(stdin);
		fgetws(name, sizeof(name), stdin);
		removeTheLastCharacter(name);
		myFile = _wfopen(name, L"w+");
		if (wcsncmp(name, L"0", 2) == 0) {
			return;
		}
		if (dem == 10) {
			wprintf(L"Bạn đã bị cưỡng chế thoát vì nhập sai quá nhiều!!!\n"); return;
		}
	} while (myFile == NULL);
	fwprintf(myFile, L"%c = %0.3Lf\t%c = %0.3Lf", 'a', exp(X[0]), 'b', X[1]);
	fclose(myFile);
	wprintf(L"\nĐã ghi file thành công\n");
}
void solutionStepSetails1(List listX, List listY) {
	wprintf(L"Các bước giải gồm: \nQuy định kí hiệu:  Sigma = '[' \nBan đầu ta có \n");
	display(listX, listY);
	wprintf(L"Bước 1: \nLấy Logarit cơsố 10 hai vế: Lgy = lga + blgx \nĐặt Y = lgy; A = lga; B = b; X = lgx \nTa đưa về dạng:\tY = A + BX\n");
	result1(listX, listY);
	logarithm(listX.Elements, listX.last);
	logarithm(listY.Elements, listX.last);
	display(listX, listY);
	wprintf(L"Bước 2: \nTính [Xi : [Xi = %0.3Lf\nTính [Xi^2 : [Xi^2 = %0.3Lf\nTính [XiYi : [XiYi = %0.3Lf\nTính [Yi : [Yi = %0.3Lf\n\n", summation(listX.Elements, listX.last), sumOfSquares(listX.Elements, listX.last), multiplication(listX.Elements, listY.Elements, listX.last), summation(listY.Elements, listX.last));
	wprintf(L"Bước 3: \nPhương pháp bình phương bé nhất: A, B là nghiệm hệ phương trình\n\tn*A + B*[Xi = [Yi \n\t[Xi*A + B *[Xi^2 = [XiYi \n<=>\n");
	wprintf(L"\t%d*A + B*%0.3Lf = %0.3Lf \n", listX.last, summation(listX.Elements, listX.last), summation(listY.Elements, listX.last));
	wprintf(L"\t%0.3Lf*A + B*%0.3Lf = %0.3Lf \n", summation(listX.Elements, listX.last), sumOfSquares(listX.Elements, listX.last), multiplication(listX.Elements, listY.Elements, listX.last));
	wprintf(L"Giải hệ phương trình ta được: A = %0.3Lf,\tB = %0.3Lf \n\n", X[0], X[1]);
	wprintf(L"Suy ra: a = 10^A = %0.3Lf,\tb = B = %0.3Lf\n\n", pow(10, X[0]), X[1]);
}
void solutionStepSetails2(List listX, List listY) {
	wprintf(L"Các bước giải gồm: \nQuy định kí hiệu:  Sigma = '[' \nBan đầu ta có \n");
	display(listX, listY);
	wprintf(L"Bước 1: \nLấy Logarit hai vế: lny = lna + bx \nĐặt Y = lny; A = lna; B = b; X = x \nTa đưa về dạng:\tY = A + BX\n");
	result2(listX, listY);
	logarithmE(listY.Elements, listX.last);
	display(listX, listY);
	wprintf(L"Bước 2: \nTính [Xi : [Xi = %0.3Lf\nTính [Xi^2 : [Xi^2 = %0.3Lf\nTính [XiYi : [XiYi = %0.3Lf\nTính [Yi : [Yi = %0.3Lf\n\n", summation(listX.Elements, listX.last), sumOfSquares(listX.Elements, listX.last), multiplication(listX.Elements, listY.Elements, listX.last), summation(listY.Elements, listX.last));
	wprintf(L"Bước 3: \nPhương pháp bình phương bé nhất: A, B là nghiệm hệ phương trình\n\tn*A + B*[Xi = [Yi \n\t[Xi*A + B *[Xi^2 = [XiYi \n<=>\n");
	wprintf(L"\t%d*A + B*%0.3Lf = %0.3Lf \n", listX.last, summation(listX.Elements, listX.last), summation(listY.Elements, listX.last));
	wprintf(L"\t%0.3Lf*A + B*%0.3Lf = %0.3Lf \n", summation(listX.Elements, listX.last), sumOfSquares(listX.Elements, listX.last), multiplication(listX.Elements, listY.Elements, listX.last));
	wprintf(L"Giải hệ phương trình ta được: A = %0.3Lf,\tB = %0.3Lf \n\n", X[0], X[1]);
	wprintf(L"Suy ra: a = e^A = %0.3Lf,\tb = B = %0.3Lf\n\n", exp(X[0]), X[1]);
}
void result1(List listX, List listY) {
	logarithm(listX.Elements, listX.last);
	logarithm(listY.Elements, listX.last);
	cramer((lb)listX.last, summation(listX.Elements, listX.last), summation(listY.Elements, listX.last), summation(listX.Elements, listX.last), sumOfSquares(listX.Elements, listX.last), multiplication(listX.Elements, listY.Elements, listX.last));
}
void result2(List listX, List listY) {
	logarithmE(listY.Elements, listX.last);
	cramer((lb)listX.last, summation(listX.Elements, listX.last), summation(listY.Elements, listX.last), summation(listX.Elements, listX.last), sumOfSquares(listX.Elements, listX.last), multiplication(listX.Elements, listY.Elements, listX.last));
}
void call1(List Lx, List Ly) {
	int vitri = 0;
	int dem = 1;
	do {
		system("cls");
		SetColor(8); wprintf(L"Các chức năng của chương trình\n");
		for (int i = 0; i < 6; i++) {
			if (i == vitri) {
				SetColor(5); wprintf(L">> %s <<\n", m[i]);
			}
			else {
				SetColor(6); wprintf(L"%s\n", m[i]);
			}
		}
		SetColor(10);
		int flag = 0;
		while (1) {
			char key = getch();
			switch (key)
			{
			case 13:
				system("cls");
				switch (vitri)
				{
				case 0:
					readListFromFile(&Lx, &Ly);
					if (check == 0) {}
					else {
						if (checkList(Lx, Ly) == 0) {
							wprintf(L"\nLỗi dữ liệu trong file\n");
						}
						else {
							wprintf(L"\nĐọc dữ liệu trong file thành công\n");
							display(Lx, Ly);
						}
					}
					system("pause"); break;
				case 1:
					readListFromKeyboard(&Lx, &Ly);
					if (checkList(Lx, Ly) == 0) {
						wprintf(L"\nLỗi dữ liệu\n");
					}
					else {
						wprintf(L"\nĐọc dữ liệu trong file thành công\n");
						display(Lx, Ly);
					}
					system("pause"); break;
				case 2:
					if (checkList(Lx, Ly) == 0) {
						wprintf(L"Vui lòng hãy nhập dữ liệu trước khi sử dụng chứ năng\n\n"); system("pause");
					}
					else {
						writeTheAnswerInTheScreen1(Lx, Ly); system("pause");
					}
					break;
				case 3:
					if (checkList(Lx, Ly) == 0) {
						wprintf(L"Vui lòng hãy nhập dữ liệu trước khi sử dụng chứ năng\n\n"); system("pause");
					}
					else {
						writeTheAnswerToTheFile1(Lx, Ly); system("pause");
					}
					break;
				case 4:
					if (checkList(Lx, Ly) == 0) {
						wprintf(L"Vui lòng hãy nhập dữ liệu trước khi sử dụng chứ năng\n\n"); system("pause");
					}
					else {
						solutionStepSetails1(Lx, Ly); system("pause");
					}
					break;
				case 5:
					dem = 0; break;
				}
				flag = 1; break;
			case 49:
				vitri = 0; flag = 1; break;
			case 50:
				vitri = 1; flag = 1; break;
			case 51:
				vitri = 2; flag = 1; break;
			case 52:
				vitri = 3; flag = 1; break;
			case 53:
				vitri = 4; flag = 1; break;
			case 54:
				vitri = 5; flag = 1; break;
			case 72:
				vitri--; flag = 1; break;
			case 80:
				vitri++; flag = 1;
			}
			if (vitri < 0) {
				vitri += 6;
			}
			vitri = vitri % 6;
			if (flag) {
				break;
			}
		}
	} while (dem != 0);
}
void call2(List Lx, List Ly) {
	int vitri = 0;
	int dem = 1;
	do {
		system("cls");
		SetColor(8); wprintf(L"Các chức năng của chương trình\n");
		for (int i = 0; i < 6; i++) {
			if (i == vitri) {
				SetColor(5); wprintf(L">> %s <<\n", m[i]);
			}
			else {
				SetColor(6); wprintf(L"%s\n", m[i]);
			}
		}
		SetColor(10);
		int flag = 0;
		while (1) {
			char key = getch();
			switch (key)
			{
			case 13:
				system("cls");
				switch (vitri)
				{
				case 0:
					readListFromFile(&Lx, &Ly);
					if (check == 0) {}
					else {
						if (checkList(Lx, Ly) == 0) {
							wprintf(L"\nLỗi dữ liệu trong file\n");
						}
						else {
							wprintf(L"\nĐọc dữ liệu trong file thành công\n");
							display(Lx, Ly);
						}
					}
					system("pause");
					break;
				case 1:
					readListFromKeyboard(&Lx, &Ly);
					if (checkList(Lx, Ly) == 0) {
						wprintf(L"\nLỗi dữ liệu trong file\n");
					}
					else {
						wprintf(L"\nĐọc dữ liệu trong file thành công\n");
						display(Lx, Ly);
					}
					system("pause");
					break;
				case 2:
					if (checkList(Lx, Ly) == 0) {
						wprintf(L"Vui lòng hãy nhập dữ liệu trước khi sử dụng chứ năng\n\n"); system("pause");
					}
					else {
						writeTheAnswerInTheScreen2(Lx, Ly); system("pause");
					}
					break;
				case 3:
					if (checkList(Lx, Ly) == 0) {
						wprintf(L"Vui lòng hãy nhập dữ liệu trước khi sử dụng chứ năng\n\n"); system("pause");
					}
					else {
						writeTheAnswerToTheFile2(Lx, Ly); system("pause");
					}
					break;
				case 4:
					if (checkList(Lx, Ly) == 0) {
						wprintf(L"Vui lòng hãy nhập dữ liệu trước khi sử dụng chứ năng\n\n"); system("pause");
					}
					else {
						solutionStepSetails2(Lx, Ly); system("pause");
					}
					break;
				case 5:
					dem = 0; break;
				}
				flag = 1; break;
			case 49:
				vitri = 0; flag = 1; break;
			case 50:
				vitri = 1; flag = 1; break;
			case 51:
				vitri = 2; flag = 1; break;
			case 52:
				vitri = 3; flag = 1; break;
			case 53:
				vitri = 4; flag = 1; break;
			case 54:
				vitri = 5; flag = 1; break;
			case 72:
				vitri--; flag = 1; break;
			case 80:
				vitri++; flag = 1;
			}
			if (vitri < 0) {
				vitri += 6;
			}
			vitri = vitri % 6;
			if (flag) {
				break;
			}
		}
	} while (dem != 0);
}
lb summation(lb* A, int n) {
	lb s = 0;
	for (int i = 0; i < n; i++) {
		s += *(A + i);
	}
	return s;
}
lb sumOfSquares(lb* A, int n) {
	lb s = 0;
	for (int i = 0; i < n; i++) {
		s += pow(*(A + i), 2);
	}
	return s;
}
lb multiplication(lb* A, lb* B, int n) {
	lb s = 0;
	for (int i = 0; i < n; i++) {
		s += *(A + i) * *(B + i);
	}
	return s;
}
void logarithm(lb* A, int n) {
	for (int i = 0; i < n; i++) {
		*(A + i) = (lb)log10(*(A + i));
	}
}
void logarithmE(lb* A, int n) {
	for (int i = 0; i < n; i++) {
		*(A + i) = (lb)log(*(A + i));
	}
}
void cramer(lb a, lb b, lb x, lb c, lb d, lb y) {
	X[0] = (x * d - b * y) / (a * d - b * c);
	X[1] = (a * y - c * x) / (a * d - b * c);
}
int checkList(List listX, List listY) {
	int dx = 0, dy = 0;
	for (int i = 0; i < listX.last; i++) {
		if (listX.Elements[i] == -6277438562204192487878988888393020692503707483087375482269988814848.000 || listX.Elements[i] <= 0) {
			dx++;
		}
	}
	for (int i = 0; i < listX.last; i++) {
		if (listY.Elements[i] == -6277438562204192487878988888393020692503707483087375482269988814848.000 || listY.Elements[i] <= 0) {
			dy++;
		}
	}
	return (dx != 0 || dy != 0 || listX.last < 2 || listY.last < 2) ? 0 : 1;
}
void display(List listX, List listY) {
	int len = listX.last;
	wprintf(L"\nn = %d\n", len);
	wprintf(L"X\t|\t");
	for (int i = 0; i < len; i++) {
		wprintf(L"%0.3Lf ", listX.Elements[i]);
	}
	wprintf(L"\nY\t|\t");
	for (int i = 0; i < len; i++) {
		wprintf(L"%0.3Lf ", listY.Elements[i]);
	}
	wprintf(L"\n\n");
}
void SetColor(WORD code)
{
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, code);
}
void removeTheLastCharacter(wchar_t* x) {
	size_t len = wcslen(x);
	if (x[len - 1] == '\n') {
		x[len - 1] = '\0';
	}
}
