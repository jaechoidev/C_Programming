#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct student{
    char student_ID[40];
    char student_name[40];
    char Email_ID[40];
    char course_ID[40];
    char grade[40];
};


void display_main_menu(){
    printf(" \n");
    printf(" \n");
    printf("           M A I N    M E N U              \n");
    printf("1. Create the Binary File (or add new student) \n");
    printf("2. Display the contents of the file \n");
    printf("3. Seek a specific record \n");
    printf("4. Update the contents of a record \n");
    printf("5. Delete a record for the specific name \n");
    printf("6. Exit \n");
    printf(" \n");
    printf("            Please Enter Your Choice ....     \n");
}

void count_student_data(){
    struct student student_01;
    int student_count = 0;
    FILE *fptr = fopen("student_list.bin","rb");

    if (fptr == NULL){
        printf("Error! opening file");
        // Program exits if the file pointer returns NULL.
        exit(1);
    }
    while(1){
        fread(&student_01, sizeof(student_01), 1, fptr);
        int eof = feof(fptr);
        if (eof == 1){
            printf("There are(is) %d student(s) in the list.\n", student_count);
            break;
        }
        student_count ++;
    }
    fclose(fptr);
}

int file_exists(){
    FILE *file;
    if((file = fopen("student_list.bin","r"))!=NULL)
    {
        // file exists
        fclose(file);
        return 1;
    }
    else
    {
        //File not found, no memory leak since 'file' == NULL
        //fclose(file) would cause an error
        return 0;
    }
}

bool student_validation(char* new_student_id) {
    struct student student_01;
    FILE *fptr = fopen("student_list.bin", "rb");

    if (fptr == NULL) {
        printf("Error! opening file");
        // Program exits if the file pointer returns NULL.
        exit(1);
    }

    while (1) {
        fread(&student_01, sizeof(student_01), 1, fptr);
        int eof = feof(fptr);
        if (eof == 1) {
            fclose(fptr);
            return true;
        }
        if (strcmp(student_01.student_ID, new_student_id) == 0) {
            fclose(fptr);
            return false;
        }
    }
}

void create_student_data(){
    FILE *fptr;
    struct student new_student;

    if ((fptr = (fopen("student_list.bin","a"))) == NULL){
        printf("Error! opening file");

        // Program exits if the file pointer returns NULL.
        exit(1);
    }
    bool valid = false;
    count_student_data();
    printf("Register new student. \n");
    printf("=========================================================================================================\n");

    while(valid == false) {
        printf("Student ID : \n");
        scanf("%s", new_student.student_ID);
        valid = student_validation(new_student.student_ID);
        if (valid == false) {
            printf("Student ID should be unique. Please enter new student ID.\n\n");
            continue;
        }
    }
    printf("Student Name : \n");
    scanf("%s", new_student.student_name);
    printf("Student Email : \n");
    scanf("%s", new_student.Email_ID);
    printf("Course ID : \n");
    scanf("%s", new_student.course_ID);
    while(1){
        printf("Grade : \n");
        scanf("%s", new_student.grade);
        if (strcmp(new_student.grade,"A+") == 0||
            strcmp(new_student.grade,"A") == 0||
            strcmp(new_student.grade,"B+") == 0||
            strcmp(new_student.grade,"B") == 0||
            strcmp(new_student.grade,"C+") == 0||
            strcmp(new_student.grade,"C") == 0||
            strcmp(new_student.grade,"D+") == 0||
            strcmp(new_student.grade,"D") == 0||
            strcmp(new_student.grade,"F") == 0){
            break;
        }else{
            printf("Grade should be one of following (Case-sensitive) - A+, A, B+, B, C+, C, D+, D, F \n\n");
            continue;
        }
    }
    fwrite(&new_student, sizeof(struct student), 1, fptr);
    fclose(fptr);
}

void show_student_data(){
    struct student student_01;

    FILE *fptr = fopen("student_list.bin","rb");

    if (fptr == NULL){
        printf("Please create the Binary File First.");
        // Program exits if the file pointer returns NULL.
        return;
    }
    count_student_data();
    printf("=========================================================================================================\n");
    printf("%-20s\t%-20s\t%-20s\t%-20s\t%-20s\t\n",
           "STUDENT_ID",
           "STUDENT_NAME",
           "EMAIL_ID",
           "COURSE_ID",
           "GRADE");
    printf("--------------------------------------------------------------------------------------------------------\n");
    while(1){
        fread(&student_01, sizeof(student_01), 1, fptr);
        int eof = feof(fptr);
        if (eof == 1){
            break;
        }
        printf("%-20s\t%-20s\t%-20s\t%-20s\t%-20s\t\n",
               student_01.student_ID,
               student_01.student_name,
               student_01.Email_ID,
               student_01.course_ID,
               student_01.grade);
    }
    printf("=========================================================================================================\n");
}

void update_student_data(){
    char student_id[40];
    printf("Please enter student ID that you want to update. (- quit() to go menu)\n");
    scanf("%s", student_id);
    if (strcmp(student_id, "quit()") == 0){
        return ;
    }

    struct student student_01;
    FILE *fptr = fopen("student_list.bin","rb");
    FILE *ftmpptr = fopen("tmp.bin", "wb");

    if (fptr == NULL){
        printf("Error! opening file");
        // Program exits if the file pointer returns NULL.
        exit(1);
    }

    while(1){
        fread(&student_01, sizeof(student_01), 1, fptr);
        int eof = feof(fptr);
        if (eof == 1){
            break;
        }
        char user_update[40];
        char student_id_tmp[40];

        if (strcmp(student_01.student_ID, student_id) == 0){
            while(1){
                printf("Choose field you want to update.\n");
                printf("1. Student_ID\n");
                printf("2. Student_name\n");
                printf("3. Email_ID\n");
                printf("4. Course_ID\n");
                printf("5. Grade\n");
                scanf("%s", user_update);
                if (strlen(user_update) > 1){
                    printf("Please enter one of the field.");
                    continue;
                }else{
                    break;
                }
            }
            if (strcmp(user_update, "1") == 0){
                bool valid = false;
                while(valid == false) {
                    printf("Student ID : \n");
                    scanf("%s", student_id_tmp);
                    valid = student_validation(student_id_tmp);
                    if (valid == false) {
                        printf("Student ID should be unique. Please enter new student ID.\n\n");
                        continue;
                    }
                }
                printf("Student ID is changed from %s to %s.", student_01.student_ID, student_id_tmp);
                for (int i = 0; i <= strlen(student_id_tmp); i++) {
                    if(i == strlen(student_id_tmp)) {
                        student_01.student_ID[i] = '\0';
                    }else{
                        student_01.student_ID[i] = student_id_tmp[i];
                    }
                }
            }else if (strcmp(user_update, "2") == 0){
                printf("Student Name : \n");
                scanf("%s", student_01.student_name);
                printf("Student name is changed to %s.", student_01.student_name);
            }else if (strcmp(user_update, "3") == 0){
                printf("Student Email : \n");
                scanf("%s", student_01.Email_ID);
                printf("Email ID is changed to %s.", student_01.Email_ID);
            }else if (strcmp(user_update, "4") == 0){
                printf("Course ID : \n");
                scanf("%s", student_01.course_ID);
                printf("Course ID is changed to %s.", student_01.course_ID);
            }else if (strcmp(user_update, "5") == 0) {
                while (1) {
                    printf("Grade : \n");
                    scanf("%s", student_01.grade);
                    if (strcmp(student_01.grade, "A+") == 0 ||
                        strcmp(student_01.grade, "A") == 0 ||
                        strcmp(student_01.grade, "B+") == 0 ||
                        strcmp(student_01.grade, "B") == 0 ||
                        strcmp(student_01.grade, "C+") == 0 ||
                        strcmp(student_01.grade, "C") == 0 ||
                        strcmp(student_01.grade, "D+") == 0 ||
                        strcmp(student_01.grade, "D") == 0 ||
                        strcmp(student_01.grade, "F") == 0) {
                        break;
                    } else {
                        printf("Grade should be one of following (Case-sensitive) - A+, A, B+, B, C+, C, D+, D, F \n\n");
                        continue;
                    }
                }
                printf("Grade is changed to %s.", student_01.grade);
            }
            fwrite(&student_01, sizeof(struct student), 1, ftmpptr);
        }else{
            fwrite(&student_01, sizeof(struct student), 1, ftmpptr);
        }
    }
    fclose(fptr);
    fclose(ftmpptr);

    remove("student_list.bin");
    rename("tmp.bin", "student_list.bin");
}

void delete_student_data(){
    char * student_id;
    printf("Please enter student ID that you want to delete. (- quit() to go menu)\n");
    scanf("%s", student_id);

    if (strcmp(student_id, "quit()") == 0){
        return ;
    }
    struct student student_01;
    FILE *fptr = fopen("student_list.bin","rb");
    FILE *ftmpptr = fopen("tmp.bin", "wb");

    if (fptr == NULL){
        printf("Error! opening file");
        // Program exits if the file pointer returns NULL.
        exit(1);
    }

    while(1){
        fread(&student_01, sizeof(student_01), 1, fptr);
        int eof = feof(fptr);
        if (eof == 1){
            break;
        }
        if (strcmp(student_01.student_ID, student_id) != 0){
            fwrite(&student_01, sizeof(struct student), 1, ftmpptr);
        }else{
            printf("Student_ID : %s - will be deleted.\n", student_id);
        }
    }
    fclose(fptr);
    fclose(ftmpptr);

    remove("student_list.bin");
    rename("tmp.bin", "student_list.bin");
}

void create_binary_file(){
    if (file_exists() == 0){
        // binary file doesn't exist
        printf("Creating Binary File......\n");
        FILE *fptr;
        if ((fptr = (fopen("student_list.bin","a"))) == NULL){
            printf("Error! opening file");
            // Program exits if the file pointer returns NULL.
            exit(1);
        }
        fclose(fptr);
        printf("do you want to add student? (y/n)\n");
    }else{
        //binary file exists
        printf("Binary file already exists, do you want to add student? (y/n)\n");
        }

    char user_answer[4];
    while(1){
        scanf("%s", user_answer);
        if (strlen(user_answer) > 1){
            printf("Please enter correct answer (y/n).\n");
        }else if (user_answer[0] == 'y' || user_answer[0] == 'Y'){
            create_student_data();
            break;
        }else if (user_answer[0] == 'n' || user_answer[0] == 'N'){
            printf("Going to main menu......\n");
            break;
        }else{
            printf("Please enter correct answer (y/n).\n");
        }

    }
}

void find_student_data(){
    struct student student_01;

    FILE *fptr = fopen("student_list.bin","rb");

    if (fptr == NULL){
        printf("Error! opening file");
        // Program exits if the file pointer returns NULL.
        exit(1);
    }
    char search[40];
    printf("Search : \n");
    scanf("%s", search);

    printf("============================================ SEARCH RESULT ============================================\n");
    printf("%-20s\t%-20s\t%-20s\t%-20s\t%-20s\t\n",
           "STUDENT_ID",
           "STUDENT_NAME",
           "EMAIL_ID",
           "COURSE_ID",
           "GRADE");
    printf("--------------------------------------------------------------------------------------------------------\n");
    while(1){
        fread(&student_01, sizeof(student_01), 1, fptr);
        int eof = feof(fptr);
        if (eof == 1){
            break;
        }

        bool matched = false;

        for (int i = 0; i < strlen(search); i++){
            if (search[i] != student_01.student_ID[i]){
                matched = false;
                break;
            }else{
                matched = true;
            }
        }
        if (matched == true){
            printf("%-20s\t%-20s\t%-20s\t%-20s\t%-20s\t\n",
                   student_01.student_ID,
                   student_01.student_name,
                   student_01.Email_ID,
                   student_01.course_ID,
                   student_01.grade);
            continue;
        }

        for (int i = 0; i < strlen(search); i++){
            if (search[i] != student_01.student_name[i]){
                matched = false;
                break;
            }else{
                matched = true;
            }
        }
        if (matched == true){
            printf("%-20s\t%-20s\t%-20s\t%-20s\t%-20s\t\n",
                   student_01.student_ID,
                   student_01.student_name,
                   student_01.Email_ID,
                   student_01.course_ID,
                   student_01.grade);
            continue;
        }

        for (int i = 0; i < strlen(search); i++){
            if (search[i] != student_01.Email_ID[i]){
                matched = false;
                break;
            }else{
                matched = true;
            }
        }
        if (matched == true){
            printf("%-20s\t%-20s\t%-20s\t%-20s\t%-20s\t\n",
                   student_01.student_ID,
                   student_01.student_name,
                   student_01.Email_ID,
                   student_01.course_ID,
                   student_01.grade);
            continue;
        }

        for (int i = 0; i < strlen(search); i++){
            if (search[i] != student_01.course_ID[i]){
                matched = false;
                break;
            }else{
                matched = true;
            }
        }
        if (matched == true){
            printf("%-20s\t%-20s\t%-20s\t%-20s\t%-20s\t\n",
                   student_01.student_ID,
                   student_01.student_name,
                   student_01.Email_ID,
                   student_01.course_ID,
                   student_01.grade);
            continue;
        }

        for (int i = 0; i < strlen(search); i++){
            if (search[i] != student_01.grade[i]){
                matched = false;
                break;
            }else{
                matched = true;
            }
        }
        if (matched == true){
            printf("%-20s\t%-20s\t%-20s\t%-20s\t%-20s\t\n",
                   student_01.student_ID,
                   student_01.student_name,
                   student_01.Email_ID,
                   student_01.course_ID,
                   student_01.grade);
            continue;
        }
    }
    printf("============================================ SEARCH END ===============================================\n");
    fclose(fptr);
}
int main() {
    char user_input[40];

    while(user_input[0] != '6'){
        display_main_menu();
        scanf("%s", user_input);
        if (strlen(user_input) > 1){
            printf("Please type in one number of menu.");
        }else{
            switch (user_input[0]){
                case '1':
                    create_binary_file();
                    break;
                case '2':
                    show_student_data();
                    break;
                case '3':
                    find_student_data();
                    break;
                case '4':
                    show_student_data();
                    update_student_data();
                    break;
                case '5':
                    show_student_data();
                    delete_student_data();
                    break;
                case '6':
                    printf("exit");
                    break;
                default:
                    printf("wrong input %s", user_input);
                    continue;
            }
        }
    }
    return 0;
}



