/*
Program that is supposed to be used by university's administration for managing borrowing laptops to students.
Implements OOP principles.
*/
#include <iostream>
#include <string>
#include <stdexcept>
#include <map>

class Student
{
    int indexnumber;
    std::string academic_year, name_surname, address, telephone_number;
    bool TestOfIndex (int number) {
        if(number<=0)return false;
        int counter=0;
        while(number!=0) {
            number/=10;
            counter++;
        }
        if(counter==5)return true;
        return false;
    }

    bool TestOfYear (std::string year) {
        if(year.size()==0)return false;
        std::string niz[11]= {"1","2","3","1/B","2/B","3/B","1/M","2/M","1/D","2/D","3/D"};
        int i=0;
        for(; i<11; i++) {
            if(year==niz[i])break;
        }
        if(i!=11)return true;
        return false;
    }

    bool TestOfNumber(std::string number) {
        if(number.size()==0) return false;
        int i=0;
        if(number[i]>='0' && number[i]<='9') {
            while(i<number.size() && number[i]>='0' && number[i]<='9') {
                i++;
            }
            if(i!=number.size() && number[i]=='/') {
                i++;
                while(i<number.size() && number[i]>='0' && number[i]<='9') {
                    i++;
                }
                if(i!=number.size() && number[i]=='-') {
                    i++;
                    while(i<number.size() && number[i]>='0' && number[i]<='9') {
                        i++;
                    }
                    if(i!=number.size())return false;

                } else return false;
            } else return false;
        } else return false;

        return true;
    }
    
    std::string FixName(std::string name) {
        std::string temp=std::string();
       int i=0;
       while(i!=name.size()) {
       while(i<name.size() && name[i]==' '){
           i++;
       } int j=i;
       while(j<name.size() &&name[j]!=' ') {
           j++;
       }
        temp+=name.substr(i,j-i);
        if(j!=name.size()){
            int k=j; while(k<name.size() && name[k]==' ' )k++;
            
            if(k!=name.size())temp+=' ';
            
        }
        i=j;
        
    }
   return temp;
}

public:

    Student(int index, std::string year, std::string name, std::string address, std::string number);
    int GiveIndex() const {return indexnumber;}
    std::string ReturnNameSurname() const {return name_surname;}
    std::string ReturnAcademicYear() const {
        if(academic_year=="1")return"1/B";
        if(academic_year=="2")return"2/B";
        if(academic_year=="3")return"3/B";
        return academic_year;}
    std::string ReturnAddress() const {return address;}
    std::string ReturnPhone() const {return telephone_number;}
    void Ispisi () const {
        std::cout<<"Index number: "<<indexnumber<<std::endl;
        std::cout<<"Academic Year: "<<ReturnAcademicYear()<<std::endl;
        std::cout<<"Name and Surname: "<<name_surname<<std::endl;
        std::cout<<"Address: "<<address<<std::endl;
        std::cout<<"Telephone: "<<telephone_number<<std::endl;
    }
    

};

Student::Student(int index, std::string year, std::string name, std::string address1, std::string number)
{
    if(!TestOfIndex(index) || !TestOfYear(year) ||!TestOfNumber(number)) throw std::domain_error("Incorrect parameters");
    name =FixName(name);
     indexnumber=index; academic_year=year; name_surname=name; address=address1; telephone_number=number;
}

class Laptop {
  int ev_broj; std::string name, characteristics;
  Student *who_has_it;
  public: 
  Laptop(int number,std::string name, std::string characteristics):name(name),characteristics(characteristics),who_has_it(nullptr) {
      if(number<0)throw std::domain_error("Incorrect parameters");
      ev_broj=number;
  }
  int ReturnSerialNumber()const {return ev_broj;}
  std::string ReturnName() const {return name;}
  std::string ReturnCharacteristics() const {return characteristics;}
  void Borrow (Student & student) {
      if(who_has_it!=nullptr)throw std::domain_error("Laptop already borrowed");
      who_has_it=&student;
  }
  void ReturnLaptop() {if(who_has_it!=nullptr)who_has_it=nullptr;}
  bool IsItBorrowed() {if(who_has_it!=nullptr)return true; return false;}
  Student & ReturnWhoHasIt() {
      if(who_has_it==nullptr)throw std::domain_error("Laptop not borrowed");
      return *who_has_it;
  }
    Student* ReturnPtrWhoHasIt() {return who_has_it;}
    void Ispisi() const {
    std::cout<<"Serial number: "<<ev_broj<<std::endl;
    std::cout<<"Name: "<<name<<std::endl;
    std::cout<<"Characteristics: "<<characteristics<<std::endl;
}    
};


class Administration {
  std::map<int, Student*> map_students;
  std::map<int, Laptop*> map_laptops;
  public :
  Administration()=default;
  Administration (const Administration& admin);
  Administration(Administration && admin);
  Administration& operator=(const Administration& admin);
  Administration &operator=(Administration &&admin);    
  void RegisterNewStudent(int index, std::string year, std::string name, std::string address, std::string number);
  void RegisterNewLaptop(int number,std::string name, std::string characteristics);
  Student& FindStudent(int number) {
      auto it=map_students.find(number); if(it==map_students.end()) throw std::domain_error("Student not found"); else return *it->second;
  }
  Student FindStudent(int number) const{
      auto it=map_students.find(number); if(it==map_students.end()) throw std::domain_error("Student not found"); else return *it->second;
  }
  Laptop& FindLaptop(int number) {
      auto it=map_laptops.find(number); if(it==map_laptops.end()) throw std::domain_error("Laptop not found"); else return *it->second;
  }
  Laptop FindLaptop(int number) const{
      auto it=map_laptops.find(number); if(it==map_laptops.end()) throw std::domain_error("Laptop not found"); else return *it->second;
  }
  void ListAllStudents();
  void ListAllLaptops();
  void BorrowLaptop(int index, int evid);
  int FindFreeLaptop ();
  void BringLaptopBack(int evid);
  void ShowBorrowings();
  ~Administration();
  
};

Administration::Administration(const Administration& admin) {
    auto it=admin.map_students.begin();
    try {
    while(it!=admin.map_students.end()) {
        map_students.insert(std::make_pair(it->first,new Student(*it->second)));
        
        it++;
    }}
    catch(...) {
        auto it=map_students.begin();
        while(it!=map_students.end()){
            delete it->second;
            it++;
        }
        throw;
    }
    
}

Administration::Administration(Administration &&admin) {
    map_students=admin.map_students;
    map_laptops=admin.map_laptops;
    for(auto it=admin.map_students.begin();it!=admin.map_students.end();it++) {
        it->second=nullptr;
    }
    for(auto it=admin.map_laptops.begin();it!=admin.map_laptops.end();it++) {
        it->second=nullptr;
    }
}

Administration& Administration:: operator=(const Administration &admin) {
 
  for(auto it=map_students.begin();it!=map_students.end();it++) {
      delete it->second;
      it=map_students.erase(it);
  }
  for(auto it=map_laptops.begin();it!=map_laptops.end();it++){
      delete it->second;
      it=map_laptops.erase(it);
  }
  try {
  for(auto it=admin.map_students.begin();it!=admin.map_students.end();it++) {
     map_students.insert(std::make_pair(it->first,new Student(*it->second)));
  }}
  catch(...) {
      for(auto it=map_students.begin();it!=map_students.end();it++) {
          delete it->second;
      }
      throw;
  }
  
  try {
  for(auto it=admin.map_laptops.begin();it!=admin.map_laptops.end();it++) {
     map_laptops.insert(std::make_pair(it->first,new Laptop(*it->second)));
  }}
  catch(...) {
      for(auto it=map_laptops.begin();it!=map_laptops.end();it++) {
          delete it->second;
      }
      
  }
   return *this;
}

Administration& Administration::operator=( Administration&& admin) {
    
    map_laptops=std::move(admin.map_laptops);
    map_students=std::move(admin.map_students);
    
    return *this;
}

void Administration::RegisterNewStudent(int index, std::string year, std::string name, std::string address, std::string number) {
    auto it=map_students.find(index);
    if(it!=map_students.end())throw std::domain_error ("Student with that index number already exists");
    map_students.insert(std::make_pair(index,new Student( index,year, name, address,  number) ) ) ;
}

void Administration::RegisterNewLaptop(int number,std::string name, std::string characteristics) {
    auto it=map_laptops.find(number);
    if(it!=map_laptops.end())throw std::domain_error("Laptop with that serial number already exists");
    map_laptops.insert(std::make_pair(number,new Laptop(number,name,characteristics)));
}

void Administration::ListAllStudents() {
    for(auto it=map_students.begin();it!=map_students.end();it++) {
        it->second->Ispisi(); std::cout<<std::endl;
    }
}

void Administration::ListAllLaptops() {
    for(auto it=map_laptops.begin();it!=map_laptops.end();it++) {
        it->second->Ispisi();
        if(it->second->IsItBorrowed()) {
            auto pok2=it->second->ReturnPtrWhoHasIt();
            std::cout<<std::endl;std::cout<<"Borrowed to: "<<pok2->ReturnNameSurname()<<" ("<<pok2->GiveIndex()<<")"<<std::endl;
        }
    }
}

void Administration::BorrowLaptop(int index, int evid) {
    auto it=map_students.find(index);
    if(it==map_students.end())throw std::domain_error("Student not found");
    auto it2=map_laptops.find(evid);
    if(it2==map_laptops.end())throw std::domain_error("Laptop not found");
    if(it2->second->IsItBorrowed())throw std::domain_error("Laptop already borrowed");
    for(auto it2=map_laptops.begin();it2!=map_laptops.end();it2++) {
        auto pok2=it2->second->ReturnPtrWhoHasIt();
        if(pok2!=nullptr){
        if(pok2->ReturnAddress()==it->second->ReturnAddress() && 
        pok2->GiveIndex()==it->second->GiveIndex() && 
        pok2->ReturnAcademicYear()==it->second->ReturnAcademicYear() &&
        pok2->ReturnNameSurname()==it->second->ReturnNameSurname() && 
        pok2->ReturnPhone()==it->second->ReturnPhone()) throw std::domain_error("Student already borrowed a laptop");
        }
    }
    it2->second->Borrow(*it->second);
}

int Administration::FindFreeLaptop() {
    auto it=map_laptops.begin();
    for(;it!=map_laptops.end();it++){
        if(!it->second->IsItBorrowed())break;
    }
    if(it==map_laptops.end())throw std::domain_error("No available laptops");
    
    return it->second->ReturnSerialNumber();
}

void Administration::BringLaptopBack(int evid){
    auto it=map_laptops.begin(); 
    for(;it!=map_laptops.end();it++) {
        if(it->second->ReturnSerialNumber()==evid)break;
    }
  if(it==map_laptops.end())throw std::domain_error("Laptop not found");
  if(!it->second->IsItBorrowed()) throw std::domain_error("Laptop not borrowed");
  it->second->ReturnLaptop();
  
}

void Administration::ShowBorrowings() {
    auto it=map_laptops.begin(); int counter=0;
    for(;it!=map_laptops.end();it++) {
        auto pok=it->second->ReturnPtrWhoHasIt();
        if(pok!=nullptr) {
            std::cout<<"Student "<<pok->ReturnNameSurname()<<" ("<<pok->GiveIndex()<<") borrowed laptop number "<<it->second->ReturnSerialNumber()<<std::endl;
        }
        if(pok==nullptr)counter++;
    }
    if( counter==map_laptops.size() )std::cout<<"No borrowings"<<std::endl;
}

Administration::~Administration () {
    auto it=map_students.begin();
    for(;it!=map_students.end();it++) {
        delete it->second;
    }
    auto it2=map_laptops.begin();
    for(;it2!=map_laptops.end();it2++) {
        delete it2->second;
    }
    
}

int main ()
{
    Administration admin; int option=11;
    do{
    std::cout<<"Choose option or O for END: "<<std::endl;
    std::cout<<"1. Register a student"<<std::endl;
    std::cout<<"2. Register a laptop"<<std::endl;
    std::cout<<"3. Find student"<<std::endl;
    std::cout<<"4. Find laptop"<<std::endl;
    std::cout<<"5. List students"<<std::endl;
    std::cout<<"6. List laptops"<<std::endl;
    std::cout<<"7. Borrow laptop"<<std::endl;
    std::cout<<"8. Find free laptop"<<std::endl;
    std::cout<<"9. Bring laptop back"<<std::endl;
    std::cout<<"10. List all borrowings"<<std::endl;
     std::cin>>option; 
     std::cin.ignore(10000,'\n');
     if(option==1) {
         std::cout<<"Insert name and surname: "; std::string name_surname; std::getline(std::cin,name_surname); 
          std::cout<<"Insert telephone number: "; std::string telephone; std::getline(std::cin,telephone);
         std::cout<<"Insert address: "; std::string address; std::getline(std::cin, address); 
          std::cout<<"Insert academic year: "; std::string year; std::getline(std::cin,year);
         std::cout<<"Insert number of index: "; int number; std::cin>>number;
         admin.RegisterNewStudent(number, year, name_surname, address, telephone);
     }
     if(option==2) {
         std::cout<<"Insert number: "; int number; std::cin>>number; std::cin.ignore(10000,'\n');
         std::cout<<"Insert name: "; std::string name; std::getline(std::cin, name);
         std::cout<<"Insert characteristics: "; std::string characteristics; std::getline(std::cin, characteristics);
         admin.RegisterNewLaptop(number, name, characteristics);
     }
     if(option==3) {
         std::cout<<"Insert number of index: "; int number; std::cin>>number;
         Student s=admin.FindStudent(number);
         s.Ispisi();
     }
     if(option==4) {
         std::cout<<"Insert serial number: "; int number; std::cin>>number;
         Laptop p=admin.FindLaptop(number);
         p.Ispisi();
     }
     if(option ==5) {
         admin.ListAllStudents();
     }
     if(option==6){
         admin.ListAllLaptops();
     }
     if(option==7){
         std::cout<<"Insert index number of astudents: "; int br1; std::cin>>br1;
         std::cout<<"Insert serial number of a laptop: "; int br2; std::cin>>br2;
         admin.BorrowLaptop(br1,br2);
     }
     if(option==8){
         int number=admin.FindFreeLaptop();
         Laptop p=admin.FindLaptop(number);
         std::cout<<"First free is "; p.Ispisi();
     }
     if(option==9) {
         std::cout<<"Insert serial number: "; int number; std::cin>>number;
         admin.BringLaptopBack(number);
     }
     
     if(option==10) {
         admin.ShowBorrowings();
     }
     
    }while(option!=0);
    
    
    
    
    
    return 0;
}
