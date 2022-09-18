
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

struct passenger;
struct bus;

//buses and passengers linked lists and their pointers creation

typedef struct passenger *ptr_passenger;
typedef struct bus *ptr_bus;
typedef ptr_passenger pos;

struct passenger{

    int traveler_ID;
    int travelling_Date;
    char travelling_Time[10];
    char from[20];
    char to[20];
    ptr_passenger next;

};

struct bus{
    int busline;
    int busdate;
    char bustime[10];
    char from[20];
    char to[20];
    int price;
    int capacity;
    int nunmatch;
    int numofpass;     // current number of passengers in the bus
    int nwaits;        // number of waiting passengers
    struct passenger *pass;     // passengers linked list
    struct passenger *waiting; // waiting passengers linked list
    struct passenger *unmatch;
    ptr_bus next;
};

typedef ptr_passenger passengers_list;
typedef ptr_bus busses_list;

//functions prototypes
void menu();
void choice(passengers_list passenger_header, busses_list bus_header);
void BussesFileToArray();
void BussesFileToLL(busses_list bus_header);
passengers_list PassengersFileTOLL(passengers_list passenger_header);
void printfPass(passengers_list temp);
ptr_bus create_bus_node(busses_list header);
ptr_passenger create_pass_node(passengers_list header);
void busses_data(busses_list node , char line[]);
void passengers_data(passengers_list node , char line[]);
int Time (char* t , char* tt);
int destination(char* f1 , char* f2 , char* t1 , char* t2);
int isEmpty(passengers_list p);
int isEmpty(busses_list b);
void assignpass(passengers_list passenger_header,busses_list bus_header);
void printAssign(busses_list bus_header);
void add_to_unmatch(passengers_list p , busses_list bus_header);
void waiting_list(busses_list bus_header);
void information(busses_list bus_header , int line);
void add_new_pass(passengers_list passenger_header, busses_list bus_header);
void delete_Pnode(passengers_list passenger_header , int i);
void delete_pass(passengers_list passenger_header , busses_list bus_header ,int id, int line);
busses_list deleteBnode(busses_list bus_header , int line);
void delete_busNum(busses_list bus_header , int line);
void AddToFile(int id , int date , char *time , char *from , char *to);

// functions to trim strings (to compare between them)
char *ltrim(char *s);
char *rtrim(char *s);
char *trim(char *s);


int main()
{

   // create a passengers linked list
    passengers_list passenger_header = (passengers_list)malloc(sizeof(struct passenger));
    passenger_header->next = NULL;


   // create a buses linked list
    busses_list bus_header = (busses_list)malloc(sizeof(struct bus));
    bus_header->next = NULL;

    menu();
    choice(passenger_header, bus_header);

    return 0 ;

}


// a function to print the choices
void menu()
{
    // print choices menu

    printf(" Choose from the following Choices Menu : \n");
    printf(" 1. Load the bus information file \n");
    printf(" 2. Load the passenger information file \n");
    printf(" 3. Assign passengers and print assignment information of all busses \n");
    printf(" 4. Print a specific bus information along with its passengers information (names and IDs) \n");
    printf(" 5. Print unmatched passengers \n");
    printf(" 6. Add new passenger \n");
    printf(" 7. Delete passenger \n");
    printf(" 8. Delete bus number \n");
    printf(" 9. Exit \n\n");

    printf(" \t NOTE 1 : you have to load info (choice 1,2) to be able to choose from 3 to 8\n");
    printf(" \t NOTE 2 : you have to choose choice 3 first to be able to choose from 4 to 8 \n ");
}


// a function to process the chosen choice
void choice(passengers_list passenger_header , busses_list bus_header)
{

    // variables to check chosen choices
    int c1 = 0,c2 = 0,c3 = 0;


    // create the linked list of passengers
    passengers_list p = PassengersFileTOLL(passenger_header);


    // read user's choices until exit (choice 9)
    while(1)
    {
       int choice;

       // scan the user's choice
       scanf("%d",&choice);

       switch(choice)
       {
           case 1 : BussesFileToArray();
                    c1 = 1;
                    break;


           case 2 : printfPass(p);
                    c2 = 1;
                    break;


           case 3 : if(c1 && c2)
                   {
                       assignpass(p , bus_header);
                       printAssign(bus_header);
                       c3 = 1;
                   }

                   else
                   {
                       printf("\t please load Files first ! choices 1 & 2 \n");
                   }

                   break;


           case 4 : if(c1 && c2 && c3)
                  {
                     int line;
                     printf("\t Enter the Bus Line :     ");
                     scanf("%d",&line);

                     information(bus_header,line);
                  }

                  else
                  {
                      printf("\t Assign passengers to Buses First ! choice 3 \n");
                  }

                  break;


           case 5 : if(c1 && c2 && c3)
                  {
                      waiting_list(bus_header);

                      printf("\n\t\t UNMATCHED Passengers : \n");
                      printf("\t\t------------------------ \n");

                      while(bus_header->unmatch != NULL)
                      {
                          printf("Passenger ID: %d\tTravel Date: %d\tTravel Time: %s\tFrom: %s\t   To: %s",bus_header->unmatch->traveler_ID,bus_header->unmatch->travelling_Date,bus_header->unmatch->travelling_Time,bus_header->unmatch->from,bus_header->unmatch->to);
                          bus_header->unmatch = bus_header->unmatch->next;
                      }

                      printf("\n");
                  }

                  else
                  {
                      printf("\t Assign passengers to Buses First ! choice 3 \n");
                  }

                    break;


           case 6 :if( c1 && c2 && c3)

                   {
                       add_new_pass(p,bus_header);
                   }

                   else
                   {
                       printf("Check that you load Files and Assign passengers to Buses please ! , choice 1 & 2 & 3 \n");
                   }

                   break;


           case 7 : if( c1 && c2 && c3)
                {
                    printf("\t Enter the ID of the passenger you want to delete: ");
                    int id;
                    scanf("%d",&id);

                    printf("\t Enter the Bus Line for this Passenger to delete it from the Bus too : ");
                    int line;
                    scanf("%d",&line);

                    printf("\n ");

                    delete_pass(p,bus_header,id,line);

                }

                  else
                {
                    printf("Check that you load Files and Assign passengers to Buses please ! , choice 1 & 2 & 3 \n");
                }

                    break;


           case 8 : if(c1 && c2 && c3)

                     {
                         printf("\t Enter the Bus Line you want to delete :  ");
                         int line;
                         scanf("%d",&line);
                         printf("\n");

                         delete_busNum(bus_header , line);

                     }

                     else
                        printf("Please check that you load files , and Assign passengers to buses , choice 1 & 2 & 3");

                     break;


           case 9 : exit(0);
                    break;


          default : printf("please choose a number between 1 - 9 ONLY ! \n");

       }
    }
}


// a function to load buses info from the file to an array
void BussesFileToArray()
{
    FILE *BF;

    // open file to read
    BF = fopen("busses.txt","r");

    // check if the file exist and not NUll if no exit
    if(BF == NULL)
    {
        printf("Busses File is Empty or does not exist");
        exit(0);
    }


        // char pointer to read from file
        char *p;

        // create array of struct with size 1000
        struct bus *b = (bus*)malloc(sizeof(struct bus)* 1000);

        // number of buses
        int n = 0 ;
        char line[500];

        // get each line until the end
        while(fgets(line,500,BF) != NULL)
        {

          // get info for each bus and save it to the array

          p = strtok(line,"#");
          b[n].busline = atoi(p);

          p = strtok(NULL, "#");
          b[n].busdate = atoi(p);

          p = strtok(NULL,"#");
          strcpy(b[n].bustime,p);

          p = strtok(NULL,"#");
          strcpy(b[n].from,p);

          p = strtok(NULL,"#");
          strcpy(b[n].to,p);

          p = strtok(NULL,"#");
          b[n].price = atoi(p);

          p = strtok(NULL,"#");
          b[n].capacity = atoi(p);

          b[n].numofpass = 0;

          n++;
        }


    // print buses data

    for(int i = 0 ; i < n ; i++)
    {
       printf("\tBus line: %d\tBus Date: %d\tBus Time: %s\t   From: %s\tTo: %s\tCapacity: %d \tprice: %d \n" , b[i].busline , b[i].busdate , b[i].bustime , b[i].from , b[i].to , b[i].capacity , b[i].price);

    }

    // close the file
    fclose(BF);

}


// a function to create a linked list of the buses
void BussesFileToLL(busses_list bus_header)
{

    FILE *BF;

    // open buses file to read data
    BF = fopen("busses.txt","r");

    if(BF == NULL)
    {
        printf("Busses File is Empty or does not exist");
        exit(0);
    }

    char line[500];
    fgets(line,500,BF);

    // create the linked list header
    busses_data(bus_header,line);

    while(fgets(line,500,BF) != NULL)
    {
        // create buses linked list with the prev. header
        busses_list b = create_bus_node(bus_header);

        // fill data in the node
        busses_data(b,line);
    }

    // close file
    fclose(BF);

}


// a function to create passengers linked list
passengers_list PassengersFileTOLL(passengers_list passenger_header)
{
    FILE *PF;

    //open file to read data
    PF = fopen("passengers.txt","r");

    if(PF == NULL)
    {
        printf(" Passengers File is Empty or does not exist");
        exit(0);
    }

    int numofPass = 1;
    char line[500];
    fgets(line,500,PF);

    // create header node
    passengers_data(passenger_header,line);

    // create linked list nodes and fill them with data from the file
    while(fgets(line,500,PF) != NULL)
    {
        numofPass++;
        passengers_list p = create_pass_node(passenger_header);
        passengers_data(p,line);
    }

    passengers_list temp = passenger_header;

    fclose(PF);

    return temp;
}


// a function to print passengers linked list
void printfPass(passengers_list temp)
{

    printf("\n\t ");

    while(temp != NULL)
    {
        printf("Passenger ID: %d\tTravel Date: %d\tTravel Time: %s\tFrom: %s\t   To: %s\t ",temp->traveler_ID,temp->travelling_Date,temp->travelling_Time,temp->from,temp->to);
        temp = temp->next;
    }

    printf("\n");
}


// a function to create a new node in the buses linked list
ptr_bus create_bus_node(busses_list header)
{
    busses_list b = header;

    // add a node to the end of the list
    while(b->next != NULL)
    {
        b = b->next;
    }

    // create the node
    busses_list Node = (struct bus*)malloc(sizeof(struct bus));
    b->next = Node;
    Node->next = NULL;

    return Node;
}


// a function to create a new node in the passengers list
ptr_passenger create_pass_node(passengers_list header)
{
    passengers_list p = header;

    // add a node at the end of the list
    while(p->next != NULL)
    {
        p = p->next;
    }

    // create the node
    passengers_list Node = (passengers_list)malloc(sizeof(struct passenger));
    p->next = Node;
    Node->next = NULL;

    return Node;
}


// a function to get the bus node data from the buses file
void busses_data(busses_list node , char line[])
{
    char *p;

    p = strtok(line,"#");
    node->busline = atoi(p);

    p = strtok(NULL,"#");
    node->busdate = atoi(p);

    p = strtok(NULL,"#");
    strcpy(node->bustime,p);

    p = strtok(NULL,"#");
    strcpy(node->from,p);

    p = strtok(NULL,"#");
    strcpy(node->to,p);

    p = strtok(NULL,"#");
    node->price = atoi(p);

    p = strtok(NULL,"#");
    node->capacity = atoi(p);

}


// a function to get the passenger node data from the passengers file
void passengers_data(passengers_list node, char line[])
{
    char *p;

    p = strtok(line,"#");
    node->traveler_ID = atoi(p);

    p = strtok(NULL,"#");
    node->travelling_Date = atoi(p);

    p = strtok(NULL,"#");
    strcpy(node->travelling_Time,p);

    p = strtok(NULL,"#");
    strcpy(node->from,p);

    p = strtok(NULL,"#");
    strcpy(node->to,p);

}


// a function to compare between the travel time of the bus , and the passenger
int Time (char* t , char* tt)
{
    if( strcmp(t,tt) == 0)
    {
        return 1;
    }

    else
        return 0;
}


// a function to compare between the destination(from,to) of the bus and the passenger
int destination(char* f1 , char* f2 , char* t1 , char* t2)
{
    if(strcmp(f1,f2) == 0 && strcmp(t1,t2) == 0)
    {
        return 1;
    }
    else
        return 0;
}


// trim the string from the left
char *ltrim(char *s)
{
    while(isspace(*s)) s++;
    return s;
}


// trim the string from the right
char *rtrim(char *s)
{
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}


// return the final trimmed string
char *trim(char *s)
{
    return rtrim(ltrim(s));
}


// a function to check if a passenger linked list is empty
int isEmpty(passengers_list p)
{
    return p->next == NULL;
}


// a function to check if a buses linked list is empty
int isEmpty(busses_list b)
{
    return b->next == NULL;
}


// a function to assign each passenger to the matched bus
void assignpass(passengers_list passenger_header , busses_list bus_header)
{

    // create the buses linked list
    BussesFileToLL(bus_header);
    busses_list b = bus_header;

    // create unmatched passengers linked list
    b->unmatch = (passengers_list)malloc(sizeof(struct passenger));
    b->unmatch->next = NULL;
    b->nunmatch = 0;

    // for each bus node create two passengers linked lists , waiting , and current passengers
    while( b != NULL)
    {
        b->pass = (passengers_list)malloc(sizeof(struct passenger));
        b->pass->next= NULL;

        b->waiting = (passengers_list)malloc(sizeof(struct passenger));
        b->waiting->next = NULL;

        // initialize the number of current passengers and the waitings to zero
        b->numofpass = 0;
        b->nwaits = 0;

        b = b->next;
    }


    passengers_list p = passenger_header;


    // to check if their is a matched bus
    int check;


    while(p!= NULL)
    {
        b = bus_header;

        while(b!= NULL)
        {
            check = 0 ;

            // compare the the travel date
            if(b->busdate == p->travelling_Date)
            {
                // check the travel time
                if(Time(b->bustime,p->travelling_Time))
                {
                    // check the destination
                    if(destination(trim(b->from),trim(p->from),trim(b->to),trim(p->to)))
                    {
                        // their is a matched bus
                        check = 1;

                        // check if their is a space for the passenger
                        if(b->numofpass < b->capacity)
                        {
                            // if yes add the passenger to the bus passengers linked list
                           int header = b->numofpass;

                           // check if its the first node as a header
                           if( header == 0 )
                           {
                               b->pass->traveler_ID = p->traveler_ID;
                               b->pass->travelling_Date = p->travelling_Date;
                               strcpy(b->pass->travelling_Time,p->travelling_Time);
                               strcpy(b->pass->from,p->from);
                               strcpy(b->pass->to,p->to);
                               b->pass->next = NULL;

                               b->numofpass = b->numofpass+1;
                               b->capacity = b->capacity-1;

                               p = p->next;
                           }

                           // if it's not the first node create a new node
                           else
                           {
                               passengers_list New = create_pass_node(b->pass);
                               New->traveler_ID = p->traveler_ID;
                               New->travelling_Date = p->travelling_Date;
                               strcpy(New->travelling_Time,p->travelling_Time);
                               strcpy(New->from,p->from);
                               strcpy(New->to,p->to);

                               b->numofpass = b->numofpass+1;
                               b->capacity = b->capacity-1;

                               b = b->next;
                           }

                        }

                        // if their is no space in the bus ad the passenger to the waiting list of the bus
                        else
                        {
                           int wheader = b->nwaits;

                           if(wheader == 0)
                           {
                               b->waiting->traveler_ID = p->traveler_ID;
                               b->waiting->travelling_Date = p->travelling_Date;
                               strcpy(b->waiting->travelling_Time,p->travelling_Time);
                               strcpy(b->waiting->from,p->from);
                               strcpy(b->waiting->to,p->to);
                               b->waiting->next = NULL;

                               b->nwaits = b->nwaits+1;

                               p = p->next;
                           }

                           else
                           {
                               passengers_list New = create_pass_node(b->waiting);
                               New->traveler_ID = p->traveler_ID;
                               New->travelling_Date = p->travelling_Date;
                               strcpy(New->travelling_Time,p->travelling_Time);
                               strcpy(New->from,p->from);
                               strcpy(New->to,p->to);

                               b->nwaits = b->nwaits+1;

                               p = p->next;
                           }

                        }

                    }
                    else
                        b = b->next;
                }
                else
                    b = b->next;
            }

            else
                b = b->next;

        }

      // fill unmatched passengers list
      if(check == 0)
      {
         add_to_unmatch(p,bus_header);

      }

      p  = p->next;

    }

    printf("\n\n");

}


// a function to added unmatched passengers to unmatched list
void add_to_unmatch(passengers_list p , busses_list bus_header)
{
    busses_list b = bus_header;

    // check if it's the first node in the list or not

      if(b->nunmatch == 0)
    {
            b->unmatch->traveler_ID = p->traveler_ID;
            b->unmatch->travelling_Date = p->travelling_Date;
            strcpy(b->unmatch->travelling_Time,p->travelling_Time);
            strcpy(b->unmatch->from,p->from);
            strcpy(b->unmatch->to,p->to);
            b->unmatch->next = NULL;

            b->nunmatch = b->nunmatch +1;

    }

    else

    {
            passengers_list New = create_pass_node(b->unmatch);
            New->traveler_ID = p->traveler_ID;
            New->travelling_Date = p->travelling_Date;
            strcpy(New->travelling_Time,p->travelling_Time);
            strcpy(New->from,p->from);
            strcpy(New->to,p->to);

            b->nunmatch = b->nunmatch +1;

    }

}


//a function print the results of assigning passengers to buses
void printAssign(busses_list bus_header)
{
    busses_list b = bus_header;

    while(b != NULL)
    {
        printf("\t BUS LINE: %d \n" , b->busline);
        printf("\t BUS DATE: %d \n" , b->busdate);
        printf("\t BUS TIME: %s \n" , b->bustime);
        printf("\t FROM    : %s \n" , b->from);
        printf("\t TO      : %s \n" , b->to);
        printf("\t CAPACITY: %d \n" , b->capacity);
        printf("\t PRICE   : %d \n\n" , b->price);

        printf("\t PASSENGERS ID'S IN THIS BUS : \n");

        passengers_list p = b->pass;

        if(b->numofpass == 0)
        {
            printf("\t\t NONE \n");
            printf("\n ------------------------------- \n");
            b = b->next;
        }

        else
        {
            while(p != NULL)
          {
            printf("\t       %d \n",p->traveler_ID);
            p = p->next;
          }

          printf("\n --------------------------------- \n");
          b = b->next;
       }

    }
}


// a function to print waiting list for each bus
void waiting_list(busses_list bus_header)
{
    busses_list b = bus_header;

    printf("\t\t Waiting List \n");
    printf("\t\t---------------\n");

    while(b != NULL)
    {
        printf("Passenger ID's waiting in Bus Line %d :  " , b->busline);

        if(b->nwaits == 0)
        {
            printf(" None . \n");
            b = b->next;
        }

        else
        {
            while(b->waiting != NULL)
            {
                printf("%d   ", b->waiting->traveler_ID);
                b->waiting = b->waiting->next;
            }

             printf("\n");
             b =b->next;
        }
    }

}


// a function to print the chosen bus line information
void information(busses_list bus_header , int line)
{

    printf("\n");

    int check = 0 ;

    busses_list b = bus_header;

    while(b != NULL)
    {
        if(b->busline == line)
        {
            printf("\t BUS LINE : %d \n", b->busline);
            printf("\t BUS DATE : %d \n" , b->busdate);
            printf("\t BUS TIME : %s \n", b->bustime);
            printf("\t FROM : %s \t TO : %s \n" , b->from , b->to);
            printf("\t BUS CAPACITY : %d \n",b->capacity);
            printf("\t PRICE : %d \n\n", b->price);

            printf("\t BUS PASSENGERS ID's : \n");

            if(b->numofpass == 0 || b->pass == NULL)
            {
                printf("\t\t NONE \n");
                check = 1 ;
                break;
            }

            else
            {
                while( b->pass != NULL)
              {
                  printf("\t\t %d \n" , b->pass->traveler_ID);
                  check = 1;
                  b->pass = b->pass->next;
              }

              break;
            }
        }

        b = b->next;
     }

       if(check == 0)
     {
        printf(" \t THEiR IS NO BUS WITH BUS LINE %d \n" , line);
     }

}


//a function to add a passenger
void add_new_pass(passengers_list passenger_header, busses_list bus_header)
{
    passengers_list p = passenger_header;

    int id , date;
    char time[10];
    char from[20];
    char to[20];

    printf("\t Enter ID : ");
    scanf("%d",&id);

    // check if their is a passenger with the given id
    while(p != NULL)
    {
        if(p->traveler_ID == id)
        {
            printf("\t Passenger is NOT ADDED , because their is a passenger with this ID ! \n");
            return;
        }
        else
            p = p->next;
    }


    p = passenger_header;


    printf("\n\t Enter Travel Date : ");
    scanf("%d",&date);

    printf("\n\t Enter Travel Time : ");
    scanf("%s",time);

    printf("\n\t Travel From : ");
    scanf("%s",from);

    printf("\n\t To : ");
    scanf("%s",to);

    printf("\n\n");


    // if not create a new node in the passengers list

    ptr_passenger newnode = create_pass_node(p);

    newnode->traveler_ID = id;
    newnode->travelling_Date = date;
    strcpy(newnode->travelling_Time ,time);
    strcpy(newnode->from,from);
    strcpy(newnode->to,to);

    printf("\t passenger %d is Added to Passengers List \n", id);


    // to check if their is a matched bus
    int match = 0;

   busses_list b = bus_header;

   // add the passenger to a matched bus
   while( b!= NULL)
   {
       if(b->busdate == date)
       {
           if(Time(b->bustime , time))
           {
               if(destination( trim(b->from) , trim(from) , trim(b->to) , trim(to) ))
               {
                   match = 1;

                   if(b->numofpass < b->capacity)
                   {
                        if(b->numofpass < b->capacity)
                        {
                           int header = b->numofpass;

                           if( header == 0 )
                           {
                               b->pass->traveler_ID = id;
                               b->pass->travelling_Date = date;
                               strcpy(b->pass->travelling_Time,time);
                               strcpy(b->pass->from,from);
                               strcpy(b->pass->to,to);
                               b->pass->next = NULL;

                               b->numofpass = b->numofpass+1;
                               b->capacity = b->capacity-1;

                           }

                           else
                           {
                               passengers_list New = create_pass_node(b->pass);
                               New->traveler_ID = id;
                               New->travelling_Date = date;
                               strcpy(New->travelling_Time,time);
                               strcpy(New->from,from);
                               strcpy(New->to,to);

                               b->numofpass = b->numofpass+1;
                               b->capacity = b->capacity-1;
                           }

                        }

                        else
                        {
                           int wheader = b->nwaits;

                           if(wheader == 0)
                           {
                               b->waiting->traveler_ID = id;
                               b->waiting->travelling_Date = date;
                               strcpy(b->waiting->travelling_Time,time);
                               strcpy(b->waiting->from,from);
                               strcpy(b->waiting->to,to);
                               b->waiting->next = NULL;

                               b->nwaits = b->nwaits+1;

                           }

                           else
                           {
                               passengers_list New = create_pass_node(b->waiting);
                               New->traveler_ID = id;
                               New->travelling_Date = date;
                               strcpy(New->travelling_Time,time);
                               strcpy(New->from,from);
                               strcpy(New->to,to);

                               b->nwaits = b->nwaits+1;
                           }

                        }

                        printf("\t passenger %d is added to waiting list of bus line %d \n\n \t BUS INFO : \n\n", id,b->busline);
                        printf("\t BUS LINE : %d \n", b->busline);
                        printf("\t BUS DATE : %d \n" , b->busdate);
                        printf("\t BUS TIME : %s \n", b->bustime);
                        printf("\t FROM : %s \t TO : %s \n" , b->from , b->to);
                        printf("\t BUS CAPACITY : %d \n",b->capacity);
                        printf("\t PRICE : %d \n\n", b->price);

                        break;

                    }
                    else
                        b = b->next;
                }
                else
                    b = b->next;
            }

            else
                b = b->next;
       }
       else
        b = b->next;
   }

   if(match == 0)
   {
       printf("\t Their is no matched Bus ! :( \n");
   }

}


// a function to delete a passenger node
void delete_Pnode(passengers_list passenger_head , int pos)
{
    passengers_list p = passenger_head;

    if(isEmpty(passenger_head))
    {
        return;
    }

    if(pos == 1)
    {
        passenger_head = p->next;
        free(p);
        return;
    }

    for(int i = 0 ; p != NULL && i < pos-1 ; i++)
    {
        p = p->next;
    }

    if(p == NULL || p->next == NULL)
    {
        return;
    }


    struct passenger *next = p->next->next;
    free(p->next);

    p->next = next;

}

// a function to print the deletion results
void delete_pass(passengers_list passenger_header , busses_list bus_header , int id , int line)
{

    int Ppos = 0;
    int Bpos = 1;
    printf("\n\n ");

    int check = 0;

    passengers_list p = passenger_header;

    // check if their is a passenger with the given id
    while( p != NULL)
    {
        if(p->traveler_ID == id)
        {
            check = 1;
            break;
        }
        else
        {
            Ppos++;
            p = p->next;
        }

    }

    if(check == 0)
    {
        printf("\t Their is no passenger with this ID ! \n");
    }

    else
    {
        delete_Pnode(p,Ppos);
        printf("\t Passenger %d is deleted From Passengers List.\n\n", id);

    }

    int checkL = 0 ;
    int checkP = 0;

    if( check == 1)
    {
        busses_list b = bus_header;

        while( b != NULL)
        {
            if(b->busline == line)
            {
                checkL = 1;

                while( b->pass != NULL)
                {
                    if(b->pass->traveler_ID == id)
                    {
                        checkP = 1;
                        delete_Pnode(b->pass,++Bpos);
                        b->numofpass = b->numofpass -1;
                        b->capacity = b->capacity +1;
                        printf("\t Passenger %d is deleted from Bus Line %d \n\n", id,line);
                        printf("\t New Bus Info : \n");
                        information(b,b->busline);

                        break;
                    }
                    else
                    {
                        b->pass = b->pass->next;
                        ++Bpos;
                    }

                }
                break;
            }
            else
                b = b->next;
        }
    }


    if(checkL == 0)
    {
        printf("\t Their is no bus line with this Line ! :( \n");
    }

    if(checkP == 0)
    {
        printf("\t Their is no passenger with this id in this bus Line ! \n");
    }

}


// a function to delete a bus from buses list
busses_list deleteBnode(busses_list bus_header , int line)
{
    busses_list L = bus_header;

    if(isEmpty(L))
    {
        return NULL;
    }

    ptr_bus p = L;
    ptr_bus q = L->next;

    if(p->busline == line)
    {
        L = L->next;
        free(p);
        return L;
    }

    else
    {
        while(q->busline != line && q->next != NULL)
      {
         p = p->next;
         q = q->next;
      }

         p->next = q->next;
         free(q);

         return L;

    }


}


// a function to delete a bus
void delete_busNum(busses_list bus_header , int line)
{

    busses_list b = bus_header;

    int check = 0;

    while( b != NULL)
    {
        if(b->busline == line)
        {
            check = 1;
            break;
        }
        else
            b = b->next;
    }

    if(check == 0)
    {
        printf("\t Their is no Bus Line with this Line ! \n");
    }

    else
    {

        while( b!= NULL)
        {
            if(b->busline == line)
            {
                while( b->pass != NULL)
                {
                    if( b->numofpass == 0)
                    {
                        printf("\t No passengers in this bus :) ");
                        break;
                    }

                    else
                    {
                        printf("\t Passenger %d is added to waiting list.\n",b->pass->traveler_ID);
                        add_to_unmatch(b->pass,bus_header);
                    }

                   b->pass = b->pass->next;
                }
                break;
            }
            else
                b = b->next;
        }


        b = deleteBnode(bus_header,line);

        if(b == NULL)
        {
            printf("\t Empty List ! \n");
        }

        else
      {
         printf("\n\t Bus Line %d is deleted from buses List . \n\n", line);
         printf("\t New Buses List : \n");


         while(b != NULL)
         {
            printf("\tBus line: %d\tBus Date: %d\tBus Time: %s\t   From: %s\tTo: %s\tCapacity: %d \tprice: %d \n" , b->busline , b->busdate , b->bustime , b->from , b->to , b->capacity , b->price);
            b = b->next;
         }

      }

    }


}


// a function to add the passenger to the file
void AddToFile(int id , int date , char *time , char *from , char *to)
{
    FILE *p;
    p = fopen("passengers.txt","a");

    char sid[20];
    char sdate[10];

    fputs(itoa(id,sid,10),p);
    fputs("#",p);
    fputs(itoa(date,sdate,10),p);
    fputs("#",p);
    fputs(time,p);
    fputs("#",p);
    fputs(from,p);
    fputs("#",p);
    fputs(to,p);
    fputs("\n",p);

    fclose(p);
}
