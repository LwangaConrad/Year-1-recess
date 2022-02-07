#include <stdio.h>
#include<mysql.h>
#include <time.h>
#include<string.h>
#include <stdlib.h>

void main() {
    MYSQL* con = mysql_init(NULL);
    if (mysql_real_connect(con, "localhost", "root", "root",
        "kindercare", 3306, NULL, 0) == 0)
    {
        printf("Unsuccessful");
    }
    else
        printf("Successfully connected\n");
    char fname[20], lname[20], usercode[30]="", command[30];
    printf("Welcome to the KinderCare Character Draw System\n");
    printf("Please supply your First name: ");
    scanf_s("%s", fname, 20);
    printf("Please supply your Last name: ");
    scanf_s("%s", lname, 20);
    printf("Please supply your usercode: ");
    scanf_s("%s", usercode, 30);
    char stmt[100] = "SELECT Activated FROM pupils WHERE UserCode = '";
    strcat_s(stmt, 100, usercode);
    strcat_s(stmt, 100, "'");
    mysql_query(con, stmt);
    MYSQL_ROW row;
    MYSQL_RES* result = NULL;
    result = mysql_store_result(con);
    if ((row = mysql_fetch_row(result)) != NULL) {
        printf("Welcome you are successfully logged in as a pupil\n");
        while (1) {
            printf("Please type in a suitable command: ");
            scanf_s("%s", command, 30);
            if (strcmp(command, "ViewAll") == 0) {
                printf("Showing all assignments: \n");
                //show all assignments
                mysql_query(con, "SELECT * FROM assignments");
                MYSQL_RES* res = mysql_store_result(con);
                if (res == NULL)
                {
                    printf("No assignments to display");
                }
                else {
                    int num_fields = mysql_num_fields(res);
                    MYSQL_ROW row;
                    while ((row = mysql_fetch_row(res)))
                    {
                        for (int i = 0; i < num_fields; i++)
                        {
                            printf("%s ", row[i] ? row[i] : "NULL");
                        }
                        printf("\n");
                    }
                    mysql_free_result(res);
                }
            }
            else if (strcmp(command, "CheckStatus") == 0) {
                printf("Number of assignments attempted: \n");
                //retrieve assignments completed by pupil
                char buf[100] = "SELECT number_of_assignments FROM pupils WHERE Usercode = '";
                strcat_s(buf, 100, usercode);
                strcat_s(buf, 100, "'");
                mysql_query(con, buf);
                MYSQL_RES* rst = mysql_store_result(con);
                MYSQL_ROW row;
                row = mysql_fetch_row(rst);
                char chr[200];
                sprintf_s(chr, 200, "%s", row[0] ? row[0] : "0");
                printf(chr);
                printf("\n Number of assignments missed: \n");
                //retrieve assignments missed by pupil
                unsigned long nu = 0;
                printf("%lu", nu);
                printf("\nPercentage of assignments missed: \n");
                mysql_query(con, "SELECT * FROM assignments");
                MYSQL_RES* rsl = mysql_store_result(con);
                my_ulonglong rows = mysql_num_rows(rsl);
                unsigned long t = (nu / (unsigned long)rows)*100;
                printf("%lu", t);
                printf("\nPercentage of assignments attempted: \n");
                printf("%lu \n", (100 - t));
            }
            else if (strcmp(command, "ViewAssignment") == 0) {
                char attempt[1], identifier[5];
                int id;
                printf("Enter assignment id: ");
                scanf_s("%d", &id);
                _itoa_s(id, identifier, 5, 10);
                //grab assignment from database and display it's details
                char state[100] = "SELECT * FROM assignments WHERE id = ";
                strcat_s(state, 100, identifier);
                mysql_query(con, state);
                MYSQL_RES* resul = mysql_store_result(con);
                if (resul == NULL)
                {
                    printf("No assignment with specified id to display");
                }
                else {
                    int num_fields = mysql_num_fields(resul);
                    MYSQL_ROW row;
                    while ((row = mysql_fetch_row(resul)))
                    {
                        for (int i = 0; i < num_fields; i++)
                        {
                            printf("%s ", row[i] ? row[i] : "NULL");
                        }
                        printf("\n");
                    }
                    mysql_free_result(resul);
                }
                printf("Do you wish to attempt assignment? y/n: ");
                scanf_s("%s", attempt, 2);
                if (strcmp(attempt, "y") == 0) {
                    //check if pupil is activated
                    char st[100] = "SELECT * FROM pupils WHERE UserCode = '";
                    strcat_s(st, 100, usercode);
                    strcat_s(st, 100, "' AND Activated = 1");
                    mysql_query(con, st);
                    MYSQL_RES* re = mysql_store_result(con);
                    if(re != NULL){
                        clock_t t;
                        t = clock();
                        int i = 0;
                        int arr[7][4];
                        while (i < 7) {
                            int c = 0;
                            while (c < 4) {
                                printf("Please enter a 0 or 1 with 1 representing an *: ");
                                scanf_s("%d", &arr[i][c]);
                                c++;
                            }
                            i++;
                        }
                        for (int j = 0; j < 7; j++)
                        {
                            for (int k = 0; k < 4; k++)
                                if (arr[j][k] == 1) {
                                    printf("[*]");
                                }
                                else
                                    printf("[ ]");
                            printf("\n");
                        }
                        t = clock() - t;
                        double time_taken = ((double)t) / CLOCKS_PER_SEC;
                        double total_time_taken = 0;
                        total_time_taken += time_taken;
                        printf("You took %f seconds to complete character \n", time_taken);
                        char buf[100] = "Update pupils set number_of_assignments = number_of_assignments+1";
                        mysql_query(con, buf);
                        //get character
                        char ofre[100] = "SELECT character_assignment FROM assignments WHERE id = ";
                        strcat_s(ofre, 100, identifier);
                        mysql_query(con, ofre);
                        MYSQL_RES* results = mysql_store_result(con);
                        MYSQL_ROW row;
                        row = mysql_fetch_row(results);
                        char character[200];
                        char cr[5];
                        int answer[7][4];
                        sprintf_s(character, 200, "%s", row[0] ? row[0] : "");
                        if (strcmp(character, "A") == 0) {
                            int ans[7][4] = { 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1 };
                            memcpy(answer, ans, sizeof(int)*28);
                        }
                        else if (strcmp(character, "B") == 0) {
                            int ans[7][4] = { 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1 };
                            memcpy(answer, ans, sizeof(int) * 28);
                        }
                        else if (strcmp(character, "C") == 0) {
                            int ans[7][4] = { 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1 };
                            memcpy(answer, ans, sizeof(int) * 28);
                        }
                        else if (strcmp(character, "D") == 0) {
                            int ans[7][4] = { 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1 };
                            memcpy(answer, ans, sizeof(int) * 28);
                        }
                        else if (strcmp(character, "E") == 0) {
                            int ans[7][4] = { 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1 };
                            memcpy(answer, ans, sizeof(int) * 28);
                        }
                        else if (strcmp(character, "F") == 0) {
                            int ans[7][4] = { 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 };
                            memcpy(answer, ans, sizeof(int) * 28);
                        }
                        else if (strcmp(character, "G") == 0) {
                            int ans[7][4] = { 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1 };
                            memcpy(answer, ans, sizeof(int) * 28);
                        }
                        else if (strcmp(character, "H") == 0) {
                            int ans[7][4] = { 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1 };
                            memcpy(answer, ans, sizeof(int) * 28);
                        }
                        else if (strcmp(character, "I") == 0) {
                            int ans[7][4] = { 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1 };
                            memcpy(answer, ans, sizeof(int) * 28);
                        }
                        else if (strcmp(character, "J") == 0) {
                            int ans[7][4] = { 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1 };
                            memcpy(answer, ans, sizeof(int) * 28);
                        }
                        else if (strcmp(character, "K") == 0) {
                            int ans[7][4] = { 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1 };
                            memcpy(answer, ans, sizeof(int) * 28);
                        }
                        else if (strcmp(character, "L") == 0) {
                            int ans[7][4] = { 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1 };
                            memcpy(answer, ans, sizeof(int) * 28);
                        }
                        else if (strcmp(character, "M") == 0) {
                            int ans[7][4] = { 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1 };
                            memcpy(answer, ans, sizeof(int) * 28);
                        }
                        else if (strcmp(character, "N") == 0) {
                            int ans[7][4] = { 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1 };
                            memcpy(answer, ans, sizeof(int) * 28);
                        }
                        else if (strcmp(character, "O") == 0) {
                            int ans[7][4] = { 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1 };
                            memcpy(answer, ans, sizeof(int) * 28);
                        }
                        else if (strcmp(character, "P") == 0) {
                            int ans[7][4] = { 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 };
                            memcpy(answer, ans, sizeof(int) * 28);
                        }
                        else if (strcmp(character, "Q") == 0) {
                            int ans[7][4] = { 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1 };
                            memcpy(answer, ans, sizeof(int) * 28);
                        }
                        else if (strcmp(character, "R") == 0) {
                            int ans[7][4] = { 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1 };
                            memcpy(answer, ans, sizeof(int) * 28);
                        }
                        else if (strcmp(character, "S") == 0) {
                            int ans[7][4] = { 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1 };
                            memcpy(answer, ans, sizeof(int) * 28);
                        }
                        else if (strcmp(character, "T") == 0) {
                            int ans[7][4] = { 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0 };
                            memcpy(answer, ans, sizeof(int) * 28);
                        }
                        else if (strcmp(character, "U") == 0) {
                            int ans[7][4] = { 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1 };
                            memcpy(answer, ans, sizeof(int) * 28);
                        }
                        else if (strcmp(character, "V") == 0) {
                            int ans[7][4] = { 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0 };
                            memcpy(answer, ans, sizeof(int) * 28);
                        }
                        else if (strcmp(character, "W") == 0) {
                            int ans[7][4] = { 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1 };
                            memcpy(answer, ans, sizeof(int) * 28);
                        }
                        else if (strcmp(character, "X") == 0) {
                            int ans[7][4] = { 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1 };
                            memcpy(answer, ans, sizeof(int) * 28);
                        }
                        else if (strcmp(character, "Y") == 0) {
                            int ans[7][4] = { 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1 };
                            memcpy(answer, ans, sizeof(int) * 28);
                        }
                        else if (strcmp(character, "Z") == 0) {
                            int ans[7][4] = { 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1 };
                            memcpy(answer, ans, sizeof(int) * 28);
                        }
                        printf("The answer is: \n");
                        for (int p = 0; p < 7; p++)
                        {
                            for (int q = 0; q < 4; q++)
                                if (answer[p][q] == 1) {
                                    printf("[*]");
                                }
                                else
                                    printf("[ ]");
                            printf("\n");
                        }
                        if (memcmp(arr, answer, sizeof(arr)) != 0) {
                            printf("Sorry you got it wrong\n");
                            strcpy_s(cr, 2, "0");
                        }
                        else {
                            printf("Congratulations you got it correct\n");
                            strcpy_s(cr, 2, "1");
                        }
                        //add attempt to assignments done
                        char stet[200] = "insert into attempts(firstname, lastname, usercode, assignment_id, correct) values('";
                        strcat_s(stet, 200, fname);
                        strcat_s(stet, 200, "', '");
                        strcat_s(stet, 200, lname);
                        strcat_s(stet, 200, "', '");
                        strcat_s(stet, 200, usercode);
                        strcat_s(stet, 200, "', '");
                        strcat_s(stet, 200, identifier);
                        strcat_s(stet, 200, "', '");
                        strcat_s(stet, 200, cr);
                        strcat_s(stet, 200, "')");
                        mysql_query(con, stet);
                    }
                    else
                        printf("\nYou are not activated please ask your teacher to activate you by sending an activation request using the command 'RequestActivation'\n");
                }
                else
                    continue;
            }
            else if (strcmp(command, "CheckDates") == 0) {
                char datefrom[30], dateto[30];
                printf("Enter date from: ");
                scanf_s("%s", datefrom, 30);
                printf("Enter date to: ");
                scanf_s("%s", dateto, 30);
                //retrieve assignments between this time from database
                char stt[100] = "SELECT * FROM assignments WHERE (date_of_creation Between '";
                strcat_s(stt, 100, datefrom);
                strcat_s(stt, 100, "' and '");
                strcat_s(stt, 100, dateto);
                strcat_s(stt, 100, "')");
                mysql_query(con, stt);
                MYSQL_RES* rs = mysql_store_result(con);
                if (rs == NULL)
                {
                    printf("No assignments to display\n");
                }
                else {
                    int num_fields = mysql_num_fields(rs);
                    MYSQL_ROW row;
                    while ((row = mysql_fetch_row(rs)))
                    {
                        for (int i = 0; i < num_fields; i++)
                        {
                            printf("%s ", row[i] ? row[i] : "NULL");
                        }
                        printf("\n");
                    }
                    mysql_free_result(rs);
                }

            }
            else if (strcmp(command, "RequestActivation") == 0) {
                char ucode[20], first[30], last[30];
                printf("Please enter your usercode: ");
                scanf_s("%s", ucode, 20);
                printf("Please enter your first name: ");
                scanf_s("%s", first, 30);
                printf("Please enter your last name: ");
                scanf_s("%s", last, 30);
                //add student data to request table
                char stt[100] = "insert into requests(firstname, lastname, usercode) values('";
                strcat_s(stt, 100, first);
                strcat_s(stt, 100, "', '");
                strcat_s(stt, 100, last);
                strcat_s(stt, 100, "', '");
                strcat_s(stt, 100, ucode);
                strcat_s(stt, 100, "')");
                mysql_query(con, stt);
                printf("Sending request for Activation...\n");
            }
            else if (strcmp(command, "Logout") == 0) {
                break;
            }
            else
                printf("Invalid command try again\n");
        }
    }
    else
        printf("Invalid credentials please ask your teacher to register you then try again ");
}
