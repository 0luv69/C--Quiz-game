#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define FILENAME "quiz_data.quiz"
#define USERFILENAME "user_data.quiz"

typedef struct {
    char question[200];
    char options[4][100];
    int correct_answer;
} QuizQuestion;

typedef struct {
    char username[30];
    int total_score;
    int code_pass;
} User_struct;


void login();
void signup();
void show_all_user();

void admin_Page();
void addQuestion();
void Play_game();
void DeleteQuestion();
void help_Page();
void menu_page();
void clearInputBuffer();

void login(){
    printf("\n\n---------------------\n");
    printf(">>>> Login Page\t     |\n");
    printf("---------------------");

    char username_var[30];
    int code_pass_var, times_entered_pass;


    printf("\n\nEnter Your Username :\t");
    fgets(username_var, 30, stdin);
    strtok(username_var, "\n");
    // Check User exits or not
    if (checkuser(username_var) == 0){
        printf("\n\nsorry no user exits in this user name --->>> %s",username_var);
        printf("\nSign up here with the user name\n\n");
        signup();
    }else{
        enter_password:
        times_entered_pass++;
        if (times_entered_pass <7){
            printf("Enter Your Password:\t");
        scanf("%d",&code_pass_var);
        getchar();

        FILE *file = fopen(USERFILENAME, "rb");
        if (file == NULL) {
            printf("\nError: Failed to open user file.\n");
            return;
        }

        User_struct reading_user;
        while (fread(&reading_user, sizeof(User_struct), 1, file) == 1) {
            if (strcmp(reading_user.username, username_var) == 0) {
                if (reading_user.code_pass ==code_pass_var) {
                    printf("Login successful.\n");
                    Play_game(username_var);
                } else {
                    printf("Incorrect password.\n");
                    goto enter_password;
                }
                break;
            }
        }
        fclose(file);
        }else{
            printf("\n\nToooo Many Attampt sorry You cant get in\n\n");
            exit(0);

        }

    }
}

void signup(){
        printf("\n\n---------------------\n");
    printf(">>>> Signup Page\t     |\n");
    printf("---------------------");


    char username_var[30];
    srand(time(NULL));
    printf("\n\nEnter Your Desire Username :\t");
    fgets(username_var, 30, stdin);
    strtok(username_var, "\n");

    if (checkuser(username_var) == 0){
    User_struct New_user;
    strcpy(New_user.username,username_var);
    New_user.total_score=0;
    New_user.code_pass=rand() %9000 +1000;

    printf("\n\n\n\t\t\t\t-----------> Your pass code is : %d", New_user.code_pass);
    printf("\n\t\t\t\tPlz remember it else Your Account could get Lost");
    FILE *file;
    file = fopen(USERFILENAME, "ab+");
   if (file == NULL) {
        perror("Error opening file");
        return;
    }

    fwrite(&New_user, sizeof(User_struct), 1, file);
    fclose(file);
    } else{
    printf("\nSorry user name exits\n Try Something New");
     signup();
    }

    menu_page();
}

void show_all_user(){
        FILE *file = fopen(USERFILENAME, "rb");
        if (file == NULL) {
            printf("\nError: Failed to open user file.\n");
            return;
        }
        User_struct reading_user;
        int index=0;
        printf("\n\nS.n                     Username              Pass Code           Socre\n");
        while (fread(&reading_user, sizeof(User_struct), 1, file) == 1) {
                index++;
                printf("%d) \t\t\t%s \t\t\t %d \t\t   %d\n",index,reading_user.username,reading_user.code_pass,reading_user.total_score );
        }
        admin_Page();

}

int checkuser(checking_usename){
    FILE *file;
    file = fopen(USERFILENAME, "ab+");
   if (file == NULL) {
        printf("\nNO user Exits\n");
        return 0;
    }

    User_struct reading_user;
    while (fread(&reading_user, sizeof(User_struct), 1, file) == 1) {
        if (strcmp(reading_user.username,checking_usename)==0){
            // user exits
            fclose(file);
            return 1;
        }else{
        //user doesnt exit
        return 0;
        }
    }


}

void admin_Page() {
    int option;
    printf("\n\n   **********************");
    printf("\n|||||>>> Admin Page <<<|||||\n");
    printf("   **********************");
    printf("\nType 3 to go back to the menu page\n\n");

    while (1) {
        printf("Choose an option:\n");
        printf("1. Add a Question\n");
        printf("2. Remove All Questions\n");
        printf("3. Show all Users\n");
        printf("4. Menu page\n");
        printf("Option: ");
        scanf("%d", &option);
        clearInputBuffer();

        switch (option) {
            case 1:
                addQuestion();
                break;
            case 2:
                DeleteQuestion();
                break;
            case 3:
                show_all_user();
                break;
            case 4:
                menu_page();
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }
}

void addQuestion() {
    int output_is_int,choice,j=0;
    char temp_que[200];
    FILE *file;
    file = fopen(FILENAME, "ab+"); // Open the file in append and binary mode

    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    QuizQuestion New_que_Struct[100];
    printf("\n\n\t\t\t:: Add Question and then 4 options with the index of the correct answer to end write -exit::");
    printf("\n\t\t\t\t\tTo exit or finish adding questions, type '-exit'\n");

    while (1) {
        printf("\nEnter the Question:\t");
        fgets(temp_que, 200, stdin);
        strtok(temp_que, "\n");
        if (strcmp(temp_que, "-exit") == 0) {
            fwrite(&New_que_Struct, sizeof(QuizQuestion), j, file);
            fclose(file);
            menu_page();
            return;
        }
        strcpy(New_que_Struct[j].question,temp_que);
        for (int i = 0; i < 4; i++) {
            printf("Enter Option %d:\t", i + 1);
            fgets(New_que_Struct[j].options[i], 100, stdin);
            strtok(New_que_Struct[j].options[i], "\n");
        }

        while (1) {
            printf("Enter the index of the correct answer:\t");
            output_is_int = scanf("%d", &choice);
            clearInputBuffer();
            if (choice >= 1 && choice <= 4 && output_is_int == 1) {
                New_que_Struct[j].correct_answer=choice;
                break;
            } else {
                printf("\nInvalid input! Please enter a number from 1 to 4.\n");
            }
        }
        j++;
    }
}

void Play_game(username) {
        printf("\n\n---------------------\n");
    printf(">>>> Game Play Zone   |\n");
    printf("---------------------");
    FILE *file;
    file = fopen(FILENAME, "rb");

    if (file == NULL) {

        printf("\n \t\t\t\tNo Quiz Data added yet Plz tell ur Admin To add some\n");
        menu_page();
    }
    printf("\n\n\t\t\t\t\tYou are playing as %s\n\n",username );

    int choice, index = 0, correct_ans = 0, output_is_int, palyed_or_not;
    QuizQuestion reading_question;

    while (fread(&reading_question, sizeof(QuizQuestion), 1, file) == 1) {
        index++;
        palyed_or_not=1;
        printf("\nQuestion %d: %s\n", index, reading_question.question);
        for (int i = 0; i < 4; i++) {
            printf("%d. %s\n", i + 1, reading_question.options[i]);
        }

        while (1) {
            printf("Enter your choice (1-4): ");
            output_is_int = scanf("%d", &choice);
            clearInputBuffer();
            if (choice >= 1 && choice <= 4 && output_is_int == 1) {
                break;
            } else {
                printf("\nInvalid input! Please enter a number from 1 to 4.\n");
            }
        }

        if (choice == reading_question.correct_answer) {
            correct_ans++;
            printf("Correct!\n");
            printf("....................You have Gained %d Points.................", correct_ans);
        } else {
            printf("Incorrect! The correct answer is: %s\n", reading_question.options[reading_question.correct_answer - 1]);
        }
    }
    if (palyed_or_not==1){
        printf("\nYour score: %d\n", correct_ans);
        if (strcmp(username,"Random")==0){}
        else{
            add_new_score(username,correct_ans);
            }
    fclose(file);
    menu_page();

    }else{

    printf("\n\n\n\t\t!!!!!!!!!!!!!!!!!!! Plz add the quiz data first !!!!!!!!!!!!!!!!!!!!!!!!!");
    menu_page();
    }

}

void DeleteQuestion() {
    FILE *file;
    file = fopen(FILENAME, "w");
    fclose(file);
    printf("Removed All Question sucessfully");
    menu_page();
}

void add_new_score(username, score){
    FILE *file;
    file = fopen(USERFILENAME, "rb+");
   if (file == NULL) {
        printf("\nNO user Exits\n");
        return 0;
    }
    User_struct reading_user;
    while (fread(&reading_user, sizeof(User_struct), 1, file) == 1) {
        if (strcmp(reading_user.username,username)==0){
            reading_user.total_score =score;
            fseek(file, -sizeof(reading_user), SEEK_CUR);
            fwrite(&reading_user, sizeof(User_struct), 1, file);
            fclose(file);
            }
        }
        menu_page();
    }

void help_Page() {
    printf("\n>>>> Help Page\n");
    printf("\nWelcome to the Quiz Game!\n");
    printf("\nAs a player, you can:\n");
    printf("1. Play the quiz game.\n");
    printf("2. Log in to your account or sign up if you're new.\n");
    printf("3. Access the admin panel (if allowed).\n");
    printf("4. Exit the program.\n");
    printf("\nTo play the game, just press any key (except the power button) when prompted.\n");
    printf("To log in to your account, type '-login' and press Enter. If you're new, type '-sign' to sign up.\n");
    printf("To access the admin panel (if allowed), enter the appropriate code.\n");
    printf("To exit the program, type '-end' and press Enter.\n");
    printf("\nNote: You can always type '-help' or '-h' to return to this help page.\n");

    printf("\nAs an administrator, you can:\n");
    printf("1. Add questions to the quiz.\n");
    printf("2. Remove all questions from the quiz.\n");
    printf("3. Return to the main menu.\n");
    printf("\nTo add a question, select option 1 and follow the prompts.\n");
    printf("To remove all questions, select option 2.\n");
    printf("To return to the main menu, select option 3.\n");
    printf("\nNote: Access to the admin panel may require a special code.\n");

    menu_page(); // Return to the main menu
}

void menu_page() {
    char initial_input[10];
    printf("\n\n---------------------\n");
    printf(">>>> Menu Page\t     |\n");
    printf("---------------------");

    printf("\nUse '-help' or '-h' for help\n");
    printf("To begin the game, press any button except the power button: ");
    fgets(initial_input, 10, stdin);

    if (initial_input[strlen(initial_input) - 1] == '\n') {
        initial_input[strlen(initial_input) - 1] = '\0';
    }

    if (strcmp(initial_input, "-help") == 0 || strcmp(initial_input, "-h") == 0) {
        help_Page();
    } else if (strcmp(initial_input, "-a") == 0) {
        admin_Page();
    } else if (strcmp(initial_input, "-sign") == 0) {
        signup();

    } else if (strcmp(initial_input, "-login") == 0) {
        login();

    }else if (strcmp(initial_input, "-end") == 0) {
        exit(0);
    }else {
        Play_game("Random");
    }
}

void clearInputBuffer() {
    while (getchar() != '\n');
}

int main() {
    printf("***************************************************************************************\n");
    printf("\n\t----------------------Welcome to the Quiz Game---------------------------\n");
    printf("\t----------------------Built with Love by Rujal---------------------------\n\n");
    printf("***************************************************************************************\n");
    menu_page();
    return 0;
}
