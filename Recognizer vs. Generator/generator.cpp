#include<iostream>
#include<string>
#include<cstdlib>
#include "queue.h"
using namespace std;
// include queue.h or equivalent such as <queue>

//----------------------------------------------
// CS421 HW1 
// Write a generator in C++ for L = {x | x is a binary number}.
// Your name: Tyler Cochran
//----------------------------------------------

// Copy the recognizer function here from the other file.
bool recognizer(string s)
{
  for(int counter = 0; counter < s.size(); counter++)//cycle through user string
    {
      if(s[counter] != '0' && s[counter] != '1')
	return false;
    }
  return true;
}


// main: It should create each string over E = {0,1,2} systematically
//   (short to long) and pass each string to the recognizer function
//   created in Part a).  Hint: use a queue to generate strings
//   Only those strings for which the recognizer returned TRUE
//   should be displayed. 
//   Keeps on going until the queue overflows but the user can 
//   terminate the program with control-C 
//   after about 20 strings have been displayed.
int main()
{
  queue stringQueue;
  int in;//input
  int genCount;//amount of num gen
  bool result = false;//check if input is binary
  stringQueue.add("0");
  stringQueue.add("1");
  stringQueue.add("2");
  cout << "enter 1 to start the generator: " << endl;
  cin >> in;
  if(in != 1)
    {
      cout << " ending program " << endl;
      exit(1);
    }
  
  while(in = 1)
    {
        try
	  {
	    string temp;//local temp var
	    stringQueue.remove(temp);
	    result = recognizer(temp);
	    if(result==true)//while number is binary
	      {
		cout << temp << endl;
		genCount++;
		if(genCount >=20)//print 20 strings
		  {
		    cout << "at least 20 binary nums have been generated, enter 1 to continue: " << endl;
		    cin >> in;
		    if(cin.fail())
		      in=0;
		  }
	      }
	    stringQueue.add(temp + '0');
	    stringQueue.add(temp + '1');
	    stringQueue.add(temp + '2');
	  }
	catch(queue::Overflow)//error after overflow
	  {
	    cerr << "error: overflow too many items in queue" << endl; 
	    exit(1);
	  }
	catch(queue::Underflow)//error when empty
	  {
	    cerr << "error underflow no items in queue" << endl; 
	    exit(1);
	  }
	catch(char const* errorcode)
	  {
	    cerr << "error: " << errorcode << endl;
	    exit(1);
	  }

    }// end of while
  
}// end of main
