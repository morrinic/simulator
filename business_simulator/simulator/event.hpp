//
//  event.hpp
//  simulator
//
//  Created by Nicole Morris on 4/2/19.
//  Copyright © 2019 Nicole Morris. All rights reserved.
//

#ifndef event_hpp
#define event_hpp

#include <stdio.h>
class Event{
    
private:
    
    int business_arrival_time_;
    int service_time_needed_;
    int line;
    int line_arrival_time_;
    int left_time_;
    int total_time_in_bank_;
    
public:
    Event(int arrival_time, int service_time);
    int getStoreArrivalTime();
    int getServiceTime();
    int getLine();
    int getLineArrivalTime();
    int getLeftTime();
    int getTotalTime();
    bool addToLine(int line_arrival_time);
    bool operator<(const Event& rhs) const;
};

#endif /* event_hpp */
