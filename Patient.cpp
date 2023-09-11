//
// Created by schut on 4/5/2023.
//

#include "Patient.h"
Patient::Patient() {
    treated = false;
}

Patient::Patient(const Patient &other) {
    firstname = other.firstname;
    middleName = other.middleName;
    lastName = other.lastName;
    suffix = other.suffix;
    doctor = other.doctor;
    treated = other.treated;
    priority = other.priority;
    ailments = other.ailments;
}

Patient& Patient::operator=(const Patient& other) {
    if (this != &other) {
        // Copy member variables
        firstname = other.firstname;
        middleName = other.middleName;
        lastName = other.lastName;
        suffix = other.suffix;
        doctor = other.doctor;
        treated = other.treated;
        priority = other.priority;
        ailments = other.ailments;
    }
    return *this;
}

const string &Patient::getFirstname() const {
    return firstname;
}

const string &Patient::getMiddleName() const {
    return middleName;
}

const string &Patient::getLastName() const {
    return lastName;
}

const string &Patient::getSuffix() const {
    return suffix;
}

const string &Patient::getDoctor() const {
    return doctor;
}

bool Patient::isTreated() const {
    return treated;
}

int Patient::getPriority() const {
    return priority;
}

void Patient::setFirstname(const string &firstname) {
    Patient::firstname = firstname;
}

void Patient::setMiddleName(const string &middleName) {
    Patient::middleName = middleName;
}

void Patient::setLastName(const string &lastName) {
    Patient::lastName = lastName;
}

void Patient::setSuffix(const string &suffix) {
    Patient::suffix = suffix;
}

void Patient::setDoctor(const string &doctor) {
    Patient::doctor = doctor;
}

void Patient::setTreated(bool treated) {
    Patient::treated = treated;
}

void Patient::setPriority(int priority) {
    Patient::priority = priority;
}

vector<string> Patient::getAilments() const {
    return ailments;
}
void Patient::setAilements(const vector<string> &ailment) {
    ailments.clear();
    for(int i =0; i< ailment.size();i++){
        ailments.push_back(ailment[i]);
    }
}