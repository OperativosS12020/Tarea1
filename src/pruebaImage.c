#include <stdio.h>
#include <stdlib.h>

#define IMG_1 "mario.png"
#define IMG_2 "tia.png"
#define IMG_3 "piolin.png"
#define IMG_4 "creeper.png"
#define IMG_5 "lena.png"

#define IDHR_NAME "IHDR"
#define IDAT_NAME "IDAT"
#define IEND_NAME "IEND"

#define PNG_SIGNATURE_LENGHT 8

//PNG signature - 8 bytes
/*
	msbit set	1 byte
	name chunck 3 bytes
	crtl-m 		1 byte
	line feed 	1 byte
	ctrl-z 		1 byte
	line feed 	1 byte
*/

//IEND content 12 bytes
/*
	size chunck 4 bytes
	name chunck 4 bytes
	CRC 		4 bytes
*/


/*
	structure to hold header of 
	the png image. content 25 bytes
	size chunck 4 bytes
	name chunck 4 bytes
	width img 	4 bytes
	height img 	4 bytes
	bit depth 	1 byte
	color type 	1 byte
	compr mth 	1 byte
	filth mth 	1 byte
	inter mth 	1 byte
	CRC 		4 bytes
*/
struct IHDR_PNG{
	int lenght;
	int width;
	int height;
	char bitDepth;
	char colorType;
	char compMeth;
	char filtMeth;
	char interMth;
	int CRC;
};

/*
	structre to hold the entire 
	data of the image.
	size chunck 4 bytes
	name chunck 4 bytes
	data 		n bytes
	CRC 		4 bytes
*/
struct IDAT_PNG{
	int size;
	char * data;
	int CRC;
};

/*
	function to get the max size
	of a file in bytes.
*/
int getSize(const char* name){
	FILE *fp;
    char ch;
    int size = 0;
    fp = fopen(name, "r");
    if (fp == NULL)
        return -1;
    fseek(fp, 0, 2);    /* file pointer at the end of file */
    size = ftell(fp);   /* take a position of file pointer un size variable */
    fclose(fp);
    return size;
}

/*
	function to reverse a number for
	endianess.
*/
int * getValueInt(const char * value){
	char * temp = malloc(sizeof(char)*4);
	for(int i=0; i<4 ; i++){
		temp[3-i]=value[i];
	}
	return (int*)temp;
}

struct IHDR_PNG * getHeaderPNG(const char* img_temp,int place){
	struct IHDR_PNG * ihdr_temp=(struct IHDR_PNG*)malloc(sizeof(struct IHDR_PNG)*1);
    //reading the IHDR
    ihdr_temp->lenght=*(getValueInt(img_temp+place));
    place+=8;
    ihdr_temp->width=*(getValueInt(img_temp+place));
    place+=4;
    ihdr_temp->height=*(getValueInt(img_temp+place));
    place+=4;
    ihdr_temp->bitDepth=img_temp[place];
    place+=1;
    ihdr_temp->colorType=img_temp[place];
    place+=1;
    ihdr_temp->compMeth=img_temp[place];
    place+=1;
    ihdr_temp->filtMeth=img_temp[place];
    place+=1;
    ihdr_temp->interMth=img_temp[place];
    place+=1;
    ihdr_temp->CRC=*(getValueInt(img_temp+place));
    return ihdr_temp;
}

struct IDAT_PNG * getDataPNG(){

}

int main(){
	int img_size=getSize(IMG_2);
	printf("%d\n", img_size);

	FILE *f;							//my file pointer
	f=fopen(IMG_2,"rb");				//setting my file pointer for reading in binary format
	char img_buffer[img_size];			//creating the image buffer
	fread(img_buffer,img_size,1,f);		//setting the data inside the buffer
	fclose(f); 

	int global_index=0, i=0;
	printf("-printing the png signature-\n");
	//reading the png signature
	for(i=0; i<PNG_SIGNATURE_LENGHT; i++){
        printf ("%c\n",img_buffer[i]); 
    }
    printf("%d\n",i-global_index);	
    printf("----------------------------\n");

    global_index=i;
    printf("-printing the IHDR-\n");
    //reading the IDHR
    int *tt=getValueInt(img_buffer+i);
    printf ("largo del IHDR %d\n",*tt);
    i+=8;
    tt=getValueInt(img_buffer+i);
    printf ("width: %d\n",*tt);
    i+=4;
    tt=getValueInt(img_buffer+i);
    printf ("height: %d\n",*tt);
    i+=4;
    printf ("bit depth: %02x\n",img_buffer[i]);
    i+=1;
    printf ("color type: %02x\n",img_buffer[i]);
    i+=1;
    printf ("compression method: %02x\n",img_buffer[i]);
    i+=1;
    printf ("filther method: %02x\n",img_buffer[i]);	
    i+=1;
    printf ("interlace method: %02x\n",img_buffer[i]);
    i+=1;
    tt=getValueInt(img_buffer+i);
    printf ("CRC: %d\n",*tt);
    i+=4;
    printf("-------------------\n");

    printf("%d\n",i);

    printf("finding the IDAT place\n");

    for(int j=i; j<img_size; j++){
    	if(img_buffer[j]=='I' && img_buffer[j+1]=='D' && img_buffer[j+2]=='A' && img_buffer[j+3]=='T')
    		break;
    }

    i-=4;
    global_index=i;

    printf("-printing the IDAT-\n");
	
	tt=getValueInt(img_buffer+i);
    printf ("lenght: %d\n",*tt);
    i+=8;

  	printf("--\n");
/*	Read contents from file 
	char pngHead[8]={0,0,0,0,0,0,0,0};
	char ihdr[13]={0,0,0,0,0,0,0,0,0,0,0,0,0};

    //getting the header of the file
    for(int i=0; i<PNG_LENGHT; i++){
    	pngHead[i]=fgetc(f); 
    	printf ("%c\n", pngHead[i]);
    }
    printf("\n-fin del png head-\n");

    //getting the header of the file
    for(int i=0; i<IHDR_LENGHT; i++){
    	pngHead[i]=fgetc(f); 
    	printf ("%c\n", ihdr[i]);
    }
    printf("\n-fin del ihdr-\n");
    */

    return 0; 
}