/*
    1- login (Data)

    2- Welcoming the user & asking for the service
        (A) ADSL Services
          1- Request
            - Gigabytes consumption during a period of time
            - Number in waiting list and time of waiting
            - To be transfered to customer service
          2- General information(ADSL number , Name , Quota , Balance)
          3- Billing (Recharge , Renewing the quota)
          4- Technical support

        (B) Mobile phone Services
          1- Request
            - Megabytes consumption
            - Minutes consumption
            - Points consumption
            - Number in waiting list and time of waiting
            - To be transfered to customer service
         2- General information (Mobile Number, Name , Quota , Balance)
         3- Billing (Recharge , Renewing the quota)
         4- Complaints

    3- getting a valid answer

    4- asking the user if he/she wants another service

    5- Asking the user to give us his feedback


*/

/*
          Name                          ID

       Abdullah Ayman                21-101131
       Amar Wael                     21-101152
       Asem Ibrahiem                 21-101159
       Youssef Nagah                 21-101139
*/

#include<stdio.h>
#include<string.h>                               // we searched for it to get //the strings

//  Functions' Prototypes

void services(
    char service_type,
    int option,
    int curr_user_index,
    float balances[4],
    char systems[6][20],
    char users_systems[4][20],
    int systems_costs[6],
    int mbs_CPD[4][16],
    int minutes_CPD[4][16],
    char usernames[4][20],
    char mobile_numbers[4][20],
    int systems_full_points[6],
    float balances_adsl[4],
    int gbs_CPD[4][16],
    int adsl_systems_cost[4],
    int adsl_systems_Gbs[4],
    char adsl_numbers[4][20],
    char users_adsl_systems[4][20]
);

void feedback();

int login(char mobile_phones[4][20], char passwords[4][20]);

void print_options(char* service_type, int* option);

int get_valid_num(int min, int max);

void request_mobile(
    int user_index,
    int balance,
    char systems[6][20],
    char* user_system,
    int systems_costs[6],
    int mbs_CPD[4][16],
    int minutes_CPD[4][16]
);

void calc_consumption(int arr[16], char title[20]);

void general_info_m(
    char username[20],
    char phone_number[20],
    float balance,
    char system[20]
);

int waiting_list_time(int min_time, int max_time);

int waiting_list_num(int min_num, int max_num);

void renew(
    float* balance,
    int system_cost,
    int system_points,
    char points_or_gbs[],
    int curr_user_index
);

void recharging(float* balance);


void complaints();

void request_adsl(
    int user_index,
    float balances_adsl,
    char* adsl_systems,
    int adsl_system_cost[6],
    int gbs_CPD[4][16]
);

void general_info_adsl(
    char username[20],
    char adsl_number[20],
    float balances_adsl,
    char users_adsl_systems[20]
);

void technical_support_adsl();
void billing(
    float* balance,
    int system_cost,
    int system_points,
    char points_or_gbs[],
    int curr_user_index
);

// the body of the functions

// (1)General functions

int login(char mobile_phones[4][20], char passwords[4][20]) {              // a) Function to validate the loging in proccess
    char curr_password[20], curr_number[20];
    int valid = 0, curr_user_index = 0; // 1 valid, 0 not valid

    while (valid == 0) {

        printf("Please Enter Your number: ");
        gets(curr_number);                                                //To insert a string

        for (int i = 0; i < 4; i++) {
            if (strcmp(curr_number, mobile_phones[i]) == 0) {                     //To compare the entered mobile number with the right one
                curr_user_index = i;
                valid = 1;
                break;
            }
        }

        printf("Please Enter Your password: ");
        gets(curr_password);                                             //To insert a string


        if (strcmp(curr_password, passwords[curr_user_index]) != 0) valid = 0;     //To compare the entered password with the right one

        if (valid == 0) {
            puts("");
            puts("Phone number or password is incorrect !");
        }
    }
    puts("");
    puts("Logged in Successfully\n");

    return curr_user_index;                                         // To return cuurent index to be used in the other functions
}

int get_valid_num(int min, int max) {                                            // b) Function to validate the user's choice in all proccesses
    int entered_data;

    do {
        printf("Please enter a valid number (from %d to %d): ", min, max);
        scanf_s("%d", &entered_data);
    } while (entered_data < min || entered_data > max);
    return entered_data;                                         // To return the max and mini value
}

void print_options(char* service_type_ptr, int* option) {                            //c) Printing the services to the user to choose from
    //Choose the service you want
    puts("\nDo you want Mobile Services or ADSL Services?\n");
    do {
        puts("Enter 'M' for Mobile Services or 'A' for ADSL Services\n");
        scanf_s(" %c", service_type_ptr, 1);
    } while (*service_type_ptr != 'A' && *service_type_ptr != 'a' && *service_type_ptr != 'M' && *service_type_ptr != 'm');

    if (*service_type_ptr == 'A' || *service_type_ptr == 'a')   //ADSL Services
    {
        puts("");
        puts("\nEnter '1' for Request");
        puts("Enter '2' for General information");
        puts("Enter '3' for Billing");
        puts("Enter '4' for Technical Support");

        *option = get_valid_num(1, 4);                                           // Calling the validation function for the first time

    }
    else if (*service_type_ptr == 'M' || *service_type_ptr == 'm')   //mobile Services
    {
        puts("");
        puts("\nEnter '1' for Request");
        puts("Enter '2' for General information");
        puts("Enter '3' for Billing");
        puts("Enter '4' for Complaints");
        puts("");

        *option = get_valid_num(1, 4);                                           // Calling the validation function for the second time
    }

}

// (2)Functions for both Mobile and ADSL services

void calc_consumption(int arr[16], char title[20]) {                           //d) Function to calculate the consumptio  of the user
    // Keyboard Type: numbers
    printf("Initial Day: ");
    
    int inital_day = get_valid_num(1, 15);                                    // Calling the validation function for the third time
    
    printf("\nFinal Day: ");

    int final_day = get_valid_num(inital_day + 1, 16);                        // Calling the validation function for the fourth time

    int sum = 0;
    for (int i = inital_day - 1; i < final_day; i++) {
        sum += arr[i];
    }
    printf("\nYou have consumed %d %s from day %d to day %d", sum, title, inital_day, final_day);
}



int waiting_list_time(int min_time, int max_time)                              //e) Function to give you the time of waiting
{
    int result = 0, low_time = 0, hi_time = 0;


    low_time = min_time;
    hi_time = max_time + 1; // include max_num in output


    srand(time(NULL));                                  //https://www.geeksforgeeks.org/rand-and-srand-in-ccpp/ 
    result = (rand() % (hi_time - low_time)) + low_time;
    printf("\nAnd the time of waiting is: %d minutes\n", result);
    return result;
}

int waiting_list_num(int min_num, int max_num)                                  //f) Function to give you waiting number
{
    int result = 0, low_num = 0, hi_num = 0;


    low_num = min_num;
    hi_num = max_num + 1; // include max_num in output


    srand(time(NULL));                                //https://www.geeksforgeeks.org/rand-and-srand-in-ccpp/
    result = (rand() % (hi_num - low_num)) + low_num;
    printf("Your number in waiting list is: %d\n", result);
    waiting_list_time(50, 200);
    return result;
}

void renew(                                                                   //g) Function to renew the quota
    float* balance,
    int system_cost,
    int system_points,
    char points_or_gbs[],
    int curr_user_index
) {
    char proceed = 'y';
    printf("\nRenewal price is %d, Are you sure you want to proceed? ('y' for yes, any other letter for no): ", system_cost);
    scanf_s(" %c", &proceed, 1);
    if (proceed == 'y' || proceed == 'Y') {                             
        if (*balance >= system_cost) {                                     // Checking the balance
            puts("Your quota has been renewed successfully!");
            printf("Your current %s are: %d", points_or_gbs, system_points);
            *balance -= system_cost;
            printf("\nYour balance now is: %.2f", *balance);
        }
        else {
            char agree = 'y';                                  
            puts("Your balance is not enough to renew the quota.");
            printf("Do you want to recharge? ('y' for yes, otherwise for no):");
            scanf_s(" %c", &agree, 1);
            if (agree = 'y') recharging(balance);                       // Calling recharging function
           
            puts("");

            renew(                                                     // Calling renew function to renew after transaction
                balance,
                system_cost,
                system_points,
                points_or_gbs,
                curr_user_index
            );
        }
    }
}

void recharging(float* balance) {                                           //h) Recharging function
    float recharged = 0;
    printf("\nYour current balance is: %.2f", *balance);
    printf("\nHow much do you want to recharge (in EGP): ");
    scanf_s("%f", &recharged);
    *balance += recharged;
    printf("\n\nYour balance after the transaction is: %.2f", *balance);
};

void billing(                                                                //i) Function to make the user recharge and renew the quota
        float* balance,
        int system_cost,
        int system_points,
        char points_or_gbs[],
        int curr_user_index
        ) {
    puts("What do you want to do: ");
    puts("");
    puts("Enter '1' for recharging");
    puts("Enter '2' for renew the quota");
    puts("");
    int option = get_valid_num(1, 2);                                     //Calling validation function for the fifth time
    char choice;
    if (option == 1) {
        recharging(balance);                                             //Calling recharging function 
    }
    else
    {
        renew(                                                         // Calling renew function
            balance,
            system_cost,
            system_points,
            points_or_gbs,
            curr_user_index
        );
    }
}

// (3)Mobile Services functions

void request_mobile(                                                        // j) Function to make the user ask for(consumption, Waiting list and customer service
    int user_index,
    int balance,
    char systems[6][20],
    char* user_system,
    int systems_costs[6],
    int mbs_CPD[4][16],
    int minutes_CPD[4][16]
) {
    puts("");
    puts("What do you want to request for: ");
    puts("");
    puts("Enter '1' for Miga-bytes consumption");
    puts("Enter '2' for Minutes consumption");
    puts("Enter '3' for Points consumption");
    puts("Enter '4' for Waiting list");
    puts("Enter '5' to be transfered to one of our customer service members");
    puts("");

    int option = get_valid_num(1, 5);                                     // Calling the validation function for the sixth time

    puts("");

    switch (option)
    {
    case 1:                                                             // megabytes consumption
        // Keyboard Type: numbers
        calc_consumption(mbs_CPD[user_index], "Mbs");
        break;
    case 2:                                                            // Minutes consumption
        calc_consumption(minutes_CPD[user_index], "Minutes");
        break;
    case 3:                                                           // Points consumption
        printf("Initial Day: ");
        int inital_day = get_valid_num(1, 15);
        printf("\nFinal Day: ");
        int final_day = get_valid_num(inital_day + 1, 16);

        int sum = 0;
        for (int i = inital_day - 1; i < final_day; i++) {
            sum += mbs_CPD[user_index][i];
        }
        for (int i = inital_day - 1; i < final_day; i++) {
            sum += minutes_CPD[user_index][i];
        }

        printf("\nYou have consumed %d Points from day %d to day %d", sum, inital_day, final_day);
        break;
    case 4:                                                          // Waiting list
        waiting_list_num(1, 100);
        break;
    case 5:                                                         // Customer service
        puts("To talk to one of our customer service members call the Hotline: 77750");
        puts("or if you want to chat one of our customer service team go to : euitelecom.com/support_chat");
        break;
    }
}

void general_info_m(                                                      // k)To give the user his general information (Username, phone number, Balance and System)
    char username[20],
    char phone_number[20],
    float balance,
    char system[20]
) {
    printf("\nUsername: %s\nPhone Number: %s\nBalance: %.2f\nSystem: %s",
        username, phone_number, balance, system);
}

void complaints() {                                                  // l) If user wants to give some complaints
    char complaint[400];
    puts("Kindly enter your complaint (up to 300 letter):");
    getchar();
    gets(complaint);
    puts("Thank you for your feedback\n we will work on your complaint soon.");
}

// (4)Adsl service functions

void request_adsl(                                               // m) Function to make the user ask for (Consumption , waiting lis and customer service)
    int user_index,
    float balances_adsl,
    char* adsl_systems,
    int adsl_system_cost[6],
    int gbs_CPD[4][16]
) {
    puts("");
    puts("What do you want to request for: ");
    puts("");
    puts("Enter '1' for Giga-bytes consumption");
    puts("Enter '2' for Waiting list");
    puts("Enter '3' to be transfered to one of our customer service members");
    puts("");

    int option = get_valid_num(1, 3);                           // Calling the validation function for the seventh time

    puts("");

    switch (option)
    {
    case 1:                                                  // Gigabytes consumption
        // Keyboard Type: numbers
        calc_consumption(gbs_CPD[user_index], "Gbs");
        break;
    case 2:                                                 // Waiting list
        waiting_list_num(1, 100);
        break;
    case 3:                                                // Customer service
        puts("To talk to one of our customer service members call the Hotline: 77750");
        break;
    }
}

void general_info_adsl(                                       //n) To give the user his general information(Username, ADSL number , balance and system)
    char username[20],
    char adsl_number[20],
    float balances_adsl,
    char users_adsl_systems[20]
) {
    printf("\nUsername: %s\nPhone Number: %s\nBalance: %.2f\nSystem: %s",
        username, adsl_number, balances_adsl, users_adsl_systems);
}

void technical_support_adsl() {                              //o) If the user wants to contact technical support 
    puts("common problems : ");
    puts("If there is a problem in internet connection, try to:");
    puts("");
    puts("1- Restart the device");
    puts("2- Make sure that all cables are connected");
    puts("3- Make sure that the problem is not in electricity");
    puts("");
    puts("if the problem hasn't been solved yet , press y \n ");
    char problem_solved_or_not;
    scanf_s(" %c", &problem_solved_or_not, 1);
    if (problem_solved_or_not == 'y')
    {
        puts("");
        puts("To talk to one of our customer service members call the Hotline: 77750");
    }

}

// Function that includes all our funcions to be put in main

void services(
    char service_type,
    int option,
    int curr_user_index,
    float balances[4],
    char systems[6][20],
    char users_systems[4][20],
    int systems_costs[6],
    int mbs_CPD[4][16],
    int minutes_CPD[4][16],
    char usernames[4][20],
    char mobile_numbers[4][20],
    int systems_full_points[6],
    float balances_adsl[4],
    int gbs_CPD[4][16],
    int adsl_systems_cost[4],
    int adsl_systems_Gbs[4],
    char adsl_number[4][20],
    char users_adsl_systems[4][20]
) {
    if (service_type == 'M' || service_type == 'm') {
       // calling Mobile functions
        switch (option) {
        case 1:                                              //calling request function  
            request_mobile(
                curr_user_index,
                balances[curr_user_index],
                systems,
                users_systems[curr_user_index],
                systems_costs,
                mbs_CPD,
                minutes_CPD
            );
            break;
        case 2:                                            // Calling general info function
            general_info_m(
                usernames[curr_user_index],
                mobile_numbers[curr_user_index],
                balances[curr_user_index],
                systems[curr_user_index]
            );
            break;
        case 3:                                           // calling billing function
            billing(
                &balances[curr_user_index],
                systems_costs[curr_user_index],
                systems_full_points[curr_user_index],
                "points",
                curr_user_index
            );
            break;
        case 4:                                          // calling complaints function
            complaints();
            break;
        };
    }
    // Calling ADSL functions
    else {
        switch (option) {
        case 1:                                        // Calling request function
            request_adsl(
                curr_user_index,
                balances_adsl[curr_user_index],
                users_adsl_systems[curr_user_index],
                adsl_systems_cost,
                gbs_CPD
            );
            break;
        case 2:                                      // Calling general info function
            general_info_adsl(
                usernames[curr_user_index],
                adsl_number[curr_user_index],
                balances_adsl[curr_user_index],
                users_adsl_systems[curr_user_index]
            );
            break;
        case 3:                                      // calling billing function
            billing(
                &balances_adsl[curr_user_index],
                adsl_systems_cost[curr_user_index],
                adsl_systems_Gbs[curr_user_index],
                "gbs",
                curr_user_index
            );
            break;
        case 4:                                    // Calling technical support function
            technical_support_adsl();
            break;
        }
    }
}

// Function to be called after finishing all services

void feedback() {                             
    char feedback[400];
    puts("Kindly give us your feedback for the services (up to 300 letter):");
    puts("");
    getchar();
    gets(feedback);                                               //To insert a string
    puts("");
    puts("Thank you for your feedback!");
}

// The main function

int main(void) {

    // Database
    // Users' Data-----------------------------------------------------
    char usernames[4][20] = {
        "Abdullah Ayman",
        "Amar Wael",
        "Asem Elwany",
        "Youssef Nagah"
    };
    char passwords[4][20] = {
        "whatisth",
        "21052003",
        "12345678",
        "15122003"
    };
    char mobile_numbers[4][20] = {
        "01753509018",
        "01729759236",
        "01747592747",
        "01722347400",
    };

    char adsl_numbers[4][20] = {
        "0223454836",
        "0223634633",
        "0223463455",
        "0223787687",
    };

    // User's mobile Database

    float balances_mobile[4] = { 100, 150, 25.5, 200 };

    char users_mobile_systems[4][20] = {
        "Hekaya",
        "flexat",
        "kicks",
        "SupermegaX"
    };

    int mbs_CPD[4][16] = {
        {12, 25, 13, 27, 11, 22, 13, 25, 12, 24, 12, 24, 13, 24, 15, 21},
        {16, 22, 14, 24, 16, 21, 13, 22, 17, 24, 12, 27, 11, 22, 19, 21},
        {10, 28, 11, 23, 12, 26, 12, 21, 12, 26, 12, 25, 12, 27, 11, 21},
        {11, 22, 11, 20, 12, 25, 11, 26, 13, 28, 16, 21, 12, 23, 15, 23}
    };

    
    int minutes_CPD[4][16] = {
        {20, 50, 30, 70, 10, 20, 30, 50, 20, 40, 20, 40, 30, 40, 50, 10},
        {60, 20, 40, 40, 60, 10, 30, 20, 70, 40, 20, 70, 10, 20, 90, 10},
        {0, 80, 10, 30, 20, 60, 20, 100, 20, 60, 20, 50, 20, 70, 10, 10},
        {10, 20, 10, 15, 20, 50, 10, 60, 30, 80, 60, 10, 20, 30, 50, 30},
    };

    char mobile_systems[6][20] = {
        "Hekaya",
        "flexat",
        "kicks",
        "SupermegaX",
        "Mared",
        "Number#1"
    };
    int systems_full_points[6] = {
       3000,
       2500,
       4000,
       3500,
       1000,
       8000
    };
    int mobile_systems_costs[6] = {
        65,
        55,
        80,
        73,
        25,
        150
    };

    //ADSL Database
    
    float balances_adsl[4] = { 200 , 350 , 150 , 40 };

    char users_adsl_systems[4][20] = {
        "Super 140",
        "Mega 200",
        "Max 250",
        "Ultra 400"
    };

    int gbs_CPD[4][16] = {
        {2, 5, 3, 7, 1, 2, 3, 5, 2, 4, 2, 4, 3, 4, 5, 1},
        {6, 2, 4, 4, 6, 1, 3, 2, 7, 4, 2, 7, 1, 2, 9, 1},
        {0, 8, 1, 3, 2, 6, 2, 10, 2, 6, 2, 5, 2, 7, 1, 1},
        {1, 2, 1, 0, 2, 5, 1, 6, 3, 8, 6, 1, 2, 3, 5, 3},
    };
    
    int adsl_systems_cost[4] = {
        137,
        193,
        239,
        388
    };

    int adsl_systems_Gbs[4] = {
        140,
        200,
        250,
        400
    };

    // -----------------------------------------------------------

    puts("\t\t\tHello to our Chatbot, We hope to do what you want.");        // Welcoming the user
    puts("");

    int curr_user_index = login(mobile_numbers, passwords);                 // calling the log in function

    printf("Hello, %s\n", usernames[curr_user_index]);

    char cont = 'y';
    
    // The loop to repeat our services operations

    do {
        char service_type;
        int option;

        print_options(&service_type, &option);                            // Calling print options function


        services(                                                        // Calling services function which includes all services functions
            service_type,
            option,
            curr_user_index,
            balances_mobile,
            mobile_systems,
            users_mobile_systems,
            mobile_systems_costs,
            mbs_CPD,
            minutes_CPD,
            usernames,
            mobile_numbers,
            systems_full_points,
            balances_adsl,
            gbs_CPD,
            adsl_systems_cost,
            adsl_systems_Gbs,
            adsl_numbers,
            users_adsl_systems
        );
        puts("");
        printf("\nDo you need another service (y for yes, otherwise for no): ");              // Asking the user if he wants to repeat the operations
        scanf_s(" %c", &cont, 1);
        puts("");

    } while (cont == 'y' || cont == 'Y');

    feedback();                                                                               // Asking the user to give us his feedback and opinion on our services 

    return 0;
}

                                     // End of the program _______________________________________________

                                                             /*Thank you*/