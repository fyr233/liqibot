#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <errno.h>
#include <string>

#include "qtts.h"
#include "msp_cmn.h"
#include "msp_errors.h"


#ifdef _WIN64
#pragma comment(lib,"../libs/msc_x64.lib")//x64
#else
#pragma comment(lib,"../libs/msc.lib")//x86
#endif


/* wav��Ƶͷ����ʽ */
typedef struct _wave_pcm_hdr
{
	char            riff[4];                // = "RIFF"
	int				size_8;                 // = FileSize - 8
	char            wave[4];                // = "WAVE"
	char            fmt[4];                 // = "fmt "
	int				fmt_size;				// = ��һ���ṹ��Ĵ�С : 16

	short int       format_tag;             // = PCM : 1
	short int       channels;               // = ͨ���� : 1
	int				samples_per_sec;        // = ������ : 8000 | 6000 | 11025 | 16000
	int				avg_bytes_per_sec;      // = ÿ���ֽ��� : samples_per_sec * bits_per_sample / 8
	short int       block_align;            // = ÿ�������ֽ��� : wBitsPerSample / 8
	short int       bits_per_sample;        // = ����������: 8 | 16

	char            data[4];                // = "data";
	int				data_size;              // = �����ݳ��� : FileSize - 44 
} wave_pcm_hdr;


class ifly
{
private:
	/* Ĭ��wav��Ƶͷ������ */
	wave_pcm_hdr default_wav_hdr =
	{
	{ 'R', 'I', 'F', 'F' },
	0,
	{ 'W', 'A', 'V', 'E' },
	{ 'f', 'm', 't', ' ' },
	16,
	1,
	1,
	16000,
	32000,
	2,
	16,
	{ 'd', 'a', 't', 'a' },
	0
	};

	int         ret = MSP_SUCCESS;
	const char* login_params = "appid = 59285cdd, work_dir = .";//��¼����,appid��msc���,��������Ķ�
																/*
																* rdn:           �ϳ���Ƶ���ַ�����ʽ
																* volume:        �ϳ���Ƶ������
																* pitch:         �ϳ���Ƶ������
																* speed:         �ϳ���Ƶ��Ӧ������
																* voice_name:    �ϳɷ�����
																* sample_rate:   �ϳ���Ƶ������
																* text_encoding: �ϳ��ı������ʽ
																*
																*/
public:
	std::string session_begin_params = "voice_name = xiaoqi, text_encoding = gb2312, sample_rate = 16000, speed = 65, volume = 50, pitch = 47, rdn = 2";
	std::string filename = "data\\record\\iflytexttosound.wav"; //�ϳɵ������ļ�����
	std::string text = "";//�ı�����

	std::string voice_name = "xiaoqi";
	std::string speed = "65";
	std::string volume = "50";
	std::string pitch = "47";
	//std::string rdn = "2";

private:
	/* �ı��ϳ� */
	int text_to_speech(const char* src_text, const char* des_path, const char* params);

public:
	int TextSaveasWav();

};

