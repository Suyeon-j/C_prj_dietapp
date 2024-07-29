//다이어트 어플
#include <stdio.h>
#include <stdlib.h>
#define MAX 50

void MainMenu();
int ReadInput();
int LogIn();
void Join();
void SubMenu();
void MyPage();
void CashMenu();
void Cash();
void AEdit();
void AEditMenu();
void ReadData();
void WriteData();
void BMI();
void DailyMenu();
void addrecord();
void viewrecord();
void editrecord();
void MyDaily();
void DailyReadData();
void DailyWriteData();

//구조체01 체중관리 프로그램
typedef struct daily {
	char date[7];
	float today_wgt;
}Daily;

//구조체 02 (회원정보 > 로그인 정보 저장)
typedef struct Inform {
	char id[8];
	char pwd[10];
	char name[10];
	int age;
	float hgt;
	float wgt;
	int cash;
	Daily* Daily[MAX];
	int numOfDaily;
}inform;
inform* informa[MAX];

//구조체 03 (다이어트 상품명, 가격)
struct product {
	int no;
	char p_name[40];
	int price;
};

struct product list[6];

int  numOfInform = 0;
numOfDaily = 0;
int inform_index;

int main()
{
	int input, input2;
	int i, gaesu, nnum;

	struct product list[6] = {
						{1,"닭가슴살 슬라이스 100g 10팩",17500},
						{2,"닭가슴살 스테이크 오리지널 100g 10팩",12000},
						{3,"단백질쉐이크 330mlx12개입",39600},
						{4,"단백질 보충제 1000g",36900},
						{5,"닭가슴살 야채 곤약 볶음밥 250g 20팩",44000},
						{6,"케이준 샐러드 160g",4300}
	};
	ReadData();
	do {
		MainMenu();
		input = ReadInput();
		switch (input)
		{
		case 1: //회원가입
			Join();
			break;
		case 2: //로그인
			LogIn();
			do {
				SubMenu();
				input2 = ReadInput();
				switch (input2)
				{
				case 1: //물건구매
					//상품내역 출력
					printf("\n다이어트 식품 =======\n");
					for (i = 0; i < 6; i++) {
						printf("%d. %s\n \t\t\t ----- %d원\n", i + 1, list[i].p_name, list[i].price);
					}
					printf("구매할 물건 번호와 수량을 입력하세요. > ");
					scanf_s("%d %d", &nnum, &gaesu);

					//구매 상품 목록 출력 후 수량 입력 받기
					printf("<구매내역>\n");
					printf("내용\t/\t수량\t/\t판매가\t/\t계\n");
					printf("%s \t/ %d개 \t/ %d\t/ %d원\n", list[nnum - 1].p_name, nnum, list[nnum - 1].price, list[nnum - 1].price * gaesu);
					printf("결제를 진행합니다.\n");

					if (list[nnum - 1].price * gaesu > informa[inform_index]->cash)
					{
						printf("캐쉬 잔액이 부족하여 출금할 수 없습니다.\n");
						printf("캐쉬 관리 페이지로 이동합니다.\n");
						Cash();
					}
					else
					{
						informa[inform_index]->cash -= list[nnum - 1].price * gaesu;
						printf("%d 캐쉬가 결제되어 잔액은 총 %d 캐쉬입니다.\n", list[nnum - 1].price * gaesu, informa[inform_index]->cash);
					}
					break;
				case 2: //마이페이지
					MyPage();
					//스위치
					input2 = ReadInput();
					switch (input2)
					{
					case 1:
						//01 BMI
						BMI();
						break;
					case 2:
						//02 하루의 기록 > 다이어리-파일 입출력함수
						MyDaily();
						break;
					case 3:
						//03 캐쉬 관리 > 은행 활용
						Cash();
						break;
					case 4:
						//04 회원정보 입력 및 수정(이름, 나이, 키, 몸무게, - 캐쉬) + 탈퇴
						AEdit();
						break;
					case 5:
						break;
					default:
						printf("\n다시 시도하세요.\n");
					}
					break;
				case 3: //시스템 종료
					WriteData();
					return 0;
					break;
				default:
					printf("\n다시 시도하세요.\n");
				}
			} while (1);
			break;
		case 3:
			WriteData();
			return 0;
			break;
		default:
			printf("\n다시 시도하세요.\n");
		}
	} while (1);
}

void ReadData()
{
	int i;
	FILE* fp;
	fopen_s(&fp, "inform.text", "rt");

	if (fp == NULL) {
		printf("파일 읽기 불가능\n");
		return;
	}
	fscanf_s(fp, "%d", &numOfInform);
	for (i = 0; i < numOfInform; i++)
	{
		informa[i] = (inform*)malloc(sizeof(inform));
		fscanf_s(fp, "%s %s %s %d %f %f %d", informa[i]->id, sizeof(informa[i]->id), informa[i]->pwd, sizeof(informa[i]->pwd), informa[i]->name, sizeof(informa[i]->name), &informa[i]->age, &informa[i]->hgt, &informa[i]->wgt, &informa[i]->cash);
	}
	fclose(fp);
}

void Join()
{
	informa[numOfInform] = (inform*)malloc(sizeof(inform));
	printf("아이디 > ");
	scanf_s("%s", informa[numOfInform]->id, sizeof(informa[numOfInform]->id));
	printf("비밀번호 > ");
	scanf_s("%s", informa[numOfInform]->pwd, sizeof(informa[numOfInform]->pwd));
	printf("이름 > ");
	scanf_s("%s", informa[numOfInform]->name, sizeof(informa[numOfInform]->name));
	printf("나이 > ");
	scanf_s("%d", &informa[numOfInform]->age);
	printf("키 > ");
	scanf_s("%f", &informa[numOfInform]->hgt);
	printf("몸무게 > ");
	scanf_s("%f", &informa[numOfInform]->wgt);

	informa[numOfInform++]->cash = 1000;
}

int LogIn()
{
	char id[10], pwd[10];
	int i, end = 0;

	do {
		printf("아이디를 입력하세요. > ");
		scanf_s("%s", id, sizeof(id));
		printf("비밀번호를 입력하세요. > ");
		scanf_s("%s", pwd, sizeof(pwd));
		for (i = 0; i < numOfInform; i++)
		{
			//로그인 성공
			if (!strcmp(id, informa[i]->id) && !strcmp(pwd, informa[i]->pwd))
			{
				printf("로그인 성공!\n");
				end = 1;
				break;
			}

			else if (!strcmp(id, informa[i]->id))
			{
				printf("다시 입력해주세요.\n");
			}
		}
		if (i == numOfInform)
		{
			printf("존재하지않는 회원입니다.\n");
		}
	} while (end != 1);
	if (end == 1)
		inform_index = i;
}

void MainMenu()
{
	//메인 메뉴- 회원가입/로그인/종료
	printf("\n<다이어트 어플>\n");
	printf("1. 회원가입\n");
	printf("2. 로그인\n");
	printf("3. 종료\n");
	printf("번호를 입력하세요 > ");
}

int ReadInput()
{
	int input;
	scanf_s("%d", &input);
	return input;
}

void SubMenu()
{
	printf("\n%s 님 환영합니다!\n", informa[inform_index]->name);
	printf("\n<다이어트 어플>\n");
	printf("1. 다이어트 식품 구매\n");
	printf("2. 마이페이지\n");
	printf("3. 어플 종료\n");
	printf("번호를 입력하세요 > ");
}

void MyPage()
{
	printf("\n<마이페이지>\n");
	printf("1. BMI\n");
	printf("2. 하루의 기록\n");
	printf("3. 캐쉬 관리\n");
	printf("4. 회원정보 수정\n");
	printf("5. 이전페이지\n");
	printf("번호를 입력하세요 > ");
}

void BMI()
{
	float bmi;
	float mheight;
	int hweight1, hweight2;

	mheight = (float)informa[inform_index]->hgt / 100;
	bmi = informa[inform_index]->wgt / (mheight * mheight);
	printf("<BMI지수>");
	printf("\nBMI 지수 = %.2f\n", bmi);

	if (0 <= bmi && bmi < 18.5)
		printf("%s님은 저체중입니다.", informa[inform_index]->name);
	else if (18.5 <= bmi && bmi < 23)
		printf("%s님은 정상 체중입니다.", informa[inform_index]->name);
	else if (23 <= bmi && bmi < 25)
		printf("%s님은 과체중입니다.", informa[inform_index]->name);
	else if (25 <= bmi && bmi < 30)
		printf("%s님은 비만입니다.", informa[inform_index]->name);
	else
		printf("%s님은 고도비만입니다.", informa[inform_index]->name);
	hweight1 = (int)18.5 * (mheight * mheight);
	hweight2 = (int)23 * (mheight * mheight);
	printf("\n%s님의 정상 몸무게의 범위는 %dkg ~ %dkg입니다.\n", informa[inform_index]->name, hweight1, hweight2);
}

void CashMenu()
{
	printf("\n<캐쉬 관리>\n");
	printf("1. 입금\n");
	printf("2. 출금\n");
	printf("3. 조회\n");
	printf("4. 다이어트 식품 구매 / 마이페이지로 이동\n");
	printf("번호를 입력하세요 > ");
}

void DailyReadData() {
	int i, j;
	FILE* fp;

	fopen_s(&fp, "mydailyrecord.text", "rt");
	
	//회원수 입력
	if (fp == NULL) {
		printf("파일 읽기 불가능");
		return;
	}
	for (j = 0; j < numOfInform; j++)
		for (i = 0; i < numOfDaily; i++)
			fscanf_s(fp, "%s %f", informa[j]->Daily[i]->date, sizeof(informa[j]->Daily[i]->date), &informa[j]->Daily[i]->today_wgt);
	fclose(fp);
}

void DailyWriteData() {
	int i;
	FILE* fp;

	fopen_s(&fp, "mydailyrecord.text", "wt");
	if (fp == NULL) {
		printf("파일 쓰기 불가능");
		return;
	}

	for (i = 0; i < numOfDaily; i++)
		fprintf(fp, "%s %f\n",informa[inform_index]->Daily[i]->date, informa[inform_index]->Daily[i]->today_wgt);
	fclose(fp);
}

void MyDaily()
{
	int choice;
	DailyReadData();
	do
	{
		DailyMenu();
		choice = ReadInput();
		switch (choice)
		{
		case 1:
			addrecord();
			DailyWriteData();
			break;
		case 2:
			viewrecord();
			break;
		case 3:
			editrecord();
			DailyWriteData();
			break;
		case 4:
			return;
		default:
			printf("다시 입력하세요!!");
			break;
		}
	} while (1);
}

void DailyMenu()
{
	printf("\n====하루 기록====\n");
	printf("1. 오늘 체중 입력\n");
	printf("2. 그동안의 기록 출력\n");
	printf("3. 기록 수정/삭제하기\n");
	printf("4. 이전페이지\n");
	printf("번호를 입력하세요 > ");
}

void addrecord()
{
	informa[inform_index]->Daily[numOfDaily] = (Daily*)malloc(sizeof(Daily) * MAX);
	//날짜 입력
	printf("오늘 날짜(ex. 211130): ");
	scanf_s("%s", informa[inform_index]->Daily[numOfDaily]->date, sizeof(informa[inform_index]->Daily[numOfDaily]->date));
	//체중 입력
	printf("체중 입력: ");
	scanf_s("%f", &informa[inform_index]->Daily[numOfDaily]->today_wgt);
	//하루 늘어남
	numOfDaily++; 
}

void viewrecord()
{
	int i;

	for (i = 0; i < numOfDaily; i++)
	{
		printf("\n날짜: %s", informa[inform_index]->Daily[i]->date);
		printf("\nD+%d", i + 1);
		printf("\n체중: %.2f", informa[inform_index]->Daily[i]->today_wgt);
	}
}

void editrecord()
{
	int i;
	char date[7];
	int index, choice;
	do
	{
		printf("수정하고 싶은 날짜를 입력하세요: ");
		scanf_s("%s", date, sizeof(date));
		for (i = 0; i < numOfDaily; i++)
		{
			if (!strcmp(date, informa[inform_index]->Daily[i]->date))
			{
				index = i;
				break;
			}
		}
		if(i==numOfDaily)
			printf("다시 입력하세요. \n");
	} while (strcmp(date, informa[inform_index]->Daily[i]->date) != 0);

	do
	{
		printf("어떤 부분을 수정할 것인가요? 1.날짜 2.체중: ");
		scanf_s("%d", &choice);
		switch (choice)
		{
		case 1:
			printf("날짜를 변경하세요: ");
			scanf_s("%s", informa[inform_index]->Daily[index]->date, sizeof(informa[inform_index]->Daily[index]->date));
			return;
		case 2:
			printf("체중을 변경하세요: ");
			scanf_s("%f", &informa[inform_index]->Daily[index]->today_wgt);
			return;
		default:
			printf("다시 입력하세요!!\n");
		}
	} while (1);
	printf("수정이 완료되었습니다.\n");
}

void Cash()
{
	int input, money;
	do
	{
		CashMenu();
		input = ReadInput();
		switch (input)
		{
		case 1: // 입금
			printf("입금 금액을 입력하세요. > ");
			scanf_s("%d", &money);
			informa[inform_index]->cash += money;
			printf("%d원이 입금되어 총 잔액은 %d 캐쉬입니다.\n", money, informa[inform_index]->cash);
			break;
		case 2: // 출금
			printf("출금 금액을 입력하세요. > ");
			scanf_s("%d", &money);
			if (money > informa[inform_index]->cash)
				printf("잔금이 부족하여 출금할 수 없습니다.\n");
			else
			{
				informa[inform_index]->cash -= money;
				printf("%d원이 출금되어 총 잔액은 %d 캐쉬입니다.\n", money, informa[inform_index]->cash);
			}
			break;
		case 3: // 조회
			printf("%s 님의 총 잔액은 %d 캐쉬입니다.\n", informa[inform_index]->name, informa[inform_index]->cash);
			break;
		case 4:  // 이전페이지
			return;
		default:
			printf("다시 시도하세요.\n");
		}
	} while (1);
}

void AEdit()
{
	char pwd[10];
	int input, i;

	do {
		printf("\n=== 회원정보 입력 및 수정 ===\n");
		printf("\n< 회원정보 >\n");
		printf("아이디 > %s\n", informa[inform_index]->id);
		printf("비밀번호 > %s\n", informa[inform_index]->pwd);
		printf("이름 > %s\n", informa[inform_index]->name);
		printf("나이 > %d\n", informa[inform_index]->age);
		printf("키 > %.2f\n", informa[inform_index]->hgt);
		printf("몸무게 > %.2f\n", informa[inform_index]->wgt);
		printf("캐쉬 > %d\n", informa[inform_index]->cash);

		AEditMenu();
		input = ReadInput();
		switch (input)
		{
		case 1: //나이/키/몸무게 수정
			printf("나이 > ");
			scanf_s("%d", &informa[inform_index]->age);
			printf("키 > ");
			scanf_s("%f", &informa[inform_index]->hgt);
			printf("몸무게 > ");
			scanf_s("%f", &informa[inform_index]->wgt);
			break;
		case 2:
			printf("새 비밀번호 > ");
			scanf_s("%s", pwd, sizeof(pwd));
			strcpy_s(informa[inform_index]->pwd, sizeof(informa[inform_index]->pwd), pwd);
			break;
		case 3: //탈퇴하기
			for (i = inform_index; i < numOfInform - 1; i++)
			{
				strcpy_s(informa[i]->id, sizeof(informa[i]->id), informa[i + 1]->id);
				strcpy_s(informa[i]->pwd, sizeof(informa[i]->pwd), informa[i + 1]->pwd);
				strcpy_s(informa[i]->name, sizeof(informa[i]->name), informa[i + 1]->name);
				informa[i]->age = informa[i + 1]->age;
				informa[i]->hgt = informa[i + 1]->hgt;
				informa[i]->wgt = informa[i + 1]->wgt;
				informa[i]->cash = informa[i + 1]->cash;
			}
			numOfInform--;
			printf("탈퇴되었습니다.\n\n");
			WriteData();
			exit(0);
		case 4:
			return;
		default:
			printf("다시 시도하세요.\n");
			break;
		}
	} while (1);
}

void AEditMenu()
{
	printf("\n<회원정보 메뉴>\n");
	printf("1. 회원정보(나이/키/몸무게) 수정\n");
	printf("2. 비밀번호 변경\n");
	printf("3. 탈퇴하기\n");
	printf("4. 이전페이지\n");
	printf("번호를 입력하세요 > ");
}

void WriteData()
{
	int i;
	FILE* fp;
	fopen_s(&fp, "inform.text", "wt");

	if (fp == NULL) {
		printf("파일 쓰기 불가능\n");
		return;
	}
	fprintf(fp, "%d\n", numOfInform);
	for (i = 0; i < numOfInform; i++) {
		fprintf(fp, "%s %s %s %d %f %f %d\n", informa[i]->id, informa[i]->pwd, informa[i]->name, informa[i]->age, informa[i]->hgt, informa[i]->wgt, informa[i]->cash);
	}
	for (i = 0; i < numOfDaily; i++)
		free(informa[inform_index]->Daily[i]);

	for (i = 0; i < numOfInform; i++) {
		free(informa[i]);
	}
	
	fclose(fp);
}
