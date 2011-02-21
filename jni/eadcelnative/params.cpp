#include "eadcelnative/params.h"
#include "iva/common/commonDefs.h"

void setVideoParams(EncodeVideoParams ** paramsVideo){
//		formato de pixel:
//		padrao:IvaPixFmt::FMT_YUV420P
//		possiveis:
//	    FMT_NONE = 0,  ///< formato de pixel não válido
//	    FMT_YUV420P,   ///< planar YUV 4:2:0, 12bpp, (1 Cr & Cb sample per 2x2 Y samples)
//	    FMT_RGB24,     ///< packed RGB 8:8:8, 24bpp, RGBRGB...
//	    FMT_RGB32,
//	    FMT_BGR32,
//	    FMT_YUV422P,   ///< planar YUV 4:2:2, 16bpp, (1 Cr & Cb sample per 2x1 Y samples)
//	    FMT_YUV411P,   ///< planar YUV 4:1:1, 12bpp, (1 Cr & Cb sample per 4x1 Y samples)
//	    FMT_RGB555,
//	    FMT_DVSD,      ///< DV25
//	    FMT_COUNT      ///< para fazer laços com o enum
//		(*paramsVideo)->setPixelsFormat(IvaPixFmt::FMT_YUV420P);

//		codec:
//		padrao:COMMON_CODEC_NONE
//		possiveis:
//		COMMON_VIDEO_DEFAULT_CODEC            COMMON_CODEC_VIDEO_MPEG4  ///< Codec padrão de vídeo
//		COMMON_CODEC_NONE                   0        ///< Codec não especificado
//		COMMON_CODEC_VIDEO_MPEG2            10       ///< Codec de vídeo: MPEG-2
//		COMMON_CODEC_VIDEO_MPEG4            11       ///< Codec de vídeo: MPEG-4
//		COMMON_CODEC_VIDEO_H264             12       ///< Codec de vídeo: H.264
//		COMMON_CODEC_VIDEO_DV25             13       ///< Codec de vídeo: DV25
		(*paramsVideo)->setCodec(COMMON_CODEC_VIDEO_MPEG4);

//		bitrate:
//		padrao:COMMON_VIDEO_DEFAULT_BITRATE
//		possiveis:
//		COMMON_VIDEO_DEFAULT_BITRATE          1400000                   ///< Bitrate padrão de vídeo (em bit/s)
//		segundo documentacao, qualquer valor entre 100000 e 4000000
		(*paramsVideo)->setBitRate(256000);

//		framerate:
//		padrao:COMMON_VIDEO_DEFAULT_FPS
//		possiveis:
//		COMMON_VIDEO_DEFAULT_FPS              30                        ///< FPS padrão dos vídeos
//		COMMON_CODEC_VIDEO_MIN_FPS          2       ///< Menor fps permitido no sistema
//		COMMON_CODEC_VIDEO_MAX_FPS          60      ///< Maior fps permitido no sistema
//		segundo documentacao, qualquer valor entre 1 e 60
		(*paramsVideo)->setFrameRate(15);

//		width:
//		padrao:COMMON_VIDEO_DEFAULT_WIDTH
//		possiveis:
//		COMMON_VIDEO_DEFAULT_WIDTH            720                       ///< Largura padrão dos vídeos
//		COMMON_CODEC_VIDEO_MIN_WIDTH        180     ///< Menor largura de vídeo permitida
//		COMMON_CODEC_VIDEO_MAX_WIDTH        1440    ///< Maior largura de vídeo permitida
//		segundo documentacao, 1280, 720 e 360
		(*paramsVideo)->setWidth(320);

//		heigth:
//		padrao:COMMON_VIDEO_DEFAULT_HEIGHT
//		possiveis:
//		COMMON_VIDEO_DEFAULT_HEIGHT           480                       ///< Altura padrão dos vídeos
//		COMMON_CODEC_VIDEO_MIN_HEIGHT       120     ///< Menor altura de vídeo permitida
//		COMMON_CODEC_VIDEO_MAX_HEIGHT       960     ///< Maior altura de vídeo permitida
//		segundo documentacao, 720, 480 e 240
		(*paramsVideo)->setHeight(240);

//		gop:
//		padrao:COMMON_VIDEO_DEFAULT_GOP
//		possiveis:
//		COMMON_VIDEO_DEFAULT_GOP              12                        ///< GOP padrão para cod de vídeo
//		(*paramsVideo)->setGopSize(32);

}

void setAudioParams(EncodeAudioParams ** paramsAudio){
	(*paramsAudio)->setCodec(COMMON_CODEC_AUDIO_MP2);
	(*paramsAudio)->setChannels(1);
	(*paramsAudio)->setBitRate(64000);
	(*paramsAudio)->setSampleRate(22050);
}
