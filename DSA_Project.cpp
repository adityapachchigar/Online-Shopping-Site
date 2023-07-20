#include<iostream>
#include <iomanip>
#include<string.h>
using namespace std;
bool flag=false;
int total_price=0;
struct product
{
    int price;
    int id;
    string name,brand;
    int stock;
    int items;
    struct product *next;
}mobile[20],tv[20],fridge[20],ac[20],laptop[20],sports[20],*root;
void start();
bool compare(string a,string b)
{
    int i=0;
    if(a.size()!=b.size())
    return false;
    else
    {
      while(i<a.size()&&b.size())
      {
          char p,q;
          p=a[i];
          q=b[i];
          if(p>='A'&&p<='Z')
          p=p-'A'+'a';
          if(q>='A'&&q<='Z')
          q=q-'A'+'a';
        if(p!=q)
        return false;
        i++;
      }
      return true;
    }
}

void Delete_from_cart(){
    cout<<"Enter the id \n";
    int x;
    cin>>x;
    struct product *ptr;
    ptr=root;
    if(ptr->id==x){
        total_price-=((ptr->price)*(ptr->items));
        root=ptr->next;
    }
    else if(ptr->next->id==x){
        struct product*b=ptr->next->next;
        total_price-=((ptr->next->price)*(ptr->next->items));
        ptr->next=b;
    }
    else{
        while(ptr->next->id!=x){
        ptr=ptr->next;
        }
        total_price-=((ptr->next->price)*(ptr->next->items));
        struct product*b=ptr->next->next;
        ptr->next=b;
    }
    struct product *temp;
    temp=root;
    root->id=1;
    int i=2;
    while(temp->next!=NULL){
        temp->next->id=i;
        temp=temp->next;
        i++;
    }

}

void go_to_cart()
{
   struct product *temp;
   temp=root;
   if(flag==true)
    return;
        if(root==NULL){
            cout<<"---------------------------------------\n";
            cout<<"Your Cart is Empty\n";
        }
        else
        {
            for(int j=0;j<90;j++){
            cout<<"-";
            }
            cout<<"\n";
            cout<<left<<setw(7)<<"index"<<left<<setw(12)<<"Brand"<<left<<setw(35)<<"Name"<<left<<setw(12)<<" Price"<<left<<setw(14)<<" no. of items\n";
            for(int j=0;j<90;j++){
                cout<<"-";
            }
            cout<<"\n";
            while(temp!=NULL)
            {
                 cout<<left<<setw(7)<<temp->id<<left<<setw(12)<<temp->brand<<left<<setw(35)<<temp->name<<left<<setw(12)<<temp->price<<left<<setw(14)<<temp->items<<endl;
                temp=temp->next;
            }
            cout<<endl;
            cout<<endl;
        }
        cout<<"\n----------------------\n";
        cout<<"Total Price :"<<total_price;
        cout<<"\n----------------------\n\n\n";
        for(; ;)
        {
            if(flag==true){
                return ;
            }
        cout<<"1. Remove item from the cart\n";
        cout<<"2. Continue shopping\n";
        cout<<"3. Confirm Order\n";

        cout<<"\n Enter choice :";
        int ch;
        cin>>ch;
        if(ch==1){
            Delete_from_cart();
            // flag=true;

            break;
        }
        else if(ch==2)
            start();
          else if(ch==3)
          {
            cout<<"Total price : "<<total_price<<endl;
            cout<<" Thank you for the shopping \n";
            flag=true;
            return ;
          }
          else
            cout<<"Enter correct choice\n";
        }
}

void add_to_cart(string brand1,string name1,int price1,int items1)
{
    struct product *temp,*ptr;
    temp=new product();
    temp->name=name1;
    temp->brand=brand1;
    temp->price=price1;
    temp->items=items1;
    temp->next=NULL;
    total_price+=(price1*items1);
    if(root==NULL)
    {
       root=temp;
       root->id=1;
    }
    else
    {
        ptr=root;
        int i=2;
        while(ptr->next!=NULL){
            i++;
            ptr=ptr->next;
        }
        ptr->next=temp;
        ptr->next->id=i;
    }
    cout<<"\nitem  successfully added to the cart\n";
    for(; ;)
    {
        if(flag==true){
            return ;
        }
     cout<<"1. Go to Cart\n";
    cout<<"2. Continue shopping\n";
    cout<<"Enter choice :";
    int ch;
    cin>>ch;
    if(ch==1)
        go_to_cart();
    else if(ch==2)
        start();
    else
        cout<<"Enter correct choice\n";
    }
}

void sort_by_brand(struct product main[],int size)
{
     string Brand;
     if(flag==true)
        return ;
     cout<<"Enter Brand Name :";
     cin>>Brand;
     int count=0,i;
     for(i=0;i<size;i++)
     {
         if(compare(Brand,main[i].brand))
             count++;
     }
     if(count==0)
     cout<<"Brand doesn't exist , please enter correct brand\n\n";
     else
     {
         cout<<left<<setw(7)<<"index"<<left<<setw(12)<<"Brand"<<left<<setw(35)<<"Name"<<left<<setw(12)<<" Price"<<left<<setw(12)<<" Stock\n";
          for(i=0;i<73;i++)
           cout<<"-";
          cout<<endl;
         for(i=0;i<size;i++)
         {
             if(compare(Brand,main[i].brand))
             {
                 cout<<left<<setw(7)<<i+1<<left<<setw(12)<<main[i].brand<<left<<setw(35)<<main[i].name<<left<<setw(12)<<main[i].price;
                 if(main[i].stock==0)
                    cout<<setw(12)<<"Out of stock\n";
                 else
                    cout<<setw(12)<<main[i].stock<<endl;
             }
         }
         cout<<endl<<endl;
         for(; ;)
         {
             if(flag==true)
                return;
             cout<<"1. Buy\n";
             cout<<"2. Add to cart\n";
             cout<<"3. Go to Cart\n";
             cout<<"4. Go to previous Menu\n";
             cout<<"5. Go to Main Menu\n";
             cout<<"\nEnter choice :";
             int c;
             cin>>c;
             if(c==1||c==2)
             {
                 cout<<"Enter index of the product :";
                 int in;
                 cin>>in;
                 if(in>0&&in<=size)
                 {
                     cout<<"How many items :";
                     int qnty;
                     cin>>qnty;
                     if(qnty<=main[in-1].stock&&qnty>0)
                     {
                         main[in-1].stock=main[in-1].stock-qnty;
                         add_to_cart(Brand,main[in-1].name,main[in-1].price,qnty);
                        if(c==1)
                       go_to_cart();
                        else
                        cout<<"item added to cart successfully\n\n";
                     }
                     else
                        cout<<qnty<<" items are not available\n"<<endl;
                 }
                 else
                 cout<<"Invalid index\n";
             }
             else if(c==3)
             go_to_cart();
             else if(c==4)
             break;
             else if(c==5)
             start();
             else
             cout<<"Enter Correct choice\n\n";
         }
     }
}



void show(struct product main[],int size)
{
    start:
        if(flag==true)
            return ;
    for(int j=0;j<73;j++){
        cout<<"-";
    }
    cout<<"\n";
    // cout<<"----------------------------------------------------------------\n";
    cout<<left<<setw(7)<<"index"<<left<<setw(12)<<"Brand"<<left<<setw(35)<<"Name"<<left<<setw(12)<<" Price"<<left<<setw(12)<<" Stock";
    // cout<<"----------------------------------------------------------------\n";
    cout<<"\n";
    for(int j=0;j<73;j++){
        cout<<"-";
    }
    cout<<"\n";
    for(int i=0;i<size;i++)
    {
     cout<<left<<setw(7)<<i+1<<left<<setw(12)<<main[i].brand<<left<<setw(35)<<main[i].name<<left<<setw(12)<<main[i].price;
     if(main[i].stock==0)
        cout<<setw(12)<<"Out of stock\n";
     else
        cout<<setw(12)<<main[i].stock<<endl;
    }

    for(; ;)
    {
        int c,index;
        if(flag==true){
            return;
        }
    cout<<"1. Buy\n";
    cout<<"2. Add to cart\n";
    cout<<"3. Go to Cart\n";
    cout<<"4. previous Menu\n";
    cout<<"5. Sort By Brand\n";
    cout<<"6. Sort By Price\n";
    cout<<"\n Enter choice : ";
       cin>>c;
       if(c==1)
       {
           cout<<"Enter index of the product\n";
           cin>>index;
           if(index>0&&index<=size)
           {
               cout<<"how many items :";
               int s;
               cin>>s;
               if(s>0&&s<=main[index-1].stock)
               {
                   main[index-1].stock=main[index-1].stock-s;
                   cout<<"-------------------------------------------------------------------\n";
                   cout<<"Your order : "<<main[index-1].brand<<" : "<<main[index-1].name<<" booked successfully\n";
                   cout<<"Thank you for shopping\n";
                   cout<<"\n-------------------------------------------------------------------\n";
                   flag=true;
                   return ;
               }
               else
               {
                cout<<s<<" items are not available\n";
                goto start;
               }
           }
           else
           {
            cout<<"Entered index doesn't exist\n";
            goto start;
           }
       }
       else if(c==2)
       {
           cout<<"Enter index of the product\n";
           cin>>index;
            cout<<"how many items :";
               int s;
               cin>>s;
               if(s>0&&s<=main[index-1].stock)
               {
                   main[index-1].stock=main[index-1].stock-s;
                   add_to_cart(main[index-1].brand,main[index-1].name,main[index-1].price,s);
               }
               else
               {
                cout<<s<<" items are not available\n";
                goto start;
               }
       }
        else if(c==3)
            go_to_cart();
       else if(c==4)
        break;
        else if(c==5)
        {
        sort_by_brand(main,size);
        goto start;
        }
        else if(c==6){
            int h;
            cout<<"1. Sort: High-to-Low\n";
            cout<<"2. Sort: Low-to-High\n";
            cout<<"Enter choice: ";
            cin>>h;
            if(h==1){
                for(int i=0;i<size;i++){
                    for(int j=i+1;j<size;j++){
                        int temp1=0,temp2=0;
                        if(main[i].price < main[j].price){
                            temp1=main[i].price;
                            main[i].price=main[j].price;
                            main[j].price=temp1;

                            temp2=main[i].stock;
                            main[i].stock=main[j].stock;
                            main[j].stock=temp2;

                            main[i].name.swap(main[j].name);

                            main[i].brand.swap(main[j].brand);
                        }
                    }
                }
                show(main,size);
            }
            else if(h==2){

                for(int i=0;i<size;i++){
                    for(int j=i+1;j<size;j++){
                        int temp1=0,temp2=0;
                        if(main[i].price > main[j].price){
                            temp1=main[i].price;
                            main[i].price=main[j].price;
                            main[j].price=temp1;

                            temp2=main[i].stock;
                            main[i].stock=main[j].stock;
                            main[j].stock=temp2;

                            main[i].name.swap(main[j].name);

                            main[i].brand.swap(main[j].brand);
                        }
                    }
                }
                show(main,size);
            }
        }
        else
            cout<<"Enter correct choice\n";
    }
}

void list_laptop()
{
    //for laptop 1
    laptop[0].price=88490;
    laptop[0].name="Macbook Air 2020";
    laptop[0].brand="Apple";
    laptop[0].stock=3;
    //for laptop 2
    laptop[1].price=26990;
    laptop[1].name="Chromebook 14-inch";
    laptop[1].brand="HP";
    laptop[1].stock=3;
    //for laptop 3
    laptop[2].price=99990;
    laptop[2].name="Zenbook 13";
    laptop[2].brand="ASUS";
    laptop[2].stock=3;
    //for laptop 4
    laptop[3].price=57990;
    laptop[3].name="TUF Gaming F15";
    laptop[3].brand="ASUS";
    laptop[3].stock=3;
    //for laptop 5
    laptop[4].price=123990;
    laptop[4].name="Surface Laptop 14";
    laptop[4].brand="Microsoft";
    laptop[4].stock=3;
    //for laptop 6
    laptop[5].price=53990;
    laptop[5].name="Inspiron 3510";
    laptop[5].brand="Dell";
    laptop[5].stock=3;
    //for laptop 7
    laptop[6].price=62990;
    laptop[6].name="Pavilion Gaming Laptop";
    laptop[6].brand="HP";
    laptop[6].stock=3;
    //for laptop 8
    laptop[7].price=179990;
    laptop[7].name="Macbook Pro 2020";
    laptop[7].brand="Apple";
    laptop[7].stock=3;
    //for laptop 9
    laptop[8].price=56990;
    laptop[8].name="Pavilion 15";
    laptop[8].brand="HP";
    laptop[8].stock=3;
    //for laptop 10
    laptop[9].price=36990;
    laptop[9].name="Vivobook 14";
    laptop[9].brand="ASUS";
    laptop[9].stock=3;
    //for laptop 11
    laptop[10].price=101990;
    laptop[10].name="Surface Pro X";
    laptop[10].brand="Microsoft";
    laptop[10].stock=3;
    //for laptop 12
    laptop[11].price=67990;
    laptop[11].name="Thinkbook 15";
    laptop[11].brand="Lenovo";
    laptop[11].stock=3;
    //for laptop 13
    laptop[12].price=44990;
    laptop[12].name="ThinkPad E15";
    laptop[12].brand="Lenovo";
    laptop[12].stock=3;
    //for laptop 14
    laptop[13].price=56750;
    laptop[13].name="Vostro 3400";
    laptop[13].brand="Dell";
    laptop[13].stock=3;
    //for laptop 15
    laptop[14].price=36990;
    laptop[14].name="IdeaPad Slim 3";
    laptop[14].brand="Lenovo";
    laptop[14].stock=3;
}
void list_ac()
{
    //for ac 1
    ac[0].price=34490;
    ac[0].name="AB01 1.5-TON Split AC";
    ac[0].brand="BlueStar";
    ac[0].stock=3;
    //for ac 2
    ac[1].price=41999;
    ac[1].name="AH01 2-TON Split AC";
    ac[1].brand="Hitachi";
    ac[1].stock=4;
    //for ac 3
    ac[2].price=32950;
    ac[2].name="AV01 1.5-TON Split AC";
    ac[2].brand="Voltas";
    ac[2].stock=4;
    //for ac 4
    ac[3].price=31490;
    ac[3].name="AB02 1-TON Split AC";
    ac[3].brand="BlueStar";
    ac[3].stock=4;
    //for ac 5
    ac[4].price=29999;
    ac[4].name="AH02 1-TON Split AC";
    ac[4].brand="Hitachi";
    ac[4].stock=4;
    //for ac 6
    ac[5].price=27950;
    ac[5].name="AV02 1-TON Split AC";
    ac[5].brand="Voltas";
    ac[5].stock=4;
    //for ac 7
    ac[6].price=49990;
    ac[6].name="AB03 2-TON Split AC";
    ac[6].brand="BlueStar";
    ac[6].stock=4;
    //for ac 8
    ac[7].price=33990;
    ac[7].name="AH03 1.5-TON Split AC";
    ac[7].brand="Hitachi";
    ac[7].stock=4;
    //for ac 9
    ac[8].price=43990;
    ac[8].name="AV03 2-TON Split AC";
    ac[8].brand="Voltas";
    ac[8].stock=4;
    //for ac 10
    ac[9].price=32990;
    ac[9].name="AS01 1.5-TON Split AC";
    ac[9].brand="Samsung";
    ac[9].stock=4;
    //for ac 11
    ac[10].price=37490;
    ac[10].name="AL01 1.5-TON Split AC";
    ac[10].brand="Lloyd";
    ac[10].stock=4;
    //for ac 12
    ac[11].price=33499;
    ac[11].name="AL02 1-TON Split AC";
    ac[11].brand="Lloyd";
    ac[11].stock=4;
    //for ac 13
    ac[12].price=30990;
    ac[12].name="AS02 1-TON Split AC";
    ac[12].brand="Samsung";
    ac[12].stock=4;
    //for ac 14
    ac[13].price=46990;
    ac[13].name="AD01 1.5-TON Split AC";
    ac[13].brand="Daikin";
    ac[13].stock=4;
    //for ac 15
    ac[14].price=39990;
    ac[14].name="AL02 1-TON Split AC";
    ac[14].brand="Daikin";
    ac[14].stock=4;
}
void list_fridge()
{
    //for fridge 1
    fridge[0].price=74990;
    fridge[0].name="FSA01 700L Side-By-Side";
    fridge[0].brand="Samsung";
    fridge[0].stock=6;
    //for fridge 2
    fridge[1].price=95040;
    fridge[1].name="FL01 675L Side-By-Side";
    fridge[1].brand="LG";
    fridge[1].stock=6;
    //for fridge 3
    fridge[2].price=23590;
    fridge[2].name="FH01 256L Double-Door";
    fridge[2].brand="Haier";
    fridge[2].stock=6;
    //for fridge 4
    fridge[3].price=71990;
    fridge[3].name="FSA02 580L Side-By-Side";
    fridge[3].brand="Samsung";
    fridge[3].stock=6;
    //for fridge 5
    fridge[4].price=15490;
    fridge[4].name="FL02 190L Single-Door";
    fridge[4].brand="LG";
    fridge[4].stock=6;
    //for fridge 6
    fridge[5].price=34490;
    fridge[5].name="FH02 346L Double-Door";
    fridge[5].brand="Haier";
    fridge[5].stock=6;
    //for fridge 7
    fridge[6].price=24990;
    fridge[6].name="FSA03 253L Double-Door";
    fridge[6].brand="Samsung";
    fridge[6].stock=6;
    //for fridge 8
    fridge[7].price=24990;
    fridge[7].name="FL03 260L Double-Door";
    fridge[7].brand="LG";
    fridge[7].stock=6;
    //for fridge 9
    fridge[8].price=17290;
    fridge[8].name="FH03 242L Single-Door";
    fridge[8].brand="Haier";
    fridge[8].stock=6;
    //for fridge 10
    fridge[9].price=12390;
    fridge[9].name="FSA04 192L Single-Door";
    fridge[9].brand="Samsung";
    fridge[9].stock=6;
    //for fridge 11
    fridge[10].price=38990;
    fridge[10].name="FL04 360L Double-Door";
    fridge[10].brand="LG";
    fridge[10].stock=6;
    //for fridge 12
    fridge[11].price=58990;
    fridge[11].name="FH04 570L Side-By-Side";
    fridge[11].brand="Haier";
    fridge[11].stock=6;
    //for fridge 13
    fridge[12].price=33790;
    fridge[12].name="FSA05 324L Double-Door";
    fridge[12].brand="Samsung";
    fridge[12].stock=6;
    //for fridge 14
    fridge[13].price=31490;
    fridge[13].name="FL05 284L Double-Door";
    fridge[13].brand="LG";
    fridge[13].stock=6;
    //for fridge 15
    fridge[14].price=32490;
    fridge[14].name="FH05 345L Double-Door";
    fridge[14].brand="Haier";
    fridge[14].stock=6;
}
void list_tv()
{
    //for tv 1
    tv[0].price=17490;
    tv[0].name="SA01 HD TV-32 inch";
    tv[0].brand="Samsung";
    tv[0].stock=6;
    //for tv 2
    tv[1].price=37499;
    tv[1].name="L01 4K Ultra HD TV-43 inch";
    tv[1].brand="LG";
    tv[1].stock=5;
    //for tv 3
    tv[2].price=25490;
    tv[2].name="S01 HD TV-32 inch";
    tv[2].brand="Sony";
    tv[2].stock=6;
    //for tv 4
    tv[3].price=36990;
    tv[3].name="SA02 4K Ultra HD TV-43 inch";
    tv[3].brand="Samsung";
    tv[3].stock=4;
    //for tv 5
    tv[4].price=52999;
    tv[4].name="L02 4K Ultra HD TV-55 inch";
    tv[4].brand="LG";
    tv[4].stock=4;
    //for tv 6
    tv[5].price=40990;
    tv[5].name="S02 HD TV-43 inch";
    tv[5].brand="Sony";
    tv[5].stock=4;
    //for tv 7;
    tv[6].price=51990;
    tv[6].name="SA03 4K Ultra HD TV-55 inch";
    tv[6].brand="Samsung";
    tv[6].stock=3;
    //for tv 8
    tv[7].price=83599;
    tv[7].name="L03 4K Ultra HD TV-65 inch";
    tv[7].brand="LG";
    tv[7].stock=1;
    //for tv 9
    tv[8].price=54990;
    tv[8].name="S03 4K Ultra HD TV-43 inch";
    tv[8].brand="Sony";
    tv[8].stock=1;
    //for tv 10
    tv[9].price=48990;
    tv[9].name="SA04 4K Ultra HD TV-50 inch";
    tv[9].brand="Samsung";
    tv[9].stock=3;
    //for tv 11
    tv[10].price=89999;
    tv[10].name="L04 4K Ultra HD OLED TV-48 inch";
    tv[10].brand="LG";
    tv[10].stock=3;
    //for tv 12
    tv[11].price=105990;
    tv[11].name="S04 4K Ultra HD TV-65 inch";
    tv[11].brand="Sony";
    tv[11].stock=5;
    //for tv 13
    tv[12].price=89990;
    tv[12].name="SA05 4K Ultra HD TV-65 inch";
    tv[12].brand="Samsung";
    tv[12].stock=1;
    //for tv 14
    tv[13].price=51999;
    tv[13].name="L05 4K Ultra HD TV-50 inch";
    tv[13].brand="LG";
    tv[13].stock=5;
    //for tv 15
    tv[14].price=72990;
    tv[14].name="S05 4K Ultra HD TV-55 inch";
    tv[14].brand="Sony";
    tv[14].stock=3;
}
void list_mobiles()
{
    //for mobile 1
    mobile[0].price=7990;
    mobile[0].name="A12";
    mobile[0].brand="Oppo";
    mobile[0].stock=3;
    //for mobile 2
    mobile[1].price=24000;
    mobile[1].name="Y21e";
    mobile[1].brand="Vivo";
    mobile[1].stock=4;
    //for mobile 3
    mobile[2].price=11200;
    mobile[2].name="Y20A";
    mobile[2].brand="Vivo";
    mobile[2].stock=6;
    //for mobile 4
    mobile[3].price=35999;
    mobile[3].name="A52s";
    mobile[3].brand="Samsung";
    mobile[3].stock=2;
    //for mobile 5
    mobile[4].price=8990;
    mobile[4].name="A33";
    mobile[4].brand="Oppo";
    mobile[4].stock=4;
    //for mobile 6
    mobile[5].price=13499;
    mobile[5].name="A12";
    mobile[5].brand="Samsung";
    mobile[5].stock=4;
    //for mobile 7;
    mobile[6].price=11249;
    mobile[6].name="A035";
    mobile[6].brand="Samsung";
    mobile[6].stock=1;
    //for mobile 8
    mobile[7].price=17990;
    mobile[7].name="F17pro";
    mobile[7].brand="Oppo";
    mobile[7].stock=8;
    //for mobile 9
    mobile[8].price=14990;
    mobile[8].name="A54";
    mobile[8].brand="Oppo";
    mobile[8].stock=3;
    //for mobile 10
    mobile[9].price=34300;
    mobile[9].name="X60";
    mobile[9].brand="Vivo";
    mobile[9].stock=1;
    //for mobile 11
    mobile[10].price=10789;
    mobile[10].name="M12";
    mobile[10].brand="Samsung";
    mobile[10].stock=4;
    //for mobile 12
    mobile[11].price=10990;
    mobile[11].name="A15";
    mobile[11].brand="Oppo";
    mobile[11].stock=2;
    //for mobile 13
    mobile[12].price=10100;
    mobile[12].name="Y125";
    mobile[12].brand="Vivo";
    mobile[12].stock=1;
    //for mobile 14
    mobile[13].price=9490;
    mobile[13].name="Y15";
    mobile[13].brand="Vivo";
    mobile[13].stock=3;
    //for mobile 15
    mobile[14].price=9000;
    mobile[14].name="M02s";
    mobile[14].brand="Samsung";
    mobile[14].stock=7;
}
void list_sports()
{
     //for sports equipment 1
    sports[0].price=1795;
    sports[0].name="Liverpool F.C.(football)";
    sports[0].brand="Nike";
    sports[0].stock=3;
    //for sports equipment 2
    sports[1].price=9099;
    sports[1].name="evoPOWER 4.17 SNR bat";
    sports[1].brand="Puma";
    sports[1].stock=4;
    //for sports equipment 3
    sports[2].price=11200;
    sports[2].name="Scorer Cricket Bat";
    sports[2].brand="SG";
    sports[2].stock=6;
    //for sports equipment 4
    sports[3].price=1595;
    sports[3].name="Nike Jr. Goalkeeper Match";
    sports[3].brand="Nike";
    sports[3].stock=2;
    //for sports equipment 5
    sports[4].price=8990;
    sports[4].name="Nike AeroBill(Cap)";
    sports[4].brand="Nike";
    sports[4].stock=4;
    //for sports equipment 6
    sports[5].price=4499;
    sports[5].name="evo 1 batting pad";
    sports[5].brand="Puma";
    sports[5].stock=4;
    //for sports equipment 7;
    sports[6].price=11249;
    sports[6].name="RP Lite Batting Gloves";
    sports[6].brand="SG";
    sports[6].stock=1;
    //for sports equipment 8
    sports[7].price=1499;
    sports[7].name="Neymar Jr. Shin Guards";
    sports[7].brand="Puma";
    sports[7].stock=8;
    //for sports equipment 9
    sports[8].price=1490;
    sports[8].name="SG Test™ Leather Ball";
    sports[8].brand="SG";
    sports[8].stock=3;
    //for sports equipment 10
    sports[9].price=3490;
    sports[9].name="MY FIRST KIT (KL Rahul)";
    sports[9].brand="SG";
    sports[9].stock=1;

}
void show_electronics()
{
    cout<<"--------------------------------------\n";
    cout<<"Electronics Products\n";
    cout<<"--------------------------------------\n";
    int c;
    for(; ;)
    {
        if(flag)
        return ;
        cout<<"1. TV\n";
        cout<<"2. Fridge\n";
        cout<<"3. AC\n";
        cout<<"4. Laptop\n";
        cout<<"5. Go to Main Menu\n";
        cout<<"6. Go to cart\n";
        cout<<"\n Enter choice: ";
        cin>>c;
        if(c==1)
            show(tv,15);
        else if(c==2)
            show(fridge,15);
        else if(c==3)
            show(ac,15);
        else if(c==4)
            show(laptop,15);
        else if(c==5)
            start();
        else if(c==6)
            go_to_cart();
        else
            cout<<"Enter correct choice.\n";
    }
}
void start()
{
    int c;
    if(flag==true)
        return;
        for(int i=0 ; ;)
      {
        if(flag==true)
        return ;
      cout<<"1. Electronics\n";
      cout<<"2. Mobiles\n";
      cout<<"3. Sports Equipments\n";
      cout<<"4. Go to cart\n";
      cout<<"5. Exit\n";

      cout<<"\nEnter Choice: ";
      cin>>c;

      if(c==1)
        show_electronics();
      else if(c==2)
        show(mobile,15);
      else if(c==3)
        show(sports,10);
        else if(c==4)
            go_to_cart();
      else if(c==5)
      {
        cout<<"Thank You\n";
        flag=true;
        break;
      }
      else
        cout<<"Enter Correct Choice\n";
    }
}

int main()
{
    list_ac();
    list_tv();
    list_fridge();
    list_laptop();
    list_mobiles();
    list_sports();
    cout<<"----------------------------------------------------\n";
    cout<<"\t Welcome to Our Shopping site\n";
    cout<<"----------------------------------------------------\n\n";
    start();
    if(flag)
    return 0;
}