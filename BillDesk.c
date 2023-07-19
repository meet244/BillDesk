#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<dirent.h>
#include<string.h>
#include<time.h>
#include<math.h>

/*
Made By : 
Meet Patel S002
Harshil Damania S051
*/

void print(char* ptr){
    int i;
    int speed = 15;// millis break between letters
    for(i=0;i<strlen(ptr);i++){
        printf("%c",ptr[i]);
        usleep(speed*1000);
    }
}

int checkdir(){

    DIR *d;
    struct dirent *dir;
    d = opendir("C:/");
    int res=1;
    if (d) {
        while ((dir = readdir(d)) != NULL) {
        res = strcmp(dir->d_name,"Cmini");
        if(res==0){
            break;
        }
        }
        closedir(d);
    }
    return res;   // 0 = folder detected // 1 = folder undetected
}

void makedir(){
    int check;
    char* dirname = "Cmini";
  
    check = _mkdir(dirname,0777);
  
    // check if directory is created or not
    if (check){
        printf("ERROR - Unabe to Create Directory\n");
        exit(1);}
}

char *strremove(char *str, const char *sub) {
    size_t len = strlen(sub);
    if (len > 0) {
        char *p = str;
        while ((p = strstr(p, sub)) != NULL) {
            memmove(p, p + len, strlen(p + len) + 1);
        }
    }
    return str;
}

char *truncString(char *str, int pos)
{
    size_t len = strlen(str);

    if (len > abs(pos)) {
        if (pos > 0)
            str = str + pos;
        else
            str[len + pos] = 0;
    }

    return str;
}

struct myproduct
{
    int id,stock,count;
    float price,tprice;
    char name[15];
}myproducts[100],tempProduct;

int totalproducts = 0;
void makeproduct(){
    FILE *ogFile = fopen("C:\\Cmini\\product.txt", "r");

    int productCount,i;
    fscanf(ogFile, "%d", &productCount);
    totalproducts = productCount;

    for (i=0;i<productCount;i++) {
        fscanf(ogFile, "%d", &myproducts[i].id);
        fscanf(ogFile, "%s", &myproducts[i].name);
        fscanf(ogFile, "%f", &myproducts[i].price);
        fscanf(ogFile, "%d", &myproducts[i].stock);
        myproducts[i].count=0;
        myproducts[i].tprice=0;
    }

    fclose(ogFile);
}


int opt,i,flag = 0,addStock,id;



void main(){

    start:
    int a;

    print("Welcome to BillDesk!\nPress 0 for printing bill.\nPress 1 for searchiing bill.\nPress 2 for editing items.\nPress 3 for exit.\nEnter Input : ");
    scanf("%d",&a);

    switch(a){
        case 3:
        exit(0);break;

        case 1:
        // clearing screen
        system("cls");
        // checking if dir exists?
        again1:
        if(checkdir()==1){ printf("ERROR : Unable to detect folder.");exit(0); }
        // setting dir
        int ch=chdir("C:/Cmini");
        if(ch<0){ printf("ERROR : Unable to change directory\n");exit(0); }
        // Asking bill Number
        int ask;
        print("Press 0 to go back.\n");
        print("Enter Bill Number to search : ");
        scanf("%d",&ask); 
        // finding files
        if(ask==0){
            system("cls");
            break;}
        int inp = 1;
        int found = 0;
        DIR *d;
        struct dirent *dir;
        d = opendir(".");
        if (d) {
            while ((dir = readdir(d)) != NULL) {
                char *file_name_ptr = dir->d_name;
                char *ret = strstr(file_name_ptr, ".txt");
                if (ret){   // Filter 1 : file cntains ".txt"
                    char *shot = strremove(file_name_ptr,".txt");
                    if(strlen(shot)==8){    // Filter 2 : length of file is 8 char
                        int num = atoi(shot);
                        if(num==ask){
                            found = 1;
                            strcat(file_name_ptr,".txt");
                            FILE *f;
                            char s;
                            f=fopen((file_name_ptr),"r");
                            while((s=fgetc(f))!=EOF) {
                                printf("%c",s);
                            }
                            fclose(f);
                            printf("\n\n");
                            goto again1;
                            break;
                        }
                    }
                }
            }
            closedir(d);
        }
        system("cls");
        if(found!=1){
            print("Bill not found!\n\n");
        }
        goto again1;
        system("cls");
        break;

        case 0:
        makeproduct();
        system("cls");
        //Geting date
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        char day[5], mth[5], yr[5], dte[20];

        sprintf(day, "%02d", tm.tm_mday);
        sprintf(mth, "%02d", tm.tm_mon + 1);
        sprintf(yr, "%d", tm.tm_year + 1900);

        strcat(day, "/");
        strcat(day, mth);
        strcat(day, "/");
        strcat(day, yr);
        // checking and making dir
        int ch2=chdir("C:/");
        if(ch2<0)
        printf("ERROR : Unable to change directory\n");

        if(checkdir()==1){
            makedir();
        }
        
        ch=chdir("C:/Cmini");
        if(ch<0)
        printf("ERROR : Unable to change directory\n");
        //-----GETTING BILL NO-----
        int high=0;
        DIR *d2;
        struct dirent *dir2;
        d2 = opendir(".");
        if (d2) {
            while ((dir2 = readdir(d2)) != NULL) {
                char *file_name_ptr = dir2->d_name;
                char *ret = strstr(file_name_ptr, ".txt");
                if (ret){   // Filter 1 : file cntains ".txt"
                    char *shot = strremove(file_name_ptr,".txt");
                    if(strlen(shot)==8){    // Filter 2 : length of file is 8 char
                        int num = atoi(shot);
                        if(num>high){
                            high=num;
                        }
                    }
                }
            }
        }
        
        closedir(d2);
        // converting to char str
        char no[10];
        char no_name[10];
        sprintf(no, "%08d", high+1);
        strcpy(no_name,no);
        strcat(no,".txt");
        
        //-----ASKING FOR ITEMS-----
        system("cls");       
        while (1){ 
            char itm_str[10];
            int itm;
            print("Press 0 for next.\n");
            print("Enter item code : ");
            scanf("%s",&itm_str);

            if(atoi(itm_str)==0){
                    system("cls");       
                    break;
            }
            if(strlen(itm_str)!=4){
                invd:
                system("cls");       
                print("Invalid item\n\n");
                continue;
            }
            itm = atoi(itm_str);
            int temp,added=0;
            for(temp=0;temp<totalproducts;temp++){
                if(itm==myproducts[temp].id){
                    if(myproducts[temp].stock>0){
                        myproducts[temp].count++;
                        myproducts[temp].stock--;
                        system("cls");
                        print("Item Added\n\n");
                        added=1;
                    }
                    else{
                        system("cls");
                        print("Item Out of stock\n\n");
                        added=1;
                    }
                }
            }
            if(added!=1){
                goto invd;
            }
        }
        //-----Checking if items are added?-----
        int i1,this_qty=0,this_itms=0;
        float payment;
        for(i1=0;i1<totalproducts;i1++){
            if(myproducts[i1].count>0){
                this_itms++;
                this_qty+=myproducts[i1].count;
                myproducts[i1].tprice=myproducts[i1].count*myproducts[i1].price;
                payment+=myproducts[i1].tprice;
                while(strlen(myproducts[i1].name)<15){
                    strcat(myproducts[i1].name," ");
                }
            }
        }
        printf("tc = %d",this_qty);
        //-----ASkING FOR MONEY COLLECTED-----
        system("cls");
        float fpayment = round(payment+((payment/100)*18));
        
        float money_coll = 0;
        int balance_paid = 0;
        while(1){
            printf("Amount to be paid by customer : %.2f\n",fpayment);
            print("Enter amount collected : ");
            scanf("%f",&money_coll);
            if (money_coll>=fpayment){
                balance_paid = round(money_coll-fpayment);
                printf("%d",balance_paid);
                break;
            }
            else{
                system("cls");
                print("Invalid Input\n\n");
            }
        }
        //-----SAVING STOCK IN FILE-------
        FILE *tempFile = fopen("temp.txt", "w");
        //Printing Product count
        fprintf(tempFile, "%d ", totalproducts);
        //Printing ID Name Price Stock 
        for (int i3=0;i3<totalproducts;i3++) {
            fprintf(tempFile, "\n%d ", myproducts[i3].id);
            fprintf(tempFile, "%s ", myproducts[i3].name);
            fprintf(tempFile, "%.2f ", myproducts[i3].price);
            fprintf(tempFile, "%d ", myproducts[i3].stock);
        }

        fclose(tempFile);

        remove("product.txt");
        rename("temp.txt", "product.txt");
        //-----WRITING IN FILE-----
        FILE * myf;
        myf = fopen(no, "w");

        fputs("----------------------------------------\n", myf);
        fputs("               FRESH MART               \n", myf);
        fputs("----------------------------------------\n", myf);
        fputs("        Fresh Mart, Opp To Bhor,        \n", myf);
        fputs("        Industries, Near Western        \n", myf);
        fputs("      Express Highway, Kandivli(e)      \n", myf);
        fputs("       Mumbai-400101, Maharashtra       \n", myf);
        fputs("             Ph-02256990091             \n", myf);
        fputs("        GSTIN - 24AACCA8432H1ZW         \n", myf);
        fputs("     CIN NO - L21091KA2019OPC141331     \n", myf);
        fputs("________________________________________\n", myf);
        fputs("               Invoice                  \n", myf);
        fputs("Bill No : ", myf);
        fputs(no_name, myf);
        fputs("  Bill Dt : ", myf);
        fputs(day, myf);
        fputs("\n", myf);
        fputs("________________________________________\n", myf);
        fputs("----------------------------------------\n", myf);
        fputs("HSN  Particuars       Qty  N/Rate  Value\n", myf);
        fputs("----------------------------------------\n", myf);
        int i2;
        for(i2=0;i2<totalproducts;i2++){
            if(myproducts[i2].count>0){
                char txt_id[4],txt_count[5],txt_price[7],txt_tprice[7];
                sprintf(txt_id, "%04.0d", myproducts[i2].id);
                fputs(txt_id, myf);
                fputs(" ", myf);
                fputs(myproducts[i2].name, myf);
                fputs("  ", myf);
                sprintf(txt_count, "%02.0d", myproducts[i2].count);
                fputs(txt_count, myf);
                fputs("  ", myf);
                sprintf(txt_price, "%6.2f", myproducts[i2].price);
                fputs(txt_price, myf);
                fputs("  ", myf);
                sprintf(txt_tprice, "%6.2f", myproducts[i2].tprice);
                fputs(txt_tprice, myf);
                fputs("\n", myf);
                }
            }
        // fputs("0001 Paperboat Mango  03    18.65  55.95\n", myf);
        fputs("----------------------------------------\n", myf);
        // fputs("Items :06  Qty :018  SubTotal :  0335.70\n", myf);
        fputs("Items :", myf);
        char txt_itm[3];
        sprintf(txt_itm,"%02.0d",this_itms);
        fputs(txt_itm, myf);
        fputs("  Qty :",myf);
        char txt_qty[5];
        sprintf(txt_qty,"%03.0d",this_qty);
        fputs(txt_qty,myf);
        fputs("  SubTotal :  ",myf);
        char txt_pay[10];
        sprintf(txt_pay,"%7.2f",payment);
        fputs(txt_pay,myf);
        fputs("\n",myf);

        fputs("________________________________________\n", myf);
        fputs("<----------GST BREAKUP Details--------->\n", myf);
        fputs("Taxable Amt  CGST(9%)  SGST(9%)    Total\n", myf);
        // fputs("335.70       030.21    030.21    0396.12\n", myf);
        fputs(txt_pay, myf);
        fputs("      ", myf);
        char txt_gst[7];
        sprintf(txt_gst,"%6.2f",(fpayment-payment)/2);
        fputs(txt_gst,myf);
        fputs("    ", myf);
        fputs(txt_gst,myf);
        fputs("    ", myf);
        char txt_fpay[10];
        sprintf(txt_fpay,"%7.2f",fpayment);
        fputs(txt_fpay,myf);
        fputs("\n",myf);
        fputs("----------------------------------------\n", myf);
        // fputs("                Cash :   500/-          \n", myf);
        fputs("                Cash :   ", myf);
        char txt_got[10];
        sprintf(txt_got,"%03.2f",money_coll);
        fputs(txt_got,myf);
        fputs("/-          \n", myf);
        fputs("Balance Paid In Cash :   ", myf);
        char txt_bal[10];
        sprintf(txt_bal,"%03.0d",balance_paid);
        fputs(txt_bal,myf);
        fputs("/-          \n",myf);
        // fputs("Balance Paid In Cash :   104/-          \n", myf);
        fputs("----------------------------------------\n", myf);
        fputs("  Thank you for shopping at our store!  \n", myf);
        fputs("        Love to see you again :)        \n", myf);
        fputs("________________________________________\n", myf);
        
        fclose(myf);
        
        system("cls");
        printf("Bill Printed\n\n");
        break;

        case 2:

        int ch3=chdir("C:/Cmini");
        if(ch3<0){ printf("ERROR : Unable to change directory\n");exit(0); }

        makeproduct();

        while(1==1){
            begin : 
            system("cls");
            print("Press... \n 1 to Edit Product");
            print("\n 2 to Create New Product");
            print("\n 3 to delete Product");
            print("\n 0 to go back");
            print("\n\nYour Option : ");
            scanf("%d", &opt);

            system("cls");
            switch (opt) {

            case 0:
            break;

            case 1 : 
                edit : 
                system("cls");
                printf("\nEnter Product ID : ");
                scanf("%d", &id);
                        

                for (i=0;i<totalproducts;i++) {
                    if (id == myproducts[i].id) {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0) {
                    printf("Product Not Found in List...");
                    printf("\nWould you like to search for a different Product \n 1-YES \n 0-NO ?");
                    printf("\n--------------------------------------------------------------\n");
                    printf("Your Option : ");
                    scanf("%d",&opt);
                    
                    if (opt == 1) goto edit;
                    else break;   
                }

                // If product found copy data to Temp Product
                tempProduct = myproducts[i];
                        
                label : 
                //Display Og Product Data
                printf("\n ID : %d", myproducts[i].id);
                printf("\n Name : %s", myproducts[i].name);
                printf("\n Price : %.2f", myproducts[i].price);
                printf("\n Stock : %d", myproducts[i].stock);
                printf("\n--------------------------------------------------------------\n");
                //Asking What to edit
                printf("Press... \n 1 to Edit Name ");
                printf("\n 2 to edit Price");
                printf("\n 3 to Add Stock");
                printf("\n--------------------------------------------------------------\n");
                printf("Your Option : ");
                scanf("%d", &opt);

                //Edit according to option selected
                switch (opt) {
                case 1:
                printf("\n Enter New Name : ");
                scanf("%s", &tempProduct.name);
                break;

                case 2 : 
                printf("\n Enter New Price : ");
                scanf("%d", &tempProduct.price);
                break;

                case 3 : 
                printf("\n Enter Added Stock : ");
                scanf("%d",&addStock);
                tempProduct.stock += addStock;
                break;
                        
                default: goto label;}
                    
                //Confirm Changes
                printf("Do you want to save the Changes  ? \n 1 - YES \n 0-NO ");
                printf("\nYour Option : ");
                scanf("%d", &opt);

                if (opt == 1) {
                    myproducts[i] = tempProduct;
                }
                else {break;
                }
                break;

            case 2 :
                //-------------------
                new : 
                // Need to generate Product ID
                printf("Enter ID of Product : ");
                scanf("%d", &tempProduct.id);
                printf("Enter Name of Product : ");
                scanf("%s", &tempProduct.name);
                printf("Enter Price : ");
                scanf("%f", &tempProduct.price);
                printf("Enter Stock : ");
                scanf("%d", &tempProduct.stock);

                // Confirming New Product
                printf("DO you want to create this New Product ? \n 1-YES \n 0-NO ");
                printf("\n Your Option : ");
                scanf("%d", &opt);

                //If confirmed yes then add new product to list of products
                if (opt == 1) {
                    totalproducts++;
                    myproducts[totalproducts-1] = tempProduct;
                    break;
                } 
                else {
                    goto begin;
                }
                //-------------------
            break; 

            case 3 : 
                del : 
                system("cls");
                flag = 0;
                print("\nEnter Product Id : ");
                scanf("%d", &id);
                // Checking for product id in product list
                for (int i=0;i<totalproducts;i++) {
                    if (id == myproducts[i].id) {
                        printf("\n Name : %s", myproducts[i].name);
                        printf("\n Price : %.2f", myproducts[i].price);
                        printf("\n Stock : %d", myproducts[i].stock);
                        print("\n\n Do You want to delete this Product ? \n 1-Yes \n 0-No");                                                
                        print("\nYour Option : ");
                        scanf("%d",&opt);
                        if (opt == 1) {
                            //totalproducts--;
                            myproducts[i].id = 0;
                            flag = 1;
                            
                            /* Code to Save the Product Objects in Text file once Program is CLosed */
                            FILE *tempFile1 = fopen("temp.txt", "w");
                            //Printing Product count
                            fprintf(tempFile1, "%d ", totalproducts-1);
                            //Printing ID Name Price Stock 
                            for (int i4=0;i4<totalproducts;i4++) {
                                if (myproducts[i4].id == 0) continue; 
                                fprintf(tempFile1, "\n%4d ", myproducts[i4].id);
                                fprintf(tempFile1, "%s ", myproducts[i4].name);
                                fprintf(tempFile1, "%.2f ", myproducts[i4].price);
                                fprintf(tempFile1, "%d ", myproducts[i4].stock);
                            }

                            fclose(tempFile1);

                            remove("product.txt");
                            rename("temp.txt", "product.txt");

                            makeproduct();

                            break;
                        }
                    }
                }

                if (flag == 0) {
                    // If product not found ask whether they want to search another one ?? 
                    print("Product Id not found in List..."); 
                    print("\nWould You like to search for another Product ? \n 1-Yes \n 0-No");
                    print("\n\nYour Option : ");
                    scanf("%d", &opt);
                    // If yes then repeat otherwise break to Edit screen....
                    if (opt == 1) goto del;
                    else break;
                }

            break;

            default :  
            print("Invalid Input");
            goto begin;
            }
            break;
        }

        /* Code to Save the Product Objects in Text file once Program is CLosed */
        FILE *tempFile1 = fopen("temp.txt", "w");
        //Printing Product count
        fprintf(tempFile1, "%d ", totalproducts);
        //Printing ID Name Price Stock 
        for (int i4=0;i4<totalproducts;i4++) {
            if (myproducts[i4].id == 0) continue; 
            fprintf(tempFile1, "\n%4d ", myproducts[i4].id);
            fprintf(tempFile1, "%s ", myproducts[i4].name);
            fprintf(tempFile1, "%.2f ", myproducts[i4].price);
            fprintf(tempFile1, "%d ", myproducts[i4].stock);
        }

        fclose(tempFile1);

        remove("product.txt");
        rename("temp.txt", "product.txt");
        system("cls");
        print("changes saved\n\n");
        break;

        default:
        system("cls");
        printf("Invaid Input\n\n");
        
    }
    goto start;
}