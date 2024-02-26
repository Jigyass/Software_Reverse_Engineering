int gval;

int func1(arg)
{
	arg+=5;
	return arg;
}

void gfunc(arg)
{
	gval += arg;
}

void main()
{
	if(argc <= 1)
	{
		puts("Error");
		exit(0);
	}
	int local_var = atoi(argv[1]);
	if(local_var>1000)
	{
		int local_var2 = func1(local_var);
		printf("Local_var2:%d\n", local_var2);
	}
	else if(local_var>500)
	{
		if(local_var == 600)
		{
			printf("local_var:%d\n", local_var);
		}
		else
		{
			puts("Sorry, its not 600");
		}
	}
	else if(local_var>200)
	{
		while(temp<local_var)
		{
			array[i] = local_var & i;
			temp++;
		}
		printf("Some Message:%d", array[100]);
	}
	else if(local_var>100)
	{
		gfunc(local_var);
		printf("Some Message:%d", gval);
	}
	else if(local_var>10)
	{
		char str1[] = "EECS690/"
		char str2[] = "700SRE"
		char str3[123];
		strcpy(str3, str1);
		strcat(str3, str2);

		if(strlen(str3) == local_var)
		{
			puts("E: FLAG Reached\n");
		}
	}
	else if(local_var<=9)
	{
		int last;
		switch (local_var) 
		{
        		case 1: last = local_var + 1; break;
        		case 2: last = local_var + 2; break;
        		case 3: last = local_var + 3; break;
        		case 4: last = local_var + 4; break;
        		case 5: last = local_var + 5; break;
        		case 6: last = local_var + 6; break;
        		case 7: last = local_var + 7; break;
        		case 8: last = local_var + 8; break;
        		case 9: last = local_var + 9; break;
    		}
		printf("Some Message:%d\n", last);
	


	}
	return 0;


}
