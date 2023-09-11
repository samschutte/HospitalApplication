#include <iostream>
#include <queue>
#include <vector>

#include "compare.cpp"
#include "Logger.h"
#include "Patient.h"
#include "HospitalFunctions.cpp"
using namespace std;



int main() {
    priority_queue<Patient, vector<Patient>, compare> triage;
    vector<Patient> treated;
    int input = 0;
    logger.log("User has started application");
    cout << "Hospital Administration Application" << endl;
    do{
        displayMenu();
        cout << "How can we assist you today? Enter your selection from the menu" << endl;
        cin >> input;
        logger.log("User selected from menu #" + to_string(input));
        switch(input){
            case 1: // add patient

                addPatient(triage, treated);
                logger.log("Patient was added to system");
                break;
            case 2: // treat next patient

                treatNext(triage,treated);
                logger.log("Next patient was treated according to Triaged Order");
                break;
            case 3: // print one patient report

                printPatient(triage, treated);
                logger.log("Patient report was printed");
                break;
            case 4: // print all patients in triage

                printTriaged(triage);
                logger.log("All patients in triage reports printed");
                break;
            case 5: // print treated

                printTreated(treated);
                logger.log("All patients treated reports printed");
                break;
            case 6: // get next patient

                getNextPatient(triage);

                logger.log("Next person to be treated retrieved");
                break;
            case 7: //treat all

                treatAll(triage,treated);
                logger.log("All patients in triage treated");
                break;
            case 8: // print by doc

                printByDoc(triage,treated);
                logger.log("Patients names printed by specified doctor");
                break;
            case 9: // add bulk patients

                addPatients(triage,treated);
                logger.log("Patients added from file");
                break;
            case 10: // change debugmode

                changeMode();
                logger.log("Debug mode has been toggled");
                break;
            case 11: // get help

                printHelp();
                logger.log("Help menu has been printed");
                break;
            case 12:
                logger.log("User exited program");
                cout << "See ya!" << endl;
                break;
            default:
                logger.log("Invalid entry from user from main menu");
                cout << "Invalid entry made. Please retry" << endl;
        }

    } while(input != 12 );
}