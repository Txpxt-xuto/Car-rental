#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_ROW 1000
#define MAX_COL 500
#define MAX 200

char customers[MAX_ROW][MAX_COL][100];

void Menu();
void Booking();
void Readrule();
void Unbooking();
void Search();
void Canclerent();
int Count_days(int d, int m, int y);
int Days_in_month(int m, int y);
int Check_leap_year (int y);
int ChooseCar();
void Input_dmy_user(int Id_of_car);
void Checkavailable(int Id,int start,int end);
void SaveCustomer(int Id,int start,int end);
int checkRangeZero(char *filename, int targetRow, int startCol, int endCol);
void setRangeOne(char *filename, int targetRow, int startCol, int endCol);
void setRangeZero(char *filename, int targetRow, int startCol, int endCol);
void Input_dmy_user_every_car();
void Checkavailable_every_car(char *filename, int start, int end);
void Recall(int Id,int start,int end);
int Getvalueint(char *filename, int targetRow, int targetCol);
void Deletecustomer(char *filename, char *fname, char *lname);
int loadCSV(char *filename, char data[][MAX_COL][100], int *rows);
void saveCSV(char *filename, char data[][MAX_COL][100], int rows);
void deleteRow(char data[][MAX_COL][100], int *rows, int target);
int isLeap(int year) ;
int countDay(int dayOfYear,int i);



/*


void Menu()
{
    int i;
    do
    {
        printf("\n           Car Rental System           \n");
        printf("*****************************************\n");
        printf("*   [1]  Booking                        *\n");
        printf("*   [2]  Unbooking                      *\n");
        printf("*   [3]  Check for available vehicles   *\n");
        printf("*   [4]  Read the rules                 *\n");
        printf("*   [5]  Quit                           *\n");
        printf("*****************************************\n");
        printf("Please choose menu : ");
        scanf("%d",&i);
        if(i==1) Booking();
        else if(i==2) Unbooking();
        else if(i==3) Search();
        else if(i==4) Readrule();
    }while (i!=5);
}







int Check_leap_year (int y)
{
    if((y%4==0 && y%100!=0) || y%400==0) return 1;
    return 0;
}

int Days_in_month(int m, int y)
{
    int d[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if(m==2 && Check_leap_year(y)) return 29;
    return d[m-1];
}

int Count_days(int d, int m, int y)
{

    int days = d;

    for(int i=1;i<m;i++) days += Days_in_month(i,y);
    for(int i=1;i<y/2026;i++)
    {
        days += 365;
        if(Check_leap_year(i)) days += 1;
    }
    return days;
}








void Booking()
{
    int Car = ChooseCar();
    Input_dmy_user(Car);
}

int ChooseCar()
{
    int Car;

    printf("*****************************************\n");
    printf("*        [1]  Toyota Altis Gray         *\n");
    printf("*        [2]  Toyota Vios Black         *\n");
    printf("*        [3]  Toyota Vios White         *\n");
    printf("*        [4]  Toyota Innova White       *\n");
    printf("*        [5]  Izusu Dmax Gold           *\n");
    printf("*        [6]  Honda Accord Black        *\n");
    printf("*        [7]  Suzuki Celerio White      *\n");
    printf("*****************************************\n");
    printf("Please choose car : ");

    scanf("%d",&Car);
    return Car;
}

void Input_dmy_user(int Id_of_car)
{
    int DayS,MonthS,YearS,DayE,MonthE,YearE;

    printf("Start date (dd mm yyyy): ");
    scanf("%d %d %d",&DayS,&MonthS,&YearS);
    printf("End  date  (dd mm yyyy): ");
    scanf("%d %d %d",&DayE,&MonthE,&YearE);

    int days1 = Count_days(DayS,MonthS,YearS);
    int days2 = Count_days(DayE,MonthE,YearE);
    Checkavailable(Id_of_car,days1+2,days2+2);
}

void Checkavailable(int Id,int start,int end)
{
    int ans,result = checkRangeZero("CAR.csv", Id, start, end);

    if(result == 1)
    {
        Recall(Id,start,end);
        SaveCustomer(Id,start,end);
        setRangeOne("CAR.csv", Id, start, end);
    }

    else if(result == 0)
    {
        printf("Some dates are already booked.\n");
        printf("Do you want to booking aging?\n[1] Yes \t[2] No\n>>> ");
        scanf("%d",&ans);
        if(ans==1) Search();
        else Menu();
    }
    else
    {
        printf("ERROR!\n");
        Menu();
    }
}

void Recall(int Id,int start,int end)
{
    int deltatime=end-start,Accident_insurance_money=3000;
    int value = Getvalueint("CAR.csv", Id, 1);

    printf("Number of days : %10d Days\nPrice per day : %11d Bath\nTotal cost : %14d Bath\nCar insurance cost : %6d Bath\nNet total : %15d Bath\n",deltatime,value,(value*deltatime),Accident_insurance_money,(value*deltatime)+Accident_insurance_money);
    printf("Please fill in information to rent.\n");
}

int Getvalueint(char *filename, int targetRow, int targetCol)
{
    FILE *fp = fopen(filename, "r");
    if(fp == NULL)
    {
        printf("File error\n");
        return -1;
    }

    char line[10000];
    int currentRow = 0;

    while(fgets(line, sizeof(line), fp))
    {
        currentRow++;
        // ข้ามหัวตาราง
        if(currentRow == 1) continue;
        if(currentRow == targetRow + 1)
        {
            int col = 1;
            char *token = strtok(line, ",");

            while(token != NULL)
            {
                if(col == targetCol)
                {
                    token[strcspn(token, "\n")] = 0;
                    fclose(fp);
                    return atoi(token); // แปลงเป็น int ตรงนี้
                }
                token = strtok(NULL, ",");
                col++;
            }
        }
    }
    fclose(fp);
    return -1;
}

void SaveCustomer(int Id,int start,int end)
{
    FILE *fp = fopen("CUSTOMER.csv", "a"); // a = append เพิ่มข้อมูล
    if(fp == NULL)
    {
        printf("File error\n");
        return;
    }

    char fname[50], lname[50], phone[20], email[100], code4digit[5], time[5];
    int dd, yy, mm, hour, min;

    printf("First name: ");
    scanf("%s", fname);

    printf("Last name: ");
    scanf("%s", lname);

    printf("Phone: ");
    scanf("%s", phone);

    printf("Email: ");
    scanf("%s", email);

    if(Id==1) Id=Id+989 ;
    else if(Id==2) Id=Id+898 ;
    else if(Id==3) Id=Id+847 ;
    else if(Id==4) Id=Id+2496 ;
    else if(Id==5) Id=Id+945 ;
    else if(Id==6) Id=Id+994 ;
    else if(Id==7) Id=Id+793 ;

    printf("Please transfer a deposit of 1000 baht to Government Savings Bank, account number 0202-9242-2407\n");
    printf("Please enter the last 4 digits of the reference code: ");
    scanf("%s",code4digit);
    printf("Please enter the date of transferb (dd mm yy) : ");
    scanf("%d %d %d", &dd, &mm, &yy);
    printf("Please fill in the time of transfer (ex 07:12 --> ans 0712): ");
    scanf("%s",time);

    // เขียนลง CSV ใน excel ลงในไฟล์ชื่อ customers.csv
    fprintf(fp, "%s,%s,%s,%s,%d,%d,%d,%s,%d,%d,%d,%s\n", fname, lname, phone, email, Id, start-2, end-2, code4digit, dd, mm, yy, time);
    fclose(fp); //ปิดไฟล์
    printf("Customer saved!\n");
}

int checkRangeZero(char *filename, int targetRow, int startCol, int endCol)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("File error\n");
        return -1;
    }

    char line[10000];
    int currentRow = 0;

    while(fgets(line, sizeof(line), fp))
    {
        currentRow++;
        if (currentRow == 1) continue;
        if (currentRow == targetRow + 1)
        {
            int col = 1;
            char *token = strtok(line, ",");

            while (token != NULL)
            {
                if (col >= startCol && col <= endCol)
                {
                    if (atoi(token) != 0)
                    {
                        fclose(fp);
                        return 0;
                    }
                }
                token = strtok(NULL, ",");
                col++;
            }
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return -1;
}

void setRangeOne(char *filename, int targetRow, int startCol, int endCol)
{
    FILE *fp = fopen(filename, "r");
    FILE *temp = fopen("temp.csv", "w");

    if(fp == NULL || temp == NULL)
    {
        printf("File error\n");
        return;
    }

    char line[10000];
    int currentRow = 0;

    while(fgets(line, sizeof(line), fp))
    {
        currentRow++;
        if(currentRow == 1)
        {
            fprintf(temp, "%s", line);
            continue;
        }
        if(currentRow == targetRow + 1)
        {
            int col = 1;
            char *token = strtok(line, ",");

            while(token != NULL)
            {
                if(col >= startCol && col <= endCol) fprintf(temp, "1");
                else
                {
                    token[strcspn(token, "\n")] = 0;
                    fprintf(temp, "%s", token);
                }
                token = strtok(NULL, ",");
                if(token != NULL) fprintf(temp, ",");
                col++;
            }
            fprintf(temp, "\n");
        }
        else fprintf(temp, "%s", line);
    }
    fclose(fp);
    fclose(temp);
    remove(filename);
    rename("temp.csv", filename);
    printf("Booking Successfully!\n");
}








void Readrule()
{
    //เขียนรายละเอียดเพิ่มเติม
    printf("กติกาการเช่ารถ\n");
    printf("1.ห้ามชน \n2.ห้ามบิด \n3.ห้าม 18+");
}







void Search()
{
    Input_dmy_user_every_car();
}

void Input_dmy_user_every_car()
{
    int DayS,MonthS,YearS,Car,DayE,MonthE,YearE,Ans;

    printf("Start date (dd mm yyyy): ");
    scanf("%d %d %d",&DayS,&MonthS,&YearS);

    printf("End  date  (dd mm yyyy): ");
    scanf("%d %d %d",&DayE,&MonthE,&YearE);

    int days1 = Count_days(DayS,MonthS,YearS);
    int days2 = Count_days(DayE,MonthE,YearE);
    Checkavailable_every_car("CAR.csv",days1+2,days2+2);
}

void Checkavailable_every_car(char *filename, int start, int end)
{
    FILE *fp = fopen(filename, "r");

    if(fp == NULL)
    {
        printf("File error\n");
        return;
    }

    char line[10000];
    int getId[8]={0};
    int currentRow = 0,ans;
    int index = 1; //  ลำดับที่ใช้แสดง

    while(fgets(line, sizeof(line), fp))
    {
        currentRow++;
        if (currentRow == 1) continue; // skip header
        char tempLine[10000];
        strcpy(tempLine, line);
        int col = 1;
        int isAvailable = 1;
        char *token = strtok(line, ",");

        //  เช็คว่าวันที่ต้องการเป็น 0(ว่างให้เช่า)
        while(token != NULL)
        {
            if(col >= start && col <= end)
            {
                if(atoi(token) != 0)
                {
                    isAvailable = 0;
                    break;
                }
            }
            token = strtok(NULL, ",");
            col++;
        }

        // ถ้าว่างให้แสดงพร้อมลำดับ
        if(isAvailable)
        {
            char *t = strtok(tempLine, ","); // col1
            t = strtok(NULL, ",");          // col2

            if(t != NULL)
            {
                t[strcspn(t, "\n")] = 0;
                printf("[%d] %s\n", index, t);
                index++;
                getId[currentRow-1]=index-1;
            }
        }
        else getId[currentRow]=0;
    }
    fclose(fp);

    for(int i=1;i<=7;i++) printf("%d{ %d }  ",i, getId[i] );
    if(index == 1) printf("No available cars\n");

    else
    {
        printf("Please choose car : ");
        scanf("%d",&ans);
        for(int i=1;i<=7;i++)
        {
            if(ans==getId[i])
            {
                ans=i;
                i=8;
            }
        }
        Recall(ans,start,end);
        SaveCustomer(ans,start,end);
        setRangeOne("CAR.csv", ans, start, end);
    }
}








void Unbooking()
{
    FILE *fp = fopen("CUSTOMER.csv", "r");

    if(fp == NULL)
    {
        printf("File error\n");
        return;
    }
    char searchF[50], searchL[50];

    printf("First name: ");
    scanf("%s", searchF);

    printf("Last name: ");
    scanf("%s", searchL);

    char line[1000];
    int found = 0;

    while(fgets(line, sizeof(line), fp))
    {
        // ข้าม header
        if(strncmp(line, "FirstName", 9) == 0) continue;

        char temp[1000];
        strcpy(temp, line);

        char *fname = strtok(line, ",");
        char *lname = strtok(NULL, ",");
        char *phone = strtok(NULL, ",");
        char *email = strtok(NULL, ",");
        char *price = strtok(NULL, ",");
        char *start = strtok(NULL, ",");
        char *end = strtok(NULL, ",");

        if(fname && lname)
        {
            // ตัด \n
            lname[strcspn(lname, "\n")] = 0;
            if(strcmp(fname, searchF) == 0 && strcmp(lname, searchL) == 0)
            {
                int startCol = atoi(start), targetRow = atoi(price), endCol = atoi(end);
                Deletecustomer("CUSTOMER.csv",searchF,searchL);
                setRangeZero("CAR.csv",targetRow,startCol,endCol);
                found = 1;
                break;
            }
        }
    }

    if(!found) printf("Customer not found\n");
    fclose(fp);
}

void Deletecustomer(char *filename, char *fname, char *lname)
{
    int custRows, carRows;

    // โหลดไฟล์
    loadCSV("CUSTOMER.csv", customers, &custRows);
    int foundRow = -1;

    // ค้นหาลูกค้า
    for(int i = 1; i < custRows; i++)
    { 
        // ข้าม header
        if(strcmp(customers[i][0], fname) == 0 && strcmp(customers[i][1], lname) == 0)
        {
            foundRow = i;
            break;
        }
    }

    if(foundRow == -1) printf("Customer not found\n");

    // ดึงข้อมูลการจอง
    char FName = customers[foundRow][0];
    char Lname = customers[foundRow][1];
    char Tel   = customers[foundRow][2];
    char Email = customers[foundRow][3];
    int startCol = atoi(customers[foundRow][5]);
    int endCol   = atoi(customers[foundRow][6]);

    printf("\n             Booking found             \n");
    printf("****************************************\n");
    printf("*   Firstname  : %-20s  *\n",customers[foundRow][0]);
    printf("*   Lastname   : %-20s  *\n",customers[foundRow][1]);
    printf("*   Telephone  : %-20s  *\n",customers[foundRow][2]);
    printf("*   Email User : %-20s *\n",customers[foundRow][3]);
    countDay(startCol,1);
    countDay(endCol,0);
    printf("****************************************\n");

    // ลบลูกค้า
    deleteRow(customers, &custRows, foundRow);

    // บันทึกไฟล์
    saveCSV("CUSTOMER.csv", customers, custRows);
    printf("****************************************\n");
    printf("*   Cancel booking & delete success!   * \n");
    printf("****************************************\n");
    return 0;
}

int isLeap(int year) 
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int countDay(int dayOfYear,int i)
{
    int year=2026,month = 0;;


    // จำนวนวันแต่ละเดือน
    int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};

    // ถ้า leap year -> ก.พ. = 29
    if(isLeap(year)) daysInMonth[1] = 29;
    
    // หาเดือน
    while(dayOfYear > daysInMonth[month])
    {
        dayOfYear -= daysInMonth[month];
        month++;
    }

    // แสดงผล
    if(i==0) printf("*   Day Start  : %d / %d / %d          *\n", dayOfYear, month + 1, year);
    else printf("*   Day End    : %d / %d / %d          *\n", dayOfYear, month + 1, year);
    return 0;
}

int loadCSV(char *filename, char data[][MAX_COL][100], int *rows)
{
    FILE *fp = fopen(filename, "r");
    if(fp == NULL)
    {
        printf("File error: %s\n", filename);
        return 0;
    }

    char line[10000];
    int row = 0;

    while(fgets(line, sizeof(line), fp))
    {
        int col = 0;
        char *token = strtok(line, ",");

        while(token != NULL)
        {
            token[strcspn(token, "\n")] = 0;
            strcpy(data[row][col], token);

            token = strtok(NULL, ",");
            col++;
        }
        row++;
    }

    fclose(fp);
    *rows = row;
    return 1;
}

void saveCSV(char *filename, char data[][MAX_COL][100], int rows)
{
    FILE *fp = fopen(filename, "w");
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < MAX_COL; j++)
        {
            if(strlen(data[i][j]) == 0) break;
            fprintf(fp, "%s", data[i][j]);
            if(strlen(data[i][j+1]) > 0) fprintf(fp, ",");
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

void deleteRow(char data[][MAX_COL][100], int *rows, int target)
{
    for(int i=target;i<*rows-1;i++) for(int j=0;j<MAX_COL;j++) strcpy(data[i][j], data[i+1][j]);
    (*rows)--;
}

void setRangeZero(char *filename, int targetRow, int startCol, int endCol)
{
    FILE *fp = fopen(filename, "r");
    FILE *temp = fopen("temp.csv", "w");


    if(fp == NULL || temp == NULL)
    {
        printf("File error\n");
        return;
    }
    if(targetRow==990) targetRow=1 ;
    else if(targetRow==900) targetRow=2 ;
    else if(targetRow==850) targetRow=3 ;
    else if(targetRow==2500) targetRow=4 ;
    else if(targetRow==950) targetRow=5 ;
    else if(targetRow==1000) targetRow=6 ;
    else if(targetRow==800) targetRow=7 ;
    char line[10000];
    int currentRow = 0;
    while(fgets(line, sizeof(line), fp))
    {
        currentRow++;
        if(currentRow == 1)
        {
            fprintf(temp, "%s", line);
            continue;
        }
        if(currentRow == targetRow + 1)
        {
            int col = 1;
            char *token = strtok(line, ",");

            while(token != NULL)
            {
                if(col >= startCol+2 && col <= endCol+2) fprintf(temp, "0");
                else
                {
                    token[strcspn(token, "\n")] = 0;
                    fprintf(temp, "%s", token);
                }
                token = strtok(NULL, ",");
                if(token != NULL) fprintf(temp, ",");
                col++;
            }
            fprintf(temp, "\n");
        }
        else
        {
            fprintf(temp, "%s", line);
        } // แถวอื่น copy โง่ๆ
    }
    fclose(fp);
    fclose(temp); // แทนไฟล์เดิม
    remove(filename);
    rename("temp.csv", filename);
    printf("Unbooking Successfully!\n");
}

*/




int main()
{
    printf("Content-type: text/html\n\n");
    printf("<h1>CGI ทำงานแล้ว</h1>");
    return 0;
    /*printf("Content-type: text/html\n\n");

    char *query = getenv("QUERY_STRING");

    if(query == NULL){
        printf("No data received");
        return 0;
    }

    // ตัวแปรเก็บค่า
    char fname[MAX] = "", lname[MAX] = "", tel[MAX] = "";
    char email[MAX] = "", start[MAX] = "", end[MAX] = "";

    // copy query เพราะ strtok จะทำลาย string
    char data[1000];
    strcpy(data, query);

    // แยกด้วย &
    char *token = strtok(data, "&");

    while(token != NULL){
        char key[50], value[200];

        sscanf(token, "%[^=]=%s", key, value);

        if(strcmp(key, "fname") == 0) strcpy(fname, value);
        else if(strcmp(key, "lname") == 0) strcpy(lname, value);
        else if(strcmp(key, "tel") == 0) strcpy(tel, value);
        else if(strcmp(key, "email") == 0) strcpy(email, value);
        else if(strcmp(key, "start") == 0) strcpy(start, value);
        else if(strcmp(key, "end") == 0) strcpy(end, value);

        token = strtok(NULL, "&");
    }

    // 🔥 เขียน CSV
    FILE *fp = fopen("data.csv", "a");

    if(fp != NULL){
        fprintf(fp, "%s,%s,%s,%s,%s,%s\n",
            fname, lname, tel, email, start, end);
        fclose(fp);
    }

    // แสดงผล
    printf("<h2>บันทึกข้อมูลสำเร็จ</h2>");
    printf("<p>%s %s</p>", fname, lname);

    return 0;*/
}