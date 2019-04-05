//
//  main.cpp
//  simulator
//
//  Created by Nicole Morris on 4/1/19.
//  Copyright © 2019 Nicole Morris. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <iomanip>

#include "business.hpp"

int main(int argc, const char * argv[]) {
    
    std::cout << std::fixed << std::setprecision(2);
    
    //First, customer arrival rate in terms of customers per minute.
    double arrival_rate = atof(argv[1]);
    
    //The second parameter is maximum customer service time, measured in minutes.
    double max_service_time = atof(argv[2]);
    
    //The third parameter is a random number seed.
    int seed = atoi(argv[3]);
    
   std::cout << "Arrival rate = " << arrival_rate << "\n";
   std::cout << "Max service time = " << max_service_time << "\n";
   std::cout << "Seed = " << seed << "\n";

    //Run bank simulation
    srand(seed);
    Business bank;
    std::cout << "\nBank service times in minutes: \n";
    bank.runSimulation(1,arrival_rate,max_service_time,seed);
    
    //Run store simulation
    srand(seed);
    Business store;
   std::cout << "\nStore service times in minutes: \n";
   store.runSimulation(6,arrival_rate,max_service_time,seed);
    
    return 0;
}
