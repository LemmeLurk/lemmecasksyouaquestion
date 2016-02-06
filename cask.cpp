#include <iostream>
#include <math.h>

using namespace std;

/*
 * Globals
 */

// User input -- how many of each kind?
int numOfFull, numOfHalf, numOfEmpty;

// User input -- how many people
int numOfPeople; 
// User inputs amount of each type -- compute total amount
int numOfBarrels;

// Computer generated amounts
double wineAmountOwed;
int    barrelsOwed;

// Simple Person 'object'
struct Person {
    double wineAmount   = 0.0;
    int    barrelAmount = 0;
};


/*
 * Function Helpers
 */
 
bool enoughBarrels() {

    if (numOfBarrels % numOfPeople == 0)
        return true;
    else
        return false;
}

/*
 * First find out if the wineAmount allocated to each can be made with the
 * quanity of wine given
 */
bool enoughWine() {
    // Assume it won't work; let the computation change this to true if need be
    bool check = false;
    
    // Find out how much wine there is total
    double total = numOfFull + (numOfHalf * 0.5);

    
    // Case 1.) Total amount of wine divides evenly among the number of people
    // Case 2.) Total / numOfPeople has remainder that can be made by half
    // bottles -- represented by 0.5
    // If it divides evenly, Compute and Store result of division
    // Otherwise, return false
    if (fmod(total, numOfPeople) == 0 || 
            (fmod(fmod(total, numOfPeople), 0.5) == 0)) {
        // Compute and Store the wine amount owed to each person
        wineAmountOwed = total / numOfPeople;
        check = true;
    }
    
    return check;
}

void inputAmounts() {
    cout << "How many Full?";
    cin >> numOfFull;

    cout << "How many Half?";
    cin >> numOfHalf;

    cout << "How many Empty?\n";
    cin >> numOfEmpty;

    cout << "How many people?";
    cin >> numOfPeople;
    
    // Compute and Store the number of barrels
    numOfBarrels = numOfFull + numOfHalf + numOfEmpty;
}

bool wineAmountEven(struct Person *people) {
    bool check = true;

    double amounts[numOfPeople];
    for (int i = 0; i < numOfPeople; i++) {
        amounts[i] = people[i].wineAmount;
    }

    double currentAmount = amounts[0];

    for (int i = numOfPeople - 1; i >= 1; i--) {
        // First instance when this check fails means not all amounts are even
        if (amounts[i] == currentAmount) {
            continue;
        }
        else {
            check = false;
            break;
        }
    }

    return check;
}

bool barrelAmountEven(struct Person *people) {
    bool check = true; 

    double amounts[numOfPeople];
    for (int i = 0; i < numOfPeople; i++) {
        amounts[i] = people[i].barrelAmount;
    }

    double currentAmount = amounts[0];

    for (int i = numOfPeople - 1; i > 0; i--) {
        if (amounts[i] == currentAmount) {
            continue;
        }
        else {
            check = false;
            break;
        }
    }

    return check;
}


// Distribute until == All wine is equal between the three, all casks are equal
// between the three, and there are 0 casks left
void distribute(struct Person *person) {
    // Loop through as many people as needed
    for (int i = 0; i < numOfPeople; ++i) {
        for (int j = 0; j < numOfBarrels; ++j) {
            // Give Full?
            if (person[i].wineAmount + 1 < wineAmountOwed && 
                    numOfFull > 0) {
                person[i].wineAmount++;
                person[i].barrelAmount++;
                --numOfFull;
            }
            // Give Half?
            else if (person[i].wineAmount + 0.5 <= wineAmountOwed && 
                    numOfHalf > 0) {

                person[i].wineAmount += 0.5;
                person[i].barrelAmount++;
                --numOfHalf;
            }
            else {
                cout << "Person " << i << endl;
                cout << "Wine Amount + 1: " << person[i].wineAmount + 1 << endl;
                cout << "wineAmountOwed: " << wineAmountOwed << endl;
                cout << "numOfFull: " << numOfFull << endl;
            }            
        }
    }

    // Check that amount is even, and given everyone same amount of casks
    while (!barrelAmountEven(person)) {
        for (int i = 0; i < numOfPeople; ++i) {
            if (person[i].barrelAmount + 1 < barrelsOwed && numOfEmpty > 0) {
                person[i].barrelAmount++;
                --numOfEmpty;
            }
        }
    }

    for (int i = 0; i < numOfPeople; i++) {
        cout << "\nPerson " << i << endl;
        
        cout << "Wine amount: \t";
        cout << person[i].wineAmount << endl;

        cout << "Barrel amount: \t";
        cout << person[i].barrelAmount << endl;

        cout << "\n\n";
    }
}

// Why pass size if numOfPeople is available? -- sig.'s more explicit, perhaps?
void createPersons(struct Person *person, int size) {
    for (int i = 0; i < size; ++i) { 
        person[i].wineAmount   = 0;
        person[i].barrelAmount = 0;
    }
}



int main() {

    // Start by getting user's input
    inputAmounts();

    // Create array of Person 'objects' -- size of numOfPeople
    struct Person people[numOfPeople];
    
    // Fill in the values
    createPersons(people, numOfPeople);

    // Make sure this is possible -- otherwise, end.
    if (enoughBarrels() && enoughWine())
        distribute(people);
    else
        cout << ".....do the math.\n\n That shit don't work.";

    return 0;
}

