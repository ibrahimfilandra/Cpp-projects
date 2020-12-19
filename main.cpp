/*
Program about linear interpolation which is done based on input points

*/

#include <iostream>
#include <functional>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <cmath>

std::function<double(double)> Linear_Interpolation(std::vector<std::pair<double,double>> pairs) {
    
      
    for(auto it=pairs.begin();it!=pairs.end();it++) {
        
        if(std::count_if(it,pairs.end(),[it] (std::pair<double,double>par){
           if(fabs(it->first-par.first)<0.000001)return true;
           return false;
       })>1) throw std::domain_error("Incorrect pairs");
    } 
    
    std::sort(pairs.begin(),pairs.end(), [] (std::pair<double,double> first_in_order, std::pair<double,double>second_in_order){
        return first_in_order.first<second_in_order.first;} );
        
    return [pairs] (double x) {
        
        if(x<pairs[0].first || x>pairs[pairs.size()-1].first) throw std::range_error("Argument out of bounds");
        auto smaller=pairs.begin();
        while(smaller!=pairs.end() && smaller->first<x)smaller++;
       if(smaller!=pairs.begin()) smaller--;
        auto bigger=pairs.begin();
        while(bigger!= pairs.end()&&bigger->first <x)bigger++;
            
            return smaller->second + (x-smaller->first)*(bigger->second - smaller->second)/(bigger->first - smaller->first);
    };
    
} 

std::function<double(double)>Linear_Interpolation(std::function<double(double)>f, double xmin, double xmax, double deltax){
    
    if(xmin>xmax || deltax<=0)throw std::domain_error("Incorrect parameters");
    std::vector<std::pair<double,double>> pairs;
    double x=xmin;
    while(x<=xmax){
        pairs.push_back(std::make_pair(x,f(x)));
        x+=deltax;
    }
   
    return Linear_Interpolation(pairs);
}


int main ()
{
    std::cout<<"Choose option (1 - insert pairs, 2 - approximation): ";
    int option; std::cin>>option;
   
   try{ 
    if(option==1) {
    std::cout<<"Insert number of pairs: ";
    int number_of_pairs; std::cin>>number_of_pairs;
    std::cout<<"Insert members of pairs x y: ";
    double x, y;
    std::vector<std::pair<double,double>>vektor;
    for(int i=0;i<number_of_pairs;i++) {
        std::cin>>x;
        std::cin>>y;
        vektor.push_back(std::make_pair(x,y));
    }
     while(1) {
         try {
            Linear_Interpolation(vektor)(1); //to throw exception before printing the text
    std::cout<<"Insert argument (or \"end\" for end): ";
    double argument;
    std::cin>>argument;
    if(!std::cin)return 0;
    std::cout<<"f("<<argument<<") = "<<Linear_Interpolation(vektor)(argument)<<std::endl;     
         }
            catch(std::range_error izuzetak) {
       std::cout<<izuzetak.what()<<std::endl;
   }
   catch(std::domain_error izuzetak) {
       throw;
   }
   
     }



    }
    if(option==2) {
        
    std::cout<<"Insert limits of the interval and the step: ";
    double xmin,xmax,deltax;
    std::cin>>xmin; std::cin>>xmax; std::cin>>deltax;
    while(1) {
        try{
    std::cout<<"Insert argument (or \"end\" for end): ";   
    double argument;
    std::cin>>argument;
    if(!std::cin)return 0;
    std::cout<<"f("<<argument<<") = "<<std::sin(argument)+argument*argument<<" fapprox("<<argument<<") = "<<Linear_Interpolation([](double x){return std::sin(x)+x*x;},xmin,xmax,deltax )(argument)<<std::endl;
        }
        catch(std::range_error izuzetak){
            std::cout<<izuzetak.what()<<std::endl;
        }
        catch(std::domain_error izuzetak) {
            throw;
        }
    }
        
    }
   }
    catch(std::domain_error izuzetak) {
        std::cout<<izuzetak.what();
    }
    

    
	return 0;
}
