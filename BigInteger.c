#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char* initializeINTAL()
{
	int n=1001;
	char* operand = (char *)malloc(n*sizeof(char));

	for(int i=0 ; i<n-1 ; i++)
		operand[i]='0';

	operand[1000]='\0';

	return operand;
}

int giveLength(char* a)
{
	char* temp = a;
	int l = 0;

	while(*(temp++)!='\0')l++;

	return l;
}

int compareINTAL( char *a , char *b)
{
	int l1=giveLength(a);
	int l2=giveLength(b);

	if(l1 > l2) return 1;
	if(l1 < l2) return -1;

	while(*a != '\0' && *b != '\0')
	{
		if(*a < *b) return -1;
		if(*a > *b) return -1;

		a++;
		b++;
	}

	return 0;

}

char* subINTAL(char *a , char *b)
{
	int n1 = giveLength(a);
	int n2 = giveLength(b);
	int n;

	if(n1>n2)  n=n1; else n=n2 ;

	char *ans = initializeINTAL();
	int carry = 0;

	int i=n1-1;
	int j=n2-1;
	int ai=n;

	while(i>=0 && j>=0)
	{
		int o1 = (int) a[i]-'0';
		int o2 = (int) b[j]-'0';


		char toPut;

		if(o1 < (o2+carry))
		{
			toPut =  '0' + ( (o1+10)-(o2+carry) );
			carry = 1;
		} 
		else
		{
			toPut =  '0' + ( o1-(o2+carry) );
			carry = 0;
		}

		//printf("%c",toPut);

		ans[ai] = toPut;

		ai--;
		i--;
		j--;
	}

	while(i>=0)
	{
		int o1 = (int) a[i]-'0';
		int o2 = 0;


		char toPut;

		if(o1 < (o2+carry))
		{
			toPut =  '0' + ( (o1+10)-(o2+carry) );
			carry = 1;
		} 
		else
		{
			toPut =  '0' + ( o1-(o2+carry) );
			carry = 0;
		}

		//printf("%c",toPut);

		ans[ai] = toPut;

		ai--;
		i--;
		j--;
	}

	while(j>=0)
	{
		int o1 = 0;
		int o2 = (int) b[j]-'0';


		char toPut;

		if(o1 < (o2+carry))
		{
			toPut =  '0' + ( (o1+10)-(o2+carry) );
			carry = 1;
		} 
		else
		{
			toPut =  '0' + ( o1-(o2+carry) );
			carry = 0;
		}

		//printf("%c",toPut);

		ans[ai] = toPut;

		ai--;
		i--;
		j--;
	}

	//ans[0]=(char)('0'+carry);
	ans[n+1]='\0';

	if(carry == 0 )ans = &ans[1];

	ans = strtok(ans,"\0");

	return ans;

}


char* addINTAL(char *a , char *b)
{
	int n1 = giveLength(a);
	int n2 = giveLength(b);
	int n;

	if(n1>n2)  n=n1; else n=n2 ;

	char *ans = initializeINTAL();
	int carry = 0;

	int i=n1-1;
	int j=n2-1;
	int ai=n;

	while(i>=0 && j>=0)
	{
		int o1 = (int) a[i]-'0';
		int o2 = (int) b[j]-'0';

		char toPut = (char)( '0'+( (o1+o2+carry)%10 ) );
		carry = (o1+o2+carry)/10;

		//printf("%c",toPut);

		ans[ai] = toPut;

		ai--;
		i--;
		j--;
	}

	while(i>=0)
	{
		int o1 = (int) a[i]-'0';
		int o2 = 0;

		
		char toPut = (char)( '0'+( (o1+o2+carry)%10 ) );
		carry = (o1+o2+carry)/10;

		ans[ai] = toPut;

		ai--;
		i--;
	}

	while(j>=0)
	{
		int o1 = 0;
		int o2 = (int) b[j]-'0';

		
		char toPut = (char)( '0'+( (o1+o2+carry)%10 ) );
		carry = (o1+o2+carry)/10;

		ans[ai] = toPut;

		ai--;
		j--;
	}

	ans[0]=(char)('0'+carry);
	ans[n+1]='\0';

	if(carry == 0 )ans = &ans[1];

	ans = strtok(ans,"\0");

	return ans;

}



char * trim(char * str)
{
	int i=0;
	for( ; i<1000 ; i++)
	{
		if(str[i]!='0')break;
	}
	return &str[i];
}

char * multiplicationINTAL(char * a , char * b)
{

	
	char * ans = initializeINTAL();
	char * tempAns = initializeINTAL();


	int l1 = giveLength(a);
	int l2 = giveLength(b);



	int carry = 0;
	int dig1;
	int dig2;
	int mul;
	int lastInd = 0;
	for(int i=l2-1 ; i>=0 ; i--)
	{
		char * tempAns = initializeINTAL();
		int tempInd = l1+l2 - lastInd;
		lastInd++;
		carry = 0;

		for(int j=l1-1 ; j>=0 ; j--)
		{
			dig1 = a[j]-'0';
			dig2 = b[i]-'0';
			mul = ((dig1 * dig2) + carry ) % 10;
			carry = ((dig1 * dig2) + carry ) / 10;

			tempAns[tempInd--] = '0' + mul;

		}

		tempAns[tempInd--] = '0'+ carry;
		ans=addINTAL(ans,tempAns);

		
	}

		ans[l1+l2+1] = '\0';
		ans = trim(strtok(ans,"\0"));
		if(!giveLength(ans)) return "0";
	return ans;

}


char * BigPow(char *num , int power)
{

	if(power == 0) return "1";
	if(power ==1) return num;

	char *ans;


	if(power%2) 
	{		
			ans = BigPow(num,power-1);
			ans = multiplicationINTAL( num , ans);
	}
	else
	{
			char * temp = BigPow(num , power/2 );
			ans = multiplicationINTAL(temp,temp);
	}

	return ans;

}


char* Bigfactorial(char *num)
{
	num = trim(num);
	int l1 = giveLength(num);

	if(l1 == 0 ) return "1";

	char* next = subINTAL(num,"1");

	char* temp = Bigfactorial(next);

	temp = multiplicationINTAL(num,temp);

	return temp;
}


char * BigFibonacci(int n)
{
	char* dig1 = "0";
	char* dig2 = "1";
	char* temp;

	if (n==0) return dig1;
	if (n==1) return dig2;

	for(int i=2 ; i<=n ; i++)
	{
		temp = dig2;
		dig2 = addINTAL(dig1,dig2);
		dig1 = temp; 
	}

	return dig2;
}

int main()
{
	printf("******************************************* Let's Play With BIG INTEGER ************************************************\n\n\n\n" );
	printf("------------------------------------------- press 1. for Addition------------------------------------------------------- \n\n");
	printf("------------------------------------------- press 2. for Subtraction---------------------------------------------------- \n\n");
	printf("------------------------------------------- press 3. for Multiplication------------------------------------------------- \n\n");
	printf("------------------------------------------- press 4. for Factorial------------------------------------------------------ \n\n");
	printf("------------------------------------------- press 5. for Exponentiation------------------------------------------------- \n\n");
	printf("------------------------------------------- press 6. for n th Fibonacci------------------------------------------------- \n\n");
	printf("------------------------------------------- press 0. for Exit----------------------------------------------------------- \n\n");

	int n=1;

	while(n){

	printf("Please enter your choice :");
	scanf("%d",&n);
	switch(n)
	{
		case 1:
		{
			char * num1 = initializeINTAL();
			char * num2 = initializeINTAL();

			printf("Enter the First operand\n");

			scanf("%s",num1);

			printf("Enter the Second operand\n");

			scanf("%s",num2);
			
			char * ans = addINTAL(num1,num2);
			printf("result : %s\n",ans);

			break;

		}


		case 2:
		{
			char * num1 = initializeINTAL();
			char * num2 = initializeINTAL();

			printf("Enter the First operand\n");

			scanf("%s",num1);

			printf("Enter the Second operand\n");

			scanf("%s",num2);
			
			char * ans = subINTAL(num1,num2);
			printf("result : %s\n",ans);

			break;

		}

		case 3:
		{
			char * num1 = initializeINTAL();
			char * num2 = initializeINTAL();

			printf("Enter the First operand\n");

			scanf("%s",num1);

			printf("Enter the Second operand\n");

			scanf("%s",num2);
			
			char * ans = multiplicationINTAL(num1,num2);
			printf("result : %s\n",ans);

			break;

		}

		case 4:
		{
			char * num1 = initializeINTAL();
			char * num2 = initializeINTAL();

			printf("Enter the Number\n");

			scanf("%s",num1);

			char * ans = Bigfactorial(num1);
			printf("result : %s\n",ans);

			break;

		}

		case 5:
		{
			char * num1 = initializeINTAL();
			int  n ;

			printf("Enter the number\n");

			scanf("%s",num1);

			printf("Enter the power\n");

			scanf("%d",&n);
			
			char * ans = BigPow(num1,n);
			printf("result : %s\n",BigPow(num1,n));

			break;

		}

		case 6:
		{
			int n;

			printf("Enter the position\n");

			scanf("%d",&n);
			
			char * ans = BigFibonacci(n);
			printf("your %d th Fibonacci is : %s\n",n,ans);

			break;

		}
		case 0:
		{
			printf("Thank You :)");
			break;

		}
	}

	}
}