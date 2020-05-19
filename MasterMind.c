#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

typedef struct player{ //��@�Ӹ���������@�ӷs�W�r,�ϭ�l�X�����\Ū�M�z�ѡC
	char Name[20];
	int mark;
	int time;
	int chance;	
} players;

void SetColor(int ForgC) { //ref:http://www.programming-techniques.com/2011/08/how-to-change-text-color-of-console.html (�t�d�]�m��r���C��)
     WORD wColor;
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}
//�t�d���C�� 


int UIshow(){ //��ܥD�e�� 
	FILE *UI;
	char UIB[2048];  
	UI = fopen("bin/Main.UI","r"); // �}��UI�γ]�w��Ū���Ҧ� 
	if ( UI == NULL ) {  // ���ɮ׫��Ь�NULL�� 
	SetColor(1);
		printf("-A Fatal ERROR Occured-\n");
       printf("�S���ɮ�Main.UI��Ū���ɮ׿��~�C\n");
       system("pause");
       exit(1);
       return 1;
    }
	while (!feof(UI)) { // �u�n���O�ɮ׵����A�K����{}�����e 
          fgets(UIB,8192,UI); // �v��Ū����r
          if (feof(UI)){
          	break;
		  } // �p�GŪ���ɮק��K���Xwhile���c 
			SetColor(1);
        	UIB[strlen(UIB)-1] = '\0'; // �bŪ������r�����[�W\0 
        	printf("%s\n",UIB); // ���r��X����ܾ� 
    }
    SetColor(0);
}

void menu() { //��������
	int control_UI;
	UIshow(); //��ܥD�e��
	while(1) {
		scanf("%d",&control_UI);
		switch(control_UI) {
		case 1:
			system("cls");
			StartGameL1();
			break;
		case 2:
			system("cls");
			StartGameL2();
		case 3:
			system("cls");
			Instruction();
		case 4:
			system("cls");
			ranking();
		case 5:
			exit(1);
		default:
			SetColor(4);
			printf("��J���~ \n");
			SetColor(7);
		}
	}
}

void ranking(){
	int i=0;
	players leaderboard[8];
	char UIB[2048];  
	system("cls");
	SetColor(4);
	FILE *fp = fopen("bin/rankingdb.cdat","r");
	printf("\t\t\t\t�s��]\n");
	printf("__________________________________________________________________________\n\n");
	printf("\t�z�w�w�w�w�w�s�w�w�w�w�s�w�w�w�w�w�w�w�s�w�w�w�w�w�w�{\n");
	printf("\t�x   �W�r   �x  �o��  �x�ϥΤF���ɶ�  �x�ϥΤF�����|�x\n");
	printf("\t�|�w�w�w�w�w�r�w�w�w�w�r�w�w�w�w�w�w�w�r�w�w�w�w�w�w�}\n");
	while(1){ //��ܱƦW
		fscanf(fp,"%s %d %d %d",&leaderboard[i].Name,&leaderboard[i].mark,&leaderboard[i].time,&leaderboard[i].chance);
		printf("\t   %s    \t %d \t    %ds              %d��\n",leaderboard[i].Name,leaderboard[i].mark,leaderboard[i].time,leaderboard[i].chance);
		i++;
		if(feof(fp)){
			break;
		}	
	}
	printf("\n\t\t\t     -�����N���~��-\n");
	getch();
	system("cls");
	menu();
}
int AnsGen() { //
	int a,b,min=0,max=6;
	a=(rand() % max) + min;
}

int ExactAns(char InputAns[],char Ans[]){ //�����M�����O�_�@�Ҥ@�� 
	int i,corret=0;
	for (i=0;i<6;i++){
		if (Ans[i] == InputAns[i]) {
			corret++;
			if (corret == 6){	
				return 1;
			}
		} 
	} 
	return 0;
}

void AnsCheck(char InputAns[],char Ans[]){ //ALG of checking Ans 
	int i,j , temp[6]={};
	for(i=0;i<6;i++){
		for(j=0;j<6;j++) {
			if(Ans[i] == InputAns[j]) { 
				if(temp[j]==0) {
					if(InputAns[j]==Ans[j]) 
						printf("��");
					else {
						printf("��");
					}
					temp[j]++;
					break;
				}
			}
		}
	}
}

void AddRank(int chance,int time){ //�K�[�s�ƦW
	players leaderboard[5]={};
	char name[20];
	int check,i,temp;
	FILE *addrank = fopen("bin/rankingdb.cdat","r+"); //Read Ranking File
	for(i=0;i<6;i++)
		fscanf(addrank,"%s %d %d %d",&leaderboard[i].Name,&leaderboard[i].mark,&leaderboard[i].time,&leaderboard[i].chance);
		scanf("%s",name);
		rewind(addrank);
	
	for(i=0;i<6;i++){ 
		if(Score(chance,time) > leaderboard[i].mark && check==0){ //����ƦW 
			fprintf(addrank,"%s %d %d %d\n",name,Score(chance,time),time,chance);
			check=1;
			temp++;
		}
		else //��ܱƦW
			fprintf(addrank,"%s %d %d %d\n",leaderboard[i].Name,leaderboard[i].mark,leaderboard[i].time,leaderboard[i].chance);
			temp++;
			if(temp==6)
				break;	
	}
	fclose(addrank);
}

void ThreeSecBackMenu(){ //�T����N��^<��������>����
	int t1,t2;
	printf("\n\t\t\t  --- �T����N��^��� ---");
	t1 = time(NULL);
	while(1){
	t2 = time(NULL);
		if (t2-t1==3.0){ // Timer
			system("cls");
    		menu();
    		break;
			}
		}
}

void LoseGame(int t1,int t2,char Ans[]){ //��������ç�Τ᭫�s�ɤަ�<��������>����
	int i;
	SetColor(4);
	system("cls");
	printf(" 			--- �C������ ---");
		for (i=0;i<6;i++) {
			printf("%c",Ans[i]); //Model Ans Print 
		}
		printf("\n");
		printf("\t\t\t-�D�ԥ���-\n");
		printf("\t\t\t�Э��s�D��\n");
		printf("\t\t\t--- �T����N��^��� ---");
		ThreeSecBackMenu();
}

void WinGame(int used_time,int used_chance){ //�Ǧ^�ήa�ӥX�C���᪺�@�����(�p����,�ɶ������)
	printf("������������\n");
	printf("\n\t\t\t�AĹ�F!\n");
	printf("\n\t\t\t�A�ϥΤF�����|: %d\n", used_chance);
	printf("\n\t\t\t���Ƭ�: %d\n",Score(used_chance,used_time));
	printf("\n\t\t\t�C���ɶ�: %d��\n",used_time);
}



void InputError(){ //�Ǧ^���~�T��
	SetColor(4);
	printf("��J�L�ġI �ЦA����J�I\n");
	SetColor(0);
}

void ShowUserInput(char InputAns[]){ //��ܥΤ᪺��J
	int i;
	SetColor(3);
	printf("�A������:");
	for (i=0;i<6;i++) {
	    printf("%c",InputAns[i]);
	}
}

int CheckValid(char InputAns[]){  //���ĩ����� 
	int color[]={82,71,66,89,87,80}; 
	int i,j,valid=0;
	for(i=0;i<6;i++){
		if (strlen(InputAns) !=6){ //���׬O�_�����Ӧr��?
			return 0;
			break;
			}
			for(j=0;j<6;j++){
				if (InputAns[j] == color[i]){
					valid++; //���ļƦr���`�M 
					}
				} 
			}
	
	if (valid==6){ //���ļƦr���`�M=6,
		return 1;
	} else {
		return 0;
	}
}
int StartGameL2() {
	int color[]={82,71,66,89,87,80}; 
	char Ans[6];
	char InputAns[6];
	int i,input,gen,temp;
	int used_chance=0,used_time=0,chance;
	int t1,t2;
	SetColor(0);
	//===================Variable=====================
	for(i=0;i<6;i++){
		gen=(rand() % 6);
		temp=color[i];
		color[i]=color[gen];
		color[gen]=temp;
	}	
	for (i=0;i<6;i++) {
		Ans[i] = color[i]; //Give color number to Array(Answer)
		printf("%c",Ans[i]);//print ans (DEMO)
	}
	printf("\t\t\t      �iLevel 2�j\n");
		printf("__________________________________________________________________________\n");
		printf("�п�J�����Ӧ쪺����: (�d�� - BRGYPP)\n");
	t1 = time(NULL);
	printf("\n�}�l�ɶ�: %d",t1);
	for(chance=7;chance>=0;chance--) {
		if (chance == 0){
                t2 = time(NULL);
			    LoseGame(t1,t2,Ans);
		}
		printf("\n");
		L2Inputagain:
		scanf("%s",InputAns); //input Ans
		if (CheckValid(InputAns) == 1){
			SetColor(3);
			used_chance = used_chance + 1; //count used chance
			ShowUserInput(InputAns);
			printf("| ");
			if (ExactAns(InputAns,Ans) == 0) { //wrong guess
				AnsCheck(InputAns,Ans);
				printf("\n�A�l�U�����|: %d\n",chance);
				SetColor(0);
			} else if (ExactAns(InputAns,Ans) == 1) { //coreect guess and win
                t2 = time(NULL);
        	    printf("�����ɶ�: %d",t2);
				used_time = t2-t1; //count used time
				WinGame(used_time,used_chance); //�Ǧ^Ĺ���C�����ƾڤθ�� 
				printf("\n�п�J�z���W�r: ");
				fflush(stdin);
				AddRank(used_chance,used_time);//�K�[�ƦW 
			    ThreeSecBackMenu();
			} 
		} else if (CheckValid(InputAns) == 0) {
			InputError();
			goto L2Inputagain;
		}
	}
}

int StartGameL1() {
	int color[]={82,71,66,89,87,80}; 
	char Ans[6];
	char InputAns[6];
	int i,input;
	int used_chance=0,used_time=0;
	int t1,t2;
	SetColor(0);
	//===================Variable=====================
	printf("\t\t\t      �iLevel 1�j\n");
	printf("__________________________________________________________________________\n");
	printf("�п�J�����Ӧ쪺����: (�d�� - BRGYPP)\n");
	printf("\n");
		for (i=0;i<6;i++) {
			Ans[i] = color[AnsGen()];//Give color number to Array(Answer)
			printf("%c",Ans[i]);//print ans (DEMO)
		}
	while(1){
		t1 = time(NULL);
		printf("\n");
		SetColor(0);
		L1Inputagain:	
		scanf("%s",InputAns);
		if (CheckValid(InputAns) == 1){
		    SetColor(3);
		    used_chance = used_chance + 1; //�|�[�ϥξ��|
            ShowUserInput(InputAns); //��ܥΤ᪺��J
			printf("�W ");
		    if (ExactAns(InputAns,Ans) == 0) {
			    AnsCheck(InputAns,Ans); 
			    printf("\n�A�ثe�ϥΤF�����|: %d\n",used_chance);
		    } else if (ExactAns(InputAns,Ans) == 1) {
                t2 = time(NULL);
                
        	    used_time = t2-t1; //count used time
			    SetColor(3);
			    WinGame(used_time,used_chance); //�Ǧ^�ήa�ӥX�C���᪺�@�����(�p����,�ɶ������)
				;
		        ThreeSecBackMenu(); //�T����N��^<��������>����
		    }    
	} else if (CheckValid(InputAns) == 0) {
			InputError();
			goto L1Inputagain;
	}
}
}
int Instruction() {
	system("cls");
	system("color F0");
	printf("\t\t\t\t����\n");
	printf("__________________________________________________________________________\n");
	SetColor(0);
	printf("\n1.  �C�ӡ��N���q���F�@���C��M��m���T\n");
	printf("2.  �C�ӡ��N���q���F�@���C�����m�����T\n");
	printf("3.  ����1�]�w���L�����|,���׷|���ƥX�{,�����Z���|�p��J�Ʀ�]\n");
	printf("4.  ����2�]�w��7�����|,���פ��|���ƥX�{,���Z�|�p��J�Ʀ�]\n");
	SetColor(4);
	printf("\n\t\t\t\t�Ҧp:\n");
	printf("\t\t    ����: (���ܥk����) �Ŭ��������\n");
	printf("\t\t\t     ���a�ݿ�J\n");
	printf("\t\t\t\tBRGYPP\n");
	SetColor(0);
	printf("\n\t\t\t      ��Ӫ��p�U:\n");
	
	SetColor(1);
	printf("\t\t�� = B ");
	
	SetColor(2);
	printf("�� = G ");
	
	SetColor(4);
	printf("�� = R ");
	
	SetColor(5);
	printf("�� = P ");
	
	SetColor(7);
	printf("�� = W ");
	
	SetColor(6);
	printf("�� = Y\n");
	
	printf("\n\t\t\t   -�����N���~��-\n");
	getch();
	SetColor(0);
	system("cls");
	menu();
}

int Score(int chance,int time){
	return pow((9-chance)*10,2) - time*10; 
}

int main() {
	//initalization
	system("mode con:cols=74 lines=25");
	int i,control_UI;
	system("color F0");
	system("title Mastermind Game - by Carl CHK");
	srand(time(NULL));
	//varible
	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime (&rawtime); 
	menu();
	return 0;
}
