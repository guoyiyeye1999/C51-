#include<regx51.h>

typedef unsigned char uchar;
typedef unsigned int uint;

uchar code num[11]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0X40};  // 0~9����

uchar miao=50, fen=59, shi=23,day=28,mon=02,year=21; //��λ��־λ

uint i=0;  //��ʱ

uchar miao_L, miao_H, fen_L, fen_H, shi_L, shi_H, day_g,day_s,mon_g,mon_s,year_g,year_s; //ʱ���֡���ĸ�λ��xxx_L����ʮλ��xxx_H��

 void delay_ms(unsigned int t)
{
      unsigned int i,j;	
      for(j=0;j<t;j++)	  
           for(i=0;i<116;i++);
   }//��ʱ���� 

void Timer0Init(void)		//1����@12.000MHz
{
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0x18;		//���ö�ʱ��ֵ
	TH0 = 0xFC;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
   ET0=1;
   EA=1;
   PT0=0;
}
 void Nixie1(unsigned char Location1,Number1)
{
	switch(Location1)		//λ�����
	{
		case 9:P2_7=0;P2_6=0;P2_5=0;break; //LED9
		case 10:P2_7=0;P2_6=0;P2_5=1;break;	//LED10
		case 11:P2_7=0;P2_6=1;P2_5=0;break;
		case 12:P2_7=0;P2_6=1;P2_5=1;break;
		case 13:P2_7=1;P2_6=0;P2_5=0;break;
		case 14:P2_7=1;P2_6=0;P2_5=1;break;
		case 15:P2_7=1;P2_6=1;P2_5=0;break;
		case 16:P2_7=1;P2_6=1;P2_5=1;break;
	}
	P0=num[Number1];	//�������
	delay_ms(1);				//��ʾһ��ʱ��
    P0=0x00;	//������0����Ӱ
}
 void Nixie2(unsigned char Location2,Number2)
{
	switch(Location2)		//λ�����
	{
	    case 1:P2_3=0;P2_2=0;P2_1=0;break; //LED1
		case 2:P2_3=0;P2_2=0;P2_1=1;break;
		case 3:P2_3=0;P2_2=1;P2_1=0;break;
		case 4:P2_3=0;P2_2=1;P2_1=1;break;
		case 5:P2_3=1;P2_2=0;P2_1=0;break;
		case 6:P2_3=1;P2_2=0;P2_1=1;break;
		case 7:P2_3=1;P2_2=1;P2_1=0;break;
		case 8:P2_3=1;P2_2=1;P2_1=1;break;
	}
	P1=num[Number2];	//�������
	delay_ms(1);				//��ʾһ��ʱ��
    P1=0x00;	//������0����Ӱ
}
void display(){  //��ʾ
    Nixie1(16,miao_L);
	Nixie1(15,miao_H);
	Nixie1(14,10);	
	Nixie1(13,fen_L);
	Nixie1(12,fen_H);
	Nixie1(11,10);	
	Nixie1(10,shi_L); 
	Nixie1(9,shi_H);	 
	Nixie2(8,day_g);	
	Nixie2(7,day_s);	
	Nixie2(6,10);	
	Nixie2(5,mon_g);	 
	Nixie2(4,mon_s);	 
	Nixie2(3,10);	 
	Nixie2(2,year_g);
	Nixie2(1,year_s); 
}
void keyscan(){  //��������
  switch(P3)
  { 
   case(0x3E):
   { 
    if(P2_4==0)
	{delay_ms(20);
		if(P2_4== 0)
		{
			year++;  
			while(!P2_4);
		} 
	 }
	}//�꣫��
   case(0x7E):
   {   
   if(P2_4==0)
   {delay_ms(20);
		if(P2_4==0)
		{
			year--;  
			while(!P2_4);
		}  
	 }
    }//��--
   case(0x3D):{ 
   if(P2_4==0)
   {delay_ms(20);
		if(P2_4== 0)
		{
		   mon++;
		   if(mon==13){mon=1;} 
			while(!P2_4);
		}  
	 }
   }//��++
   case(0x7D):{ 
   if(P2_4==0)
   {delay_ms(20);
		if(P2_4== 0)
		{
			mon--; 
			if(mon==0){mon=12;} 
			while(!P2_4);
		}  
	 }
 }// ��--
   case(0x3B):{   
   	 if(P2_4==0)
   {delay_ms(20);
		if(P2_4== 0)
		{
			day++;
			if(mon==1||mon==3||mon==5||mon==7||mon==8||mon==10||mon==12) 
			{if(day==32){day=1;}}
			else if(mon==4||mon==6||mon==9||mon==11) {if(day==31){day=1;}}
			else if(mon==2)
					{
					if((year+2000)%400==0||((year+2000)%100!=0&&(year+2000)%4==0))
						{
					  		if(day==30)
								{day=1;}}
					 else  
							{
							if(day==29)
							{day=1;}
			 				}
					}
			while(!P2_4);
		}  
	 }
   }// ��++
   case(0x7B):{   
   	   if(P2_4==0)
   {delay_ms(20);
		if(P2_4== 0)
		{
			day--; 
			if(mon==1||mon==3||mon==5||mon==7||mon==8||mon==10||mon==12) 
			{if(day==0){day=31;}}
			else if(mon==4||mon==6||mon==9||mon==11) {if(day==0){day=30;}}
			else if(mon==2)
					{
					if((year+2000)%400==0||((year+2000)%100!=0&&(year+2000)%4==0))
						{
					  		if(day==0)
								{day=29;}}
					 else  
							{
							if(day==0)
							{day=28;}
			 				}
					}		
			while(!P2_4);
		}  
	 }
    }// ��--
   case(0x37):{  
   		if(P2_4==0)
   {delay_ms(20);
		if(P2_4==0)
		{
			shi++;
			if(shi==24){shi=0;}  
			while(!P2_4);
		}  
	 }
    }// ʱ++
   case(0x77):{ 
   		if(P2_4==0)
   {delay_ms(20);
		if(P2_4== 0)
		{  
			if(shi>0)
		   shi=shi-1;
		   else shi=23; 
			while(!P2_4);
		}  
	 }
  }// ʱ--
   case(0x2F):{  
   
   	if(P2_4==0)
   {delay_ms(20);
		if(P2_4== 0)
		{
			fen++;
			if(fen>=60){fen=0;}  
			while(!P2_4);
		}  
	 }
    }// ��++
   case(0x6F):{ 
   if(P2_4==0)
   {delay_ms(20);
		if(P2_4== 0)
		{
			if(fen>0)
		   fen=fen-1;
		else fen=59;  
			while(!P2_4);
		}  
	 }
   }// ��--
   case(0x1F):{  
   		 if(P2_4==0)
   {delay_ms(20);
		if(P2_4== 0)
		{
			miao++;  
			if(miao>=60){miao=0;}
			while(!P2_4);
		}  
	 }   
    }// ��++
   case(0x5F):{
   	    
	   if(P2_4==0)
   {delay_ms(20);
		if(P2_4== 0)
		{
			if(miao>0)
		     miao=miao-1;
		      else  miao=59;
			while(!P2_4);
		}  
	 }   
   }// ��--
  }
 }
void main(){

       Timer0Init();  //��ʱ����ʼ��
	while(1){
		display();//��ʾ
		keyscan();		
   }

}
 
void timer0_int() interrupt 1{  //�жϷ�����
 	 
	 TL0 = 0x18;	
	TH0 = 0xFC;	 
	 i++;
    if(i == 1000){
	 	i = 0;  //��һ������
	 	miao++;	//i = 1000 Ϊһ�����־λ�� 1

		if(miao == 60){
			miao = 0;  //��һ������
			fen++;

			if(fen == 60){
				fen = 0;  //��һʱ����
				shi++;

				if(shi == 24)
				{
					shi = 0;  //24Сʱ��
					fen = 0;
					miao = 0;
				   day++;
				   if(mon==1||mon==3||mon==5||mon==7||mon==8||mon==10||mon==12)
				   {
				   	 if(day==32)
					 {day=1;
					 mon++;
					 }
				   }
				   else if(mon==4||mon==6||mon==9||mon==11)
				   {
				   	 if(day==31)
					 {day=1;
					 mon++;
					 }
					}
				   else if(mon==2)
					{
					if((year+2000)%400==0||((year+2000)%100!=0&&(year+2000)%4==0))
						{
					  		if(day==30)
								{day=1;
					   			  mon++;
								}
				    	}
					else  
							{
							if(day==29)
							{day=1;
							mon++;
							}
			       		 }
					}
				if (mon==13)
					 { mon=1;
					 year++;
					}
				   }
				}
			}
		}
		miao_L = miao%10;  //���λ
		miao_H = miao/10;  //��ʮλ

		fen_L = fen%10;  //�ָ�λ
		fen_H = fen/10;  //��ʮλ

		shi_L = shi%10;  //ʱ��λ
		shi_H = shi/10;  //ʱʮλ

		day_g=day%10;
		day_s=day/10;

		mon_g=mon%10;
		mon_s=mon/10;

		year_g=year%10;
		year_s=year/10;
 }

