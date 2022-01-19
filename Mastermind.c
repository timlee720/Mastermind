#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
//------------------------------------------------------------------------------global array
int score;//score in int
int duplicate=1;// 1=allow ,0=not allow
int chance=9;//store the chances to guess
int mark;//to store the number of data in recorded
int superuser=0;//permission of superuser (1=enable,0=unable)
char answer[10];//store answer code
char n[30];//store player name 
char num[9];//store player phone number
char name[100][30];//store recorded name
char phone[100][20];//store recorded phone number
char result[100][10];//store recorded mark
char pt[100][10];//store recorded play time
char rank[100][6];//store recorded rank
char s[10];//score in char
//------------------------------------------------------------------------------For AI 
char g_code[5]; //code guessed by user or algorithm
char a_code[5]; //code guessed by user or algorithm
char allcode[4096][5];//store all possible answer
char initial=1;
int hins;       //result for ai to check
int position;   //
char rightcode[5];
int checkmark=0;
int lastposition;
//--------------------------------------------------------------------------------File I/O
FILE*fp; //read
FILE*fp2;//write
int newtxt(){
     fp2=fopen("RANK.TXT","w");
     //printf("newtxt\n");
     fprintf(fp2,"%-6s%-30s%-20s%-12s%-10s\n","Rank","Player_Name","Phone_Number","Mark","Play_Time");
     fclose(fp2);
}

void read(){
	 mark=0;
	 fp=fopen("RANK.TXT","r");
	 if(fp==NULL)
	 newtxt();
	 fclose(fp);
	 fp=fopen("RANK.TXT","r");
	 while(fscanf(fp,"%6s%30s%20s%12s%10s",rank[mark],name[mark],phone[mark],result[mark],pt[mark])!=EOF)
	 	//printf("%-20s%-20s%-20s",n[mark],s[mark],t[mark]);
	       mark=mark+1;
           //printf("mark=%d\n",mark);
	 fclose(fp);
}
   
int display(){
    int i=0;
    fp=fopen("RANK.TXT","r");
    do{
       printf("%-6s%-32s%-20s%-12s%-10s",rank[i],name[i],phone[i],result[i],pt[i]);
       i++;
    }while(i<mark);
    printf("\n");
    fclose(fp);
} 

int swape(int a,int b){
	char temp[30];
	strcpy(temp,name[a]);
	strcpy(name[a],name[b]);
	strcpy(name[b],temp);         //
	strcpy(temp,result[a]);
	strcpy(result[a],result[b]);
	strcpy(result[b],temp);       //
	strcpy(temp,pt[a]);
	strcpy(pt[a],pt[b]);
	strcpy(pt[b],temp);           //   
    strcpy(temp,phone[a]);
	strcpy(phone[a],num);
	strcpy(num,temp);             //
}

void exist(){
	int i,k;     //if exist,i=999
	for (i=0;i<mark;i++){         
		if (strcmp(name[i],n)==0){
		   //printf("exist\n");
		   if (strcmp(result[i],s)<=0)
		      strcpy(result[i],s);
		   k=atoi(pt[i]);
		   k++;
		   sprintf(pt[i],"%d",k);
		   i=998;
	    }
	}
	//printf("%d\n",i);
	if (i!=999){
	   //printf("no exist\n");
       strcpy(name[mark],n);
       strcpy(result[mark],s);
       strcpy(pt[mark],"1");
       sprintf(rank[mark],"%d",mark);
       strcpy(phone[mark],num);
	   //printf("-%6s%-30s%-20s%-12s%-10s",rank[mark],name[mark],phone[mark],result[mark],pt[mark]);
	   mark++;
	}
}
	
void sort(){
	int i=1,j,flag=0,win;
	//printf("mark=%d",mark);
	fp2=fopen("RANK.TXT","w");
	fprintf(fp2,"%-6s%-30s%-20s%-12s%-10s\n",rank[0],name[0],phone[0],result[0],pt[0]);
		while(i<mark){
			 for (j=i+1 ;j<mark;j++){
		         if (strcmp(result[j],result[i])>0)
                    swape(i,j);
		         else if (strcmp(result[j],result[i])==0)
		                 if (strcmp(pt[j],pt[i])<0)
		                    swape(i,j);}
		     //printf("added %d",mark);
		//fprintf(fp2,"%-20s%-20s%-20s\n",n[win],s[j],t[j]);
	    fprintf(fp2,"%-6d%-30s%-20s%-12s%-10s\n",i,name[i],phone[i],result[i],pt[i]);
		i++;}
	fclose(fp2);	
}
	
void search(){
     int i=1,flag;
     char k;
     renew(0,15);
     printf("Please enter your name:");
     scanf("%s",&n);
     fflush(stdin);
     do{
         if (strcmp(name[i],n)==0){
            flag=1;
            printf("This is the record you search for:\n");
            textcolor(2);
            printf("%-6s%-30s%-20s%-12s%-10s\n",rank[0],name[0],phone[0],result[0],pt[0]);
            printf("%-6s%-30s%-20s%-12s%-10s\n",rank[i],name[i],phone[i],result[i],pt[i]);
            textcolor(15);
            }
         i++;
     }while(i<mark&&flag!=1);
     if (flag!=1)
        printf("Your record is not existed !\n");
     printf("Enter 'R' to search another record\n");
     printf("Enter another key to back to main menu\n");
     scanf("%c",&k);
     if (k=='R'||k=='r')
        search();
     main();
}
//------------------------------------------------------------------------------Game process
void messagebox(int m){
     int i,x,y;
     char message[10][50]={"Invalid command,please try again !",
                           "your phone number is too long!Please try again !",
                           "your phone number is too short!Please try again !",
                           "Your first number should not be ""0"" !",
                           "Invalid phone number !",
                           "Invalid command,please try again!"};
     x=wherex();
     y=wherey();
     gotoxy(1,20);
     for (i=1;i<=80;i++)
         printf("=");
     for (i=24;i>20;i--)
         printf("%-79c%c",'|','|');
     gotoxy(2,22);
     printf("%55s",message[m]);
     //gotoxy(2,22);
     //clreol();
     if (m==0){
        gotoxy(x,y);
        system("pause");
        }
     else{
        gotoxy(1,y-1);
        clreol(); 
        }
     }

int sure(){          //if sure flag=0
    int check,flag;
    char YesNo;
    printf("Are you sure your information had been entered correctly? <Y/N>\n");
    do{
       check=1;
       scanf("%c",&YesNo);
       fflush(stdin);
       if (YesNo=='Y'||YesNo=='y')
          flag=0;
       else if (YesNo=='N'||YesNo=='n')
               flag=99;
       else {
            check=0;
            messagebox(5);
            }
    }while(check!=1);
    return flag;
    }
    
int check(char code[],int n,char answer[]){
    int i,j,pass[2][10],match=0,sim=0;//pass[0]<-answer
    for(i=0;i<2;i++)                  //pass[1]<-code
          for(j=0;j<n;j++)
          pass[i][j]=0;
    for (j=0;j<n;j++)
        for (i=0;i<n;i++)
            if (answer[i]==code[j]&&pass[0][i]!=2){ 
               if (j==i){
         //printf("do i=%d j=%d \n",i,j);
                  match=match+1;
        // printf("i=%d,j=%d +match\n",i,j);
         //if (pass[1][j]==1){
            //printf("-sim\n");
            //sim=sim-1;}
                  pass[0][i]=2;
                  pass[1][j]=2;
                  i+=n;
                  }
                }
    for (j=0;j<n;j++)
    //printf("a=%c \n",a[j]);
        for (i=0;i<n;i++)
            if (answer[i]==code[j])
               if (pass[0][i]==0&&pass[1][j]==0){
                  pass[0][i]=1;
                  pass[1][j]=1;
                  sim=sim+1;
             //printf("j=%d i=%d\npass=%d+sim\n",j,i,pass[1][j]);
                  }
    printf("t=%d s=%d\n",match,sim);
    printf("======================");
    if (match==n)
       return 1;
    else 
       return 0;
    }

int spawnanswer(int n1,int n2){//n1 = digit
    int i,j,num;               //n2 = colors
    char n3[2][8]={"without","with"};
    printf("You need to guess %d digit code in %d colors %s duplicate!\n",n1,n2,n3[duplicate]);
    for(i=0;i<n1;i++){
       num=rand()%n2+48;
       //printf("num=%d",num);
       answer[i]=num;
       if (duplicate==0&&i>0)
          for(j=i-1;j>=0;j--)
             if (answer[i]==answer[j])
             {
                j=-10;
                i=0;}
    }
    answer[i]='\0';  
    if (superuser==1)
       printf("The answer is %s",answer);
}
int getanswer(int n,int m,int mode){    //mode 1=single
    int i,j,len,flag,bingo,result,a[20];//mode 2=multiplay
    char g[n+1];                        //mode 3=player vs AI
    if (mode!=3){                       //n=digit,m=colors
       chance=8;
       printf("\nGuess %d number\n",m);
    }
    else 
       printf("Is your turn\n");
    do{
      fflush(stdin);
      scanf("%s",&g);
      len=strlen(g);
      flag=0;
      fflush(stdin);
      if (len!=n){
         printf("You entered %d color,please try again!\n",len);
         fflush(stdin);
         flag=1;}
      else if (duplicate==0){
         for (i=0;i<n;i++)
             for (j=i+1;j<n;j++)
                 if (strncmp(&g[i],&g[j],1)==0){
                    printf("In this gamemode ,duplicate number is not allowed.please try again!\n");
                    flag=1;
                    i=99;
                    j=99;
                    }
             }
      else 
          for (i=0;i<n;i++){
              a[i]=g[i]-'0';
              if (a[i]>=m||a[i]<0){
                 printf("%c is a wrong color number,please try again!\n",g[i]);
                 fflush(stdin);
                 i=99;
                 flag=1;}
            }
     if (flag==0){ 
        g[i]='\0'; 
        if (mode==3)
           bingo=1;          
        else
           bingo=check(g,n,answer);
           if (bingo==0){
              chance--;
              textcolor(4);
              printf("You have %d chance to guess!\n",chance);
              textcolor(0);
              }
        }
    }while(flag!=0||len!=n||bingo==0&&chance!=0);
    if (mode!=3){
       renew(15,0);
       result=end(bingo,mode);  
       }
    else
       strcpy(g_code,g);
}
//------------------------------------------------------------------------------
int showcolor(int num2){
    int i;
    char color[8][15]={"BLUE",	       
                      "GREEN",
                      "CYAN",	
                      "RED",	
                      "MAGENTA",	
                      "BROWN",
                      "LIGHTGRAY",
                      "DARKGRAY"};
    renew(15,0);
    gotoxy(65,2);
    printf("| TO ENTER:\n");
    for (i=0;i<num2;i++){
        textcolor(i+1);
        printf("%65c %d=%s\n",'|',i,color[i]);
    }
    printf("%65c==============",'=');
    textcolor(0);
    gotoxy(1,2);
    }

int renew(int bgcolor,int txtcolor){
    int i,j;
    fflush(stdin); 
    textbackground(bgcolor); 
    system ("cls");
    for (j=1;j<=25;j+=24){
        gotoxy(1,j);
    for (i=1;i<=80;i++){
        textcolor(rand()%9);
        printf("=");}
    }
    gotoxy(35,1);
    textcolor(txtcolor);
    printf("=MasterMind=");
    gotoxy(1,2); 
    textcolor(txtcolor);   
}
//------------------------------------------------------------------admin mode
int login(){                     
    char password[20];
    renew(0,15);
    if (superuser==0){
       printf("Enter the password to login the admin game mode\n");
       scanf("%s",&password);
       fflush(stdin);
       if (strcmp(password,"admin")==0){
          printf("You have enter the admin mode,the answer will be showed in the game\n");           
          superuser=1;                    
       }
    else 
       printf("You have enter a wrong password !");
       }
    else{
       printf("You have been a admin ,now!\n");
       printf("If you want to login out,enter 'Y',else enter 'N'\n");
       scanf("%c",&password[0]);
       fflush(stdin);
       if (password[0]=='Y'||password[0]=='y'){
          printf("You have logout!\n");
          superuser=0;
          }
       }
    printf("Enter another key to back to the main menu.\n");
    scanf("%c",&password[0]);
    fflush(stdin);
    main();
    }
//------------------------------------------------------get user's information
int playerinfo(){          
     int i,flag=1,check;
     do{
        if (flag==1){
           flag=0;
           renew(0,15);
           printf("Welcome to ABC school!\nBefore start the game,please enter your information to recording the result.\n");
           printf("Player who get the highest marks will be given a gift!\n");
           printf("Your information will be delete after school open day!\n");
           printf("What is your name?\n");
           scanf("%s",&n);
           fflush(stdin);
           printf("What is your phone number?\n");  
           }
           flag=0;
           scanf("%s",&num);
           fflush(stdin);
           if (strlen(num)==8)
              flag=1;
           else if (strlen(num)>8)
                   messagebox(1);
           else if (strlen(num)<8)
                   messagebox(2);
           else if (num[0]=='0')
                   messagebox(3);
           else 
               for (i=0;i<8;i++)
                   if (num[i]>'9'||num[i]<'0'){
                      messagebox(4);
                      i=9;
                      }      
     if (flag==1)
        check=sure();
     }while(check!=0);
     renew(15,0);
     printf("It will be start in 3 second,Enjoy your game!");
     for(i=3;i>0;i--){
        gotoxy(1,3);
        printf("%d",i);              
        delay(1000);
        }
     }

//------------------------------------------------------------------------------Main game (user function)

int play(int type){                    //type 1=single,type 2=multiplay
    int num1=4,num2=8,i;               //num1=number of digit	       
    fflush(stdin);                     //num2=number of color
    if (type==1){
       difficult(&num1,&num2); 
       playerinfo();}
    showcolor(num2);
    if (type==1)
       spawnanswer(num1,num2);
    else if (type=2)
            printf("Now,Player2 guess the answer\n");
    getanswer(num1,num2,type);
    }  
    
//------------------------------------------------------------------------------Set answer by player
int SetAnswer(int num1,int num2 ,int mode){  //mode 0 = Multiplay
    int i,j,flag,check,a[20];                //mode 1 = AI vs computer
    char n1[2][7]={"without","with"};        //num1=digit , num2=colors
    char n2[2][15]={"Multiplay","AI Vs Computer"};
    //printf("You need to guess %d digit code in %d colors %s duplicate!\n",num1,num2,n2[duplicate]);
    showcolor(num2);
    printf("In %s gamemode,the score will not be recorded!\n",n2[mode]);
    if (mode==0)
       printf("Player 1:\nPlease enter %d number in %d colors %s duplicate as the answer!\n",num1,num2,n1[duplicate]);
    else 
       printf("Please enter %d number in %d colors %s duplicate as the answer!\n",num1,num2,n1[duplicate]);
    do{
       do{
         flag=0;
         scanf("%s",&answer);
         fflush(stdin);
         if (strlen(answer)!=num1){
            printf("You entered %d color,please try again!\n",strlen(answer));
            fflush(stdin);
            flag=1;
            }
         else if (duplicate==0){
                 for (i=0;i<4;i++)
                     for (j=i+1;j<4;j++)
                         if (strncmp(&answer[i],&answer[j],1)==0){
                            printf("In this gamemode , duplicate number is not allow.please guess again!\n");
                            flag=1;
                            i=99;
                            j=99;
                            }
                 }
         else 
             for (i=0;i<num1;i++){
                 a[i]=answer[i]-'0';
                 if (a[i]>=num2||a[i]<0){
                    printf("%c is a wrong color number,please try again!\n",answer[i]);
                    fflush(stdin);
                    i=99;
                    flag=1;}
                 }
         }while(flag==1);
    check=sure();
    }while(check!=0);
    if (mode==0)
       play(2);
}
//------------------------------------------------------------------------------
int difficult(int*num1,int*num2){
    int gm,flag,check,i;
    char message[5][30]={"1:Newbie",
                         "2:Normal",
                         "3:Hell on the world",
                         "4:Define difficulty yourself",
                         "5:Back to Main Menu"};
    do{
      renew(0,15);
      for(i=0;i<5;i++)
      printf("%-50s%c\n",message[i],'|');
      printf("===================================================\n");
      printf("Select the gamemode:");
      scanf("%d",&gm);
      fflush(stdin);
      if (gm>5||gm<1){
         messagebox(0);
         }
    }while(gm>5||gm<1);
    if (gm==1){
       *num1=4;
       *num2=4;
       duplicate=0;}
    else if (gm==2){
            *num1=4;
            *num2=4;
            duplicate=1;}
    else if (gm==3){
            *num1=8;
            *num2=8;
            duplicate=1;}
    else if (gm==4){
            do{
            renew(0,15);
            printf("How long of code you want to guess? <'4' to '12' digit>\n");
            do{
               flag=0;
               scanf ("%d",&*num1);
               fflush(stdin);
               if (*num1<4||*num1>12){
                  printf("Invalid number is entered,please try again! %d\n",*num1);
                  flag=1;}
            }while(flag!=0);
            printf("How many number of colors you want to guess?  <'4' to '8' type of colors>\n");
            do{
                flag=0;
                scanf("%d",&*num2);
                fflush(stdin);
                if (*num2<4||*num2>8){
                   printf("Invalid number is entered,please try again! %d\n",*num2);
                   flag=1;}
            }while(flag!=0);
            printf("Allow duplicate? <Yes=1>/<No=0>\n");
            do{
                flag=0;
                scanf("%d",&duplicate);
                fflush(stdin);
                if (duplicate!=1&&duplicate!=0){
                   printf("Invalid number is entered,please try again!\n");
                   flag=1;}
            }while(flag!=0);
            check=sure();
            }while(check!=0);
            }
    else
        main();
    score=*num1+*num2;
    }
//--------------------------------------------------------------------------------------AI section    
void baseNcounter(int num[],int n){
     int i,j,find;
     do{
     find=0;
     num[3]++;
     if (num[3] == n){
        num[2]++;
         if  (num[2] == n){
             num[1]++;
             if (num[1] == n){
                num[0]++;
                if (num[0]==n) 
                   num[0] = 0;
                   num[1] = 0;
             }
             num[2] = 0;
         }
         num[3] = 0;
     }
     if (duplicate==0)
         for (i=3;i>0;i--)
             for(j=i-1;j>=0;j--)
             if(num[i]==num[j]){
             find=1;
             i=-1;
             j=-1;
             }                
     }while(find==1);
     num[4]='\0';
}

void setallcode(char allcode[4096][5],int n){
     int i,j,k;
     int code[4]={0,0,0,0};
     k=pow(n,4);
     if (duplicate==1)
        sprintf(allcode[0],"0000");
     else 
         sprintf(allcode[0],"0123");
     for (i=1;i<k;i++){
         baseNcounter(code,n);
         for (j=0;j<4;j++)
             allcode[i][j]=code[j]+'0';
         if (duplicate==0){
            if (code[0]==n)
               k=0;
               //system ("pause");
         }
     }
     strcpy(rightcode,allcode[i-1]);
     printf("AI:There are 1/%d possibility\n",i);
}

int AIcheck(char code[],int n,char answer[]){
    int i,j,pass[2][4],match=0,sim=0;//pass[0]<-answer
    for(i=0;i<2;i++)                 //pass[1]<-code
          for(j=0;j<4;j++)
          pass[i][j]=0;
    for (j=0;j<n;j++)
    for (i=0;i<n;i++)
    if (answer[i]==code[j]&&pass[0][i]!=2){ 
       if (j==i){
         //printf("do i=%d j=%d \n",i,j);
         match=match+1;
         //printf("i=%d,j=%d +match\n",i,j);
         //if (pass[1][j]==1){
            //printf("-sim\n");
            //sim=sim-1;}
         pass[0][i]=2;
         pass[1][j]=2;
         i+=n;}
    }
    for(j=0;j<n;j++)
    //printf("a=%c \n",a[j]);
    for (i=0;i<n;i++)
       if (answer[i]==code[j])
          if (pass[0][i]==0&&pass[1][j]==0){
             pass[0][i]=1;
             pass[1][j]=1;
             sim=sim+1;
             //printf("j=%d i=%d\npass=%d+sim\n",j,i,pass[1][j]);
             } 
    //printf("%d",match*10+sim);
    //printf("|%s| b=%d w=%d\n",code,match,sim);
    return match*10+sim;
    }

void renewcode(char postcode[]){
     if(hins==AIcheck(postcode,4,a_code)){
       strcpy(allcode[position],postcode);
       //printf("%d|%s|\n",position+1,allcode[position]);
       position++;
     }
     if(strcmp(postcode,rightcode)==0){
       strcpy(rightcode,allcode[position-1]);
       //printf("Renewed %s,there are %d possibility which is %d(checked %d)\nlast code is %s\n",a_code,position,hins,checkmark,rightcode);     
       lastposition=position;
       checkmark=0;
       }
     else {
         checkmark++;
         renewcode(allcode[checkmark]);  
    }
}

void MinMax(){
     int sum,division,count=0,find,i,j,king,lastscore,score[9999],post_score;
     int min=99999;
     float average;
     while (count<lastposition){
           sum=0;
           division=0;
           for (i=0;i<lastposition;i++){         ///////////////////////////////find the average hin of a code if we guess it
               find=0;
               post_score=AIcheck(allcode[i],4,allcode[count]);
               if (division==0){
                  score[0]=post_score;
                  score[1]=1;
                  division=1;
                  }
               else{
                   lastscore=division*2-2;        //mark the position of last score
                   for (j=lastscore;j>=0;j-=2)    //store hins
                       if(post_score==score[j]){
                       score[j+1]++;
                       find=1;
                       j=-1;                      //exit
                       }
                   if (find==0){
                      score[lastscore+2]=post_score;
                      score[lastscore+3]=1;
                      division++;           
                      }
                   }
               sum++;    
               }
               
           average=lastposition/division;
           if (average<min){
              min=average;
              king=count;                             
              }             ////////////////////////////////
           count++;
           }
     position=king;
}     
     
void AIguess(num,mode,AIlevel){        
     int i=0,j=0,turn=0,playermark=0;        //mode1=Player vs AI
     renew(0,15);                            //mode2=AI vs Computer
     showcolor(num);
     setallcode(allcode,num);                //turn0=ai
     position=0;                             //turn1=player or AI player
     do{        
        strcpy(a_code,allcode[position]);
        //printf("%s,%s",answer,a_code);
        hins=AIcheck(a_code,4,answer);
        i++;
        printf("AI:my guess is %s \n",a_code);
        printf("T=%d S=%d\n",hins/10,hins%10);
        printf("======================\n");
        if (hins!=40&&mode==1){       
           getanswer(4,num,3);
           playermark=AIcheck(g_code,4,answer);
           chance--;
           }
        if (hins!=40&&playermark!=40){
           if (playermark>hins&&AIlevel>2){
              hins=playermark;
              strcpy(a_code,g_code);
              //system ("pause");
           }
           position=0;
           renewcode(allcode[position]);
           if (AIlevel>1)
              MinMax();//<-------------------------find out which code is better to guess
           else 
              position=0;
           }
        chance--;
        system ("pause");
        if (mode==3){
           strcpy(g_code,allcode[position]);
           playermark=AIcheck(g_code,4,answer);
           printf("AI player:my guess is %s\n",g_code);
           printf("T=%d S=%d\n",playermark/10,playermark%10);
           printf("======================\n");
           if (playermark!=40)
              MinMax();
           j++; 
           chance--;
           printf("%d chance to guess!\n",chance);
           //turn=1;                     
        }
     }while(playermark!=40&&hins!=40&&chance!=0);
     if (hins==40) 
        printf("\n\nAI:I did it in %d guess",i);
     else if(playermark==40&&mode==3)
            printf("\n\nAI player:I won! I get it in %d guess",j);
     else if(hins==40&&mode==2)
        printf("AI:I am fail\n");
     else 
        printf("AI:We are lose\n");
     printf("The answer is %s\n\n",answer);
     printf("Press any key to main menu:");
     scanf("%d",num);
     fflush(stdin);
     main();
     }

void AImode(){
     int i,num,gamemode,flag,check,set,AIlevel;                //setanswer used in gamemode 2
     char message[5][50]={"AI mode menu",
                          "The result will not be recorded in AI mode!",
                          "1;Player vs AI",                    //gamemode1=Player vs AI
                          "2:AI vs Computer",                  //gmaemode2=AI vs Computer
                          "3:AI Player vs AI"};     //gamemode3=AI player vs AI
     renew(0,15);   
     for (i=0;i<5;i++)                                         
         printf("%-15c%-50s%c\n",'|',message[i],'|');
     printf("==================================================================\n");                                    
     printf("Please select AI gamemode:\n");
     do{
       scanf("%d",&gamemode);
       fflush(stdin);
       if (gamemode>3||gamemode<1)
          messagebox(5);
     }while(gamemode>3||gamemode<1);
     do{
        renew(0,15);
        printf("Intelligen level of AI ? <lower'1' to higher'3'>\n");
        do{
           flag=0;
           scanf("%d",&AIlevel);
           fflush(stdin);
           if (AIlevel<1|AIlevel>3){
              messagebox(5);
              flag=1;}
        }while(flag!=0);
        
        printf("How many number of colors you want to guess?  <'4' to '8' type of colors>\n");
        do{
           flag=0;
           scanf("%d",&num);
           fflush(stdin);
           if (num<4||num>8){
              messagebox(5);
              flag=1;}
        }while(flag!=0);
        
        printf("Allow duplicate? <Yes=1>/<No=0>\n");
        do{
           flag=0;
           scanf("%d",&duplicate);
           fflush(stdin);
           if (duplicate!=1&&duplicate!=0){
              messagebox(5);
              flag=1;}
        }while(flag!=0);
        
        printf("How many chances to guess? <'2' to '99'>\n");
        do{
           flag=0;
           scanf("%d",&chance);
           fflush(stdin);
           if (chance>99||chance<2){
              messagebox(5);
              flag=1;}
        }while(flag!=0);
        check=sure();
     }while(check!=0);
     
        if (gamemode!=1){
           renew(0,15);
           printf("Would you like to set the answer? <Yes=1>/<No=0>\n");
           do{
              flag=0;
              scanf("%d",&set);
              fflush(stdin);
              if (set!=1&&set!=0){
                 messagebox(5);
                 flag=1;}
           }while(flag!=0);
           if (set==1)
              SetAnswer(4,num,1);
           }     
     spawnanswer(4,num);
     AIguess(num,gamemode,AIlevel);
     }
     
int end(int type,int mode){
    int y=5,flag=1;
    char get; 
    score=(score+chance)*(type+duplicate);
    sprintf(s, "%d", score);
    gotoxy(1,2);
    printf("The correct answer is:%s\n",answer);
    if (type==1){
       textcolor(4);
       if (mode==1){
          read();
          exist();
          sort();
          printf("Bingo!,you get %d marks,your result have been recorded !\n",score);}
       else if (mode==2)
               printf("Bingo! Player2 win the game and get %d marks\n",score);}
    //gotoxy(30,y+1);
    else if (type==0){
            textcolor(4);
            if (mode==1)
               printf("Sorry you are fail,your result have been recorded\n");
            else if (mode==2)
                    printf("Player1 win the game !\n");
            }
    textcolor(0);
    printf("Press q back to the main menu\n");
    printf("Press r to check your ranking\n");
    do{
       fflush(stdin);
       scanf("%c",&get);
       if (get!='q'&&get!='r')
          //printf("You enter a wrong command!Please try again!");
          messagebox(5);
       else 
          flag=0;
     }while (flag==1);
     if (get=='q')
        main();
     else 
        show_ranking();}

//--------------------------------------------------------------------------------menu page   
void menu(){
     int i;
     char str[4][20]={"How to play",
                      "Play",
                      "Ranking",
                      "Quit Game"};
     renew(0,15);
     printf("%-15cWelcome to the MasterMind!%15c\n",'|','|');
     for(i=0;i<4;i++)
        printf("%-15c%d:%-38s%c\n",'|',i+1,str[i],'|');
        printf("========================================================\n");
     }
     
int menu_select(){
     int choice;
     do{
        menu();
        printf("Enter the number of option to be continue:" );
        scanf("%d",&choice);
        fflush(stdin);
        if (choice>4||choice<1){
           messagebox(0);
           //printf("Invalid option is selected,please try again!\n");
           }
     }while(choice>4||choice<1);
     return choice;     
     }

void display_rule(){
     char g; 
     do{
     renew(0,15);
     printf("Rule of Mastermind\n");
     printf("The computer picks a sequence of colors randomly.\nThe number of colors and the code length will be changed in different difficult.");
     printf("We need to guess the exact positions of the colors in sequence.\n");
     printf("After enter your answer\nEach color in your answer that is in the correct color  and correct position.\n'T' will be displayed.\n"); 
     printf("Each color in your answer that is in the correct color but 'NOT' in the correct position.\n'S'will be displayed.\n");
     printf("How to win?\nGuess the correct answer in limited attempts,you will win the game!\n");
     printf("If you cannot guess the correct answer in  limited attempts,you will lose!\n");
     printf("About the score of each game");
     printf("The score of each game is depend on the difficult.\nTry your best to get a higher mark!\n");
     printf("Enter 'b' back to the main menu:");
        scanf("%c",&g);
        fflush(stdin);
        if (g!='B'&&g!='b')
           messagebox(0);
     }while(g!='B'&&g!='b');
     main();
}
void gamemode_select(){
     int gm,i;
     char message[5][20]={"1:Single-play",
                          "2:Multi-play",
                          "3:AI mode",
                          "4:Admin mode",
                          "5:Back to main menu"};
     do{
       renew(0,15);
       for (i=0;i<5;i++)
           printf("%-15c%-40s%c\n",'|',message[i],'|');
       printf("========================================================\n");
       printf("Select the gamemode:");
       scanf("%d",&gm);
       fflush(stdin);
       if (gm>5||gm<1){
          messagebox(0);
          }
     }while(gm>5||gm<1);
     if (gm==1)
        play(1);
     else if (gm==2)
             SetAnswer(4,8,0);
     else if (gm==3)
             AImode();
     else if (gm==4)
             login();
     else 
         main();
    }

int show_ranking(){
     char k;
     renew(0,15);
     read();
     display();
     printf("Enter 'S' to search your record.\n");
     printf("Enter another key to back to the main menu\n");
        scanf("%c",&k);
        fflush(stdin);
        if (k=='S'||k=='s')
           search();
     main();
     //newtxt();
     //printf("this is the ranking\n");
     }

int main(){
    int choice;
    srand(time(NULL));
    choice=menu_select();
    if (choice==1)
       display_rule();
    else if (choice==2)
            gamemode_select();
    else if (choice==3)
            show_ranking();
    else
        printf("BYE !");           
    system ("pause");
    return 0;   
}
