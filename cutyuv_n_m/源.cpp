#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
//#define _CRT_SECURE_NO_WARNINGS

//#define	IMAGEWIDTH 2048  //图像的宽
//#define	IMAGEHEIGHT 1536    //高

int main(int argc, char *argv[])
{
	//读入参数，共有3个参数
	if (argc != 7)
	{
		printf("Please input infile and outfile!\n");
		exit(-1);
	}

	FILE * input_yuvfile;    //输入YUV文件
	FILE * output_yuvfile;     //输出YUV图像文件
	input_yuvfile = fopen(argv[1], "rb");
	if (NULL == input_yuvfile) //argv[1]应该表示输入文件名
	{
		printf("File input is can't open!\n");
		return -1;
	}
	if (NULL == (output_yuvfile = fopen(argv[2], "wb")))//argv[2]表示输出文件名，那argv[0]呢？
	{
		printf("File output is can't open!\n");
		return -1;
	}
	int IMAGEWIDTH = 1024;
	int IMAGEHEIGHT = 768;
	int startframe = 1;
	int endframe = 1;
	
	IMAGEWIDTH = atoi(argv[3]);
	IMAGEHEIGHT = atoi(argv[4]);
	startframe = atoi(argv[5]);
	endframe = atoi(argv[6]);
	int cframe = endframe - startframe + 1;



	int readsize;
	int dize;
	unsigned char *in_buff; //输入yuv文件在内存中的存放地址
	in_buff = (unsigned char *)malloc(cframe*IMAGEWIDTH*IMAGEHEIGHT*sizeof(unsigned char) * 3 / 2); //malloc函数是一种分配长度为num_bytes字节的内存块的函数
	memset(in_buff, 0, IMAGEWIDTH*IMAGEHEIGHT*sizeof(unsigned char) * 3 / 2);

	////将yuv_buff指针指向的当前位置后面的IMAGEWIDTH*IMAGEHEIGHT*sizeof(unsigned char)*3/2个字节用0代替；也就是初始化
	//memset(yuv_buff, 0, outframe*IMAGEWIDTH*IMAGEHEIGHT*sizeof(unsigned char) * 3 / 2);



	dize = fseek(input_yuvfile, startframe*IMAGEHEIGHT*IMAGEWIDTH * 3 / 2, SEEK_CUR);
	////将input_yuvfile中IMAGEWIDTH*IMAGEHEIGHT*3/2个字节读入到in_buff中，返回读入“1”个字节的个数，成功时返回IMAGEWIDTH*IMAGEHEIGHT*3/2
	readsize = fread(in_buff, 1, cframe*IMAGEWIDTH*IMAGEHEIGHT * 3 / 2, input_yuvfile);
	
	
	//in_buff = in_buff + startframe*IMAGEWIDTH*IMAGEHEIGHT * sizeof(unsigned char) * 3 / 2;
	//memcpy函数的功能是从源in_buff所指的内存地址的起始位置开始拷贝n个字节到目标yuv_buff所指的内存地址的起始位置中
	//memcpy(yuv_buff, in_buff, outframe*IMAGEWIDTH*IMAGEHEIGHT*sizeof(unsigned char) * 3 / 2);


	//fwrite是把内存中yuv_buff的数据写入到文件output_yuvfile，和fread正好相反
	fwrite(in_buff, 1, cframe*IMAGEWIDTH*IMAGEHEIGHT * sizeof(unsigned char)*3 / 2, output_yuvfile);



	free(in_buff);
	in_buff = NULL;



	fclose(input_yuvfile);
	fclose(output_yuvfile);



}