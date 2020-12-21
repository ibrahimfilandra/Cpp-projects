/*
Program where the user writes some text inside a "book" and the index of all terms entered is created
*/
#include <iostream>
#include <utility>
#include <set>
#include <tuple>
#include <map>
#include <vector>
#include <string>

typedef std::map<std::string, std::vector<std::string>>Book;
typedef std::map<std::string, std::set<std::tuple<std::string,int,int>>> Index;

bool LetterOrNumber(char a) { if((a>='A' && a<='Z')|| (a>='a' && a<='z')|| (a>='0'&&a<='9') )return true;return false; }
std::string ToLowercase(std::string word) {for(int i=0;i<word.size();i++) if(word[i]>='A' && word[i]<='Z')word[i]+=32;return word;}
Index CreateIndexOfTerms(Book book) {
    
    for(auto it=book.begin();it!=book.end();it++) {
        for(int i=0;i<it->second.size();i++) {
            it->second[i]=ToLowercase(it->second[i]);
        }
    }
    
   Index index;
   for(auto it=book.begin();it!=book.end();it++) { //through the map, it->second is vector
       
       for(int i=0;i<it->second.size();i++) {  //through the vector of strings
           
            for(int j=0;j<it->second[i].size();j++) {
                while(j<it->second[i].size() && !LetterOrNumber(it->second[i][j]))j++;
                int k=j;
                while(k<it->second[i].size() && LetterOrNumber(it->second[i][k]))k++;
                if(!index.count( it->second[i].substr(j,k-j)) ) {   //if no words up to now
                    std::set<std::tuple<std::string,int,int>> tempset;
                    for(auto it2=it;it2!=book.end();it2++) {
                        
                        int l;
                        if(it2==it)l=i;else l=0;
                        for(;l<it2->second.size();l++) {
                            int o; if(l==i)o=j; else o=0;
                            for(;o<it2->second[l].size();o++) {
                                while(o<it2->second[l].size() && !LetterOrNumber(it2->second[l][o]))o++;
                                int p=o;
                                while(p<it2->second[l].size() && LetterOrNumber(it2->second[l][p]))p++;
                                if(ToLowercase(it2->second[l].substr(o,p-o))==it->second[i].substr(j,k-j)){
                                    tempset.insert(std::make_tuple(it2->first,l+1,o));
                                }
                                o=p;
                            }
                            
                        }
                        
                    }
                   
                    index.insert(std::make_pair( it->second[i].substr(j,k-j),tempset) );
                }
             j=k;   
            }
       }
       
   }
   
    return index;
}

std::set<std::tuple<std::string,int,int>> SearchIndexOfTerms(std::string word, Index index) {
    word=ToLowercase(word);
    if(!index.count(word)) throw std::logic_error ("Term not found");
    return index[word];
}

void PrintIndexOfTerms (Index index) {
    for(auto it=index.begin();it!=index.end();it++) {
        std::cout<<it->first<<": ";
        auto temp=it->second;
        int number=temp.size();int counter=0;
        for(auto it2=temp.begin();it2!=temp.end();it2++) {
            std::cout<<std::get<0>(*it2)<<"/"<<std::get<1>(*it2)<<"/"<<std::get<2>(*it2);
            if(counter!=number-1)std::cout<<", "; else std::cout<<std::endl;
            counter++;
        }
    } 
}

int main ()
{   
    
    Book book;
    while(1) {
    std::cout<<"Enter the name of the chapter: ";
    std::string chapter;std::getline(std::cin,chapter);
    if(chapter.size()==1 && chapter[0]=='.')break;
    std::vector<std::string>vektor;
    int pagenumber=0;
    while(1) {
        std::cout<<"Enter the content of the page "<<pagenumber+1<<": ";
        std::string page;
        std::getline(std::cin,page);
        if(page.size()==1 && page[0]=='.') break;
        vektor.push_back(page);
        pagenumber++;
    }
     book.insert(std::make_pair(chapter,vektor));   
    }
    std::cout<<std::endl;
    std::cout<<"Created index of terms: "<<std::endl;
    Index index=CreateIndexOfTerms(book);
    PrintIndexOfTerms(index);
    std::cout<<std::endl;
    while(1) {
        try {
        std::cout<<"Insert word: ";
        std::string word; std::getline(std::cin,word);
        if(word.size()==1 && word[0]=='.')break;
        if(SearchIndexOfTerms(word,index).size()!=0) {
        auto tempset=SearchIndexOfTerms(word,index);
        for(auto it=tempset.begin();it!=tempset.end();it++) {
            std::cout<<std::get<0>(*it)<<"/"<<std::get<1>(*it)<<"/"<<std::get<2>(*it)<<" ";
        } std::cout<<std::endl;
    }
        }
        catch(std::logic_error izuzetak) {std::cout<<"Entered word not found!"<<std::endl;}
    }
    
    
   
	return 0;
}
