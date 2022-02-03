#include "cachelab.h"
#include <stdlib.h>
#include <unistd.h> 
#include <limits.h>// 各种宏定义 如INT_MAX
#include <getopt.h>
#include <string.h>
#include <stdio.h>
int h,v,s,E,b,S;// S 代表set，E代表每个set的cache line行数,s,b,代表两个偏移量
int hit_count,miss_count,eviction_count;
char t[1000];
typedef struct
{
    int valid_bits;
    int tag;
    int stamp;
}cache_line,*cache_asso,**cache;
cache _cache_=NULL;

void printUsage()
{
    printf("Usage: ./csim-ref [-hv] -s <num> -E <num> -b <num> -t <file>\n"
            "Options:\n"
            "  -h         Print this help message.\n"
            "  -v         Optional verbose flag.\n"
            "  -s <num>   Number of set index bits.\n"
            "  -E <num>   Number of lines per set.\n"
            "  -b <num>   Number of block offset bits.\n"
            "  -t <file>  Trace file.\n\n"
            "Examples:\n"
            "  linux>  ./csim-ref -s 4 -E 1 -b 4 -t traces/yi.trace\n"
            "  linux>  ./csim-ref -v -s 8 -E 2 -b 4 -t traces/yi.trace\n");
}
void init_cache()
{
    _cache_=(cache)malloc(sizeof(cache_asso) * S);
    for(int i = 0;i < S;++i)
    {
        _cache_[i] = (cache_asso)malloc(sizeof(cache_line) * E);
            for(int j=0 ;j<E;++j)
            {
                _cache_[i][j].valid_bits=0;
                _cache_[i][j].tag=-1;
                _cache_[i][j].stamp=0;
            }
    }
}
void update(unsigned int address)
{
    int set_index_add=(address >> b) & ((-1u)>>(64 - s));// s 位是组索引,b为块偏移
    int tag_add = address >> (b+s);
    int max_stamp = INT_MIN;
    int max_stamp_index = -1;
    for(int i = 0; i < E;++i)
    {
        if(_cache_[set_index_add][i].tag==tag_add && _cache_[set_index_add][i].valid_bits == 1)
        {  
            _cache_[set_index_add][i].stamp=0;//tag相同,就hit 时间戳置零
            ++hit_count;
            return;
        }
    }
    for(int i = 0;i < E;++i)
    {
        if(_cache_[set_index_add][i].valid_bits == 0)
        {
            _cache_[set_index_add][i].valid_bits=1;
            _cache_[set_index_add][i].tag=tag_add;
            _cache_[set_index_add][i].stamp=0;
            miss_count++;
            return;
        }
    }
    eviction_count++;//没有空行 又没有hit 那就需要替换
    miss_count++;
    for(int i = 0;i < E;++i)
    {
        if( _cache_[set_index_add][i].stamp > max_stamp)//找到同一个set 中cache line 时间戳最大的line 替换掉
        {
            max_stamp = _cache_[set_index_add][i].stamp;
            max_stamp_index = i;
        }
    }
    _cache_[set_index_add][max_stamp_index].tag=tag_add;
    _cache_[set_index_add][max_stamp_index].stamp=0;
    return;

}
void update_stamp()
{
    for (int i = 0;i < S;++i)
    {
        for(int j = 0;j < E;++j)
        {
            if(_cache_[i][j].valid_bits==1)
            {
                ++_cache_[i][j].stamp; // 每次更新时间戳+1，时间戳大的就表示很久没替换过LRU
            }//LRU 选择那个最后被访问的时间距离现在最远的块 以为很久没被访问过的块很久就没用过
        }
    }
}
void parse_trace()
{
    FILE * fp = fopen(t,"r");
    if(fp == NULL)
    {
        printf("Opening file error");
        exit(-1);
    }
    char op;
    unsigned int address;
    int size;
    while(fscanf(fp,"%c %x,%d\n",&op,&address,&size)>0)//data的size 不用管这里只是模拟cache 不用存数据
    {
        switch (op)
        {
        case 'I':continue;
        case 'L'://load data
            update(address);
            break;
        case 'M'://modified data = load data + store data
            update(address);
        //因为M要执行load 和store两个操作所以这里无break,执行完这个update，会继续执行下面的S的update操作
        case 'S':
            update(address);
        default:
            break;
        }
        //每次执行完操作 更新时间戳
        update_stamp();
    }
    fclose(fp);
    for(int i = 0; i < S;++i)
    {
        free(_cache_[i]);
        _cache_[i]=NULL;
    }
    free(_cache_);
    _cache_=NULL;

}
int main(int argc,char * argv[])
{
    h=v=0;//h=help flag that prints usage info,v=verbose flag that displays trace info
    hit_count=miss_count=eviction_count=0;
    int opt;
    while(-1!=(opt=(getopt(argc,argv,"hvs:E:b:t:"))))
    {
        switch(opt)
        {
            case 'v':
                v=1;
                printUsage();
                break;
            case 'h':
                h=1;
                printUsage();
                break;
            case 'E': 
                E = atoi(optarg);
                break;
            case 's':
                s = atoi(optarg);
                break;
            case 'b':
                b = atoi(optarg);
                break;
            case 't':
                strcpy(t,optarg);
                break;
            default:
                printUsage();
                break;
        }
    }
    if(s<=0 || E <=0 || b <=0 || t==NULL)
        return -1;
    S = 1 << s;// S = 2^s
    init_cache();
    parse_trace();
    printSummary(hit_count, miss_count, eviction_count);
    return 0;
}
