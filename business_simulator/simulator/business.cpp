//
//  business.cpp
//  simulator
//
//  Created by Nicole Morris on 4/1/19.
//  Copyright © 2019 Nicole Morris. All rights reserved.
//

#include "business.hpp"

#include <array>
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <iomanip>
#include <fstream>


static bool sort_using_less_than(Event u, Event v)
{
    return u.getTotalTime() < v.getTotalTime();
}

void Business::storeVariables(int lines, double arrival_time, double max_service_time, int seed){
    employees_ = 6;
    lines_ = lines;
    arrival_time_ = arrival_time;
    max_service_time_ = max_service_time;
    seed_ = seed;
}

void Business::populateEvents(){

    //12 hours of events = 43200 seconds
    for(int time = 0; time < 43200; time++){

        bool customer = (rand() / (double) RAND_MAX) < (arrival_time_ / 60);

        if(customer){
 
            //Convert max_service_time_ to seconds instead of minutes (60 seconds/minute)
            int seconds = max_service_time_ * 60;
            
            //Random time in at or below seconds below max service time
            int service_time = rand() % seconds + 1;
            
            //Add event to queue
            Event e = *new Event(time, service_time);
            arrival_events_queue.push(e);
            
        }
    }
    
}

int Business::findNextBankServicer(const std::vector<std::priority_queue<Event>>& servicers){
    
    //If employee 1 is not helping someone
    if(servicers.at(0).empty()){
        return 0;
    }
    
    Event first_servicer = servicers.at(0).top();
    int lowest_servicer = 0;
    int lowest_time = first_servicer.getLeftTime();
    for(int i = 1; i < servicers.size(); i++){
        
        if(servicers.at(i).empty()){
            return i;
        }
        
        Event next_servicer = servicers.at(i).top();
        int old_time = next_servicer.getLeftTime();
        if(old_time < lowest_time){
            lowest_time = old_time;
            lowest_servicer = i;
        }
            
    }

    return lowest_servicer;
}

int Business::findNextStoreServicer(const std::vector<std::vector<Event>>& servicers){
    
    //If employee 1 is not helping someone
    if(servicers.at(0).empty()){
        return 0;
    }
    
    long old_size = servicers.at(0).size() - 1;
    Event last_in_smallest_line = servicers.at(0).at(old_size);
    int smallest_line = 0;
    for(int i = 1; i < lines_; i++){
        
        if(servicers.at(i).empty()){
            return i;
        }
        
        long current_line_size = servicers.at(i).size()-1;
        Event last_in_current_line = servicers.at(i).at(current_line_size);
        if(last_in_current_line.getLeftTime() < last_in_smallest_line.getLeftTime()){
            smallest_line = i;
            last_in_smallest_line = last_in_current_line;
        }
        
    }
    
    return smallest_line;
    
}

void Business::runBank(){

    //Make servicers
    std::vector<std::priority_queue<Event>> servicers;
    for(int i = 0; i < employees_; i++){
        std::priority_queue<Event> servicer;
        servicers.push_back(servicer);
    }
    
    //Add people to servicer queue
    long customers = arrival_events_queue.size();
    for(int i = 0; i < customers; i++){

        Event event = arrival_events_queue.top();
        arrival_events_queue.pop();
        
        int next_servicer = findNextBankServicer(servicers);
        
        if(servicers.at(next_servicer).empty()){
            
            //Add to line details to event
            event.addToLine(event.getStoreArrivalTime());
            
            //Add new event to line
            servicers.at(next_servicer).push(event);
            
        } else {
            
            //Add to line details to event
            Event old = servicers.at(next_servicer).top();
            if(event.addToLine(old.getLeftTime())){

                //Remove old event from line
                servicers.at(next_servicer).pop();
            
                //Add new event to line
                servicers.at(next_servicer).push(event);
            
                //Save results
                results.push_back(event);

            }

        }
    }
    
    //Add last people in line to results
    for(int i = 0; i < servicers.size(); i++){
        if(!servicers.at(i).empty()){
            Event event = servicers.at(i).top();
            results.push_back(event);
        }
    }
    
}

void Business::runStore(){

    //Make servicers
    std::vector<std::vector<Event>> servicers;
    for(int i = 0; i < lines_; i++){
        std::vector<Event> line;
        servicers.push_back(line);
    }
    
    //Add people to servicer queue
    long customers = arrival_events_queue.size();
    for(int i = 0; i < customers; i++){
        
        Event event = arrival_events_queue.top();
        arrival_events_queue.pop();

        int next_servicer = findNextStoreServicer(servicers);
        
        if(servicers.at(next_servicer).empty()){
            
            //Add to line details to event
            event.addToLine(event.getStoreArrivalTime());
            
            //Add new event to line
            servicers.at(next_servicer).push_back(event);
            
        } else {
            
            //Add to line details to event
            long size = servicers.at(next_servicer).size()-1;
            Event old = servicers.at(next_servicer).at(size);
            if(event.addToLine(old.getLeftTime())){
                
                //Add new event to line
                servicers.at(next_servicer).push_back(event);
            
                //Save results
                results.push_back(event);

            }

        }
        
    }
    
    //Add last people in line to results
    for(int i = 0; i < servicers.size(); i++){
        if(servicers.at(i).size() != 0){
            long size = servicers.at(i).size();
            Event event = servicers.at(i).at(size-1);
            results.push_back(event);
        }
        
    }
    
}

void Business::runEvents(){
    
    if(lines_ == 1){
        runBank();
    } else {
        runStore();
    }

}

double Business::findResultsAverage(){
    
    double total = 0;
    for(int i = 0; i < results.size(); i++){
        total += results.at(i).getTotalTime();
    }
    double average = total/results.size();
    return average;
    
}

void Business::analyzeResults(){
    
    //Sort results
    std::sort(results.begin(), results.end(), sort_using_less_than);
    
    int tenth = 0.1 * results.size();
    int fiftieth = 0.5 * results.size();
    int ninetieth = 0.9 * results.size();
    
    std::cout << "10th percentile = " << results.at(tenth).getTotalTime() /60 << "\n";
    std::cout << "50th percentile = " << results.at(fiftieth).getTotalTime() /60  << "\n";
    std::cout << "90th percentile = " << results.at(ninetieth).getTotalTime() /60 << "\n";
    
    double average = findResultsAverage();
    std::cout << "Average service time = " << average / 60 << "\n";

}

void Business::updateFileData(){
    
    std::string file_name;
    if(lines_ == 1){
        file_name = "bank_results.txt";
    } else {
        file_name = "store_results.txt";
    }
    std::ofstream out(file_name, std::ios::app);
    out << results.at(0.9 * results.size()).getTotalTime() /60 << "\t" << max_service_time_ << "\t" << arrival_time_ << "\n";

}

void Business::runSimulation(int lines, double arrival_time, double max_service_time, int seed){
    
    storeVariables(lines, arrival_time, max_service_time, seed);
    populateEvents();
    runEvents();
    if(results.size() != 0){
        analyzeResults();
        updateFileData();
    } else {
        std::cout << "No customers\n";
    }
    
}
