#include<iostream>
#include<string>
using namespace std;

//-------------------------------------------------------
// CS421 HW1 
// Write a recognizer in C++ for L = {x | x is a binary number}.
// Your name: Tyler Cochran
//-------------------------------------------------------

//  The recognizer function should return TRUE or FALSE 
//  checking each character
//  to make sure it is 0 or 1. (leading 0's are allowed).
bool recognizer(string s)
{
  for(int counter =0; counter< s.size(); counter++)
    {
      if(s[counter] != '0' && s[counter] != '1')
	return false;
    }//end for loop
  return true;

}// end of recognizer

//main: Given a string (from E) cined from the user, pass it to
//      the recognizer function.
//      Cout "YES IN L" or "NO NOT IN L" depending on what was returned.
int main()
{
  string userinp;

  cout << "Please input a binary number" << endl;

  if(!getline(cin, userinp)) { return -1;}

  if(userinp.empty()){ cout << "nothing was inputted, ending program"; return 0;}

  bool result = recognizer(userinp);//send user input to recognizer to see if binary

  if(result==true)
    cout<< "YES IN L"<<endl;
  else 
    cout<<"NOT IN L"<<endl;

  return 0;

}// end of main
