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


/* wav音频头部格式 */
typedef struct _wave_pcm_hdr
{
	char            riff[4];                // = "RIFF"
	int				size_8;                 // = FileSize - 8
	char            wave[4];                // = "WAVE"
	char            fmt[4];                 // = "fmt "
	int				fmt_size;				// = 下一个结构体的大小 : 16

	short int       format_tag;             // = PCM : 1
	short int       channels;               // = 通道数 : 1
	int				samples_per_sec;        // = 采样率 : 8000 | 6000 | 11025 | 16000
	int				avg_bytes_per_sec;      // = 每秒字节数 : samples_per_sec * bits_per_sample / 8
	short int       block_align;            // = 每采样点字节数 : wBitsPerSample / 8
	short int       bits_per_sample;        // = 量化比特数: 8 | 16

	char            data[4];                // = "data";
	int				data_size;              // = 纯数据长度 : FileSize - 44 
} wave_pcm_hdr;


class ifly
{
private:
	/* 默认wav音频头部数据 */
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
	const char* login_params = "appid = 59285cdd, work_dir = .";//登录参数,appid与msc库绑定,请勿随意改动
																/*
																* rdn:           合成音频数字发音方式
																* volume:        合成音频的音量
																* pitch:         合成音频的音调
																* speed:         合成音频对应的语速
																* voice_name:    合成发音人
																* sample_rate:   合成音频采样率
																* text_encoding: 合成文本编码格式
																*
																*/
public:
	std::string session_begin_params = "voice_name = xiaoqi, text_encoding = gb2312, sample_rate = 16000, speed = 65, volume = 50, pitch = 47, rdn = 2";
	std::string filename = "data\\record\\iflytexttosound.wav"; //合成的语音文件名称
	std::string text = "";//文本内容

	std::string voice_name = "xiaoqi";
	std::string speed = "65";
	std::string volume = "50";
	std::string pitch = "47";
	//std::string rdn = "2";

private:
	/* 文本合成 */
	int text_to_speech(const char* src_text, const char* des_path, const char* params);

public:
	int TextSaveasWav();

};

