#include <iostream>
#include <fstream>
#include <cstring>
#include "bmplib.h"
#include "bmplib.cpp"
using namespace std;
unsigned char image [SIZE][SIZE][RGB];
unsigned char download[SIZE][SIZE][RGB];

void upload_image(){
    char upload_image[200];
    cout<<"please enter the name of the image you want to upload:\n ";cin>>upload_image;
    strcat(upload_image,".bmp");
    readRGBBMP(upload_image,image);}


void download_image(){
    char download_image[200];
    cout<<"please enter the name of the image you want to download:\n ";cin>>download_image;
    strcat(download_image,".bmp");
    writeRGBBMP(download_image,image);}
int main() {
    upload_image();
    download_image();
    return 0;
}
