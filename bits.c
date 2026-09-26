/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x|~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return (~((~x)&(~y)))&(~(x&y));  //x^y=(x|y)&(~(x&y)),x|y可由bitAnd反推
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if(!x && !y)return 1;//都是0
    if(!x)return 0;
    if(!y)return 0;
    int sign_x=x>>31;//提取最高位
    int sign_y=y>>31;
    if(!sign_x && !sign_y)return 1;
    if(sign_x && sign_y)return 1;
    return 0;
    
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int a=((v>>16)>0)<<4;
    v=v>>a;
    int b=((v>>8)>0)<<3;
    v=v>>b;
    int c=((v>>4)>0)<<2;
    v=v>>c;
    int d=((v>>2)>0)<<1;
    v=v>>d;
    int e=(v>>1>0);

    return a|b|c|d|e;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    n=n<<3;
    m=m<<3;
    int byte_n=((x>>n)&0xFF)<<m;
    x=x&~(0xFF<<n);//一定要取了n位就马上用掩码清零x（应对m=n情形）
    int byte_m=((x>>m)&0xFF)<<n;
    x=x&~(0xFF<<m);
    
    return x+(byte_n^byte_m);
    
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned ans=0x0;
    int count=32;
    while(count){
        ans=ans<<1;
        unsigned tmp=v-((v>>1)<<1);//括号！
        v=v>>1;
        ans+=tmp;
        count--;//一定要满打满算32次
    }
    return ans;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int mask=0x80000000;//这个本身默认是unsigned int！
    mask=((~(mask>>n))<<1)+1;
    return  (x>>n)&mask;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    //跟log2思想类似，先取反可将判断是否是1转化为判断是否是0
    x=~x;
    int b16=(!(x>>16))<<4;
    x<<=b16;
    int b8=(!(x>>24))<<3;
    x<<=b8;
    int b4=(!(x>>28))<<2;
    x<<=b4;
    int b2=(!(x>>30))<<1;
    x<<=b2;
    int b1=(!(x>>31));
    x<<=b1;
    int b0=(!(x>>31));
    
    return (b16|b8|b4|b2|b1)+b0;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    if(!x)return 0;
    unsigned bias=(1<<7)-1;
    unsigned ans=0;
    unsigned orgin;
    unsigned tmp=x;//x=0x80000000=-2147483648时取倒数会溢出int
    unsigned sign=tmp&0x80000000;
    //处理负数
    if(x<0){
        tmp=(~tmp)+1; 
    }
    orgin=tmp;
    
    ans|=sign;
    
    //计算阶数
    unsigned exp=0;
    while(tmp>=2){
        tmp>>=1;
        exp++;
    }
    unsigned fraction=orgin-(tmp<<exp);//有可能发生隐式类型转化
    unsigned frac;
    //舍入问题
    if(exp<23){
        frac=fraction<<(23-exp);
    }else{
        int shift=exp-23;
        frac=fraction>>shift;
        unsigned rest=fraction-(frac<<shift);//unsigned rest=fraction&((<<shift)-1);
        unsigned half=tmp<<(shift-1);

        if(rest+(frac&1)>half)frac++;
        

        // if(frac>>23){
        //     exp++;
        //     frac=0;
        // }

    }
    ans+=((exp+bias)<<23)+frac;
    return ans;





}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign=uf&0x80000000;
    unsigned exp=(uf>>23)&0xFF;
    unsigned frac=uf&0x7FFFFF;
    if(exp==0xFF)return uf;
    if(exp==0)frac<<=1;//非格式化的才进位
    else{//格式化的直接给阶数+1
        exp++;
    }
    unsigned ans=0;
    ans|=sign;
    ans+=(exp<<23)+frac;
    return ans;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    
    unsigned sign=uf2&0x80000000;
    unsigned exp=(uf2>>20)&0x7FF;//注意移位符不要漏!000000
    unsigned frac1=(uf2&0xFFFFF)|0x100000;//把小数点前面的一起带上
    unsigned frac2=uf1;
    int flag=1;
    unsigned ans;
    if(sign>>31)flag=-1;
    //判断exp正负
    //exp<0
    if(exp<1023){
        return 0;
    }
    exp-=1023;
    if(exp>30){
        return 0x80000000;//正负溢出都是overflow,不是underflow!
        
    }
    if(exp<=20){
        ans=frac1>>(20-exp);
    }else{
        ans=(frac1<<(exp-20))|(frac2>>(52-exp));
    }
    if (flag>0)return ans;
    ans=(~ans)+1;
    return ans;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if(x>127)return 0x7F800000;//+INF的float表示,exp的最大值为254=127+127（255=0xFF有其他用）
    if(x<-149)return 0;//太小了，都不能用denormal了
    if(x<-126)return 1<<(x+149);//x+127都小于等于0,用denormal表示
    return (x+127)<<23;
}
