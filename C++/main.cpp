#include <iostream>
#include <string> //for string operations

using namespace std;

int main(){
    //This is my learning c++ documentation

    //BASICS

    /*
    Datatypes:
    int ... 123 or -123
    double ... 19.99 or -19.99
    char ... 'C'  (stored in single brackets)
    string ... "string" (stored in double brackets)
    bool ... true or false (the same as 1 and 0)
    */
   string test_char = "test"; //datatype string doesn't get syntax highlight

    // cout << "string " << 1 << endl;
    // printf("string %d \n",1); // Has the same output as cout but
    // is shorter if combining different datatypes

    const int number_1 = 1; // number_1 will always be 1 (read only)
    
    /*Logical Operators:
    && ... and
    || ... or
    ! ... not
    */

   //structs are used to group variables of different datatypes together
   struct {
    int num;
    string name;
   } _struct_name1, _struct_name2; // Structure variable

    _struct_name1.num = 10; //access structs variables

    _struct_name2.name = "chris"; //changing this variable will not effect _struct_name1

    // When the struct name is used right after struct it creates a datatype with the structname
    // Every Variable now assigned with the structname will become a struct

    struct car{
        int year;
        string model;
    };
    
    car Ford;
    
    Ford.year = 2007;
    Ford.model = "galaxy";

    //references & pointers:
    int value = 10;                     // value = 10
    int &value_memory_address = value; //&value_memory_address = 0x802edff73c
    int* pointer = &value_memory_address; //pointer = 0x802edff73c *pointer = 10

}

// FUNCTIONS

int function(){ //int functions do have a return value
    cout << "This function works!";
    return 0;
}

void output(){ //void functions do not have a return value
    cout << "This got output with a void funtion!";
}

// references are used to modify multiple values
void swapNums(int &x, int &y) {
  int z = x;
  x = y;
  y = z;
}


//OOP

class stepper{
    public:
        int speed;
        bool rotate_cw;

        //method defined inside of class
        void turn(bool direction, int speed){
            cout << "turning";
        }
};

//method defined outside of class

void stepper::turn(bool direction, int speed){
    cout << "turning";
}

