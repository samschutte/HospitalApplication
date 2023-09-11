
#ifndef HospitalApp_compare
#define HospitalApp_compare

#include "Patient.h"


class compare{
public:
    bool operator() (const Patient &l, const Patient &r) const {
        return l.getPriority() > r.getPriority();
    }
};


#endif