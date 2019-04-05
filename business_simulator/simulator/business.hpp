//
//  business.hpp
//  simulator
//
//  Created by Nicole Morris on 4/1/19.
//  Copyright © 2019 Nicole Morris. All rights reserved.
//

#ifndef business_hpp
#define business_hpp

#include "event.hpp"
#include <queue>
#include <stdio.h>
#include <string>
#include <vector>

class Business{
private:

    int employees_;
    int lines_;
    double arrival_time_;
    double max_service_time_;
    int seed_;
    std::priority_queue<Event> arrival_events_queue;
    std::priority_queue<Event> left_events_queue;
    std::vector<Event> results;
    
    void storeVariables(int lines, double arrival_time, double max_service_time, int seed);
    void populateEvents();
    void runEvents();
    void runBank();
    void runStore();
    int findNextBankServicer(const std::vector<std::priority_queue<Event>>& servicers);
    int findNextStoreServicer(const std::vector<std::vector<Event>>& servicers);
    double findResultsAverage();
    void analyzeResults();
    void updateFileData();
    
public:
    
    void runSimulation(int lines, double arrival_time, double max_service_time, int seed);

};
#endif /* business_hpp */
