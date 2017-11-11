#include "stdio.h"
#include "balance.h"
#include <stdlib.h>
#include <conio.h>
#include <memory.h>

#pragma warning(disable : 4996)
void Find_Coin();

int main()
{
   initialize();
   Find_Coin();
   return 0;
}

void Find_Coin()
{
   int GoodCoin[2] = { -1,-1 };
   int BadCoin[100] = { -1, }; //�ҷ����� �迭
   for (int i = 0; i < 100; i++)
      BadCoin[i] = -1;
   int UnknownCoin[100];        //�Ǻ��Ұ� ���� �迭 : ������ �˻��� �� ���� �ε��� �迭
   for (int i = 0; i < 100; i++)
      UnknownCoin[i] = i;
   int RestCoin[100] = { -1 };   //�˻� for���� �� �ڿ� �Ǻ��Ұ��� ������ ������ �迭
   int empty[1] = { -1 };

   int B_array_size = 1;   //�ҷ����� �迭 ������
   int R_array_size = 1;   //Rest�迭 ������

   int result;

   int a[2] = { 0, -1 };
   int b[2] = { 0, -1 };
   int c[2] = { 0, -1 };

   for (int j = 0; j < 100; j++)//Rest�迭 �ʱ�ȭ
      RestCoin[j] = -1;

   for (int i = 0; i < 100; i++)//Rest�迭�� ���� ����ų ������
   {
      a[0] = UnknownCoin[i++];
      b[0] = UnknownCoin[i++];
      c[0] = UnknownCoin[i];


      //i���� 100�� �Ѱ� �Ǹ� ������ ���Ҹ� Rest�迭�� �ְ� for�� Ż��
      if (i >= 100)
      {
         R_array_size++;
         RestCoin[R_array_size - 2] = 99;
         break;
      }

      result = balance(a, b, c);
      if (result == ONE)
      {
         GoodCoin[0] = a[0];
         B_array_size += 2;
         BadCoin[B_array_size - 3] = UnknownCoin[i - 1];
         BadCoin[B_array_size - 2] = UnknownCoin[i];
      }

      else if (result == TWO)
      {
         GoodCoin[0] = b[0];
         B_array_size += 2;
         BadCoin[B_array_size - 3] = UnknownCoin[i - 2];
         BadCoin[B_array_size - 2] = UnknownCoin[i];
      }

      else if (result == THREE)
      {
         GoodCoin[0] = c[0];
         B_array_size += 2;
         BadCoin[B_array_size - 3] = UnknownCoin[i - 2];
         BadCoin[B_array_size - 2] = UnknownCoin[i - 1];
      }

      else if (result == EQUAL_ONETWO)
      {
         GoodCoin[0] = a[0];
         B_array_size++;
         BadCoin[B_array_size - 2] = UnknownCoin[i];
      }

      else if (result == EQUAL_TWOTHREE)
      {
         GoodCoin[0] = b[0];
         B_array_size++;
         BadCoin[B_array_size - 2] = UnknownCoin[i - 2];
      }

      else if (result == EQUAL_ONETHREE)
      {
         GoodCoin[0] = c[0];
         B_array_size++;
         BadCoin[B_array_size - 2] = UnknownCoin[i - 1];
      }
      //���� 3���� �� ���� ��� �� �������� �ҷ����� ��������
      //���� ���ϱ� ������ RestCoin�� �����صд�
      else if (result == EQUAL_ALL)
      {
         R_array_size += 3;
         for (int j = 2; j < 5; j++)
            RestCoin[R_array_size - j] = UnknownCoin[i - j + 2];
      }
   }
   /*      99���� ���� ���� ��   */
   if (RestCoin[99] != -1) {
      RestCoin[99] = 99;
      int Bad_Bad_Coin[101];   //�������� ?1�� �־���� �ϹǷ� 101�� �迭����
      memcpy(Bad_Bad_Coin, RestCoin, sizeof(RestCoin));
      Bad_Bad_Coin[100] = -1;
      if (balance(Bad_Bad_Coin, empty, empty) == SUCCESS)   exit();
      else   RestCoin[99] = -1; //������ ������ �������̹Ƿ� RestCoin���� ����
   }

   //���� �𸣴� ������ �� �����ϰ��̶� �����ϰ� ���￡ �ѹ� �÷�����
   //�� ���� �ҷ��������� �������� ���� ��츦 ����ؼ� �־�� ���̴�.
   if (balance(BadCoin, empty, empty) == SUCCESS) exit(1);

   //Rest�迭�� Unknown�迭�� ����
   memcpy(UnknownCoin, RestCoin, sizeof(RestCoin));

   R_array_size = 1;
   
   for (int j = 0; j < 100; j++)//Rest�迭 �ʱ�ȭ
      RestCoin[j] = -1;
   int a_1[3] = { 0,0, -1 };
   int b_1[3] = { 0,0, -1 };
   int c_1[3] = { 0,0, -1 };

   for (int i = 0; UnknownCoin[i] != -1; i += 12)
   {
      a_1[0] = UnknownCoin[i];
      a_1[1] = UnknownCoin[i + 3];
      b_1[0] = UnknownCoin[i + 6];
      b_1[1] = UnknownCoin[i + 9];
      c_1[0] = BadCoin[0];
      c_1[1] = GoodCoin[0];

      if (a_1[0] == -1)
         break;
      //UnKnownCoin�� ������ 3���� �������� ���
      else if (a_1[1] == -1) {
         if (balance(BadCoin, empty, empty) == SUCCESS) exit(1);
         else {
            B_array_size += 3;
            BadCoin[B_array_size - 2] = UnknownCoin[i + 2];
            BadCoin[B_array_size - 3] = UnknownCoin[i + 1];
            BadCoin[B_array_size - 4] = UnknownCoin[i];
         }
         break;
      }
      //UnKnownCoin�� ������ 6�� �������� ���
      if (b_1[0] == -1)
      {
         c[0] = BadCoin[0];
         a[0] = a_1[0];
         b[0] = a_1[1];

         result = balance(a, b, c);

         if (result == ONE) {
            B_array_size += 3;
            BadCoin[B_array_size - 2] = UnknownCoin[i + 5];
            BadCoin[B_array_size - 3] = UnknownCoin[i + 4];
            BadCoin[B_array_size - 4] = UnknownCoin[i + 3];
         }
         else if (result == TWO) {
            B_array_size += 3;
            BadCoin[B_array_size - 2] = UnknownCoin[i + 2];
            BadCoin[B_array_size - 3] = UnknownCoin[i + 1];
            BadCoin[B_array_size - 4] = UnknownCoin[i];
         }
         else if (result == EQUAL_ALL)
         {
            B_array_size += 3;
            BadCoin[B_array_size - 2] = UnknownCoin[i + 2];
            BadCoin[B_array_size - 3] = UnknownCoin[i + 1];
            BadCoin[B_array_size - 4] = UnknownCoin[i];

            B_array_size += 3;
            BadCoin[B_array_size - 2] = UnknownCoin[i + 5];
            BadCoin[B_array_size - 3] = UnknownCoin[i + 4];
            BadCoin[B_array_size - 4] = UnknownCoin[i + 3];
         }
         break;
      }
      //UnKnownCoin�� ������ 9�� �������� ���
      else if (b_1[1] == -1) {
         a[0] = UnknownCoin[i];
         b[0] = UnknownCoin[i + 3];
         c[0] = UnknownCoin[i + 6];
         result = balance(a, b, c);

         if (result == ONE)
         {
            B_array_size += 3;
            BadCoin[B_array_size - 2] = UnknownCoin[i + 5];
            BadCoin[B_array_size - 3] = UnknownCoin[i + 4];
            BadCoin[B_array_size - 4] = UnknownCoin[i + 3];

            B_array_size += 3;
            BadCoin[B_array_size - 2] = UnknownCoin[i + 8];
            BadCoin[B_array_size - 3] = UnknownCoin[i + 7];
            BadCoin[B_array_size - 4] = UnknownCoin[i + 6];
         }

         else if (result == TWO)
         {
            B_array_size += 3;
            BadCoin[B_array_size - 2] = UnknownCoin[i + 2];
            BadCoin[B_array_size - 3] = UnknownCoin[i + 1];
            BadCoin[B_array_size - 4] = UnknownCoin[i];

            B_array_size += 3;
            BadCoin[B_array_size - 2] = UnknownCoin[i + 8];
            BadCoin[B_array_size - 3] = UnknownCoin[i + 7];
            BadCoin[B_array_size - 4] = UnknownCoin[i + 6];
         }

         else if (result == THREE)
         {
            B_array_size += 3;
            BadCoin[B_array_size - 2] = UnknownCoin[i + 2];
            BadCoin[B_array_size - 3] = UnknownCoin[i + 1];
            BadCoin[B_array_size - 4] = UnknownCoin[i];

            B_array_size += 3;
            BadCoin[B_array_size - 2] = UnknownCoin[i + 5];
            BadCoin[B_array_size - 3] = UnknownCoin[i + 4];
            BadCoin[B_array_size - 4] = UnknownCoin[i + 3];
         }

         else if (result == EQUAL_ONETWO)
         {
            B_array_size += 3;
            BadCoin[B_array_size - 2] = UnknownCoin[i + 8];
            BadCoin[B_array_size - 3] = UnknownCoin[i + 7];
            BadCoin[B_array_size - 4] = UnknownCoin[i + 6];
         }

         else if (result == EQUAL_TWOTHREE)
         {
            B_array_size += 3;
            BadCoin[B_array_size - 2] = UnknownCoin[i + 2];
            BadCoin[B_array_size - 3] = UnknownCoin[i + 1];
            BadCoin[B_array_size - 4] = UnknownCoin[i];
         }

         else if (result == EQUAL_ONETHREE)
         {
            B_array_size += 3;
            BadCoin[B_array_size - 2] = UnknownCoin[i + 5];
            BadCoin[B_array_size - 3] = UnknownCoin[i + 4];
            BadCoin[B_array_size - 4] = UnknownCoin[i + 3];
         }
         else if (result == EQUAL_ALL) {
            //���� error�� �Ǵ°Ÿ� ���⼭ error�� ���ð�� ���� �ҷ��迭�� �ִ°ɷ�
            //error�� �ȵǴ°Ÿ� ���δ� ó�����ֱ�
            //�� �κж��� �ҷ��������� �������� �� ���� ��쿡
            //��Ƶ� �ҷ������� ���￡ �޾ƺ���
            if (balance(BadCoin, empty, empty) == SUCCESS) exit(1);
            //���� SUCCESS�� �ƴϸ� �𸣴� �������� �ҷ������̹Ƿ�
            //�ҷ����� �迭�� �ٽóְ� balance
            else {
               B_array_size += 3;
               BadCoin[B_array_size - 2] = UnknownCoin[i + 2];
               BadCoin[B_array_size - 3] = UnknownCoin[i + 1];
               BadCoin[B_array_size - 4] = UnknownCoin[i];

               B_array_size += 3;
               BadCoin[B_array_size - 2] = UnknownCoin[i + 5];
               BadCoin[B_array_size - 3] = UnknownCoin[i + 4];
               BadCoin[B_array_size - 4] = UnknownCoin[i + 3];

               B_array_size += 3;
               BadCoin[B_array_size - 2] = UnknownCoin[i + 8];
               BadCoin[B_array_size - 3] = UnknownCoin[i + 7];
               BadCoin[B_array_size - 4] = UnknownCoin[i + 6];


            }
         }

         break;

      }
      result = balance(a_1, b_1, c_1);   //c_1���� ����1�� ������1��

      if (result == ONE)   //a_1������ ���� �����ϴ°��
      {
         a[0] = b_1[0];   //b_1[0]���� i+6���� 
         b[0] = b_1[1];   //b_1[1]���� i+9����
         result = balance(a, b, GoodCoin);
         if (result == THREE) {
            B_array_size += 3;
            BadCoin[B_array_size - 2] = UnknownCoin[i + 8];
            BadCoin[B_array_size - 3] = UnknownCoin[i + 7];
            BadCoin[B_array_size - 4] = UnknownCoin[i + 6];

            B_array_size += 3;
            BadCoin[B_array_size - 2] = UnknownCoin[i + 11];
            BadCoin[B_array_size - 3] = UnknownCoin[i + 10];
            BadCoin[B_array_size - 4] = UnknownCoin[i + 9];


         }
         else if (result == EQUAL_ONETHREE) {
            B_array_size += 3;
            BadCoin[B_array_size - 2] = UnknownCoin[i + 11];
            BadCoin[B_array_size - 3] = UnknownCoin[i + 10];
            BadCoin[B_array_size - 4] = UnknownCoin[i + 9];
         }
         else if (result == EQUAL_TWOTHREE) {
            B_array_size += 3;
            BadCoin[B_array_size - 2] = UnknownCoin[i + 8];
            BadCoin[B_array_size - 3] = UnknownCoin[i + 7];
            BadCoin[B_array_size - 4] = UnknownCoin[i + 6];
         }
         else continue;
      }

      else if (result == TWO)
      {
         a[0] = a_1[0];
         b[0] = a_1[1];
         result = balance(a, b, GoodCoin);
         if (result == THREE) {
            B_array_size += 3;
            BadCoin[B_array_size - 2] = UnknownCoin[i + 2];
            BadCoin[B_array_size - 3] = UnknownCoin[i + 1];
            BadCoin[B_array_size - 4] = UnknownCoin[i];

            B_array_size += 3;
            BadCoin[B_array_size - 2] = UnknownCoin[i + 5];
            BadCoin[B_array_size - 3] = UnknownCoin[i + 4];
            BadCoin[B_array_size - 4] = UnknownCoin[i + 3];
         }
         else if (result == EQUAL_ONETHREE) {
            B_array_size += 3;
            BadCoin[B_array_size - 2] = UnknownCoin[i + 5];
            BadCoin[B_array_size - 3] = UnknownCoin[i + 4];
            BadCoin[B_array_size - 4] = UnknownCoin[i + 3];
         }
         else if (result == EQUAL_TWOTHREE) {
            B_array_size += 3;
            BadCoin[B_array_size - 2] = UnknownCoin[i + 2];
            BadCoin[B_array_size - 3] = UnknownCoin[i + 1];
            BadCoin[B_array_size - 4] = UnknownCoin[i];
         }
         else continue;
      }

      else if (result == THREE)
      {
         B_array_size += 3;
         BadCoin[B_array_size - 2] = UnknownCoin[i + 2];
         BadCoin[B_array_size - 3] = UnknownCoin[i + 1];
         BadCoin[B_array_size - 4] = UnknownCoin[i];

         B_array_size += 3;
         BadCoin[B_array_size - 2] = UnknownCoin[i + 5];
         BadCoin[B_array_size - 3] = UnknownCoin[i + 4];
         BadCoin[B_array_size - 4] = UnknownCoin[i + 3];

         B_array_size += 3;
         BadCoin[B_array_size - 2] = UnknownCoin[i + 8];
         BadCoin[B_array_size - 3] = UnknownCoin[i + 7];
         BadCoin[B_array_size - 4] = UnknownCoin[i + 6];

         B_array_size += 3;
         BadCoin[B_array_size - 2] = UnknownCoin[i + 11];
         BadCoin[B_array_size - 3] = UnknownCoin[i + 10];
         BadCoin[B_array_size - 4] = UnknownCoin[i + 9];
      }
      //c_1���� �ҷ������� �������� �ֱ⶧����
      //EQUAL_ONETWO�� ������ ���� a_1�� b_1�� ���� �������� ���Ѵ�
      else if (result == EQUAL_ONETWO)
      {
         continue;
      }

      else if (result == EQUAL_TWOTHREE)
      {
         B_array_size += 3;
         BadCoin[B_array_size - 2] = UnknownCoin[i + 2];
         BadCoin[B_array_size - 3] = UnknownCoin[i + 1];
         BadCoin[B_array_size - 4] = UnknownCoin[i];

         B_array_size += 3;
         BadCoin[B_array_size - 2] = UnknownCoin[i + 5];
         BadCoin[B_array_size - 3] = UnknownCoin[i + 4];
         BadCoin[B_array_size - 4] = UnknownCoin[i + 3];
         //b_1���� ����� �ҷ��� �ֱ⿡ ��󳽴�
         a[0] = b_1[0];
         b[0] = b_1[1];
         result = balance(a, b, GoodCoin);
         if (result == THREE) {
            B_array_size += 3;
            BadCoin[B_array_size - 2] = UnknownCoin[i + 8];
            BadCoin[B_array_size - 3] = UnknownCoin[i + 7];
            BadCoin[B_array_size - 4] = UnknownCoin[i + 6];

            B_array_size += 3;
            BadCoin[B_array_size - 2] = UnknownCoin[i + 11];
            BadCoin[B_array_size - 3] = UnknownCoin[i + 10];
            BadCoin[B_array_size - 4] = UnknownCoin[i + 9];


         }
         else if (result == EQUAL_ONETHREE) {
            B_array_size += 3;
            BadCoin[B_array_size - 2] = UnknownCoin[i + 11];
            BadCoin[B_array_size - 3] = UnknownCoin[i + 10];
            BadCoin[B_array_size - 4] = UnknownCoin[i + 9];
         }
         else if (result == EQUAL_TWOTHREE) {
            B_array_size += 3;
            BadCoin[B_array_size - 2] = UnknownCoin[i + 8];
            BadCoin[B_array_size - 3] = UnknownCoin[i + 7];
            BadCoin[B_array_size - 4] = UnknownCoin[i + 6];
         }
         else continue;

      }

      else if (result == EQUAL_ONETHREE)
      {
         B_array_size += 3;
         BadCoin[B_array_size - 2] = UnknownCoin[i + 8];
         BadCoin[B_array_size - 3] = UnknownCoin[i + 7];
         BadCoin[B_array_size - 4] = UnknownCoin[i + 6];

         B_array_size += 3;

         BadCoin[B_array_size - 4] = UnknownCoin[i + 9];

         if (UnknownCoin[i + 9] != 99)
         {
            BadCoin[B_array_size - 2] = UnknownCoin[i + 11];
            BadCoin[B_array_size - 3] = UnknownCoin[i + 10];
         }
         else             B_array_size -= 2;



         a[0] = a_1[0];
         b[0] = a_1[1];
         result = balance(a, b, GoodCoin);
         if (result == THREE) {
            B_array_size += 3;
            BadCoin[B_array_size - 2] = UnknownCoin[i + 2];
            BadCoin[B_array_size - 3] = UnknownCoin[i + 1];
            BadCoin[B_array_size - 4] = UnknownCoin[i];

            B_array_size += 3;
            BadCoin[B_array_size - 2] = UnknownCoin[i + 5];
            BadCoin[B_array_size - 3] = UnknownCoin[i + 4];
            BadCoin[B_array_size - 4] = UnknownCoin[i + 3];
         }
         else if (result == EQUAL_ONETHREE) {
            B_array_size += 3;
            BadCoin[B_array_size - 2] = UnknownCoin[i + 5];
            BadCoin[B_array_size - 3] = UnknownCoin[i + 4];
            BadCoin[B_array_size - 4] = UnknownCoin[i + 3];
         }
         else if (result == EQUAL_TWOTHREE) {
            B_array_size += 3;
            BadCoin[B_array_size - 2] = UnknownCoin[i + 2];
            BadCoin[B_array_size - 3] = UnknownCoin[i + 1];
            BadCoin[B_array_size - 4] = UnknownCoin[i];
         }
         else continue;
      }

      else if (result == EQUAL_ALL)
      {
         a[0] = a_1[0];
         b[0] = b_1[0];
         result = balance(a, b, GoodCoin);
         if (result == THREE) {
            B_array_size += 3;
            BadCoin[B_array_size - 2] = UnknownCoin[i + 2];
            BadCoin[B_array_size - 3] = UnknownCoin[i + 1];
            BadCoin[B_array_size - 4] = UnknownCoin[i];

            B_array_size += 3;
            BadCoin[B_array_size - 2] = UnknownCoin[i + 8];
            BadCoin[B_array_size - 3] = UnknownCoin[i + 7];
            BadCoin[B_array_size - 4] = UnknownCoin[i + 6];
         }
         else if (result == EQUAL_ALL) {
            B_array_size += 3;
            BadCoin[B_array_size - 2] = UnknownCoin[i + 5];
            BadCoin[B_array_size - 3] = UnknownCoin[i + 4];
            BadCoin[B_array_size - 4] = UnknownCoin[i + 3];

            B_array_size += 3;
            BadCoin[B_array_size - 2] = UnknownCoin[i + 11];
            BadCoin[B_array_size - 3] = UnknownCoin[i + 10];
            BadCoin[B_array_size - 4] = UnknownCoin[i + 9];
         }
         else if (result == EQUAL_TWOTHREE) {
            B_array_size += 3;
            BadCoin[B_array_size - 2] = UnknownCoin[i + 2];
            BadCoin[B_array_size - 3] = UnknownCoin[i + 1];
            BadCoin[B_array_size - 4] = UnknownCoin[i];

            B_array_size += 3;
            BadCoin[B_array_size - 2] = UnknownCoin[i + 11];
            BadCoin[B_array_size - 3] = UnknownCoin[i + 10];
            BadCoin[B_array_size - 4] = UnknownCoin[i + 9];
         }
         else if (result == EQUAL_ONETHREE) {
            B_array_size += 3;
            BadCoin[B_array_size - 2] = UnknownCoin[i + 5];
            BadCoin[B_array_size - 3] = UnknownCoin[i + 4];
            BadCoin[B_array_size - 4] = UnknownCoin[i + 3];

            B_array_size += 3;
            BadCoin[B_array_size - 2] = UnknownCoin[i + 6];
            BadCoin[B_array_size - 3] = UnknownCoin[i + 7];
            BadCoin[B_array_size - 4] = UnknownCoin[i + 8];
         }
      }
      else continue;
   }


   for (int j = 0; BadCoin[j] != -1; j++)
      printf("%2d ", BadCoin[j]);

   printf("\n");

   BadCoin[B_array_size - 1] = -1;
   printf("finish\n");
   balance(BadCoin, empty, empty);
   getch();
}

