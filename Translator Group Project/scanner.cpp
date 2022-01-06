#include<iostream>
#include<fstream>
#include<string>
#include <map>
using namespace std;

/* Look for all **'s and complete them */

//=====================================================
// File scanner.cpp written by: Group Number: **15 
//Anjelina, Ronalyn, and Tyler 
//=====================================================

// --------- Two DFAs ---------------------------------

// WORD DFA 
// Done by: anjelina v
// RE: (vowel | vowel n |bmknhprg vowel| bmknhprg vowel n| dwzyj vowel| dwzyj vowel n| bmknhprg y vowel| bmknhprg y vowel n| t vowel| t vowel n| t s vowel| t s vowel n| s vowel| s vowel n|s h vowel| s h vowel n| ch vowel| ch vowel n) ^+
bool word (string s)
{

  int state = 0;
  int charpos = 0;
  /* replace the following todo the word dfa  ** Prof. Krell notes given
  while (s[charpos] != '\0') 
    {
      if (state == 0 && s[charpos] == 'a')
      state = 1;
      else
      if (state == 1 && s[charpos] == 'b')
      state = 2;
      else
      if (state == 2 && s[charpos] == 'b')
      state = 2;
      else
	  return(false);
      charpos++;
    }//end of while

  // where did I end up????
  if (state == 2) return(true);  // end in a final state
   else return(false);
  */

  /* why I used case of if... both do them do the same thig I find switch statements allow
for cleaner/ nicer code. Swicth statements to me seem easier to use especially when comparing
multiple experssions like in this funcation.
Ronalyn, when checking this if you see anything wrong with my switch statemens let me know. THANK YOU!   
   */
  while (s[charpos] != '\0')
    {   //this is the start of q0
      if (state == 0){
	switch(s[charpos]) {
	case 'a': case 'e': case 'i': case 'o': case 'u': case 'I': case 'E':
	  state = 1; break;
	case 'd': case 'w': case 'z': case 'y': case 'j':
	  state = 2; break;
	case 'b': case 'm': case 'k': case 'n': case 'h': case 'p': case 'r': case 'g':
	  state = 6; break;
	case 't':
	  state = 3; break;
	case 's':
	  state = 4; break;
	case 'c':
	  state = 5;  break;
	default:
	  return false;
	}
      } // end q0
        
      // start switch of q0 q1
      else if (state == 1) {
	switch(s[charpos]) {
	case 'n':
	  state = 0; break;
	case 'a': case 'e': case 'i': case 'o': case 'u': case 'I': case 'E':
	  state = 1; break;
	case 'd': case 'w': case 'z': case 'y': case 'j':
	  state = 2; break;
	case 't':
	  state = 3; break;
	case 's':
	  state = 4; break;
	case 'c':
	  state = 5;  break;
	case 'b': case 'm': case 'k': case 'h': case 'p': case 'r': case 'g':
	  state = 6; break;
	default:
	  return false;
	}
      } // end switch q0 q1
        
      //(small) start switch qsa
      else if (state == 2) {
	switch(s[charpos]) {
	case 'a': case 'e': case 'i': case 'o': case 'u': case 'I': case 'E':
	  state = 1; break;
	default:
	  return false;
	}
      }//end of qsa switch
        
      // start of qt
      else  if (state == 3) {
	switch(s[charpos]) {
	case 'a': case 'e': case 'i': case 'o': case 'u': case 'I': case 'E':
	  state = 1; break;
	case 's':
	  state = 4; break;
	default:
	  return false;
	}
      } // end of qt switch

        //START of qs
      else if (state == 4) {
	switch(s[charpos]) {
	case 'a': case 'e': case 'i': case 'o': case 'u': case 'I': case 'E':
	  state = 1; break;
	case 'h':
	  state = 2; break;
	default:
	  return false;
	}
      }// end of qs switch

      //start of qc
      else if (state == 5) {
	switch(s[charpos]) {
	case 'a': case 'e': case 'i': case 'o': case 'u': case 'I': case 'E':
	  state = 1; break;
	case 'h':
	  state = 2; break;
	default:
	  return false;
	}
      } // end of switch qc

        //START OF qr
      else if (state == 6) {
	switch(s[charpos])
	  {
	  case 'a': case 'e': case 'i': case 'o': case 'u': case 'I': case 'E':
	    state = 1; break;
	  case 'y' : state = 2; break;
	  default:
	    return false;
	  }
      } // end of qr
        
      else {
	cout <<"STUCK"<<endl;
	return false;
      }
      charpos++;
    }//end of while

  // where did I end up????
  if (state == 0 || state == 1) return(true);  // end in a final state
  else return(false);
}


// PERIOD DFA 
// Done by: ANJLEINA V
bool period (string s)
{
  // complete this **
  if(s[0] == '.') return true;
  else return false;
}

// ------ Three  Tables -------------------------------------

// TABLES Done by: anjelina V 

// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, EOFM, etc.
//Ronalyn let me know if I missed anything I'vebeen looking at this for 
//too long. I feel like it should be correct.
enum tokentype {WORD1, WORD2, PERIOD, VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS, OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR, ERROR, EOFM};

// ** For the display names of tokens - must be in the same order as the tokentype.
string tokenName[30] = {"WORD1", "WORD2", "PERIOD", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR", "ERROR", "EOFM"}; 

// ** Need the reservedwords table to be set up here. 
// ** Do not require any file input for this. Hard code the table.
// ** a.out should work without any additional files.
//Hey Ronalyn let me know how you feel about what I did below.
//It is funcationing correcetly but I've been looking at this for so 
//long everything looks right

map<string,tokentype> reservedWords;
map<string,tokentype> :: iterator it;

void createMap(){
  reservedWords["masu"] = VERB;
  reservedWords["masen"] = VERBNEG;
  reservedWords["mashita"] = VERBPAST;
  reservedWords["masendeshita"] = VERBPASTNEG;
  reservedWords["desu"] = IS;
  reservedWords["deshita"] = WAS;
  reservedWords["o"] = OBJECT;
  reservedWords["wa"]=SUBJECT;
  reservedWords["ni"] = DESTINATION;
  reservedWords["watashi"] = PRONOUN;
  reservedWords["anata"]= PRONOUN;
  reservedWords["kare"]=PRONOUN;
  reservedWords["kanojo"]=PRONOUN;
  reservedWords["sore"]=PRONOUN;
  reservedWords["mata"]=CONNECTOR;
  reservedWords["soshite"]=CONNECTOR;
  reservedWords["shikashi"]=CONNECTOR;
  reservedWords["dakara"]=CONNECTOR;
  reservedWords["eofm"]=EOFM;
}

// ------------ Scanner and Driver ----------------------- 

ifstream fin;  // global stream for reading from the input file
string nextWord;
// Scanner processes only one word each time it is called
// Gives back the token type and the word itself

// ** Done by:ANJELIna V
int scanner(tokentype& tt, string& w)
{
  // ** Grab the next word from the file via fin
  // 1. If it is eofm, return right now.   

  /*  **
  2. Call the token functions (word and period) 
     one after another (if-then-else).
     Generate a lexical error message if both DFAs failed.
     Let the tokentype be ERROR in that case.

  3. If it was a word,
     check against the reservedwords list.
     If not reserved, tokentype is WORD1 or WORD2
     decided based on the last character.

  4. Return the token type & string  (pass by reference)
  */
    fin >> w;
    if(w == "eofm") return-1;

    if(word(w)) {
      it = reservedWords.find(w);

      if(it != reservedWords.end()){
	tt = it->second;
      }
      else if(w[w.length()-1] == 'I' || w[w.length()-1] == 'E') {
	tt = WORD2;
      }
      else {
	tt = WORD1;
      }
    }else if(period(w)) {
      tt =  PERIOD;
    } else {
      tt = ERROR;
      cout << "Lexical error: " << w << " is not a valid token" <<endl;
    }
    return 0;
}//the end of scanner


// The temporary test driver to just call the scanner repeatedly  
// This will go away after this assignment
// DO NOT CHANGE THIS!!!!!! 
// Done by:  Louis

int main()
{
  createMap();
  tokentype thetype;
  string theword; 
  string filename;

  cout << "Enter the input file name: ";
  cin >> filename;

  fin.open(filename.c_str());

  // the loop continues until eofm is returned.
   while (true)
    {
       scanner(thetype, theword);  // call the scanner which sets
                                   // the arguments  
       if (theword == "eofm") break;  // stop now

       cout << "Type is:" << tokenName[thetype] << endl;
       cout << "Word is:" << theword << endl;   
    }

   cout << "End of file is encountered." << endl;
   fin.close();

}// end
