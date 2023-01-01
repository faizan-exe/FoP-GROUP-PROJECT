#include <stdio.h>
#include <time.h>
#include <regex.h>
#include <ctype.h>


bool parkinglist[] = {false};
char carnum[20];

char line[1024];
char line1[1024];
char line2[1024];
char line3[1024];
char line4[1024];
char line5[1024];

int countyearly = 0;
int countmonthly = 0;

bool flag2;

int mon, moneytopay;
char *token;

bool bigloop2;


void removeSubstr (char *string, char *sub) {
    char *match;
    int len = strlen(sub);
    while ((match = strstr(string, sub))) {
        *match = '\0';
        strcat(string, match+len);
    }
}


char *strstrip(char *s)
{
        size_t size;
        char *end;

        size = strlen(s);

        if (!size)
                return s;

        end = s + size - 1;
        while (end >= s && isspace(*end))
                end--;
        *(end + 1) = '\0';

        while (*s && isspace(*s))
                s++;

        return s;
}


void findAndReplaceInFile(char* readfile, char* newfile, char*to_replace,char* replacement)
{
    FILE *ifp, *ofp;
    char word[100], ch, read[100], replace[100];
    int word_len, i, p = 0;

    ifp = fopen(readfile, "r");
    ofp = fopen(newfile, "w+");
    if (ifp == NULL || ofp == NULL) {
        printf("Can't open file.");
        exit(0);
    }

    // // displaying file contents
    // while (1) {
    //     ch = fgetc(ifp);
    //     if (ch == EOF) {
    //         break;
    //     }
    //     printf("%c", ch);
    // }

    strcpy(word, to_replace);
    strcpy(replace,replacement);

    // removes the newline character from the string
    // word[strlen(word) - 1] = word[strlen(word)];


    // // removes the newline character from the string
    // replace[strlen(replace) - 1] = replace[strlen(replace)];

    // fprintf(ofp, "%s - %s\n", word, replace);

    // comparing word with file
    rewind(ifp);
    while (!feof(ifp)) {

        fscanf(ifp, "%s", read);

        if (strcmp(read, word) == 0) {

            // for deleting the word
            strcpy(read, replace);
        }

        // In last loop it runs twice
        fprintf(ofp, "%s ", read);
    }

    // Printing the content of the Output file
    rewind(ofp);
    while (1) {
        ch = fgetc(ofp);
        if (ch == EOF) {
            break;
        }
        // fprintf("%c", ch);
    }

    fclose(ifp);
    fclose(ofp);
}








bool is_regex(char* regex, char* fileName, char* match){
    FILE *fp;
    char line[1024];
    int retval = 0;
    regex_t re;
    regmatch_t rm[2];

    if (regcomp(&re, regex, REG_EXTENDED) != 0)
    {
        fprintf(stderr, "Failed to compile regex '%s'\n", regex);
    }

    fp = fopen(fileName, "r");
    if (fp == 0)
    {
        fprintf(stderr, "Failed to open file %s (%d: %s)\n", fileName, errno, strerror(errno));
    }

    bool flag = false;
    while ((fgets(line, 1024, fp)) != NULL)
    {
        line[strcspn(line, "\n")] = '\0';
        if ((retval = regexec(&re, line, 2, rm, 0)) == 0)
        {
            char arr[8];
            strcpy(arr,line + rm[0].rm_so);
            removeSubstr(arr, " NO");
            arr[8] = '\0';

            if(strcmp(match,arr) == 0){
                return true;
            }
            else{
                flag = false;
                continue;
            }
        }
    }
    if(flag == false){
        return false;
    }
}


void removeSubstr (char *string, char *sub) {
    char *match;
    int len = strlen(sub);
    while ((match = strstr(string, sub))) {
        *match = '\0';
        strcat(string, match+len);
    }
}


int randspot()
{
    int spot = rand() % ((60) + 1 - 1) + 1;
    return spot;
}


bool checkspot(int spot)
{
    int count = 0;

    while (count <= 60)
    {
        if (parkinglist[spot] == false)
        {
            parkinglist[spot] = true;
            printf("You have been alloted parking spot %d", spot);
            return true;
        }
        else
        {
            spot = randspot();
            count++;
        }
    }
    return false;
}



int main(){

    srand(time(0));

    int timetostay;

    char txt[20];
    char txt2[20];


    char line[1024];

    int i = 0;

    printf("\nEnter the no. of hours of you want to park the car: ");
    scanf("%d", &timetostay);

    while(timetostay < 1 || timetostay>18){
        printf("\nInvalid input, try again: ");
        scanf("%d", &timetostay);
    }

    time_t seconds;
    struct tm *timeStruct;

    seconds = time(NULL);

    timeStruct = localtime(&seconds);

    int current_time_hour = timeStruct->tm_hour;

    while(timetostay + current_time_hour) > 24 {

        printf("\nYou can't park your car as parking will close down.\n");
        printf("Enter the number of hours you want to park the car. If you want to abort, press 0: ");

        scanf("%d", &timetostay);
        if (timetostay == 0){
            break;
        }

        while(timetostay < 1 || timetostay > 18){
            printf("\nInvalid input, try again: ");
            scanf("%d", &timetostay);
        }

    }

    txt = "YES";
    txt2 = "YESM";

    while (current_time_hour>=6 && current_time_hour <=24){


        printf("\n--------------------------------------------------------\n");
        printf("WELCOME TO THE PARKING AREA!\n");
        printf("********************************************************\n");

        int spoty = randspot();

        if (checkspot(spoty)){
            FILE *fptr;

            fptr = fopen("Personaldetails.txt", "r"); // you may have to change to a+ later

            if(fptr == NULL)
           {
              printf("Error!");
              exit(1);
           }


            while (fgets(line, sizeof(line), fptr)){

                if (is_regex("[A-Z][A-Z][A-Z]\\-[0-9][0-9][0-9]", "Personaldetails.txt", carnum)){

                    if(is_regex("YES|NO", "Personaldetails.txt", txt)){

                        FILE *fptr1;

                        fptr1 = fopen("Yearlycountfile.txt", "r");

                        while (fgets(line1, sizeof(line1), fptr1)){

                            char teststr[255] = "50";

                            if(is_regex("[A-Z][A-Z][A-Z]\\-[0-9][0-9][0-9]", "Yearlycountfile.txt", carnum)){

                                char **check;
                                check = search_regex(line1, "[0-9]?[0-9]$");
                                check = strstrip(*check[0]);

                                countyearly++;


                                // convert int to string
                                char string_countyearly[5];
                                itoa(countyearly, string_countyearly, 10);

                                findAndReplaceInFile("Personaldetails.txt", "Personaldetails1.txt", check, string_countyearly);

                                /* with open("Yearlycountfile.txt", 'w') as filedata:
                                                filedata.write(filedatawrite) */
                                // what's the point of this?

                                // convert string to integer
                                int int_check = atoi(check);
                                int int_teststr = atoi(teststr);

                                if (int_check > int_teststr){

                                     findAndReplaceInFile("Yearlycountfile.txt", "Yearlycountfile1.txt", check, '0');

                                /*  with open("Yearlycountfile.txt", 'w') as file:
                                                    file.write(fil)   */
                                // what's the point of this?

                                printf("\nYou got a free parking.\n");

                                }
                                else{

                                    printf("\nYou have to pay Rs. 50 per hour.\n");
                                    moneytopay = 200*timetostay;

                                    FILE *fptr2;

                                    fptr2 = fopen("Walletdetails.txt", "r");

                                    while(fgets(line2, sizeof(line2), fptr2)){

                                        if(is_regex("[A-Z][A-Z][A-Z]\\-[0-9][0-9][0-9]", "Walletdetails.txt", carnum)){

                                            int i = 0;

                                            bool flag2 = true;

                                            line2 = strstrip(line2);

                                            token = strtok(line2, ",");

                                            while (token != NULL){

                                                    if (i==1){
                                                        mon = atoi(token);
                                                        break;
                                                    }
                                                    i++;
                                            }

                                        }
                                    }

                                    if(mon < moneytopay){

                                        printf("\nYou don't have enough money.\n");

                                    }
                                    else {
                                        int newmon = mon - moneytopay;

                                        // convert int to str
                                        char str_mon[5];
                                        char str_new_mon[5];
                                        itoa(newmon, str_new_mon, 10);
                                        itoa(mon, str_mon, 10);

                                        findAndReplaceInFile("Walletdetails.txt", "Walletdetails1.txt", str_mon, str_new_mon);

                                        /* with open("Walletdetails.txt", 'w') as file:
                                                        file.write(fil) */
                                        // what;'s the point of this?



                                    }



                                }

                            }

                        }

                    }

                    else if(is_regex("YESM|NO", "Walletdetails.txt", txt2)){

                        FILE *fptr3;

                        fptr3 = fopen("Monthlycountfile.txt", "r");

                        while(fgets(line3, sizeof(line3), fptr3)){

                            char teststr1[50] = "100";

                            if (is_regex("[A-Z][A-Z][A-Z]\\-[0-9][0-9][0-9]", "Monthlycountfile.txt", carnum)){

                                char **check1;
                                check1 = search_regex(line3, "[0-9]?[0-9]?[0-9]$");
                                check1 = strstrip(*check1[0]);
                                countmonthly++;



                                // convert int to string
                                char string_countmonthly[5];
                                itoa(countmonthly, string_countmonthly, 10);

                                findAndReplaceInFile("Monthlycountfile.txt", "Monthlycountfile1.txt", check1, string_countmonthly);

                                /* with open("Monthlycountfile.txt", 'w') as filedata:
                                                filedata.write(filedatawrite)
                                                */
                                // what's the point?

                                // convert string to integer
                                int int_check1 = atoi(check1);
                                int int_teststr1 = atoi(teststr1);

                                if (check1 > teststr1){

                                     findAndReplaceInFile("Monthlycountfile.txt", "Monthlycountfile1.txt", check1, '0');

                                /*  with open("Yearlycountfile.txt", 'w') as file:
                                                    file.write(fil)   */
                                // what's the point of this?

                                    printf("\nYou got a free parking.\n");


                                }

                                else {
                                    printf("\nYou've to pay Rs. 200 per hour\n");
                                    moneytopay = 200*timetostay;

                                    FILE *fptr4;
                                    fptr4 = fopen("Walletdetails.txt", "r");

                                    while(fgets(line4, sizeof(line4), fptr4)){

                                        if (is_regex("[A-Z][A-Z][A-Z]\\-[0-9][0-9][0-9]", "Walletdetails.txt", carnum)){

                                            flag2 = false;

                                            line4 = strstrip(line4);

                                            token = strtok(line4, ",");

                                            while (token != NULL){

                                                    if (i==1){
                                                        mon = atoi(token);
                                                        break;
                                                    }
                                                    i++;
                                            }

                                            if (mon < moneytopay){
                                                printf("\nYou don't have enough money to pay\n");
                                            }
                                            else {
                                                int newmon = mon-moneytopay;

                                                // convert int to str
                                                char str_mon[5];
                                                char str_new_mon[5];
                                                itoa(newmon, str_new_mon, 10);
                                                itoa(mon, str_mon, 10);



                                                findAndReplaceInFile("Walletdetails.txt", "Walletdetails1.txt", str_mon, str_new_mon);
                                                /*  with open("Walletdetails.txt", 'w') as file:
                                                        file.write(fil) */




                                            }



                                        }

                                    }



                                }


                            }

                        }

                    }

                    else{
                        printf("\nYou have to pay Rs. 200 per hour.\n");

                        moneytopay = 200*timetostay;

                        FILE *fptr5;

                        fptr5 = fopen("Walletdetails.txt", "r");


                        while(fgets(line5, sizeof(line5), fptr5)){

                            if(is_regex("[A-Z][A-Z][A-Z]\\-[0-9][0-9][0-9]", "Walletdetails.txt", carnum)){

                                flag2 = true;

                                line5 = strstrip(line5);

                                token = strtok(line5, ",");

                                while (token != NULL){

                                    if (i==1){
                                        mon = atoi(token);
                                        break;
                                        }
                                    i++;
                                            }

                                        }
                                    }

                                    if(mon < moneytopay){

                                        printf("\nYou don't have enough money.\n");

                                    }

                                    else {
                                                int newmon = mon-moneytopay;

                                                // convert int to str
                                                char str_mon[5];
                                                char str_new_mon[5];
                                                itoa(newmon, str_new_mon, 10);
                                                itoa(mon, str_mon, 10);



                                                findAndReplaceInFile("Walletdetails.txt", "Walletdetails1.txt", str_mon, str_new_mon);
                                                /*  with open("Walletdetails.txt", 'w') as file:
                                                        file.write(fil) */


                            }

                        }

                    }
                    else{
                        printf("\nNo account found, you can't park.\n");
                        break;
                    }


                }

            }
            else {

                printf("\nSorry the parking is currently full.\n");
            }

            break;


        }

        bool bigloopflag = false;
        char contchoice2;
        printf("\nDo you want to reuse the PARKING SOFTWARE? Enter Y or N: ");
        scanf("%c", &contchoice2);



        while(toupper(contchoice2)!= 'Y' || toupper(contchoice2) != 'N'){
                printf("\nWrong choice try again\n");
                scanf("%c", &contchoice2);

        }

        if (contchoice2 == 'Y'){
            bigloop2 = false;
        }
        else{
            bigloop2 = true;
        }

    }




