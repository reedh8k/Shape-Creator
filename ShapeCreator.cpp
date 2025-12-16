#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

//Shape Creator
//Square: length and width based on rows & columns of the character
//Triangle: sides based on total of a side characters (including blank spaces between columns)
int main(){
    ofstream outFile("C:\\Users\\99210\\Documents\\GitHub\\Shape-Creator\\ShapeCreator.txt");
    if (outFile.is_open()){
        bool cont = true;
        while (cont == true){
            char character;
            int size;
            char shape;
            //asks for desired shape
            cout << "Please input the shape you want out of the following: s = square, t = triangle, c = circle, o = other.\n";
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
                cout << "You have selected: Triangle\nPlease input one of the following: e = equilateral, i = isosceles\n";
                cin >> option;
                //identifies type
                if (option == 'e'){ //equilateral
                    cout << "Please select the character that will make up the shape, and the size of a side, separated by spaces.\n";
                    cin >> character;
                    cin >> size;
                    int height = size * 0.4;

// top point
for (int s = 0; s < size / 2; s++) {
    outFile << ' ';
}
outFile << character << '\n';

// sides
for (int r = 1; r < height; r++) {
    // left padding
    for (int s = 0; s < (size / 2 - r); s++) {
        outFile << ' ';
    }

    outFile << character;

    // inside spacing
    for (int s = 0; s < (2 * r - 1); s++) {
        outFile << ' ';
    }

    outFile << character << '\n';
}

// base
for (int i = 0; i < size; i++) {
    outFile << character;
}
outFile << '\n';

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