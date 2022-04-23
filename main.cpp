// FCI – Programming 1 – 2022 - Assignment 3
// Program Name: ImageFilters.cpp
// Last Modification Date: 23/4/2022
// Author1 and ID and Group: Kareem El Sakkary, 20210301, S1
// Author2 and ID and Group: Nada Mohammed, 20210422, S1
// Author3 and ID and Group: Hoda Samir, 20210443, S1
// Teaching Assistant: Nesma
// Purpose: create a program that take a colored image and add filters to it then save it

#include <iostream>
#include <fstream>
#include <cstring>
#include "bmplib.h"
#include "bmplib.cpp"
using namespace std;
unsigned char image [SIZE][SIZE][RGB];
unsigned char download[SIZE][SIZE][RGB];


char getOption();
void assign(unsigned char image1 [SIZE][SIZE][RGB],int x1,int y1,unsigned char image2 [SIZE][SIZE][RGB],int x2,int y2);

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


void invertImage() {
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            for (int l = 0; l < 3; l++) {
                image[i][j][l] = 255 - image[i][j][l]; // invert each color pixel by subtracting 255 from each pixel value
            }
        }
    }
    imageName += " invert";
}


void blackWhite(){
    int sum = 0;
    for(int i =0;i<SIZE;i++){
        for(int j =0;j<SIZE;j++){
            for (int l = 0; l < 3; l++) {
                sum+=(int) image[i][j][l];
            }
        }
    }
    int avg = sum/(SIZE*SIZE);
    for(int i =0;i<SIZE;i++){
        for(int j =0;j<SIZE;j++){
            if((image[i][j][0]+image[i][j][1]+image[i][j][2])>=avg) {
                image[i][j][0] = 255;
                image[i][j][1] = 255;
                image[i][j][2] = 255;
            }
            else{
                image[i][j][0]=0;
                image[i][j][1]=0;
                image[i][j][2]=0;
                }
            }
        }
    imageName+=" B&W";
}


void flipImage(){
    char dir='n';
    while (dir!='h'&&dir!='v'){
        cout << "Flip horizontally(h) or vertically(v)";
        cin>>dir;
    }
    if(dir == 'h'){
        unsigned char temp;
        for(int i =0;i<SIZE/2;i++){
            for(int j =0;j<SIZE;j++){
                for(int l =0;l<3;l++){
                    temp = image[i][j][l];
                    image[i][j][l]=image[SIZE-i-1][SIZE-j-1][l];
                    image[SIZE-i-1][SIZE-j-1][l]=temp;
                }
            }
        }
        imageName+=" flip (h)";
    }else{
        unsigned char temp;
        for(int i =0;i<SIZE;i++){
            for(int j =0;j<SIZE/2;j++){
                for(int l =0;l<3;l++){
                    temp = image[i][j][l];
                    image[i][j][l] = image[i][SIZE - j - 1][l];
                    image[i][SIZE - j - 1][l] = temp;
                }
            }
        }
        imageName+=" flip (v)";
    }
}// for rotateImage
void rotate() { // function to rotate by 90 degree only
    unsigned char tempMat[256][256][3];
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            for(int l=0;l<3;l++) {
                tempMat[j][256 - i][l] = image[i][j][l];// rotate clockwise rotation by replacing each row with opposite column from the end
            }
        }
    }
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            for(int l=0;l<3;l++){ image[i][j][l] = tempMat[i][j][l]; }
        }
    }
}
void rotateImage(){
    int degree, c{0};
    cout << "Which degree do you want to rotate by ? (90 - 180 - 270)" << endl;
    cin >> degree;// take the degree that the user wants to rotate the image by it
    if (degree == 90) {
        rotate();
    }
    if (degree == 180) { // 180 - rotate by 90 degree twice
        while (c < 2) {
            rotate();
            c++;
        }
    }
    if (degree == 270) { // 270 - rotate by 90 degree 3 times
        while (c < 3) {
            rotate();
            c++;
        }
    }
    imageName+= " rotate "+to_string(degree)+" degree";
}
void enlargeImage(){
    // take the number of the quarter that the user wants to enlarge it
    cout << "Please enter the number of the quarter you want to enlarge: " << endl;
    int nQuarter, startX, startY, countX = 0, countY = 0; ;
    cin >> nQuarter;
    while (nQuarter < 0 || nQuarter > 4){
        cout << "Invalid! Please enter a number from [1, 2, 3, 4]" << endl;
        cin >> nQuarter;
    } // set the starting point depending on which quarter the user will choose
    if (nQuarter == 1)
        startX = startY = 0;
    if (nQuarter == 2){
        startX = 0;
        startY = 128;
    }
    if (nQuarter == 3){
        startX = 128;
        startY = 0;
    }
    if (nQuarter == 4)
        startX = startY = 128;
    unsigned char enlargedImage[256][256][3], tmp;
    for (int x = startX; x < startX + 128; x++){
        for (int y = startY; y < startY + 128; y++){
            for(int l=0;l<3;l++) {
                tmp = image[x][y][l];
                for (int i = countX;i < countX + 2; i++) { // enlarge the quarter image by duplicating each pixel 4 times
                    for (int j = countY; j < countY + 2; j++) {
                        enlargedImage[i][j][l] = tmp;
                    }
                }
            }
            countY += 2;
        }
        countY = 0;
        countX += 2;
    }
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            for(int l=0;l<3;l++) {
                image[i][j][l] = enlargedImage[i][j][l];
            }
        }
    }
    imageName+= " enlarge "+to_string(nQuarter)+"th quarter";

}
void shrinkImage(){
    cout << "please enter the value you want to shrink with from the list[1/2,1/3,1/4]\n";
    string shrink_value;
    cin >> shrink_value;
        if (shrink_value == "1/2") {
            int c = 0;
            for (int i = 0; i < SIZE; i += 2) {
                int d = 0;
                for (int j = 0; j < SIZE; j += 2) {
                    for(int l=0;l<3;l++) {
                        image[c][d][l] = (
                                (image[i][j][l] + image[i + 1][j][l] + image[i][j + 1][l] + image[i + 1][j + 1][l]) /
                                4);
                    }d++;
                }
                c++;
            }
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    for(int l=0;l<3;l++) {
                    if (i >= (SIZE / 2) || j >= (SIZE / 2)) {
                        image[i][j][l] = SIZE - 1;
                    }}
                }
            }
        } else if (shrink_value == "1/3") {
            int c = 0;
            for (int i = 0; i < SIZE; i += 3) {
                int d = 0;
                for (int j = 0; j < SIZE; j += 3) {
                    for(int l=0;l<3;l++) {
                        image[c][d][l] = (
                                (image[i][j][l] + image[i + 1][j][l] + image[i][j + 1][l] + image[i + 1][j + 1][l] +
                                 image[i][j + 2][l] +
                                 image[i + 2][j][l] + image[i + 2][j + 2][l] + image[i + 1][j + 2][l] +
                                 image[i + 2][j + 1][l]) / 9);
                    }d++;
                }
                c++;
            }
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    for(int l=0;l<3;l++) {
                    if (i >= (SIZE / 3) || j >= (SIZE / 3)) {
                        image[i][j][l] = SIZE - 1;
                    }}
                }
            }
        } else if (shrink_value == "1/4") {
            int c = 0;
            for (int i = 0; i < SIZE; i += 4) {
                int d = 0;
                for (int j = 0; j < SIZE; j += 4) {
                    for(int l=0;l<3;l++) {
                        image[c][d][l] = (
                                (image[i][j][l] + image[i + 1][j][l] + image[i][j + 1][l] + image[i + 1][j + 1][l] +
                                 image[i][j + 2][l] +
                                 image[i + 2][j][l] + image[i + 2][j + 2][l] + image[i + 1][j + 2][l] +
                                 image[i + 2][j + 1][l] +
                                 image[i + 3][j][l] + image[i][j + 3][l] + image[i + 1][j + 3][l] +
                                 image[i + 3][j + 1][l] +
                                 image[i + 3][j + 2][l] + image[i + 2][j + 3][l]) / 16);
                    }d++;
                }
                c++;
            }
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    for(int l=0;l<3;l++) {
                    if (i >= (SIZE / 4) || j >= (SIZE / 4)) {
                        image[i][j][l] = SIZE - 1;
                    }}
                }
            }
        }

    imageName+= " shrink with "+shrink_value;
}
void mirrorHalf(){
    char half='n';
    while (half!='l'&&half!='r'&&half!='u'&&half!='d'){
        cout << "Mirror left(l), right(r), upper(u), down(d) side? ";
        cin>>half;
    }
    switch (half) {
        case 'l':
            for(int i =0;i<SIZE;i++){
                for(int j =0;j<SIZE/2;j++){
                    for(int l =0 ;l<3;l++) {
                        image[i][SIZE - j - 1][l] = image[i][j][l];
                    }
                }
            }
            imageName+=" mirror (l)";
            break;
        case 'r':
            for(int i =0;i<SIZE;i++){
                for(int j =0;j<SIZE/2;j++){
                    for(int l =0 ;l<3;l++){
                        image[i][j][l] = image[i][SIZE - j - 1][l];
                    }
                }
            }
            imageName+=" mirror (r)";
            break;
        case 'd':
            for(int i =0;i<SIZE/2;i++){
                for(int j =0;j<SIZE;j++){
                    for(int l =0 ;l<3;l++)
                    { image[255 - i][j][l] = image[i][j][l]; }
                }
            }
            imageName+=" mirror (d)";
            break;
        case 'u':
            for(int i =0;i<SIZE/2;i++){
                for(int j =0;j<SIZE;j++){
                    for(int l =0 ;l<3;l++) {
                        image[i][j][l] = image[SIZE - i - 1][j][l];
                    }
                }
            }
            imageName+=" mirror (u)";
            break;
    }
}
void shuffleImage(){
    string order;
    // take the order from the user
    cout << "Please enter the order you want to the quarters in the new image: " << endl;
    cin.ignore();
    getline(cin, order);
    unsigned char tempMatrix[256][256][3];
    int q{1};
    for (char k: order) {
        if(k == ' '){
            continue;
        }
        for (int i = 0; i < 256 / 2; i++) {
            for (int j = 0; j < 256 / 2; j++) {
                for(int l =0 ;l<3;l++) {
                    // fill the quarters in the temp matrix by the given order
                    if (q == 1) {  // first quarter
                        if (k == '1') {
                            tempMatrix[i][j][l] = image[i][j][l];
                        }
                        if (k == '2') {
                            tempMatrix[i][j][l] = image[i][j + 128][l];
                        }
                        if (k == '3') {
                            tempMatrix[i][j][l] = image[i + 128][j][l];
                        }
                        if (k == '4') {
                            tempMatrix[i][j][l] = image[i + 128][j + 128][l];
                        }
                    }
                    if (q == 2) {  // second quarter
                        if (k == '1') {
                            tempMatrix[i][j + 128][l] = image[i][j][l];
                        }
                        if (k == '2') {
                            tempMatrix[i][j + 128][l] = image[i][j + 128][l];
                        }
                        if (k == '3') {
                            tempMatrix[i][j + 128][l] = image[i + 128][j][l];
                        }
                        if (k == '4') {
                            tempMatrix[i][j + 128][l] = image[i + 128][j + 128][l];
                        }
                    }
                    if (q == 3) {  // third quarter
                        if (k == '1') {
                            tempMatrix[i + 128][j][l] = image[i][j][l];
                        }
                        if (k == '2') {
                            tempMatrix[i + 128][j][l] = image[i][j + 128][l];
                        }
                        if (k == '3') {
                            tempMatrix[i + 128][j][l] = image[i + 128][j][l];
                        }
                        if (k == '4') {
                            tempMatrix[i + 128][j][l] = image[i + 128][j + 128][l];
                        }
                    }
                    if (q == 4) {  // fourth quarter
                        if (k == '1') {
                            tempMatrix[i + 128][j + 128][l] = image[i][j][l];
                        }
                        if (k == '2') {
                            tempMatrix[i + 128][j + 128][l] = image[i][j + 128][l];
                        }
                        if (k == '3') {
                            tempMatrix[i + 128][j + 128][l] = image[i + 128][j][l];
                        }
                        if (k == '4') {
                            tempMatrix[i + 128][j + 128][l] = image[i + 128][j + 128][l];
                        }
                    }
                }
            }
        }
        q++;
    }
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 256; j++) {
            for(int l =0 ;l<3;l++) {
                image[i][j][l] = tempMatrix[i][j][l];
            }
        }
    }
    imageName+= " shuffle by order "+order;

}
void blurImage(){
    int value;
    for (int i=0 ; i<253 ; i+=2){
        for (int j=0 ; j<253 ; j+=2){
            for(int k =0;k<4;k++){
                value =((image[i][j][k]+image[i+1][j][k]+image[i][j+1][k]+image[i+1][j+1][k]+image[i][j+2][k]+image[i+2][j][k]+image[i+2][i+2][k]+image[i+1][j+2][k]+image[i+2][j+1][k]+image[i+3][j][k]+image[i][j+3][k]+image[i+3][j+3][k]+image[i+2][j+3][k]+image[i+3][j+2][k])/14);
                image[i][j][k]=value;
                image[i+1][j][k]=value;
                image[i][j+1][k]=value;
                image[i+1][j+1][k]=value;
                image[i][j+2][k]=value;
                image[i+2][j][k]=value;
                image[i+2][i+2][k]=value;
                image[i+1][j+2][k]=value;
                image[i+2][j+1][k]=value;
                image[i+3][j][k]=value;
                image[i][j+3][k]=value;
                image[i+3][j+3][k]=value;
                image[i+2][j+3][k]= value;
                image[i+3][j+2][k]=value;

            }}}
    imageName+= " blur";

}
void mergeImage(){
    char upload_image[200];
    unsigned char to_merge [SIZE][SIZE][RGB];
    cout<<"please enter the name of the image you want to merge with:\n ";cin>>upload_image;
    strcat(upload_image,".bmp");
    readRGBBMP(upload_image,to_merge);

    for(int i = 0;i<SIZE;i++){
        for(int j = 0;j<SIZE;j++){
            for(int k = 0;k<4;k++){
                download[i][j][k]=(image[i][j][k]+to_merge[i][j][k])/2;
                image[i][j][k]=download[i][j][k];

            }}}}
void detectImageEdges(){
    unsigned char newImage[SIZE][SIZE][3];
    for(int i =0;i<SIZE-2;i++){
        for(int j =0;j<SIZE-2;j++){
           int colorX, colorY;
           for(int l =0;l<3;l++){
               colorX =image[i][j][l]*1   + image[i][j+1][l]*0   +image[i][j+2][l]*-1;
               colorX+=image[i+1][j][l]*2 + image[i+1][j+1][l]*0 +image[i+1][j+2][l]*-2;
               colorX+=image[i+1][j][l]*1 + image[i+1][j+1][l]*0 +image[i+1][j+2][l]*-1;
               colorX = colorX > 255 ? 255 : colorX;
               colorY =image[i][j][l]*1   + image[i][j+1][l]*2   +image[i][j+2][l]*1;
               colorY+=image[i+1][j][l]*0 + image[i+1][j+1][l]*0 +image[i+1][j+2][l]*0;
               colorY+=image[i+1][j][l]*-1 + image[i+1][j+1][l]*-2 +image[i+1][j+2][l]*-1;
               colorY = colorY > 255 ? 255 : colorY;
               newImage[i][j][l]= (abs(colorX)+ abs(colorY))>255?255:(abs(colorX)+ abs(colorY));
           }
        }
    }
    for(int i =SIZE-2;i<SIZE;i++){
        for(int j =SIZE-2;j<SIZE;j++) {
            for(int l =0;l<3;l++) {
                newImage[i][j][l]=0;
            }
        }
    }
    for(int i =0;i<SIZE;i++){
        for(int j =0;j<SIZE;j++) {
            for(int l =0;l<3;l++){
                image[i][j][l] = newImage[i][j][l];
            }
        }
    }
    imageName+= "`s objects edges";
}//done

void darkenLightenImage(){
    string action;
    cout<<"Darken or lighten?"; cin>>action;
    if (action == "Darken"){
        for(int i = 0;i<=SIZE;i++) {
            for(int k =0;k<=RGB;k++){
                for (int j = 0; j <= SIZE; j++) {
                    download[i][j][k]=(image[i][j][k]+255)/2;
                    image[i][j][k] = download[i][j][k];

                }}}
    }else if (action == "lighten"){
        for(int i = 0;i<=SIZE;i++){
            for(int j = 0; j<=SIZE;j++){
                for(int k =0;k<=RGB;k++){

                    download[i][j][k]=(image[i][j][k])/2;
                    image[i][j][k] = download[i][j][k];
                }}}
    }}
