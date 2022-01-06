#include<iostream>
#include<fstream>
#include<string>
#include "scanner.cpp"
#include <stdlib.h>
#include <vector>
using namespace std;

/* INSTRUCTION:  copy your parser.cpp here
      cp ../ParserFiles/parser.cpp .
   Then, insert or append its contents into this file and edit.
   Complete all ** parts.
*/

//=================================================
// File translator.cpp written by Group Number: 15
//=================================================

void sNonterm();
void afterSubjectNonterm();
void afterNounNonterm();
void afterObjectNonterm();
void nounNonterm();
void verbNonterm();
void beNonterm();
void tenseNonterm();

vector <string> wordJ;
vector <string> wordE;

string savedEword;

ofstream outFile;

string saved_lexeme;
tokentype saved_token;
bool token_available = false;

// ----- Additions to the parser.cpp ---------------------

// ** Declare Lexicon (i.e. dictionary) that will hold the content of lexicon.txt
// Make sure it is easy and fast to look up the translation.
// Do not change the format or content of lexicon.txt 
//  Done by: Tyler Cochran


// ** Additions to parser.cpp here:
//    getEword() - using the current saved_lexeme, look up the English word
//                 in Lexicon if it is there -- save the result   
//                 in saved_E_word
//  Done by: Tyler Cochran

void getEword()
{
  bool found = false;
  for(int a = 0; a < wordJ.size(); a++)
    {
      if(wordJ[a] == saved_lexeme)
	{
	  savedEword = wordE[a];
	  found = true;
	}
    }
  if(found == false)
    {
      savedEword = saved_lexeme;
    }
}

//    gen(line_type) - using the line type,
//                     sends a line of an IR to translated.txt
//                     (saved_E_word or saved_token is used)
//  Done by: Tyler Cochran

void gen(string line_type)
{
  if(line_type == "TENSE")
    {
      outFile << line_type << " " << tokenName[saved_token] << endl;
    }
  else
    {
      outFile << line_type << " " << savedEword << endl;
    }
}

// ----- Changes to the parser.cpp content ---------------------

// ** Comment update: Be sure to put the corresponding grammar 
//    rule with semantic routine calls
//    above each non-terminal function 

// ** Each non-terminal function should be calling
//    getEword and/or gen now.

//=================================================
// File parser.cpp written by Group Number: **15
//=================================================

// ----- Four Utility Functions and Globals -----------------------------------

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
//    to display syntax error messages as specified by me.


// Type of error: **Matching error
// Done by: **Ronalyn Castilla
void syntaxerror1(string lexeme, tokentype expected) {
  cout << "\nSYNTAX ERROR: expected " << tokenName[expected] << " but found " << lexeme << "\n";
  exit(1);
}
// Type of error: **Error in parser
// Done by: **Ronalyn Castilla
void syntaxerror2(string lexeme, string parserFunction) {
  cout << "\nSYNTAX ERROR: unexpected " << lexeme << " found in " << parserFunction << "\n";
  exit(1);
}

// ** Need the updated match and next_token with 2 global vars
// saved_token and saved_lexeme

// Purpose: **Save the token, the lexeme, and the flag if a token is available. Set the flag if there is a token available
// Done by: **Ronalyn Castilla
tokentype next_token() {
  if(!token_available) {
    //If token_available is false then eat a token on the scanner and save it
    scanner(saved_token, saved_lexeme);
    token_available = true;
  }
  //Return the saved token
  return saved_token;
}

// Purpose: **To match a given token type with the saved token
// Done by: **Ronalyn Castilla
bool match(tokentype expected) {
  //Check if there is not a match
  if(next_token() != expected)
    {
      //Matching error
      syntaxerror1(saved_lexeme, expected);
    }
  else
    {
      //If there is a match, eat the token on the scanner and print that there was a match
      token_available = false;
      cout << "Matched " << tokenName[expected] << "\n";
      return true;
    }
}

// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Be sure to put the name of the programmer above each function

// Grammar: **<noun> ::= WORD1 | PRONOUN
// Done by: **Ronalyn Castilla
// Updated by: Tyler Cochran
void nounNonterm() {
  cout << "Processing <noun>\n";
  switch(next_token())
    {
    case WORD1:
      match(WORD1);
      getEword();
      break;
    case PRONOUN:
      match(PRONOUN);
      getEword();
      break;
    default:
      syntaxerror2(saved_lexeme, "noun");
    }
}

// Grammar: **<verb> ::= WORD2
// Done by: **Ronalyn Castilla
// Updated by Tyler Cochran
void verbNonterm() {
  cout << "Processing <verb>\n";
  switch(next_token())
    {
    case WORD2:
      match(WORD2);
      getEword();
      gen("ACTION");
      break;
    default:
      syntaxerror2(saved_lexeme, "verb");
    }
}

// Grammar: **<be> ::= IS | WAS
// Done by: **Ronalyn Castilla
// Updated by: Tyler Cochran
void beNonterm() {
  cout << "Processing <be>\n";
  gen("DESCRIPTION");
  switch(next_token())
    {
    case IS:
      match(IS);
      gen("TENSE");
      break;
    case WAS:
      match(WAS);
      gen("TENSE");
      break;
    default:
      syntaxerror2(saved_lexeme, "be");
    }
}

// Grammar: **<tense> ::= VERBPAST | VERBPASTNEG | VERB | VERBNEG
// Done by: **Ronalyn Castilla
// Updated by: Tyler Cochran
void tenseNonterm() {
  cout << "Processing <tense>\n";
  switch(next_token())
    {
    case VERBPAST:
      match(VERBPAST);
      gen("TENSE");
      break;
    case VERBPASTNEG:
      match(VERBPASTNEG);
      gen("TENSE");
      break;
    case VERB:
      match(VERB);
      gen("TENSE");
      break;
    case VERBNEG:
      match(VERBNEG);
      gen("TENSE");
      break;
    default:
      syntaxerror2(saved_lexeme, "tense");
    }
}

// Grammar: **<afterObject> ::= <verb> #getEword# #gen("ACTION")# <tense> #gen("TENSE")# PERIOD | <noun> #getEword# DESTINATION #gen("TO")# <verb> #getEword# #gen("ACTION")# <tense> #gen("TENSE")# PERIOD
// Done by: **Ronalyn Castilla
// Updated by: Tyler Cochran
void afterObjectNonterm() {
  cout << "Processing <afterObject>\n";
  switch(next_token())
    {
    case WORD2:
      verbNonterm();
      tenseNonterm();
      match(PERIOD);
      break;
    case WORD1:
      nounNonterm();
      match(DESTINATION);
      gen("TO");
      verbNonterm();
      tenseNonterm();
      match(PERIOD);
      break;
    case PRONOUN:
      nounNonterm();
      match(DESTINATION);
      gen("TO");
      verbNonterm();
      tenseNonterm();
      match(PERIOD);
      break;
    default:
      syntaxerror2(saved_lexeme, "afterObject");
    }
}

// Grammar: **<afterNoun> ::= <be> #gen("DESCRIPTION")# #gen("TENSE")# PERIOD | DESTINATION #gen("TO")# <verb> #getEword# #gen("ACTION") <tense> #gen("TENSE")# PERIOD | OBJECT #gen("OBJECT")# <afterObject>
// Done by: **Ronalyn Castilla
// Updated by: Tyler Cochran
void afterNounNonterm() {
  cout << "Processing <afterNoun>\n";
  switch(next_token())
    {
    case IS:
      beNonterm();
      match(PERIOD);
      break;
    case WAS:
      beNonterm();
      match(PERIOD);
      break;
    case DESTINATION:
      match(DESTINATION);
      gen("TO");
      verbNonterm();
      tenseNonterm();
      match(PERIOD);
      break;
    case OBJECT:
      match(OBJECT);
      gen("OBJECT");
      afterObjectNonterm();
      break;
    default:
      syntaxerror2(saved_lexeme, "afterNoun");
    }
}

// Grammar: **<afterSubject> ::= <verb> #getEword# #gen("ACTION")# <tense> #gen("TENSE")# PERIOD | <noun> #getEword# <afterNoun>
// Done by: **Ronalyn Castilla
// Updated by: Tyler Cochran
void afterSubjectNonterm() {
  cout << "Processing <afterSubject>\n";
  switch(next_token())
    {
    case WORD2:
      verbNonterm();
      tenseNonterm();
      match(PERIOD);
      break;
    case WORD1:
      nounNonterm();
      afterNounNonterm();
      break;
    case PRONOUN:
      nounNonterm();
      afterNounNonterm();
      break;
    default:
      syntaxerror2(saved_lexeme, "afterSubject");
    }
}

// Grammar: **<s> ::= [CONNECTOR #getEword# #gen("CONNECTOR")] <noun> #getEword# SUBJECT gen("ACTOR") <afterSubject>
// Done by: **Ronalyn Castilla
// Updated by: Tyler Cochran
void sNonterm() {
  next_token();
  if(saved_lexeme != "eofm")
    {
      cout << "Processing <s>\n";
    
      if(next_token() == CONNECTOR) {
	match(CONNECTOR);
	getEword();
	gen("CONNECTOR"); 
      }

      nounNonterm();
      match(SUBJECT);
      gen("ACTOR");
      afterSubjectNonterm();
    }
}

// Grammar: **<story> ::= <s> {<s>}
// Done by: **Ronalyn Castilla
void storyNonterm() {
  cout << "Processing <story>\n\n";
  sNonterm();
  while(true && (saved_lexeme != "eofm"))
    {
      outFile << endl;
      sNonterm();
    }      
  cout << "\nSuccessfully parsed <story>.\n";
}

// ---------------- Driver ---------------------------

// The final test driver to start the translator
// Done by:  Tyler Cochran
int main()
{
  //** opens the lexicon.txt file and reads it into Lexicon
  ifstream input;
  string tJ;
  string tE;
  input.open("lexicon.txt");
  cout << "Opening File" << endl;

  while(input)
    {
      input >> tJ;
      input >> tE;
      wordJ.push_back(tJ);
      wordE.push_back(tE);
    }

  //** closes lexicon.txt 
  input.close();

  //** opens the output file translated.txt
  outFile.open("translated.txt");

  string filename;
  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());

  createMap();

  //** calls the <story> to start parsing
  storyNonterm();

  //** closes the input file 
  fin.close();

  //** closes traslated.txt
  outFile.close();
}// end

//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions

