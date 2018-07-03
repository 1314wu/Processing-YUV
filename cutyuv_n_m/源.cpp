#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
//#define _CRT_SECURE_NO_WARNINGS

//#define	IMAGEWIDTH 2048  //ͼ��Ŀ�
//#define	IMAGEHEIGHT 1536    //��

int main(int argc, char *argv[])
{
	//�������������3������
	if (argc != 7)
	{
		printf("Please input infile and outfile!\n");
		exit(-1);
	}

	FILE * input_yuvfile;    //����YUV�ļ�
	FILE * output_yuvfile;     //���YUVͼ���ļ�
	input_yuvfile = fopen(argv[1], "rb");
	if (NULL == input_yuvfile) //argv[1]Ӧ�ñ�ʾ�����ļ���
	{
		printf("File input is can't open!\n");
		return -1;
	}
	if (NULL == (output_yuvfile = fopen(argv[2], "wb")))//argv[2]��ʾ����ļ�������argv[0]�أ�
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
	unsigned char *in_buff; //����yuv�ļ����ڴ��еĴ�ŵ�ַ
	in_buff = (unsigned char *)malloc(cframe*IMAGEWIDTH*IMAGEHEIGHT*sizeof(unsigned char) * 3 / 2); //malloc������һ�ַ��䳤��Ϊnum_bytes�ֽڵ��ڴ��ĺ���
	memset(in_buff, 0, IMAGEWIDTH*IMAGEHEIGHT*sizeof(unsigned char) * 3 / 2);

	////��yuv_buffָ��ָ��ĵ�ǰλ�ú����IMAGEWIDTH*IMAGEHEIGHT*sizeof(unsigned char)*3/2���ֽ���0���棻Ҳ���ǳ�ʼ��
	//memset(yuv_buff, 0, outframe*IMAGEWIDTH*IMAGEHEIGHT*sizeof(unsigned char) * 3 / 2);



	dize = fseek(input_yuvfile, startframe*IMAGEHEIGHT*IMAGEWIDTH * 3 / 2, SEEK_CUR);
	////��input_yuvfile��IMAGEWIDTH*IMAGEHEIGHT*3/2���ֽڶ��뵽in_buff�У����ض��롰1�����ֽڵĸ������ɹ�ʱ����IMAGEWIDTH*IMAGEHEIGHT*3/2
	readsize = fread(in_buff, 1, cframe*IMAGEWIDTH*IMAGEHEIGHT * 3 / 2, input_yuvfile);
	
	
	//in_buff = in_buff + startframe*IMAGEWIDTH*IMAGEHEIGHT * sizeof(unsigned char) * 3 / 2;
	//memcpy�����Ĺ����Ǵ�Դin_buff��ָ���ڴ��ַ����ʼλ�ÿ�ʼ����n���ֽڵ�Ŀ��yuv_buff��ָ���ڴ��ַ����ʼλ����
	//memcpy(yuv_buff, in_buff, outframe*IMAGEWIDTH*IMAGEHEIGHT*sizeof(unsigned char) * 3 / 2);


	//fwrite�ǰ��ڴ���yuv_buff������д�뵽�ļ�output_yuvfile����fread�����෴
	fwrite(in_buff, 1, cframe*IMAGEWIDTH*IMAGEHEIGHT * sizeof(unsigned char)*3 / 2, output_yuvfile);



	free(in_buff);
	in_buff = NULL;



	fclose(input_yuvfile);
	fclose(output_yuvfile);



}