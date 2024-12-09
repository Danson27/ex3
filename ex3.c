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

// function signatures
int dayMaxIndexReturns (int arr[], int numOfDays);
int dayMaxSumReturns (int arr[], int numOfDays);
int brandMaxSumReturns (int arr[], int numOfBrands);
int brandMaxIndexReturns (int arr[], int numOfBrands);
int typeMaxSumReturns (int arr[], int numOfTypes);
int typeMaxIndexReturns (int arr[], int numOfTypes);

// Initializes the cube with the default value
void initializeCube (int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]) {
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
// Case 2: Populate sales data for all brands on a specific day
int populateADayOfSalesForAllBrands(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],
    char brands[NUM_OF_BRANDS][BRANDS_NAMES],
    int dayCounter) {
// Tracks how many brands' data has been entered
    int stopper = 0;
// Tracks which brands have been entered
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
            // Validate the brand index
        if (brand < 0 || brand >= NUM_OF_BRANDS) {
                printf("This brand is not valid\n");
                continue;
            }
            // Check if the brand has already been entered
            if (dataEnteredTracker [brand] == 1){
                printf("This brand is not valid\n");
                continue;
            }
         // Store the data in the cube
            cube[dayCounter][brand][0] = SUVSales;
            cube[dayCounter][brand][1] = sedanSales;
            cube[dayCounter][brand][2] = coupeSales;
            cube[dayCounter][brand][3] = GTSales;
            dataEnteredTracker[brand] = 1;
            stopper++;
        }
    // Increment the day counter
    return dayCounter+1;
    }
// Case 3: Provide daily statistics for a specific day
    void provideDailyStats (
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],
char brands[NUM_OF_BRANDS][BRANDS_NAMES],
char types[NUM_OF_TYPES][TYPES_NAMES],
int dayCounter
    ) {
    int dayNumber;
    int sum = 0;
    int brandMaxSum = 0;
    int typeMaxSum =0;
    int typeMaxIndex = 0;
    int brandMaxIndex = 0;
    // Prompt for day number and validate input
    printf ("What day would you like to analyze?\n");
    scanf("%d", &dayNumber);
    while (dayNumber < 1 || dayNumber > DAYS_IN_YEAR || dayNumber > dayCounter) {
        printf("Please enter a valid day.\n");
        printf ("What day would you like to analyze?\n");
        scanf("%d", &dayNumber);
    }
    printf ("In day number %d: \n", dayNumber);
    // Calculate total sales for the day
    for (int brand = 0; brand < NUM_OF_BRANDS; brand++) {
        for (int type = 0; type < NUM_OF_TYPES; type++) {
            sum += cube[(dayNumber-1)][brand][type];
        }
    } printf ("The sales total was %d\n", sum);
    // Calculate sums for each brand and type
    int sumBrands [NUM_OF_BRANDS] = {0};
    int sumTypes [NUM_OF_TYPES] = {0};
        for (int brand = 0; brand < NUM_OF_BRANDS; brand++) {
            for (int type = 0; type < NUM_OF_TYPES; type++) {
                sumTypes[type] += cube[dayNumber-1][brand][type];
                sumBrands[brand] += cube[dayNumber-1][brand][type];
            }
        }
    // Find the best-selling brand and type
    brandMaxSum += brandMaxSumReturns(sumBrands, NUM_OF_BRANDS);
    brandMaxIndex += brandMaxIndexReturns(sumBrands, NUM_OF_BRANDS);
    typeMaxSum += typeMaxSumReturns (sumTypes, NUM_OF_TYPES);
    typeMaxIndex += typeMaxIndexReturns(sumTypes, NUM_OF_TYPES);
    printf("The best sold brand with %d sales was %s \n", brandMaxSum, brands[brandMaxIndex]);
    printf ("The best sold type with %d sales was %s \n", typeMaxSum, types[typeMaxIndex]);

}



//for case 4
void printAllData(
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],
    char brands[NUM_OF_BRANDS][BRANDS_NAMES],
    char types[NUM_OF_TYPES][TYPES_NAMES],
    int dayCounter) {
        // Iterate through each brand
    for (int brand = 0; brand < NUM_OF_BRANDS; brand++) {
        // Print the sales header for the current brand
        printf ("Sales for %s:\n", brands[brand]);
        // Iterate through the days recorded so far
        for (int days = 0; days <=dayCounter-1; days++) {
            // Print the day number (1-based indexing for user-friendly output)
            printf("Day %d-", days+1);
            // Iterate through each type of car
            for (int type = 0; type < NUM_OF_TYPES; type++) {
                // Print sales data for the current type on the current day
                printf(" %s: %d ", types[type], cube[days][brand][type]);
            }
            //Move to the next line after printing all types for the current day
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
void provideOverallInsights (int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],
    char brands[NUM_OF_BRANDS][BRANDS_NAMES],
    char types[NUM_OF_TYPES][TYPES_NAMES],
    int dayCounter) {
    // Arrays to store the total sales data for brands, types, and days
    int sumOfBrands [NUM_OF_BRANDS] = {0};
    int sumTypes[NUM_OF_TYPES] = {0};
    int sumDays [DAYS_IN_YEAR] = {0};

    // Variables to store the maximum sales and their respective indices
    int dayMaxSum =0;
    int dayMaxIndex = 0;
    int brandMaxSum = 0;
    int typeMaxSum = 0;
    int typeMaxIndex = 0;
    int brandMaxIndex = 0;
    // Loop through each recorded day, brand and type of car
    for (int days = 0; days <= dayCounter-1; days++) {
        for (int brand = 0; brand < NUM_OF_BRANDS; brand++) {
            for (int type = 0; type < NUM_OF_TYPES; type++) {
                // Accumulate sales for the current day, brand, and type
                sumDays[days] += cube[days][brand][type];
                sumOfBrands[brand] += cube[days][brand][type];
                sumTypes[type] += cube[days][brand][type];
            }
        }
    }
    // Calculate the maximum sales and their indices using helper functions
    dayMaxSum += dayMaxSumReturns(sumDays, DAYS_IN_YEAR);
    dayMaxIndex += dayMaxIndexReturns(sumDays, DAYS_IN_YEAR);
    brandMaxSum += brandMaxSumReturns(sumOfBrands, NUM_OF_BRANDS);
    brandMaxIndex += brandMaxIndexReturns(sumOfBrands, NUM_OF_BRANDS);
    typeMaxSum += typeMaxSumReturns (sumTypes, NUM_OF_TYPES);
    typeMaxIndex += typeMaxIndexReturns(sumTypes, NUM_OF_TYPES);

    // Print insights
    printf("The best-selling brand overall is %s: %d$ \n", brands[brandMaxIndex], brandMaxSum);
    printf ("The best-selling type of car is %s: %d$ \n", types[typeMaxIndex], typeMaxSum);
    printf("The most profitable day was day number %d: %d$\n", (dayMaxIndex+1), dayMaxSum);

}



// for case 6
void provideDeltaMetrics(
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],
    char brands[NUM_OF_BRANDS][BRANDS_NAMES],
    int dayCounter) {
    // Array to store the average delta for each brand
    float averageDeltas[NUM_OF_BRANDS] = {0};

    // Loop through each brand
    for (int brand = 0; brand < NUM_OF_BRANDS; brand++) {
        float delta = 0;

        // Loop through each day except the last (to calculate changes)
        for (int days = 0; days < dayCounter - 1; days++) {
            // Calculate daily change in sales for the current brand and type
            for (int type = 0; type < NUM_OF_TYPES; type++) {
                delta += cube[days + 1][brand][type] - cube[days][brand][type];
            }
        }
        // Calculate the average delta by dividing the total delta by the number of changes
        averageDeltas[brand] = delta / (dayCounter - 1);
    }

    // Print the average delta for each brand
    for (int brand = 0; brand < NUM_OF_BRANDS; brand++) {
        printf("Brand: %s, Average Delta: %f\n", brands[brand], averageDeltas[brand]);
    }
}



    int main() {
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
    char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};
    int dayCounter = 0;
    initializeCube(cube);
    int choice;
        // Display the main menu
        printMenu();
        scanf("%d", &choice);
        while(choice != done) {
            switch(choice) {
                case addOne: {
                    break;
                }
                // Populate data for all brands
                case addAll: {
                    dayCounter = populateADayOfSalesForAllBrands(cube, brands, dayCounter);
                    break;
                }
                // Provide stats for a specific day
                case stats: {
                    provideDailyStats(cube, brands, types, dayCounter);
                    break;
                }
                // Print all sales data
                case print: {
                    printf ("*****************************************\n");
                    printAllData(cube, brands, types, dayCounter);
                    printf ("*****************************************\n");
                    break;
                }
                // Provide overall insights into the data
                case insights: {
                    provideOverallInsights(cube, brands, types, dayCounter);
                    break;
                }
                // Provide average delta metrics for each brand
                case deltas: {
                    provideDeltaMetrics(cube, brands, dayCounter);
                    break;
                }
                // Handle invalid menu inputs
                default:
                    printf("Invalid input\n");
            }
             // Display the menu again after an operation
            printMenu();
            // Get the user's next choice
            scanf("%d", &choice);
        }
         printf("Goodbye!\n"); // Exit message
        return 0; // Exit the program
    }




// Function to get the index of the maximum value in a type sales array
int dayMaxIndexReturns (int arr[], int numOfDays) {
    // Variable to store the current maximum value
    int max = 0;
    // Variable to store the index of the maximum value
    int index =0;
    for (int i = 0; i < numOfDays; i++) {
        // If the current value is greater than max
        if (arr[i] > max) {
            // Update the maximum value
            max = arr[i];
             //Upate the index
            index = i;
        }
    }
    // Return the index of the maximum value
    return index;
}
// Function to get the maximum value in an array representing daily sales
int dayMaxSumReturns (int arr[], int numOfDays) {
    int max = 0;
    for (int i = 0; i < numOfDays; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}
// Function to get the maximum value in an array representing sales by brand
int brandMaxSumReturns (int arr[], int numOfBrands) {
    int max = 0;
    for (int i = 0; i < numOfBrands; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;

}
// Function to get the index of the maximum value in an array representing sales by brand
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
// Function to get the maximum value in an array representing sales by product type
int typeMaxSumReturns (int arr[], int numOfTypes) {
    int max = 0;
    for (int i = 0; i < numOfTypes; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}
// Function to get the index of the maximum value in an array representing sales by product type
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
