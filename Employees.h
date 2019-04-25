class Employee {
  private:
    int timeWorked;
    int givenID;
    int index0ID;
    int index1ID;
    int index2ID;
    int index3ID;
    int index4ID;
    String fName;
    String lName;
    bool isManager;
  public:
    Employee(){ 
    }
    Employee(String firstName,String lastName,bool isMng, int(*arr)[1][5],int givenID, int timeWrk){
      this->fName = firstName;
      this->lName = lastName;
      this->isManager = isMng;
      this->timeWorked = timeWrk;
      this->givenID = givenID;
      this->index0ID = (*arr)[givenID][0];
      this->index1ID = (*arr)[givenID][1];
      this->index2ID = (*arr)[givenID][2];
      this->index3ID = (*arr)[givenID][3];
      this->index4ID = (*arr)[givenID][4];
    }
    void setEmpID(int(*arr)[2][5]) {
      this->index0ID = (*arr)[this->givenID][0];
      this->index1ID = (*arr)[this->givenID][1];
      this->index2ID = (*arr)[this->givenID][2];
      this->index3ID = (*arr)[this->givenID][3];
      this->index4ID = (*arr)[this->givenID][4];
    }
    void setFirstName(String firstName = "John") {
      this->fName = firstName;
    }
    void setLastName(String lastName = "Doe") {
      this->lName = lastName;
    }
    void setIsManager(bool isMngr = false) {
      this->isManager = isMngr;
    }
    void setTimeWorked(int timeWrk){
      this->timeWorked =  this->timeWorked + timeWrk;
    }
    String getFirstName() {
      return this->fName;
    }
    String getLastName() {
      return this->lName;
    }
    bool getIsManager() {
      return this->isManager;
    }
    int getEmpID(int pos) {
      if (pos == 0) {
        return this->index0ID;
      } else if (pos == 1) {
        return this->index1ID;
      } else if (pos == 2) {
        return this->index2ID;
      } else if (pos == 3) {
        return this->index3ID;
      } else if (pos == 4) {
        return this->index4ID;
      }
    }
    int getGivenID(){
      return this->givenID;
    }
    int getTimeWorked(){
      return this->timeWorked;
    }
};
