#include <bits/stdc++.h>
using namespace std;

//Global Variables
int n,toempty,age;
int slots[10001];
string slotsRegistrationQuery = "Slot_number_for_car_with_number";
string slotsAgeQuery = "Slot_numbers_for_driver_of_age";
map<string,int> registrationToSlot;
map<int,string> slotToRegistration;
map<int,int> slotsToAge;
multimap<int,int> ageToSlots;

void intialize()
{
    registrationToSlot.clear();
    slotToRegistration.clear();
    ageToSlots.clear();
    slotsToAge.clear();
    ageToSlots.clear();
}

void extractSlots(string str)
{
    stringstream ss;
    ss << str;
    string temp;
    int found;
    while (!ss.eof()) {
        ss >> temp;
        if (stringstream(temp) >> found)
            n = found;
        temp = "";
    }
}
void extractEmptySlots(string str)
{
    stringstream ss;
    ss << str;
    string temp;
    int found;
    while (!ss.eof()) {
        ss >> temp;
        if (stringstream(temp) >> found)
            toempty = found;
        temp = "";
    }
}
void extractAge(string str)
{
    stringstream ss;
    ss << str;
    string temp;
    int found;
    while (!ss.eof()) {
        ss >> temp;
        if (stringstream(temp) >> found)
            age = found;
        temp = "";
    }
}
void parkVehicle(string str)
{
    string regPlate=""; // Assuming Registration plate will always be of format XX-XX-XX-XXXX
    bool parked = 0;
    int checkSpaceAndk = 0;
    int driverAge = stoi(str.substr(30,2));       //Assuming Age of Driver lies between 16 to 99

    //Finding Registration Number of Vehicle from Given input
    for(int i=1;i<str.length();i++)
    {
        if(checkSpaceAndk == 1)
        {
            if(str[i]==' ')
            {
                checkSpaceAndk = 0;
                break;
            }
            regPlate+=str[i];
        }
        else
        {
            if(str[i-1]=='k' && str[i]==' ')
                checkSpaceAndk = 1;
        }
    }
    for(int i=1;i<=n;i++)
    {
        if(slots[i]!=1)
        {
             cout<<"Car with vehicle registration number "<<"\""<<regPlate<<"\""<<" has been parked at slot number "<<i<<endl;
             slots[i]=1;
             parked=1;
             registrationToSlot[regPlate] = i;
             slotToRegistration[i] = regPlate;
             slotsToAge[i] = driverAge;
             ageToSlots.insert( {driverAge,i} );
             break;
        }
    }
    if(parked==0)
        cout<<"No Slots for Parking is available!"<<endl;
}
void getAgeBasedSlots(string str)
{
    int countSlots = 0;
    extractAge(str);
    for (auto itr = ageToSlots.begin(); itr != ageToSlots.end(); itr++)
    {
        if (itr -> first == age )
        {
            countSlots++;
            cout << itr->second <<" ";
        }
    }
    if(countSlots == 0)
    {
        cout << "The Parking does not contain any vehicle in any slot with given Driver Age"<<endl;
    }
    cout<<endl;
}
void getRegBasedSlots(string str)
{
    string regNumber="";
    int numberBegin = 0;
    for(int i=0;i<str.length();i++)
    {
        if(numberBegin == 1)
        {
            regNumber+=str[i];
        }
        else
        {
            if(str[i]==' ' && str[i-1]=='r')
            {
                numberBegin = 1;
            }
        }
    }
    if(registrationToSlot[regNumber]==0)
        cout<<"No Such Vehicle is present in the Parking lot"<<endl;
    else
        cout<<registrationToSlot[regNumber]<<endl;
}
void checkQuery(string str)
{
    int i = 0;
    int ageBased = 0, regBased = 0;
    while( i<str.length() )
    {
        if(str[i]!=slotsAgeQuery[i])
        {
            regBased = 1;
            break;
        }
        if(str[i]!=slotsRegistrationQuery[i])
        {
            ageBased = 1;
            break;
        }
        i++;
    }
    if(ageBased == 1)
    {
        getAgeBasedSlots(str);
    }
    if(regBased == 1)
    {
        getRegBasedSlots(str);
    }
}
void exitVehicle(string str)
{
    extractEmptySlots(str);
    if(slots[toempty]!=1)
        cout<<"Slot already vacant"<<endl;
    else
    {
        slots[toempty] = 0;
        int driverAge = slotsToAge[toempty];
        string vehicleNumber = slotToRegistration[toempty];
        //erase driverage,slots

        typedef multimap<int, int>::iterator iterator;

        pair<iterator, iterator> iterpair = ageToSlots.equal_range(driverAge);
        iterator it = iterpair.first;

        for (; it != iterpair.second; ++it)
        {
            if (it->second == toempty)
            {
                ageToSlots.erase(it);
                break;
            }
        }
        registrationToSlot[vehicleNumber]=0;
        cout<<"Slot number "<<toempty<<" vacated, the car with vehicle registration number "<<"\""<<vehicleNumber<<"\""<<" left the space, the driver of the car was of age "<<driverAge<<endl;
    }
}
int main()
{
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
	#endif
    string input;
    int inputCount = 0, inputCorrect = 0;
    intialize();
    while ( getline(cin,input))
    {
        if(inputCount==0)
        {
            if(input[0]=='C' || input[0]=='c')
            {
                extractSlots(input);
                printf("Created parking of %d slots\n",n);
                memset(slots,0,sizeof(slots));
                inputCount++;
                inputCorrect = 1;
            }
            else
            {
                printf("No Slots Created, Input File is not correct\n");
                inputCorrect = 0;
            }
        }

        else if(inputCount!=0 && (input[0]=='C' || input[0]=='c'))
            cout<<"Cannot Create more Parking lot, already created with "<<n<<" slots"<<endl;

        if(inputCorrect == 1)
        {
            if(input[0]=='P' || input[0]=='p')
            {
                parkVehicle(input);
            }

            if(input[0]=='L' || input[0]=='l')
            {
                exitVehicle(input);
            }
            if(input[0]=='S' || input[0]=='s')
            {
                checkQuery(input);
            }
            if(input[0]=='V' || input[0]=='v')
            {
                int tempCount = 0;
                extractAge(input);
                //cout<<age<<endl;
                for (auto itr = ageToSlots.begin(); itr != ageToSlots.end(); itr++)
                {
                    if (itr -> first == age )
                        tempCount++;
                }
                if(tempCount==0)
                    cout<<"null"<<endl;
                else
                {
                    //cout<<"All Vehicles Parked by drivers of age:"<<age<<endl;
                    for (auto itr = ageToSlots.begin(); itr != ageToSlots.end(); itr++)
                    {
                        if (itr -> first == age )
                        {
                            int position = itr -> second;
                            tempCount++;
                            cout<<slotToRegistration[position]<<endl;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

