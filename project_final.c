#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "clui.h"

//define all function 
void menu_login(void);
int login(void);
int signup(void);
void user_menu(void);
void leaderboard(void);
int add_new_word(void);
int check_repeat(char*,char);
void check_digit(char*,char,char*,char*,char*);
void print_answer(char*,int);
void game(void);
void add_score(int,int);
void print_lose(int);
int check_password(char*);
void change_password(int);
void reduce_score(int);
void get_help(char*,char*);
void print_wrong_characters(char*,int);
void print_karbari(int,int);

//Global variable
int counter_word=0;//count down from size(word) to 0
int counter_vorodi=0;//counter
int counter_lose=0;//count mistakes
typedef struct {
       char username[50];
       int score;
}User_score;
User_score loggedin_user;//save user and score of logged user
int number_of_logged_user;//save number of logged user in list

void print_karbari(int mistake,int tedad){//print number of mistakes graphical
       if(tedad>8){
              printf("| ");
              for(int i=0 ; i<mistake ; i++){
                     change_color_rgb(150, 10, 15);//red
                     printf("X ");
                     reset_color();
                     printf("| ");
              }
              for(int j=0 ; j<10-mistake ; j++){
                     change_color_rgb(0, 140, 0);//green
                     printf("V ");
                     reset_color();
                     printf("| ");
              }
       }else{
              printf("| ");
              for(int i=0 ; i<mistake ; i++){
                     change_color_rgb(150, 10, 15);//red
                     printf("X ");
                     reset_color();
                     printf("| ");
              }
              for(int j=0 ; j<5-mistake ; j++){
                     change_color_rgb(0, 140, 0);//green
                     printf("V ");
                     reset_color();
                     printf("| ");
              }
       }
       puts(" ");
}

void print_wrong_characters(char wrong_characters[],int counter_lose){//print list of wrong char which user guessed
       change_color_rgb(150, 10, 15);//red
       printf("Wrong characters: ");
       reset_color();
       for(int i=0 ; i<counter_lose ; i++){
              printf("%c ",wrong_characters[i]);
       }
       puts(" ");
}

void get_help(char answer[50],char word[50]){//help user and show one character
       for(int i=0 ; i<strlen(answer) ; i++){//find first digit which is not "_"
              if(answer[i]=='_'){
                     answer[i]=word[i];
                     for(int j=0 ; j<strlen(answer) ; j++){//check if another characters are as same as selected digit
                            if(word[j]==word[i]){
                                   answer[j]=word[i];
                                   counter_word--;//to reduce number of right char which user should guess
                            }
                     }
                     break;
              }
       }
}

void reduce_score(int line){//reduce score if user get help
       typedef struct{
              char username_temp[50];
              char password_temp[50];
              int score_temp;
       }User_copy;
       
       FILE *fptr = fopen("user_list.text","r+");
       int tedad;
       User_copy user_copy[line];

       fscanf(fptr," %d",&tedad);
       
       for(int i=0 ; i<line ; i++){
              fscanf(fptr,"%s %s %d",user_copy[i].username_temp,user_copy[i].password_temp,&user_copy[i].score_temp);
       }

       user_copy[line-1].score_temp--;//reduce score
       loggedin_user.score=user_copy[line-1].score_temp;//set new score
       
       fseek(fptr,0,SEEK_SET);
       fprintf(fptr,"%d\n",tedad);
       for(int i=0 ; i<line ; i++){
              fprintf(fptr,"%s %s %d\n",user_copy[i].username_temp,user_copy[i].password_temp,user_copy[i].score_temp);
       }
       
       fclose(fptr);
}

void change_password(int line){//change password of logged user
       typedef struct{
              char username_temp[50];
              char password_temp[50];
              int score_temp;
       }User_copy;
       char new_password[50];
       while(1==1){
              printf("Plese insert new password:\n");
              printf("(At least 8 character A combination of uppercase letters, lowercase letters, numbers and symbols.\n");
              scanf("%s",new_password);
              if(check_password(new_password)==0){//check if password is acceptable.
                     clear_screen();
                     change_color_rgb(150, 10, 15);//red
                     printf("This password is unacceptable.\n");
                     reset_color();
                     //get another pass
              }else{
                     break;
              }
       }

       FILE *fptr = fopen("user_list.text","r+");
       int tedad;
       User_copy user_copy[line];

       fscanf(fptr," %d",&tedad);
       
       for(int i=0 ; i<line ; i++){
              fscanf(fptr,"%s %s %d",user_copy[i].username_temp,user_copy[i].password_temp,&user_copy[i].score_temp);
       }
       strcpy(user_copy[line-1].password_temp,new_password);
       
       fseek(fptr,0,SEEK_SET);
       fprintf(fptr,"%d\n",tedad);
       for(int i=0 ; i<line ; i++){
              fprintf(fptr,"%s %s %d\n",user_copy[i].username_temp,user_copy[i].password_temp,user_copy[i].score_temp);
       }
       clear_screen();
       printf("Password changed successfully :)\n");
       fclose(fptr);
}

int check_password(char pass[100]){//check if user insert acceptable password
       if(strlen(pass)<8){
              return 0;
       }else{
              for( int i=0 ; i<strlen(pass) ; i++){
                     if((int)pass[i]>96 && (int)pass[i]<123){//check regular character
                            for(int j=0 ; j<strlen(pass) ; j++){
                                   if((int)pass[j]>64 && (int)pass[j]<91){//check capital character
                                          for(int k=0 ; k<strlen(pass) ; k++){
                                                 if((int)pass[k]>47 && (int)pass[k]<58){//check number as character
                                                        for(int z=0 ; z<strlen(pass) ; z++){
                                                               if(((int)pass[z]>122 && (int)pass[z]<127) || ((int)pass[z]>90 && (int)pass[z]<97) ||((int)pass[z]>32 && (int)pass[z]<47) ||((int)pass[z]>57 && (int)pass[z]<65))//check special character
                                                                      return 1;
                                                        }
                                                        return 0;      
                                                 }
                                          }
                                          return 0;
                                   }
                            }
                            return 0;
                     }
              }
              return 0;
       }
}

void print_lose(int mistake){//print "loser" graphical
       change_color_rgb(150, 10, 15);//red
       switch (mistake){
              case 0://print->
                     printf("     _ \n");//line 1
                     printf("    ( \\ \n");//line 2
                     printf("     \\ \\\n");//line 3
                     printf(" _____\\ \\ \n");//line 4
                     printf("(_____)) )\n");//line 5
                     printf("      / / \n");//line 6
                     printf("     / /  \n");//line 7
                     printf("    (_/   \n");//line 8
                     break;
              case 1://print l
                     printf("     _     _ \n");//line 1
                     printf("    ( \\   ( \\ \n");//line 2
                     printf("     \\ \\  | ( \n");//line 3
                     printf(" _____\\ \\ | | \n");//line 4
                     printf("(_____)) )| | \n");//line 5
                     printf("      / / | | \n");//line 6
                     printf("     / /  | (____/\\ \n");//line 7
                     printf("    (_/   (_______/ \n");//line 8
                     break;
              case 2://print lo
                     printf("     _     _         _______ \n");//line 1
                     printf("    ( \\   ( \\       (  ___  )\n");//line 2
                     printf("     \\ \\  | (       | (   ) |\n");//line 3
                     printf(" _____\\ \\ | |       | |   | |\n");//line 4
                     printf("(_____)) )| |       | |   | |\n");//line 5
                     printf("      / / | |       | |   | |\n");//line 6
                     printf("     / /  | (____/\\ | (___) |\n");//line 7
                     printf("    (_/   (_______/ (_______)\n");//line 8
                     break;
              case 3://print los
                     printf("     _     _         _______   _______ \n");//line 1
                     printf("    ( \\   ( \\       (  ___  ) (   ___ \\ \n");//line 2
                     printf("     \\ \\  | (       | (   ) | |  (   \\/\n");//line 3
                     printf(" _____\\ \\ | |       | |   | | |  (____ \n");//line 4
                     printf("(_____)) )| |       | |   | | (_____  )\n");//line 5
                     printf("      / / | |       | |   | |       ) |\n");//line 6
                     printf("     / /  | (____/\\ | (___) | /\\____) |\n");//line 7
                     printf("    (_/   (_______/ (_______) \\_______)\n");//line 8
                     break;
              case 4://print lose
                     printf("     _     _         _______   _______   _______ \n");//line 1
                     printf("    ( \\   ( \\       (  ___  ) (   ___ \\ (  ____ \\ \n");//line 2
                     printf("     \\ \\  | (       | (   ) | |  (   \\/ | (    \\/ \n");//line 3
                     printf(" _____\\ \\ | |       | |   | | |  (____  | (__ \n");//line 4
                     printf("(_____)) )| |       | |   | | (_____  ) |  __) \n");//line 5
                     printf("      / / | |       | |   | |       ) | | ( \n");//line 6
                     printf("     / /  | (____/\\ | (___) | /\\____) | | (____/\\ \n");//line 7
                     printf("    (_/   (_______/ (_______) \\_______) (_______/ \n");//line 8
                     break;
              case 5://print loser
                     printf("     _     _         _______   _______   _______   _______ \n");//line 1
                     printf("    ( \\   ( \\       (  ___  ) (   ___ \\ (  ____ \\ (  ____ )\n");//line 2
                     printf("     \\ \\  | (       | (   ) | |  (   \\/ | (    \\/ | (    )| \n");//line 3
                     printf(" _____\\ \\ | |       | |   | | |  (____  | (__     | (____)|\n");//line 4
                     printf("(_____)) )| |       | |   | | (_____  ) |  __)    |     __) \n");//line 5
                     printf("      / / | |       | |   | |       ) | | (       | (\\ (   \n");//line 6
                     printf("     / /  | (____/\\ | (___) | /\\____) | | (____/\\ | ) \\ \\__ \n");//line 7
                     printf("    (_/   (_______/ (_______) \\_______) (_______/ |/   \\__/ \n");//line 8
              break;
       }
       reset_color();
}

void add_score(int line,int size){//add sizeof(word) score if user win
       typedef struct{
              char username_temp[50];
              char password_temp[50];
              int score_temp;
       }User_copy;
       
       FILE *fptr = fopen("user_list.text","r+");
       int tedad;
       User_copy user_copy[line];

       fscanf(fptr," %d",&tedad);
       
       for(int i=0 ; i<line ; i++){
              fscanf(fptr,"%s %s %d",user_copy[i].username_temp,user_copy[i].password_temp,&user_copy[i].score_temp);
       }
       user_copy[line-1].score_temp+=size;//size = size of digits of selected word
       loggedin_user.score=user_copy[line-1].score_temp;//set new score
       
       fseek(fptr,0,SEEK_SET);
       fprintf(fptr,"%d\n",tedad);
       for(int i=0 ; i<line ; i++){
              fprintf(fptr,"%s %s %d\n",user_copy[i].username_temp,user_copy[i].password_temp,user_copy[i].score_temp);
       }

       fclose(fptr);
}

int check_repeat(char vorodi[],char digit){//check if user insert a character more than once
       for(int i=0 ; i<strlen(vorodi) ; i++){
              if(vorodi[i]==digit){
                     printf("You inserted repeated character.\n");
                     return 0;
              }
       }
       vorodi[counter_vorodi]=digit;
       counter_vorodi++;
       return 1;
}

void check_digit(char word[],char digit,char answer[],char vorodi[],char wrong_characters[]){//check if inserted character is true or false
       int flag=1;
       for(int i=0 ; i<strlen(word);i++){
              if(word[i]==digit){
                     answer[i]=digit;
                     counter_word--;
                     flag=0;
              }
       }
       if(flag==1){
              printf("Wrong suggest.\n");
              wrong_characters[counter_lose]=digit;
              counter_lose++;
       }
}

void print_answer(char answer[],int size){//print array of answer each turn
       for(int i=0 ; i<size ; i++){
              printf("%c ",answer[i]);
       }
       printf("\n\n"); 
}

void game(){//the whole game
       int shansi=0;
       counter_vorodi=0,counter_lose=0;
       clear_screen();
       FILE *fword = fopen("word_list.text","r");

       if(fword == NULL ){
              change_color_rgb(150, 10, 15);//red
              printf("Error! There isn't any words in list. please add new words.\n"); 
              reset_color();
              fclose(fword); 
              FILE *fword = fopen("word_list.text","w+");//create new list when user can't find it
              rewind(fword);
              fprintf(fword,"0");
              fclose(fword);
              user_menu();
              return ;          
       }
       char word[50];
       int tedad=0;
       rewind(fword);
       fscanf(fword," %d",&tedad);//number of words in list

       srand(time(NULL));
       shansi=rand()%tedad+1;
       //printf("%d\n%d\n",tedad,shansi);
       int score_temp=0;
       
       for(int i=0 ; i<shansi ; i++){
              fscanf(fword,"%s %d",word,&score_temp);//get randome word
       }
       fclose(fword);
       char answer[strlen(word)];
       char vorodi[strlen(word)];
       counter_word=strlen(word);
       for(int i=0 ; i<strlen(word);i++){//initialize answer arr with "_"
              answer[i]='_';
       }
       puts(" ");

       print_answer(answer,strlen(word));//print number of digits of selected word
       int flag_get_help=1;
       char digit;
       char wrong_characters[50];
       while(1){
              printf("plese insert a character:\n\n");
              scanf(" %c",&digit);
              if(digit=='1'){//just one time shows get help
                     if(flag_get_help==1){
                            flag_get_help=0;
                            if(loggedin_user.score>0){
                                   clear_screen();
                                   get_help(answer,word);
                                   reduce_score(number_of_logged_user);
                            }else{
                                   clear_screen();
                                   change_color_rgb(150, 10, 15);//red
                                   printf("You don't have enough score to get help.\n");
                                   reset_color();
                            }
                     }
                     goto label_skip_check;
              }
              puts(" ");
              if(check_repeat(vorodi,digit)==1){
                     check_digit(word,digit,answer,vorodi,wrong_characters);
              }
              clear_screen();
              label_skip_check:
              if(flag_get_help==1){
                     printf("For getting help insert '1':\n\n");
              }
              print_answer(answer,strlen(word));

              print_wrong_characters(wrong_characters,counter_lose);

              if(strlen(word)>8){      
                     print_lose(counter_lose/2);
              }else{
                     print_lose(counter_lose);
              }
              print_karbari(counter_lose,strlen(word));
              if(counter_word==0){
                     clear_screen();
                     printf("%s\n",word);
                     change_color_rgb(0, 140, 0);//green
                     printf("YOU WIN!\n");//add score to user
                     printf("you get %d points.\n\n",strlen(word));
                     reset_color();
                     add_score(number_of_logged_user,strlen(word));//mitonim emtiyaz yaro ro chap konim
                     break;
              }else if((counter_lose==5 && strlen(word)<9) || (counter_lose==10 && strlen(word)>8)){
                     change_color_rgb(150, 10, 15);//red
                     printf("YOU LOSE!\n");
                     reset_color();
                     break;
              }
       }
       user_menu();
}

int add_new_word(){//add new word to list
       clear_screen();
       FILE *fword = fopen("word_list.text","r+");

       if(fword == NULL ){
              change_color_rgb(150, 10, 15);//red
              printf("Error the file is empty! please select new word.\n"); 
              reset_color();
              fclose(fword);  
              FILE *fword = fopen("word_list.text","w+");//create new list when user can't find it
              rewind(fword);
              fprintf(fword,"0");
              fclose(fword);
              user_menu();
              return 0;          
       }
       printf("Please insert new word:\n");
       char new_word[50];
       scanf("%s",new_word);
       if(new_word=='\n'){
              printf("Salam");
       }
       int tedad=0;
       rewind(fword);
       fscanf(fword," %d",&tedad);
       int score_temp;
       char temp[50];
       for(int i=0 ; i<tedad ; i++){
              fscanf(fword,"%s %d",temp,&score_temp);
              if(strcmp(temp,new_word)==0){
                     printf("the word already exists.\n\n");
                     fclose(fword);
                     return 0;
              }
       }

       fprintf(fword,"\n%s %lu",new_word,strlen(new_word));

       fseek(fword,0,SEEK_SET);
       tedad++;
       fprintf(fword,"%d\n",tedad);
       clear_screen();
       printf("new word is added.\n");

       fclose(fword);
       return 1;
}

void leaderboard(){//show scores of every player
       clear_screen();
       FILE *fptr = fopen("user_list.text","r");

       if(fptr == NULL ){
              printf("Error!\n");   
              return ;          
       }
       int tedad=0;
       rewind(fptr);
       fscanf(fptr," %d",&tedad);

       User_score user_score[tedad];
       
       char pass_temp[50];
       
       for(int i=0; i<tedad ; i++){
              fscanf(fptr,"%s",user_score[i].username);
              fscanf(fptr,"%s",pass_temp);
              fscanf(fptr," %d",&user_score[i].score);
       }
       
       //it is optional to sort them with score
       for(int i=0 ; i<tedad-1 ; i++){
              for(int j=0 ; j<tedad-1-i ; j++){
                     if(user_score[j].score<user_score[j+1].score){
                            User_score temp=user_score[j];
                            user_score[j]=user_score[j+1];
                            user_score[j+1]=temp;

                     }
              }
       }

       for(int i=0 ; i<tedad ; i++){
              printf("%d->  ",i+1);
              if(i<9){//for print more clear
                     printf(" ");
              }
              printf("%s",user_score[i].username);
              change_color_rgb(245, 255, 76);//yellow
              for(int j=0 ; j<18-strlen(user_score[i].username) ; j++){
                     printf(".");
              }
              reset_color();
              printf("%d\n",user_score[i].score);
       }
       
}

void user_menu(){//second menu
       int option=0;
       change_color_rgb(0, 100, 255);//blue
       printf("1-> Start game\n2-> Show leaderboard\n3-> New word\n4-> Change Password\n5-> Exit\n");
       printf("Plese insert an options to continue (just type number):\n");

       scanf(" %d",&option);
       reset_color();
       switch (option){
              case 1://start game function
                     game();
                     break;
              case 2://show leaderboard function
                     leaderboard();
                     printf("\n");
                     user_menu();
                     break;
              case 3://add new word function
                     while(add_new_word()==0){//if new_word has problem             
                     }
                     user_menu();
                     break;
              case 4:
                     change_password(number_of_logged_user);
                     menu_login();
                     break;
              case 5://exit to login_menu and log out 
                     clear_screen();
                     menu_login();
                     break;
              default:
                     clear_screen();
                     user_menu();
       }
}

int signup(){//register new user
       FILE *fptr = fopen("user_list.text","r+");

       if(fptr == NULL ){
              change_color_rgb(150, 10, 15);//red
              printf("Error the file is empty! please try again and select singup.\n"); 
              reset_color();
              fclose(fptr); 
              FILE *fptr = fopen("user_list.text","w+");//create new list when user can't find it
              rewind(fptr);
              fprintf(fptr,"0");
              fclose(fptr);
              return 0;          
       }

       char new_user[50],new_pass[50];
       printf("Plese insert new username:\n");
       scanf("%s",new_user);

       int tedad=0;
       rewind(fptr);
       fscanf(fptr,"%d",&tedad);
       if(tedad==0){
              rewind(fptr);
              fprintf(fptr,"0");
       }
       //printf("%d\n",tedad);
       char username[tedad][50];
       char temp[50];
       int temp_score=0;
       for(int i=0 ; i<tedad ; i++){
              fscanf(fptr,"%s",username[i]);
              if(strcmp(username[i],new_user)==0){//check if we have any user at the same name
                     clear_screen();
                     change_color_rgb(150, 10, 15);//red(error)
                     printf("the username already exists.\n");
                     reset_color();
                     fclose(fptr);
                     signup();//get another username and pass
                     return 0;
              }
              fscanf(fptr,"%s",temp);
              fscanf(fptr," %d",&temp_score);
       }

       while(1==1){
              printf("Plese insert new password:\n");
              printf("(At least 8 character A combination of uppercase letters, lowercase letters, numbers and symbols.\n");
              scanf("%s",new_pass);
              if(check_password(new_pass)==0){//check if password is acceptable.
                     clear_screen();
                     change_color_rgb(150, 10, 15);//red(error)
                     printf("This password is unacceptable.\n");
                     reset_color();
              }else{
                     break;
              }
       }
       fprintf(fptr,"\n%s %s %d",new_user,new_pass,0);
       fseek(fptr,0,SEEK_SET);
       tedad++;
       rewind(fptr);
       fprintf(fptr,"%d",tedad);
       clear_screen();
       printf("new username is added.\n");
       
       fclose(fptr);
       return 1;
}

int login(){//login
       clear_screen();
       FILE *fptr = fopen("user_list.text","r");

       if(fptr == NULL ){
              change_color_rgb(150, 10, 15);//red
              printf("Error with opening file! please signup fisrt.\n");
              reset_color();
              fclose(fptr);
              return 0;          
       }
       int tedad=0;
       rewind(fptr);
       fscanf(fptr," %d",&tedad);
       char username[tedad][50];
       char password[tedad][50];
       int score[tedad];
       char find_user[50];
       char find_pass[50];

       printf("Plese insert username:\n");
       scanf("%s",find_user);
       printf("Plese insert password:\n");
       scanf("%s",find_pass);
       for(int i=0 ; i<tedad ; i++){
              fscanf(fptr,"%s",username[i]);
              fscanf(fptr,"%s",password[i]);
              fscanf(fptr," %d",&score[i]);
       }
       puts(" ");
       int flag=0;
       for(int i=0 ; i<tedad ; i++){
              if(strcmp(username[i],find_user)==0){
                     if(strcmp(password[i],find_pass)==0){
                            clear_screen();
                            change_color_rgb(0, 140, 0);//green
                            printf("username and password are right :) \n\n");
                            strcpy(loggedin_user.username,username[i]);
                            loggedin_user.score=score[i];
                            number_of_logged_user=i+1;
                            //printf("i==%d\n%s\n%d\n",i+1,loggedin_user.username,loggedin_user.score);
                            reset_color();
                            fclose(fptr);
                            return 1;
                     }else{
                            clear_screen();
                            change_color_rgb(150, 10, 15);//red
                            printf("password is wrong :( \n\n");
                            fclose(fptr);
                            reset_color();
                            return 0;
                     }
                     flag=1;
              }
       }
       if(flag==0){
              clear_screen();
              change_color_rgb(150, 10, 15);//red
              printf("username not found!\n\n");
              return 0;
              reset_color();
       }
       fclose(fptr);
}

void menu_login(){//first menu
       int option=0;
       change_color_rgb(0, 140, 0);//green
       printf("1-> Login\n2-> Signup\n3-> Exit\n");
       printf("Plese insert an options to continue (just type number 1 or 2 or 3):\n");

       scanf(" %d",&option);
       reset_color();
       switch (option){
              case 1://call login function
                     if(login()==1){//check if user and pass are right.
                            user_menu();
                            break;
                     }else{
                            menu_login();
                     }
              case 2://call signup function
                     clear_screen();
                     signup();//add new user and then go to login_menu
                     menu_login();
                     break;
              case 3://call exit and finish whole the program
                     clear_screen();
                     change_color_rgb(150, 10, 15);//red
                     printf("Goodbye and have fun!\n");
                     reset_color();
                     break;
              default://if user insert any otherthings
                     clear_screen();
                     menu_login();
       }
       exit(1);
}

int main(){
       clear_screen();
       menu_login();//first menu
       return 0;
}