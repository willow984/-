/*串的操作及KMP算法*/

//串的定长存储结构
typedef struct Str{
    char str[maxSize + 1];
    //maxSize表示串的最大长度，maxSize+1是因为串尾多一个默认结束符'\0'.
    int length;
}Str;

//串的变长存储结构
typedef struct Str{
    char *ch;   
    //该指针指向分配的用来存储串的空间的首地址.
    int length;
}
Str S;      //创建一个变长串结构
S.length = L;       //长度为L
S.ch = (char*)malloc((1 + L) * sizeof(char))    //分配1+L个字符长度的空间，用S的ch分量指向它

int StrAssign(Str &str, char *ch){
    /*串的赋值操作，str是用来接受赋值的串，ch是用来赋值的值*/
    
    /*先判断str是否已经指向一片空间，如果是，则释放这片空间*/
    if (str.ch)  free(str.ch);
    
    /*先求用来赋值的字符串的长度*/
    int len = 0;
    char *c = ch;
    while(*c){
        ++len;
        ++c;    //++c表示指针c往后移动一个存储空间
    }

    /*如果用来赋值的串是空串，则赋值后也是空串*/
    if (len == 0){
        str.ch = NULL;
        str.length = 0;
        return 1
    }

    /*正常赋值操作*/
    else{
        str.ch = ()malloc((1 + len) * sizeof(char));  //先分配空间；
        if (str.ch == NULL)  return 0;  //空间分配失败则返回0；
        else{
            c = ch;
            for(int i = 0; i < len; ++i, ++c){
                str.ch[i] = *c;         //此处*为取值符
            }
            str.length = len;
            return 1;
        }  
    }
}

int StrCompare(Str s1, Str s2){
    /*按照字典顺序比较字符串的大小,返回值的正负表示两个字符的大小关系*/
    
    for(int i = 0; i < s1.length && i < s2.length; ++i){
        if (s1.ch[i] != s2.ch[i])
            return s1.ch[i] - s2.ch[i];
    }

    /*
    若两串完全相同，返回0；
    若在短串结束时两串字符都相同，则长串较大
    */
    return s1.length - s2.length;
}

int StrConnect(Str &str, Str str1, Str str2){
    /*连接两个字符串，生成一个新字符串*/
    
    /*先判断str是否已经指向一片空间，如果是，则释放这片空间*/
    if (str.ch){
        free(str.ch);
        str.ch = NULL;
    }

    /*分配空间，并检查是否分配成功*/
    str.ch = (char*)malloc((1 + str1.length + str2.length) * sizeof(char));
    if(str.ch == NULL)  return 0;

    /*先将str1挪入str*/
    int i = 0;
    while (i < str1.length){
        str.ch[i] = str1.ch[i];
        ++i;
    }

    /*再先将str2挪入str*/
    int j = 0;
    while (j <= str2.length){
    //注意。此处用了<=是讲str2末尾的'\0'一起挪入str中
        str.ch[i+j] = str2.ch[j];
        ++j;
    }

    str.length = str1.length + str2.length；
    //length标记的是纯长度，不包括'\0'，只有分配空间时才要+1.
    return 1;
}

int GetSubString(Str &sub, Str str, int pos, int len){
    /*求串str中，从第pos个位置起，长度为len的字串，存入sub中*/

    /*先判断位置的合法性*/
    if (pos < 0 || pos > str.length || len < 0 || len > str.length - pos)
        return 0;

    /*如果子串sub指针已经指向一片空间，则先释放这片空间*/
    if (sub.ch){
        free(sub.ch);
        sub.ch = NULL;
    }

    /*如果要求len的长度为0，则存入sub的是空串*/
    if (len == 0){
        sub.ch = NULL;
        sub.length = 0;
        return 1;
    }

    /*其余正常取串的操作*/
    else{
        sub.ch = (char*)malloc(sizeof(char) * (1 + len))
        int i = pos;
        int j = 0;
        while (i < pos + len){
            sub.ch[j] = str.ch[i];
            ++i;
            ++j;
        }
        sub.ch[j] = '\0';
        //手动补充结束符
        sub.length = len;
        return 1;
    }
}

int SubIndex(Str S, Str T){
    /*在主串s中定位子串t的位置*/

    int i = 0;
    n = S.length;
    m = T.length;
    while (i < n - m + 1){
        /*i是可以比较的位置*/
        GetSubString(sub, S, i, m);
        /*取当前i位置长度为m的子串*/
        if(StrCompare(sub, T) != 0)
        /*比较*/
            ++i;
            //失败则后移，成功则返回当前位置i；
        else return i;
    }
    return 0;
}

int StrClear(Str &str){
    /*清空串就是先释放当前ch指针指向的空间，然后再让ch指针指向NULL*/
    
    if(str.ch){
        free(str.ch);
        str.ch == NULL;
    }
    str.length = 0;
    return 1;
}
/*-----------------------------简单模式匹配（暴力）----------------------------*/
int Index(Str S, Str T){

    /*S为主串，T为模式串*/
    int i = 1, j = 1;
    while (i < S.length && j < T.length){
        if(S.ch[i] == T.ch[j]){
            ++i; ++j;
        }
        else{
            i = i - j + 2;  //i-j+1是本次比较主串开始的位置，再+1就是下一次起始
            j = 1;
        }
    }
    if (j > T.length) return i - T.length;
    else return 0;
}
/*----------------------------------KMP算法-----------------------------------*/
void GetNext(Str T, int next[]){
    
    /*求模式串T的next数组，T是模式串*/
    
    int i = 1, j = 0;
    next[1] = 0;
    while (i < T.length){
        if (j == 0 || T.ch[i] == T.ch[j]){
            ++i; ++j;
            next[i] = j;
        }
        else j = next[j];
    }
}

void GetNextval(Str T, int nextval[]){
    /*求nextval数组,先求得next数组*/

    int i = 1, j = 0;
    nextval[1] = 0;

    while (i < T.length){
        if (j == 0 || T.ch[i] == T.ch[j]){
            ++i; ++j;
            if (T.ch[i] != T.ch[j]) nextval = j;
            else nextval[i] = nextval[j];
        }
        else j = nextval[j];
    }
}

int KMP(Str S, Str T, int next[]){

    /*S是主串。T是模式串，i是主串指针，j是模式串指针*/
    int i = 1, j = 1;
    
    while (i <= S.length && j <= T.length){
        
        /*若i指向的元素与j指向的元素匹配，或者j为0(即模式串第一个就不匹配)，
          则指针i与j同步后移一位*/
        if (j == 0 || T.ch[j] == S.ch[i]){
            ++i; ++j
        }

        /*若i指向的元素与j指向的元素不匹配，则j回到next[j]标出的元素*/
        else
            j = next[j];    //优化过后的KMP算法用nextval数组
    }

    /*匹配成功则返回位置*/
    if (j > T.length) return i - T.length;  //返回时候原串位置从0开始
    else return 0;
}

/*---------------------------------------------------------------------------*/