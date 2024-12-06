
/******************
Name: Dan Sonnenblick
ID: 345287882
Assignment: ex3
*******************/

#include <stdio.h>


#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
#define DAYS_IN_YEAR 365
#define INITIALIZE_CUBE -1
#define addOne  1
#define addAll  2
#define stats  3
#define print  4
#define insights  5
#define deltas  6
#define done  7


char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};
int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
int dayCounter = 0;
void initializeCube () {
    for (int day = 0; day < DAYS_IN_YEAR; day++) {
        for (int brand = 0; brand < NUM_OF_BRANDS; brand++) {
            for (int type = 0; type < NUM_OF_TYPES; type++) {
                cube [day][brand][type] = INITIALIZE_CUBE;
            }
        }
    }
}
void printMenu(){
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
           "1.Enter Daily Data For A Brand\n"
           "2.Populate A Day Of Sales For All Brands\n"
           "3.Provide Daily Stats\n"
           "4.Print All Data\n"
           "5.Provide Overall (simple) Insights\n"
           "6.Provide Average Delta Metrics\n"
           "7.exit\n");
}
// function for case 2 (addAll)
void populateADayOfSalesForAllBrands() {
    int stopper = 0;

    int dataEnteredTracker [NUM_OF_BRANDS] = {0};
    while (stopper < NUM_OF_BRANDS) {
        printf ("No data for brands ");
        for (int i = 0; i < NUM_OF_BRANDS; i++) {
            if (dataEnteredTracker[i] == 0 ) {
                printf ("%s ", brands[i]);
            }
        }
            printf("\n Please complete the data \n");
            int brand;
            int SUVSales, sedanSales, coupeSales, GTSales;
            scanf("%d %d %d %d %d", &brand, &SUVSales, &sedanSales, &coupeSales, &GTSales);
            if (brand < 0 || brand >= NUM_OF_BRANDS) {
                printf("This brand is not valid\n");
                continue;
            }
            if (dataEnteredTracker [brand] == 1){
                printf("This brand is not valid\n");
                continue;
            }
            cube[dayCounter][brand][0] = SUVSales;
            cube[dayCounter][brand][1] = sedanSales;
            cube[dayCounter][brand][2] = coupeSales;
            cube[dayCounter][brand][3] = GTSales;
            dataEnteredTracker[brand] = 1;
            stopper++;
        }
    dayCounter++;
    }
// for case 3
    void provideDailyStats () {
    int dayNumber;
    int sum = 0;
    int brandMaxSum = 0;
    int typeMaxSum =0;
    int typeMaxIndex = 0;
    int brandMaxIndex = 0;
    printf ("What day would you like to analyze?\n");
    scanf("%d", &dayNumber);
    if (dayNumber < 1 || dayNumber > DAYS_IN_YEAR || dayNumber > dayCounter) {
        printf("Please enter a valid day.\n");
        printf ("What day would you like to analyze?\n");
        scanf("%d", &dayNumber);
    }
    printf ("In day number %d \n", dayNumber);
    for (int brand = 0; brand < NUM_OF_BRANDS; brand++) {
        for (int type = 0; type < NUM_OF_TYPES; type++) {
            sum += cube[(dayNumber-1)][brand][type];
        }
    } printf ("The sales total was %d\n", sum);

    int sumBrands [NUM_OF_BRANDS] = {0};
    int sumTypes [NUM_OF_TYPES] = {0};
        for (int brand = 0; brand < NUM_OF_BRANDS; brand++) {
            for (int type = 0; type < NUM_OF_TYPES; type++) {
                sumTypes[type] += cube[dayNumber-1][brand][type];
                sumBrands[brand] += cube[dayNumber-1][brand][type];
            }
        }
    brandMaxSum += brandMaxSumReturns(sumBrands, NUM_OF_BRANDS);
    brandMaxIndex += brandMaxIndexReturns(sumBrands, NUM_OF_BRANDS);
    typeMaxSum += typeMaxSumReturns (sumTypes, NUM_OF_TYPES);
    typeMaxIndex += typeMaxIndexReturns(sumTypes, NUM_OF_TYPES);
    printf("The best sold brand with %d sales was %s \n", brandMaxSum, brands[brandMaxIndex]);
    printf ("The best sold type with %d sales was %s \n", typeMaxSum, types[typeMaxIndex]);

}



//for case 4
void printAllData() {
    for (int brand = 0; brand < NUM_OF_BRANDS; brand++) {
        printf ("Sales for %s:\n", brands[brand]);
        for (int days = 0; days <=dayCounter-1; days++) {
            printf("Day %d-", days+1);
            for (int type = 0; type < NUM_OF_TYPES; type++) {
                printf("%s: %d ", types[type], cube[days][brand][type]);
            }
            printf ("\n");
        }
    }
}
//for case 5

    /*This is why we were hired-
     *Here we demonstrate our skills by providing useful insights into the sales data.
     *The simple insights should be printed as:
The best-selling brand overall is X:sales$
The best-selling type of car is Y:sales$
The most profitable day was day number Z:sales$*/
void provideOverallInsights () {
    int sumOfBrands [NUM_OF_BRANDS] = {0};
    int sumTypes[NUM_OF_TYPES] = {0};
    int sumDays [DAYS_IN_YEAR] = {0};
    int dayMaxSum =0;
    int dayMaxIndex = 0;
    int brandMaxSum = 0;
    int typeMaxSum = 0;
    int typeMaxIndex = 0;
    int brandMaxIndex = 0;
    for (int days = 0; days <= dayCounter-1; days++) {
        for (int brand = 0; brand < NUM_OF_BRANDS; brand++) {
            for (int type = 0; type < NUM_OF_TYPES; type++) {
                sumDays[days] += cube[days][brand][type];
                sumOfBrands[brand] += cube[days][brand][type];
                sumTypes[type] += cube[days][brand][type];
            }
        }
    }
    dayMaxSum += dayMaxSumReturns(sumDays, DAYS_IN_YEAR);
    dayMaxIndex += dayMaxIndexReturns(sumDays, DAYS_IN_YEAR);
    brandMaxSum += brandMaxSumReturns(sumOfBrands, NUM_OF_BRANDS);
    brandMaxIndex += brandMaxIndexReturns(sumOfBrands, NUM_OF_BRANDS);
    typeMaxSum += typeMaxSumReturns (sumTypes, NUM_OF_TYPES);
    typeMaxIndex += typeMaxIndexReturns(sumTypes, NUM_OF_TYPES);
    printf("The best-selling brand overall is %s:%d$ \n", brands[brandMaxIndex], brandMaxSum);
    printf ("The best-selling type of car is %s:%d$ \n", types[typeMaxIndex], typeMaxSum);
    printf("The most profitable day was day number %d:%d$\n", (dayMaxIndex+1), dayMaxSum);

}
int dayMaxIndexReturns (int arr[], int numOfDays);
int dayMaxSumReturns (int arr[], int numOfDays);
int brandMaxSumReturns (int arr[], int numOfBrands);
int brandMaxIndexReturns (int arr[], int numOfBrands);
int typeMaxSumReturns (int arr[], int numOfTypes);
int typeMaxIndexReturns (int arr[], int numOfTypes);


// for case 6
void provideDeltaMetrics() {
    float averageDeltas[NUM_OF_BRANDS] = {0};

    for (int brand = 0; brand < NUM_OF_BRANDS; brand++) {
        float delta = 0;
        for (int days = 0; days < dayCounter - 1; days++) {
            for (int type = 0; type < NUM_OF_TYPES; type++) {
                delta += cube[days + 1][brand][type] - cube[days][brand][type];
            }
        }
        averageDeltas[brand] = delta / (dayCounter - 1);
    }

    for (int brand = 0; brand < NUM_OF_BRANDS; brand++) {
        printf("Brand: %s, Average Delta: %f\n", brands[brand], averageDeltas[brand]);
    }
}



    int main() {
        initializeCube();
        int day = 0;
        int choice;
        printMenu();
        scanf("%d", &choice);
        while(choice != done) {
            switch(choice) {
                case addOne: {
                    break;
                }
                case addAll: {
                    populateADayOfSalesForAllBrands ();
                    break;
                }
                case stats: {
                    provideDailyStats ();
                    break;
                }
                case print: {
                    printf ("*****************************************\n");
                    printAllData();
                    printf ("*****************************************\n");
                    break;
                }
                case insights: {
                    provideOverallInsights();
                    break;
                }
                case deltas: {
                    provideDeltaMetrics();
                    break;
                }
                default:
                    printf("Invalid input\n");
            }
            printMenu();
            scanf("%d", &choice);
        }
        printf("Goodbye!\n");
        return 0;
    }





int dayMaxIndexReturns (int arr[], int numOfDays) {
    int max = 0;
    int index =0;
    for (int i = 0; i < numOfDays; i++) {
        if (arr[i] > max) {
            max = arr[i];
            index = i;
        }
    }
    return index;
}
int dayMaxSumReturns (int arr[], int numOfDays) {
    int max = 0;
    for (int i = 0; i < numOfDays; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}
int brandMaxSumReturns (int arr[], int numOfBrands) {
    int max = 0;
    for (int i = 0; i < numOfBrands; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;

}
int brandMaxIndexReturns (int arr[], int numOfBrands) {
    int max = 0;
    int index = 0;

    for (int i = 0; i < numOfBrands; i++) {
        if (arr[i] > max) {
            index = i;
            max = arr[i];
        }
    }
    return index;

}
int typeMaxSumReturns (int arr[], int numOfTypes) {
    int max = 0;
    for (int i = 0; i < numOfTypes; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}
int typeMaxIndexReturns (int arr[], int numOfTypes) {
    int max = 0;
    int index = 0;
    for (int i = 0; i < numOfTypes; i++) {
        if (arr[i] > max) {
            index = i;
            max = arr[i];
        }
    }
    return index;
}










