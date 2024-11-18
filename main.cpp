// Ian Rohrbacher
// Operating Systems
// Programming Assignment #2
// 11/22/2024

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>



/**Global Variables */
const int n = 5; // number of processes
const int m = 3; // the number of resource types
int availableResource[m] = {10, 5, 7}; // the amount of total resources for each m
int processCount = 0; // to keep track of the amount of processes created

/**A Class Storing All Values For A Process To Run Banker’s Algorithm */
class Process {
  public:
    Process(int allocat[m], int max[m]) {
      processNum = processCount++;
      for(int i=0; i<m; i++) {
        resource[i] = tryAllocat(allocat[i], i);
        maxResource[i] = max[i];
      }
    };
    std::string printAllocation() const {
      std::string result = "Allocation";
      for(int i=0; i<m; i++) {
        result += " " + std::string(1, char('A'+i)) + ":" + std::to_string(resource[i]);
      }
      return result;
    };
    std::string printMax() const {
      std::string result = "Max";
      for(int i=0; i<m; i++) {
        result += " " + std::string(1, char('A'+i)) + ":" + std::to_string(maxResource[i]);
      }
      return result;
    };
    bool canFinish() {
      bool result = ((resource[0]+availableResource[0]) >= maxResource[0]);
      for(int i=1; i<(m); i++) {
        result = result && ((resource[i]+availableResource[i]) >= maxResource[i]);
      }
      return result;
    };
    void remove() {
      for(int i=0; i<m; i++) {
        availableResource[i] += resource[i];
        resource[i] = 0;
      }
    };
    friend std::ostream& operator<<(std::ostream& out, const Process& obj) {
        out << "| Process:" << obj.processNum << " | " << obj.printAllocation() << " | " << obj.printMax() << " | ";
        return out;
    };

  private:
    int processNum;
    int resource[m];
    int maxResource[m];

    int tryAllocat(int attempt, int i) {
      int temp = availableResource[i] - attempt;
      if(temp < 0){
        return -1;
      } else {
        availableResource[i] = temp;
        return attempt;
      }
    };
};



void available() {
  std::cout << "| Available A:" << std::to_string(availableResource[0]) << " B:" << std::to_string(availableResource[1]) << " C:" << std::to_string(availableResource[2]) << " |\n";
}

/**Shows The User What Was Created */
void printSystem(std::vector<Process> &system) {
  for(Process& processInstance : system){
    std::cout << processInstance << std::endl;
  }
  available();
}

/**Finds And Prints The Order The Processes Are Safe To Execute In Using Banker’s Algorithm */
void findSafe(std::vector<Process> &system) {
  bool flag[n] = {true, true, true, true, true};
  int order[n] = {-1, -1, -1, -1, -1};
  int orderplace = 0;
  bool running = true;
  bool endEarly = true;
  while(running && endEarly) {
    endEarly = false;
    // Check Each Value And Sorts The Order Of Execution
    for(int i=0; i<n; i++) {
      if(flag[i] && system[i].canFinish()) {
        endEarly = true;
        flag[i] = false;
        order[orderplace++] = i;
        system[i].remove();
      }
    }

    // Check If Order Is Full And Stop Loop
    bool breakLoop = true;
    for(int i=0; i<sizeof(order); i++){
      if(order[i] == -1) {
        breakLoop = false;
      }
    }
    if(breakLoop){
      running = false;
    }
  }

  // Prints the Result If A Order Exists Or Not
  if(endEarly) {
    std::cout << "This System Is In A Save State!\nThe Following Is The Safe Sequence\n";
    for(int i=0; i<n; i++) {
      std::cout << "P" << order[i] << ((i!=(n-1)) ? " -> " : "");
    }
    std::cout << std::endl;
  } else {
    std::cout << "This System Is Not In A Safe State!\n";
  }
}



int main() {
  // Shows The User The Starting Resource Instances
  std::cout << std::endl;
  available();

// SETUP ***********************************************************
  // Row = Process' Resources | Column 1 = Allocation Resources | Column 2 = Max Resources
  int processInit[n][2][m] = {
    {{0,1,0}, {7,5,3}},
    {{2,0,0}, {3,2,2}},
    {{3,0,2}, {9,0,2}}, 
    {{2,1,1}, {2,2,2}},
    {{0,0,2}, {4,3,3}}
  };

  // Creates a List of n Processes
  std::vector<Process> system;
  for(int i=0; i<n; i++) {
    system.push_back(Process(processInit[i][0], processInit[i][1]));
  }
// SETUP ***********************************************************

  printSystem(system);
  findSafe(system);

  return 0;
}

/*
Following is the SAFE Sequence
P1 -> P3 -> P4 -> P0 -> P2
*/