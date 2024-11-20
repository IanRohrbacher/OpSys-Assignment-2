// Ian Rohrbacher
// Operating Systems
// Programming Assignment #2
// 11/22/2024

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Process {
    int processNum;
    std::vector<int> resource;
    std::vector<int> maxResource;
};

int n; // number of processes
int m; // the number of resource types
std::vector<int> availableResource; // the amount of total resources for each m



void printOut(std::vector<Process> s) {
  std::cout << "n:" << n << " | m:" << m << " | Available Resources:{";
  for(int i=0; i<m; i++) {
    std::cout << availableResource.at(i) << ((i==(m-1)) ? "" : ", ");
  }
  std::cout << "} |\n";
  for(int i=0; i<n; i++) {
    std::cout << "P" << s.at(i).processNum << " | Allocation:{";
    for(int j=0; j<m; j++) {
      std::cout << s.at(i).resource.at(j) << ((j==(m-1)) ? "" : ", ");
    }
    std::cout << "} | Max:{";
    for(int j=0; j<m; j++) {
      std::cout << s.at(i).maxResource.at(j) << ((j==(m-1)) ? "" : ", ");
    }
    std::cout << "} |\n";
  }
}

std::vector<Process> createSystem(std::string s){
  // get input.txt file and store it in a string
  std::string stringFile = "";
  std::ifstream file(s);
  if (!file.is_open()) {
		std::cout << "Unable To Open File\n";
    std::vector<Process> empty;
    return empty;
	}
	else {
		char ch;
		file.get(ch);
		while (!file.eof()) {
			stringFile += ch;
			file.get(ch);
		}
	}
  file.close();
  //std::cout << stringFile << '\n';
  
  // using the stringFile, parse the data into the following variables
  std::string tempS = stringFile.substr(stringFile.find("n=")+2, stringFile.find("m=")-stringFile.find("n=")-3);
  n = std::stoi(tempS);
  
  tempS = stringFile.substr(stringFile.find("m=")+2, stringFile.find("availableResource=")-stringFile.find("m=")-3);
  m = std::stoi(tempS);
  
  tempS = stringFile.substr(stringFile.find("availableResource=")+19, stringFile.find("allocation0=")-stringFile.find("availableResource=")-21);
  availableResource.clear();
  for(int i=0; i<m; i++) {
    availableResource.push_back(std::stoi(tempS.substr(0, tempS.find(','))));
    tempS = tempS.substr(tempS.find(',')+1);
  }

  int processCount = 0; // to keep track of the amount of processes created
  std::vector<Process> finalSystem;
  // Creates a List of n Processes
  for(int i=0; i<n; i++) {
    Process tempP;
    std::string tempSA = "";
    std::string tempSM = "";
    tempP.processNum = processCount++;
    
    tempSA = stringFile.substr(stringFile.find("allocation"+std::to_string(i)+"=")+13, stringFile.find("maxAllocation"+std::to_string(i)+"=")-stringFile.find("allocation"+std::to_string(i)+"=")-15);
    for(int j=0; j<m; j++) {
      int tempI = std::stoi(tempSA.substr(0, tempSA.find(',')));
      availableResource.at(j) -= tempI;
      tempP.resource.push_back(tempI);
      tempSA = tempSA.substr(tempSA.find(',')+1);
    }

    tempSM = stringFile.substr(stringFile.find("maxAllocation"+std::to_string(i)+"=")+16, stringFile.find("allocation"+std::to_string(i+1)+"=")-stringFile.find("maxAllocation"+std::to_string(i)+"=")-18);
    for(int j=0; j<m; j++) {
      tempP.maxResource.push_back(std::stoi(tempSM.substr(0, tempSM.find(','))));
      tempSM = tempSM.substr(tempSM.find(',')+1);
    }

    finalSystem.push_back(tempP);
  }

  return finalSystem;
}

bool canFinish(Process p) {
    bool result = ((p.resource.at(0)+availableResource.at(0)) >= p.maxResource.at(0));
    for(int i=1; i<(m); i++) {
        result = result && ((p.resource.at(i)+availableResource.at(i)) >= p.maxResource.at(i));
    }
    return result;
}

void remove(Process p) {
    for(int i=0; i<m; i++) {
        availableResource.at(i) += p.resource.at(i);
        p.resource.at(i) = 0;
    }
}

void findSafe(std::vector<Process> &system) {
  std::vector<bool> flag(n, true);
  std::vector<int> order(n, -1);
  int orderplace = 0;
  bool running = true;
  bool endEarly = true;
  while(running && endEarly) {
    endEarly = false;
    // Check Each Value And Sorts The Order Of Execution
    for(int i=0; i<n; i++) {
      if(flag.at(i) && canFinish(system.at(i))) {
        endEarly = true;
        flag.at(i) = false;
        order[orderplace++] = i;
        remove(system.at(i));
      }
    }

    // Check If Order Is Full And Stop Loop
    bool breakLoop = true;
    for(int i=0; i<n; i++){
      if(order.at(i) == -1) {
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
      std::cout << "P" << order.at(i) << ((i!=(n-1)) ? " -> " : "");
    }
    std::cout << std::endl;
  } else {
    std::cout << "This System Is Not In A Safe State!\n";
  }
}


int main(int argc, char* argv[]) {
  std::vector<std::string> input;
  
  for(int i=1; i<argc; i++) {
    input.push_back(argv[i]);
  }
  
  for (std::string s : input) {
    std::vector<Process> system = createSystem("input/"+s);
    printOut(system);
    findSafe(system);
  }
  
  return 0;
}

/*
Following is the SAFE Sequence
P1 -> P3 -> P4 -> P0 -> P2
*/