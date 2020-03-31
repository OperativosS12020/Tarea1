#include <stdio.h>
#include <stdlib.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <dirent.h>

#define IMG_1 "mario.png"
#define IMG_2 "tia.png"
#define IMG_3 "piolin.png"
#define IMG_4 "creeper.png"
#define IMG_LENGHT_NAME 100

struct pixelColor{
	int r;
	int g;
	int b;
};

char * copyName(const char * source){
	char * final=(char *)malloc(sizeof(char)*IMG_LENGHT_NAME);
	int i=0;
	for(; i<IMG_LENGHT_NAME || source[i]=='\0'; i++){
		final[i]=source[i];
	}
	final[i]='\0';
	return final;
}

void getFiles(){
	char * tt; 
	char * t1;
	DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d){
        while ((dir = readdir(d)) != NULL){
        	if(dir->d_type==DT_REG){
        		//t1=copyName(dir->d_name);
        		printf("%s\n", dir->d_name);
        		//printf("----%s----\n", t1);	
        	}
        }
        closedir(d);
    }
}


void mid_3_color(struct pixelColor* pixCol[], int i, int j, int xmax, int ymax){
	int R=0,G=0,B=0;
	if(i==0 && j==0){
		R=pixCol[i][j+1].r+pixCol[i+1][j].r+pixCol[i+1][j+1].r;
		G=pixCol[i][j+1].g+pixCol[i+1][j].g+pixCol[i+1][j+1].g;
		B=pixCol[i][j+1].b+pixCol[i+1][j].b+pixCol[i+1][j+1].b;
		pixCol[i][j].r=R/3; pixCol[i][j].g=G/3; pixCol[i][j].b=B/3;
	}
	else if(i==xmax && j==ymax){
		R=pixCol[i][j-1].r+pixCol[i-1][j].r+pixCol[i-1][j-1].r;
		G=pixCol[i][j-1].g+pixCol[i-1][j].g+pixCol[i-1][j-1].g;
		B=pixCol[i][j-1].b+pixCol[i-1][j].b+pixCol[i-1][j-1].b;
		pixCol[i][j].r=R/3; pixCol[i][j].g=G/3; pixCol[i][j].b=B/3;
	}
	else if(i==0 && j==ymax){
		R=pixCol[i][j-1].r+pixCol[i+1][j].r+pixCol[i+1][j-1].r;
		G=pixCol[i][j-1].g+pixCol[i+1][j].g+pixCol[i+1][j-1].g;
		B=pixCol[i][j-1].b+pixCol[i+1][j].b+pixCol[i+1][j-1].b;
		pixCol[i][j].r=R/3; pixCol[i][j].g=G/3; pixCol[i][j].b=B/3;
	}
	else if(i==xmax && j==0){
		R=pixCol[i][j+1].r+pixCol[i-1][j].r+pixCol[i-1][j+1].r;
		G=pixCol[i][j+1].g+pixCol[i-1][j].g+pixCol[i-1][j+1].g;
		B=pixCol[i][j+1].b+pixCol[i-1][j].b+pixCol[i-1][j+1].b;
		pixCol[i][j].r=R/3; pixCol[i][j].g=G/3; pixCol[i][j].b=B/3;
	}
}

void mid_5_color(struct pixelColor* pixCol[], int i, int j, int xmax, int ymax){
	int R=0,G=0,B=0;
	if(i==0){
		R=pixCol[i][j-1].r+pixCol[i+1][j-1].r+pixCol[i+1][j].r+pixCol[i+1][j+1].r+pixCol[i][j+1].r;
		G=pixCol[i][j-1].g+pixCol[i+1][j-1].g+pixCol[i+1][j].g+pixCol[i+1][j+1].g+pixCol[i][j+1].g;
		B=pixCol[i][j-1].b+pixCol[i+1][j-1].b+pixCol[i+1][j].b+pixCol[i+1][j+1].b+pixCol[i][j+1].b;
		pixCol[i][j].r=R/5; pixCol[i][j].g=G/5; pixCol[i][j].b=B/5;
	}
	else if(i==xmax){
		R=pixCol[i][j-1].r+pixCol[i-1][j-1].r+pixCol[i-1][j].r+pixCol[i-1][j+1].r+pixCol[i][j+1].r;
		G=pixCol[i][j-1].g+pixCol[i-1][j-1].g+pixCol[i-1][j].g+pixCol[i-1][j+1].g+pixCol[i][j+1].g;
		B=pixCol[i][j-1].b+pixCol[i-1][j-1].b+pixCol[i-1][j].b+pixCol[i-1][j+1].b+pixCol[i][j+1].b;
		pixCol[i][j].r=R/5; pixCol[i][j].g=G/5; pixCol[i][j].b=B/5;
	}
	else if(j==0){
		R=pixCol[i-1][j].r+pixCol[i-1][j+1].r+pixCol[i][j+1].r+pixCol[i+1][j+1].r+pixCol[i+1][j].r;
		G=pixCol[i-1][j].g+pixCol[i-1][j+1].g+pixCol[i][j+1].g+pixCol[i+1][j+1].g+pixCol[i+1][j].g;
		B=pixCol[i-1][j].b+pixCol[i-1][j+1].b+pixCol[i][j+1].b+pixCol[i+1][j+1].b+pixCol[i+1][j].b;
		pixCol[i][j].r=R/5; pixCol[i][j].g=G/5; pixCol[i][j].b=B/5;
	}
	else if(j==ymax){
		R=pixCol[i-1][j].r+pixCol[i-1][j-1].r+pixCol[i][j-1].r+pixCol[i+1][j-1].r+pixCol[i+1][j].r;
		G=pixCol[i-1][j].g+pixCol[i-1][j-1].g+pixCol[i][j-1].g+pixCol[i+1][j-1].g+pixCol[i+1][j].g;
		B=pixCol[i-1][j].b+pixCol[i-1][j-1].b+pixCol[i][j-1].b+pixCol[i+1][j-1].b+pixCol[i+1][j].b;
		pixCol[i][j].r=R/5; pixCol[i][j].g=G/5; pixCol[i][j].b=B/5;
	}
}

void mid_8_color(struct pixelColor* pixCol[], int i, int j){
	int R=0,G=0,B=0;
	R=pixCol[i-1][j-1].r+pixCol[i][j-1].r+pixCol[i+1][j-1].r+pixCol[i+1][j].r
		+pixCol[i+1][j+1].r+pixCol[i][j+1].r+pixCol[i-1][j+1].r+pixCol[i-1][j].r;
	G=pixCol[i-1][j-1].g+pixCol[i][j-1].g+pixCol[i+1][j-1].g+pixCol[i+1][j].g
		+pixCol[i+1][j+1].g+pixCol[i][j+1].g+pixCol[i-1][j+1].g+pixCol[i-1][j].g;
	B=pixCol[i-1][j-1].b+pixCol[i][j-1].b+pixCol[i+1][j-1].b+pixCol[i+1][j].b
		+pixCol[i+1][j+1].b+pixCol[i][j+1].b+pixCol[i-1][j+1].b+pixCol[i-1][j].b;
	pixCol[i][j].r=R/8; pixCol[i][j].g=G/8; pixCol[i][j].b=B/8;
}

int applying_mid_filter(const char*  img, int flag){
	cv::Mat image=cv::imread(img,flag);
	if( image.empty() ){
        printf("Could not open or find the image\n");
        return -1;
    }
    int xmax=image.rows;
    int ymax=image.cols;
    cv::Vec3b bgrPixel;
    struct pixelColor pixCol[xmax][ymax];
    for(int i = 0; i < xmax; i++){
    	for(int j = 0; j < ymax; j++){
    		bgrPixel = image.at<cv::Vec3b>(i, j);
    		pixCol[i][j].b=bgrPixel.val[0];
    		pixCol[i][j].g=bgrPixel.val[1];
    		pixCol[i][j].r=bgrPixel.val[2];
    	}
    }
    for(int i = 0; i < xmax; i++){
    	for(int j = 0; j < ymax; j++){
    		//color original
    		printf("--before--%d %d %d- \n", pixCol[i][j].r, pixCol[i][j].g, pixCol[i][j].b);
    		//esquinas de la imagen
    		mid_3_color(pixCol, i, j, xmax, ymax);
    		//bordes de la imagen
    		mid_5_color(pixCol, i, j, xmax, ymax);
    		//otros
    		mid_8_color(pixCol, i, j);
    		//comprobando si hubo cambio
    		printf("--after--%d %d %d- \n", pixCol[i][j].r, pixCol[i][j].g, pixCol[i][j].b);
    	}
    }
    return 0;
}

int main(){
	getFiles();
	applying_mid_filter(IMG_1,cv::IMREAD_COLOR);
	//reading_Img(IMG_1,cv::IMREAD_COLOR);
    return 0;
}