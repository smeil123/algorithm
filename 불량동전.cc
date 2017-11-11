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
   int BadCoin[100] = { -1, }; //불량동전 배열
   for (int i = 0; i < 100; i++)
      BadCoin[i] = -1;
   int UnknownCoin[100];        //판별불가 동전 배열 : 실제로 검사할 때 넣을 인덱스 배열
   for (int i = 0; i < 100; i++)
      UnknownCoin[i] = i;
   int RestCoin[100] = { -1 };   //검사 for문을 돈 뒤에 판별불가로 남겨진 동전의 배열
   int empty[1] = { -1 };

   int B_array_size = 1;   //불량동전 배열 사이즈
   int R_array_size = 1;   //Rest배열 사이즈

   int result;

   int a[2] = { 0, -1 };
   int b[2] = { 0, -1 };
   int c[2] = { 0, -1 };

   for (int j = 0; j < 100; j++)//Rest배열 초기화
      RestCoin[j] = -1;

   for (int i = 0; i < 100; i++)//Rest배열의 끝을 가리킬 때까지
   {
      a[0] = UnknownCoin[i++];
      b[0] = UnknownCoin[i++];
      c[0] = UnknownCoin[i];


      //i값이 100이 넘게 되면 마지막 원소를 Rest배열에 넣고 for문 탈출
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
      //동전 3개가 다 같을 경우 이 동전들이 불량인지 정상인지
      //알지 못하기 때문에 RestCoin에 보류해둔다
      else if (result == EQUAL_ALL)
      {
         R_array_size += 3;
         for (int j = 2; j < 5; j++)
            RestCoin[R_array_size - j] = UnknownCoin[i - j + 2];
      }
   }
   /*      99개가 전부 같을 때   */
   if (RestCoin[99] != -1) {
      RestCoin[99] = 99;
      int Bad_Bad_Coin[101];   //마지막에 ?1을 넣어줘야 하므로 101개 배열선언
      memcpy(Bad_Bad_Coin, RestCoin, sizeof(RestCoin));
      Bad_Bad_Coin[100] = -1;
      if (balance(Bad_Bad_Coin, empty, empty) == SUCCESS)   exit();
      else   RestCoin[99] = -1; //마지막 동전은 정상동전이므로 RestCoin에서 제외
   }

   //아직 모르는 동전이 다 정상일것이라 가정하고 저울에 한번 올려본다
   //이 경우는 불량동전보다 정상동전이 많을 경우를 대비해서 넣어둔 것이다.
   if (balance(BadCoin, empty, empty) == SUCCESS) exit(1);

   //Rest배열을 Unknown배열에 복사
   memcpy(UnknownCoin, RestCoin, sizeof(RestCoin));

   R_array_size = 1;
   
   for (int j = 0; j < 100; j++)//Rest배열 초기화
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
      //UnKnownCoin에 동전이 3개가 남아있을 경우
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
      //UnKnownCoin에 동전이 6개 남아있을 경우
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
      //UnKnownCoin에 동전이 9개 남아있을 경우
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
            //만약 error가 되는거면 여기서 error가 나올경우 전부 불량배열에 넣는걸로
            //error가 안되는거면 전부다 처리해주기
            //이 부분또한 불량동전보다 정상동전이 더 많을 경우에
            //모아둔 불량동전만 저울에 달아본다
            if (balance(BadCoin, empty, empty) == SUCCESS) exit(1);
            //만약 SUCCESS가 아니면 모르는 동전또한 불량동전이므로
            //불량동전 배열에 다시넣고 balance
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
      result = balance(a_1, b_1, c_1);   //c_1에는 정상1개 비정상1개

      if (result == ONE)   //a_1에전부 정상만 존재하는경우
      {
         a[0] = b_1[0];   //b_1[0]에는 i+6부터 
         b[0] = b_1[1];   //b_1[1]에는 i+9부터
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
      //c_1에는 불량동전과 정상동전이 있기때문에
      //EQUAL_ONETWO가 나오는 것은 a_1과 b_1이 전부 정상임을 뜻한다
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
         //b_1에는 정상과 불량이 있기에 골라낸다
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

