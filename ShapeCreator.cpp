#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//Shape Creator
//Square: length and width based on rows & columns of the character
//Triangle: sides based on total of a side characters (including blank spaces between columns)
//Diamond: sides based on total of a side characters (including blank spaces between columns)
int main(){
    ofstream outFile("C:\\Users\\99210\\Documents\\GitHub\\Shape-Creator\\ShapeCreator.txt");
    if (outFile.is_open()){
        bool cont = true;
        while (cont == true){
            char character;
            int size;
            char shape;
            //asks for desired shape
            cout << "Please input the shape you want out of the following: s = square, t = triangle, d = diamond, o = other.\n";
            cin >> shape;
            //identifies shape
            if (shape == 's'){ //square
                cout << "You have selected: Square\nPlease input the character used to make up the square and the size.\n";
                cin >> character;
                cin >> size;
                if (size > 0){
                    for (int j = 1; j <= size; j++){
                        for (int i = 1; i <= size; i++){
                            outFile << character << setw(3);
                        }
                        outFile << "\n";
                    }
                } else cout << "Invalid input for size.";
            } else if (shape == 't'){ //triangle
                char option;
                //specifies triangle type
                cout << "You have selected: Triangle\nPlease input one of the following: e = equilateral, r = right\n";
                cin >> option;
                //identifies type
                if (option == 'e'){ //equilateral
                    cout << "Please select the character that will make up the shape, and the size of a side, separated by spaces.\n";
                    cin >> character;
                    cin >> size;
                    outFile << setw(1+size*.5) << character << endl;
                    for (int i = 1; i <= (size*.433); i++){ //.433 is the rough estimate of amount of rows based on height and space between rows (.866/2)
                        outFile << setw(1+size*.5-i) << character;
                        outFile << setw(2*i) << character << endl;
                    }
                    for (int i = 1; i <= size; i++){
                        outFile << character;
                    }
                    outFile << endl;
                } else if (option == 'r'){
                    int height;
                    cout << "Please select the character that will make up the shape, and the length of the base, and the height, separated by spaces.\n";
                    cin >> character;
                    cin >> size;
                    cin >> height;
                    outFile << character << endl;
                    for (int i = 1; i <= (height/2.5); i++){ //rough estimate to help with space between rows(not applied in square creator)
                        outFile << character;
                        outFile << setw(i*1.5) << character << endl;
                    }
                    for (int i = 1; i <= size; i++){
                        outFile << character;
                    }
                    outFile << endl;
                } else {
                    cout << "Invalid input.";
                } 
            } else if (shape == 'd'){
                cout << "Please select the character that will make up the shape, and the size of a side, separated by spaces. (Diamond works best with larger numbers)\n";
                    cin >> character;
                    cin >> size;
                    outFile << setw(1+size*.5) << character << endl;
                    for (int i = 1; i <= (size*.433); i++){ //.433 is the rough estimate of amount of rows based on height and space between rows (.866/2)
                        outFile << setw(1+size*.5-i) << character;
                        outFile << setw(2*i) << character << endl;
                    }
                    for (int i = (size*.43); i >= 1; i--){
                        outFile << setw(1+size*.5-i) << character;
                        outFile << setw(2*i) << character << endl;
                    }
                    outFile << setw(1+size*.5) << character << endl;
                    outFile << endl;
            }
            outFile << endl;
            char another;
            cout << "Would you like to print another shape? (y/n)\n";
            cin >> another;
            if (another == 'n'){
                cont = false;
            }
        }
    } else cout << "File is not open.";
    outFile.close();

    //Confirms file output
    string line;
    ifstream inFile("C:\\Users\\99210\\Documents\\GitHub\\Shape-Creator\\ShapeCreator.txt");
    cout<<"\nReading from \"C:\\Users\\99210\\Documents\\GitHub\\Shape-Creator\\ShapeCreator.txt\"\nYou have created the following shapes:" << endl;
    if(inFile.is_open()){
        while(getline(inFile, line)){ //reads line by line
            cout << line << endl;
        }
        inFile.close();
    } else{
        cout << "Unable to open file for reading" << endl;
    }
}