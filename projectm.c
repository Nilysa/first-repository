#include<stdio.h>
#include<string.h>
#include<limits.h>
#include<stdlib.h>
#include<ctype.h>
int j;
int array[32]={0};
int sobat[8]={2,2,2,2,2,2,2,2};
int stack[50];
//sobatvaziatha
void parity_flag(int result){
    int count = 0;
    while(result>0){
        if(result%2==1){
            count++;
        }
        result/=2;
    }
    if(count%2==1){
        sobat[0]=1;
    }
    else{
        sobat[0]=0;
    }
}
void zero_flag(int result){
    if(result==0){
        sobat[1]=1;
    }
    else{
        sobat[1]=0;
    }
}
void sign_flag(int result){
    if(result<0){
        sobat[2]=1;
    }
    else{
        sobat[2]=0;
    }
}
void overflow_flag_sum(int result,int a,int b){
    if(a>0 && b>0 && result<0 || a<0 && b<0 && result>0){
        sobat[5]=1;
    }
    else{
        sobat[5]=0;
    }
}
void overflow_flag_sub(int result,int a,int b){
    if(a>0 && b<0 && result<0 || a<0 && b>0 && result>0){
        sobat[5]=1;
    }
    else{
        sobat[5]=0;
    }
}
void overflow_flag_product(int result,int a,int b){
    /*if((a>0 && b>0 && result<0) || (a<0 && b<0 && result<0) || (a>0 && b<0 && result>0) || (a<0 && b>0 && result>0)){
        sobat[5]=1;
    }
    else{
        sobat[5]=0;
    }*/
    if(a != 0 && (result/a) != b){
        sobat[5]=1;
    }
    else{
        sobat[5]=0;
    }
}
//functions
void PUSH(int n){
    for(int i=0;i<50;i++){
        stack[i+1]=stack[i];
    }
    stack[0]=sobat[n];
}
void POP(int n){
    sobat[n]=stack[0];
    for(int i=0;i<50;i++){
        stack[i]=stack[i+1];
    }
}
void ADD(int add,int srt,int srs){
    array[add]=array[srt]+array[srs];
    parity_flag(array[add]);
    zero_flag(array[add]);
    sign_flag(array[add]);
    overflow_flag_sum(array[add],array[srt],array[srs]);
}
void SUB(int sub,int srt,int srs){
    array[sub]=array[srt]-array[srs];
    parity_flag(array[sub]);
    zero_flag(array[sub]);
    sign_flag(array[sub]);
    overflow_flag_sub(array[sub],array[srt],array[srs]);
}
void AND(int and,int srt,int srs){
    array[and]=array[srt]&array[srs];
    parity_flag(array[and]);
    zero_flag(array[and]);
    sign_flag(array[and]);
}
void XOR(int xor,int srt,int srs){
    array[xor]=array[srt]^array[srs];
    parity_flag(array[xor]);
    zero_flag(array[xor]);
    sign_flag(array[xor]);
}
void OR(int or,int srt,int srs){
    array[or]=array[srt]|array[srs];
    parity_flag(array[or]);
    zero_flag(array[or]);
    sign_flag(array[or]);
}
void ADDI(int addi,int srs,int imm){
    array[addi]=array[srs]+imm;
    parity_flag(array[addi]);
    zero_flag(array[addi]);
    sign_flag(array[addi]);
    overflow_flag_sum(array[addi],array[srs],imm);
}
void SUBI(int subi,int srs,int imm){
    array[subi]=array[srs]-imm;
    parity_flag(array[subi]);
    zero_flag(array[subi]);
    sign_flag(array[subi]);
    overflow_flag_sub(array[subi],array[srs],imm);
}
void ANDI(int andi,int srs,int imm){
    array[andi]=array[srs]&imm;
    parity_flag(array[andi]);
    zero_flag(array[andi]);
    sign_flag(array[andi]);
}
void XORI(int xori,int srs,int imm){
    array[xori]=array[srs]^imm;
    parity_flag(array[xori]);
    zero_flag(array[xori]);
    sign_flag(array[xori]);
}
void ORI(int ori,int srs,int imm){
    array[ori]=array[srs]|imm;
    parity_flag(array[ori]);
    zero_flag(array[ori]);
    sign_flag(array[ori]);
}
void MOV(int srt, int imm){
    array[srt] = imm;
}
void SWP(int srs,int srt){
    int t=array[srs];
    array[srs]=array[srt];
    array[srt]=t;
}
void DUMP_REGS(){
    printf("\narray:");
    for(int i=0;i<32;i++){
        printf("%d ",array[i]);
    }
    printf("\nsobat vaziat ha:");
    for(int i=0;i<8;i++){
        printf("%d ",sobat[i]);
    }
}
void DUMP_REGS_F(){
    FILE *file;
    file = fopen("regs.text","w");
    if(file == NULL){
        printf("error");
    }
    else{
        fprintf(file,"\nsobat vaziat ha:");
        for(int i =0;i<8;i++){
            fprintf(file,"%d ",sobat[i]);
        }
        fprintf(file,"\narray:");
        for(int i =0;i<32;i++){
            fprintf(file,"%d",array[i]);
        }
    }
    fclose(file);
}
void INPUT(){
    scanf("%d",&array[0]);
}
void OUTPUT(){
    printf("%d",array[0]);
}
void DIV(int srs,int srt){
    int quotient=array[srt]/array[srs];
    int remainder=array[srt]%array[srs];
    array[srt]=quotient;
    array[srs]=remainder;
    parity_flag(array[srt]);
    zero_flag(array[srt]);
    sign_flag(array[srt]);
}
void MULL(int srt,int srs){
    int product=array[srt]*array[srs];
    //array[srt]=product <<4;
    //array[srs]=product >>4;
    int temp1 = 15;
    int temp2 = 240;
    array[srt] = product & temp2;
    array[srs] = product & temp1;
    array[srt]=array[srt]>>4;
    parity_flag(product);
    zero_flag(product);
    sign_flag(product);
    overflow_flag_product(product,array[srt],array[srs]);
}
//function ends here
int main(int argc,char* argv[]){
    printf("the file name is\n: %s",argv[1]);

    //char name[100];
    char buffer[1000];
    //printf("enter name:");
    //scanf("%s",name);
    FILE *enter;
    if(argc<2){
        enter=fopen("in.txt","r");
    }
    else{
        enter=fopen(argv[1],"r");
    }
    //enter= fopen(name,"r");

    while(fscanf(enter,"%[^\n]\ns",buffer) != EOF){
        int a,b,c;
        for(int i=0;i<sizeof(buffer);i++){
            buffer[i]=toupper(buffer[i]);
        }
        char command[15]={'\0'};
        for(j=0;buffer[j]!=' ';j++){
            command[j]=buffer[j];
        }
        //command[j+1]='\0';
        if(strcmp(command,"EXIT") == 0){
            exit(0);
        }
        else if(strcmp(command,"ADD") == 0){
            sscanf(buffer,"ADD S%d, S%d, S%d",&a,&b,&c);
            ADD(a,b,c);
        }
        else if(strcmp(command,"SUB") == 0){
            sscanf(buffer,"SUB S%d, S%d, S%d",&a,&b,&c);
            SUB(a,b,c);
        }
        else if(strcmp(command,"AND") == 0){
            sscanf(buffer,"AND S%d, S%d, S%d",&a,&b,&c);
            AND(a,b,c);
        }
        else if(strcmp(command,"XOR") == 0){
            sscanf(buffer,"XOR S%d, S%d, S%d",&a,&b,&c);
            XOR(a,b,c);
        }
        else if(strcmp(command,"OR") == 0){
            sscanf(buffer,"OR S%d, S%d, S%d",&a,&b,&c);
            OR(a,b,c);
        }
        else if(strcmp(command,"ADDI") == 0){
            sscanf(buffer,"ADDI S%d, S%d, %d",&a,&b,&c);
            ADDI(a,b,c);
        }
        else if(strcmp(command,"SUBI") == 0){
            sscanf(buffer,"SUBI S%d, S%d, %d",&a,&b,&c);
            SUBI(a,b,c);
        }
        else if(strcmp(command,"ANDI") == 0){
            sscanf(buffer,"ANDI S%d, S%d, %d",&a,&b,&c);
            ANDI(a,b,c);
        }
        else if(strcmp(command,"XORI") == 0){
            sscanf(buffer,"XORI S%d, S%d, %d",&a,&b,&c);
            XORI(a,b,c);
        }
        else if(strcmp(command,"ORI") == 0){
            sscanf(buffer,"ORI S%d, S%d, %d",&a,&b,&c);
            ORI(a,b,c);
        }
        else if(strcmp(command,"MOV") == 0){
            if(buffer[8] == 'S' || buffer[9] == 'S'){
                sscanf(buffer, "MOV S%d, S%d", &a, &b);
                MOV(a, array[b]);
            }
            else{
                sscanf(buffer, "MOV S%d, %d", &a, &b);
                MOV(a, b);
            }
        }
        else if(strcmp(command,"SWP") == 0){
            sscanf(buffer,"SWP S%d, S%d",&a,&b);
            SWP(a,b);
        }
        else if(strcmp(command,"DUMP_REGS") == 0){
            DUMP_REGS();
        }
        else if(strcmp(command,"DUMP_REGS_F") == 0){
            DUMP_REGS_F();
        }
        else if(strcmp(command,"INPUT") == 0){
            INPUT();
        }
        else if(strcmp(command,"OUTPUT") == 0){
            OUTPUT();
        }
        else if(strcmp(command,"JMP") == 0){
            int countlines=1,countchars=0;
            sscanf(buffer, "JMP %d",&a);
            rewind(enter);
            while(countlines != a){
                countchars++;
                if(fgetc(enter) == '\n'){
                    countlines++;
                }
            }
            fseek(enter,countchars+1,SEEK_SET);
            fscanf(enter, "%[^\n]\n",buffer);
            for(j=0;buffer[j] != ' ';j++){
                command[j]=buffer[j];
            }
            command[j]='\0';
        }
        else if(strcmp(command,"SKIE") == 0){
            sscanf(buffer, "SKIE S%d, S%d", &a, &b);
            if(array[a]==array[b]){
                fscanf(enter,"%[^\n]\n",buffer);
                // for(j=0;buffer[j] != ' ';j++){
                //     command[j]=buffer[j];
                // }
                //command[j]='\0';
            }
        }
        else if(strcmp(command,"DIV") == 0){
            if(sscanf(buffer,"DIV S%d, S%d",&a,&b)){
                DIV(a,b);
            }
        }
        else if(strcmp(command,"MULL") == 0){
            if(sscanf(buffer,"MULL S%d, S%d",&a,&b)){
                MULL(a,b);
            }
        }
        else if(strcmp(command,"PUSH") == 0){
            if(sscanf(buffer,"PUSH S%d",&a)){
                PUSH(a);
            }
        }
        else if(strcmp(command,"POP") == 0){
            if(sscanf(buffer,"POP S%d",&a)){
                POP(a);
            }
        }
        else{
            printf("\nwrong input");
        }
    }
    fclose(enter);
}