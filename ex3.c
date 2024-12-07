/******************
Name: shaked iudcowski
ID: 212488548
Assignment: ex3
*******************/

#include <stdio.h>


//the programs defines
#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
#define DAYS_IN_YEAR 365
#define addOne  1
#define addAll  2  
#define stats  3
#define print  4
#define insights  5
#define deltas  6
#define done  7



char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};
int cnt=0;

void printMenu()
{
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
           "1.Enter Daily Data For A Brand\n"
           "2.Populate A Day Of Sales For All Brands\n"
           "3.Provide Daily Stats\n"
           "4.Print All Data\n"
           "5.Provide Overall (simple) Insights\n"
           "6.Provide Average Delta Metrics\n"
           "7.exit\n");
}

//here are my functions
void restartArray(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]);
int isfull(int changed[]);
void fillcube(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES] , int number, int cnt);
void printNonCompletedArray( char brands[NUM_OF_BRANDS][BRANDS_NAMES] , int changed[5]);  
int gettotal(int cube[365][5][4] , int  number);
int getBSBNum(int cube[365][5][4] , int number);
int getBSBrand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES] , int number1 );
int getBestType( int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES] , int number1);
int getBTNum(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES] , int number1);
void getEverySale(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES] , int cnt , char types[NUM_OF_TYPES][TYPES_NAMES], int bn );  
void findMostProfitableBrand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int cnt, char brands[NUM_OF_BRANDS][BRANDS_NAMES]);
void findMostProfitableType(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int cnt,char types[NUM_OF_TYPES][TYPES_NAMES] );
void findMostProfitableDay(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int cnt);
void getDelta( int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES] , int cnt , int  i );
int getSumDay(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES] , int day, int i);


int main() {
    //the programs inputs
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    int days[NUM_OF_BRANDS] = {0};
    int choice;
    restartArray(cube);
    
    

    printMenu();
    scanf("%d", &choice);
    while(choice != done)
    {
        switch(choice){
            case addOne:
                //...
                break;
            case addAll:



            int number;
            int changed[5]={0};


            // we set data until the user put data at the whole five brands
            while(isfull(changed) ==0)
            {

              //asking for brandinput from the user
              printf("No data for brands ");
              printNonCompletedArray(brands,  changed);
              printf("\n");
              printf("Please complete the data\n");
              scanf("%d", &number);

              // if the user put a number that not between 0-4
              while(number>4 || number<0)
              {
                printf("This brand is not valid\n");
                printf("No data for brands ");
                printNonCompletedArray(brands , changed);
                printf("\n");
                printf("Please complete the data\n");
                scanf("%d", &number);
              }

                //now we fill the cube with data at the relevant place
                fillcube( cube, number, cnt);
                
                // now we set 1 in the relevant place to avoid printing the brand name it the next round
                changed[number] = 1;

            }
            cnt++;


              break;


            case stats:

            int number1;

           // asking from the user an input
            printf("What day would you like to analyze?\n"); 
            scanf("%d", &number1);

            // making the transition from the day the user put to the relevant place in the array
            number1=number1-1;

            // checking if the user put the correct input, asking from the user an input 
            //and making the transition from the day the user put to the relevant place in the array
            while(number1>364 || number1<0)
            {
             printf( "Please enter a valid day.\n");
             printf( "Which day would you like to analyze?\n");
             scanf("%d", &number1);
             number1=number1-1;
            }


            // printing the first scentence
           printf("In day number %d:\n", number1+1);

            // here we get the sales for the day the user asked
           int x= gettotal(cube, number1);
           printf("The sales total was %d\n" , x );

            //here we get the best sold brand and its sales
           int b = getBSBNum( cube , number1);
           int y = getBSBrand(cube , number1 );
           printf("The best sold brand with %d sales was %s\n" , b, brands[y]);

            // here we get the most solt type and its sales
           int z= getBestType( cube , number1);
           int t= getBTNum(cube , number1);
           printf("The best sold type with %d sales was %s\n" , t, types[z]);

      
                break;

          case print:


            int bn=0;

            //printing the first line
            printf("*****************************************\n");
            printf("\n");

            //get the sales for toyoga
            printf("Sales for Toyoga:\n");
            getEverySale(cube ,cnt,  types, bn );

            // now printing sales for HyunNight
            bn=1;
            printf("Sales for HyunNight:\n");
            getEverySale(cube ,cnt,  types, bn );

            // now printing sales for Mazduh
            bn=2;
            printf("Sales for Mazduh:\n");
            getEverySale(cube ,cnt,  types, bn );

            // now printing sales for FolksVegan
            bn=3;
            printf("Sales for FolksVegan:\n");
            getEverySale(cube ,cnt,  types, bn );

            // now printing sales for Key-Yuh
            bn=4;
            printf("Sales for Key-Yuh:\n");
            getEverySale(cube ,cnt,  types, bn );

            //then printing the last line
            printf("\n");
            printf("*****************************************\n");

            break;




            case insights:


            printf("The best-selling brand overall is ");
            findMostProfitableBrand(cube, cnt, brands);
            printf("\n");



            printf("The best-selling type of car is ");
            findMostProfitableType(cube, cnt, types);
            printf("\n");


            printf("The most profitable day was day number ");
            findMostProfitableDay(cube, cnt);
            printf("\n");
            


            break;




            case deltas:

              
            for(int i=0 ; i<5 ; i++)
            {
            printf("Brand: %s, Average Delta: " , brands[i] );
            getDelta(cube , cnt, i );
             printf("\n");
            }


            break;



            case done:

            printf("Goodbye!\n");
            return 0;






            /*
             ......Type
             */
            default:
                printf("Invalid input\n");
        }
        printMenu();
        scanf("%d", &choice);
    }
    printf("Goodbye!\n");
    return 0;
}




void restartArray(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES])
{
 for( int i= 0; i<DAYS_IN_YEAR;i++)
 {
    for(int k = 0; k < NUM_OF_BRANDS; k++)
    {
        for( int j = 0 ; j<NUM_OF_TYPES ;j++)
        {
            cube[i][k][j]=-1;
        }
    }
 }


    
}

int isfull(int changed[])
{
  for(int i=0 ; i<5 ; i++)
  {
    if (changed[i]==0)
    {
      return 0;
    }
  }
  return 1;
}

void fillcube(int cube[365][5][4], int number, int  cnt)
 {
  int n1, n2, n3, n4;

  scanf("%d", &n1);
  scanf("%d", &n2);
  scanf("%d", &n3);
  scanf("%d", &n4);


  cube[cnt][number][0]=n1;
  cube[cnt][number][1]=n2;
  cube[cnt][number][2]=n3;
  cube[cnt][number][3]=n4;


 }


 

 void printNonCompletedArray(char brands[NUM_OF_BRANDS][BRANDS_NAMES],  int changed[5] )
 {
  for(int i=0; i<NUM_OF_BRANDS; i++)
  {
    if(changed[i]==0)
    {
     printf("%s ",  brands[i]); 
    }
  }
 }


      int gettotal(int cube[365][5][4] , int  number1)
      {
        int sum=0;
        for(int k = 0; k < NUM_OF_BRANDS; k++)
        {
          for( int j = 0 ; j<NUM_OF_TYPES ;j++)
          {
            sum= sum + cube[number1][k][j];
          }
        }
        return sum;
      }          


      int getBSBNum(int cube[365][5][4] , int number1)
      {
        int max=0;
        int sum=0;

        for(int i =0 ; i<5; i++)
        {
          for(int k =0 ; k<4; k++)
          {
            sum=sum+cube[number1][i][k];
          }
          if (sum>max)
          {
            max=sum;
          }
          sum=0;
        }
        return max;

      }

      int getBSBrand( int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES] , int number1 )
      {

        int max=0;
        int sum=0;
        int maxindex=-1;

        for(int i =0 ; i<5; i++)
        {
          for(int k =0 ; k<4; k++)
          {
            sum=sum+cube[number1][i][k];
          }
          if (sum>max)
          {
            max=sum;
            maxindex=i;
          }
          sum=0;
        }
        return maxindex;

      }

      int  getBTNum( int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES] , int number1)
      {
        int max=0;
        int sum=0;

        for(int i =0 ; i<NUM_OF_TYPES; i++)
        {
          for(int k =0 ; k<NUM_OF_BRANDS; k++)
          {
            sum=sum+cube[number1][k][i];
          }
          if (sum>max)
          {
            max=sum;
          }
          sum=0;
        }
        return max;

      }

      
        int getBestType(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES] , int number1)
        {
        int max=0;
        int sum=0;
        int maxindex=-1;

        for(int i =0 ; i<NUM_OF_TYPES; i++)
        {
          for(int k =0 ; k<NUM_OF_BRANDS; k++)
          {
            sum=sum+cube[number1][k][i];
          }
          if (sum>max)
          {
            max=sum;
            maxindex=i;
          }
          sum=0;
        }
        return maxindex;

        }



      void getEverySale(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES] , int cnt,  char types[NUM_OF_TYPES][TYPES_NAMES], int bn ) 
      {
         
          for (int i=0 ; i < cnt ; i++)
          {
            printf("day %d- " , i+1);
            for(int k=0; k< NUM_OF_TYPES ; k++)
            {
             printf("%s: " , types[k]);
             int h=cube[i][bn][k];
             if(h==0)
             {
              printf("x");
              printf(" ");
             }
             else
             {
              printf("%d" , h);
              printf(" ");
             }
            }
            printf("\n");
          }
        }


        void findMostProfitableBrand(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int cnt ,  char brands[NUM_OF_BRANDS][BRANDS_NAMES])
        {
          int sum1;
          int max1=0;
          int indexmax1=-1;

            for( int i= 0; i< NUM_OF_BRANDS;i++)
            {
             for(int k = 0; k < NUM_OF_TYPES ; k++)
             {  
              for( int j = 0 ; j< cnt ;j++)
              {
               sum1 += cube[j][i][k];
              }

             }  
             if (sum1>max1)
             {
                max1=sum1;
                indexmax1=i;

             }
              sum1=0;
            }
            printf("%s: " ,brands[indexmax1] );
            printf("%d$" , max1);

            
        }


        void findMostProfitableType(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int cnt,char types[NUM_OF_TYPES][TYPES_NAMES] )
        {

          int sum2;
          int max2=0;
          int indexmax2=-1;

            for( int i= 0; i< NUM_OF_TYPES;i++)
            {
             for(int k = 0; k < NUM_OF_BRANDS ; k++)
             {  
              for( int j = 0 ; j< cnt ;j++)
              {
               sum2 += cube[j][k][i];
              }

             }  
             if (sum2>max2)
             {
                max2 = sum2;
                indexmax2=i;

             }
              sum2=0;
            }
            printf("%s: " ,types[indexmax2] );
            printf("%d$" , max2);
          
        }

        void findMostProfitableDay(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int cnt)
        {
          int sum3;
          int max3=0;
          int indexmax3=-1;

            for( int i= 0; i< cnt;i++)
            {
             for(int k = 0; k < NUM_OF_BRANDS ; k++)
             {  
              for( int j = 0 ; j< NUM_OF_TYPES ;j++)
              {
               sum3 += cube[i][k][j];
              }

             }  
             if (sum3>max3)
             {
                max3 = sum3;
                indexmax3=i;

             }
              sum3=0;
            }
            printf("%d: " , indexmax3+1 );
            printf("%d$" , max3);
          
        }
        
        void getDelta( int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES] , int cnt , int  i )
        {
          float delta=0;
          int d1=0;
          int d2=1;

          while(d2 < cnt )
          {
          int sd1 = getSumDay(cube, d1, i);
          int sd2 = getSumDay(cube, d2, i);
          delta = delta+(sd1-sd2);
          
          d1++;
          d2++;
          
          
          }
          delta= delta/cnt;

            printf("%f", delta);

        }

       int getSumDay(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES] , int day, int i)
       {

        int sumd=0;
          for(int k=0 ; k<NUM_OF_TYPES ; k++)
          {
            sumd+= cube[day][i][k];

          }

          return sumd;




       }



        












