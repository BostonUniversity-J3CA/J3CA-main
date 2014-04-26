#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

int hexToInt(string hex_string);

int main(int argc, char *argv[]){
  // argv[1] = filename to read from
  // argv[2] = line to read from
  // argv[3] = the type of data to return

  ifstream fs;
  string line;

  // For splitting the data by space
  int index = 0;
  string portion;
  string hex;
  int appc = 0;

  string option = argv[3];
  fs.open(argv[1]);
  if ( fs.good() ){
    int counter = 0;
    while ( getline(fs,line) ){
      if ( counter == atoi(argv[2]) ){
	int disp = 0;
	int n = 0;
	while ( (index = line.find(' ')) != string::npos ){
	  if ( disp > 20 ){
	    cerr << "Forced break" << endl;
	    break;
	  }
	  portion = line.substr(0,index);
	  if ( option == "--gps-status" ){
	    if ( n == 1 ){
	      cout << portion[0]-'0' << endl;
	      return portion[0]-'0';
	    }
	  }
	  else if ( option == "--flight-mode" ){
	    if ( n == 0 ){
	      cout << portion[0]-'0' << endl;
	      return portion[0]-'0';
	    }
	  }
	  else if ( option == "--longitude" ){
	    if ( n == 2 )
	      hex.append(portion);
	    else if ( n == 3 )
	      hex.append(portion);
	    else if ( n == 4 )
	      hex.append(portion);
	    else if ( n == 5 ){
	      hex.append(portion);
	      cout << hex << "->" << hexToInt(hex) << endl;
	      return hexToInt(hex);
	    }
	  }
	  else if ( option == "--latitude" ){
	    if ( n == 6 )
	      hex.append(portion);
	    else if ( n == 7 )
	      hex.append(portion);
	    else if ( n == 8 )
	      hex.append(portion);
	    else if ( n == 9 ){
	      hex.append(portion);
	      cout << hexToInt(hex) << endl;
	      return hexToInt(hex);
	    }
	  }
	  else if ( option == "--altitude" ){
	    if ( n == 10 )
	      hex.append(portion);
	    else if ( n == 11 )
	      hex.append(portion);
	    else if ( n == 12 )
	      hex.append(portion);
	    else if ( n == 13 ){
	      hex.append(portion);
	      cout << hex << endl;
	      return hexToInt(hex);
	    }
	  }
	  else {
	    cout << "Unknown command" << endl;
	    return -2;
	  }
	    
	  line = line.substr(index+1);
	  disp++;
	  n++;
	}
	break;
      }
      else 
	counter++;
    }
  }
  else {
    cout << "Failed to open file" << endl;
    return -2; // File does not exist
  }
  return -1;
}
int hexToInt(string hex){
  int sum  = 0;
  int expn = 0;
  int n    = 0;
  for (int i = hex.length()-1; i > -1; i--,expn++ ){
    switch(hex[i]){
    case 'a': 
      n = 10;
      break;
    case 'b':
      n = 11;
      break;
    case 'c':
      n = 12;
      break;
    case 'd':
      n = 13;
      break;
    case 'e':
      n = 14;
      break;
    case 'f':
      n = 15;
      break;
    default:
      n = hex[i]-'0';
    }
    sum += n*pow(16,expn);
  }
  return sum;
}
