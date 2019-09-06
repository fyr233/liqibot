/*
* 语音合成（Text To Speech，TTS）技术能够自动将任意文字实时转换为连续的
* 自然语音，是一种能够在任何时间、任何地点，向任何人提供语音信息服务的
* 高效便捷手段，非常符合信息时代海量数据、动态更新和个性化查询的需求。
*/

#include "stdafx.h"
#include "ifly.h"

int ifly::text_to_speech(const char* src_text, const char* des_path, const char* params)
{
	int          ret = -1;
	FILE*        fp = NULL;
	const char*  sessionID = NULL;
	unsigned int audio_len = 0;
	wave_pcm_hdr wav_hdr = default_wav_hdr;
	int          synth_status = MSP_TTS_FLAG_STILL_HAVE_DATA;

	if (NULL == src_text || NULL == des_path)
	{
		//printf("params is error!\n");
		return ret;
	}
	fopen_s(&fp, des_path, "wb");
	if (NULL == fp)
	{
		//printf("open %s error.\n", des_path);
		return ret;
	}
	/* 开始合成 */
	sessionID = QTTSSessionBegin(params, &ret);
	if (MSP_SUCCESS != ret)
	{
		printf("QTTSSessionBegin failed, error code: %d.\n", ret);
		fclose(fp);
		return ret;
	}
	ret = QTTSTextPut(sessionID, src_text, (unsigned int)strlen(src_text), NULL);
	if (MSP_SUCCESS != ret)
	{
		printf("QTTSTextPut failed, error code: %d.\n", ret);
		QTTSSessionEnd(sessionID, "TextPutError");
		fclose(fp);
		return ret;
	}
	printf("正在合成 ...\n");
	fwrite(&wav_hdr, sizeof(wav_hdr), 1, fp); //添加wav音频头，使用采样率为16000
	while (1)
	{
		/* 获取合成音频 */
		const void* data = QTTSAudioGet(sessionID, &audio_len, &synth_status, &ret);
		if (MSP_SUCCESS != ret)
			break;
		if (NULL != data)
		{
			fwrite(data, audio_len, 1, fp);
			wav_hdr.data_size += audio_len; //计算data_size大小
		}
		if (MSP_TTS_FLAG_DATA_END == synth_status)
			break;
		printf(">");
		Sleep(50); //防止频繁占用CPU
	}
	printf("\n");
	if (MSP_SUCCESS != ret)
	{
		printf("QTTSAudioGet failed, error code: %d.\n", ret);
		QTTSSessionEnd(sessionID, "AudioGetError");
		fclose(fp);
		return ret;
	}
	/* 修正wav文件头数据的大小 */
	wav_hdr.size_8 += wav_hdr.data_size + (sizeof(wav_hdr) - 8);

	/* 将修正过的数据写回文件头部,音频文件为wav格式 */
	fseek(fp, 4, 0);
	fwrite(&wav_hdr.size_8, sizeof(wav_hdr.size_8), 1, fp); //写入size_8的值
	fseek(fp, 40, 0); //将文件指针偏移到存储data_size值的位置
	fwrite(&wav_hdr.data_size, sizeof(wav_hdr.data_size), 1, fp); //写入data_size的值
	fclose(fp);
	fp = NULL;
	/* 合成完毕 */
	ret = QTTSSessionEnd(sessionID, "Normal");
	if (MSP_SUCCESS != ret)
	{
		printf("QTTSSessionEnd failed, error code: %d.\n", ret);
	}

	return ret;
}

int ifly::TextSaveasWav()
{
	if (!voice_name.empty() && !speed.empty() && !volume.empty() && !pitch.empty())
		session_begin_params = "voice_name = " + voice_name + ", text_encoding = gb2312, sample_rate = 441000, speed = " + speed + ", volume = " + volume + ", pitch = " + pitch + ", rdn = 2";

	/* 用户登录 */
	ret = MSPLogin("17356513251", "qazwsx123", login_params); //第一个参数是用户名，第二个参数是密码，第三个参数是登录参数，用户名和密码可在http://www.xfyun.cn注册获取
	if (MSP_SUCCESS != ret)
	{
		//printf("MSPLogin failed, error code: %d.\n", ret);
		MSPLogout();//登录失败，退出登录
		return 0;
	}

	/* 文本合成 */
	ret = text_to_speech(text.c_str(), filename.c_str(), session_begin_params.c_str());

	MSPLogout(); //退出登录
	if (ret)
		return ret;//错误

	return 0;
}