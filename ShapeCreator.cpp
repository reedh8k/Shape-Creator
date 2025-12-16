#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//Shape Creator
int main(){
    ofstream outFile("C:\\Users\\99210\\ShapeCreator.txt");
    if (outFile.is_open()){
        bool cont = true;
        while (cont == true){
            char character;
            int size;
            char shape;
            cout << "Please input the shape you want out of the following: s = square, t = triangle, c = circle, o = other.\n";
            cin >> shape;
            if (shape == 's'){
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
            } else if (shape == 't'){
                char option;
                cout << "You have selected: Triangle\nPlease input one of the following: e = equilateral, i = isosceles\n";
                cin >> option;
                if (option == 'e'){
                    cout << "Please select the character that will make up the shape, and the size of a side, separated by spaces.\n";
                    cin >> character;
                    cin >> size;
                    outFile << setw(size/2) << character;
                    for (int i = 1; i < (size/))
                } /*else if (option == 'i'){

                } else {
                    cout << "Invalid input.";
                } */
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
}