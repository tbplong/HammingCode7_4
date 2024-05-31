#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

// Function to convert a character to its binary representation
string charToBinary(char c) {
    string binary;
    for (int i = 7; i >= 0; i--) {
        binary.push_back((c & (1 << i)) ? '1' : '0');
    }
    return binary;
}

// Function to convert a binary string to its decimal representation
int binaryToDecimal(const string& binary){
    int decimal = 0;
    for (int i = 0; i < binary.length(); i++) {
        decimal = decimal * 2 + (binary[i] - '0');
    }
    return decimal;
}

string setStringtoASCII(string str){
    int N = str.length();
    if (N % 8 != 0) {
        return "Not Possible!";
    }
    string res = "";
    for (int i = 0; i < N; i += 8) {
        int decimal_value
            = binaryToDecimal((str.substr(i, 8)));
        res += char(decimal_value);
    }
    return res;
}

void displayMatrix4(int matrix[][4], int length)
{
    for(int i = 0; i < length; i++)
    {
        cout << " ";
        for(int j = 0; j < 4; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void displayMatrix7(int matrix[][7], int length)
{
    for(int i = 0; i < length; i++)
    {
        cout << " ";
        for(int j = 0; j < 7; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

string converto(int matrix[][7], int length){
    string binary = "";
    string output;
    for(int i = 0; i < 7; i++){
        if(i == 0 || i == 1 || i == 3){
            continue;
        }
        for(int j = 0; j < length*2; j++){
            binary += to_string(matrix[j][i]);
        }
    }
    output = setStringtoASCII(binary);
    return output;
}

int main() {
    //Initialize
    srand(time(0));
    int count = 0;
    int countBinary = 0;
    
    string input;
    cout << "Enter a string: ";
    getline(cin, input);
    cout << "-----------------------------------" << endl;
    int length = input.length();
    string binary = charToBinary(input[count]);
    int matrix4[length * 2][4] = {};
    int matrix[length * 2][7] = {};

    //Matrix 4col
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < length*2; j++)
        {
            if(countBinary == 8)
            {
                count++;
                countBinary = 0;
                binary = charToBinary(input[count]);
            }
            matrix4[j][i] = binary[countBinary] - '0';
            countBinary++;
        }
    }
    
    //Display Matrix 4col
    cout << "Input converted to binary matrix with 4 cols:" << endl;
    displayMatrix4(matrix4, length*2);
    cout << "-----------------------------------" << endl;
    //reset count and countBinary
    count = 0;
    countBinary = 0;
    binary = charToBinary(input[count]);

    //Matrix 7col
    for(int i = 0; i < 7; i++)
    {
        if(i == 0 || i == 1 || i == 3){
            continue;
        }
        for(int j = 0; j < length*2; j++)
        {
            if(countBinary == 8)
            {
                count++;
                countBinary = 0;
                binary = charToBinary(input[count]);
            }
            matrix[j][i] = binary[countBinary] - '0';
            countBinary++;
        }
    }

    //Parity bit initialize
    for(int i = 0; i < length*2; i++)
    {
        matrix[i][0] = matrix4[i][0] ^ matrix4[i][1] ^ matrix4[i][3];
        matrix[i][1] = matrix4[i][0] ^ matrix4[i][2] ^ matrix4[i][3];
        matrix[i][3] = matrix4[i][1] ^ matrix4[i][2] ^ matrix4[i][3];
    }

    //Display with p bit
    cout << "Matrix with p bit:" << endl;
    displayMatrix7(matrix, length*2);
    cout << "-----------------------------------" << endl;
    //Distort random Matrix 7col
    for(int i = 0; i < length*2; i++)
    {
        int random = rand() % 7;
        if(random == 0){
            random += 2;
        }
        else if(random == 1 || random == 3){
            random++;
        }
        matrix[i][random] = !matrix[i][random];
    }

    //Display After Distort
    cout << "Matrix After Distort:" << endl;
    displayMatrix7(matrix, length*2);
    //Convert
    cout << "Before error fixing: " << converto(matrix, length) << endl;
    cout << "-----------------------------------" << endl;
    //Fix distortion
    for(int i = 0; i < length*2; i++)
    {
        int p = 0;
        int p1 = matrix[i][2] ^ matrix[i][4] ^ matrix[i][6];
        if(p1 != matrix[i][0]){
            p += 1;
        }
        int p2 = matrix[i][2] ^ matrix[i][5] ^ matrix[i][6];
        if(p2 != matrix[i][1]){
            p += 2;
        }
        int p3 = matrix[i][4] ^ matrix[i][5] ^ matrix[i][6];
        if(p3 != matrix[i][3]){
            p += 4;
        }
        if(p != 0)
        {
            p--;
            cout << "Error detected at position " << p << " in row " << i << endl;
            matrix[i][p] = !matrix[i][p];
        }
    }

    //Display After Fix
    cout << "Matrix After Fix:" << endl;
    displayMatrix7(matrix, length*2);
    cout << "After error fixing:" << converto(matrix, length) << endl;
    return 0;
}