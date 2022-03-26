#include<stdio.h>
#include <math.h>
typedef long long ll;

ll giaiThua(ll n);
ll tongGiaiThua(ll n);
ll fibonanci(ll n);
void printNumberEven();
int main() {
	printf("_______________________________ Bai Tap Ve Nha _______________________________\n");
	printf("1/ Tinh n giai thua\n");
	printf("2/ tinh tong giai thua tu 1 den n\n");
	printf("3/ In ra n so fibonanci dau tien\n");
	printf("4/ In ra cac so chan tu 2 den 100 tren 10 dong\n");
	printf("5/ Ket thuc\n");
	printf("---------------------------------------------------------------------------\n");
	while (1) {
		ll x, y, z;
		printf("Chon chuc nang ban muon thuc hien:\n");
		int n;
		scanf("%d", &n);
		switch (n)
		{
		case 1:
			printf("Nhap so n: ");
			scanf("%lld", &x);
			printf("Giai thua cua n vua nhap la: %lld", giaiThua(x));
			printf("\n\n");
			break;
		case 2:
			printf("Nhap so n: ");
			scanf("%lld", &y);
			printf("Tong gia thua tu 1 den n vua nhap la: %lld \n", tongGiaiThua(y));
			printf("\n\n");
			break;
		case 3:
			printf("Nhap so n: ");
			scanf("%lld", &z);
			printf("N so fibonanci dau tien la: ");
			for (int i = 1; i <= z; i++) {
				printf("%lld ", fibonanci(i));
			}
			printf("\n\n");
			break;
		case 4:
			printf("Cac so chan tu 2 -> 100 tren 10 dong la\n");
			printNumberEven();
			printf("\n\n");
			break;
		case 5:
			exit(0);
		default:
			printf("Ban khong chon dung chuc nang! Moi nhap lai\n\n");
			break;
		}
	}
}

ll giaiThua(ll n) {
	if (n == 0)
		return 1;
	return n * giaiThua(n - 1);
}

ll tongGiaiThua(ll n) {
	ll s = 0;
	for (ll i = 1; i <= n; i++) {
		s += giaiThua(i);
	}
	return s;
}
ll fibonanci(ll n) {
	return (pow((1 + sqrt(5)), n) - pow((1 - sqrt(5)), n)) / (pow(2, n) * sqrt(5));
}
void printNumberEven() {
	int d = 0;
	for (int i = 2; i <= 100; i++) {
		if (i & 1)
			continue;
		printf("%d ", i);
		d++;
		if (d % 5 == 0)
			printf("\n");
	}
}
