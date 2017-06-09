#include <iostream>
#include <conio.h>
#include <fstream>
#include <windows.h>
using namespace std;



class Snake
{

public:
	Snake()
	{
		wight=25;
		height=20;
		sleep=100;
	}
	bool game_over;
	bool lock ;

	int wight;
	int height;
	int x,y,sleep;

	void start()
	{
		setup();
		system("Color 2f");
		game_over=false;
		while (!game_over)
		{
			input();

			draw();
			//input();
			logic();
			Sleep(sleep);

		}
		gameOver();
	}
	
protected:
	int fruitx,fruity,score,best_score;
	int tailx[100],taily[100];
	int ntail;
	enum eDirection {STOP= 0,LEFT,RIGHT,UP,DOWN};
	eDirection dir;

	void setup()
	{
		optionsGet();
		game_over = false;
		dir = STOP;
		x = wight / 2;
		y = height / 2;
		fruitx =rand() % wight;
		fruity =rand() % height;
		score=0;
		ntail=0;

	}
	void draw()
	{
		system("cls");
		for(int i =0; i<wight+1;i++)
			cout<<"#";
		cout<<endl;
		for(int i=0;i<height;i++)
		{

			for(int j=0;j<wight;j++)
			{
				if(j==0)
					cout<<"#";
				if(i==y&&j==x)
					cout<<"O";
				else if(i==fruity &&j==fruitx)
					cout<<"@";
				else
				{
					bool tail=false;
					for(int k=0;k<ntail;k++)
					{

						if(tailx[k]==j&&taily[k]==i)
						{
							cout<<"*";
							tail=true;
						}
					}
					if(!tail)
						cout<<" ";
				}
				if(j==wight-1)
					cout<<"#";
			}
			cout<<endl;
		}
		for(int i =0; i<wight+1;i++)
			cout<<"#";
		cout<<endl;
		cout<<"Score: "<<score<<endl;
		cout<<"move with the arrows"<<endl;

	}
	void input()
	{
		if(_kbhit())
		{
			switch (_getch())
			{
			case 75:
				dir=LEFT;
				break;
			case 77:
				dir=RIGHT;
				break;
			case 72:
				dir=UP;
				break;
			case 80:
				dir=DOWN;
				break;
			case'o':
				game_over=true;
				break;
			}
		}
	}
	void bestScoreWrite(int bs){
		ofstream outfile;
		outfile.open("bestscore.txt");
		outfile.clear();
		outfile << bs << endl;
		outfile.close();
	}
	int bestScoreRead(){
		ifstream infile;
		infile.open("bestscore.txt");
		int x = 0;
		infile >> x;
		infile.close();
		return x;
	}
	void optionsGet(){
		ifstream infile;
		infile.open("options.txt");
		char x[6];
		infile >> x;
		infile.close();
	
		switch (x[0])
		{
		case '1':
			lock = true;
			break;
		case '0':
			lock = false;
			break;
		default:
			lock = false;
			break;
		}
		switch (x[1])
		{case '2':
			if (x[2] == '5')
			{
				wight = 30;
				height = 20;
			}
			else{
				wight = 20;
				height = 20;
			}
			break;
		case '3':
			wight = 30;
			height = 25;
			break;
		default:
			wight = 25;
			height = 20;
			break;
		}
		switch (x[3])
		{
		case '3':
			sleep = 300;
			break;
		case '1':
			sleep = 100;
			break;
		case '0':
			sleep = 0;
			break;

		default:
			sleep = 100;
			break;
		}

	}
	void bestScore()
	{
		best_score=bestScoreRead();
		if(score>best_score)
			best_score=score;
		cout<<"Best Score :"<<best_score<<endl;
		bestScoreWrite(best_score);
		
		return;
	}
	void logic()
	{

		int prevx=tailx[0];
		int prevy=taily[0];
		int prevx2,prevy2;
		for(int i=1;i<ntail;i++)
		{
			prevx2=tailx[i];
			prevy2=taily[i];
			tailx[i]=prevx;
			taily[i]=prevy;
			prevx=prevx2;
			prevy=prevy2;
			tailx[0]=x;
			taily[0]=y;

		}
		switch (dir)
		{
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
		default:
			break;
		}
		if(lock==false)
		{
			if(x >=wight)
				x=0;
			else if(x<0) 
				x=wight-1;
			if(y >=height)
				y=0;
			else if(y<0) 
				y=height-1;
		}
		else if(lock==true)
		{

			if(x>wight||x<0||y>height||y<0)
				game_over=true;
		}
		for(int i=0;i<ntail;i++)
		{
			if(tailx[i] == x && taily[i] == y)
				game_over=true;
		}
		if(x==fruitx&&y==fruity)
		{
			score=score+10;
			fruitx =rand() % wight;
			fruity =rand() % height;
			ntail=ntail+1;
		}
	}
	
	void gameOver()
	{
		system("cls");
		cout<<"Game Over"<<endl<<"score :"<<score<<endl;
		bestScore();
		cout << endl;
		char key;
		cout<<"start game press s"<<endl;
		cout<<" quit press q"<<endl;
		cout<<":->";
		cin>>key;
		switch (key)
		{
		case 's':
			start();
			break;
		case 'S':
			start();
			break;
		case 'q':
			
			
			return;
			break;
		case 'Q':
			
			

			return;
			break;

		}
		
	
		cin.get();
	}

};


class options
{
public:
	options()
	{
	}
	int x,y;
	
	void optionsMenu(Snake s)
	{
		system("cls");
		cout<<"* choose the option *"<<endl;
		int op;
		cout<<"1-map locked"<<endl;
		cout<<"2-map size"<<endl;
		cout<<"3-game speed"<<endl;
		cout<<"4-to go back to main menu"<<endl;
		cout<<":->";
		cin>>op;
		switch (op)
		{
		case 1:
			option1(s);
			break;
		case 2:
			mapSize(s);
			break;
		case 3:
			speed(s);
			break;
		case 4:
			optionSave(s);
			system("cls");
			char key;
			cout<<"start game press s"<<endl;
			cout<<" quit press q"<<endl;
			cout<<":->";
			cin>>key;
			switch (key)
			{
			case 's':
				s.start();
				break;
			case 'S':
				s.start();
				break;
			case 'q':
				
				return;
				break;
			case 'Q':
				
				return;
				break;
			}
			break;

		default:
			optionsMenu(s);
			break;
		}
	}
protected:
	void optionSave(Snake s){
		ofstream outfile;
		outfile.open("options.txt");
		outfile.clear();
		int first,second ,therd;
		if (s.lock){
			first = 1;
		}
		else{
			first = 0;
		}
		
		second = s.wight;
		
		therd = s.sleep;
		outfile << first << second << therd;
		outfile.close();
	}
	void option1(Snake s)
	{
		system("cls");
		char l;
		cout<<"do you want a locked the map choose (y,n)"<<endl<<":->";
		cin>>l;

		switch (l)
		{
		case 'y':
			s.lock=true;
			break;
		case 'Y':
			s.lock=true;
			break;
		case 'n':
			s.lock=false;
			break;
		case 'N':
			s.lock=false;
			break;

		default:
			cout<<"please choose 'y' or 'n'"<<endl;

			option1( s);
			break;
		}
	
		optionsMenu(s);
	}
	void mapSize(Snake s)
	{
		system("cls");
		int size;
		cout<<"Choose a size"<<endl;
		cout<<"1-small"<<endl;
		cout<<"2-medium"<<endl;
		cout<<"3-large"<<endl;
		cout<<":->";
		cin>>size;
		switch (size)
		{
		case 1:
			x=y=20;
			break;
		case 2:
			x=25;
			y=20;
			break;
		case 3:
			x=30;
			y=25;
			break;
		default:
			cout<<"please choose betwen 1,2,3"<<endl;
			mapSize(s);
			break;
		}
		x=s.wight;
		y=s.height;
		optionsMenu(s);
	}
	void speed(Snake s)
	{
		system("cls");
		cout<<"* Game speed *"<<endl;
		cout<<"1-slow"<<endl;
		cout<<"2-normal"<<endl;
		cout<<"3-fast"<<endl;
		cout<<":->";
		int key;
		cin>>key;
		switch (key)
		{
		case 1:
			s.sleep=500;
			break;
		case 2:
			s.sleep=100;
			break;
		case 3:
			s.sleep=0;
			break;
	
		default:
			speed(s);
			break;
		}
		optionsMenu(s);
	}
};


void  startMenu(Snake s,options o);	 


void main()
{

	Snake game;
	options option;
	startMenu( game, option);


}

void startMenu(Snake s,options o)
{
	char key;
	cout<<"start game press s"<<endl;
	cout<<"options press o"<<endl;
	cout<<" quit press q"<<endl;
	cout<<":->";
	cin>>key;
	switch (key)
	{
	case 's':
		s.start();
		break;
	case 'S':
		s.start();
		break;
	case 'o':
		o.optionsMenu(s);

		break;
	case 'O':
		o.optionsMenu(s);
		break;
	case 'q':
		
		return;
		break;
	case 'Q':
		
		return;
		break;
	default:
		startMenu(s,o);
		break;
	}
}
