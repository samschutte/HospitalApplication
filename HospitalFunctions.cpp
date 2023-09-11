//
// Created by schut on 4/20/2023.
//

#include <iostream>
#include <queue>
#include <unistd.h>
#include "Logger.h"
#include "Patient.h"
#include "compare.cpp"
using namespace std;
static void printReport(const Patient&);

static void addPatient(priority_queue<Patient, vector<Patient>, compare> & triage,
vector<Patient> & treated){
    // get input for all fields, create new patient and add to treated or triage
    logger.log("User accessed addPatient function");

    Patient pat;
    string temp;
    int priority;
    int numAilments = 0;
    vector<string> ailments;
    cout <<"Enter the patient's first name" << endl;
    cin >> temp;
    pat.setFirstname(temp);
    cout <<"Enter the patient's middle name" << endl;
    cin >> temp;
    pat.setMiddleName(temp);
    cout <<"Enter the patient's last name" << endl;
    cin >> temp;
    pat.setLastName(temp);
    cout <<"Enter the patient's suffix if applicable. If not enter 'none' " << endl;
    cin >> temp;
    if (temp != "none")
        pat.setSuffix(temp);
    else
        pat.setSuffix("");
    cout <<"Enter the patient's doctor's name"<< endl;
    cin >> temp;
    pat.setDoctor(temp);
    cout <<"How many ailments does the patient have? (Enter a number)" << endl;
    cin >> numAilments;
    cin.ignore();
    if(numAilments == 0)
        ailments.emplace_back("");
    for (int i=1; i<= numAilments; i++) {
        cout << "Enter ailment #" << i << endl;
        getline(cin,temp);
        ailments.push_back(temp);
    }
    pat.setAilements(ailments);
    ailments.clear();
    cout << "Has the patient been treated already? (yes/no)" << endl;
    cin >> temp;
    if (temp == "yes")
        pat.setTreated(true);
    else
        pat.setTreated(false);
    cout<< "Lastly, what is the patient's priority, 1 being the highest? " << endl;
    cin >> priority;
    while (priority < 1 ){
        cout << "That is an invalid priority level, please retry" << endl;
        cin >> priority;
    }
    pat.setPriority(priority);
    if (pat.isTreated())
        treated.push_back(pat);
    else
        triage.push(pat);
}

static void treatNext(priority_queue<Patient, vector<Patient>, compare> & triage, vector<Patient> & treated){
    // sleep interval
    logger.log("User accessed treatNext function");
    Patient toTreat = triage.top();
    toTreat.setTreated(true);
    cout << toTreat.getFirstname() + " " + toTreat.getLastName() + " is being treated :) " << endl;
    int wait = rand() % 3 + 1;
    sleep(wait);
    cout << toTreat.getFirstname() + " " + toTreat.getLastName() + " is treated :) " << endl;
    treated.push_back(toTreat);
    triage.pop();
    logger.log("User treated " + toTreat.getFirstname() + " " + toTreat.getLastName() );
}

static void printPatient(priority_queue<Patient, vector<Patient>, compare> & triage, vector<Patient> & treated){
    logger.log("User accessed PrintPatients function");
    // get first and last from user
    string first, last;
    // flag
    bool found = false;
    cout << "Enter first name of patient you would like to see report on " << endl;
    cin >> first;
    cout << "Enter last name of patient you would like to see report on " << endl;
    cin >> last;

    // create copy of triage to not affect the list, but rather iterate
    //********** deep copy? **************
    priority_queue<Patient, vector<Patient>,compare>& copyTriage = triage;
    while(!copyTriage.empty()){
        if(copyTriage.top().getFirstname() == first && copyTriage.top().getLastName() == last){
            printReport(copyTriage.top());
            found = true;
            logger.log("Patient found in triaged container");
            break;
        }
        copyTriage.pop(); // remove top patient, look at next
    }
    for(const Patient& a : treated){
        if (a.getFirstname() == first && a.getLastName() == last){
            printReport(a);
            found = true;
            logger.log("Patient found in treated container");
            break;
        }
    }

    if(!found){
        cout << "No patient was found with that name :( Try again!" << endl;
        logger.log("Patient not found in triaged or treated containers");
    }

}
static void printTreated(vector<Patient> & treated){
    logger.log("User accessed printTreated function");
    // iterate through treated container
    for(const Patient& a: treated){
        printReport(a);
    }
    // call print patient

}
static void getNextPatient(priority_queue<Patient, vector<Patient>, compare> & triage){
    logger.log("User accessed getNextPatient function");
    if(!triage.empty()){
        const Patient& a = triage.top();
        cout << "Next patient to be treated is " + a.getFirstname() + " " + a.getLastName() << endl;
    }
    else{
        cout << "There are no patients in line to be treated " << endl;
    }


}
static void treatAll(priority_queue<Patient, vector<Patient>, compare> & triage, vector<Patient> & treated){
    logger.log("User accessed treatAll function");
    while(!triage.empty()){
        Patient a = triage.top();
        a.setTreated(true);
        treated.push_back(a);
        triage.pop();
        int wait = rand() %3 +1;
        sleep(wait);
        cout << "Patient with name: " + a.getFirstname() + " " + a.getLastName() + " has been treated" << endl;
        logger.log("Patient with name: " + a.getFirstname() + " " + a.getLastName() + " has been treated");

    }
    logger.log("treatALl function completed");
}

static void printTriaged(priority_queue<Patient, vector<Patient>, compare> & triage){
    // iterate through triaged
    priority_queue<Patient,vector<Patient>,compare> copy = triage;
    while(!copy.empty()){
        Patient a = copy.top();
        printReport(a);
        copy.pop();
    }
    // print report, or call print patient
}
static void printByDoc(priority_queue<Patient, vector<Patient>, compare> & triage, const vector<Patient>& treated){
    logger.log("User accessed printByDoc function");
    string doc;
    cout << "Please enter the name of the doctor to see their patients" << endl;
    cin >> doc;
    // vector of patients to hold that doctors patients (clear after each call)
    vector<Patient> docPatient;
    // iterate through triaged and treated
    priority_queue<Patient,vector<Patient>,compare> copy = triage;
    while(!copy.empty()){
        if(copy.top().getDoctor() == doc){
            docPatient.push_back(copy.top());
        }
        copy.pop(); // remove top, move on to next Patient
    }
    for( const Patient& a: treated){
        if (a.getDoctor() == doc){
            docPatient.push_back(a);
        }
    }

    cout << "There are " << docPatient.size() << " patients being cared for by " + doc  << endl;
    if(!docPatient.empty()) {
        cout << doc + "'s patients are: " << endl;
        for (const Patient &a: docPatient)
            cout << a.getFirstname() + " " + a.getLastName() << endl;
    }
    docPatient.clear();
}
static void addPatients(priority_queue<Patient, vector<Patient>, compare> & triage, vector<Patient> & treated){
    logger.log("User accessed addPatients function");
    string fileName, line;
    Patient pat;
    vector<string> ailment;
    cout << "Enter the name of the file that contains patient information " <<endl;
    cin >> fileName;
    ifstream file;
    file.open(fileName);
    if(file.is_open()){
        while(getline(file,line)){
            size_t colinPosition = line.find(":");
            string type = line.substr(0,colinPosition);
            string value = line.substr(colinPosition+1);
            if(!line.empty()) {
                if (type == "firstName") {
                    pat.setFirstname(value);
                } else if (type == "middleName") {
                    pat.setMiddleName(value);
                } else if (type == "lastName") {
                    pat.setLastName(value);
                } else if (type == "suffix") {
                    pat.setSuffix(value);
                } else if (type == "ailment") {
                    ailment.push_back(value);
                } else if (type == "doctor") {
                    pat.setDoctor(value);
                } else if (type == "treated") {
                    if(value == "0")
                        pat.setTreated(false);
                    else
                        pat.setTreated(true);
                } else if (type == "priority") {
                    int priority = stoi(value);
                    pat.setPriority(priority);
                }
            }else{ // line is empty

                pat.setAilements(ailment);
                if(pat.isTreated())
                   treated.push_back(pat);
                else
                    triage.push(pat);
                ailment.clear();
                logger.log("Added patient " + pat.getFirstname() + " " + pat.getLastName());
                cout << "Added patient " + pat.getFirstname() + " " + pat.getLastName() << endl;
            }
        }
        // same code as else, adds last patient of file that doesn't end in empty line
        pat.setAilements(ailment);
        if(pat.isTreated())
            treated.push_back(pat);
        else
            triage.push(pat);
        ailment.clear();
        logger.log("Added patient " + pat.getFirstname() + " " + pat.getLastName());
        cout << "Added patient " + pat.getFirstname() + " " + pat.getLastName() << endl;


        logger.log("Ended patient file, file was closed");
    } else{
        cout << "File did not open :(" << endl;
    }
}
static void changeMode(){
    logger.log("User has accessed changeMode function");
    logger.setDebugMode(!logger.getDebugMode()); // set debug to opposite of what it currently is
}
static void printReport(const Patient& a){
    cout << "First name: " + a.getFirstname() << endl;
    cout << "Middle name: " + a.getMiddleName() << endl;
    cout << "Last name: " + a.getLastName() << endl;
    cout << "Suffix: " + a.getSuffix() << endl;
    cout << "Doctor: " + a.getDoctor() << endl;
    cout << "Treated: " << a.isTreated() << endl;
    cout << "Priority: " <<  a.getPriority() << endl;
    for(const string& s: a.getAilments())
        cout << "Ailment: " + s << endl;
    if(a.getAilments().empty())
        cout << "No Ailments" << endl;
    cout << endl;
}
static void printHelp(){
    logger.log("Help menu accessed");
    int in;
    cout << "What menu item do you want more information on?" << endl;
    cin >> in;
    switch(in){
        case 1:
            logger.log("Help requested for add patient");
            cout << "Adding a patient will prompt input for their first and last name,"
                    " their suffix, doctor, and ailments. It will also prompt input for "
                    "if the patient has been treated already and their priority " << endl;
            break;
        case 2:
            logger.log("Help requested for treat most urgent patient");
            cout << "Treat most urgent patient will get the patient with the next"
                    "highest priority based on their first and last name that is inputted"
                    "by the user. That patient will be treated" << endl;
            break;
        case 3:
            logger.log("Help requested for print patient report");
            cout << "Print patient report will prompt the user to input patient's first "
                    "and last name, and then the system will print a report with their information" << endl;
            break;
        case 4:
            logger.log("Help requested for print all patients in triage");
            cout << "Print all patients in triage will print reports for each patient that"
                    "has not yet been treated. Reports will include all of the patient's information" << endl;
            break;
        case 5:
            logger.log("Help requested for print all patients treated");
            cout << "Print all patients treated will print reports for each patient that has already"
                    "been treated. Reports will include all of the patient's information" <<endl;
            break;
        case 6:
            logger.log("Help requested for Next Patient");
            cout << "Next patient will give the first and last name of the next patient to be"
                    "treated according to priority" << endl;
            break;
        case 7:
            logger.log("Help requested for Treat All Patients");
            cout << "Treat all Patients will treat the patients according to priority order"
                    " that have not already been treated. This may take some time depending on "
                    " how many untreated patients there are " << endl;
            break;
        case 8:
            logger.log("Help requested for print patients by doctor");
            cout << "Print patients by doctor will prompt the user to enter a valid doctor's name."
                    " The system will output a list of first and last name of patients of that doctor." << endl;
            break;
        case 9:
            logger.log("Help requested for Add multiple patients");
            cout << "Add multiple patients will prompt the user to enter the name of a file"
                    " that contains patient information. The system will add these patients to the"
                    " appropriote containers" << endl;
            break;
        case 10:
            logger.log ("Help requested for Toggle Debug Mode");
            cout << "Toggle Debug mode will change the current state of debug mode. When turned on,"
                    " operations of the system will be outputted to the console. When not in debug mode,"
                    " operations of the system will be outputted to file log.txt" << endl;
            break;
        default:
            logger.log("User entered invalid input for help menu");
            cout << "Please enter a number 1-10 to see a help guide for that selection " << endl;



    }
}
static void displayMenu(){
    cout << "1.     Add patient to system" << endl;
    cout << "2.     Treat most urgent patient" << endl;
    cout << "3.     Print patient report" << endl;
    cout << "4.     Print all patients in triage " << endl;
    cout << "5.     Print all patients treated " << endl;
    cout << "6.     Get next patient to be treated" << endl;
    cout << "7.     Treat all Patients" << endl;
    cout << "8.     Print patients by doctor" << endl;
    cout << "9.     Add multiple patients" << endl;
    cout << "10.    Toggle Debug mode"   << endl;
    cout << "11.    Help Guide" << endl;
    cout << "12.    Quit" << endl;
}