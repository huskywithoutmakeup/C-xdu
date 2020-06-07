#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#pragma pack(1) 
typedef struct myBITMAPFILEHEADER { //定义一个存储头文件数据结构体
 unsigned short bfType;		 //保存图片类型。 'BM'
 unsigned long bfSize; 	     //位图文件的大小，以字节为单位（3-6字节，低位在前）
 unsigned short bfReserved1;//位图文件保留字，必须为0(7-8字节）
 unsigned short bfReserved2;//位图文件保留字，必须为0(9-10字节）
 unsigned long bfOffBits;   //RGB数据偏移地址,位图数据的起始位置，以相对于位图（11-14字节，低位在前）
}BITMAPFILEHEADER;

typedef struct myBITMAPINFOHEADER{ //定义一个存储位图信息的结构体
 unsigned long 	biSize; 		 //本结构所占用字节数（15-18字节）
 unsigned long  biWidth; 	 //位图的宽度，以像素为单位（19-22字节）
 unsigned long  biHeight; 	 //位图的高度，以像素为单位（23-26字节）
 unsigned short biPlanes; 	 //目标设备的级别，必须为1(27-28字节）
 unsigned short biBitCount;  //每个像素所需的位数，必须是1（双色）（29-30字节）,4(16色），8(256色）16(高彩色)或24（真彩色）之一
 unsigned long  biCompression;//位图压缩类型，必须是0（不压缩），（31-34字节）
 //1(BI_RLE8压缩类型）或2(BI_RLE4压缩类型）之一
 unsigned long  biSizeImage;  //位图的大小(其中包含了为了补齐行数是4的倍数而添加的空字节)，以字节为单位（35-38字节）
 unsigned long  biXPelsPerMeter;//位图水平分辨率，每米像素数（39-42字节）
 unsigned long  biYPelsPerMeter;//位图垂直分辨率，每米像素数（43-46字节)
 unsigned long  biClrUsed; 		 //位图实际使用的颜色表中的颜色数（47-50字节）
 unsigned long  biClrImportant; //位图显示过程中重要的颜色数（51-54字节）
}BITMAPINFOHEADER;

void Zoom(double scale,char *a,char *b)
{
    //定义原照片信息结构体
	BITMAPFILEHEADER head;
    BITMAPINFOHEADER info;
    //清空结构体	
    memset(&head,0,sizeof(BITMAPFILEHEADER));
    memset(&info,0,sizeof(BITMAPINFOHEADER));

	
 	FILE *reader=fopen(a,"rb"); //只读
	FILE *writer=fopen(b,"wb");//只写
	
	if(reader==NULL||writer==NULL) //处理文件不存在的情况
	{
	printf("图片打开失败!\n");
	return ;
	}
	//读取原照片的头信息
	fread(&head,sizeof(BITMAPFILEHEADER),1,reader);
	fread(&info,sizeof(BITMAPINFOHEADER),1,reader);

	unsigned int old_width=info.biWidth;//获取原图片的宽
	unsigned int old_height=info.biHeight;//获取原图片的高

	//获取原图片的位图数据
	unsigned char *src_data=(unsigned char *)malloc(old_width*old_height*3);//分配所需内存空间，并返回一个指向它的指针
	fseek(reader,54,SEEK_SET); //随机定位，以字节数为1开始定位，后54位 
	fread(src_data,old_width*old_height*3,1,reader);

	printf("原图片的宽:%d\n",old_width);
	printf("原图片的高:%d\n",old_height);

	//修改原照片的宽高
	unsigned int new_width,new_height;
	printf("新图片的宽:%d \n",(int)scale*old_width);
	printf("新图片的高:%d \n",(int)scale*old_height);
	new_width=(int)scale*old_width;
	new_height=(int)scale*old_height;
	head.bfSize=new_width*new_height*3+54;
	info.biWidth=new_width;
	info.biHeight=new_height;

	//将修改过的头信息写入新照片
	fwrite(&head,sizeof(BITMAPFILEHEADER),1,writer);
	fwrite(&info,sizeof(BITMAPINFOHEADER),1,writer);
	//现在是把内容字节缩小或放大，并且拷贝到put_data 
	int i=0,j=0;
	unsigned long dwsrcX,dwsrcY;
	unsigned char *pucDest;
	unsigned char *pucSrc;
	unsigned char *dest_data=(unsigned char *)malloc(new_width*new_height*3);
	//这里是拷贝原图片的数据信息，但根据缩放倍率的不同，缩小按照比例从范围内抽去像素点，放大则是把像素点按照比列复制在其周围。
	for(i=0;i<new_height;i++)
	{
		dwsrcY=i/scale;
		pucDest=dest_data+i*new_width*3;		
		pucSrc=src_data+dwsrcY*old_width*3;	
		for(j=0;j<new_width;j++)
		{
			dwsrcX=j/scale;
			memcpy(pucDest+j*3,pucSrc+dwsrcX*3,3);//拷贝数据，从源sourec中复制m个字节到目标destination中
 		}
	}
	fseek(writer,54,SEEK_SET);//随机定位，以字节数为1开始定位，后54位 
	fwrite(dest_data,new_width*new_height*3,1,writer);
	printf("图片缩放成功!\n");	
	//释放堆空间,并且关闭文件
	free(dest_data);
	free(src_data);
	fclose(reader);
	fclose(writer);
}
int main(int argc, char* argv[])
{
  	double scale = atof(argv[2])/100.0; 
	Zoom(scale,argv[1],argv[3]);
	return 0;
}
