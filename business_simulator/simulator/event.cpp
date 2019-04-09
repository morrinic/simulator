//
//  event.cpp
//  simulator
//
//  Created by Nicole Morris on 4/2/19.
//  Copyright © 2019 Nicole Morris. All rights reserved.
//

#include "event.hpp"
#include <iostream>

Customer::Customer(int business_arrival_time, int service_time_needed){
    
    business_arrival_time_ = business_arrival_time;
    service_time_needed_ = service_time_needed;
    line_arrival_time_ = 0;
    left_time_ = 0;
    total_time_in_bank_ = 0;
    
}

bool Customer::addToLine(int line_arrival_time){
    
    
    if(line_arrival_time == 200){
        return false;
    }

    if(line_arrival_time < business_arrival_time_){
        line_arrival_time_ = business_arrival_time_;
    } else {
        line_arrival_time_ = line_arrival_time;
    }

    left_time_ = line_arrival_time_ + service_time_needed_;
    
    //12 hours of events = 43200 seconds
    if(left_time_ > total_seconds){
        left_time_ = total_seconds;
    }
    
    total_time_in_bank_ = left_time_ - business_arrival_time_;
    
    return true;
}

// Overloaded <
bool Customer::operator<(const Customer& rhs) const {
    return rhs.business_arrival_time_< business_arrival_time_;
}

int Customer::getStoreArrivalTime(){
    return business_arrival_time_;
}

int Customer::getServiceTime(){
    return service_time_needed_;
}

int Customer::getLineArrivalTime(){
    return line_arrival_time_;
}

int Customer::getLeftTime(){
    return left_time_;
}

int Customer::getTotalTime(){
    return total_time_in_bank_;
}
