//
// Created by schut on 4/5/2023.
//

#ifndef HOSPITALAPP_PATIENT_H
#define HOSPITALAPP_PATIENT_H

#include<string>
#include<vector>

using namespace std;

class Patient {
public:

    Patient();

    Patient(const Patient& other);

    Patient& operator=(const Patient& other);

    const string &getFirstname() const;

    const string &getMiddleName() const;

    const string &getLastName() const;

    const string &getSuffix() const;

    const string &getDoctor() const;

    bool isTreated() const;

    int getPriority() const;

    void setFirstname(const string &firstname);

    void setMiddleName(const string &middleName);

    void setLastName(const string &lastName);

    void setSuffix(const string &suffix);

    void setDoctor(const string &doctor);

    void setTreated(bool treated);

    void setPriority(int priority);

    vector<string> getAilments() const;
    void setAilements(const vector<string> & ailment);

private:
    string firstname;
    string middleName;
    string lastName;
    string suffix;
    string doctor;
    bool treated;
    int priority{};
    vector<string> ailments;
};


#endif //HOSPITALAPP_PATIENT_H
