#include <iostream>
#include <fstream>
#include <cstring>
#include "bmplib.h"
#include "bmplib.cpp"
using namespace std;
unsigned char image [SIZE][SIZE][RGB];
unsigned char download[SIZE][SIZE][RGB];


char getOption();

void upload_image();
void blackWhite();
void invertImage();
void mergeImage();
void flipImage();
void darkenLightenImage();
void rotateImage();
void detectImageEdges();
void enlargeImage();
void shrinkImage();
void mirrorHalf();
void shuffleImage();
void blurImage();
void download_image();
string imageName;



int main() {
    char op;
    upload_image();
    while(true){
        op = getOption();
        if(op=='0'){
            break;
        }
        switch (op) {
            case '1':
                blackWhite();
                break;
            case '2':
                invertImage();
                break;
            case '3':
                mergeImage();
                break;
            case '4':
                flipImage();
                break;
            case '5':
                rotateImage();
                break;
            case '6':
                darkenLightenImage();
                break;
            case '7':
                detectImageEdges();
                break;
            case '8':
                enlargeImage();
                break;
            case '9':
                shrinkImage();
                break;
            case 'a':
                mirrorHalf();
                break;
            case 'b':
                shuffleImage();
                break;
            case 'c':
                blurImage();
                break;
            case 's':
                download_image();
                break;
            case 'w':
                upload_image();
                break;
            default:
                break;
        }
    }
    return 0;
}
char getOption() {
    char op;
    cout <<"Please select a filter to apply on "<<imageName<<" or 0 to exit:\n"
             "1- Black & White Filter    \t"
             "2- Invert Filter\n"
             "3- Merge Filter            \t"
             "4- Flip Image\n"
             "5- Rotate Image             \t"
             "6- Darken and Lighten Image\n"
             "7- Detect Image Edges      \t"
             "8- Enlarge Image\n"
             "9- Shrink Image            \t"
             "a- Mirror 1/2 Image\n"
             "b- Shuffle Image           \t"
             "c- Blur Image\n"
             "s- Save the image to a file\t"
             "w- Change the image\n"
             "0- Exit\n"
             "-->";
    cin >> op;
    return op;
}

void upload_image(){
    char upload_image[200];
    cout<<"please enter the name of the image you want to upload:\n ";cin>>upload_image;
    imageName = upload_image;
    strcat(upload_image,".bmp");
    readRGBBMP(upload_image,image);

}


void download_image(){
    char download_image[200];
    cout<<"please enter the name of the image you want to download:\n ";cin>>download_image;
    strcat(download_image,".bmp");
    writeRGBBMP(download_image,image);}
