// A command-line interface program concept for the UCLan Student Pizza machine. Created by Will Corkill 
#include <iostream>
#include <iomanip> // iomanip is used to display some numbers, such as credit prices, to two decimal places (Shukaylo, 2011)

void clearInput() // The keyword 'void' has been used, to signal that the function does not return a value.
{
    const int defaultConsoleWidth = 80; // A constant for the default console width has been used to prevent the occurance of a 'magic number'.
    std::cin.clear(); // Clear the value given to std::cin
    std::cin.ignore(defaultConsoleWidth, '\n'); // Ignore the values on the current line, as to stop another error from occurring.
}
int getIntegerInputWithinRange(int maxValue, std::string errorMessage) // Used to extract a number for validation within a certain range, reduces repeating code and bugs
// The maxValue defined is the upper limit for the range, and the error message will be displayed each time the user submits invalid input.
{
    int tempValueHolder; // Used to store the value the user wishes to enter
    std::cin >> tempValueHolder;
    while (std::cin.fail() || tempValueHolder < 1 || tempValueHolder > maxValue) // 1 is used as the values for this will always be between 1 and maxValue
    {
        clearInput(); // std::cin must be cleared and the ignore reset in order to function properly again
        std::cout << errorMessage << "\nPlease try again (1 - " << maxValue << "): ";
        std::cin >> tempValueHolder;
    }
    return tempValueHolder; // The validated input will be returned to the user
}
float addToBalance(float currentBalance) /* The function will return the addition to the user's balance, the function accepts the user's current balance as a parameter
A function has been used for adding credits to a user's balance, this is because the user may need to add credits if they order a pizza with an insufficient funds, thus reducing repeating code. */
{
    const int minBalanceIncrement = 0; // The minimum value the user can increase at one time.
    const int maxBalanceIncrement = 100; // The maximum value the user can add at one time.
    std::cout << "You have chosen to add to your balance.\nYour current balance is " << currentBalance << " credits." << "\nThe maximum credits you can add at one time is 100 credits (Enter 0 to cancel).\n\nEnter the number of credits you wish to add: ";
    float creditsToAdd; // Used to allow the user to enter decimal values if they wish to add 'partial' amounts of credits
    std::cin >> creditsToAdd;
    while (std::cin.fail() || creditsToAdd < minBalanceIncrement || creditsToAdd > maxBalanceIncrement) // getIntegerInputWithinRange can't be used because it is possible to add 0 credits to cancel
    {
        std::cout << "The amount entered is invalid!\nNote that the maximum number of credits you can add at one time is " << maxBalanceIncrement << "\n\nPlease try again (0 - 100): ";
        std::cin >> creditsToAdd;
    }
    if (creditsToAdd == minBalanceIncrement) // The code to execute if the user enters 0, which means to cancel the addition to their balance
    {
        std::cout << "\nBalance addition cancelled.\nYour balance remains at " << currentBalance << " credits.\n\n";
        return 0;
    }
    else // If the amount greater than zero, then there are no special conditions that should be applied.
    {
        std::cout << "\nYou have successfully added " << creditsToAdd << " credits to your balance.\n" << "Your new balance is: " << currentBalance + creditsToAdd << " credits.\n";
        return creditsToAdd;
    }
}

int main()
{
    std::cout << "\nWelcome to the UCLan Student Pizza machine.\n" << std::fixed << std::setprecision(2); // The two functions at the end fix the precision to show two decimal places on numbers with one or more decimal places (Shukaylo, 2011)
    int exitConfirmation = 1; // Will be checked in the main do-while loop so the program exits when told.
    float customerBalance = 0.00; // A float is used as the number can be decimal, a float is used instead of a double due to not needing increased precision and to reduce the memory used (4 bytes instead of 8).
    
    const int pizzaSizes[3] = {7, 9, 14}; // Note for further code, units to be used are inches
    const std::string pizzaToppings[6] = {"Ham", "Mushrooms", "Pepperoni", "Olives", "Pineapple", "Extra Cheese"};
    const float pizzaSizePrices[3] = {3.00, 5.50, 7.25};
    const float toppingPrices[6] = {0.8, 0.5, 1.0, 0.3, 0.6, 1.2};
    const int lenPizzaSizes = sizeof(pizzaSizes)/sizeof(*pizzaSizes); // The division is to calculate the size of the array in memory as there is no built-in function to calculate the size of an array in C++. (Charlesworth and Dormann, 2021)
    const int lenToppingPrices = sizeof(pizzaToppings)/sizeof(*pizzaToppings); // (Charlesworth and Dormann, 2021)

    do // A do-while loop is used to ensure that the loop runs at least once.
    {
        std::cout << "\n+-----+\n\nMain Menu\n\n1) Add credits to balance\n2) Order Pizza\n3) Exit\n\nYour current credit balance is: " << customerBalance << " credits";
        std::cout << "\n\nEnter an option to continue (1, 2, or 3): "; // An integer choice between 1 and 3 will be used for the main menu choice, with full validation provided below using getIntegerInputWithinRange
        int mainMenuChoice = getIntegerInputWithinRange(3, "Sorry, this is an invalid option, valid options are:\n1) Add credits to balance\n2) Order pizza\n3) Exit");
        std::cout << "\n+-----+\n\n";

        switch (mainMenuChoice) // A switch-case is used as there are three defined outcomes after variable validation.
        {
            case 1: // For future reference, case 1 is used for adding to the customer balance
                customerBalance += addToBalance(customerBalance);
                break; // All cases in a switch-case need to be broken from to return to the main body of code
            case 2: // Case 2 is used to order pizza.
                int orderAnotherPizza; // Will be used in the do-while loop to check if the user wishes to order another pizza. An integer is used instead of a bool for consistency.
                orderAnotherPizza = 1; // The variable is assigned to in this manner because of the way variables are initialised in switch-case blocks. 1 is used as the default value of a range 1-2.
                do // Do-while used so at least one pizza is ordered.
                {
                    float userPizzaCost = 0;
                    bool addedToppings[lenToppingPrices] = {}; // The toppings that have been added will be stored here to avoid duplicate adding of toppings. lenToppingPrices as the array does not need to be longer than the number of toppings
                    bool cancelPizzaOrder = false;
                    std::cout << "You have chosen to order a pizza.\nYour current balance is " << customerBalance << " credits.\n\nPlease select a size of pizza from the options below:\n";
                    // PIZZA SIZES
                    for (int index = 0; index < lenPizzaSizes; index++) // Uses a loop with the number of pizza sizes to output all options
                    {
                        std::cout << index + 1 << ") " << pizzaSizes[index] << " inches (Price: " << pizzaSizePrices[index] << " credits)" <<  std::endl;
                    }
                    std::cout << lenPizzaSizes + 1 << ") Return to Main Menu\n\nSelect your size of pizza (1 - " << lenPizzaSizes + 1 << "): ";
                    int selectedPizzaSize = getIntegerInputWithinRange(lenPizzaSizes + 1, "Sorry this is an invalid size of pizza."); // The user can select a value between 1 and the number of sizes of pizza
                    if (selectedPizzaSize == lenPizzaSizes + 1)
                    {
                        std::cout << "\nPizza order cancelled.\n";
                        cancelPizzaOrder = true; // Will be used to break out of the outer-loop once the inner-loop is broken from.
                        break;
                    }
                    else
                    {
                        userPizzaCost += pizzaSizePrices[selectedPizzaSize - 1]; // Add the cost of the pizza to the cost variable. - 1 is used as the indexing in C++ begins at 0, not 1.
                        std::cout << "\nYou have chosen a " << pizzaSizes[selectedPizzaSize - 1] << "-inch pizza.\nThe base cost of this pizza is " << userPizzaCost << " credits\n\n+-----+\n\nPizza Toppings\n";
                        // PIZZA TOPPINGS
                        int addAnotherTopping = 1; // Determine if the user wishes to add further toppings after each loop
                        std::cout << "\nPlease choose at least one topping from the list below:";
                        do
                        {
                            std::cout << std::endl;
                            int quantityAddedToppings = 0;
                            for (int index = 0; index < lenToppingPrices; index++) // This loop will be used to calculate the number of added toppings
                            {
                                if (addedToppings[index] == true)
                                {
                                    quantityAddedToppings++;
                                }
                            }
                            if (quantityAddedToppings == lenToppingPrices)
                            {
                                std::cout << "You have added the maxmimum number of toppings!\n\n";
                                break;
                            }
                            else
                            {
                                for (int index = 0; index < lenToppingPrices; index++) // Show the user the available toppings
                                {
                                    std::cout << index + 1 << ") " << pizzaToppings[index] << " (Price: " << toppingPrices[index] << " credits)" << std::endl;
                                }
                                std::cout << lenToppingPrices + 1 << ") Return to Main Menu" << std::endl;
                                std::cout << std::endl << "Enter your choice here (1 - " << lenToppingPrices + 1 << "): ";
                                int toppingChoice = getIntegerInputWithinRange(lenToppingPrices + 1, "Sorry, this is not a valid topping!");
                                if (toppingChoice == lenToppingPrices + 1)
                                {
                                    std::cout << "\nPizza order cancelled.\n";
                                    cancelPizzaOrder = true;
                                    break; // Returns the user to the main menu
                                }
                                else
                                {
                                    int indexedToppingChoice = toppingChoice - 1; // The array index of the chosen topping
                                    if (addedToppings[indexedToppingChoice])
                                    {
                                        std::cout << "\nYou have already added " << pizzaToppings[indexedToppingChoice] << " to your pizza!\nPlease try again.\n";
                                    }
                                    else
                                    {
                                        addedToppings[indexedToppingChoice] = true; // Setting this value to true in the array will stop it from being selected multiple times
                                        userPizzaCost += toppingPrices[toppingChoice - 1]; // Add the cost of the topping to the cost variable. -1 used for indexing reasons
                                        std::cout << "\nYou have chosen to add " << pizzaToppings[toppingChoice - 1] << " to your pizza.\nThe new cost of the pizza is " << userPizzaCost << " credits\n";
                                        std::cout << "Would you like to add another topping?\n1) Yes\n2) No\nEnter your choice here (1 - 2): ";
                                        addAnotherTopping = getIntegerInputWithinRange(2, "That option is invalid! Valid options are:\n1) Yes\n2) No\n"); // 2 is used as the maximum range as there are only 2 options.
                                    }
                                }
                            }
                        } while (addAnotherTopping == 1);
                    }
                    // Check if the order has been cancelled
                    if (cancelPizzaOrder) {
                        break;
                    }
                    /* Display the pizza info to the user */
                    std::cout << "\nThe pizza ordering process is now complete.\nYour pizza will cost " << userPizzaCost << " credits.\n\nAdditional toppings:\n";
                    for (int index = 0; index < lenToppingPrices; index++) // Check the added toppings array for "true" boolean values
                    {
                        if (addedToppings[index] == true)
                        {
                            std::cout << "- " << pizzaToppings[index] << " (Price: " << toppingPrices[index] << " credits)" << std::endl;
                        }
                    }
                    std::cout << std::endl;
                    // Manage if there are insufficient funds
                    while (userPizzaCost > customerBalance)
                    {
                        std::cout << "You do not have sufficient funds to purchase this pizza!\nWould you like to add funds to your balance?\n1) Add to balance\n2) Cancel order\nEnter your choice here (1 - 2): ";
                        if (getIntegerInputWithinRange(2, "This is not a valid choice!") == 2)
                        {
                            std::cout << "\nPizza order cancelled.\n\n";
                            cancelPizzaOrder = true;
                            break; // Immediately exit from the case and return to the main menu
                        }
                        else
                        {
                            customerBalance += addToBalance(customerBalance);
                            std::cout << std::endl;
                        }
                    }
                    // Check if the order has been cancelled
                    if (cancelPizzaOrder) {
                        break;
                    }
                    // Ask the user if they wish to pay or cancel
                    std::cout << "Your pizza is ready to order. Would you like to pay " << userPizzaCost << " credits for this pizza?\n1) Yes, pay for my pizza\n2) No, cancel my order\nEnter an option (1 - 2): ";
                    if (getIntegerInputWithinRange(2, "This is not a valid option!") == 1)
                    {
                        customerBalance -= userPizzaCost; // Remove the cost of the pizza from the user's current balance
                        std::cout << "\nThank you for purchasing a pizza from the UCLan Pizza Machine\nYour remaining balance is " << customerBalance << " credits.\n\n";
                    }
                    else
                    {
                        std::cout << "Your order has been cancelled\n";
                        break;
                    }
                    // Ask user if they wish to order another pizza
                    std::cout << "Would you like to order another pizza?\n1) Yes\n2) No\nEnter an option (1 - 2): ";
                    orderAnotherPizza = getIntegerInputWithinRange(2, "Sorry, this is an invalid option, valid options are:\n1) Yes, order another pizza\n2) No, return to main menu");
                } while (orderAnotherPizza == 1);
                break;
            case 3: // Case 3 is used to exit the program.
                std::cout << "You have chosen to exit this service.\n1) Return to main menu\n2) Exit\nEnter an option to continue (1 - 2): "; // 2 is used as there are only two valid options to continue
                exitConfirmation = getIntegerInputWithinRange(2, "Sorry, this is an invalid option, valid options are:\n1) Return to main menu\n2) Exit");
                std::cout << std::endl; // Add a line gap before the main menu if the return option is chosen
                break;
        }
    } while (exitConfirmation == 1);
    std::cout << std::endl << "Exit confirmed.\nThank you for using the UCLan Student Pizza machine.\n";
    return 0;
}
