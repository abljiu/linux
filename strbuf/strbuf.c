#include "strbuf.h"


//初始化函数
void strbuf_init(struct strbuf *sb, size_t alloc);
void strbuf_init(struct strbuf *sb, size_t alloc)
{
  sb->len=0;
  sb->alloc=alloc;
  sb->buf=(char*)malloc((alloc+1)*sizeof(char));
}

//填充函数
void strbuf_attach(struct strbuf *sb, void *str, size_t len, size_t alloc);
void strbuf_attach(struct strbuf *sb, void *str, size_t len, size_t alloc)
{
  sb->len=len;
  sb->alloc=alloc;
  sb->buf=str;
  sb->buf[len]='\0';
}

//释放结构体内存
void strbuf_release(struct strbuf *sb);
void strbuf_release(struct strbuf *sb)
{
  free(sb->buf);
}

//交换两个strbuf
void strbuf_swap(struct strbuf *a, struct strbuf *b);
void strbuf_swap(struct strbuf *a, struct strbuf *b)
{
  int tl,ta;
  char*tmp;
  
  tl=a->len;
  a->len=b->len;
  b->len=tl;

  ta=a->alloc;
  a->alloc=b->alloc;
  b->alloc=ta;

  tmp=a->buf;
  a->buf=b->buf;
  b->buf=tmp;
}

//取出内存并重新设置大小为sz
char *strbuf_detach(struct strbuf *sb, size_t *sz);
char *strbuf_detach(struct strbuf *sb, size_t *sz)
{
  char*p= sb->buf;
  *sz=sb->alloc;
  strbuf_init(sb,0);
  return p;
}

//比较两个内存是否相同
strbuf_cmp(const struct strbuf *first, const struct strbuf *second);
strbuf_cmp(const struct strbuf *first, const struct strbuf *second)
{
  int t=strcmp(first,second);
  return t;
}	

//清空结构体
void strbuf_reset(struct strbuf *sb);
void strbuf_reset(struct strbuf *sb)
{
  int i=0;
  while(sb->buf[i]!='\0')
  {
   sb->buf[i]='\0';
   i++; 
  }
}

//确保至少extra个字节可用
void strbuf_grow(struct strbuf *sb, size_t extra);
void strbuf_grow(struct strbuf *sb, size_t extra)
{
      if(sb -> len + extra < sb -> alloc) return;
    sb -> buf = (char*)realloc(sb -> buf, sb -> len + extra + 1);
    sb -> alloc = sb->len + extra + 1;
}

//向 sb 追加长度为 len 的数据 data
void strbuf_add(struct strbuf *sb, const void *data, size_t len);
void strbuf_add(struct strbuf *sb, const void *data, size_t len)
{
  if(sb->len+len>sb->alloc)
  {
    strbuf_grow(sb,len)
  }
}