#include<cstdlib>
#include<iostream>
#include<iomanip>
#include<string>

using namespace std;

int level(void);
void initialState(char vis_table[],char real_table[],int n);
void printTable(char vis_table[],int n);
void getneighbors(int neighbors[],int pos,int n);
bool isRealNeighbor(int index,int pos,int n);
void placeMines(char real_table[],int n,int mines);
void calculateNumbers(char real_table[],int n);
char countMines(char real_table[],int neighbors[],int pos,int n);
void openSafe(char real_table[],char vis_table[],int n,int pos,int &counter);
void play(char real_table[],char vis_table[],int n,int mines);

int main(void)
{
    int n,mines;
    printf("  ### MINESWEEPER ###\n");
    n=level();         //Difficulty Selection
    if(n==9)
        mines=10;
    else
        mines=40;
    char real_table[n*n];
    char vis_table[n*n];
    srand(time(NULL));
    initialState(vis_table,real_table,n);
    placeMines(real_table,n,mines);
    calculateNumbers(real_table,n);
    play(real_table,vis_table,n,mines);
    return 0;
}

int level(void)
{
    int c,n;
    printf("\n1)NORMAL\t2)EXPERT\nEnter the difficulty:");
    scanf("%d",&c);
    if(c==1)
        n=9;
    else if(c==2)
        n=16;
    else
    {
        printf("\n\tWrong choice...");
        exit(0);
    }
    return n;
}
void initialState(char vis_table[],char real_table[],int n)
{
    for(int i=0;i<(n*n);i++)
    {
        vis_table[i]='-';
        real_table[i]='-';
    }
    return;
}

void printTable(char vis_table[],int n)
{
    cout<<"\n";
    cout<<"  ";
    for(int i=1;i<=n;i++)
    {
        if(i<10)
            cout<<"  "<<i;
        else
            cout<<" "<<i;

    }
    cout<<endl;
    for(int i=0;i<n;i++)
    {
        if(i<9)
            cout<<" "<<i+1<<"  ";
        else
            cout<<i+1<<"  ";
        for(int j=0;j<n;j++)
        {
            cout<<vis_table[n*i+j]<<"  ";
        }
        cout<<endl;
    }
    return;
}

void placeMines(char real_table[], int n, int mines)
{
    int mine;
    int num_mines=0;

    while(num_mines<mines)
    {
        mine=rand()%(n*n);
        if(real_table[mine]!='*')
        {
            real_table[mine]='*';
            num_mines++;
        }
    }
    return;
}

void calculateNumbers(char real_table[], int n)
{
    int neighbors[8];
    for(int i=0;i<n*n;i++)
    {
        if(real_table[i]!='*')
        {
        getneighbors(neighbors,i,n);
        real_table[i]=countMines(real_table,neighbors,i,n);
        }
    }
    return;
}

void getneighbors(int neighbors[],int pos,int n)
{
    neighbors[0]=(pos-n)-1;
    neighbors[1]=pos-n;
    neighbors[2]=(pos-n)+1;
    neighbors[3]=pos-1;
    neighbors[4]=pos+1;
    neighbors[5]=(pos+n)-1;
    neighbors[6]=(pos+n);
    neighbors[7]=(pos+n)+1;
    return;
}

bool isRealNeighbor(int index,int pos,int n)
{
    if(pos<n)
    {
        if(index==0 || index==1 || index==2)
        {
            return false;
        }
    }
    if(n*(n-1)<=pos)
    {
        if(index==5 || index==6 || index==7)
        {
            return false;
        }
    }
    if(pos%n==0)
    {
        if(index==0 || index==3 || index==5)
        {
            return false;
        }
    }
    if((pos+1)%n==0)
    {
        if(index==2 || index==4 || index==7)
        {
            return false;
        }
    }
    return true;
}

char countMines(char real_table[],int neighbors[],int pos,int n)
{
    int mines=0;
    char value;
    for(int i=0;i<8;i++)
    {
        if(isRealNeighbor(i,pos,n))
        {
            if(real_table[neighbors[i]]=='*')
            {
                mines++;
            }
        }
    }
    if(mines==0)
    {
        value=' ';
    }
    else
    {
        value=(char)(((int)'0')+mines);
    }
    return value;
}

void play(char real_table[],char vis_table[],int n,int mines)
{
    int col;
    char confirm;
    int counter=0;
    char curr_symbol;
    int pos;
    int row;
    string s;
    int safe=n*n-mines;
    do
    {
        printTable(vis_table,n);
        cout<<"\nEnter command: ";
        cin>>row>>col;
        if(cin.eof())
        {
            cerr<<"\n";
            cerr<<"\tInput terminated with end-of-file.\n";
            cerr<<"\t\tGame terminated.\n";
            exit(1);
        }
        if(cin.fail())
        {
            cin.clear();
            cin>>s;
            if(s[0]=='Q')
            {
                cout<<"\n";
                cout<<"\tQUITTING the game... :(\n";
                cout<<"Here is the mine map:\n";
                printTable(real_table,n);
                printf("\n\tPress any key to continue...");
                cin>>confirm;
                return;
            }
            if (s[0]=='F')
            {
                cout<<"\n";
                cout<<"Enter row and column to flag mine: ";
                cin>>row>>col;
                pos=n*(row-1)+(col-1);
                if(vis_table[pos]=='-')
                {
                    vis_table[pos]='?';
                }
                cout<<"\n";
                continue;
            }
            if (s[0]=='U')
            {
                cout<<"\n";
                cout<<"Enter row and column for unflagging: ";
                cin>>row>>col;
                pos=n*(row-1)+(col-1);
                if(vis_table[pos]=='?')
                {
                    vis_table[pos]='-';
                }
                cout<<"Unflagging succesful...\n";
                continue;
            }
            if (s[0]=='H')
            {
                cout<<"\n";
                cout<<"*HELP AND INSTRUCTIONS -->";
                cout<<"\n1. a)The mineboard of normal difficulty is of size 9*9\n   (81 blocks) and has 10 mines.\n";
                cout<<"   b)The mineboard of expert difficulty has size 16*16\n   (256 blocks) and has 40 mines.\n";
                cout<<"2. The first step is to open a random block(s) and hope\n   you have not opened a block with a mine.\n";
                cout<<"3. If you open a non-bomb block, it will either open up\n   to be blank, or will contain a number from 1 to 8.\n";
                cout<<"4. These numbers specify the number of bombs that are\n   adjacent to that block. 1 means there is only 1 bomb\n   adjacent to it, while 8 would mean all blocks \n   adjacent to it are bombs.\n";
                cout<<"5. Next, you need to apply a bit of logic. You need to\n   find out which block will contain the bomb(s). These\n   calculations are to be performed based on multiple\n   blocks that are either clear or contain numbers.\n";
                cout<<"6. You can flag those blocks(F command for flagging and\n   U for unflagging a block) which you think contain\n   mines/bombs.\n";
                cout<<"7. You need to open all blocks without mines to win the\n   game and if you open a mine, the game is lost.\n";
                continue;
            }
            cerr<<"\n";
            cerr<<"PLAY - Warning!!!\n";
            cerr<<"\tThat input was illegal.\n";
            cerr<<"\tPlease enter a row number and a column number...\n";
            continue;
        }

        if (row<1 || n<row || col<1 || n<col)
        {
            cerr<<"\n";
            cerr<<"Your row or column index was illegal.\n";
            cerr<<"Legal values are between 1 and "<<n<<"...\n";
            continue;
        }
        pos=n*(row-1)+(col-1);
        if(vis_table[pos]=='-')
        {
            curr_symbol=real_table[pos];
            vis_table[pos]=curr_symbol;
            if(curr_symbol==' ')
            {
                openSafe(real_table,vis_table,n,pos,counter);
            }
            if(curr_symbol!='*')
            {
                counter++;
            }
        }
    }while(counter<safe&&curr_symbol!='*');
    if(counter==safe)
    {
        printTable(real_table,n);
        cout<<"\n";
        cout<<"You Win!!! :D"<<endl;
    }
    if(curr_symbol=='*')
    {
        for(int i=0;i<n*n;i++)
        {
            if(real_table[i]=='*')
            {
                vis_table[i]='*';
            }
        }
        printTable(vis_table,n);
        cout<<"\n";
        cout<<"You Lose!!!"<<endl;
    }
    return;
}
void openSafe(char real_table[],char vis_table[],int n,int pos,int &counter)
{
    int neighbors[8];
    getneighbors(neighbors,pos,n);
    for(int i=0;i<8;i++)
    {
        if(isRealNeighbor(i,pos,n))
        {
            if(vis_table[neighbors[i]]=='-')
            {
                vis_table[neighbors[i]]=real_table[neighbors[i]];
                counter++;
                if(vis_table[neighbors[i]]==' ')
                {
                    openSafe(real_table,vis_table,n,neighbors[i],counter);
                }
            }
        }
    }
    return;
}
