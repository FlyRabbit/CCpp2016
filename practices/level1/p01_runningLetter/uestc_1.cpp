// uestc_1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "iostream"

int main()
{
	while (1)
	{
		char ch[2];
		ch[0] = 'E'; ch[1] = 'T';
		for (int i = 1; i <= 82; i++)
		{
			for (int j = 1; j <= i; j++)
				printf(" ");
			printf("%c%c", ch[0], ch[1]);
			system("cls");
		}
		for (int i = 1; i <= 82; i++)
		{
			for (int j = 82; j >= i; j--)
				printf(" ");
			printf("%c%c", ch[0], ch[1]);
			system("cls");
		}
	}
    return 0;
}

