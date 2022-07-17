#include <stdio.h>
#include <stdlib.h>
#include"conio2.h"
#include"rlyres.h"
int main()
{
    int choice;
    int ticket_no,result;
    Passenger *ptr;
    char*train_no;
    add_trains();
    while(1)
    {
       choice=enterchoice();
       if(choice==9)
          exit(0);
       switch(choice)
       {
          case 1:
              view_trains();
              getch();
              clrscr();
              break;
          case 2:
              ptr=get_passenger_details();
              if(ptr!=NULL)
              {
                  ticket_no=book_ticket(*ptr);
                  if(ticket_no==-1)
                  {
                      textcolor(LIGHTRED);
                      printf("Booking failed");
                  }
                  else
                  {
                      textcolor(LIGHTGREEN);
                      printf("Ticket Successfully Booked\nYour ticket no is %d",ticket_no);
                  }
                  textcolor(WHITE);
                  printf("\nPress any key to go back to the main screen");
                  getch();
                  clrscr();
              }

              break;
          case 3:
              clrscr();
              ticket_no=accept_ticket_no();
              if(ticket_no!=0);
                view_ticket(ticket_no);
              textcolor(WHITE);
              printf("\nPress any key to go back to the main screen");
              getch();
              clrscr();
              break;
          case 4:
              clrscr();
              int pmob_no=accept_mob_no();
              if(pmob_no!=NULL)
              {
                  int pticket_no=get_ticket_no(pmob_no);
                  view_all_tickets(pmob_no,pticket_no);
              }
              clrscr();
              break;
          case 5:
              view_all_bookings();
              textcolor(WHITE);
              printf("Press any key to back to the main screen");
              getch();
              clrscr();
              break;
          case 6:
              clrscr();
              train_no=accept_train_no();
              if(train_no!=NULL)
                view_bookings(train_no);
              textcolor(WHITE);
              printf("\n\nPress any key to back to the main screen");
              getch();
              clrscr();
              break;
          case 7:
              clrscr();
              ticket_no=accept_ticket_no();
              if(ticket_no!=0)
              {
                result=cancel_ticket(ticket_no);
                if(result==0)
                {
                  textcolor(LIGHTRED);
                  printf("Sorry!No tickets booked against ticket no %d",ticket_no);
                }
                else if(result==1)
                {
                  textcolor(LIGHTGREEN);
                  printf("Ticket number %d successfully Cancelled",ticket_no);
                }
                else if(result==2)
                {
                  printf("Sorry!Error in cancellation, try again");
                }
                textcolor(WHITE);
                printf("\n\nPress any key to go back to the main screen");
              }
              getch();
              clrscr();
              break;
          case 8:
              clrscr();
              train_no=accept_train_no();
              if(train_no!=NULL)
              {
                result=cancel_train(train_no);
                if(result==0)
                {
                  textcolor(LIGHTRED);
                  printf("Sorry!No train against train no %s",train_no);
                }
                else if(result==1)
                {
                  textcolor(LIGHTGREEN);
                  printf("Train number %s successfully Cancelled",train_no);
                }
                else if(result==2)
                {
                  printf("Sorry!Error in cancellation, try again");
                }
                textcolor(WHITE);
                printf("\n\nPress any key to go back to the main screen");
              }
              getch();
              clrscr();
              break;
          default:
              textcolor(LIGHTRED);
              printf("Wrong Choice!Try Again\n");
              getch();
              clrscr();
       }
    }
    return 0;
}
