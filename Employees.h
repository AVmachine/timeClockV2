class Employee {
  private:
    int index0ID;
    int index1ID;
    int index2ID;
    int index3ID;
    int index4ID;
    String fName;
    String lName;
    bool isManager;
  public:
    void setEmpID(int(*arr)[1][5]) {
      this->index0ID = (*arr)[0][0];
      this->index1ID = (*arr)[0][1];
      this->index2ID = (*arr)[0][2];
      this->index3ID = (*arr)[0][3];
      this->index4ID = (*arr)[0][4];
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
      if(pos == 0){
        return this->index0ID;
      }else if(pos == 1){
        return this->index1ID;
      }else if(pos == 2){
        return this->index2ID;
      }else if(pos == 3){
        return this->index3ID;
      }else if(pos == 4){
        return this->index4ID;
      }
    }
};
