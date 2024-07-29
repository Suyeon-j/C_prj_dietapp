//다이어트 어플
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#define MAX 50

void MainMenu();
int ReadInput();
int LogIn();
void Join();
void SubMenu();
//관리 프로그램
void MyPage();
void MyPageMenu();
void BMI();
void DailyReadData();
void DailyWriteData();
void BuyProduct();
//하루 기록s
void MyDaily();
void DailyMenu();
void addrecord();
void viewrecord();
void editrecord();
void CashMenu();
void Cash();
void AEdit();
void AEditMenu();
void ReadData();
void WriteData();

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
    int Gwgt;
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
int inform_index;
int main()
{

    int input, input2;
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
                    BuyProduct();
                    break;
                case 2: //마이페이지
                    DailyReadData();
                    MyPage();
                    break;
                case 3: //시스템 종료
                    WriteData();
                    return 0;
                default:
                    printf("\n다시 시도하세요.\n");
                }
            } while (1);
            break;
        case 3:
            WriteData();
            return 0;
        default:
            printf("\n다시 시도하세요.\n");
        }
    } while (1);
}

int ReadInput()
{
    int input;
    scanf_s("%d", &input);
    return input;
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
    fscanf_s(fp, "%d ", &numOfInform);
    for (i = 0; i < numOfInform; i++)
    {
        informa[i] = (inform*)malloc(sizeof(inform));
        fscanf_s(fp, "%s %s %s %d %f %f %d %d",
            informa[i]->id, sizeof(informa[i]->id),
            informa[i]->pwd, sizeof(informa[i]->pwd),
            informa[i]->name, sizeof(informa[i]->name),
            &informa[i]->age, &informa[i]->hgt, &informa[i]->wgt, &informa[i]->Gwgt, &informa[i]->cash);
    }
    fclose(fp);
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
    informa[inform_index]->numOfDaily = 0;
}

void SubMenu()
{
    Sleep(4000);
    system("cls");
    printf("\n%s 님 환영합니다!\n", informa[inform_index]->name);
    printf("\n<다이어트 어플>\n");
    printf("1. 다이어트 식품 구매\n");
    printf("2. 마이페이지\n");
    printf("3. 어플 종료\n");
    printf("번호를 입력하세요 > ");
}

void BuyProduct()
{
    int i, gaesu, nnum;
    struct product list[6] = {
                   {1,"닭가슴살 슬라이스 100g 10팩",17500},
                   {2,"닭가슴살 스테이크 오리지널 100g 10팩",12000},
                   {3,"단백질쉐이크 330mlx12개입",39600},
                   {4,"단백질 보충제 1000g",36900},
                   {5,"닭가슴살 야채 곤약 볶음밥 250g 20팩",44000},
                   {6,"케이준 샐러드 160g",4300}
    };
    //상품내역 출력
    printf("\n다이어트 식품 =======\n");
    for (i = 0; i < 6; i++) {
        printf("%d. %s\n \t\t\t\t\t ----- %d원\n", i + 1, list[i].p_name, list[i].price);
        printf("\n");
    }
    printf("구매할 물건 번호와 수량을 입력하세요. > ");
    scanf_s("%d %d", &nnum, &gaesu);

    //구매 상품 목록 출력 후 수량 입력 받기
    printf("\n<구매내역>\n");
    printf("========================================\n");
    printf("내용\t/\t수량\t/\t판매가\t/\t계\n");
    printf("%s \t/ %d개 \t/ %d\t/ %d원\n", list[nnum - 1].p_name, nnum, list[nnum - 1].price, list[nnum - 1].price * gaesu);
    printf("========================================\n");
    printf("결제를 진행합니다.\n");
    printf("========================================\n");

    if (list[nnum - 1].price * gaesu > informa[inform_index]->cash)
    {
        printf("캐쉬 잔액이 부족하여 출금할 수 없습니다.\n");
        printf("캐쉬 관리 페이지로 이동합니다.\n");
        Sleep(4000);
        system("cls");
        Cash();
    }
    else
    {
        informa[inform_index]->cash -= list[nnum - 1].price * gaesu;
        printf("%d 캐쉬가 결제되어 잔액은 총 %d 캐쉬입니다.\n", list[nnum - 1].price * gaesu, informa[inform_index]->cash);
    }

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

void DailyReadData()
{
    int i;
    FILE* fp;

    fopen_s(&fp, "mydailyrecord.text", "rt");

    if (fp == NULL) {
        //printf("파일 읽기 불가능");
        return;
    }

    fscanf_s(fp, "%d", &inform_index);
    for (i = 0; i < informa[inform_index]->numOfDaily; i++)
        fscanf_s(fp, "%s %f %d",
            informa[inform_index]->Daily[i]->date, sizeof(informa[inform_index]->Daily[i]->date),
            &informa[inform_index]->Daily[i]->today_wgt, &informa[inform_index]->Gwgt);
    fclose(fp);
}

void MyPage()
{
    int input;
    do
    {
        MyPageMenu();
        //스위치
        input = ReadInput();
        switch (input)
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
            return;
        default:
            printf("\n다시 시도하세요.\n");
        }
    } while (1);
}

void MyPageMenu()
{
    Sleep(4000);
    system("cls");
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
    hweight1 = (int)18.5 * (mheight * mheight);
    hweight2 = (int)23 * (mheight * mheight);
    printf("\n<BMI지수>");
    printf("\nBMI 지수 = %.2f", bmi);
    printf("\n==== BMI 지수별 추천 다이어트====\n");
    if (0 <= bmi && bmi < 18.5)
    {
        printf("%s님은 저체중입니다.\n", informa[inform_index]->name);
        printf("저체중: 근육, 지방이 모두 부족\n");
        printf("ㄱ. 부위별 분할 웨이트 운동\n");
        printf("ㄴ. 단백질 보충제 섭취\n");
        printf("ㄷ. 충분한 탄수화물 섭취\n");
        printf("ㄹ. 요가나 필라테스로 자세 교정- 속근육을 키우기 위해");
    }
    else if (18.5 <= bmi && bmi < 23)
    {
        printf("%s님은 정상 체중입니다.\n", informa[inform_index]->name);
        printf("정상 체중: 바디 쉐이핑(근육과 지방 재배치)\n");
        printf("ㄱ. 부위별 웨이트 운동\n");
        printf("ㄴ. 탄단지 식단\n");
        printf("ㄷ. 규칙적인 식사 시간 + 양 통제\n");
        printf("ㄹ. 간식 통제");
    }

    else if (23 <= bmi && bmi < 25)
    {
        printf("%s님은 과체중입니다.\n", informa[inform_index]->name);
        printf("과체중, 비만, 고도비만: 체지방 감량\n");
        printf("ㄱ. 칼로리 제한\n");
        printf("ㄴ. 양 줄이기\n");
        printf("ㄷ. 종류제한 다이어트\n");
        printf("ㄹ. 전신루틴 운동");
    }

    else if (25 <= bmi && bmi < 30)
    {
        printf("%s님은 비만입니다.\n", informa[inform_index]->name);
        printf("과체중, 비만, 고도비만: 체지방 감량\n");
        printf("ㄱ. 칼로리 제한\n");
        printf("ㄴ. 양 줄이기\n");
        printf("ㄷ. 종류제한 다이어트\n");
        printf("ㄹ. 전신루틴 운동");
    }

    else
    {
        printf("%s님은 고도비만입니다.\n", informa[inform_index]->name);
        printf("과체중, 비만, 고도비만: 체지방 감량\n");
        printf("ㄱ. 칼로리 제한\n");
        printf("ㄴ. 양 줄이기\n");
        printf("ㄷ. 종류제한 다이어트\n");
        printf("ㄹ. 전신루틴 운동");
    }
    printf("\n==== 목표 몸무게 설정====");
    printf("\n%s님의 정상 몸무게의 범위는 %dkg ~ %dkg입니다.", informa[inform_index]->name, hweight1, hweight2);
    printf("\n목표 몸무게 입력: ");
    scanf_s("%d", &informa[inform_index]->Gwgt);
}

void MyDaily()
{
    int choice;
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
    Sleep(3000);
    system("cls");
    printf("\n<하루 기록>\n");
    printf("1. 오늘 체중 입력\n");
    printf("2. 그동안의 기록 출력\n");
    printf("3. 기록 수정하기\n");
    printf("4. 이전페이지\n");
    printf("번호를 입력하세요 > ");
}

void addrecord()
{
    informa[inform_index]->Daily[informa[inform_index]->numOfDaily] = (Daily*)malloc(sizeof(Daily) * MAX);
    //날짜 입력
    printf("===============\n");
    printf("오늘 날짜(ex. 211130): ");
    scanf_s("%s", informa[inform_index]->Daily[informa[inform_index]->numOfDaily]->date, sizeof(informa[inform_index]->Daily[informa[inform_index]->numOfDaily]->date));
    //체중 입력
    printf("체중 입력: ");
    scanf_s("%f", &informa[inform_index]->Daily[informa[inform_index]->numOfDaily]->today_wgt);
    printf("===============\n");
    //하루 늘어남
    informa[inform_index]->numOfDaily++;
    printf("오늘의 기록이 추가되었습니다.\n");
}

void viewrecord()
{
    int i;

    for (i = 0; i < informa[inform_index]->numOfDaily; i++)
    {
        printf("\n==============================");
        printf("\n날짜: %s", informa[inform_index]->Daily[i]->date);
        printf("\nD+%d", i + 1);
        printf("\n체중: %.2fkg", informa[inform_index]->Daily[i]->today_wgt);
        if (i != 0)
        {
            if (informa[inform_index]->Daily[i - 1]->today_wgt - informa[inform_index]->Daily[i]->today_wgt > 0)
                printf("\n어제보다 %.2fkg만큼 감량했습니다.", informa[inform_index]->Daily[i - 1]->today_wgt - informa[inform_index]->Daily[i]->today_wgt);
            else if (informa[inform_index]->Daily[i]->today_wgt - informa[inform_index]->Daily[i - 1]->today_wgt > 0)
                printf("\n어제보다 %.2fkg 증가했습니다.", informa[inform_index]->Daily[i]->today_wgt - informa[inform_index]->Daily[i - 1]->today_wgt);
            else
                printf("\n변화가 없습니다.");
        }
        printf("\n목표 몸무게까지: %.2fkg", informa[inform_index]->Daily[i]->today_wgt - informa[inform_index]->Gwgt);
        printf("\n==============================");
    }
    Sleep(10000);
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
        for (i = 0; i < informa[inform_index]->numOfDaily; i++)
            if (!strcmp(date, informa[inform_index]->Daily[i]->date))
            {
                index = i;
                break;
            }

        if (i == informa[inform_index]->numOfDaily)
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

void DailyWriteData() {
    int i;
    FILE* fp;

    fopen_s(&fp, "mydailyrecord.text", "wt");
    if (fp == NULL) {
       // printf("파일 쓰기 불가능");
        return;
    }
    fprintf(fp, "%d\n", inform_index);
    for (i = 0; i < informa[inform_index]->numOfDaily; i++)
        fprintf(fp, "%s %f %d\n",
            informa[inform_index]->Daily[i]->date,
            informa[inform_index]->Daily[i]->today_wgt, informa[inform_index]->Gwgt);

    fclose(fp);
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
    fprintf(fp, "%d \n", numOfInform);
    for (i = 0; i < numOfInform; i++) {
        fprintf(fp, "%s %s %s %d %f %f %d %d\n",
            informa[i]->id, informa[i]->pwd, informa[i]->name,
            informa[i]->age, informa[i]->hgt,
            informa[i]->wgt, informa[i]->Gwgt, informa[i]->cash);
    }
    for (i = 0; i < informa[inform_index]->numOfDaily; i++)
        free(informa[inform_index]->Daily[i]);

    for (i = 0; i < numOfInform; i++) {
        free(informa[i]);
    }

    fclose(fp);
}
