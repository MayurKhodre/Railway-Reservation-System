#include<stdio.h>
#include"conio2.h"
#include"rlyres.h"
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
int enterchoice()
{
    int choice,i;
    textcolor(YELLOW);
    gotoxy(28,1);
    printf("RAILWAY RESERVATION SYSTEM\n");
    for(i=1;i<=80;i++)
        printf("-");
    printf("\nSelect an option");
    printf("\n1- View Trains");
    printf("\n2- Book Ticket");
    printf("\n3- View Ticket");
    printf("\n4- Search Ticket No");
    printf("\n5- View All Bookings");
    printf("\n6- View Train Bookings");
    printf("\n7- Cancel Ticket");
    printf("\n8- Cancel Train");
    printf("\n9- Quit");

    printf("\n\nEnter choice:");
    scanf( "%d", &choice );
    return choice;
  }

  void add_trains()
  {
      FILE *fp;
      fp=fopen("alltrains.dat","rb");
      if(fp==NULL)
      {
          Train alltrains[4]={
                {"123","BPL","GWA",2100,1500},
                {"546","BPL","DEL",3500,2240},
                {"345","HBJ","AGR",1560,1135},
                {"896","HBJ","MUM",4500,3360}
          };
          fp=fopen("alltrains.dat","wb");
          fwrite(alltrains,4*sizeof(Train),1,fp);
          printf("File saved successfully\n");
          fclose(fp);
      }
      else
      {
          printf("File already present\n");
          fclose(fp);
      }
  }

  void view_trains()
  {
      int i;
      printf("TRAIN NO\tFROM\tTO\tFIRST AC FARE\tSECOND AC FARE\n");
      for(i=1;i<=80;i++)
        printf("-");
      FILE *fp;
      fp=fopen("alltrains.dat","rb");
      Train tr;
      while(fread(&tr,sizeof(tr),1,fp)==1)
        printf("\n%s\t\t%s\t%s\t%d\t\t%d",
        tr.train_no,tr.from,tr.to,tr.fac_fare,tr.sac_fare);
      printf("\n\n\n\n");
      fclose(fp);
  }

  int check_train_no(char*train_no)
  {
      FILE *fp;
      fp=fopen("alltrains.dat","rb");
      Train tr;
      while(fread(&tr,sizeof(tr),1,fp)==1)
      {
          if(strcmp(tr.train_no,train_no)==0)
          {
              fclose(fp);
              return 1;
          }
      }
      fclose(fp);
      return 0;
  }


  int check_mob_no(char*p_mob)
  {
      if(strlen(p_mob)!=10)
          return 0;
      while(*p_mob!='\0')
      {
          if(isdigit(*p_mob)==0)
            return 0;
          p_mob++;
      }
      return 1;
  }


Passenger *get_passenger_details()
  {
      clrscr();
      static Passenger psn;
      gotoxy(65,1);
      textcolor(LIGHTGREEN);
      printf("Press 0 to exit");
      gotoxy(1,1);
      textcolor(YELLOW);
      printf("Enter passenger name:");
      fflush(stdin);
      fgets(psn.p_name,20,stdin);
      char *pos;
      pos=strchr(psn.p_name,'\n');
      *pos='\0';
      if(strcmp(psn.p_name,"0")==0)
      {
          textcolor(LIGHTRED);
          gotoxy(1,25);
          printf("Reservation cancelled!");
          getch();
          textcolor(YELLOW);
          clrscr();
          return NULL;
      }
      int valid;
      gotoxy(1,2);
      printf("Enter gender(M/F):");
      do
      {
          valid=1;
          fflush(stdin);
          scanf("%c",&psn.gender);
          if(psn.gender=='0')
          {
          textcolor(LIGHTRED);
          gotoxy(1,25);
          printf("\t\t\t\t\t\t\t");
          gotoxy(1,25);
          printf("Reservation Cancel\n");
          getch();
          textcolor(YELLOW);
          clrscr();
          return NULL;
          }
          if(psn.gender!='M'&& psn.gender!='F')
          {
              textcolor(LIGHTRED);
              gotoxy(1,25);
              printf("Error! Gender should be M or F (in uppercase)");
              valid=0;
              getch();
              gotoxy(19,2);
              printf(" \b");
              textcolor(YELLOW);
          }
      }while(valid==0);
      gotoxy(1,25);
      printf("\t\t\t\t\t\t\t");
      gotoxy(1,3);
      printf("Enter train number:");
      do
      {
          fflush(stdin);
          scanf("%s",psn.train_no);
          if(strcmp(psn.train_no,"0")==0)
          {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Reservation Cancel\n");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
          }
          valid=check_train_no(psn.train_no);
          if(valid==0)
          {
              textcolor(LIGHTRED);
              gotoxy(1,25);
              printf("Error! Invalid train no");
              valid=0;
              getch();
              gotoxy(20,3);
              printf("\t\t\t\t");
              gotoxy(20,3);
              textcolor(YELLOW);
          }

      }while(valid==0);
      gotoxy(1,25);
      printf("\t\t\t\t\t\t\t");
      gotoxy(1,4);
      printf("Enter travelling class(First AC:F,Second AC:S):");
      do
      {
          valid=1;
          fflush(stdin);
          scanf("%c",&psn.p_class);
          if(psn.p_class=='0')
          {
          textcolor(LIGHTRED);
          gotoxy(1,25);
          printf("\t\t\t\t\t\t\t");
          gotoxy(1,25);
          printf("Reservation Cancel\n");
          getch();
          textcolor(YELLOW);
          clrscr();
          return NULL;
          }
          if(psn.p_class!='F'&&psn.p_class!='S')
          {
              textcolor(LIGHTRED);
              gotoxy(1,25);
              printf("Error! Travelling class should be F or S");
              valid=0;
              getch();
              gotoxy(48,4);
              printf(" \b");
              textcolor(YELLOW);
          }
      }while(valid==0);
      gotoxy(1,25);
      printf("\t\t\t\t\t\t\t");
      gotoxy(1,5);
      printf("Enter address:");
      fflush(stdin);
      fgets(psn.address,20,stdin);
      pos=strchr(psn.address,'\n');
      *pos='\0';
      if(strcmp(psn.address,"0")==0)
      {
          textcolor(LIGHTRED);
          gotoxy(1,25);
          gotoxy(1,25);
          printf("\t\t\t\t\t\t\t");
          printf("Reservation cancelled!");
          getch();
          textcolor(YELLOW);
          clrscr();
          return NULL;
      }
      printf("Enter age:");
      do
      {
          valid=1;
          fflush(stdin);
          scanf("%d",&psn.age);
          if(psn.age==0)
          {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Reservation Cancel\n");
            getch();
            textcolor(YELLOW);
            clrscr();
            return NULL;
          }
          if(psn.age<0)
          {
              textcolor(LIGHTRED);
              gotoxy(1,25);
              printf("Error!Age should be positive");
              valid=0;
              getch();
              gotoxy(11,6);
              printf("\t\t\t\t\t");
              gotoxy(11,6);
              textcolor(YELLOW);
          }
      }while(valid==0);
      gotoxy(1,25);
      printf("\t\t\t\t\t\t\t");
      gotoxy(1,7);
      printf("Enter mobile number:");
      do
      {
          fflush(stdin);
          fgets(psn.mob_no,12,stdin);
          pos=strchr(psn.mob_no,'\n');
          if(pos!=NULL)
            *pos='\0';
          if(strcmp(psn.mob_no,"0")==0)
          {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Reservation Cancelled!");
            getch();
            textcolor(YELLOW);
            return NULL;
          }
          valid=check_mob_no(psn.mob_no);
          if(valid==0)
          {
              textcolor(LIGHTRED);
              gotoxy(1,25);
              printf("Error! Invalid mobile No");
              getch();
              gotoxy(21,7);
              printf("\t\t\t\t\t");
              gotoxy(21,7);
              textcolor(YELLOW);
          }
      }while(valid==0);
      return &psn;
  }


int get_booked_ticket_count(char*train_no,char tc)
{
    FILE *fp;
    fp=fopen("allbookings.dat","rb");
    if(fp==NULL)
        return 0;
    Passenger psn;
    int count=0;
    while(fread(&psn,sizeof(psn),1,fp)==1)
    {
        if(strcmp(psn.train_no,train_no)==0&&psn.p_class==tc)
            ++count;
    }
    fclose(fp);
    return count;
}

int last_ticket_no()
{
    FILE *fp;
    fp=fopen("allbookings.dat","rb");
    if(fp==NULL)
        return 0;
    Passenger pr;
    fseek(fp,-1*sizeof(pr),SEEK_END);
    fread(&pr,sizeof(pr),1,fp);
    fclose(fp);
    return pr.ticketno;
}


int book_ticket(Passenger p)
{
    int ticket_count=get_booked_ticket_count(p.train_no,p.p_class);
    if(ticket_count==2)
    {
        textcolor(LIGHTRED);
        printf("All seats full in train no %s in %c class!\n",p.train_no,p.p_class);
        return -1;
    }
    int ticket_no=last_ticket_no()+1;
    p.ticketno=ticket_no;
    FILE *fp;
    fp=fopen("allbookings.dat","ab");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry! file can't opened\n");
        return -1;
    }
    fwrite(&p,sizeof(p),1,fp);
    fclose(fp);
    return ticket_no;
}

int accept_ticket_no()
{
      clrscr();
      int ticket_no;
      int valid;
      printf("Enter Ticket no:");
      do
      {
          valid=1;
          fflush(stdin);
          scanf("%d",&ticket_no);
          if(ticket_no==0)
          {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Cancelling input...!");
            textcolor(YELLOW);
            return 0;
          }
          if(ticket_no<0)
          {
              textcolor(LIGHTRED);
              gotoxy(1,25);
              printf("Error!Ticket number should be positive");
              valid=0;
              getch();
              gotoxy(17,1);
              printf("\t\t\t\t\t");
              gotoxy(17,1);
              textcolor(YELLOW);
          }
      }while(valid==0);
      return ticket_no;
}

void view_ticket(int ticket_no)
{
    Passenger psn;
    FILE *fp;
    fp=fopen("allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("No booking done yet\n");
        return ;
    }
    int x=0;
    while(fread(&psn,sizeof(psn),1,fp)==1)
    {
        if(psn.ticketno==ticket_no)
        {
            printf("Name: %s\nGender: %c\nTrain_no: %s\np_Class: %c\nAddress: %s\nAge: %d\nmoblie_no: %s",psn.p_name,psn.gender,psn.train_no,psn.p_class,psn.address,psn.age,psn.mob_no);
            printf("\n\n");
            ++x;
            break;
        }
    }
    if(x==0)
    {
        textcolor(LIGHTRED);
        printf("\nNo details of the ticket found");
    }
    fclose(fp);
}

char* accept_mob_no()
{
      static char mob_no[11];
      char *pos;
      int valid;
      printf("Enter mobile number:");
      do
      {
          fflush(stdin);
          fgets(mob_no,12,stdin);
          pos=strchr(mob_no,'\n');
          if(pos!=NULL)
            *pos='\0';
          if(strcmp(mob_no,"0")==0)
          {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Cancelling Input...!");
            getch();
            textcolor(YELLOW);
            return NULL;
          }
          valid=check_mob_no(mob_no);
          if(valid==0)
          {
              textcolor(LIGHTRED);
              gotoxy(1,25);
              printf("Error! Invalid mobile No");
              getch();
              gotoxy(21,1);
              printf("\t\t\t\t\t");
              gotoxy(21,1);
              textcolor(YELLOW);
          }
      }while(valid==0);
      clrscr();
      return mob_no;
}

int* get_ticket_no(char*p_mob_no)
{
    int count=0;
    FILE *fp;
    fp=fopen("allbookings.dat","rb");
    if(fp==NULL)
        return NULL;
    Passenger psn;
    while(fread(&psn,sizeof(psn),1,fp)==1)
    {
        if(strcmp(psn.mob_no,p_mob_no)==0)
            ++count;
    }
    if(!count)
    {
      fclose(fp);
      return NULL;
    }
    rewind(fp);
    int *p=(int*)malloc((count+1)*sizeof(int));
    int i=0;
    while(fread(&psn,sizeof(psn),1,fp)==1)
    {
        if(strcmp(psn.mob_no,p_mob_no)==0)
        {
            *(p+i)=psn.ticketno;
            i++;
        }
    }
    *(p+i)=-1;
    fclose(fp);
    return p;
}

void view_all_tickets(char* pmob_no,int* pticket_no)
{
    if(pticket_no==NULL)
    {
        textcolor(LIGHTRED);
        printf("Sorry! No tickets booked against mobile no %s",pmob_no);
        textcolor(WHITE);
        printf("\n\nPress any key to go back to the main screen");
        textcolor(YELLOW);
        getch();
        return;
    }
    printf("Following are tickets booked for mobile no %s",pmob_no);
    int i;
    printf("\n\nTICKET NO\n");
    printf("--------");
    for(i=0;*(pticket_no+i)!=-1;i++)
        printf("\n%d",*(pticket_no+i));
    textcolor(WHITE);
    printf("\n\nPress any key to go back to the main screen");
    textcolor(YELLOW);
    getch();
}

char *accept_train_no()
{
      static char train_no[20];
      int valid;
      char *pos;
      printf("Enter train number:");
      do
      {
          fflush(stdin);
          fgets(train_no,20,stdin);
          pos=strchr(train_no,'\n');
          if(pos!=NULL)
            *pos='\0';
          if(strcmp(train_no,"0")==0)
          {
            textcolor(LIGHTRED);
            gotoxy(1,25);
            printf("\t\t\t\t\t\t\t");
            gotoxy(1,25);
            printf("Cancelling Input...!");
            getch();
            textcolor(YELLOW);
            return NULL;
          }
          valid=check_train_no(train_no);
          if(valid==0)
          {
              textcolor(LIGHTRED);
              gotoxy(1,25);
              printf("Error! Invalid train No");
              getch();
              gotoxy(20,1);
              printf("\t\t\t\t\t");
              gotoxy(20,1);
              textcolor(YELLOW);
          }
      }while(valid==0);
      clrscr();
      return train_no;
}


void view_bookings(char *train_no)
{
    clrscr();
    int count=0;
    textcolor(YELLOW);
    FILE *fp;
    fp=fopen("allbookings.dat","rb");
    if(fp==NULL)
    {
        textcolor(LIGHTRED);
        printf("No bookings done yet");
        return;
    }
    Passenger psn;
     printf("TICKET NO\t\tCLASS\tNAME\t\tAGE\n");
     for(int i=0;i<80;i++)
        printf("-");
    while(fread(&psn,sizeof(psn),1,fp)==1)
    {
        if(strcmp(psn.train_no,train_no)==0)
        {
            count=1;
            printf("%d\t\t\t%c\t%s\t\t%d\n",psn.ticketno,psn.p_class,psn.p_name,psn.age);
        }
    }
    printf("\n\n\n");
    if(!count)
    {
      textcolor(LIGHTRED);
      printf("\nNo details of the train %s found",train_no);
      fclose(fp);
      return;
    }
}

int cancel_ticket(int ticket_no)
{
    FILE *fp1;
    fp1=fopen("allbookings.dat","rb");
    if(fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nNo bookings done yet!");
        return -1;
    }
    FILE *fp2;
    fp2=fopen("temp.dat","wb");
    int found=0,result;
    Passenger psn;
    while(fread(&psn,sizeof(psn),1,fp1)==1)
    {
        if(psn.ticketno==ticket_no)
        {
            found=1;
        }
        else
        {
            fwrite(&psn,sizeof(psn),1,fp2);
        }
    }
    fclose(fp1);
    fclose(fp2);
    if(found==0)
    {
        remove("temp.dat");
    }
    else
    {
      result=remove("allbookings.dat");
      if(result!=0)
        return 2;
      result=rename("temp.dat","allbookings.dat");
      if(result!=0)
        return 2;
    }
    return found;
}


int cancel_train(char *train_no)
{
    FILE *fp1;
    fp1=fopen("alltrains.dat","rb");
    if(fp1==NULL)
    {
        textcolor(LIGHTRED);
        printf("\nNo train yet!");
        return -1;
    }
    FILE *fp2;
    fp2=fopen("temp.dat","wb");
    int found=0,result;
    Train tr;
    while(fread(&tr,sizeof(tr),1,fp1)==1)
    {
        if(strcmp(tr.train_no,train_no)==0)
        {
            found=1;
        }
        else
        {
            fwrite(&tr,sizeof(tr),1,fp2);
        }
    }
    fclose(fp1);
    fclose(fp2);
    if(found==0)
    {
        remove("temp.dat");
    }
    else
    {
      result=remove("alltrains.dat");
      if(result!=0)
        return 2;
      result=rename("temp.dat","alltrains.dat");
      if(result!=0)
        return 2;
    }
    return found;
}

void view_all_bookings()
{
    clrscr();
    FILE* fp;
    fp=fopen("allbookings.dat","rb");
    if(fp == NULL)
    {
        textcolor(LIGHTRED);
        printf("No bookings done yet!\n");
        return;
    }
    printf("TICKET NO\tCLASS\tNAME\t\tGENDER\tAGE\tMOBILE NO\n");
    for(int i=0;i<80;i++)
    {
        printf("-");
    }
    Passenger pr;
    textcolor(YELLOW);
    int row=3;
    while(fread(&pr,sizeof(pr),1,fp) == 1)
    {
        printf("%d\t%s\t\t%c\t%s",pr.ticketno,pr.train_no,pr.p_class,pr.p_name);
        gotoxy(41,row);
        printf("%c\t%d\t%s\n",pr.gender,pr.age,pr.mob_no);
        row++;
    }
    fclose(fp);
}

