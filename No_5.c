#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
    
void compress(char *sourcefile,char *destinfile){
	FILE *source,*destin;
	char currentc,currents;
	int length;
	if((source=fopen(sourcefile,"rb"))==NULL){		
		printf("文件打开失败！");
		exit(0);
	}

    if((destin=fopen(destinfile,"wb"))==NULL){
		printf("文件打开失败！");
		exit(0);
    }
    
    currentc=fgetc(source);
    currents=currentc;
    length=1;
    
    while(!feof(source)){
    	currentc=fgetc(source);
    	if(currentc==currents){
    		length++;
		}
        else{
        	fputc(length,destin);
			fputc(currents,destin);
			currents=currentc;
			length=1;
		}
	}
    fclose(source);
    fclose(destin);
}

void decompress(char *sourcefile,char *destinfile){
	FILE *source,*destin;
	char currentc;
	int i,length;
	
	if((source=fopen(sourcefile,"rb"))==NULL){
		printf("文件打开失败！");
		exit(0);
	}
	
    if((destin=fopen(destinfile,"wb"))==NULL){
		printf("文件打开失败！");
    	exit(0);
	}
	
	while(!feof(source)){
		length=fgetc(source);
		currentc=fgetc(source);		
		for(i=0;i<length;i++){
			fputc(currentc,destin);
			}
		}
	fclose(source);
	fclose(destin);
}


int main(int argc, char* argv[]){
	if(strcmp(argv[2],"-c")==0){
        printf("文件压缩成功！\n");
        compress(argv[1],argv[3]); 
	}
    else if(strcmp(argv[2],"-d")==0){
        printf("文件解压成功!\n");
        decompress(argv[1],argv[3]);
    }  
    return 0;
}

