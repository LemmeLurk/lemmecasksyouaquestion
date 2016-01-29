#include <iostream>

using namespace std;

/*
 * Globals
 */

// User input -- how many of each kind?
int numOfFull, numOfHalf, numOfEmpty;

// User input -- how many people
int numOfPeople, numOfBarrels;

// Computer generated amounts
int wineAmountOwed, barrelsOwed;


/*
 * Function Helpers
 */
 
bool enoughBarrels() {

    if (numOfBarrels % numOfPeople == 0)
        return true;
    else
        return false;
}

bool enoughWine() {

    bool check = false;
    
    // Find out how much wine there is total
    // Jorges Forulma: ((7+(7*.05))/3)=3.5;
    int total = numOfFull + (numOfHalf * 0.5);

    // If it divides evenly, Compute and Store result of division
    // Otherwise, return false
    
    /* JOOOOOOOOOOOOOOOOOOOOOOOOOOOORGE
     * FIX THIS, OK?
     * When you use the 7,7,7,3 (for the wine types and number of people, respectively)
     * a false is returned because the wine amount is 10.5, which 3 does not divide evenly.
     * Soooo.... what shall we do????
     */
     
    if (total % numOfPeople == 0) {
        wineAmountOwed = total / numOfPeople;
        check = true;
    }
    
    cout << "\n\n\n\n " total % numOfPeople << "  \n\n\n\n\n\n\n\n";
    
    return check;
        
}

// Distribute until == All wine is equal between the three, all casks are equal
// between the three, and there are 0 casks left

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


void distribute() {
    int fullBarrels[numOfFull]; 
    int halfBarrels[numOfHalf]; 
    int emptyBarrels[numOfEmpty];

    // use struct instead
    int people[numOfPeople][numOfBarrels];

    int thisPersonsWineAmount = 0;
    int thisPersonsBarrelAmount = 0;
    
    for (int i = 0; i < numOfPeople; i++) {
        for (int j = 0; j < numOfBarrels; j++) {
            if (thisPersonsWineAmount + 1 <= wineAmountOwed) {
                people[i][j] = 1;
                thisPersonsWineAmount + 1;
                thisPersonsBarrelAmount + 1;
            }

            if (thisPersonsWineAmount + 0.5 <= wineAmountOwed) {
                people[i][j] = 0.5;
                thisPersonsWineAmount + 0.5;
                thisPersonsBarrelAmount + 1;
            }

            if (thisPersonsBarrelAmount + 1 <= barrelsOwed) {
                people[i][j] = 0;
                thisPersonsBarrelAmount + 1;
            }
        }
        // Don't bloody forget to reset the wine/barrel amount for the next person!
        thisPersonsWineAmount = 0;
        thisPersonsBarrelAmount + 1;
    }

    for (int i = 0; i < numOfPeople; i++) {
        cout << "\nPerson " << i;
        for (int j = 0; j < numOfBarrels; j++) {
            cout << people[i][j] << ", ";
        }

        cout << "\n";
    }

}



int main() {

    // Start by getting user's input
    inputAmounts();

    // Make sure this is possible -- otherwise, end.
    if (enoughBarrels() && enoughWine())
        distribute();
    else
        cout << ".....do the math.\n\n That shit don't work.";

    return 0;
}
