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
    std::priority_queue<Customer> arrival;
    std::priority_queue<Customer> departure;
    std::vector<Customer> results;
    
    void storeVariables(int lines, double arrival_time, double max_service_time, int seed);
    void populateEvents();
    void runEvents();
    void runBank();
    void runStore();
    int findNextBankServicer(const std::vector<std::priority_queue<Customer>>& servicers);
    int findNextStoreServicer(const std::vector<std::vector<Customer>>& servicers);
    double findResultsAverage();
    //This function divides and prints the data into percentiles
    void analyzeResults();
    //Makes the information available in a text file for graphing purposes
    void updateFileData();
    
public:
    
    //If lines == 6 then the store simulation is run, otherwise bank simulator is run
    void runSimulation(int lines, double arrival_time, double max_service_time, int seed);

};
#endif /* business_hpp */
