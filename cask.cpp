#include <iostream>
#include <math.h>

using namespace std;

/*
 * Globals
 */

// User input -- how many of each kind?
int numOfFull, numOfHalf, numOfEmpty;

// User input -- how many people
int numOfPeople, numOfBarrels;

// Computer generated amounts
double wineAmountOwed;
int barrelsOwed;


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
 * First problem is that there is a fractional part that needs to be accounted
 * for -- I am still hard coding that this fractional part is .5 (because this
 * is the half bottles of wine)
 * This is fine if the ammounts never change.. 
 * This works so long as the business rules don't change
 */
bool enoughWine() {

    bool check = false;
    
    // Find out how much wine there is total
    // Jorges Forulma: ((7+(7*.05))/3)=3.5;
    double total = numOfFull + (numOfHalf * 0.5);

    // If it divides evenly, Compute and Store result of division
    // Otherwise, return false
    
    /*
     * First find out if the wineAmount allocated to each can be made with the
     * quanity of wine given
     * Next, distribute the wine -- giving first from the FullWine, then Half
     *
     * Lastly, will need to distribute barrels -- the default problem causes the
     * last guy to get a lot more barrels -- because all that was left was half,
     * and so he ended up with 2:1 
     */
    
    // Total does not divide evenly, nor can the remainder be made from the Half
    // bottles
    if (total / numOfPeople != 0 && fmod)
    float fractionalPart = total / numOfPeople;

    // If the whole numbers can be made using the Full amounts
    // and the fractional part can be made using the fractional part
    if (((int)total % numOfPeople == 0) ||
        total 
        fmod(fractionalPart, 0.5) == 0 {

        wineAmountOwed = total / numOfPeople;
        check = true;
    }
    
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
    char fullBarrels[numOfFull]; 
    char halfBarrels[numOfHalf]; 
    char emptyBarrels[numOfEmpty];

    // use struct instead
    char people[numOfPeople][numOfBarrels];

    int thisPersonsWineAmount = 0;
    int thisPersonsBarrelAmount = 0;
    
    for (int i = 0; i < numOfPeople; i++) {
        int j = 0;
        while (thisPersonsWineAmount < wineAmountOwed) {
            // Shouldn't there be a check for giving away more 'Full Casks' than
            // are in stock?
            if (thisPersonsWineAmount + 1 <= wineAmountOwed) {
                people[i][j] = 'F';
                j++;
                thisPersonsWineAmount += 1;
                thisPersonsBarrelAmount += 1;

                --numOfFull;
            }

            if (thisPersonsWineAmount + 0.5 <= wineAmountOwed) {
                people[i][j] = 'H';
                j++;
                thisPersonsWineAmount += 1;
                thisPersonsBarrelAmount += 1;

                --numOfHalf;
            }

            // Should I rethink giving people Empty barrels just for the hell of
            // it? 
            // Should it be in a seperate function call -- that is done after
            // the amounts are poured in order to distribute the empty until all
            // people have an even amount of barrels?
            if (thisPersonsBarrelAmount + 1 <= barrelsOwed) {
                people[i][j] = 'E';
                j++;

                thisPersonsBarrelAmount += 1;

                --numOfEmpty;
            }
        }


        // Don't bloody forget to reset the wine/barrel amount for the next person!
        thisPersonsWineAmount = 0;
        thisPersonsBarrelAmount = 0;
        j = 0;
    }

    for (int i = 0; i < numOfPeople; i++) {
        cout << "\nPerson " << i << endl;
        for (int j = 0; j < 7; j++) {
            cout << people[i][j] << ", ";
        }

        cout << "\n\n";
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

