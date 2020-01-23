#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

//I am Ilayda Ademoglu (23856) this is the second homework of cs204

struct NodeforDrivers{ //DRIVERS NODE
	string drivername; //This stores the drivers name
	int laptimes; //this stores the lap time
	NodeforDrivers *next;
};

void print(NodeforDrivers *head){ //PRINTS THE FINAL ORDER
	cout << "###############################" << endl;
	cout << "Results:" << endl;
	cout << "###############################" << endl;

	NodeforDrivers *ptr = head;
	int num = 1;
	while(ptr != NULL){
		cout << num << ". " << ptr->drivername << " " << ptr->laptimes << endl;
		ptr = ptr->next;
		num++;
	}
}

void deleteList(NodeforDrivers *head){ //THIS FUNCTION DELETES THE LIST AT THE END OF THE PROGRAM
	NodeforDrivers * temporary;
	 while (head != NULL) {				
      temporary = head->next;			
      delete head;
      head = temporary;
  }

}


int main(){
	ifstream input;
	string theFileName;
	NodeforDrivers *head = NULL;
	cout << "Please enter a file name. " << endl;
	cin >> theFileName;
	input.open(theFileName);
	if(input.is_open())
			cout << "Successfully opened file " << theFileName << endl;
	while(input.fail()){
		if(!input.is_open()){
			cout << "Unable to open file " << theFileName << endl;
		}
		cout << "Please enter a different file name." << endl;
		cin>> theFileName;
		input.open(theFileName);
		if(input.is_open()){
			cout << "Successfully opened file " << theFileName << endl;
		}
	}
	cout << endl;
	cout << "###############################" << endl;
	cout << "Qualifying Laps:" << endl;
	cout << "###############################" << endl;
	string tokenformula;
	while(getline(input,tokenformula)){
		string racername;
		int lapsec;
		int karsilastir;
		stringstream iss(tokenformula);
		while(iss >> racername >> lapsec){
			cout << racername << " completed the lap in " << lapsec << " milliseconds" << endl;
			karsilastir = lapsec;
			NodeforDrivers * temp = head;
			NodeforDrivers *prevtemp = NULL;
			bool findthename = false;
			bool changed = false;
			while(temp != NULL){ //CONTROL THE NAME EXIST 
				if(temp-> drivername != racername){
					prevtemp = temp;
					temp = temp-> next;
				}
				else if(temp-> drivername == racername){
					findthename = true;
					if(lapsec < temp->laptimes){ //PERSONAL BEST CHANGED BECAUSE ITS SMALL
						temp->laptimes = lapsec;
						changed = true;
						cout << racername << ": current personal best is " << lapsec;
					}
					else if(lapsec > temp->laptimes){ //NOT CHANGED THE PERSONAL BEST
						cout << racername << ": current personal best is " << temp->laptimes;
					}

					break;

				}
			}
			if(findthename == false){ //eger adi bulunamamissa node yarat ve sirala
				NodeforDrivers *ptr = head;
				if(head == NULL || lapsec < head->laptimes){
					NodeforDrivers *tmp = new NodeforDrivers;
					tmp-> drivername = racername; 
					tmp ->laptimes = lapsec;
					tmp->next = head;
					head = tmp;
				}
				else{
					while(ptr-> next != NULL && lapsec >= ptr->next->laptimes){
						ptr = ptr-> next;
					}
					NodeforDrivers *tempfor = new NodeforDrivers;
					tempfor-> drivername = racername;
					tempfor ->laptimes = lapsec;
					tempfor->next = ptr->next;
					ptr-> next = tempfor;
				}
				int num = 1; 
				NodeforDrivers * deneme = head;
				while(deneme != NULL && deneme->drivername != racername){
					num++;
					deneme = deneme->next;
				}
				cout << racername << ": current personal best is " << lapsec;
				cout << "; current position is " << num << endl;  
			}

			if(findthename == true){ //eger adi bulunmussa duzgun bi siraya sok tempi degistiriceksin head 1 elemanli olabilir veya daha fazla
				if(changed == true){
					NodeforDrivers *kopyaptr = head;
					NodeforDrivers *sil = head;
					NodeforDrivers * tempptr = temp; 
	
					bool icerigirdimi = false;

					if(head->drivername == racername){ //eger bastaysa basi degistir degilse silip yeni nod ekle 
						head->laptimes = lapsec;
						//cout << "current position is " << 1 << endl;
					}
					else if(head-> laptimes > lapsec && head->drivername != racername){ //en basa eklemek icin
						while(sil -> next != NULL){
							if(sil -> next== temp){
								sil->next=sil->next->next;
								delete temp;
								break;
							}
							sil = sil-> next;
						}
						NodeforDrivers *tmp = new NodeforDrivers;
						tmp-> drivername = racername; //bunlari constructora koy sonra
						tmp ->laptimes = lapsec;
						tmp->next = head;
						head = tmp;
					}
					else{ //ORTALARA EKLEMEK ICIN
						if(sil == head && sil->drivername == racername){
							head = head->next;
							delete temp;
						}
						else{
							while(sil -> next != NULL){
								if(sil -> next== temp){
									sil->next=sil->next->next;
									delete temp;
									break;
								}
								sil = sil-> next;
							}
						}
						kopyaptr = head;
						
						while(kopyaptr-> next != NULL && lapsec >= kopyaptr->next->laptimes){
							kopyaptr = kopyaptr-> next;
						}
						NodeforDrivers *tmp = new NodeforDrivers;
						tmp-> drivername = racername; 
						tmp ->laptimes = lapsec;
						NodeforDrivers * devams = kopyaptr->next;
						kopyaptr-> next = tmp;
						tmp->next = devams;
					}
					int num = 1; 
					NodeforDrivers * deneme = head;
					while(deneme != NULL && deneme->drivername != racername){
						num++;
						deneme = deneme->next;
					}
					cout << "; current position is " << num << endl;
				}
				if(changed == false){
					int num = 1;
					NodeforDrivers * deneme = head;
					while(deneme != NULL && deneme->drivername != racername){
						num++;
						deneme = deneme->next;
					}
					cout << "; current position is " << num << endl;
				}
			}
		}

	}
	cout << endl << endl;
	print(head);
	deleteList(head); //List is deleted 
}