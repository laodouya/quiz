#include <string.h>
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
#include "libavutil/dict.h"

static int open_input_file(AVFormatContext **fmt_ctx_ptr, const char *filename)
{
    int err;
    AVFormatContext *fmt_ctx = NULL;
    
    AVDictionary *format_opts = NULL;
    av_dict_set(&format_opts, "scan_all_pmts", "1", AV_DICT_DONT_OVERWRITE);
    AVInputFormat *iformat = NULL; 
    
    if ((err = avformat_open_input(&fmt_ctx, filename,
                                   iformat, &format_opts)) < 0) { 
        return err; 
    }    
    
    *fmt_ctx_ptr = fmt_ctx;
    return 0;
}

static void close_input_file(AVFormatContext **ctx_ptr)
{
    int i;
    AVFormatContext *fmt_ctx = *ctx_ptr;

    /* close decoder for each stream */
    for (i = 0; i < fmt_ctx->nb_streams; i++) 
        if (fmt_ctx->streams[i]->codec->codec_id != AV_CODEC_ID_NONE)
            avcodec_close(fmt_ctx->streams[i]->codec);

    avformat_close_input(ctx_ptr);
}


int main(int argc, char **argv)
{
    av_register_all();
    avformat_network_init();
    
    AVFormatContext *fmt_ctx;
    const char* input_filename = argv[1];
    int ret = open_input_file(&fmt_ctx, input_filename);
    if (0 == ret)
    {
        printf("format name: %s\n",fmt_ctx->iformat->name);
        close_input_file(&fmt_ctx);
    } 
    avformat_network_deinit();
    return 0;
}
