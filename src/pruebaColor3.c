#include <stdio.h>
#include <stdlib.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>
//#include <dirent.h>

#define IMG_1 "mario.png"
#define IMG_2 "tia.png"
#define IMG_3 "piolin.png"
#define IMG_4 "creeper.png"
#define IMG_5 "imagen1.jpg"
#define IMG_LENGHT_NAME 100

int flag=0;

//aplying media color to the pixel when
//is on the corners
void mid_3_color(int * colorR, int * colorG, int * colorB, int i, int j, int xmax, int ymax){
	int R=0,G=0,B=0;
	int posA=i*xmax+j;
	//checking if the pixel is in one of the corners
	if(i==0 && j==0){
		int pos0=i*xmax+(j-1), pos1=(i+1)*xmax+j, pos2=(i+1)*xmax+(j+1);
		R=colorR[pos0]+colorR[pos1]+colorR[pos2];
		G=colorG[pos0]+colorG[pos1]+colorG[pos2];
		B=colorB[pos0]+colorB[pos1]+colorB[pos2];
		colorR[posA]=R/3; colorG[posA]=G/3; colorB[posA]=B/3;
		flag=1;
		return;
	}
	else if(i==xmax && j==ymax){
		int pos0=i*xmax+(j-1), pos1=(i-1)*xmax+j, pos2=(i-1)*xmax+(j-1);
		R=colorR[pos0]+colorR[pos1]+colorR[pos2];
		G=colorG[pos0]+colorG[pos1]+colorG[pos2];
		B=colorB[pos0]+colorB[pos1]+colorB[pos2];
		colorR[posA]=R/3; colorG[posA]=G/3; colorB[posA]=B/3;
		flag=1;
		return;
	}
	else if(i==0 && j==ymax){
		int pos0=i*xmax+(j-1), pos1=(i+1)*xmax+j, pos2=(i+1)*xmax+(j-1);
		R=colorR[pos0]+colorR[pos1]+colorR[pos2];
		G=colorG[pos0]+colorG[pos1]+colorG[pos2];
		B=colorB[pos0]+colorB[pos1]+colorB[pos2];
		colorR[posA]=R/3; colorG[posA]=G/3; colorB[posA]=B/3;
		flag=1;
		return;
	}
	else if(i==xmax && j==0){
		int pos0=i*xmax+(j+1), pos1=(i-1)*xmax+j, pos2=(i-1)*xmax+(j+1);
		R=colorR[pos0]+colorR[pos1]+colorR[pos2];
		G=colorG[pos0]+colorG[pos1]+colorG[pos2];
		B=colorB[pos0]+colorB[pos1]+colorB[pos2];
		colorR[posA]=R/3; colorG[posA]=G/3; colorB[posA]=B/3;
		flag=1;
		return;
	}
}

//aplying media color to the pixel when
//is on the borders, but not on the corners
void mid_5_color(int * colorR, int * colorG, int * colorB, int i, int j, int xmax, int ymax){
	int R=0,G=0,B=0;
	int posA=i*xmax+j;
	if(i==0){
		int pos0=i*xmax+(j-1), pos1=(i+1)*xmax+(j-1), pos2=(i+1)*xmax+j, pos3=(i+1)*xmax+(j+1), pos4=i*xmax+(j+1);
		R=colorR[pos0]+colorR[pos1]+colorR[pos2]+colorR[pos3]+colorR[pos4];
		G=colorG[pos0]+colorG[pos1]+colorG[pos2]+colorG[pos3]+colorG[pos4];
		B=colorB[pos0]+colorB[pos1]+colorB[pos2]+colorB[pos3]+colorB[pos4];
		colorR[posA]=R/5; colorG[posA]=G/5; colorB[posA]=B/5;
		flag=1;
		return;
	}
	else if(i==xmax){
		int pos0=i*xmax+(j-1), pos1=(i-1)*xmax+(j-1), pos2=(i-1)*xmax+j, pos3=(i-1)*xmax+(j+1), pos4=i*xmax+(j+1);
		R=colorR[pos0]+colorR[pos1]+colorR[pos2]+colorR[pos3]+colorR[pos4];
		G=colorG[pos0]+colorG[pos1]+colorG[pos2]+colorG[pos3]+colorG[pos4];
		B=colorB[pos0]+colorB[pos1]+colorB[pos2]+colorB[pos3]+colorB[pos4];
		colorR[posA]=R/5; colorG[posA]=G/5; colorB[posA]=B/5;
		flag=1;
		return;
	}
	else if(j==0){
		int pos0=(i-1)*xmax+j, pos1=(i-1)*xmax+(j+1), pos2=i*xmax+(j+1), pos3=(i+1)*xmax+(j+1), pos4=(i+1)*xmax+j;
		R=colorR[pos0]+colorR[pos1]+colorR[pos2]+colorR[pos3]+colorR[pos4];
		G=colorG[pos0]+colorG[pos1]+colorG[pos2]+colorG[pos3]+colorG[pos4];
		B=colorB[pos0]+colorB[pos1]+colorB[pos2]+colorB[pos3]+colorB[pos4];
		colorR[posA]=R/5; colorG[posA]=G/5; colorB[posA]=B/5;
		flag=1;
		return;
	}
	else if(j==ymax){
		int pos0=(i-1)*xmax+j, pos1=(i-1)*xmax+(j-1), pos2=i*xmax+(j-1), pos3=(i+1)*xmax+(j-1), pos4=(i+1)*xmax+j;
		R=colorR[pos0]+colorR[pos1]+colorR[pos2]+colorR[pos3]+colorR[pos4];
		G=colorG[pos0]+colorG[pos1]+colorG[pos2]+colorG[pos3]+colorG[pos4];
		B=colorB[pos0]+colorB[pos1]+colorB[pos2]+colorB[pos3]+colorB[pos4];
		colorR[posA]=R/5; colorG[posA]=G/5; colorB[posA]=B/5;
		flag=1;
		return;
	}
}

//aplying media color to the pixel when is on the others cases
void mid_8_color(int * colorR, int * colorG, int * colorB, int i, int j, int xmax){
	int R=0,G=0,B=0;
	int pos0=(i-1)*xmax+(j-1), pos1=i*xmax+(j-1), pos2=(i+1)*xmax+(j-1), pos3=(i+1)*xmax+j, 
		pos4=(i+1)*xmax+(j+1), pos5=i*xmax+(j+1), pos6=(i-1)*xmax+(j+1), pos7=(i-1)*xmax+j,
		posA=i*xmax+j;
	R=colorR[pos0]+colorR[pos1]+colorR[pos2]+colorR[pos3]+
		colorR[pos4]+colorR[pos5]+colorR[pos6]+colorR[pos7];
	G=colorG[pos0]+colorG[pos1]+colorG[pos2]+colorG[pos3]+
		colorG[pos4]+colorG[pos5]+colorG[pos6]+colorG[pos7];
	B=colorB[pos0]+colorB[pos1]+colorB[pos2]+colorB[pos3]+
		colorB[pos4]+colorB[pos5]+colorB[pos6]+colorB[pos7];
	colorR[posA]=R/8; colorG[posA]=G/8; colorB[posA]=B/8;
	flag=1;
	return;
}

//function to apply the media filther
int media_filther(int * colorR, int * colorG, int * colorB, int xmax, int ymax ){
	//making the media filter
    for(int i = 0; i < xmax; i++){
    	for(int j = 0; j < ymax; j++){
    		int posA=i*xmax+j;
    		//color original
    		//printf("--before--(%d, %d, %d)-\n", colorR[posA], colorG[posA], colorB[posA]);
    		//esquinas de la imagen
    		mid_3_color(colorR, colorG, colorB, i, j, xmax, ymax);
    		//bordes de la imagen
    		if(flag==0)
    			mid_5_color(colorR, colorG, colorB, i, j, xmax, ymax);
    		//otros
    		if(flag==0)
    			mid_8_color(colorR, colorG, colorB, i, j,xmax);
    		//comprobando si hubo cambio
    		//printf("--after--(%d, %d, %d)-\n", colorR[posA], colorG[posA], colorB[posA]);
    		flag=0;
    	}
    }
}

//function to filther an image that comes form a url of a machine.
int filther_image_url(const char*  img, int flag){
	cv::Mat image=cv::imread(img,flag);
	if( image.empty() ){
        printf("Could not open or find the image\n");
        return -1;
    }
    int xmax=image.rows;
    int ymax=image.cols;
    cv::Vec3b bgrPixel;
    int * colorR=(int *)malloc(sizeof(int)*xmax*ymax);
    int * colorG=(int *)malloc(sizeof(int)*xmax*ymax);
    int * colorB=(int *)malloc(sizeof(int)*xmax*ymax);
    //extranting the pixels form the image
    for(int i = 0; i < xmax; i++){
    	for(int j = 0; j < ymax; j++){
    		bgrPixel = image.at<cv::Vec3b>(i, j);
    		int posM=i*xmax+j;
    		colorB[posM]=bgrPixel.val[0];
    		colorG[posM]=bgrPixel.val[1];
    		colorR[posM]=bgrPixel.val[2];
    	}
    }

    //setting the media filther on the image.
    media_filther(colorR,colorG,colorB,xmax,ymax);
    //setting the pixels of the image
    for(int i = 0; i < xmax; i++){
    	for(int j = 0; j < ymax; j++){
    		bgrPixel = image.at<cv::Vec3b>(i, j);
    		int posM=i*xmax+j;
    		bgrPixel.val[0]=colorB[posM];
    		bgrPixel.val[1]=colorG[posM];
    		bgrPixel.val[2]=colorR[posM];
    		image.at<cv::Vec3b>(i, j)=bgrPixel;
    	}
    }
    std::string tempName="mediaFil"+std::string(img);
    cv::imwrite(tempName.c_str(),image);
    return 0;
}

int main(){
	filther_image_url(IMG_1,cv::IMREAD_COLOR);
    return 0;
}